include Server_Database;

let typeDefs = {|
  scalar Date
  scalar DateTime
  scalar Time

  type Vote {
    id: String!
    pollId: String!
    pollName: String!
    pollCreator: String!
    poll: Poll!
    voter: String!
    voterStaked: Int!
    choices: [Int!]!
    blockId: String!
    blockNum: Int!
    blockTime: String!
    trxId: String!
    metadata: String!
  }

  type Comment {
    id: String!
    pollName: String!
    pollCreator: String!
    pollTitle: String!
    poll: Poll!
    commenter: String!
    content: String!
    blockId: String!
    blockNum: Int!
    blockTime: String!
    trxId: String!
    metadata: String!
  }

  type Poll {
    id: String!
    pollName: String!
    pollCreator: String!
    version: Int!
    title: String!
    description: String!
    options: [String!]!
    whitelist: [String!]!
    blacklist: [String!]!
    minChoices: Int!
    maxChoices: Int!
    openTime: Int!
    closeTime: Int!
    blockId: String!
    blockNum: Int!
    blockTime: String!
    trxId: String!
    votes: [Vote!]!
    comments: [Comment!]!
    numVotes: Int!
    numComments: Int!
    metadata: String!
  }

  type Settings {
    account: String!
    theme: String!
    defaultWhitelist: [String!]!
    defaultBlacklist: [String!]!
    metadata: String!
  }

  type Account {
    name: String!
    holdings: String!
    polls: [Poll!]!
    votes: [Vote!]!
    comments: [Comment!]!
    settings: Settings
  }

  enum SortBy {
    POPULARITY
    CREATED
    CLOSING
  }

  type Query {
    polls(sortBy: SortBy): [Poll!]!
    votes: [Vote!]!
    comments: [Comment!]!
    poll(creator: String!, id: String!): Poll
    account(name: String!): Account
  }

  type Subscription {
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
  collection
  |. Mongo.Collection.findAll
  |. Mongo.Cursor.limit(10)
  |. Mongo.Cursor.toArray;

let findAllResolver = (collection, _o, args) => collection |> findAll(args);

let findMany = (_args, query, collection) =>
  collection |. Mongo.Collection.find(query) |. Mongo.Cursor.toArray;

let findOne = (query, collection) =>
  collection |. Mongo.Collection.find(query) |. Mongo.Cursor.next;

let findPoll = (~creator, ~name, mongo) =>
  mongo
  |> Polls.collection
  |> findOne({"pollCreator": creator, "pollName": name});

let pubsub = GraphQl.PubSub.make();

let sub = iterator => {"subscribe": () => iterator};

let subWithFilter = (test, iterator) => {
  "subscribe": () => iterator |> GraphQl.PubSub.withFilter(test),
};

let eos =
  Eos.make(
    Eos.Config.t(~httpEndpoint="http://nodeosd:8888", ~verbose=false, ()),
  );

let popularityAggregations = () => {
  let nowSeconds = Js.Date.now() /. 1000.;
  Mongo.AggregationStage.(
    [|
      match({
        "openTime": lt(nowSeconds),
        "closeTime": gt(nowSeconds -. 60. *. 60. *. 24.),
      }),
      lookup({
        "from": "votes",
        "localField": "id",
        "foreignField": "pollId",
        "as": "votes",
      }),
      addFields({
        "score":
          divide(
            size("$votes"),
            pow(
              add(divide(subtract(nowSeconds, "$openTime"), 60 * 60), 2),
              1.8,
            ),
          ),
      }),
      sort({"score": (-1)}),
      limit(5),
    |]
  );
};

let makeResolvers = mongo => {
  /* "Date": GraphQl.Scalars.date,
     "DateTime": GraphQl.Scalars.dateTime,
     "Time": GraphQl.Scalars.time, */
  "Query": {
    "polls": (_obj, args) =>
      switch (args##sortBy) {
      | "POPULARITY" =>
        mongo
        |. Polls.collection
        |. Mongo.Collection.aggregate(popularityAggregations())
        |. Mongo.AggregationCursor.toArray
      | "CLOSING" =>
        mongo
        |. Polls.collection
        |. Mongo.Collection.find({
             "closeTime": {
               "$gt": Js.Date.now() /. 1000.,
             },
           })
        |. Mongo.Cursor.sort("closeTime", 1)
        |. Mongo.Cursor.limit(5)
        |. Mongo.Cursor.toArray
      | _ =>
        Js.log2("!!!!!!!!!!!!!!!! sort by", args);
        mongo
        |> Polls.findAll
        |. Mongo.Cursor.sort("blockTime", -1)
        |. Mongo.Cursor.limit(5)
        |. Mongo.Cursor.toArray;
      },
    "votes": mongo |> Votes.collection |> findAllResolver,
    "comments": mongo |> Comments.collection |> findAllResolver,
    "poll": (_obj, args) =>
      mongo |> findPoll(~creator=args##creator, ~name=args##id),
    "account": (_obj, args) => {"name": args##name},
  },
  "Poll": {
    "votes": (poll, args) =>
      mongo |> Votes.collection |> findMany(args, {"pollId": poll##id}),
    "numVotes": poll =>
      mongo
      |. Votes.collection
      |. Mongo.Collection.find({"pollId": poll##id})
      |. Mongo.Cursor.count,
    "comments": (poll, args) =>
      mongo
      |> Comments.collection
      |> findMany(
           args,
           {"pollCreator": poll##pollCreator, "pollName": poll##pollName},
         ),
    "numComments": poll =>
      mongo
      |. Comments.collection
      |. Mongo.Collection.find({
           "pollCreator": poll##pollCreator,
           "pollName": poll##pollName,
         })
      |. Mongo.Cursor.count,
  },
  "Vote": {
    "poll": vote =>
      mongo |> findPoll(~creator=vote##pollCreator, ~name=vote##pollName),
    "voterStaked": vote =>
      eos
      |. Eos.getTableRows(
           ~json=true,
           ~code="eosio",
           ~scope="eosio",
           ~table="voters",
           ~tableKey="id",
           ~lowerBound=vote##voter,
           ~upperBound="",
           ~limit=1,
         )
      |> Js.Promise.then_(result => {
           let row =
             result##rows
             |. Belt.Array.get(0)
             |. Belt.Option.getWithDefault({"staked": 0});
           Js.Promise.resolve(row##staked);
         }),
  },
  "Comment": {
    "poll": comment =>
      mongo
      |> findPoll(~creator=comment##pollCreator, ~name=comment##pollName),
  },
  "Account": {
    "holdings": () => "",
    "polls": (account, args) =>
      mongo |> Polls.collection |> findMany(args, {"creator": account##name}),
    "votes": (account, args) =>
      mongo |> Votes.collection |> findMany(args, {"voter": account##name}),
    "comments": (account, args) =>
      mongo
      |> Comments.collection
      |> findMany(args, {"commenter": account##name}),
  },
  "Subscription": {
    "polls": pubsub |> Polls.iterator |> sub,
    "pollsFromAccount":
      pubsub
      |> Polls.iterator
      |> subWithFilter((args, poll) => poll##creator == args##account),
    "votes": pubsub |> Votes.iterator |> sub,
    "votesOnPoll":
      pubsub
      |> Votes.iterator
      |> subWithFilter((vote, args) =>
           vote##pollCreator == args##creator && vote##pollName == args##id
         ),
    "votesFromAccount":
      pubsub
      |> Votes.iterator
      |> subWithFilter((vote, args) => vote##voter == args##account),
    "comments": pubsub |> Comments.iterator |> sub,
    "commentsOnPoll":
      pubsub
      |> Comments.iterator
      |> subWithFilter((comment, args) =>
           comment##pollCreator == args##creator
           && comment##pollName == args##id
         ),
    "commentsFromAccount":
      pubsub
      |> Comments.iterator
      |> subWithFilter((comment, args) => comment##commenter == args##account),
  },
};

let make = (~mongo) =>
  GraphQl.Schema.make(~typeDefs, ~resolvers=makeResolvers(mongo));
