// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Belt_SetInt = require("bs-platform/lib/js/belt_SetInt.js");
var Caml_format = require("bs-platform/lib/js/caml_format.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Api$ReactTemplate = require("../Api.js");
var Link$ReactTemplate = require("../Components/Link.js");
var Util$ReactTemplate = require("../Util.js");

function reducer(action, state) {
  if (action.tag) {
    var i = action[0];
    var match = Belt_SetInt.has(state[/* choices */2], i);
    return /* Update */Block.__(0, [/* record */[
                /* accountName */state[/* accountName */0],
                /* pollData */state[/* pollData */1],
                /* choices */match ? Belt_SetInt.remove(state[/* choices */2], i) : Belt_SetInt.add(state[/* choices */2], i)
              ]]);
  } else {
    return /* Update */Block.__(0, [/* record */[
                /* accountName */state[/* accountName */0],
                /* pollData */action[0],
                /* choices */state[/* choices */2]
              ]]);
  }
}

var component = ReasonReact.reducerComponent("PollPage");

var eos = Util$ReactTemplate.loadEosReadOnly(/* () */0);

function renderOption(param, i, option) {
  var send = param[/* send */3];
  var state = param[/* state */1];
  console.log("choices", state[/* choices */2], i);
  var isSelected = Belt_SetInt.has(state[/* choices */2], i);
  var onClick = function () {
    return Curry._1(send, /* ToggleChoice */Block.__(1, [i]));
  };
  return React.createElement("li", {
              key: String(i),
              onClick: onClick
            }, option, isSelected ? "(selected)" : "(unselected)");
}

function castVote(self, context, poll, _) {
  var match = context[/* scatter */0];
  if (match) {
    Api$ReactTemplate.Contract[/* make */0](match[0]).then((function (contract) {
                return Promise.resolve(Api$ReactTemplate.vote(contract, poll[/* creator */1], poll[/* id */0], "alice", Belt_SetInt.toArray(self[/* state */1][/* choices */2])));
              })).then((function (result) {
              console.log("Created", result);
              return Promise.resolve(/* () */0);
            })).catch((function (error) {
            console.log("Error voting", error);
            return Promise.resolve(/* () */0);
          }));
    return /* () */0;
  } else {
    console.log("No scatter");
    return /* () */0;
  }
}

function renderPoll(self, context, poll) {
  var numVoters = poll[/* votes */4].length;
  return React.createElement("div", undefined, React.createElement("h1", undefined, poll[/* title */2]), React.createElement("p", undefined, "Voters: " + (String(numVoters) + "")), React.createElement("ol", undefined, $$Array.mapi((function (param, param$1) {
                        return renderOption(self, param, param$1);
                      }), poll[/* options */3])), React.createElement("div", undefined, React.createElement("button", {
                      disabled: context[/* scatter */0] === /* None */0,
                      onClick: (function (param) {
                          return castVote(self, context, poll, param);
                        })
                    }, "Vote"), ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* PollResults */Block.__(2, [
                            poll[/* creator */1],
                            String(poll[/* id */0])
                          ]), /* None */0, /* array */["Results"]))));
}

function make(context, accountName, pollId, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (param) {
              var send = param[/* send */3];
              Api$ReactTemplate.pollById(eos, accountName, Caml_format.caml_int_of_string(pollId)).then((function (result) {
                      var pollData = Api$ReactTemplate.Data[/* fromResult */0](result);
                      Curry._1(send, /* ChangePollData */Block.__(0, [pollData]));
                      console.log("got poll data", pollData);
                      return Promise.resolve(/* () */0);
                    }));
              return /* () */0;
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1][/* pollData */1];
              if (typeof match === "number") {
                if (match === 0) {
                  return "";
                } else {
                  return "Loading...";
                }
              } else if (match.tag) {
                return match[0];
              } else {
                return renderPoll(self, context, match[0]);
              }
            }),
          /* initialState */(function () {
              return /* record */[
                      /* accountName */accountName,
                      /* pollData : Loading */1,
                      /* choices */Belt_SetInt.empty
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */reducer,
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.reducer = reducer;
exports.component = component;
exports.eos = eos;
exports.renderOption = renderOption;
exports.castVote = castVote;
exports.renderPoll = renderPoll;
exports.make = make;
/* component Not a pure module */