// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Js_option = require("bs-platform/lib/js/js_option.js");
var Belt_Array = require("bs-platform/lib/js/belt_Array.js");
var Belt_Option = require("bs-platform/lib/js/belt_Option.js");

function accountName(t) {
  return Belt_Option.map(Js_option.andThen((function (identity) {
                    return Belt_Array.get(identity.accounts, 0);
                  }), t[/* identity */1]), (function (prim) {
                return prim.name;
              }));
}

var initial = /* record */[
  /* scatter : None */0,
  /* identity : None */0,
  /* language : English */0
];

exports.initial = initial;
exports.accountName = accountName;
/* No side effect */