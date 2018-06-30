let typeDefs = {|
  scalar Date
  scalar DateTime
  scalar Time


  type Vote {
    id: String!
    pollId: String!
    pollCreator: String!
    pollVersion: Int!
    poll: Poll!
    voter: String!
    voterHoldings: String!
    choices: [Int!]!
    blockId: String!
    blockNum: Int!
    blockTime: String!
    trxId: String!
    appLabel: String!
  }

  type Comment {
    id: String!
    pollId: String!
    pollCreator: String!
    pollVersion: Int!
    pollTitle: String!
    poll: Poll!
    commenter: String!
    content: String!
    blockId: String!
    blockNum: Int!
    blockTime: String!
    trxId: String!
    appLabel: String!
  }

  type Poll {
    id: String!
    pollId: String!
    pollCreator: String!
    version: Int!
    title: String!
    description: String!
    options: [String!]!
    whitelist: [String!]!
    blacklist: [String!]!
    openTime: String!
    closeTime: String
    blockId: String!
    blockNum: Int!
    blockTime: String!
    trxId: String!
    votes: [Vote!]!
    comments: [Comment!]!
    appLabel: String!
  }

  type Block {
    id: String!
    num: Int!
    time: String!
    numPolls: Int!
    numVotes: Int!
    numComments: Int!
    polls: [Poll!]!
    votes: [Vote!]!
    comments: [Comment!]!
  }

  type Settings {
    account: String!
    theme: String!
    defaultWhitelist: [String!]!
    defaultBlacklist: [String!]!
    appLabel: String!
  }

  type Account {
    name: String!
    holdings: String!
    polls: [Poll!]!
    votes: [Vote!]!
    comments: [Comment!]!
    settings: Settings
  }

  type Query {
    polls: [Poll!]!
    votes: [Vote!]!
    comments: [Comment!]!
    blocks: [Block!]!
    block(num: Int!): Block
    poll(creator: String!, id: String!): Poll
    account(name: String!): Account
  }

  type Subscription {
    blocks: Block!
    polls: Poll!
    pollsFromAccount(account: String!): Poll!
    votes: Vote!
    votesOnPoll(creator: String!, id: String!): Vote!
    votesFromAccount(account: String!): Vote!
    comments: Comment!
    commentsOnPoll(creator: String!, id: String!): Comment!
    commentsFromAccount(account: String!): Comment!
  }

  schema {
    query: Query
    subscription: Subscription
  }

|};

let findAll = (_args, collection) =>
  collection |. Mongo.Collection.findAll |. Mongo.Cursor.toArray;

let findAllResolver = (collection, _o, args) => collection |> findAll(args);

let findMany = (_args, query, collection) =>
  collection |. Mongo.Collection.find(query) |. Mongo.Cursor.toArray;

let findOne = (query, collection) =>
  collection |. Mongo.Collection.find(query) |. Mongo.Cursor.next;

let findPoll = (~creator, ~id, mongo) =>
  mongo
  |> Db.Polls.collection
  |> findOne({"pollCreator": creator, "pollId": id});

let pubsub = GraphQl.PubSub.make();

let sub = iterator => {"subscribe": () => iterator};

let subWithFilter = (test, iterator) => {
  "subscribe": () => iterator |> GraphQl.PubSub.withFilter(test),
};

let makeSchema = (~mongo) =>
  GraphQl.Schema.make(
    ~typeDefs,
    ~resolvers={
      /* "Date": GraphQl.Scalars.date,
         "DateTime": GraphQl.Scalars.dateTime,
         "Time": GraphQl.Scalars.time, */
      "Query": {
        "polls": () =>
          mongo
          |> Db.Polls.findAll
          |. Mongo.Cursor.sort("blockNum", -1)
          |. Mongo.Cursor.limit(20)
          |. Mongo.Cursor.toArray,
        "votes": mongo |> Db.Votes.collection |> findAllResolver,
        "comments": mongo |> Db.Comments.collection |> findAllResolver,
        "blocks": mongo |> Db.Blocks.collection |> findAllResolver,
        "block": (_obj, args) =>
          mongo |> Db.Blocks.collection |> findOne({"num": args##num}),
        "poll": (_obj, args) =>
          mongo |> findPoll(~creator=args##creator, ~id=args##id),
        "account": (_obj, args) => {"name": args##name},
      },
      "Poll": {
        "votes": (poll, args) =>
          mongo
          |> Db.Votes.collection
          |> findMany(
               args,
               {"pollCreator": poll##creator, "pollId": poll##id},
             ),
        "comments": (poll, args) =>
          mongo
          |> Db.Comments.collection
          |> findMany(
               args,
               {"pollCreator": poll##creator, "pollId": poll##id},
             ),
      },
      "Vote": {
        "poll": vote =>
          mongo |> findPoll(~creator=vote##pollCreator, ~id=vote##pollId),
      },
      "Comment": {
        "poll": comment =>
          mongo
          |> findPoll(~creator=comment##pollCreator, ~id=comment##pollId),
      },
      "Block": {
        "polls": (block, args) =>
          mongo
          |> Db.Polls.collection
          |> findMany(args, {"blockNum": block##num}),
        "votes": (block, args) =>
          mongo
          |> Db.Votes.collection
          |> findMany(args, {"blockNum": block##num}),
        "comments": (block, args) =>
          mongo
          |> Db.Comments.collection
          |> findMany(args, {"blockNum": block##num}),
      },
      "Account": {
        "holdings": () => "",
        "polls": (account, args) =>
          mongo
          |> Db.Polls.collection
          |> findMany(args, {"creator": account##name}),
        "votes": (account, args) =>
          mongo
          |> Db.Votes.collection
          |> findMany(args, {"voter": account##name}),
        "comments": (account, args) =>
          mongo
          |> Db.Comments.collection
          |> findMany(args, {"commenter": account##name}),
      },
      "Subscription": {
        "blocks": pubsub |> Db.Blocks.iterator |> sub,
        "polls": pubsub |> Db.Polls.iterator |> sub,
        "pollsFromAccount":
          pubsub
          |> Db.Polls.iterator
          |> subWithFilter((args, poll) => poll##creator == args##account),
        "votes": pubsub |> Db.Votes.iterator |> sub,
        "votesOnPoll":
          pubsub
          |> Db.Votes.iterator
          |> subWithFilter((vote, args) =>
               vote##pollCreator == args##creator && vote##pollId == args##id
             ),
        "votesFromAccount":
          pubsub
          |> Db.Votes.iterator
          |> subWithFilter((vote, args) => vote##voter == args##account),
        "comments": pubsub |> Db.Comments.iterator |> sub,
        "commentsOnPoll":
          pubsub
          |> Db.Comments.iterator
          |> subWithFilter((comment, args) =>
               comment##pollCreator == args##creator
               && comment##pollId == args##id
             ),
        "commentsFromAccount":
          pubsub
          |> Db.Comments.iterator
          |> subWithFilter((comment, args) =>
               comment##commenter == args##account
             ),
      },
    },
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

let inMemoryCache = ApolloInMemoryCache.createInMemoryCache();

let makeApolloClient = (~schema) =>
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
  let make = (~content, ~helmet, ~apolloClient, ()) => {
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

let startExpress = mongo => {
  /* make the express app */
  let app = Express.App.make();
  let schema = makeSchema(mongo);
  let apolloClient = makeApolloClient(schema);
  /* Our initial rendering function, we will soon make this way better */
  let renderHTML = (_next, req, res) => {
    let path = Express.Request.path(req);
    let route = Route.fromString(path);
    Js.log3("PATH!!!", path, route);
    ApolloServer.renderToStringWithData(<App route apolloClient />)
    |> Js.Promise.then_(content => {
         let helmet = Helmet.renderStatic();
         let template = Template.make(~content, ~helmet, ~apolloClient, ());
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
         Js.log("Connected to MongoDB!!!!!!!!!");
         SubscriptionServer.make(~server, ~schema, ~path="/subscriptions");
         Js.log(
           "listening at localhost:" ++ string_of_int(WebServerEnv.port),
         );
       }
     );
};

WebServerEnv.mongoUri
|> Mongo.Client.make
|> Js.Promise.then_(mongo => {
     DataProcessor.listen(mongo);
     /* Db.Polls.watch(mongo, pubsub, poll =>
          {"polls": poll, "poll": poll, "pollFromAccount": poll}
        );
        Db.Votes.watch(mongo, pubsub, vote =>
          {"votes": vote, "votesFromAccount": vote, "votesOnPoll": vote}
        );
        Db.Comments.watch(mongo, pubsub, comment =>
          {
            "comments": comment,
            "commentsFromAccount": comment,
            "commentsOnPoll": comment,
          }
        );
        Db.Blocks.watch(mongo, pubsub, block => {"blocks": block}); */
     startExpress(mongo);
     Js.Promise.resolve();
   });
/* starting up the express app */
/* Express.App.listen(app, ~onListen, ~port=WebServerEnv.port, ()); */
