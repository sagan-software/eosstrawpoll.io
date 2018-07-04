include Server_Database;

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
      voterStaked: Int!
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
  collection
  |. Mongo.Collection.findAll
  |. Mongo.Cursor.limit(10)
  |. Mongo.Cursor.toArray;

let findAllResolver = (collection, _o, args) => collection |> findAll(args);

let findMany = (_args, query, collection) =>
  collection |. Mongo.Collection.find(query) |. Mongo.Cursor.toArray;

let findOne = (query, collection) =>
  collection |. Mongo.Collection.find(query) |. Mongo.Cursor.next;

let findPoll = (~creator, ~id, mongo) =>
  mongo |> Polls.collection |> findOne({"pollCreator": creator, "pollId": id});

let pubsub = GraphQl.PubSub.make();

let sub = iterator => {"subscribe": () => iterator};

let subWithFilter = (test, iterator) => {
  "subscribe": () => iterator |> GraphQl.PubSub.withFilter(test),
};

let eos =
  Eos.make(
    Eos.Config.t(~httpEndpoint="http://nodeosd:8888", ~verbose=false, ()),
  );

let makeResolvers = mongo => {
  /* "Date": GraphQl.Scalars.date,
     "DateTime": GraphQl.Scalars.dateTime,
     "Time": GraphQl.Scalars.time, */
  "Query": {
    "polls": () =>
      mongo
      |> Polls.findAll
      |. Mongo.Cursor.sort("blockNum", -1)
      |. Mongo.Cursor.limit(5)
      |. Mongo.Cursor.toArray,
    "votes": mongo |> Votes.collection |> findAllResolver,
    "comments": mongo |> Comments.collection |> findAllResolver,
    "blocks": (_obj, _args) =>
      mongo
      |. Blocks.collection
      |. Mongo.Collection.findAll
      |. Mongo.Cursor.sort("num", -1)
      |. Mongo.Cursor.limit(10)
      |. Mongo.Cursor.toArray,
    "block": (_obj, args) =>
      mongo |> Blocks.collection |> findOne({"num": args##num}),
    "poll": (_obj, args) =>
      mongo |> findPoll(~creator=args##creator, ~id=args##id),
    "account": (_obj, args) => {"name": args##name},
  },
  "Poll": {
    "votes": (poll, args) =>
      mongo
      |> Votes.collection
      |> findMany(
           args,
           {"pollCreator": poll##pollCreator, "pollId": poll##pollId},
         ),
    "comments": (poll, args) =>
      mongo
      |> Comments.collection
      |> findMany(
           args,
           {"pollCreator": poll##pollCreator, "pollId": poll##pollId},
         ),
  },
  "Vote": {
    "poll": vote =>
      mongo |> findPoll(~creator=vote##pollCreator, ~id=vote##pollId),
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
      mongo |> findPoll(~creator=comment##pollCreator, ~id=comment##pollId),
  },
  "Block": {
    "polls": (block, args) =>
      mongo |> Polls.collection |> findMany(args, {"blockNum": block##num}),
    "votes": (block, args) =>
      mongo |> Votes.collection |> findMany(args, {"blockNum": block##num}),
    "comments": (block, args) =>
      mongo
      |> Comments.collection
      |> findMany(args, {"blockNum": block##num}),
    "numPolls": mongo |. Blocks.numPolls,
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
    "blocks": pubsub |> Blocks.iterator |> sub,
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
           vote##pollCreator == args##creator && vote##pollId == args##id
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
           comment##pollCreator == args##creator && comment##pollId == args##id
         ),
    "commentsFromAccount":
      pubsub
      |> Comments.iterator
      |> subWithFilter((comment, args) => comment##commenter == args##account),
  },
};

let make = (~mongo) =>
  GraphQl.Schema.make(~typeDefs, ~resolvers=makeResolvers(mongo));
