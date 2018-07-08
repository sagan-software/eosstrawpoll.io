// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Eosjs = require("eosjs");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Mongo$ReactTemplate = require("./External/Mongo.js");
var GraphQl$ReactTemplate = require("./External/GraphQl.js");
var GraphqlSubscriptions = require("graphql-subscriptions");
var Server_Database$ReactTemplate = require("./Server_Database.js");

var typeDefs = "\n  scalar Date\n  scalar DateTime\n  scalar Time\n\n  type Vote {\n    id: String!\n    pollId: String!\n    pollName: String!\n    pollCreator: String!\n    poll: Poll!\n    voter: String!\n    voterStaked: Int!\n    choices: [Int!]!\n    blockId: String!\n    blockNum: Int!\n    blockTime: String!\n    trxId: String!\n    metadata: String!\n  }\n\n  type Comment {\n    id: String!\n    pollName: String!\n    pollCreator: String!\n    pollTitle: String!\n    poll: Poll!\n    commenter: String!\n    content: String!\n    blockId: String!\n    blockNum: Int!\n    blockTime: String!\n    trxId: String!\n    metadata: String!\n  }\n\n  type Poll {\n    id: String!\n    pollName: String!\n    pollCreator: String!\n    version: Int!\n    title: String!\n    description: String!\n    options: [String!]!\n    whitelist: [String!]!\n    blacklist: [String!]!\n    minChoices: Int!\n    maxChoices: Int!\n    openTime: Int!\n    closeTime: Int!\n    blockId: String!\n    blockNum: Int!\n    blockTime: String!\n    trxId: String!\n    votes: [Vote!]!\n    comments: [Comment!]!\n    numVotes: Int!\n    numComments: Int!\n    metadata: String!\n  }\n\n  type Settings {\n    account: String!\n    theme: String!\n    defaultWhitelist: [String!]!\n    defaultBlacklist: [String!]!\n    metadata: String!\n  }\n\n  type Account {\n    name: String!\n    holdings: String!\n    polls: [Poll!]!\n    votes: [Vote!]!\n    comments: [Comment!]!\n    settings: Settings\n  }\n\n  enum SortBy {\n    POPULARITY\n    CREATED\n    CLOSING\n  }\n\n  type Query {\n    polls(sortBy: SortBy): [Poll!]!\n    votes: [Vote!]!\n    comments: [Comment!]!\n    poll(creator: String!, id: String!): Poll\n    account(name: String!): Account\n  }\n\n  type Subscription {\n    polls: Poll!\n    pollsFromAccount(account: String!): Poll!\n    votes: Vote!\n    votesOnPoll(creator: String!, id: String!): Vote!\n    votesFromAccount(account: String!): Vote!\n    comments: Comment!\n    commentsOnPoll(creator: String!, id: String!): Comment!\n    commentsFromAccount(account: String!): Comment!\n  }\n\n  schema {\n    query: Query\n    subscription: Subscription\n  }\n\n";

function findAll(_, collection) {
  return collection.find().limit(10).toArray();
}

function findAllResolver(collection, _, args) {
  return findAll(args, collection);
}

function findMany(_, query, collection) {
  return collection.find(query).toArray();
}

function findOne(query, collection) {
  return collection.find(query).next();
}

function findPoll(creator, name, mongo) {
  var collection = Curry._1(Server_Database$ReactTemplate.Polls[/* collection */1], mongo);
  return collection.find({
                pollCreator: creator,
                pollName: name
              }).next();
}

var pubsub = new GraphqlSubscriptions.PubSub();

function sub(iterator) {
  return {
          subscribe: (function () {
              return iterator;
            })
        };
}

function subWithFilter(test, iterator) {
  return {
          subscribe: (function () {
              return GraphQl$ReactTemplate.PubSub[/* withFilter */0](test, iterator);
            })
        };
}

var eos = Eosjs({
      httpEndpoint: "http://nodeosd:8888",
      verbose: false
    });

function popularityAggregations() {
  var nowSeconds = Date.now() / 1000;
  return /* array */[
          Mongo$ReactTemplate.AggregationStage[/* match_ */0]({
                openTime: Mongo$ReactTemplate.AggregationStage[/* lt */11](nowSeconds),
                closeTime: Mongo$ReactTemplate.AggregationStage[/* gt */10](nowSeconds - 60 * 60 * 24)
              }),
          Mongo$ReactTemplate.AggregationStage[/* lookup */2]({
                from: "votes",
                localField: "id",
                foreignField: "pollId",
                as: "votes"
              }),
          Mongo$ReactTemplate.AggregationStage[/* addFields */3]({
                score: Mongo$ReactTemplate.AggregationStage[/* divide */6](Mongo$ReactTemplate.AggregationStage[/* size */12]("$votes"), Mongo$ReactTemplate.AggregationStage[/* pow */4](Mongo$ReactTemplate.AggregationStage[/* add */5](Mongo$ReactTemplate.AggregationStage[/* divide */6](Mongo$ReactTemplate.AggregationStage[/* subtract */7](nowSeconds, "$openTime"), 3600), 2), 1.8))
              }),
          Mongo$ReactTemplate.AggregationStage[/* sort */8]({
                score: -1
              }),
          Mongo$ReactTemplate.AggregationStage[/* limit */9](5)
        ];
}

function makeResolvers(mongo) {
  var partial_arg = Curry._1(Server_Database$ReactTemplate.Votes[/* collection */1], mongo);
  var partial_arg$1 = Curry._1(Server_Database$ReactTemplate.Comments[/* collection */1], mongo);
  var iterator = Curry._1(Server_Database$ReactTemplate.Polls[/* iterator */5], pubsub);
  var iterator$1 = Curry._1(Server_Database$ReactTemplate.Votes[/* iterator */5], pubsub);
  var iterator$2 = Curry._1(Server_Database$ReactTemplate.Comments[/* iterator */5], pubsub);
  return {
          Query: {
            polls: (function (_, args) {
                var match = args.sortBy;
                switch (match) {
                  case "CLOSING" : 
                      return Curry._1(Server_Database$ReactTemplate.Polls[/* collection */1], mongo).find({
                                        closeTime: {
                                          $gt: Date.now() / 1000
                                        }
                                      }).sort("closeTime", 1).limit(5).toArray();
                  case "POPULARITY" : 
                      return Curry._1(Server_Database$ReactTemplate.Polls[/* collection */1], mongo).aggregate(popularityAggregations(/* () */0)).toArray();
                  default:
                    console.log("!!!!!!!!!!!!!!!! sort by", args);
                    return Curry._1(Server_Database$ReactTemplate.Polls[/* findAll */2], mongo).sort("blockTime", -1).limit(5).toArray();
                }
              }),
            votes: (function (_, param) {
                return findAll(param, partial_arg);
              }),
            comments: (function (_, param) {
                return findAll(param, partial_arg$1);
              }),
            poll: (function (_, args) {
                return findPoll(args.creator, args.id, mongo);
              }),
            account: (function (_, args) {
                return {
                        name: args.name
                      };
              })
          },
          Poll: {
            votes: (function (poll, _) {
                var collection = Curry._1(Server_Database$ReactTemplate.Votes[/* collection */1], mongo);
                var query = {
                  pollId: poll.id
                };
                return collection.find(query).toArray();
              }),
            numVotes: (function (poll) {
                return Curry._1(Server_Database$ReactTemplate.Votes[/* collection */1], mongo).find({
                              pollId: poll.id
                            }).count();
              }),
            comments: (function (poll, _) {
                var collection = Curry._1(Server_Database$ReactTemplate.Comments[/* collection */1], mongo);
                var query = {
                  pollCreator: poll.pollCreator,
                  pollName: poll.pollName
                };
                return collection.find(query).toArray();
              }),
            numComments: (function (poll) {
                return Curry._1(Server_Database$ReactTemplate.Comments[/* collection */1], mongo).find({
                              pollCreator: poll.pollCreator,
                              pollName: poll.pollName
                            }).count();
              })
          },
          Vote: {
            poll: (function (vote) {
                return findPoll(vote.pollCreator, vote.pollName, mongo);
              }),
            voterStaked: (function (vote) {
                return eos.getTableRows(true, "eosio", "eosio", "voters", "id", vote.voter, "", 1).then((function (result) {
                              var row = Belt_Option.getWithDefault(Belt_Array.get(result.rows, 0), {
                                    staked: 0
                                  });
                              return Promise.resolve(row.staked);
                            }));
              })
          },
          Comment: {
            poll: (function (comment) {
                return findPoll(comment.pollCreator, comment.pollName, mongo);
              })
          },
          Account: {
            holdings: (function () {
                return "";
              }),
            polls: (function (account, _) {
                var collection = Curry._1(Server_Database$ReactTemplate.Polls[/* collection */1], mongo);
                var query = {
                  creator: account.name
                };
                return collection.find(query).toArray();
              }),
            votes: (function (account, _) {
                var collection = Curry._1(Server_Database$ReactTemplate.Votes[/* collection */1], mongo);
                var query = {
                  voter: account.name
                };
                return collection.find(query).toArray();
              }),
            comments: (function (account, _) {
                var collection = Curry._1(Server_Database$ReactTemplate.Comments[/* collection */1], mongo);
                var query = {
                  commenter: account.name
                };
                return collection.find(query).toArray();
              })
          },
          Subscription: {
            polls: {
              subscribe: (function () {
                  return iterator;
                })
            },
            pollsFromAccount: subWithFilter((function (args, poll) {
                    return Caml_obj.caml_equal(poll.creator, args.account);
                  }), Curry._1(Server_Database$ReactTemplate.Polls[/* iterator */5], pubsub)),
            votes: {
              subscribe: (function () {
                  return iterator$1;
                })
            },
            votesOnPoll: subWithFilter((function (vote, args) {
                    if (Caml_obj.caml_equal(vote.pollCreator, args.creator)) {
                      return Caml_obj.caml_equal(vote.pollName, args.id);
                    } else {
                      return false;
                    }
                  }), Curry._1(Server_Database$ReactTemplate.Votes[/* iterator */5], pubsub)),
            votesFromAccount: subWithFilter((function (vote, args) {
                    return Caml_obj.caml_equal(vote.voter, args.account);
                  }), Curry._1(Server_Database$ReactTemplate.Votes[/* iterator */5], pubsub)),
            comments: {
              subscribe: (function () {
                  return iterator$2;
                })
            },
            commentsOnPoll: subWithFilter((function (comment, args) {
                    if (Caml_obj.caml_equal(comment.pollCreator, args.creator)) {
                      return Caml_obj.caml_equal(comment.pollName, args.id);
                    } else {
                      return false;
                    }
                  }), Curry._1(Server_Database$ReactTemplate.Comments[/* iterator */5], pubsub)),
            commentsFromAccount: subWithFilter((function (comment, args) {
                    return Caml_obj.caml_equal(comment.commenter, args.account);
                  }), Curry._1(Server_Database$ReactTemplate.Comments[/* iterator */5], pubsub))
          }
        };
}

function make(mongo) {
  return GraphQl$ReactTemplate.Schema[/* make */0](typeDefs, makeResolvers(mongo));
}

var MakeCollection = Server_Database$ReactTemplate.MakeCollection;

var Polls = Server_Database$ReactTemplate.Polls;

var Votes = Server_Database$ReactTemplate.Votes;

var Comments = Server_Database$ReactTemplate.Comments;

var Blocks = Server_Database$ReactTemplate.Blocks;

var Settings = Server_Database$ReactTemplate.Settings;

var EosActions = Server_Database$ReactTemplate.EosActions;

var EosBlocks = Server_Database$ReactTemplate.EosBlocks;

exports.MakeCollection = MakeCollection;
exports.Polls = Polls;
exports.Votes = Votes;
exports.Comments = Comments;
exports.Blocks = Blocks;
exports.Settings = Settings;
exports.EosActions = EosActions;
exports.EosBlocks = EosBlocks;
exports.typeDefs = typeDefs;
exports.findAll = findAll;
exports.findAllResolver = findAllResolver;
exports.findMany = findMany;
exports.findOne = findOne;
exports.findPoll = findPoll;
exports.pubsub = pubsub;
exports.sub = sub;
exports.subWithFilter = subWithFilter;
exports.eos = eos;
exports.popularityAggregations = popularityAggregations;
exports.makeResolvers = makeResolvers;
exports.make = make;
/* pubsub Not a pure module */
