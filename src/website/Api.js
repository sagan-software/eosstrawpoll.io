// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Eosjs = require("eosjs");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Json_decode = require("@glennsl/bs-json/src/Json_decode.bs.js");
var Env$ReactTemplate = require("./Env/Env.js");
var Scatter$ReactTemplate = require("./External/Scatter.js");
var WebClientEnv$ReactTemplate = require("./Env/WebClientEnv.js");

function fromResult(result) {
  if (result.tag) {
    return /* Failure */Block.__(1, [result[0]]);
  } else {
    return /* Success */Block.__(0, [result[0]]);
  }
}

var Data = /* module */[/* fromResult */fromResult];

function make(scatter) {
  var eos = Scatter$ReactTemplate.eos(scatter, Env$ReactTemplate.network, (function (prim) {
          return Eosjs(prim);
        }), Env$ReactTemplate.eosConfig, "http");
  return eos.contract(Env$ReactTemplate.codeName);
}

var Contract = /* module */[/* make */make];

function create(contract, pollCreator, pollId, title, $staropt$star, options, $staropt$star$1, $staropt$star$2, $staropt$star$3, $staropt$star$4, $staropt$star$5, $staropt$star$6, _) {
  var description = $staropt$star ? $staropt$star[0] : "";
  var whitelist = $staropt$star$1 ? $staropt$star$1[0] : /* array */[];
  var blacklist = $staropt$star$2 ? $staropt$star$2[0] : /* array */[];
  var minChoices = $staropt$star$3 ? $staropt$star$3[0] : 0;
  var maxChoices = $staropt$star$4 ? $staropt$star$4[0] : 0;
  var openTime = $staropt$star$5 ? $staropt$star$5[0] : 0;
  var closeTime = $staropt$star$6 ? $staropt$star$6[0] : 0;
  return contract.create({
              poll_creator: pollCreator,
              poll_id: pollId,
              title: title,
              description: description,
              options: options,
              whitelist: whitelist,
              blacklist: blacklist,
              min_choices: minChoices,
              max_choices: maxChoices,
              open_time: openTime,
              close_time: closeTime,
              app_label: WebClientEnv$ReactTemplate.appLabel
            }, {
              authorization: /* array */["" + (String(pollCreator) + "@active")]
            });
}

function close(contract, pollCreator, pollId) {
  return contract.close({
              poll_creator: pollCreator,
              poll_id: pollId,
              app_label: WebClientEnv$ReactTemplate.appLabel
            }, {
              authorization: /* array */["" + (String(pollCreator) + "@active")]
            });
}

function vote(contract, pollCreator, pollId, voter, choices) {
  return contract.vote({
              poll_creator: pollCreator,
              poll_id: pollId,
              voter: voter,
              choices: choices,
              app_label: WebClientEnv$ReactTemplate.appLabel
            }, {
              authorization: /* array */["" + (String(voter) + "@active")]
            });
}

function decode(json) {
  return /* record */[
          /* voter */Json_decode.field("voter", Json_decode.string, json),
          /* time */Json_decode.field("time", Json_decode.$$int, json),
          /* holdings */Json_decode.field("holdings", Json_decode.string, json),
          /* choices */Json_decode.field("choices", (function (param) {
                  return Json_decode.array(Json_decode.$$int, param);
                }), json)
        ];
}

var Vote = /* module */[/* decode */decode];

function decode$1(j) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.$$int, j),
          /* pollId */Json_decode.field("poll_id", Json_decode.$$int, j),
          /* pollCreator */Json_decode.field("poll_creator", Json_decode.string, j),
          /* pollTitle */Json_decode.field("poll_title", Json_decode.string, j),
          /* voter */Json_decode.field("voter", Json_decode.string, j),
          /* choices */Json_decode.field("choices", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), j),
          /* time */Json_decode.field("time", Json_decode.$$int, j)
        ];
}

var VoteRef = /* module */[/* decode */decode$1];

function decode$2(json) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.$$int, json),
          /* creator */Json_decode.field("poll_creator", Json_decode.string, json),
          /* title */Json_decode.field("title", Json_decode.string, json),
          /* options */Json_decode.field("options", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), json),
          /* votes */Json_decode.field("votes", (function (param) {
                  return Json_decode.array(decode, param);
                }), json),
          /* minNumChoices */Json_decode.field("min_num_choices", Json_decode.$$int, json),
          /* maxNumChoices */Json_decode.field("max_num_choices", Json_decode.$$int, json),
          /* whitelist */Json_decode.field("whitelist", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), json),
          /* blacklist */Json_decode.field("blacklist", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), json),
          /* createTime */Json_decode.field("create_time", Json_decode.$$int, json),
          /* openTime */Json_decode.field("open_time", Json_decode.$$int, json),
          /* closeTime */Json_decode.field("close_time", Json_decode.$$int, json)
        ];
}

var Poll = /* module */[/* decode */decode$2];

function decode$3(j) {
  return /* record */[
          /* id */Json_decode.field("id", Json_decode.$$int, j),
          /* pollId */Json_decode.field("poll_id", Json_decode.$$int, j),
          /* pollCreator */Json_decode.field("poll_creator", Json_decode.string, j),
          /* title */Json_decode.field("title", Json_decode.string, j),
          /* options */Json_decode.field("options", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), j),
          /* numVotes */Json_decode.field("num_votes", Json_decode.$$int, j),
          /* popularity */Json_decode.field("popularity", Json_decode.string, j),
          /* whitelist */Json_decode.field("whitelist", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), j),
          /* blacklist */Json_decode.field("blacklist", (function (param) {
                  return Json_decode.array(Json_decode.string, param);
                }), j),
          /* createTime */Json_decode.field("create_time", Json_decode.$$int, j),
          /* openTime */Json_decode.field("open_time", Json_decode.$$int, j),
          /* closeTime */Json_decode.field("close_time", Json_decode.$$int, j)
        ];
}

var PollRef = /* module */[/* decode */decode$3];

function polls(eos, creator, $staropt$star, $staropt$star$1, $staropt$star$2, $staropt$star$3, _) {
  var table = $staropt$star ? $staropt$star[0] : "polls";
  var lowerBound = $staropt$star$1 ? $staropt$star$1[0] : 0;
  var upperBound = $staropt$star$2 ? $staropt$star$2[0] : -1;
  var limit = $staropt$star$3 ? $staropt$star$3[0] : 50;
  return eos.getTableRows(true, Env$ReactTemplate.codeName, creator, table, "id", lowerBound, upperBound, limit).then((function (result) {
                console.log("got poll data", result);
                var data = $$Array.map(decode$2, result.rows);
                return Promise.resolve(/* Ok */Block.__(0, [data]));
              }));
}

function pollRefs(eos, creator, table, $staropt$star, $staropt$star$1, $staropt$star$2, _) {
  var lowerBound = $staropt$star ? $staropt$star[0] : 0;
  var upperBound = $staropt$star$1 ? $staropt$star$1[0] : -1;
  var limit = $staropt$star$2 ? $staropt$star$2[0] : 50;
  return eos.getTableRows(true, Env$ReactTemplate.codeName, creator, table, "id", lowerBound, upperBound, limit).then((function (result) {
                console.log("got poll refs data", result);
                var data = $$Array.map(decode$3, result.rows);
                return Promise.resolve(/* Ok */Block.__(0, [data]));
              }));
}

function pollById(eos, creator, id) {
  return polls(eos, creator, /* None */0, /* Some */[id], /* Some */[id + 1 | 0], /* Some */[1], /* () */0).then((function (pollData) {
                var tmp;
                if (pollData.tag) {
                  tmp = /* Error */Block.__(1, ["Couldn\'t find poll with ID \"" + (String(id) + "\"")]);
                } else {
                  var match = Belt_Array.get(pollData[0], 0);
                  tmp = match ? /* Ok */Block.__(0, [match[0]]) : /* Error */Block.__(1, ["Couldn\'t find poll with ID \"" + (String(id) + "\"")]);
                }
                return Promise.resolve(tmp);
              }));
}

function voteRefs(eos, creator, table, $staropt$star, $staropt$star$1, $staropt$star$2, _) {
  var lowerBound = $staropt$star ? $staropt$star[0] : 0;
  var upperBound = $staropt$star$1 ? $staropt$star$1[0] : -1;
  var limit = $staropt$star$2 ? $staropt$star$2[0] : 50;
  return eos.getTableRows(true, Env$ReactTemplate.codeName, creator, table, "id", lowerBound, upperBound, limit).then((function (result) {
                console.log("got vote refs data", result);
                var data = $$Array.map(decode$1, result.rows);
                return Promise.resolve(/* Ok */Block.__(0, [data]));
              }));
}

exports.Data = Data;
exports.Contract = Contract;
exports.create = create;
exports.close = close;
exports.vote = vote;
exports.Vote = Vote;
exports.VoteRef = VoteRef;
exports.Poll = Poll;
exports.PollRef = PollRef;
exports.polls = polls;
exports.pollRefs = pollRefs;
exports.pollById = pollById;
exports.voteRefs = voteRefs;
/* eosjs Not a pure module */
