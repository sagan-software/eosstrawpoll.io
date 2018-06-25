// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var TypedGlamor = require("bs-typed-glamor/src/TypedGlamor.bs.js");
var CommonStyles$ReactTemplate = require("./CommonStyles.js");
var GlobalStyles$ReactTemplate = require("./GlobalStyles.js");

var sidebarWidth = TypedGlamor.pct(20);

var container = TypedGlamor.css(/* Some */[CommonStyles$ReactTemplate.html], /* :: */[
      TypedGlamor.position(TypedGlamor.absolute),
      /* :: */[
        TypedGlamor.width(TypedGlamor.pct(100)),
        /* :: */[
          TypedGlamor.height(TypedGlamor.pct(100)),
          /* :: */[
            TypedGlamor.overflow(TypedGlamor.auto),
            /* :: */[
              TypedGlamor.display(TypedGlamor.flex),
              /* :: */[
                TypedGlamor.flexDirection(TypedGlamor.column),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var header = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.display(TypedGlamor.flex),
      /* :: */[
        TypedGlamor.height(TypedGlamor.px(50)),
        /* :: */[
          TypedGlamor.justifyContent(TypedGlamor.spaceBetween),
          /* :: */[
            TypedGlamor.alignItems(TypedGlamor.center),
            /* :: */[
              TypedGlamor.textAlign(TypedGlamor.center),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var main = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.flex3(1, 0, TypedGlamor.auto),
      /* [] */0
    ]);

var footer = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.flexShrink(0),
      /* :: */[
        TypedGlamor.textAlign(TypedGlamor.center),
        /* [] */0
      ]
    ]);

var appLogo = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.width(sidebarWidth),
      /* [] */0
    ]);

var primaryNav = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.flex_(TypedGlamor.$$int(1)),
      /* :: */[
        TypedGlamor.display(TypedGlamor.flex),
        /* [] */0
      ]
    ]);

var secondaryNav = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.flex_(TypedGlamor.$$int(1)),
      /* :: */[
        TypedGlamor.display(TypedGlamor.flex),
        /* :: */[
          TypedGlamor.justifyContent(TypedGlamor.flexEnd),
          /* [] */0
        ]
      ]
    ]);

function appLink(isSelected) {
  return TypedGlamor.css(/* None */0, /* :: */[
              TypedGlamor.padding(TypedGlamor.px(10)),
              /* :: */[
                TypedGlamor.fontWeight(isSelected ? TypedGlamor.bold : TypedGlamor.normal),
                /* [] */0
              ]
            ]);
}

var userNav = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.width(sidebarWidth),
      /* [] */0
    ]);

var loginLink = TypedGlamor.css(/* None */0, /* [] */0);

var cube = TypedGlamor.css(/* None */0, /* :: */[
      TypedGlamor.label("thing"),
      /* :: */[
        TypedGlamor.padding2(TypedGlamor.em(0.75), TypedGlamor.em(1.5)),
        /* :: */[
          TypedGlamor.padding(TypedGlamor.zero),
          /* :: */[
            TypedGlamor.transitions(/* :: */[
                  /* tuple */[
                    TypedGlamor.AnimatableProperty[/* opacity */76],
                    TypedGlamor.ms(500),
                    TypedGlamor.linear,
                    TypedGlamor.ms(0)
                  ],
                  /* :: */[
                    /* tuple */[
                      TypedGlamor.AnimatableProperty[/* height */53],
                      TypedGlamor.ms(300),
                      TypedGlamor.linear,
                      TypedGlamor.ms(200)
                    ],
                    /* [] */0
                  ]
                ]),
            /* :: */[
              TypedGlamor.transition(TypedGlamor.unset),
              /* :: */[
                TypedGlamor.display(TypedGlamor.flex),
                /* :: */[
                  TypedGlamor.flex_(TypedGlamor.$$int(1)),
                  /* :: */[
                    TypedGlamor.select("& > .title", /* :: */[
                          TypedGlamor.fontSize(TypedGlamor.larger),
                          /* [] */0
                        ]),
                    /* :: */[
                      TypedGlamor.select("> .subtitle", /* :: */[
                            TypedGlamor.fontSize(TypedGlamor.smaller),
                            /* [] */0
                          ]),
                      /* :: */[
                        TypedGlamor.hover(/* :: */[
                              TypedGlamor.background(TypedGlamor.plum),
                              /* [] */0
                            ]),
                        /* :: */[
                          TypedGlamor.select("@media (max-width: 600px)", /* :: */[
                                TypedGlamor.select("& > .subtitle", /* :: */[
                                      TypedGlamor.display(TypedGlamor.none),
                                      /* [] */0
                                    ]),
                                /* [] */0
                              ]),
                          /* [] */0
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

TypedGlamor.$$global("html", /* :: */[
      TypedGlamor.fontSize(TypedGlamor.px(15)),
      /* :: */[
        TypedGlamor.lineHeight(TypedGlamor.em(1.25)),
        /* [] */0
      ]
    ]);

var _global = TypedGlamor.$$global("html, body", /* :: */[
      TypedGlamor.backgroundColor(TypedGlamor.white),
      /* :: */[
        TypedGlamor.minHeight(TypedGlamor.pct(100)),
        /* [] */0
      ]
    ]);

var _reset = GlobalStyles$ReactTemplate._reset;

exports._reset = _reset;
exports.sidebarWidth = sidebarWidth;
exports.container = container;
exports.header = header;
exports.main = main;
exports.footer = footer;
exports.appLogo = appLogo;
exports.primaryNav = primaryNav;
exports.secondaryNav = secondaryNav;
exports.appLink = appLink;
exports.userNav = userNav;
exports.loginLink = loginLink;
exports.cube = cube;
exports._global = _global;
/* sidebarWidth Not a pure module */
