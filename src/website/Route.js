// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");

function fromUrl(url) {
  var match = url[/* path */0];
  if (match) {
    var accountName = match[0];
    var exit = 0;
    if (accountName === "about" && !match[1]) {
      return /* About */1;
    } else {
      exit = 1;
    }
    if (exit === 1) {
      var match$1 = match[1];
      if (match$1) {
        if (match$1[1]) {
          return /* Home */0;
        } else {
          return /* Post */Block.__(1, [
                    accountName,
                    match$1[0]
                  ]);
        }
      } else {
        return /* Profile */Block.__(0, [accountName]);
      }
    }
    
  } else {
    return /* Home */0;
  }
}

function toString(route) {
  if (typeof route === "number") {
    if (route === 0) {
      return "/";
    } else {
      return "/about";
    }
  } else if (route.tag) {
    return "/" + (route[0] + ("/" + route[1]));
  } else {
    return "/" + route[0];
  }
}

exports.fromUrl = fromUrl;
exports.toString = toString;
/* No side effect */
