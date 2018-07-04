let renderTemplate = (~content, ~helmet, ~apolloClient) => {
  let bodyAttributes = helmet |. Helmet.bodyAttributes |> Helmet.toString;
  let htmlAttributes = helmet |. Helmet.htmlAttributes |> Helmet.toString;
  let style = helmet |. Helmet.style |> Helmet.toString;
  let title = helmet |. Helmet.title |> Helmet.toString;
  let meta = helmet |. Helmet.meta |> Helmet.toString;
  let script = helmet |. Helmet.script |> Helmet.toString;
  let staticUrl = Env.staticUrl;
  let apolloState = apolloClient |. ApolloServer.extract |> Js.Json.stringify;
  let styles = GlamorServer.renderStatic(() => content);
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
        //window._glam = $ids;
      </script>
      <!--<style type="text/css" data-glamor>
        $css
      </style>-->
    </head>
  <body $bodyAttributes>
    <div id="app">$html</div>
    <script src="$staticUrl/client.js"></script>
    $script
  </body>
  </html>
|j};
};

let renderHtml = (~apolloClient, _next, req, res) => {
  let path = Express.Request.path(req);
  let route = Route.fromString(path);
  <App route apolloClient />
  |> ApolloServer.renderToStringWithData
  |> Js.Promise.then_(content => {
       let helmet = Helmet.renderStatic();
       let template = renderTemplate(~content, ~helmet, ~apolloClient);
       Express.Response.sendString(template, res) |> Js.Promise.resolve;
     });
};

let start = (~apolloClient, ~schema, ~logger) => {
  let app = Express.App.make();
  /* GraphQL middleware */
  Express.App.useOnPathWithMany(
    app,
    ~path="/graphql",
    [|
      ExpressCors.middleware(),
      Express.Middleware.json(),
      ApolloServer.Express.graphql(~schema),
    |],
  );
  /* GraphiQL middleware */
  Express.App.useOnPathWithMany(
    app,
    ~path="/graphiql",
    [|
      Express.Middleware.json(),
      ApolloServer.Express.graphiql(
        ~endpointUrl="/graphql",
        ~subscriptionsEndpoint=Env.siteWsUrl ++ "/subscriptions",
      ),
    |],
  );
  /* HTML middleware */
  Express.App.useOnPath(
    app,
    ~path="/",
    Express.PromiseMiddleware.from(renderHtml(~apolloClient)),
  );
  /* Start server */
  let server = Node_Http.createServer(app);
  logger |. Winston.debug("Starting HTTP server", {"port": Env.sitePort});
  Js.Promise.make((~resolve, ~reject as _) =>
    server
    |. Node_Http.listen(Env.sitePort, e =>
         switch (e) {
         | exception (Js.Exn.Error(e)) =>
           logger |. Winston.error("Error starting HTTP server", e);
           Node.Process.exit(1);
           resolve(. Belt.Result.Error(e));
         | _ =>
           logger
           |. Winston.info("Started HTTP server", {"port": Env.sitePort});
           Server_GraphQlServer.SubscriptionServer.make(
             ~server,
             ~schema,
             ~path="/subscriptions",
           )
           |> ignore;
           resolve(. Belt.Result.Ok(server));
         }
       )
  );
};
