// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var ReasonReact = require("reason-react/src/ReasonReact.js");
var ReactHelmet = require("react-helmet");

function make(children) {
  return ReasonReact.wrapJsForReason(ReactHelmet.Helmet, /* () */0, children);
}

var Property = /* module */[];

function toString(prim) {
  return prim.toString();
}

exports.make = make;
exports.Property = Property;
exports.toString = toString;
/* ReasonReact Not a pure module */