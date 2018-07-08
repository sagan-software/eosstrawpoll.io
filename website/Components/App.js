// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var TypedGlamor = require("bs-typed-glamor/src/TypedGlamor.bs.js");
var ApolloProvider = require("reason-apollo/src/ApolloProvider.bs.js");
var Env$ReactTemplate = require("../Env.js");
var Icon$ReactTemplate = require("./Icon.js");
var Link$ReactTemplate = require("./Link.js");
var Route$ReactTemplate = require("./Route.js");
var Helmet$ReactTemplate = require("../External/Helmet.js");
var Context$ReactTemplate = require("./Context.js");
var Scatter$ReactTemplate = require("../External/Scatter.js");
var HomePage$ReactTemplate = require("./HomePage.js");
var PollPage$ReactTemplate = require("./PollPage.js");
var AboutPage$ReactTemplate = require("./AboutPage.js");
var AppStyles$ReactTemplate = require("./Styles/AppStyles.js");
var ProfilePage$ReactTemplate = require("./ProfilePage.js");
var PollResultsPage$ReactTemplate = require("./PollResultsPage.js");

function reducer(action, state) {
  switch (action.tag | 0) {
    case 0 : 
        return /* Update */Block.__(0, [/* record */[
                    /* context */state[/* context */0],
                    /* route */action[0]
                  ]]);
    case 1 : 
        var init = state[/* context */0];
        return /* Update */Block.__(0, [/* record */[
                    /* context : record */[
                      /* scatter */init[/* scatter */0],
                      /* identity */action[0],
                      /* language */init[/* language */2]
                    ],
                    /* route */state[/* route */1]
                  ]]);
    case 2 : 
        var scatter = action[0];
        var init$1 = state[/* context */0];
        return /* Update */Block.__(0, [/* record */[
                    /* context : record */[
                      /* scatter : Some */[scatter],
                      /* identity */Scatter$ReactTemplate.identity(scatter),
                      /* language */init$1[/* language */2]
                    ],
                    /* route */state[/* route */1]
                  ]]);
    
  }
}

var component = ReasonReact.reducerComponent("App-ReactTemplate");

function clickedLogin(self, scatter, _) {
  Scatter$ReactTemplate.getIdentity(scatter, /* Some */[/* array */[Env$ReactTemplate.scatterNetwork]], /* None */0, /* None */0, /* () */0).then((function (identity) {
          console.log(identity);
          Curry._1(self[/* send */3], /* ChangeIdentity */Block.__(1, [/* Some */[identity]]));
          return Promise.resolve(/* () */0);
        }));
  return /* () */0;
}

function clickedLogout(self, scatter, _) {
  Scatter$ReactTemplate.forgetIdentity(scatter).then((function () {
          Curry._1(self[/* send */3], /* ChangeIdentity */Block.__(1, [/* None */0]));
          return Promise.resolve(/* () */0);
        }));
  return /* () */0;
}

function make(apolloClient, $staropt$star, _) {
  var route = $staropt$star ? $staropt$star[0] : /* Home */0;
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              return Scatter$ReactTemplate.onLoad((function () {
                            var match = window.scatter;
                            if (match == null) {
                              return /* () */0;
                            } else {
                              return Curry._1(self[/* send */3], /* ScatterLoaded */Block.__(2, [match]));
                            }
                          }));
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var context = self[/* state */1][/* context */0];
              var match = context[/* scatter */0];
              var tmp;
              if (match) {
                var scatter = match[0];
                var match$1 = Context$ReactTemplate.accountName(context);
                if (match$1) {
                  var name = match$1[0];
                  tmp = React.createElement("nav", {
                        className: TypedGlamor.toString(AppStyles$ReactTemplate.userNav)
                      }, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, [name]), /* None */0, /* array */[
                                React.createElement("img", {
                                      className: TypedGlamor.toString(AppStyles$ReactTemplate.userAvatar),
                                      src: "https://api.adorable.io/avatars/20/" + (String(name) + "@eosstrawpoll")
                                    }),
                                name
                              ])), React.createElement("a", undefined, Icon$ReactTemplate.cog), React.createElement("a", {
                            onClick: (function (param) {
                                return clickedLogout(self, scatter, param);
                              })
                          }, Icon$ReactTemplate.logout));
                } else {
                  tmp = React.createElement("a", {
                        className: TypedGlamor.toString(AppStyles$ReactTemplate.loginLink),
                        onClick: (function (param) {
                            return clickedLogin(self, scatter, param);
                          })
                      }, "Login with Scatter");
                }
              } else {
                tmp = React.createElement("a", {
                      href: "https://get-scatter.com/"
                    }, "Get Scatter");
              }
              var match$2 = self[/* state */1][/* route */1];
              var tmp$1;
              if (typeof match$2 === "number") {
                tmp$1 = match$2 === 0 ? ReasonReact.element(/* None */0, /* None */0, HomePage$ReactTemplate.make(context, /* array */[])) : ReasonReact.element(/* None */0, /* None */0, AboutPage$ReactTemplate.make(/* array */[]));
              } else {
                switch (match$2.tag | 0) {
                  case 0 : 
                      tmp$1 = ReasonReact.element(/* None */0, /* None */0, ProfilePage$ReactTemplate.make(context, match$2[0], /* array */[]));
                      break;
                  case 1 : 
                      tmp$1 = ReasonReact.element(/* None */0, /* None */0, PollPage$ReactTemplate.make(context, match$2[0], match$2[1], /* array */[]));
                      break;
                  case 2 : 
                      tmp$1 = ReasonReact.element(/* None */0, /* None */0, PollResultsPage$ReactTemplate.make(context, match$2[0], match$2[1], /* array */[]));
                      break;
                  
                }
              }
              return ReasonReact.element(/* None */0, /* None */0, ApolloProvider.make(apolloClient, /* array */[React.createElement("div", {
                                    className: TypedGlamor.toString(AppStyles$ReactTemplate.container)
                                  }, ReasonReact.element(/* None */0, /* None */0, Helmet$ReactTemplate.make(/* array */[
                                            React.createElement("html", {
                                                  prefix: "og: http://ogp.me/ns#"
                                                }),
                                            React.createElement("meta", {
                                                  content: "",
                                                  name: "description"
                                                }),
                                            React.createElement("meta", {
                                                  content: "width=device-width, initial-scale=1, shrink-to-fit=no",
                                                  name: "viewport"
                                                }),
                                            React.createElement("meta", {
                                                  content: "EOS Straw Poll",
                                                  property: "og:site_name"
                                                }),
                                            React.createElement("meta", {
                                                  content: "EOS Straw Poll",
                                                  property: "og:title"
                                                }),
                                            React.createElement("meta", {
                                                  content: "Straw polls on EOS!",
                                                  property: "og:description"
                                                }),
                                            React.createElement("meta", {
                                                  content: Route$ReactTemplate.toAbsolute(self[/* state */1][/* route */1]),
                                                  property: "og:url"
                                                }),
                                            React.createElement("link", {
                                                  href: "https://use.typekit.net/pix7uhg.css",
                                                  rel: "stylesheet"
                                                })
                                          ])), React.createElement("header", {
                                        className: TypedGlamor.toString(AppStyles$ReactTemplate.headerContainer)
                                      }, React.createElement("div", {
                                            className: TypedGlamor.toString(AppStyles$ReactTemplate.header)
                                          }, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Home */0, /* Some */[TypedGlamor.toString(AppStyles$ReactTemplate.appLogo)], /* array */[
                                                    Icon$ReactTemplate.eos(TypedGlamor.toString(AppStyles$ReactTemplate.appLogoIcon)),
                                                    React.createElement("strong", undefined, "EOS Straw Poll")
                                                  ])), tmp)), tmp$1, React.createElement("footer", {
                                        className: TypedGlamor.toString(AppStyles$ReactTemplate.footerContainer)
                                      }, React.createElement("div", {
                                            className: TypedGlamor.toString(AppStyles$ReactTemplate.footer)
                                          }, React.createElement("div", undefined, React.createElement("h3", undefined, "Like EOS Straw Poll?"), React.createElement("p", undefined, "Please consider donating to help cover server costs and fund development. Thank you!"), React.createElement("form", {
                                                    className: TypedGlamor.toString(AppStyles$ReactTemplate.donateForm)
                                                  }, React.createElement("input", {
                                                        className: TypedGlamor.toString(AppStyles$ReactTemplate.donateInput),
                                                        placeholder: "1 EOS",
                                                        type: "number"
                                                      }), React.createElement("button", {
                                                        className: TypedGlamor.toString(AppStyles$ReactTemplate.donateButton),
                                                        type: "submit"
                                                      }, "Donate "))), React.createElement("div", undefined, React.createElement("h3", undefined, "Top Donators"), React.createElement("ol", undefined, React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "20.1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "20.1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "20.1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "20.1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "20.1 EOS")))), React.createElement("div", undefined, React.createElement("h3", undefined, "Recent Donations"), React.createElement("ol", undefined, React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "1 EOS")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* Profile */Block.__(0, ["saganonroids"]), /* None */0, /* array */["saganonroids"])), React.createElement("code", undefined, "1 EOS")))), React.createElement("div", undefined, React.createElement("h3", undefined, "Links"), React.createElement("ol", undefined, React.createElement("li", undefined, React.createElement("a", {
                                                            href: "https://twitter.com/" + process.env.TWITTER_NAME
                                                          }, "Twitter")), React.createElement("li", undefined, React.createElement("a", {
                                                            href: "https://github.com/" + process.env.TWITTER_NAME
                                                          }, "Github")), React.createElement("li", undefined, React.createElement("a", {
                                                            href: "#steemit"
                                                          }, "Steemit")), React.createElement("li", undefined, React.createElement("a", {
                                                            href: "#roadmap"
                                                          }, "Roadmap")), React.createElement("li", undefined, ReasonReact.element(/* None */0, /* None */0, Link$ReactTemplate.make(/* About */1, /* None */0, /* array */["About"]))))))))]));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* context */Context$ReactTemplate.initial,
                      /* route */route
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
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
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var Cn = 0;

exports.Cn = Cn;
exports.reducer = reducer;
exports.component = component;
exports.clickedLogin = clickedLogin;
exports.clickedLogout = clickedLogout;
exports.make = make;
/* component Not a pure module */