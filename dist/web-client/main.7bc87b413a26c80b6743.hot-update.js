webpackHotUpdate("main",{

/***/ "./node_modules/bs-platform/lib/js/js_list.js":
/*!****************************************************!*\
  !*** ./node_modules/bs-platform/lib/js/js_list.js ***!
  \****************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var Js_vector = __webpack_require__(/*! ./js_vector.js */ "./node_modules/bs-platform/lib/js/js_vector.js");

function length(l) {
  var _len = 0;
  var _param = l;
  while(true) {
    var param = _param;
    var len = _len;
    if (param) {
      _param = param[1];
      _len = len + 1 | 0;
      continue ;
    } else {
      return len;
    }
  };
}

function cons(x, xs) {
  return /* :: */[
          x,
          xs
        ];
}

function isEmpty(x) {
  return x === /* [] */0;
}

function hd(param) {
  if (param) {
    return /* Some */[param[0]];
  } else {
    return /* None */0;
  }
}

function tl(param) {
  if (param) {
    return /* Some */[param[1]];
  } else {
    return /* None */0;
  }
}

function nth(l, n) {
  if (n < 0) {
    return /* None */0;
  } else {
    var _l = l;
    var _n = n;
    while(true) {
      var n$1 = _n;
      var l$1 = _l;
      if (l$1) {
        if (n$1 === 0) {
          return /* Some */[l$1[0]];
        } else {
          _n = n$1 - 1 | 0;
          _l = l$1[1];
          continue ;
        }
      } else {
        return /* None */0;
      }
    };
  }
}

function revAppend(_l1, _l2) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1) {
      _l2 = /* :: */[
        l1[0],
        l2
      ];
      _l1 = l1[1];
      continue ;
    } else {
      return l2;
    }
  };
}

function rev(l) {
  return revAppend(l, /* [] */0);
}

function mapRevAux(f, _acc, _ls) {
  while(true) {
    var ls = _ls;
    var acc = _acc;
    if (ls) {
      _ls = ls[1];
      _acc = /* :: */[
        f(ls[0]),
        acc
      ];
      continue ;
    } else {
      return acc;
    }
  };
}

function mapRev(f, ls) {
  return mapRevAux(f, /* [] */0, ls);
}

function map(f, ls) {
  return revAppend(mapRevAux(f, /* [] */0, ls), /* [] */0);
}

function iter(f, _param) {
  while(true) {
    var param = _param;
    if (param) {
      f(param[0]);
      _param = param[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function iteri(f, l) {
  var _i = 0;
  var f$1 = f;
  var _param = l;
  while(true) {
    var param = _param;
    var i = _i;
    if (param) {
      f$1(i, param[0]);
      _param = param[1];
      _i = i + 1 | 0;
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function foldLeft(f, _accu, _l) {
  while(true) {
    var l = _l;
    var accu = _accu;
    if (l) {
      _l = l[1];
      _accu = f(accu, l[0]);
      continue ;
    } else {
      return accu;
    }
  };
}

function tailLoop(f, _acc, _param) {
  while(true) {
    var param = _param;
    var acc = _acc;
    if (param) {
      _param = param[1];
      _acc = f(param[0], acc);
      continue ;
    } else {
      return acc;
    }
  };
}

function foldRight(f, l, init) {
  var loop = function (n, param) {
    if (param) {
      var t = param[1];
      var h = param[0];
      if (n < 1000) {
        return f(h, loop(n + 1 | 0, t));
      } else {
        return f(h, tailLoop(f, init, revAppend(t, /* [] */0)));
      }
    } else {
      return init;
    }
  };
  return loop(0, l);
}

function flatten(lx) {
  var _acc = /* [] */0;
  var _lx = lx;
  while(true) {
    var lx$1 = _lx;
    var acc = _acc;
    if (lx$1) {
      _lx = lx$1[1];
      _acc = revAppend(lx$1[0], acc);
      continue ;
    } else {
      return revAppend(acc, /* [] */0);
    }
  };
}

function filterRevAux(f, _acc, _xs) {
  while(true) {
    var xs = _xs;
    var acc = _acc;
    if (xs) {
      var ys = xs[1];
      var y = xs[0];
      var match = f(y);
      _xs = ys;
      if (match) {
        _acc = /* :: */[
          y,
          acc
        ];
        continue ;
      } else {
        continue ;
      }
    } else {
      return acc;
    }
  };
}

function filter(f, xs) {
  return revAppend(filterRevAux(f, /* [] */0, xs), /* [] */0);
}

function filterMapRevAux(f, _acc, _xs) {
  while(true) {
    var xs = _xs;
    var acc = _acc;
    if (xs) {
      var ys = xs[1];
      var match = f(xs[0]);
      _xs = ys;
      if (match) {
        _acc = /* :: */[
          match[0],
          acc
        ];
        continue ;
      } else {
        continue ;
      }
    } else {
      return acc;
    }
  };
}

function filterMap(f, xs) {
  return revAppend(filterMapRevAux(f, /* [] */0, xs), /* [] */0);
}

function countBy(f, xs) {
  var f$1 = f;
  var _acc = 0;
  var _xs = xs;
  while(true) {
    var xs$1 = _xs;
    var acc = _acc;
    if (xs$1) {
      _xs = xs$1[1];
      _acc = f$1(xs$1[0]) ? acc + 1 | 0 : acc;
      continue ;
    } else {
      return acc;
    }
  };
}

function init(n, f) {
  return Js_vector.toList(Js_vector.init(n, f));
}

function toVector(xs) {
  if (xs) {
    var a = new Array(length(xs));
    var _i = 0;
    var _param = xs;
    while(true) {
      var param = _param;
      var i = _i;
      if (param) {
        a[i] = param[0];
        _param = param[1];
        _i = i + 1 | 0;
        continue ;
      } else {
        return a;
      }
    };
  } else {
    return /* array */[];
  }
}

function equal(cmp, _xs, _ys) {
  while(true) {
    var ys = _ys;
    var xs = _xs;
    if (xs) {
      if (ys && cmp(xs[0], ys[0])) {
        _ys = ys[1];
        _xs = xs[1];
        continue ;
      } else {
        return false;
      }
    } else if (ys) {
      return false;
    } else {
      return true;
    }
  };
}

exports.length = length;
exports.cons = cons;
exports.isEmpty = isEmpty;
exports.hd = hd;
exports.tl = tl;
exports.nth = nth;
exports.revAppend = revAppend;
exports.rev = rev;
exports.mapRev = mapRev;
exports.map = map;
exports.iter = iter;
exports.iteri = iteri;
exports.foldLeft = foldLeft;
exports.foldRight = foldRight;
exports.flatten = flatten;
exports.filter = filter;
exports.filterMap = filterMap;
exports.countBy = countBy;
exports.init = init;
exports.toVector = toVector;
exports.equal = equal;
/* No side effect */


/***/ }),

/***/ "./node_modules/bs-platform/lib/js/js_vector.js":
/*!******************************************************!*\
  !*** ./node_modules/bs-platform/lib/js/js_vector.js ***!
  \******************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";



function filterInPlace(p, a) {
  var i = 0;
  var j = 0;
  while(i < a.length) {
    var v = a[i];
    if (p(v)) {
      a[j] = v;
      j = j + 1 | 0;
    }
    i = i + 1 | 0;
  };
  a.splice(j);
  return /* () */0;
}

function empty(a) {
  a.splice(0);
  return /* () */0;
}

function pushBack(x, xs) {
  xs.push(x);
  return /* () */0;
}

function memByRef(x, xs) {
  return xs.indexOf(x) >= 0;
}

function iter(f, xs) {
  for(var i = 0 ,i_finish = xs.length - 1 | 0; i <= i_finish; ++i){
    f(xs[i]);
  }
  return /* () */0;
}

function iteri(f, a) {
  for(var i = 0 ,i_finish = a.length - 1 | 0; i <= i_finish; ++i){
    f(i, a[i]);
  }
  return /* () */0;
}

function toList(a) {
  var _i = a.length - 1 | 0;
  var _res = /* [] */0;
  while(true) {
    var res = _res;
    var i = _i;
    if (i < 0) {
      return res;
    } else {
      _res = /* :: */[
        a[i],
        res
      ];
      _i = i - 1 | 0;
      continue ;
    }
  };
}

function init(n, f) {
  var v = new Array(n);
  for(var i = 0 ,i_finish = n - 1 | 0; i <= i_finish; ++i){
    v[i] = f(i);
  }
  return v;
}

function copy(x) {
  var len = x.length;
  var b = new Array(len);
  for(var i = 0 ,i_finish = len - 1 | 0; i <= i_finish; ++i){
    b[i] = x[i];
  }
  return b;
}

function map(f, a) {
  var l = a.length;
  var r = new Array(l);
  for(var i = 0 ,i_finish = l - 1 | 0; i <= i_finish; ++i){
    r[i] = f(a[i]);
  }
  return r;
}

function foldLeft(f, x, a) {
  var r = x;
  for(var i = 0 ,i_finish = a.length - 1 | 0; i <= i_finish; ++i){
    r = f(r, a[i]);
  }
  return r;
}

function foldRight(f, a, x) {
  var r = x;
  for(var i = a.length - 1 | 0; i >= 0; --i){
    r = f(a[i], r);
  }
  return r;
}

function mapi(f, a) {
  var l = a.length;
  if (l === 0) {
    return /* array */[];
  } else {
    var r = new Array(l);
    for(var i = 0 ,i_finish = l - 1 | 0; i <= i_finish; ++i){
      r[i] = f(i, a[i]);
    }
    return r;
  }
}

function append(x, a) {
  return a.concat(/* array */[x]);
}

exports.filterInPlace = filterInPlace;
exports.empty = empty;
exports.pushBack = pushBack;
exports.copy = copy;
exports.memByRef = memByRef;
exports.iter = iter;
exports.iteri = iteri;
exports.toList = toList;
exports.map = map;
exports.mapi = mapi;
exports.foldLeft = foldLeft;
exports.foldRight = foldRight;
exports.init = init;
exports.append = append;
/* No side effect */


/***/ }),

/***/ "./src/web-client/Route.js":
/*!*********************************!*\
  !*** ./src/web-client/Route.js ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE


var Block = __webpack_require__(/*! bs-platform/lib/js/block.js */ "./node_modules/bs-platform/lib/js/block.js");
var Js_list = __webpack_require__(/*! bs-platform/lib/js/js_list.js */ "./node_modules/bs-platform/lib/js/js_list.js");
var Belt_List = __webpack_require__(/*! bs-platform/lib/js/belt_List.js */ "./node_modules/bs-platform/lib/js/belt_List.js");

function fromList(parts) {
  if (parts) {
    var accountName = parts[0];
    var exit = 0;
    if (accountName === "about" && !parts[1]) {
      return /* About */1;
    } else {
      exit = 1;
    }
    if (exit === 1) {
      var match = parts[1];
      if (match) {
        var match$1 = match[1];
        var pollId = match[0];
        if (match$1) {
          if (match$1[0] === "results" && !match$1[1]) {
            return /* PollResults */Block.__(2, [
                      accountName,
                      pollId
                    ]);
          } else {
            return /* Home */0;
          }
        } else {
          return /* Poll */Block.__(1, [
                    accountName,
                    pollId
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

function fromUrl(url) {
  return fromList(url[/* path */0]);
}

function fromString(str) {
  return fromList(Js_list.filter((function (str) {
                    return str !== "";
                  }), Belt_List.fromArray(str.split("/"))));
}

function toString(route) {
  if (typeof route === "number") {
    if (route === 0) {
      return "/";
    } else {
      return "/about";
    }
  } else {
    switch (route.tag | 0) {
      case 0 : 
          return "/" + route[0];
      case 1 : 
          return "/" + (route[0] + ("/" + route[1]));
      case 2 : 
          return "/" + (route[0] + ("/" + (route[1] + "/results")));
      
    }
  }
}

exports.fromList = fromList;
exports.fromUrl = fromUrl;
exports.fromString = fromString;
exports.toString = toString;
/* No side effect */


/***/ })

})
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9ub2RlX21vZHVsZXMvYnMtcGxhdGZvcm0vbGliL2pzL2pzX2xpc3QuanMiLCJ3ZWJwYWNrOi8vLy4vbm9kZV9tb2R1bGVzL2JzLXBsYXRmb3JtL2xpYi9qcy9qc192ZWN0b3IuanMiLCJ3ZWJwYWNrOi8vLy4vc3JjL3dlYi1jbGllbnQvUm91dGUuanMiXSwibmFtZXMiOltdLCJtYXBwaW5ncyI6Ijs7Ozs7Ozs7OztBQUFBOztBQUVBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsU0FBUztBQUNUO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7Ozs7Ozs7Ozs7Ozs7QUM1VkE7OztBQUdBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0EsOENBQThDLGVBQWU7QUFDN0Q7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQSw2Q0FBNkMsZUFBZTtBQUM1RDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0Esc0NBQXNDLGVBQWU7QUFDckQ7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0Esd0NBQXdDLGVBQWU7QUFDdkQ7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0Esc0NBQXNDLGVBQWU7QUFDckQ7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBLDZDQUE2QyxlQUFlO0FBQzVEO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQSwrQkFBK0IsUUFBUTtBQUN2QztBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBLHdDQUF3QyxlQUFlO0FBQ3ZEO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7Ozs7Ozs7Ozs7OztBQzFJQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxXQUFXO0FBQ1g7QUFDQTtBQUNBLFNBQVM7QUFDVDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTs7QUFFQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxtQkFBbUI7QUFDbkI7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQSIsImZpbGUiOiJtYWluLjdiYzg3YjQxM2EyNmM4MGI2NzQzLmhvdC11cGRhdGUuanMiLCJzb3VyY2VzQ29udGVudCI6WyIndXNlIHN0cmljdCc7XG5cbnZhciBKc192ZWN0b3IgPSByZXF1aXJlKFwiLi9qc192ZWN0b3IuanNcIik7XG5cbmZ1bmN0aW9uIGxlbmd0aChsKSB7XG4gIHZhciBfbGVuID0gMDtcbiAgdmFyIF9wYXJhbSA9IGw7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcGFyYW0gPSBfcGFyYW07XG4gICAgdmFyIGxlbiA9IF9sZW47XG4gICAgaWYgKHBhcmFtKSB7XG4gICAgICBfcGFyYW0gPSBwYXJhbVsxXTtcbiAgICAgIF9sZW4gPSBsZW4gKyAxIHwgMDtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGxlbjtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGNvbnMoeCwgeHMpIHtcbiAgcmV0dXJuIC8qIDo6ICovW1xuICAgICAgICAgIHgsXG4gICAgICAgICAgeHNcbiAgICAgICAgXTtcbn1cblxuZnVuY3Rpb24gaXNFbXB0eSh4KSB7XG4gIHJldHVybiB4ID09PSAvKiBbXSAqLzA7XG59XG5cbmZ1bmN0aW9uIGhkKHBhcmFtKSB7XG4gIGlmIChwYXJhbSkge1xuICAgIHJldHVybiAvKiBTb21lICovW3BhcmFtWzBdXTtcbiAgfSBlbHNlIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH1cbn1cblxuZnVuY3Rpb24gdGwocGFyYW0pIHtcbiAgaWYgKHBhcmFtKSB7XG4gICAgcmV0dXJuIC8qIFNvbWUgKi9bcGFyYW1bMV1dO1xuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBOb25lICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiBudGgobCwgbikge1xuICBpZiAobiA8IDApIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH0gZWxzZSB7XG4gICAgdmFyIF9sID0gbDtcbiAgICB2YXIgX24gPSBuO1xuICAgIHdoaWxlKHRydWUpIHtcbiAgICAgIHZhciBuJDEgPSBfbjtcbiAgICAgIHZhciBsJDEgPSBfbDtcbiAgICAgIGlmIChsJDEpIHtcbiAgICAgICAgaWYgKG4kMSA9PT0gMCkge1xuICAgICAgICAgIHJldHVybiAvKiBTb21lICovW2wkMVswXV07XG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgX24gPSBuJDEgLSAxIHwgMDtcbiAgICAgICAgICBfbCA9IGwkMVsxXTtcbiAgICAgICAgICBjb250aW51ZSA7XG4gICAgICAgIH1cbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiAvKiBOb25lICovMDtcbiAgICAgIH1cbiAgICB9O1xuICB9XG59XG5cbmZ1bmN0aW9uIHJldkFwcGVuZChfbDEsIF9sMikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGwyID0gX2wyO1xuICAgIHZhciBsMSA9IF9sMTtcbiAgICBpZiAobDEpIHtcbiAgICAgIF9sMiA9IC8qIDo6ICovW1xuICAgICAgICBsMVswXSxcbiAgICAgICAgbDJcbiAgICAgIF07XG4gICAgICBfbDEgPSBsMVsxXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGwyO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gcmV2KGwpIHtcbiAgcmV0dXJuIHJldkFwcGVuZChsLCAvKiBbXSAqLzApO1xufVxuXG5mdW5jdGlvbiBtYXBSZXZBdXgoZiwgX2FjYywgX2xzKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgbHMgPSBfbHM7XG4gICAgdmFyIGFjYyA9IF9hY2M7XG4gICAgaWYgKGxzKSB7XG4gICAgICBfbHMgPSBsc1sxXTtcbiAgICAgIF9hY2MgPSAvKiA6OiAqL1tcbiAgICAgICAgZihsc1swXSksXG4gICAgICAgIGFjY1xuICAgICAgXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGFjYztcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIG1hcFJldihmLCBscykge1xuICByZXR1cm4gbWFwUmV2QXV4KGYsIC8qIFtdICovMCwgbHMpO1xufVxuXG5mdW5jdGlvbiBtYXAoZiwgbHMpIHtcbiAgcmV0dXJuIHJldkFwcGVuZChtYXBSZXZBdXgoZiwgLyogW10gKi8wLCBscyksIC8qIFtdICovMCk7XG59XG5cbmZ1bmN0aW9uIGl0ZXIoZiwgX3BhcmFtKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcGFyYW0gPSBfcGFyYW07XG4gICAgaWYgKHBhcmFtKSB7XG4gICAgICBmKHBhcmFtWzBdKTtcbiAgICAgIF9wYXJhbSA9IHBhcmFtWzFdO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogKCkgKi8wO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gaXRlcmkoZiwgbCkge1xuICB2YXIgX2kgPSAwO1xuICB2YXIgZiQxID0gZjtcbiAgdmFyIF9wYXJhbSA9IGw7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcGFyYW0gPSBfcGFyYW07XG4gICAgdmFyIGkgPSBfaTtcbiAgICBpZiAocGFyYW0pIHtcbiAgICAgIGYkMShpLCBwYXJhbVswXSk7XG4gICAgICBfcGFyYW0gPSBwYXJhbVsxXTtcbiAgICAgIF9pID0gaSArIDEgfCAwO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogKCkgKi8wO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gZm9sZExlZnQoZiwgX2FjY3UsIF9sKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgbCA9IF9sO1xuICAgIHZhciBhY2N1ID0gX2FjY3U7XG4gICAgaWYgKGwpIHtcbiAgICAgIF9sID0gbFsxXTtcbiAgICAgIF9hY2N1ID0gZihhY2N1LCBsWzBdKTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGFjY3U7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiB0YWlsTG9vcChmLCBfYWNjLCBfcGFyYW0pIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBwYXJhbSA9IF9wYXJhbTtcbiAgICB2YXIgYWNjID0gX2FjYztcbiAgICBpZiAocGFyYW0pIHtcbiAgICAgIF9wYXJhbSA9IHBhcmFtWzFdO1xuICAgICAgX2FjYyA9IGYocGFyYW1bMF0sIGFjYyk7XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBhY2M7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBmb2xkUmlnaHQoZiwgbCwgaW5pdCkge1xuICB2YXIgbG9vcCA9IGZ1bmN0aW9uIChuLCBwYXJhbSkge1xuICAgIGlmIChwYXJhbSkge1xuICAgICAgdmFyIHQgPSBwYXJhbVsxXTtcbiAgICAgIHZhciBoID0gcGFyYW1bMF07XG4gICAgICBpZiAobiA8IDEwMDApIHtcbiAgICAgICAgcmV0dXJuIGYoaCwgbG9vcChuICsgMSB8IDAsIHQpKTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiBmKGgsIHRhaWxMb29wKGYsIGluaXQsIHJldkFwcGVuZCh0LCAvKiBbXSAqLzApKSk7XG4gICAgICB9XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBpbml0O1xuICAgIH1cbiAgfTtcbiAgcmV0dXJuIGxvb3AoMCwgbCk7XG59XG5cbmZ1bmN0aW9uIGZsYXR0ZW4obHgpIHtcbiAgdmFyIF9hY2MgPSAvKiBbXSAqLzA7XG4gIHZhciBfbHggPSBseDtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBseCQxID0gX2x4O1xuICAgIHZhciBhY2MgPSBfYWNjO1xuICAgIGlmIChseCQxKSB7XG4gICAgICBfbHggPSBseCQxWzFdO1xuICAgICAgX2FjYyA9IHJldkFwcGVuZChseCQxWzBdLCBhY2MpO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gcmV2QXBwZW5kKGFjYywgLyogW10gKi8wKTtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGZpbHRlclJldkF1eChmLCBfYWNjLCBfeHMpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciB4cyA9IF94cztcbiAgICB2YXIgYWNjID0gX2FjYztcbiAgICBpZiAoeHMpIHtcbiAgICAgIHZhciB5cyA9IHhzWzFdO1xuICAgICAgdmFyIHkgPSB4c1swXTtcbiAgICAgIHZhciBtYXRjaCA9IGYoeSk7XG4gICAgICBfeHMgPSB5cztcbiAgICAgIGlmIChtYXRjaCkge1xuICAgICAgICBfYWNjID0gLyogOjogKi9bXG4gICAgICAgICAgeSxcbiAgICAgICAgICBhY2NcbiAgICAgICAgXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gYWNjO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gZmlsdGVyKGYsIHhzKSB7XG4gIHJldHVybiByZXZBcHBlbmQoZmlsdGVyUmV2QXV4KGYsIC8qIFtdICovMCwgeHMpLCAvKiBbXSAqLzApO1xufVxuXG5mdW5jdGlvbiBmaWx0ZXJNYXBSZXZBdXgoZiwgX2FjYywgX3hzKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgeHMgPSBfeHM7XG4gICAgdmFyIGFjYyA9IF9hY2M7XG4gICAgaWYgKHhzKSB7XG4gICAgICB2YXIgeXMgPSB4c1sxXTtcbiAgICAgIHZhciBtYXRjaCA9IGYoeHNbMF0pO1xuICAgICAgX3hzID0geXM7XG4gICAgICBpZiAobWF0Y2gpIHtcbiAgICAgICAgX2FjYyA9IC8qIDo6ICovW1xuICAgICAgICAgIG1hdGNoWzBdLFxuICAgICAgICAgIGFjY1xuICAgICAgICBdO1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBhY2M7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBmaWx0ZXJNYXAoZiwgeHMpIHtcbiAgcmV0dXJuIHJldkFwcGVuZChmaWx0ZXJNYXBSZXZBdXgoZiwgLyogW10gKi8wLCB4cyksIC8qIFtdICovMCk7XG59XG5cbmZ1bmN0aW9uIGNvdW50QnkoZiwgeHMpIHtcbiAgdmFyIGYkMSA9IGY7XG4gIHZhciBfYWNjID0gMDtcbiAgdmFyIF94cyA9IHhzO1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHhzJDEgPSBfeHM7XG4gICAgdmFyIGFjYyA9IF9hY2M7XG4gICAgaWYgKHhzJDEpIHtcbiAgICAgIF94cyA9IHhzJDFbMV07XG4gICAgICBfYWNjID0gZiQxKHhzJDFbMF0pID8gYWNjICsgMSB8IDAgOiBhY2M7XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBhY2M7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBpbml0KG4sIGYpIHtcbiAgcmV0dXJuIEpzX3ZlY3Rvci50b0xpc3QoSnNfdmVjdG9yLmluaXQobiwgZikpO1xufVxuXG5mdW5jdGlvbiB0b1ZlY3Rvcih4cykge1xuICBpZiAoeHMpIHtcbiAgICB2YXIgYSA9IG5ldyBBcnJheShsZW5ndGgoeHMpKTtcbiAgICB2YXIgX2kgPSAwO1xuICAgIHZhciBfcGFyYW0gPSB4cztcbiAgICB3aGlsZSh0cnVlKSB7XG4gICAgICB2YXIgcGFyYW0gPSBfcGFyYW07XG4gICAgICB2YXIgaSA9IF9pO1xuICAgICAgaWYgKHBhcmFtKSB7XG4gICAgICAgIGFbaV0gPSBwYXJhbVswXTtcbiAgICAgICAgX3BhcmFtID0gcGFyYW1bMV07XG4gICAgICAgIF9pID0gaSArIDEgfCAwO1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICByZXR1cm4gYTtcbiAgICAgIH1cbiAgICB9O1xuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBhcnJheSAqL1tdO1xuICB9XG59XG5cbmZ1bmN0aW9uIGVxdWFsKGNtcCwgX3hzLCBfeXMpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciB5cyA9IF95cztcbiAgICB2YXIgeHMgPSBfeHM7XG4gICAgaWYgKHhzKSB7XG4gICAgICBpZiAoeXMgJiYgY21wKHhzWzBdLCB5c1swXSkpIHtcbiAgICAgICAgX3lzID0geXNbMV07XG4gICAgICAgIF94cyA9IHhzWzFdO1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICByZXR1cm4gZmFsc2U7XG4gICAgICB9XG4gICAgfSBlbHNlIGlmICh5cykge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gdHJ1ZTtcbiAgICB9XG4gIH07XG59XG5cbmV4cG9ydHMubGVuZ3RoID0gbGVuZ3RoO1xuZXhwb3J0cy5jb25zID0gY29ucztcbmV4cG9ydHMuaXNFbXB0eSA9IGlzRW1wdHk7XG5leHBvcnRzLmhkID0gaGQ7XG5leHBvcnRzLnRsID0gdGw7XG5leHBvcnRzLm50aCA9IG50aDtcbmV4cG9ydHMucmV2QXBwZW5kID0gcmV2QXBwZW5kO1xuZXhwb3J0cy5yZXYgPSByZXY7XG5leHBvcnRzLm1hcFJldiA9IG1hcFJldjtcbmV4cG9ydHMubWFwID0gbWFwO1xuZXhwb3J0cy5pdGVyID0gaXRlcjtcbmV4cG9ydHMuaXRlcmkgPSBpdGVyaTtcbmV4cG9ydHMuZm9sZExlZnQgPSBmb2xkTGVmdDtcbmV4cG9ydHMuZm9sZFJpZ2h0ID0gZm9sZFJpZ2h0O1xuZXhwb3J0cy5mbGF0dGVuID0gZmxhdHRlbjtcbmV4cG9ydHMuZmlsdGVyID0gZmlsdGVyO1xuZXhwb3J0cy5maWx0ZXJNYXAgPSBmaWx0ZXJNYXA7XG5leHBvcnRzLmNvdW50QnkgPSBjb3VudEJ5O1xuZXhwb3J0cy5pbml0ID0gaW5pdDtcbmV4cG9ydHMudG9WZWN0b3IgPSB0b1ZlY3RvcjtcbmV4cG9ydHMuZXF1YWwgPSBlcXVhbDtcbi8qIE5vIHNpZGUgZWZmZWN0ICovXG4iLCIndXNlIHN0cmljdCc7XG5cblxuZnVuY3Rpb24gZmlsdGVySW5QbGFjZShwLCBhKSB7XG4gIHZhciBpID0gMDtcbiAgdmFyIGogPSAwO1xuICB3aGlsZShpIDwgYS5sZW5ndGgpIHtcbiAgICB2YXIgdiA9IGFbaV07XG4gICAgaWYgKHAodikpIHtcbiAgICAgIGFbal0gPSB2O1xuICAgICAgaiA9IGogKyAxIHwgMDtcbiAgICB9XG4gICAgaSA9IGkgKyAxIHwgMDtcbiAgfTtcbiAgYS5zcGxpY2Uoaik7XG4gIHJldHVybiAvKiAoKSAqLzA7XG59XG5cbmZ1bmN0aW9uIGVtcHR5KGEpIHtcbiAgYS5zcGxpY2UoMCk7XG4gIHJldHVybiAvKiAoKSAqLzA7XG59XG5cbmZ1bmN0aW9uIHB1c2hCYWNrKHgsIHhzKSB7XG4gIHhzLnB1c2goeCk7XG4gIHJldHVybiAvKiAoKSAqLzA7XG59XG5cbmZ1bmN0aW9uIG1lbUJ5UmVmKHgsIHhzKSB7XG4gIHJldHVybiB4cy5pbmRleE9mKHgpID49IDA7XG59XG5cbmZ1bmN0aW9uIGl0ZXIoZiwgeHMpIHtcbiAgZm9yKHZhciBpID0gMCAsaV9maW5pc2ggPSB4cy5sZW5ndGggLSAxIHwgMDsgaSA8PSBpX2ZpbmlzaDsgKytpKXtcbiAgICBmKHhzW2ldKTtcbiAgfVxuICByZXR1cm4gLyogKCkgKi8wO1xufVxuXG5mdW5jdGlvbiBpdGVyaShmLCBhKSB7XG4gIGZvcih2YXIgaSA9IDAgLGlfZmluaXNoID0gYS5sZW5ndGggLSAxIHwgMDsgaSA8PSBpX2ZpbmlzaDsgKytpKXtcbiAgICBmKGksIGFbaV0pO1xuICB9XG4gIHJldHVybiAvKiAoKSAqLzA7XG59XG5cbmZ1bmN0aW9uIHRvTGlzdChhKSB7XG4gIHZhciBfaSA9IGEubGVuZ3RoIC0gMSB8IDA7XG4gIHZhciBfcmVzID0gLyogW10gKi8wO1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHJlcyA9IF9yZXM7XG4gICAgdmFyIGkgPSBfaTtcbiAgICBpZiAoaSA8IDApIHtcbiAgICAgIHJldHVybiByZXM7XG4gICAgfSBlbHNlIHtcbiAgICAgIF9yZXMgPSAvKiA6OiAqL1tcbiAgICAgICAgYVtpXSxcbiAgICAgICAgcmVzXG4gICAgICBdO1xuICAgICAgX2kgPSBpIC0gMSB8IDA7XG4gICAgICBjb250aW51ZSA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBpbml0KG4sIGYpIHtcbiAgdmFyIHYgPSBuZXcgQXJyYXkobik7XG4gIGZvcih2YXIgaSA9IDAgLGlfZmluaXNoID0gbiAtIDEgfCAwOyBpIDw9IGlfZmluaXNoOyArK2kpe1xuICAgIHZbaV0gPSBmKGkpO1xuICB9XG4gIHJldHVybiB2O1xufVxuXG5mdW5jdGlvbiBjb3B5KHgpIHtcbiAgdmFyIGxlbiA9IHgubGVuZ3RoO1xuICB2YXIgYiA9IG5ldyBBcnJheShsZW4pO1xuICBmb3IodmFyIGkgPSAwICxpX2ZpbmlzaCA9IGxlbiAtIDEgfCAwOyBpIDw9IGlfZmluaXNoOyArK2kpe1xuICAgIGJbaV0gPSB4W2ldO1xuICB9XG4gIHJldHVybiBiO1xufVxuXG5mdW5jdGlvbiBtYXAoZiwgYSkge1xuICB2YXIgbCA9IGEubGVuZ3RoO1xuICB2YXIgciA9IG5ldyBBcnJheShsKTtcbiAgZm9yKHZhciBpID0gMCAsaV9maW5pc2ggPSBsIC0gMSB8IDA7IGkgPD0gaV9maW5pc2g7ICsraSl7XG4gICAgcltpXSA9IGYoYVtpXSk7XG4gIH1cbiAgcmV0dXJuIHI7XG59XG5cbmZ1bmN0aW9uIGZvbGRMZWZ0KGYsIHgsIGEpIHtcbiAgdmFyIHIgPSB4O1xuICBmb3IodmFyIGkgPSAwICxpX2ZpbmlzaCA9IGEubGVuZ3RoIC0gMSB8IDA7IGkgPD0gaV9maW5pc2g7ICsraSl7XG4gICAgciA9IGYociwgYVtpXSk7XG4gIH1cbiAgcmV0dXJuIHI7XG59XG5cbmZ1bmN0aW9uIGZvbGRSaWdodChmLCBhLCB4KSB7XG4gIHZhciByID0geDtcbiAgZm9yKHZhciBpID0gYS5sZW5ndGggLSAxIHwgMDsgaSA+PSAwOyAtLWkpe1xuICAgIHIgPSBmKGFbaV0sIHIpO1xuICB9XG4gIHJldHVybiByO1xufVxuXG5mdW5jdGlvbiBtYXBpKGYsIGEpIHtcbiAgdmFyIGwgPSBhLmxlbmd0aDtcbiAgaWYgKGwgPT09IDApIHtcbiAgICByZXR1cm4gLyogYXJyYXkgKi9bXTtcbiAgfSBlbHNlIHtcbiAgICB2YXIgciA9IG5ldyBBcnJheShsKTtcbiAgICBmb3IodmFyIGkgPSAwICxpX2ZpbmlzaCA9IGwgLSAxIHwgMDsgaSA8PSBpX2ZpbmlzaDsgKytpKXtcbiAgICAgIHJbaV0gPSBmKGksIGFbaV0pO1xuICAgIH1cbiAgICByZXR1cm4gcjtcbiAgfVxufVxuXG5mdW5jdGlvbiBhcHBlbmQoeCwgYSkge1xuICByZXR1cm4gYS5jb25jYXQoLyogYXJyYXkgKi9beF0pO1xufVxuXG5leHBvcnRzLmZpbHRlckluUGxhY2UgPSBmaWx0ZXJJblBsYWNlO1xuZXhwb3J0cy5lbXB0eSA9IGVtcHR5O1xuZXhwb3J0cy5wdXNoQmFjayA9IHB1c2hCYWNrO1xuZXhwb3J0cy5jb3B5ID0gY29weTtcbmV4cG9ydHMubWVtQnlSZWYgPSBtZW1CeVJlZjtcbmV4cG9ydHMuaXRlciA9IGl0ZXI7XG5leHBvcnRzLml0ZXJpID0gaXRlcmk7XG5leHBvcnRzLnRvTGlzdCA9IHRvTGlzdDtcbmV4cG9ydHMubWFwID0gbWFwO1xuZXhwb3J0cy5tYXBpID0gbWFwaTtcbmV4cG9ydHMuZm9sZExlZnQgPSBmb2xkTGVmdDtcbmV4cG9ydHMuZm9sZFJpZ2h0ID0gZm9sZFJpZ2h0O1xuZXhwb3J0cy5pbml0ID0gaW5pdDtcbmV4cG9ydHMuYXBwZW5kID0gYXBwZW5kO1xuLyogTm8gc2lkZSBlZmZlY3QgKi9cbiIsIi8vIEdlbmVyYXRlZCBieSBCVUNLTEVTQ1JJUFQgVkVSU0lPTiAzLjEuNSwgUExFQVNFIEVESVQgV0lUSCBDQVJFXG4ndXNlIHN0cmljdCc7XG5cbnZhciBCbG9jayA9IHJlcXVpcmUoXCJicy1wbGF0Zm9ybS9saWIvanMvYmxvY2suanNcIik7XG52YXIgSnNfbGlzdCA9IHJlcXVpcmUoXCJicy1wbGF0Zm9ybS9saWIvanMvanNfbGlzdC5qc1wiKTtcbnZhciBCZWx0X0xpc3QgPSByZXF1aXJlKFwiYnMtcGxhdGZvcm0vbGliL2pzL2JlbHRfTGlzdC5qc1wiKTtcblxuZnVuY3Rpb24gZnJvbUxpc3QocGFydHMpIHtcbiAgaWYgKHBhcnRzKSB7XG4gICAgdmFyIGFjY291bnROYW1lID0gcGFydHNbMF07XG4gICAgdmFyIGV4aXQgPSAwO1xuICAgIGlmIChhY2NvdW50TmFtZSA9PT0gXCJhYm91dFwiICYmICFwYXJ0c1sxXSkge1xuICAgICAgcmV0dXJuIC8qIEFib3V0ICovMTtcbiAgICB9IGVsc2Uge1xuICAgICAgZXhpdCA9IDE7XG4gICAgfVxuICAgIGlmIChleGl0ID09PSAxKSB7XG4gICAgICB2YXIgbWF0Y2ggPSBwYXJ0c1sxXTtcbiAgICAgIGlmIChtYXRjaCkge1xuICAgICAgICB2YXIgbWF0Y2gkMSA9IG1hdGNoWzFdO1xuICAgICAgICB2YXIgcG9sbElkID0gbWF0Y2hbMF07XG4gICAgICAgIGlmIChtYXRjaCQxKSB7XG4gICAgICAgICAgaWYgKG1hdGNoJDFbMF0gPT09IFwicmVzdWx0c1wiICYmICFtYXRjaCQxWzFdKSB7XG4gICAgICAgICAgICByZXR1cm4gLyogUG9sbFJlc3VsdHMgKi9CbG9jay5fXygyLCBbXG4gICAgICAgICAgICAgICAgICAgICAgYWNjb3VudE5hbWUsXG4gICAgICAgICAgICAgICAgICAgICAgcG9sbElkXG4gICAgICAgICAgICAgICAgICAgIF0pO1xuICAgICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgICByZXR1cm4gLyogSG9tZSAqLzA7XG4gICAgICAgICAgfVxuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIHJldHVybiAvKiBQb2xsICovQmxvY2suX18oMSwgW1xuICAgICAgICAgICAgICAgICAgICBhY2NvdW50TmFtZSxcbiAgICAgICAgICAgICAgICAgICAgcG9sbElkXG4gICAgICAgICAgICAgICAgICBdKTtcbiAgICAgICAgfVxuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIC8qIFByb2ZpbGUgKi9CbG9jay5fXygwLCBbYWNjb3VudE5hbWVdKTtcbiAgICAgIH1cbiAgICB9XG4gICAgXG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIC8qIEhvbWUgKi8wO1xuICB9XG59XG5cbmZ1bmN0aW9uIGZyb21VcmwodXJsKSB7XG4gIHJldHVybiBmcm9tTGlzdCh1cmxbLyogcGF0aCAqLzBdKTtcbn1cblxuZnVuY3Rpb24gZnJvbVN0cmluZyhzdHIpIHtcbiAgcmV0dXJuIGZyb21MaXN0KEpzX2xpc3QuZmlsdGVyKChmdW5jdGlvbiAoc3RyKSB7XG4gICAgICAgICAgICAgICAgICAgIHJldHVybiBzdHIgIT09IFwiXCI7XG4gICAgICAgICAgICAgICAgICB9KSwgQmVsdF9MaXN0LmZyb21BcnJheShzdHIuc3BsaXQoXCIvXCIpKSkpO1xufVxuXG5mdW5jdGlvbiB0b1N0cmluZyhyb3V0ZSkge1xuICBpZiAodHlwZW9mIHJvdXRlID09PSBcIm51bWJlclwiKSB7XG4gICAgaWYgKHJvdXRlID09PSAwKSB7XG4gICAgICByZXR1cm4gXCIvXCI7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBcIi9hYm91dFwiO1xuICAgIH1cbiAgfSBlbHNlIHtcbiAgICBzd2l0Y2ggKHJvdXRlLnRhZyB8IDApIHtcbiAgICAgIGNhc2UgMCA6IFxuICAgICAgICAgIHJldHVybiBcIi9cIiArIHJvdXRlWzBdO1xuICAgICAgY2FzZSAxIDogXG4gICAgICAgICAgcmV0dXJuIFwiL1wiICsgKHJvdXRlWzBdICsgKFwiL1wiICsgcm91dGVbMV0pKTtcbiAgICAgIGNhc2UgMiA6IFxuICAgICAgICAgIHJldHVybiBcIi9cIiArIChyb3V0ZVswXSArIChcIi9cIiArIChyb3V0ZVsxXSArIFwiL3Jlc3VsdHNcIikpKTtcbiAgICAgIFxuICAgIH1cbiAgfVxufVxuXG5leHBvcnRzLmZyb21MaXN0ID0gZnJvbUxpc3Q7XG5leHBvcnRzLmZyb21VcmwgPSBmcm9tVXJsO1xuZXhwb3J0cy5mcm9tU3RyaW5nID0gZnJvbVN0cmluZztcbmV4cG9ydHMudG9TdHJpbmcgPSB0b1N0cmluZztcbi8qIE5vIHNpZGUgZWZmZWN0ICovXG4iXSwic291cmNlUm9vdCI6IiJ9