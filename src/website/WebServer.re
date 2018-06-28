DataProcessor.listen();

let typeDefs = {|
  type Query {
    echo(message: String!): String!
  }

  type Subscription {
    everySecond: Float!
  }

  schema {
    query: Query
    subscription: Subscription
  }
|};

let pubsub = GraphQl.PubSub.make();

Js.Global.setInterval(
  () =>
    pubsub
    |. GraphQl.PubSub.publish("everySecond", {"everySecond": Js.Date.now()}),
  1000,
);

module Http = {
  type server;
  [@bs.module "http"] external createServer : Express.App.t => server = "";
  [@bs.send] external listen : (server, int, Js.Exn.t => unit) => unit = "";
};

module SubscriptionServer = {
  type t;
  [@bs.module "subscriptions-transport-ws"] [@bs.new]
  external make_ :
    (
      {
        .
        "execute": GraphQl.executeT,
        "subscribe": GraphQl.subscribeT,
        "schema": GraphQl.schema,
      },
      {
        .
        "server": Http.server,
        "path": string,
      }
    ) =>
    t =
    "SubscriptionServer";
  let make = (~schema, ~server, ~path) =>
    make_(
      {
        "execute": GraphQl.execute,
        "subscribe": GraphQl.subscribe,
        "schema": schema,
      },
      {"server": server, "path": path},
    );
};

let schema =
  GraphQl.Schema.make(
    ~typeDefs,
    ~resolvers={
      "Query": {
        "echo": (_obj, args, _c, _d) =>
          args
          |> Json.Decode.field("message", Json.Decode.string)
          |> Js.Json.string,
      },
      "Subscription": {
        "everySecond": {
          "subscribe": (_obj, _args, _c, _d) =>
            pubsub |. GraphQl.PubSub.asyncIterator("everySecond"),
        },
      },
    },
  );

[@bs.module] external inlineGlamorStyles : string => string = "glamor/inline";

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

[@bs.module] external fetch : ApolloClient.fetch = "node-fetch";

let apolloClient =
  ReasonApollo.createApolloClient(
    ~link=ApolloSchemaLink.make(~schema),
    ~cache=inMemoryCache,
    ~ssrMode=true,
    (),
  );

[@bs.val] [@bs.module "glamor/server"]
external renderStatic :
  (unit => string) =>
  {
    .
    "html": string,
    "css": string,
    "ids": Js.Json.t,
  } =
  "";

module Template = {
  let make = (~content, ~helmet, ()) => {
    let bodyAttributes = helmet |. Helmet.bodyAttributes |> Helmet.toString;
    let htmlAttributes = helmet |. Helmet.htmlAttributes |> Helmet.toString;
    let style = helmet |. Helmet.style |> Helmet.toString;
    let title = helmet |. Helmet.title |> Helmet.toString;
    let meta = helmet |. Helmet.meta |> Helmet.toString;
    let script = helmet |. Helmet.script |> Helmet.toString;
    let staticBaseUrl = WebServerEnv.staticBaseUrl;
    let apolloState =
      apolloClient |. ApolloServer.extract |> Js.Json.stringify;
    let styles = renderStatic(() => content);
    let css = styles##css;
    let html = styles##html;
    let ids = styles##ids |> Js.Json.stringify;
    {j|<!DOCTYPE html>
  <html $htmlAttributes>
    <head>
      <meta charset="utf-8">
      <meta http-equiv="x-ua-compatible" content="ie=edge">
      $title
      $meta
      $style
      <script>
        window.__APOLLO_STATE__ = $apolloState;
        window._glam = $ids;
      </script>
      <style type="text/css" data-glamor>
        $css
      </style>
    </head>
  <body $bodyAttributes>
    <div id="app">$html</div>
    <script src="$staticBaseUrl/client.js"></script>
    $script
  </body>
  </html>
|j};
  };
};

/* make the express app */
let app = Express.App.make();

/* Our initial rendering function, we will soon make this way better */
let renderHTML = (_next, req, res) => {
  let path = Express.Request.path(req);
  let route = Route.fromString(path);
  Js.log3("PATH!!!", path, route);
  ApolloServer.renderToStringWithData(<App route apolloClient />)
  |> Js.Promise.then_(content => {
       let helmet = Helmet.renderStatic();
       let template = Template.make(~content, ~helmet, ());
       Express.Response.sendString(template, res) |> Js.Promise.resolve;
     });
};

Express.App.useOnPathWithMany(
  ~path="/graphql",
  app,
  [|Express.Middleware.json(), ApolloServer.Express.graphql(~schema)|],
);

Express.App.useOnPathWithMany(
  ~path="/graphiql",
  app,
  [|
    Express.Middleware.json(),
    ApolloServer.Express.graphiql(
      ~endpointUrl="/graphql",
      ~subscriptionsEndpoint="ws://localhost:3001/subscriptions",
    ),
  |],
);

/* Express works on middleware and bs-express provides an easy way to make
   middleware out of functions */
renderHTML
|> Express.PromiseMiddleware.from
|> Express.App.useOnPath(~path="/", app);

let server = Http.createServer(app);

/* Getting a nice message when the server starts */
server
|. Http.listen(WebServerEnv.port, e =>
     switch (e) {
     | exception (Js.Exn.Error(e)) =>
       Js.log(e);
       Node.Process.exit(1);
     | _ =>
       SubscriptionServer.make(~server, ~schema, ~path="/subscriptions");
       Js.log("listening at localhost:" ++ string_of_int(WebServerEnv.port));
     }
   );
/* starting up the express app */
/* Express.App.listen(app, ~onListen, ~port=WebServerEnv.port, ()); */
