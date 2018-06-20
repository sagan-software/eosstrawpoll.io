// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Eosjs = require("eosjs");
var React = require("react");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var TypedGlamor = require("bs-typed-glamor/src/TypedGlamor.bs.js");
var Env$ReactTemplate = require("../Env.js");
var Link$ReactTemplate = require("./Link.js");
var Route$ReactTemplate = require("../Route.js");
var Words$ReactTemplate = require("../Words.js");
var Scatter$ReactTemplate = require("../Scatter.js");
var HomePage$ReactTemplate = require("./HomePage.js");
var PostPage$ReactTemplate = require("./PostPage.js");
var AboutPage$ReactTemplate = require("./AboutPage.js");
var AppStyles$ReactTemplate = require("../Styles/AppStyles.js");
var ProfilePage$ReactTemplate = require("./ProfilePage.js");

var component = ReasonReact.statelessComponent("AppLink");

function make(current, route, label, _) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              var isSelected = Caml_obj.caml_equal(current, route);
              var className = TypedGlamor.toString(AppStyles$ReactTemplate.appLink(isSelected));
              return ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(route, /* Some */[className], /* array */[Words$ReactTemplate.translate(/* English */0, label)]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var AppLink = /* module */[
  /* component */component,
  /* make */make
];

var component$1 = ReasonReact.statelessComponent("PrimaryNav");

function make$1(_, _$1) {
  return /* record */[
          /* debugName */component$1[/* debugName */0],
          /* reactClassInternal */component$1[/* reactClassInternal */1],
          /* handedOffState */component$1[/* handedOffState */2],
          /* willReceiveProps */component$1[/* willReceiveProps */3],
          /* didMount */component$1[/* didMount */4],
          /* didUpdate */component$1[/* didUpdate */5],
          /* willUnmount */component$1[/* willUnmount */6],
          /* willUpdate */component$1[/* willUpdate */7],
          /* shouldUpdate */component$1[/* shouldUpdate */8],
          /* render */(function () {
              return React.createElement("nav", {
                          className: TypedGlamor.toString(AppStyles$ReactTemplate.primaryNav)
                        });
            }),
          /* initialState */component$1[/* initialState */10],
          /* retainedProps */component$1[/* retainedProps */11],
          /* reducer */component$1[/* reducer */12],
          /* subscriptions */component$1[/* subscriptions */13],
          /* jsElementWrapped */component$1[/* jsElementWrapped */14]
        ];
}

var PrimaryNav = /* module */[
  /* component */component$1,
  /* make */make$1
];

var component$2 = ReasonReact.statelessComponent("SecondaryNav");

function make$2(current, _) {
  return /* record */[
          /* debugName */component$2[/* debugName */0],
          /* reactClassInternal */component$2[/* reactClassInternal */1],
          /* handedOffState */component$2[/* handedOffState */2],
          /* willReceiveProps */component$2[/* willReceiveProps */3],
          /* didMount */component$2[/* didMount */4],
          /* didUpdate */component$2[/* didUpdate */5],
          /* willUnmount */component$2[/* willUnmount */6],
          /* willUpdate */component$2[/* willUpdate */7],
          /* shouldUpdate */component$2[/* shouldUpdate */8],
          /* render */(function () {
              return React.createElement("nav", {
                          className: TypedGlamor.toString(AppStyles$ReactTemplate.secondaryNav)
                        }, ReasonReact.element(/* None */0, /* None */0, make(current, /* About */1, /* About */7, /* array */[])));
            }),
          /* initialState */component$2[/* initialState */10],
          /* retainedProps */component$2[/* retainedProps */11],
          /* reducer */component$2[/* reducer */12],
          /* subscriptions */component$2[/* subscriptions */13],
          /* jsElementWrapped */component$2[/* jsElementWrapped */14]
        ];
}

var SecondaryNav = /* module */[
  /* component */component$2,
  /* make */make$2
];

var temp = ( window.Eos = require('eosjs') );

console.log("BALLS", temp);

function reducer(action, state) {
  switch (action.tag | 0) {
    case 0 : 
        return /* Update */Block.__(0, [/* record */[
                    /* eos */state[/* eos */0],
                    /* route */action[0],
                    /* identity */state[/* identity */2]
                  ]]);
    case 1 : 
        return /* Update */Block.__(0, [/* record */[
                    /* eos : Some */[action[0]],
                    /* route */state[/* route */1],
                    /* identity */state[/* identity */2]
                  ]]);
    case 2 : 
        return /* Update */Block.__(0, [/* record */[
                    /* eos */state[/* eos */0],
                    /* route */state[/* route */1],
                    /* identity */action[0]
                  ]]);
    
  }
}

var component$3 = ReasonReact.reducerComponent("App");

function loadEos(self) {
  var eos = scatter.eos(Env$ReactTemplate.network, (function (prim) {
          return Eosjs(prim);
        }), {
        verbose: false
      }, "http");
  Curry._1(self[/* send */3], /* LoadedEos */Block.__(1, [eos]));
  (( window.eos = eos ));
  return eos;
}

function clickedLogin(self, _) {
  Scatter$ReactTemplate.getIdentity(/* Some */[/* array */[Env$ReactTemplate.network]], /* None */0, /* None */0, /* () */0).then((function (identity) {
              console.log(identity);
              Curry._1(self[/* send */3], /* ChangeIdentity */Block.__(2, [/* Some */[identity]]));
              var eos = loadEos(self);
              return eos.contract(Env$ReactTemplate.codeName);
            })).then((function (contract) {
            return contract.create({
                        author: "alice",
                        text: "<h1>BALLS</h1>"
                      }, {
                        authorization: /* array */["alice@active"]
                      });
          })).then((function (result) {
          console.log("result", result);
          return Promise.resolve(/* () */0);
        }));
  return /* () */0;
}

function clickedLogout(self, _) {
  scatter.forgetIdentity().then((function () {
          Curry._1(self[/* send */3], /* ChangeIdentity */Block.__(2, [/* None */0]));
          loadEos(self);
          return Promise.resolve(/* () */0);
        }));
  return /* () */0;
}

function make$3() {
  return /* record */[
          /* debugName */component$3[/* debugName */0],
          /* reactClassInternal */component$3[/* reactClassInternal */1],
          /* handedOffState */component$3[/* handedOffState */2],
          /* willReceiveProps */component$3[/* willReceiveProps */3],
          /* didMount */(function (self) {
              document.addEventListener("scatterLoaded", (function ($$event) {
                      console.log("scatter loaded", $$event);
                      console.log("network", Env$ReactTemplate.network);
                      scatter.suggestNetwork(Env$ReactTemplate.network).then((function (result) {
                              console.log("suggest network", result);
                              loadEos(self);
                              return Promise.resolve(/* () */0);
                            }));
                      return /* () */0;
                    }));
              return /* () */0;
            }),
          /* didUpdate */component$3[/* didUpdate */5],
          /* willUnmount */component$3[/* willUnmount */6],
          /* willUpdate */component$3[/* willUpdate */7],
          /* shouldUpdate */component$3[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1][/* identity */2];
              var tmp;
              if (match) {
                var name = Caml_array.caml_array_get(match[0].accounts, 0).name;
                tmp = React.createElement("button", {
                      onClick: (function (param) {
                          return clickedLogout(self, param);
                        })
                    }, "Logged in as " + (String(name) + ""));
              } else {
                tmp = React.createElement("button", {
                      className: TypedGlamor.toString(AppStyles$ReactTemplate.loginLink),
                      onClick: (function (param) {
                          return clickedLogin(self, param);
                        })
                    }, "Login");
              }
              var match$1 = self[/* state */1][/* eos */0];
              var tmp$1;
              if (match$1) {
                var match$2 = self[/* state */1][/* route */1];
                tmp$1 = typeof match$2 === "number" ? (
                    match$2 === 0 ? ReasonReact.element(/* None */0, /* None */0, HomePage$ReactTemplate.make(/* array */[])) : ReasonReact.element(/* None */0, /* None */0, AboutPage$ReactTemplate.make(/* array */[]))
                  ) : (
                    match$2.tag ? ReasonReact.element(/* None */0, /* None */0, PostPage$ReactTemplate.make(match$2[0], match$2[1], /* array */[])) : ReasonReact.element(/* None */0, /* None */0, ProfilePage$ReactTemplate.make(match$1[0], match$2[0], /* array */[]))
                  );
              } else {
                tmp$1 = "loading...";
              }
              return React.createElement("div", {
                          className: TypedGlamor.toString(AppStyles$ReactTemplate.box)
                        }, React.createElement("header", {
                              className: TypedGlamor.toString(AppStyles$ReactTemplate.header)
                            }, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Home */0, /* Some */[TypedGlamor.toString(AppStyles$ReactTemplate.appLogo)], /* array */["Twitteos"])), ReasonReact.element(/* None */0, /* None */0, make$1(self[/* state */1][/* route */1], /* array */[])), ReasonReact.element(/* None */0, /* None */0, make$2(self[/* state */1][/* route */1], /* array */[])), React.createElement("nav", {
                                  className: TypedGlamor.toString(AppStyles$ReactTemplate.userNav)
                                }, tmp)), tmp$1);
            }),
          /* initialState */(function () {
              return /* record */[
                      /* eos : None */0,
                      /* route : Home */0,
                      /* identity : None */0
                    ];
            }),
          /* retainedProps */component$3[/* retainedProps */11],
          /* reducer */reducer,
          /* subscriptions */(function (self) {
              return /* :: */[
                      /* Sub */[
                        (function () {
                            return ReasonReact.Router[/* watchUrl */1]((function (url) {
                                          return Curry._1(self[/* send */3], /* ChangeRoute */Block.__(0, [Route$ReactTemplate.fromUrl(url)]));
                                        }));
                          }),
                        ReasonReact.Router[/* unwatchUrl */2]
                      ],
                      /* [] */0
                    ];
            }),
          /* jsElementWrapped */component$3[/* jsElementWrapped */14]
        ];
}

var Styles = 0;

exports.Styles = Styles;
exports.AppLink = AppLink;
exports.PrimaryNav = PrimaryNav;
exports.SecondaryNav = SecondaryNav;
exports.temp = temp;
exports.reducer = reducer;
exports.component = component$3;
exports.loadEos = loadEos;
exports.clickedLogin = clickedLogin;
exports.clickedLogout = clickedLogout;
exports.make = make$3;
/* component Not a pure module */
