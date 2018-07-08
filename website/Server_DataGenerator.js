// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var Eosjs = require("eosjs");
var Random = require("bs-platform/lib/js/random.js");
var $$String = require("bs-platform/lib/js/string.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");
var Caml_primitive = require("bs-platform/lib/js/caml_primitive.js");
var Eos$ReactTemplate = require("./External/Eos.js");
var Mongo$ReactTemplate = require("./External/Mongo.js");
var Contract$ReactTemplate = require("./Contract.js");
var Server_Database$ReactTemplate = require("./Server_Database.js");

var pollTitles = /* array */[
  "What is your favorite color?",
  "How much RAM should be added with every block?",
  "Is RAM overpriced?",
  "What should the EOS Straw Poll team be working on?",
  "What will the price of EOS be at the end of 2018?",
  "The solution to RAM?",
  "What is your age?",
  "What is your gender?",
  "What is your favorite digital camera brand?",
  "What matters most to you when voting for BPs?",
  "How did you hear about EOS Straw Poll?",
  "What do you do for a living?",
  "What kind of dApps are you looking forward to???",
  "what is love"
];

var accounts = Belt_Array.map(process.env.DEV_ACCOUNTS.split(","), $$String.trim).filter((function (a) {
        return a !== "";
      }));

function choose(array, d) {
  return Belt_Option.getWithDefault(Belt_Array.get(array, Random.$$int(array.length)), d);
}

function chooseAccount() {
  return choose(accounts, "alice");
}

function generatePoll(contract, logger) {
  logger.debug("generating poll...", /* () */0);
  var title = choose(pollTitles, "");
  var options = Belt_Array.map(Belt_Array.range(1, Caml_primitive.caml_int_max(Random.$$int(15), 2)), (function (i) {
          return "Choice #" + (String(i) + "");
        }));
  var numOptions = options.length;
  var minChoices = 1 + Random.$$int(numOptions) | 0;
  var maxChoices = minChoices + Random.$$int((numOptions - minChoices | 0) + 1 | 0) | 0;
  var openTime = ((Date.now() / 1000 | 0) + 10 | 0) + Random.$$int(120) | 0;
  var closeTime = (openTime + 60 | 0) + Random.$$int(86400) | 0;
  var pollCreator = choose(accounts, "alice");
  var poll = {
    poll_creator: pollCreator,
    poll_name: Eos$ReactTemplate.Name[/* random */4](/* () */0),
    title: title,
    description: "",
    options: options,
    whitelist: /* array */[],
    blacklist: /* array */[],
    min_choices: minChoices,
    max_choices: maxChoices,
    open_time: openTime,
    close_time: closeTime,
    metadata: process.env.APP_LABEL
  };
  return contract.create(poll, {
                  authorization: /* array */["" + (String(pollCreator) + "@active")]
                }).then((function () {
                  return Promise.resolve((logger.debug("generated poll", poll), /* () */0));
                })).catch((function () {
                return Promise.resolve((logger.error("error generating poll", poll), /* () */0));
              }));
}

function getRandomPoll(mongo) {
  return Curry._1(Server_Database$ReactTemplate.Polls[/* collection */1], mongo).aggregate(/* array */[
                  Mongo$ReactTemplate.AggregationStage[/* match_ */0]({
                        openTime: {
                          $lt: Date.now() / 1000 | 0
                        },
                        closeTime: {
                          $gt: Date.now() / 1000 | 0
                        }
                      }),
                  Mongo$ReactTemplate.AggregationStage[/* sample */1]({
                        size: 1
                      })
                ]).next().then((function (poll) {
                return Promise.resolve((poll == null) ? /* None */0 : [poll]);
              }));
}

function generateVote(contract, mongo, logger) {
  return getRandomPoll(mongo).then((function (poll) {
                if (poll) {
                  var poll$1 = poll[0];
                  logger.debug("generating vote...", {
                        pollId: poll$1.id
                      });
                  var voter = choose(accounts, "alice");
                  var choices = /* array */[];
                  var match = poll$1.minChoices === 0;
                  var numChoices = match ? 1 : poll$1.minChoices + Random.$$int((poll$1.maxChoices - poll$1.minChoices | 0) + 1 | 0) | 0;
                  while(choices.length < numChoices) {
                    var choice = Random.$$int(poll$1.options.length);
                    if (!choices.includes(choice)) {
                      choices.push(choice);
                    }
                    
                  };
                  var vote = {
                    poll_creator: poll$1.pollCreator,
                    poll_name: poll$1.pollName,
                    voter: voter,
                    choices: choices,
                    metadata: process.env.APP_LABEL
                  };
                  return contract.vote(vote, {
                                  authorization: /* array */["" + (String(voter) + "@active")]
                                }).then((function () {
                                  return Promise.resolve((logger.debug("generated vote", vote), /* () */0));
                                })).catch((function () {
                                return Promise.resolve((logger.error("error generating vote", {
                                                  vote: vote,
                                                  poll: poll$1
                                                }), /* () */0));
                              }));
                } else {
                  return Promise.resolve((logger.warn("couldn't generate vote because no polls were found", /* () */0), /* () */0));
                }
              }));
}

function generateComment(contract, mongo, logger) {
  return getRandomPoll(mongo).then((function (poll) {
                if (poll) {
                  var poll$1 = poll[0];
                  logger.debug("generating comment...", {
                        pollId: poll$1.id
                      });
                  var comment = {
                    poll_creator: poll$1.pollCreator,
                    poll_name: poll$1.pollName,
                    commenter: "bob",
                    content: "this is a comment",
                    metadata: process.env.APP_LABEL
                  };
                  return contract.comment(comment, {
                                  authorization: /* array */["bob@active"]
                                }).then((function () {
                                  return Promise.resolve((logger.debug("generated comment", comment), /* () */0));
                                })).catch((function () {
                                return Promise.resolve((logger.error("error generating comment", {
                                                  comment: comment,
                                                  poll: poll$1
                                                }), /* () */0));
                              }));
                } else {
                  return Promise.resolve((logger.warn("couldn't generate comment because no polls were found", /* () */0), /* () */0));
                }
              }));
}

function startGenerating(minSeconds, maxSeconds, fn) {
  var generate = function () {
    return setTimeout((function () {
                  Curry._1(fn, /* () */0);
                  generate(/* () */0);
                  return /* () */0;
                }), minSeconds + Caml_int32.imul(Random.$$int(maxSeconds), 1000) | 0);
  };
  generate(/* () */0);
  return /* () */0;
}

function startGeneratingPolls(contract, logger) {
  return startGenerating(90, 120, (function () {
                generatePoll(contract, logger);
                return /* () */0;
              }));
}

function startGeneratingVotes(contract, mongo, logger) {
  return startGenerating(1, 10, (function () {
                generateVote(contract, mongo, logger);
                return /* () */0;
              }));
}

function startGeneratingComments(contract, mongo, logger) {
  return startGenerating(15, 120, (function () {
                generateComment(contract, mongo, logger);
                return /* () */0;
              }));
}

function seed(contract, mongo, logger) {
  return Promise.all(/* array */[generatePoll(contract, logger)]).then((function () {
                logger.info("done creating initial polls", /* () */0);
                var votes = Belt_Array.range(0, 1).map((function () {
                        return generateVote(contract, mongo, logger);
                      }));
                var comments = Belt_Array.range(0, 1).map((function () {
                        return generateComment(contract, mongo, logger);
                      }));
                return Promise.all(comments.concat(votes));
              }));
}

function start(mongo, logger) {
  return Contract$ReactTemplate.fromEos(Eosjs({
                      httpEndpoint: process.env.EOS_URL,
                      verbose: false,
                      keyProvider: /* array */[process.env.DEV_PRIVKEY]
                    })).then((function (contract) {
                  logger.info("seeding...", /* () */0);
                  return seed(contract, mongo, logger).then((function () {
                                return new Promise((function (resolve, _) {
                                              setTimeout((function () {
                                                      return resolve(contract);
                                                    }), 5000);
                                              return /* () */0;
                                            }));
                              }));
                })).then((function (contract) {
                logger.info("starting to generate fake data", /* () */0);
                startGeneratingPolls(contract, logger);
                startGeneratingVotes(contract, mongo, logger);
                startGeneratingComments(contract, mongo, logger);
                return Promise.resolve(/* () */0);
              }));
}

var Db = 0;

exports.Db = Db;
exports.pollTitles = pollTitles;
exports.accounts = accounts;
exports.choose = choose;
exports.chooseAccount = chooseAccount;
exports.generatePoll = generatePoll;
exports.getRandomPoll = getRandomPoll;
exports.generateVote = generateVote;
exports.generateComment = generateComment;
exports.startGenerating = startGenerating;
exports.startGeneratingPolls = startGeneratingPolls;
exports.startGeneratingVotes = startGeneratingVotes;
exports.startGeneratingComments = startGeneratingComments;
exports.seed = seed;
exports.start = start;
/* accounts Not a pure module */
