webpackHotUpdate("main",{

/***/ "./node_modules/bs-platform/lib/js/belt_List.js":
/*!******************************************************!*\
  !*** ./node_modules/bs-platform/lib/js/belt_List.js ***!
  \******************************************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";


var Curry = __webpack_require__(/*! ./curry.js */ "./node_modules/bs-platform/lib/js/curry.js");
var Belt_Array = __webpack_require__(/*! ./belt_Array.js */ "./node_modules/bs-platform/lib/js/belt_Array.js");
var Belt_SortArray = __webpack_require__(/*! ./belt_SortArray.js */ "./node_modules/bs-platform/lib/js/belt_SortArray.js");

function head(x) {
  if (x) {
    return /* Some */[x[0]];
  } else {
    return /* None */0;
  }
}

function headExn(x) {
  if (x) {
    return x[0];
  } else {
    throw new Error("headExn");
  }
}

function tail(x) {
  if (x) {
    return /* Some */[x[1]];
  } else {
    return /* None */0;
  }
}

function tailExn(x) {
  if (x) {
    return x[1];
  } else {
    throw new Error("tailExn");
  }
}

function add(xs, x) {
  return /* :: */[
          x,
          xs
        ];
}

function get(x, n) {
  if (n < 0) {
    return /* None */0;
  } else {
    var _x = x;
    var _n = n;
    while(true) {
      var n$1 = _n;
      var x$1 = _x;
      if (x$1) {
        if (n$1 === 0) {
          return /* Some */[x$1[0]];
        } else {
          _n = n$1 - 1 | 0;
          _x = x$1[1];
          continue ;
        }
      } else {
        return /* None */0;
      }
    };
  }
}

function getExn(x, n) {
  if (n < 0) {
    throw new Error("getExn");
  } else {
    var _x = x;
    var _n = n;
    while(true) {
      var n$1 = _n;
      var x$1 = _x;
      if (x$1) {
        if (n$1 === 0) {
          return x$1[0];
        } else {
          _n = n$1 - 1 | 0;
          _x = x$1[1];
          continue ;
        }
      } else {
        throw new Error("getExn");
      }
    };
  }
}

function partitionAux(p, _cell, _precX, _precY) {
  while(true) {
    var precY = _precY;
    var precX = _precX;
    var cell = _cell;
    if (cell) {
      var t = cell[1];
      var h = cell[0];
      var next = /* :: */[
        h,
        /* [] */0
      ];
      if (p(h)) {
        precX[1] = next;
        _precX = next;
        _cell = t;
        continue ;
      } else {
        precY[1] = next;
        _precY = next;
        _cell = t;
        continue ;
      }
    } else {
      return /* () */0;
    }
  };
}

function splitAux(_cell, _precX, _precY) {
  while(true) {
    var precY = _precY;
    var precX = _precX;
    var cell = _cell;
    if (cell) {
      var match = cell[0];
      var nextA = /* :: */[
        match[0],
        /* [] */0
      ];
      var nextB = /* :: */[
        match[1],
        /* [] */0
      ];
      precX[1] = nextA;
      precY[1] = nextB;
      _precY = nextB;
      _precX = nextA;
      _cell = cell[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function copyAuxCont(_cellX, _prec) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    if (cellX) {
      var next = /* :: */[
        cellX[0],
        /* [] */0
      ];
      prec[1] = next;
      _prec = next;
      _cellX = cellX[1];
      continue ;
    } else {
      return prec;
    }
  };
}

function copyAuxWitFilter(f, _cellX, _prec) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    if (cellX) {
      var t = cellX[1];
      var h = cellX[0];
      if (f(h)) {
        var next = /* :: */[
          h,
          /* [] */0
        ];
        prec[1] = next;
        _prec = next;
        _cellX = t;
        continue ;
      } else {
        _cellX = t;
        continue ;
      }
    } else {
      return /* () */0;
    }
  };
}

function copyAuxWitFilterMap(f, _cellX, _prec) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    if (cellX) {
      var t = cellX[1];
      var match = f(cellX[0]);
      if (match) {
        var next = /* :: */[
          match[0],
          /* [] */0
        ];
        prec[1] = next;
        _prec = next;
        _cellX = t;
        continue ;
      } else {
        _cellX = t;
        continue ;
      }
    } else {
      return /* () */0;
    }
  };
}

function removeAssocAuxWithMap(_cellX, x, _prec, f) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    if (cellX) {
      var t = cellX[1];
      var h = cellX[0];
      if (f(h[0], x)) {
        prec[1] = t;
        return true;
      } else {
        var next = /* :: */[
          h,
          /* [] */0
        ];
        prec[1] = next;
        _prec = next;
        _cellX = t;
        continue ;
      }
    } else {
      return false;
    }
  };
}

function setAssocAuxWithMap(_cellX, x, k, _prec, eq) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    if (cellX) {
      var t = cellX[1];
      var h = cellX[0];
      if (eq(h[0], x)) {
        prec[1] = /* :: */[
          /* tuple */[
            x,
            k
          ],
          t
        ];
        return true;
      } else {
        var next = /* :: */[
          h,
          /* [] */0
        ];
        prec[1] = next;
        _prec = next;
        _cellX = t;
        continue ;
      }
    } else {
      return false;
    }
  };
}

function copyAuxWithMap(_cellX, _prec, f) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    if (cellX) {
      var next = /* :: */[
        f(cellX[0]),
        /* [] */0
      ];
      prec[1] = next;
      _prec = next;
      _cellX = cellX[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function zipAux(_cellX, _cellY, _prec) {
  while(true) {
    var prec = _prec;
    var cellY = _cellY;
    var cellX = _cellX;
    if (cellX && cellY) {
      var next = /* :: */[
        /* tuple */[
          cellX[0],
          cellY[0]
        ],
        /* [] */0
      ];
      prec[1] = next;
      _prec = next;
      _cellY = cellY[1];
      _cellX = cellX[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function copyAuxWithMap2(f, _cellX, _cellY, _prec) {
  while(true) {
    var prec = _prec;
    var cellY = _cellY;
    var cellX = _cellX;
    if (cellX && cellY) {
      var next = /* :: */[
        f(cellX[0], cellY[0]),
        /* [] */0
      ];
      prec[1] = next;
      _prec = next;
      _cellY = cellY[1];
      _cellX = cellX[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function copyAuxWithMapI(f, _i, _cellX, _prec) {
  while(true) {
    var prec = _prec;
    var cellX = _cellX;
    var i = _i;
    if (cellX) {
      var next = /* :: */[
        f(i, cellX[0]),
        /* [] */0
      ];
      prec[1] = next;
      _prec = next;
      _cellX = cellX[1];
      _i = i + 1 | 0;
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function takeAux(_n, _cell, _prec) {
  while(true) {
    var prec = _prec;
    var cell = _cell;
    var n = _n;
    if (n === 0) {
      return true;
    } else if (cell) {
      var cell$1 = /* :: */[
        cell[0],
        /* [] */0
      ];
      prec[1] = cell$1;
      _prec = cell$1;
      _cell = cell[1];
      _n = n - 1 | 0;
      continue ;
    } else {
      return false;
    }
  };
}

function splitAtAux(_n, _cell, _prec) {
  while(true) {
    var prec = _prec;
    var cell = _cell;
    var n = _n;
    if (n === 0) {
      return /* Some */[cell];
    } else if (cell) {
      var cell$1 = /* :: */[
        cell[0],
        /* [] */0
      ];
      prec[1] = cell$1;
      _prec = cell$1;
      _cell = cell[1];
      _n = n - 1 | 0;
      continue ;
    } else {
      return /* None */0;
    }
  };
}

function take(lst, n) {
  if (n < 0) {
    return /* None */0;
  } else if (n === 0) {
    return /* Some */[/* [] */0];
  } else if (lst) {
    var cell = /* :: */[
      lst[0],
      /* [] */0
    ];
    var has = takeAux(n - 1 | 0, lst[1], cell);
    if (has) {
      return /* Some */[cell];
    } else {
      return /* None */0;
    }
  } else {
    return /* None */0;
  }
}

function drop(lst, n) {
  if (n < 0) {
    return /* None */0;
  } else {
    var _l = lst;
    var _n = n;
    while(true) {
      var n$1 = _n;
      var l = _l;
      if (n$1 === 0) {
        return /* Some */[l];
      } else if (l) {
        _n = n$1 - 1 | 0;
        _l = l[1];
        continue ;
      } else {
        return /* None */0;
      }
    };
  }
}

function splitAt(lst, n) {
  if (n < 0) {
    return /* None */0;
  } else if (n === 0) {
    return /* Some */[/* tuple */[
              /* [] */0,
              lst
            ]];
  } else if (lst) {
    var cell = /* :: */[
      lst[0],
      /* [] */0
    ];
    var rest = splitAtAux(n - 1 | 0, lst[1], cell);
    if (rest) {
      return /* Some */[/* tuple */[
                cell,
                rest[0]
              ]];
    } else {
      return /* None */0;
    }
  } else {
    return /* None */0;
  }
}

function concat(xs, ys) {
  if (xs) {
    var cell = /* :: */[
      xs[0],
      /* [] */0
    ];
    copyAuxCont(xs[1], cell)[1] = ys;
    return cell;
  } else {
    return ys;
  }
}

function mapU(xs, f) {
  if (xs) {
    var cell = /* :: */[
      f(xs[0]),
      /* [] */0
    ];
    copyAuxWithMap(xs[1], cell, f);
    return cell;
  } else {
    return /* [] */0;
  }
}

function map(xs, f) {
  return mapU(xs, Curry.__1(f));
}

function zipByU(l1, l2, f) {
  if (l1 && l2) {
    var cell = /* :: */[
      f(l1[0], l2[0]),
      /* [] */0
    ];
    copyAuxWithMap2(f, l1[1], l2[1], cell);
    return cell;
  } else {
    return /* [] */0;
  }
}

function zipBy(l1, l2, f) {
  return zipByU(l1, l2, Curry.__2(f));
}

function mapWithIndexU(xs, f) {
  if (xs) {
    var cell = /* :: */[
      f(0, xs[0]),
      /* [] */0
    ];
    copyAuxWithMapI(f, 1, xs[1], cell);
    return cell;
  } else {
    return /* [] */0;
  }
}

function mapWithIndex(xs, f) {
  return mapWithIndexU(xs, Curry.__2(f));
}

function makeByU(n, f) {
  if (n <= 0) {
    return /* [] */0;
  } else {
    var headX = /* :: */[
      f(0),
      /* [] */0
    ];
    var cur = headX;
    var i = 1;
    while(i < n) {
      var v = /* :: */[
        f(i),
        /* [] */0
      ];
      cur[1] = v;
      cur = v;
      i = i + 1 | 0;
    };
    return headX;
  }
}

function makeBy(n, f) {
  return makeByU(n, Curry.__1(f));
}

function make(n, v) {
  if (n <= 0) {
    return /* [] */0;
  } else {
    var headX = /* :: */[
      v,
      /* [] */0
    ];
    var cur = headX;
    var i = 1;
    while(i < n) {
      var v$1 = /* :: */[
        v,
        /* [] */0
      ];
      cur[1] = v$1;
      cur = v$1;
      i = i + 1 | 0;
    };
    return headX;
  }
}

function length(xs) {
  var _x = xs;
  var _acc = 0;
  while(true) {
    var acc = _acc;
    var x = _x;
    if (x) {
      _acc = acc + 1 | 0;
      _x = x[1];
      continue ;
    } else {
      return acc;
    }
  };
}

function fillAux(arr, _i, _x) {
  while(true) {
    var x = _x;
    var i = _i;
    if (x) {
      arr[i] = x[0];
      _x = x[1];
      _i = i + 1 | 0;
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function fromArray(a) {
  var a$1 = a;
  var _i = a.length - 1 | 0;
  var _res = /* [] */0;
  while(true) {
    var res = _res;
    var i = _i;
    if (i < 0) {
      return res;
    } else {
      _res = /* :: */[
        a$1[i],
        res
      ];
      _i = i - 1 | 0;
      continue ;
    }
  };
}

function toArray(x) {
  var len = length(x);
  var arr = new Array(len);
  fillAux(arr, 0, x);
  return arr;
}

function shuffle(xs) {
  var v = toArray(xs);
  Belt_Array.shuffleInPlace(v);
  return fromArray(v);
}

function reverseConcat(_l1, _l2) {
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

function reverse(l) {
  return reverseConcat(l, /* [] */0);
}

function flattenAux(_prec, _xs) {
  while(true) {
    var xs = _xs;
    var prec = _prec;
    if (xs) {
      _xs = xs[1];
      _prec = copyAuxCont(xs[0], prec);
      continue ;
    } else {
      prec[1] = /* [] */0;
      return /* () */0;
    }
  };
}

function flatten(_xs) {
  while(true) {
    var xs = _xs;
    if (xs) {
      var match = xs[0];
      if (match) {
        var cell = /* :: */[
          match[0],
          /* [] */0
        ];
        flattenAux(copyAuxCont(match[1], cell), xs[1]);
        return cell;
      } else {
        _xs = xs[1];
        continue ;
      }
    } else {
      return /* [] */0;
    }
  };
}

function concatMany(xs) {
  var len = xs.length;
  if (len !== 1) {
    if (len !== 0) {
      var len$1 = xs.length;
      var v = xs[len$1 - 1 | 0];
      for(var i = len$1 - 2 | 0; i >= 0; --i){
        v = concat(xs[i], v);
      }
      return v;
    } else {
      return /* [] */0;
    }
  } else {
    return xs[0];
  }
}

function mapReverseU(l, f) {
  var f$1 = f;
  var _accu = /* [] */0;
  var _xs = l;
  while(true) {
    var xs = _xs;
    var accu = _accu;
    if (xs) {
      _xs = xs[1];
      _accu = /* :: */[
        f$1(xs[0]),
        accu
      ];
      continue ;
    } else {
      return accu;
    }
  };
}

function mapReverse(l, f) {
  return mapReverseU(l, Curry.__1(f));
}

function forEachU(_xs, f) {
  while(true) {
    var xs = _xs;
    if (xs) {
      f(xs[0]);
      _xs = xs[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function forEach(xs, f) {
  return forEachU(xs, Curry.__1(f));
}

function forEachWithIndexU(l, f) {
  var _xs = l;
  var _i = 0;
  var f$1 = f;
  while(true) {
    var i = _i;
    var xs = _xs;
    if (xs) {
      f$1(i, xs[0]);
      _i = i + 1 | 0;
      _xs = xs[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function forEachWithIndex(l, f) {
  return forEachWithIndexU(l, Curry.__2(f));
}

function reduceU(_l, _accu, f) {
  while(true) {
    var accu = _accu;
    var l = _l;
    if (l) {
      _accu = f(accu, l[0]);
      _l = l[1];
      continue ;
    } else {
      return accu;
    }
  };
}

function reduce(l, accu, f) {
  return reduceU(l, accu, Curry.__2(f));
}

function reduceReverseUnsafeU(l, accu, f) {
  if (l) {
    return f(reduceReverseUnsafeU(l[1], accu, f), l[0]);
  } else {
    return accu;
  }
}

function reduceReverseU(l, acc, f) {
  var len = length(l);
  if (len < 1000) {
    return reduceReverseUnsafeU(l, acc, f);
  } else {
    return Belt_Array.reduceReverseU(toArray(l), acc, f);
  }
}

function reduceReverse(l, accu, f) {
  return reduceReverseU(l, accu, Curry.__2(f));
}

function mapReverse2U(l1, l2, f) {
  var _l1 = l1;
  var _l2 = l2;
  var _accu = /* [] */0;
  var f$1 = f;
  while(true) {
    var accu = _accu;
    var l2$1 = _l2;
    var l1$1 = _l1;
    if (l1$1 && l2$1) {
      _accu = /* :: */[
        f$1(l1$1[0], l2$1[0]),
        accu
      ];
      _l2 = l2$1[1];
      _l1 = l1$1[1];
      continue ;
    } else {
      return accu;
    }
  };
}

function mapReverse2(l1, l2, f) {
  return mapReverse2U(l1, l2, Curry.__2(f));
}

function forEach2U(_l1, _l2, f) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1 && l2) {
      f(l1[0], l2[0]);
      _l2 = l2[1];
      _l1 = l1[1];
      continue ;
    } else {
      return /* () */0;
    }
  };
}

function forEach2(l1, l2, f) {
  return forEach2U(l1, l2, Curry.__2(f));
}

function reduce2U(_l1, _l2, _accu, f) {
  while(true) {
    var accu = _accu;
    var l2 = _l2;
    var l1 = _l1;
    if (l1 && l2) {
      _accu = f(accu, l1[0], l2[0]);
      _l2 = l2[1];
      _l1 = l1[1];
      continue ;
    } else {
      return accu;
    }
  };
}

function reduce2(l1, l2, acc, f) {
  return reduce2U(l1, l2, acc, Curry.__3(f));
}

function reduceReverse2UnsafeU(l1, l2, accu, f) {
  if (l1 && l2) {
    return f(reduceReverse2UnsafeU(l1[1], l2[1], accu, f), l1[0], l2[0]);
  } else {
    return accu;
  }
}

function reduceReverse2U(l1, l2, acc, f) {
  var len = length(l1);
  if (len < 1000) {
    return reduceReverse2UnsafeU(l1, l2, acc, f);
  } else {
    return Belt_Array.reduceReverse2U(toArray(l1), toArray(l2), acc, f);
  }
}

function reduceReverse2(l1, l2, acc, f) {
  return reduceReverse2U(l1, l2, acc, Curry.__3(f));
}

function everyU(_xs, p) {
  while(true) {
    var xs = _xs;
    if (xs) {
      if (p(xs[0])) {
        _xs = xs[1];
        continue ;
      } else {
        return false;
      }
    } else {
      return true;
    }
  };
}

function every(xs, p) {
  return everyU(xs, Curry.__1(p));
}

function someU(_xs, p) {
  while(true) {
    var xs = _xs;
    if (xs) {
      if (p(xs[0])) {
        return true;
      } else {
        _xs = xs[1];
        continue ;
      }
    } else {
      return false;
    }
  };
}

function some(xs, p) {
  return someU(xs, Curry.__1(p));
}

function every2U(_l1, _l2, p) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1 && l2) {
      if (p(l1[0], l2[0])) {
        _l2 = l2[1];
        _l1 = l1[1];
        continue ;
      } else {
        return false;
      }
    } else {
      return true;
    }
  };
}

function every2(l1, l2, p) {
  return every2U(l1, l2, Curry.__2(p));
}

function cmpByLength(_l1, _l2) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1) {
      if (l2) {
        _l2 = l2[1];
        _l1 = l1[1];
        continue ;
      } else {
        return 1;
      }
    } else if (l2) {
      return -1;
    } else {
      return 0;
    }
  };
}

function cmpU(_l1, _l2, p) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1) {
      if (l2) {
        var c = p(l1[0], l2[0]);
        if (c === 0) {
          _l2 = l2[1];
          _l1 = l1[1];
          continue ;
        } else {
          return c;
        }
      } else {
        return 1;
      }
    } else if (l2) {
      return -1;
    } else {
      return 0;
    }
  };
}

function cmp(l1, l2, f) {
  return cmpU(l1, l2, Curry.__2(f));
}

function eqU(_l1, _l2, p) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1) {
      if (l2 && p(l1[0], l2[0])) {
        _l2 = l2[1];
        _l1 = l1[1];
        continue ;
      } else {
        return false;
      }
    } else if (l2) {
      return false;
    } else {
      return true;
    }
  };
}

function eq(l1, l2, f) {
  return eqU(l1, l2, Curry.__2(f));
}

function some2U(_l1, _l2, p) {
  while(true) {
    var l2 = _l2;
    var l1 = _l1;
    if (l1 && l2) {
      if (p(l1[0], l2[0])) {
        return true;
      } else {
        _l2 = l2[1];
        _l1 = l1[1];
        continue ;
      }
    } else {
      return false;
    }
  };
}

function some2(l1, l2, p) {
  return some2U(l1, l2, Curry.__2(p));
}

function hasU(_xs, x, eq) {
  while(true) {
    var xs = _xs;
    if (xs) {
      if (eq(xs[0], x)) {
        return true;
      } else {
        _xs = xs[1];
        continue ;
      }
    } else {
      return false;
    }
  };
}

function has(xs, x, eq) {
  return hasU(xs, x, Curry.__2(eq));
}

function getAssocU(_xs, x, eq) {
  while(true) {
    var xs = _xs;
    if (xs) {
      var match = xs[0];
      if (eq(match[0], x)) {
        return /* Some */[match[1]];
      } else {
        _xs = xs[1];
        continue ;
      }
    } else {
      return /* None */0;
    }
  };
}

function getAssoc(xs, x, eq) {
  return getAssocU(xs, x, Curry.__2(eq));
}

function hasAssocU(_xs, x, eq) {
  while(true) {
    var xs = _xs;
    if (xs) {
      if (eq(xs[0][0], x)) {
        return true;
      } else {
        _xs = xs[1];
        continue ;
      }
    } else {
      return false;
    }
  };
}

function hasAssoc(xs, x, eq) {
  return hasAssocU(xs, x, Curry.__2(eq));
}

function removeAssocU(xs, x, eq) {
  if (xs) {
    var l = xs[1];
    var pair = xs[0];
    if (eq(pair[0], x)) {
      return l;
    } else {
      var cell = /* :: */[
        pair,
        /* [] */0
      ];
      var removed = removeAssocAuxWithMap(l, x, cell, eq);
      if (removed) {
        return cell;
      } else {
        return xs;
      }
    }
  } else {
    return /* [] */0;
  }
}

function removeAssoc(xs, x, eq) {
  return removeAssocU(xs, x, Curry.__2(eq));
}

function setAssocU(xs, x, k, eq) {
  if (xs) {
    var l = xs[1];
    var pair = xs[0];
    if (eq(pair[0], x)) {
      return /* :: */[
              /* tuple */[
                x,
                k
              ],
              l
            ];
    } else {
      var cell = /* :: */[
        pair,
        /* [] */0
      ];
      var replaced = setAssocAuxWithMap(l, x, k, cell, eq);
      if (replaced) {
        return cell;
      } else {
        return /* :: */[
                /* tuple */[
                  x,
                  k
                ],
                xs
              ];
      }
    }
  } else {
    return /* :: */[
            /* tuple */[
              x,
              k
            ],
            /* [] */0
          ];
  }
}

function setAssoc(xs, x, k, eq) {
  return setAssocU(xs, x, k, Curry.__2(eq));
}

function sortU(xs, cmp) {
  var arr = toArray(xs);
  Belt_SortArray.stableSortInPlaceByU(arr, cmp);
  return fromArray(arr);
}

function sort(xs, cmp) {
  return sortU(xs, Curry.__2(cmp));
}

function getByU(_xs, p) {
  while(true) {
    var xs = _xs;
    if (xs) {
      var x = xs[0];
      if (p(x)) {
        return /* Some */[x];
      } else {
        _xs = xs[1];
        continue ;
      }
    } else {
      return /* None */0;
    }
  };
}

function getBy(xs, p) {
  return getByU(xs, Curry.__1(p));
}

function keepU(_xs, p) {
  while(true) {
    var xs = _xs;
    if (xs) {
      var t = xs[1];
      var h = xs[0];
      if (p(h)) {
        var cell = /* :: */[
          h,
          /* [] */0
        ];
        copyAuxWitFilter(p, t, cell);
        return cell;
      } else {
        _xs = t;
        continue ;
      }
    } else {
      return /* [] */0;
    }
  };
}

function keep(xs, p) {
  return keepU(xs, Curry.__1(p));
}

function keepMapU(_xs, p) {
  while(true) {
    var xs = _xs;
    if (xs) {
      var t = xs[1];
      var match = p(xs[0]);
      if (match) {
        var cell = /* :: */[
          match[0],
          /* [] */0
        ];
        copyAuxWitFilterMap(p, t, cell);
        return cell;
      } else {
        _xs = t;
        continue ;
      }
    } else {
      return /* [] */0;
    }
  };
}

function keepMap(xs, p) {
  return keepMapU(xs, Curry.__1(p));
}

function partitionU(l, p) {
  if (l) {
    var h = l[0];
    var nextX = /* :: */[
      h,
      /* [] */0
    ];
    var nextY = /* :: */[
      h,
      /* [] */0
    ];
    var b = p(h);
    partitionAux(p, l[1], nextX, nextY);
    if (b) {
      return /* tuple */[
              nextX,
              nextY[1]
            ];
    } else {
      return /* tuple */[
              nextX[1],
              nextY
            ];
    }
  } else {
    return /* tuple */[
            /* [] */0,
            /* [] */0
          ];
  }
}

function partition(l, p) {
  return partitionU(l, Curry.__1(p));
}

function unzip(xs) {
  if (xs) {
    var match = xs[0];
    var cellX = /* :: */[
      match[0],
      /* [] */0
    ];
    var cellY = /* :: */[
      match[1],
      /* [] */0
    ];
    splitAux(xs[1], cellX, cellY);
    return /* tuple */[
            cellX,
            cellY
          ];
  } else {
    return /* tuple */[
            /* [] */0,
            /* [] */0
          ];
  }
}

function zip(l1, l2) {
  if (l1 && l2) {
    var cell = /* :: */[
      /* tuple */[
        l1[0],
        l2[0]
      ],
      /* [] */0
    ];
    zipAux(l1[1], l2[1], cell);
    return cell;
  } else {
    return /* [] */0;
  }
}

var size = length;

exports.length = length;
exports.size = size;
exports.head = head;
exports.headExn = headExn;
exports.tail = tail;
exports.tailExn = tailExn;
exports.add = add;
exports.get = get;
exports.getExn = getExn;
exports.make = make;
exports.makeByU = makeByU;
exports.makeBy = makeBy;
exports.shuffle = shuffle;
exports.drop = drop;
exports.take = take;
exports.splitAt = splitAt;
exports.concat = concat;
exports.concatMany = concatMany;
exports.reverseConcat = reverseConcat;
exports.flatten = flatten;
exports.mapU = mapU;
exports.map = map;
exports.zip = zip;
exports.zipByU = zipByU;
exports.zipBy = zipBy;
exports.mapWithIndexU = mapWithIndexU;
exports.mapWithIndex = mapWithIndex;
exports.fromArray = fromArray;
exports.toArray = toArray;
exports.reverse = reverse;
exports.mapReverseU = mapReverseU;
exports.mapReverse = mapReverse;
exports.forEachU = forEachU;
exports.forEach = forEach;
exports.forEachWithIndexU = forEachWithIndexU;
exports.forEachWithIndex = forEachWithIndex;
exports.reduceU = reduceU;
exports.reduce = reduce;
exports.reduceReverseU = reduceReverseU;
exports.reduceReverse = reduceReverse;
exports.mapReverse2U = mapReverse2U;
exports.mapReverse2 = mapReverse2;
exports.forEach2U = forEach2U;
exports.forEach2 = forEach2;
exports.reduce2U = reduce2U;
exports.reduce2 = reduce2;
exports.reduceReverse2U = reduceReverse2U;
exports.reduceReverse2 = reduceReverse2;
exports.everyU = everyU;
exports.every = every;
exports.someU = someU;
exports.some = some;
exports.every2U = every2U;
exports.every2 = every2;
exports.some2U = some2U;
exports.some2 = some2;
exports.cmpByLength = cmpByLength;
exports.cmpU = cmpU;
exports.cmp = cmp;
exports.eqU = eqU;
exports.eq = eq;
exports.hasU = hasU;
exports.has = has;
exports.getByU = getByU;
exports.getBy = getBy;
exports.keepU = keepU;
exports.keep = keep;
exports.keepMapU = keepMapU;
exports.keepMap = keepMap;
exports.partitionU = partitionU;
exports.partition = partition;
exports.unzip = unzip;
exports.getAssocU = getAssocU;
exports.getAssoc = getAssoc;
exports.hasAssocU = hasAssocU;
exports.hasAssoc = hasAssoc;
exports.removeAssocU = removeAssocU;
exports.removeAssoc = removeAssoc;
exports.setAssocU = setAssocU;
exports.setAssoc = setAssoc;
exports.sortU = sortU;
exports.sort = sort;
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
  return fromList(Belt_List.fromArray(str.split("/")));
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
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9ub2RlX21vZHVsZXMvYnMtcGxhdGZvcm0vbGliL2pzL2JlbHRfTGlzdC5qcyIsIndlYnBhY2s6Ly8vLi9zcmMvd2ViLWNsaWVudC9Sb3V0ZS5qcyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiOzs7Ozs7Ozs7O0FBQUE7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsU0FBUztBQUNUO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsZ0NBQWdDLFFBQVE7QUFDeEM7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsT0FBTztBQUNQO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBOzs7Ozs7Ozs7Ozs7O0FDajdDQTtBQUNBOztBQUVBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsV0FBVztBQUNYO0FBQ0E7QUFDQSxTQUFTO0FBQ1Q7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLE9BQU87QUFDUDtBQUNBO0FBQ0E7O0FBRUEsR0FBRztBQUNIO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EiLCJmaWxlIjoibWFpbi40MmQ1MDVjMjAyNDE1NzBlYTM1MS5ob3QtdXBkYXRlLmpzIiwic291cmNlc0NvbnRlbnQiOlsiJ3VzZSBzdHJpY3QnO1xuXG52YXIgQ3VycnkgPSByZXF1aXJlKFwiLi9jdXJyeS5qc1wiKTtcbnZhciBCZWx0X0FycmF5ID0gcmVxdWlyZShcIi4vYmVsdF9BcnJheS5qc1wiKTtcbnZhciBCZWx0X1NvcnRBcnJheSA9IHJlcXVpcmUoXCIuL2JlbHRfU29ydEFycmF5LmpzXCIpO1xuXG5mdW5jdGlvbiBoZWFkKHgpIHtcbiAgaWYgKHgpIHtcbiAgICByZXR1cm4gLyogU29tZSAqL1t4WzBdXTtcbiAgfSBlbHNlIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH1cbn1cblxuZnVuY3Rpb24gaGVhZEV4bih4KSB7XG4gIGlmICh4KSB7XG4gICAgcmV0dXJuIHhbMF07XG4gIH0gZWxzZSB7XG4gICAgdGhyb3cgbmV3IEVycm9yKFwiaGVhZEV4blwiKTtcbiAgfVxufVxuXG5mdW5jdGlvbiB0YWlsKHgpIHtcbiAgaWYgKHgpIHtcbiAgICByZXR1cm4gLyogU29tZSAqL1t4WzFdXTtcbiAgfSBlbHNlIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH1cbn1cblxuZnVuY3Rpb24gdGFpbEV4bih4KSB7XG4gIGlmICh4KSB7XG4gICAgcmV0dXJuIHhbMV07XG4gIH0gZWxzZSB7XG4gICAgdGhyb3cgbmV3IEVycm9yKFwidGFpbEV4blwiKTtcbiAgfVxufVxuXG5mdW5jdGlvbiBhZGQoeHMsIHgpIHtcbiAgcmV0dXJuIC8qIDo6ICovW1xuICAgICAgICAgIHgsXG4gICAgICAgICAgeHNcbiAgICAgICAgXTtcbn1cblxuZnVuY3Rpb24gZ2V0KHgsIG4pIHtcbiAgaWYgKG4gPCAwKSB7XG4gICAgcmV0dXJuIC8qIE5vbmUgKi8wO1xuICB9IGVsc2Uge1xuICAgIHZhciBfeCA9IHg7XG4gICAgdmFyIF9uID0gbjtcbiAgICB3aGlsZSh0cnVlKSB7XG4gICAgICB2YXIgbiQxID0gX247XG4gICAgICB2YXIgeCQxID0gX3g7XG4gICAgICBpZiAoeCQxKSB7XG4gICAgICAgIGlmIChuJDEgPT09IDApIHtcbiAgICAgICAgICByZXR1cm4gLyogU29tZSAqL1t4JDFbMF1dO1xuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIF9uID0gbiQxIC0gMSB8IDA7XG4gICAgICAgICAgX3ggPSB4JDFbMV07XG4gICAgICAgICAgY29udGludWUgO1xuICAgICAgICB9XG4gICAgICB9IGVsc2Uge1xuICAgICAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gICAgICB9XG4gICAgfTtcbiAgfVxufVxuXG5mdW5jdGlvbiBnZXRFeG4oeCwgbikge1xuICBpZiAobiA8IDApIHtcbiAgICB0aHJvdyBuZXcgRXJyb3IoXCJnZXRFeG5cIik7XG4gIH0gZWxzZSB7XG4gICAgdmFyIF94ID0geDtcbiAgICB2YXIgX24gPSBuO1xuICAgIHdoaWxlKHRydWUpIHtcbiAgICAgIHZhciBuJDEgPSBfbjtcbiAgICAgIHZhciB4JDEgPSBfeDtcbiAgICAgIGlmICh4JDEpIHtcbiAgICAgICAgaWYgKG4kMSA9PT0gMCkge1xuICAgICAgICAgIHJldHVybiB4JDFbMF07XG4gICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgX24gPSBuJDEgLSAxIHwgMDtcbiAgICAgICAgICBfeCA9IHgkMVsxXTtcbiAgICAgICAgICBjb250aW51ZSA7XG4gICAgICAgIH1cbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHRocm93IG5ldyBFcnJvcihcImdldEV4blwiKTtcbiAgICAgIH1cbiAgICB9O1xuICB9XG59XG5cbmZ1bmN0aW9uIHBhcnRpdGlvbkF1eChwLCBfY2VsbCwgX3ByZWNYLCBfcHJlY1kpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBwcmVjWSA9IF9wcmVjWTtcbiAgICB2YXIgcHJlY1ggPSBfcHJlY1g7XG4gICAgdmFyIGNlbGwgPSBfY2VsbDtcbiAgICBpZiAoY2VsbCkge1xuICAgICAgdmFyIHQgPSBjZWxsWzFdO1xuICAgICAgdmFyIGggPSBjZWxsWzBdO1xuICAgICAgdmFyIG5leHQgPSAvKiA6OiAqL1tcbiAgICAgICAgaCxcbiAgICAgICAgLyogW10gKi8wXG4gICAgICBdO1xuICAgICAgaWYgKHAoaCkpIHtcbiAgICAgICAgcHJlY1hbMV0gPSBuZXh0O1xuICAgICAgICBfcHJlY1ggPSBuZXh0O1xuICAgICAgICBfY2VsbCA9IHQ7XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHByZWNZWzFdID0gbmV4dDtcbiAgICAgICAgX3ByZWNZID0gbmV4dDtcbiAgICAgICAgX2NlbGwgPSB0O1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBzcGxpdEF1eChfY2VsbCwgX3ByZWNYLCBfcHJlY1kpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBwcmVjWSA9IF9wcmVjWTtcbiAgICB2YXIgcHJlY1ggPSBfcHJlY1g7XG4gICAgdmFyIGNlbGwgPSBfY2VsbDtcbiAgICBpZiAoY2VsbCkge1xuICAgICAgdmFyIG1hdGNoID0gY2VsbFswXTtcbiAgICAgIHZhciBuZXh0QSA9IC8qIDo6ICovW1xuICAgICAgICBtYXRjaFswXSxcbiAgICAgICAgLyogW10gKi8wXG4gICAgICBdO1xuICAgICAgdmFyIG5leHRCID0gLyogOjogKi9bXG4gICAgICAgIG1hdGNoWzFdLFxuICAgICAgICAvKiBbXSAqLzBcbiAgICAgIF07XG4gICAgICBwcmVjWFsxXSA9IG5leHRBO1xuICAgICAgcHJlY1lbMV0gPSBuZXh0QjtcbiAgICAgIF9wcmVjWSA9IG5leHRCO1xuICAgICAgX3ByZWNYID0gbmV4dEE7XG4gICAgICBfY2VsbCA9IGNlbGxbMV07XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBjb3B5QXV4Q29udChfY2VsbFgsIF9wcmVjKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcHJlYyA9IF9wcmVjO1xuICAgIHZhciBjZWxsWCA9IF9jZWxsWDtcbiAgICBpZiAoY2VsbFgpIHtcbiAgICAgIHZhciBuZXh0ID0gLyogOjogKi9bXG4gICAgICAgIGNlbGxYWzBdLFxuICAgICAgICAvKiBbXSAqLzBcbiAgICAgIF07XG4gICAgICBwcmVjWzFdID0gbmV4dDtcbiAgICAgIF9wcmVjID0gbmV4dDtcbiAgICAgIF9jZWxsWCA9IGNlbGxYWzFdO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gcHJlYztcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGNvcHlBdXhXaXRGaWx0ZXIoZiwgX2NlbGxYLCBfcHJlYykge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHByZWMgPSBfcHJlYztcbiAgICB2YXIgY2VsbFggPSBfY2VsbFg7XG4gICAgaWYgKGNlbGxYKSB7XG4gICAgICB2YXIgdCA9IGNlbGxYWzFdO1xuICAgICAgdmFyIGggPSBjZWxsWFswXTtcbiAgICAgIGlmIChmKGgpKSB7XG4gICAgICAgIHZhciBuZXh0ID0gLyogOjogKi9bXG4gICAgICAgICAgaCxcbiAgICAgICAgICAvKiBbXSAqLzBcbiAgICAgICAgXTtcbiAgICAgICAgcHJlY1sxXSA9IG5leHQ7XG4gICAgICAgIF9wcmVjID0gbmV4dDtcbiAgICAgICAgX2NlbGxYID0gdDtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgX2NlbGxYID0gdDtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogKCkgKi8wO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gY29weUF1eFdpdEZpbHRlck1hcChmLCBfY2VsbFgsIF9wcmVjKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcHJlYyA9IF9wcmVjO1xuICAgIHZhciBjZWxsWCA9IF9jZWxsWDtcbiAgICBpZiAoY2VsbFgpIHtcbiAgICAgIHZhciB0ID0gY2VsbFhbMV07XG4gICAgICB2YXIgbWF0Y2ggPSBmKGNlbGxYWzBdKTtcbiAgICAgIGlmIChtYXRjaCkge1xuICAgICAgICB2YXIgbmV4dCA9IC8qIDo6ICovW1xuICAgICAgICAgIG1hdGNoWzBdLFxuICAgICAgICAgIC8qIFtdICovMFxuICAgICAgICBdO1xuICAgICAgICBwcmVjWzFdID0gbmV4dDtcbiAgICAgICAgX3ByZWMgPSBuZXh0O1xuICAgICAgICBfY2VsbFggPSB0O1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfY2VsbFggPSB0O1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiByZW1vdmVBc3NvY0F1eFdpdGhNYXAoX2NlbGxYLCB4LCBfcHJlYywgZikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHByZWMgPSBfcHJlYztcbiAgICB2YXIgY2VsbFggPSBfY2VsbFg7XG4gICAgaWYgKGNlbGxYKSB7XG4gICAgICB2YXIgdCA9IGNlbGxYWzFdO1xuICAgICAgdmFyIGggPSBjZWxsWFswXTtcbiAgICAgIGlmIChmKGhbMF0sIHgpKSB7XG4gICAgICAgIHByZWNbMV0gPSB0O1xuICAgICAgICByZXR1cm4gdHJ1ZTtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHZhciBuZXh0ID0gLyogOjogKi9bXG4gICAgICAgICAgaCxcbiAgICAgICAgICAvKiBbXSAqLzBcbiAgICAgICAgXTtcbiAgICAgICAgcHJlY1sxXSA9IG5leHQ7XG4gICAgICAgIF9wcmVjID0gbmV4dDtcbiAgICAgICAgX2NlbGxYID0gdDtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gZmFsc2U7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBzZXRBc3NvY0F1eFdpdGhNYXAoX2NlbGxYLCB4LCBrLCBfcHJlYywgZXEpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBwcmVjID0gX3ByZWM7XG4gICAgdmFyIGNlbGxYID0gX2NlbGxYO1xuICAgIGlmIChjZWxsWCkge1xuICAgICAgdmFyIHQgPSBjZWxsWFsxXTtcbiAgICAgIHZhciBoID0gY2VsbFhbMF07XG4gICAgICBpZiAoZXEoaFswXSwgeCkpIHtcbiAgICAgICAgcHJlY1sxXSA9IC8qIDo6ICovW1xuICAgICAgICAgIC8qIHR1cGxlICovW1xuICAgICAgICAgICAgeCxcbiAgICAgICAgICAgIGtcbiAgICAgICAgICBdLFxuICAgICAgICAgIHRcbiAgICAgICAgXTtcbiAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICB2YXIgbmV4dCA9IC8qIDo6ICovW1xuICAgICAgICAgIGgsXG4gICAgICAgICAgLyogW10gKi8wXG4gICAgICAgIF07XG4gICAgICAgIHByZWNbMV0gPSBuZXh0O1xuICAgICAgICBfcHJlYyA9IG5leHQ7XG4gICAgICAgIF9jZWxsWCA9IHQ7XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gY29weUF1eFdpdGhNYXAoX2NlbGxYLCBfcHJlYywgZikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHByZWMgPSBfcHJlYztcbiAgICB2YXIgY2VsbFggPSBfY2VsbFg7XG4gICAgaWYgKGNlbGxYKSB7XG4gICAgICB2YXIgbmV4dCA9IC8qIDo6ICovW1xuICAgICAgICBmKGNlbGxYWzBdKSxcbiAgICAgICAgLyogW10gKi8wXG4gICAgICBdO1xuICAgICAgcHJlY1sxXSA9IG5leHQ7XG4gICAgICBfcHJlYyA9IG5leHQ7XG4gICAgICBfY2VsbFggPSBjZWxsWFsxXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qICgpICovMDtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIHppcEF1eChfY2VsbFgsIF9jZWxsWSwgX3ByZWMpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBwcmVjID0gX3ByZWM7XG4gICAgdmFyIGNlbGxZID0gX2NlbGxZO1xuICAgIHZhciBjZWxsWCA9IF9jZWxsWDtcbiAgICBpZiAoY2VsbFggJiYgY2VsbFkpIHtcbiAgICAgIHZhciBuZXh0ID0gLyogOjogKi9bXG4gICAgICAgIC8qIHR1cGxlICovW1xuICAgICAgICAgIGNlbGxYWzBdLFxuICAgICAgICAgIGNlbGxZWzBdXG4gICAgICAgIF0sXG4gICAgICAgIC8qIFtdICovMFxuICAgICAgXTtcbiAgICAgIHByZWNbMV0gPSBuZXh0O1xuICAgICAgX3ByZWMgPSBuZXh0O1xuICAgICAgX2NlbGxZID0gY2VsbFlbMV07XG4gICAgICBfY2VsbFggPSBjZWxsWFsxXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qICgpICovMDtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGNvcHlBdXhXaXRoTWFwMihmLCBfY2VsbFgsIF9jZWxsWSwgX3ByZWMpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBwcmVjID0gX3ByZWM7XG4gICAgdmFyIGNlbGxZID0gX2NlbGxZO1xuICAgIHZhciBjZWxsWCA9IF9jZWxsWDtcbiAgICBpZiAoY2VsbFggJiYgY2VsbFkpIHtcbiAgICAgIHZhciBuZXh0ID0gLyogOjogKi9bXG4gICAgICAgIGYoY2VsbFhbMF0sIGNlbGxZWzBdKSxcbiAgICAgICAgLyogW10gKi8wXG4gICAgICBdO1xuICAgICAgcHJlY1sxXSA9IG5leHQ7XG4gICAgICBfcHJlYyA9IG5leHQ7XG4gICAgICBfY2VsbFkgPSBjZWxsWVsxXTtcbiAgICAgIF9jZWxsWCA9IGNlbGxYWzFdO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogKCkgKi8wO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gY29weUF1eFdpdGhNYXBJKGYsIF9pLCBfY2VsbFgsIF9wcmVjKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcHJlYyA9IF9wcmVjO1xuICAgIHZhciBjZWxsWCA9IF9jZWxsWDtcbiAgICB2YXIgaSA9IF9pO1xuICAgIGlmIChjZWxsWCkge1xuICAgICAgdmFyIG5leHQgPSAvKiA6OiAqL1tcbiAgICAgICAgZihpLCBjZWxsWFswXSksXG4gICAgICAgIC8qIFtdICovMFxuICAgICAgXTtcbiAgICAgIHByZWNbMV0gPSBuZXh0O1xuICAgICAgX3ByZWMgPSBuZXh0O1xuICAgICAgX2NlbGxYID0gY2VsbFhbMV07XG4gICAgICBfaSA9IGkgKyAxIHwgMDtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qICgpICovMDtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIHRha2VBdXgoX24sIF9jZWxsLCBfcHJlYykge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHByZWMgPSBfcHJlYztcbiAgICB2YXIgY2VsbCA9IF9jZWxsO1xuICAgIHZhciBuID0gX247XG4gICAgaWYgKG4gPT09IDApIHtcbiAgICAgIHJldHVybiB0cnVlO1xuICAgIH0gZWxzZSBpZiAoY2VsbCkge1xuICAgICAgdmFyIGNlbGwkMSA9IC8qIDo6ICovW1xuICAgICAgICBjZWxsWzBdLFxuICAgICAgICAvKiBbXSAqLzBcbiAgICAgIF07XG4gICAgICBwcmVjWzFdID0gY2VsbCQxO1xuICAgICAgX3ByZWMgPSBjZWxsJDE7XG4gICAgICBfY2VsbCA9IGNlbGxbMV07XG4gICAgICBfbiA9IG4gLSAxIHwgMDtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gc3BsaXRBdEF1eChfbiwgX2NlbGwsIF9wcmVjKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcHJlYyA9IF9wcmVjO1xuICAgIHZhciBjZWxsID0gX2NlbGw7XG4gICAgdmFyIG4gPSBfbjtcbiAgICBpZiAobiA9PT0gMCkge1xuICAgICAgcmV0dXJuIC8qIFNvbWUgKi9bY2VsbF07XG4gICAgfSBlbHNlIGlmIChjZWxsKSB7XG4gICAgICB2YXIgY2VsbCQxID0gLyogOjogKi9bXG4gICAgICAgIGNlbGxbMF0sXG4gICAgICAgIC8qIFtdICovMFxuICAgICAgXTtcbiAgICAgIHByZWNbMV0gPSBjZWxsJDE7XG4gICAgICBfcHJlYyA9IGNlbGwkMTtcbiAgICAgIF9jZWxsID0gY2VsbFsxXTtcbiAgICAgIF9uID0gbiAtIDEgfCAwO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiB0YWtlKGxzdCwgbikge1xuICBpZiAobiA8IDApIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH0gZWxzZSBpZiAobiA9PT0gMCkge1xuICAgIHJldHVybiAvKiBTb21lICovWy8qIFtdICovMF07XG4gIH0gZWxzZSBpZiAobHN0KSB7XG4gICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgIGxzdFswXSxcbiAgICAgIC8qIFtdICovMFxuICAgIF07XG4gICAgdmFyIGhhcyA9IHRha2VBdXgobiAtIDEgfCAwLCBsc3RbMV0sIGNlbGwpO1xuICAgIGlmIChoYXMpIHtcbiAgICAgIHJldHVybiAvKiBTb21lICovW2NlbGxdO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gICAgfVxuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBOb25lICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiBkcm9wKGxzdCwgbikge1xuICBpZiAobiA8IDApIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH0gZWxzZSB7XG4gICAgdmFyIF9sID0gbHN0O1xuICAgIHZhciBfbiA9IG47XG4gICAgd2hpbGUodHJ1ZSkge1xuICAgICAgdmFyIG4kMSA9IF9uO1xuICAgICAgdmFyIGwgPSBfbDtcbiAgICAgIGlmIChuJDEgPT09IDApIHtcbiAgICAgICAgcmV0dXJuIC8qIFNvbWUgKi9bbF07XG4gICAgICB9IGVsc2UgaWYgKGwpIHtcbiAgICAgICAgX24gPSBuJDEgLSAxIHwgMDtcbiAgICAgICAgX2wgPSBsWzFdO1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gICAgICB9XG4gICAgfTtcbiAgfVxufVxuXG5mdW5jdGlvbiBzcGxpdEF0KGxzdCwgbikge1xuICBpZiAobiA8IDApIHtcbiAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gIH0gZWxzZSBpZiAobiA9PT0gMCkge1xuICAgIHJldHVybiAvKiBTb21lICovWy8qIHR1cGxlICovW1xuICAgICAgICAgICAgICAvKiBbXSAqLzAsXG4gICAgICAgICAgICAgIGxzdFxuICAgICAgICAgICAgXV07XG4gIH0gZWxzZSBpZiAobHN0KSB7XG4gICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgIGxzdFswXSxcbiAgICAgIC8qIFtdICovMFxuICAgIF07XG4gICAgdmFyIHJlc3QgPSBzcGxpdEF0QXV4KG4gLSAxIHwgMCwgbHN0WzFdLCBjZWxsKTtcbiAgICBpZiAocmVzdCkge1xuICAgICAgcmV0dXJuIC8qIFNvbWUgKi9bLyogdHVwbGUgKi9bXG4gICAgICAgICAgICAgICAgY2VsbCxcbiAgICAgICAgICAgICAgICByZXN0WzBdXG4gICAgICAgICAgICAgIF1dO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gICAgfVxuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBOb25lICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiBjb25jYXQoeHMsIHlzKSB7XG4gIGlmICh4cykge1xuICAgIHZhciBjZWxsID0gLyogOjogKi9bXG4gICAgICB4c1swXSxcbiAgICAgIC8qIFtdICovMFxuICAgIF07XG4gICAgY29weUF1eENvbnQoeHNbMV0sIGNlbGwpWzFdID0geXM7XG4gICAgcmV0dXJuIGNlbGw7XG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIHlzO1xuICB9XG59XG5cbmZ1bmN0aW9uIG1hcFUoeHMsIGYpIHtcbiAgaWYgKHhzKSB7XG4gICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgIGYoeHNbMF0pLFxuICAgICAgLyogW10gKi8wXG4gICAgXTtcbiAgICBjb3B5QXV4V2l0aE1hcCh4c1sxXSwgY2VsbCwgZik7XG4gICAgcmV0dXJuIGNlbGw7XG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIC8qIFtdICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiBtYXAoeHMsIGYpIHtcbiAgcmV0dXJuIG1hcFUoeHMsIEN1cnJ5Ll9fMShmKSk7XG59XG5cbmZ1bmN0aW9uIHppcEJ5VShsMSwgbDIsIGYpIHtcbiAgaWYgKGwxICYmIGwyKSB7XG4gICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgIGYobDFbMF0sIGwyWzBdKSxcbiAgICAgIC8qIFtdICovMFxuICAgIF07XG4gICAgY29weUF1eFdpdGhNYXAyKGYsIGwxWzFdLCBsMlsxXSwgY2VsbCk7XG4gICAgcmV0dXJuIGNlbGw7XG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIC8qIFtdICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiB6aXBCeShsMSwgbDIsIGYpIHtcbiAgcmV0dXJuIHppcEJ5VShsMSwgbDIsIEN1cnJ5Ll9fMihmKSk7XG59XG5cbmZ1bmN0aW9uIG1hcFdpdGhJbmRleFUoeHMsIGYpIHtcbiAgaWYgKHhzKSB7XG4gICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgIGYoMCwgeHNbMF0pLFxuICAgICAgLyogW10gKi8wXG4gICAgXTtcbiAgICBjb3B5QXV4V2l0aE1hcEkoZiwgMSwgeHNbMV0sIGNlbGwpO1xuICAgIHJldHVybiBjZWxsO1xuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBbXSAqLzA7XG4gIH1cbn1cblxuZnVuY3Rpb24gbWFwV2l0aEluZGV4KHhzLCBmKSB7XG4gIHJldHVybiBtYXBXaXRoSW5kZXhVKHhzLCBDdXJyeS5fXzIoZikpO1xufVxuXG5mdW5jdGlvbiBtYWtlQnlVKG4sIGYpIHtcbiAgaWYgKG4gPD0gMCkge1xuICAgIHJldHVybiAvKiBbXSAqLzA7XG4gIH0gZWxzZSB7XG4gICAgdmFyIGhlYWRYID0gLyogOjogKi9bXG4gICAgICBmKDApLFxuICAgICAgLyogW10gKi8wXG4gICAgXTtcbiAgICB2YXIgY3VyID0gaGVhZFg7XG4gICAgdmFyIGkgPSAxO1xuICAgIHdoaWxlKGkgPCBuKSB7XG4gICAgICB2YXIgdiA9IC8qIDo6ICovW1xuICAgICAgICBmKGkpLFxuICAgICAgICAvKiBbXSAqLzBcbiAgICAgIF07XG4gICAgICBjdXJbMV0gPSB2O1xuICAgICAgY3VyID0gdjtcbiAgICAgIGkgPSBpICsgMSB8IDA7XG4gICAgfTtcbiAgICByZXR1cm4gaGVhZFg7XG4gIH1cbn1cblxuZnVuY3Rpb24gbWFrZUJ5KG4sIGYpIHtcbiAgcmV0dXJuIG1ha2VCeVUobiwgQ3VycnkuX18xKGYpKTtcbn1cblxuZnVuY3Rpb24gbWFrZShuLCB2KSB7XG4gIGlmIChuIDw9IDApIHtcbiAgICByZXR1cm4gLyogW10gKi8wO1xuICB9IGVsc2Uge1xuICAgIHZhciBoZWFkWCA9IC8qIDo6ICovW1xuICAgICAgdixcbiAgICAgIC8qIFtdICovMFxuICAgIF07XG4gICAgdmFyIGN1ciA9IGhlYWRYO1xuICAgIHZhciBpID0gMTtcbiAgICB3aGlsZShpIDwgbikge1xuICAgICAgdmFyIHYkMSA9IC8qIDo6ICovW1xuICAgICAgICB2LFxuICAgICAgICAvKiBbXSAqLzBcbiAgICAgIF07XG4gICAgICBjdXJbMV0gPSB2JDE7XG4gICAgICBjdXIgPSB2JDE7XG4gICAgICBpID0gaSArIDEgfCAwO1xuICAgIH07XG4gICAgcmV0dXJuIGhlYWRYO1xuICB9XG59XG5cbmZ1bmN0aW9uIGxlbmd0aCh4cykge1xuICB2YXIgX3ggPSB4cztcbiAgdmFyIF9hY2MgPSAwO1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGFjYyA9IF9hY2M7XG4gICAgdmFyIHggPSBfeDtcbiAgICBpZiAoeCkge1xuICAgICAgX2FjYyA9IGFjYyArIDEgfCAwO1xuICAgICAgX3ggPSB4WzFdO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gYWNjO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gZmlsbEF1eChhcnIsIF9pLCBfeCkge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHggPSBfeDtcbiAgICB2YXIgaSA9IF9pO1xuICAgIGlmICh4KSB7XG4gICAgICBhcnJbaV0gPSB4WzBdO1xuICAgICAgX3ggPSB4WzFdO1xuICAgICAgX2kgPSBpICsgMSB8IDA7XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBmcm9tQXJyYXkoYSkge1xuICB2YXIgYSQxID0gYTtcbiAgdmFyIF9pID0gYS5sZW5ndGggLSAxIHwgMDtcbiAgdmFyIF9yZXMgPSAvKiBbXSAqLzA7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgcmVzID0gX3JlcztcbiAgICB2YXIgaSA9IF9pO1xuICAgIGlmIChpIDwgMCkge1xuICAgICAgcmV0dXJuIHJlcztcbiAgICB9IGVsc2Uge1xuICAgICAgX3JlcyA9IC8qIDo6ICovW1xuICAgICAgICBhJDFbaV0sXG4gICAgICAgIHJlc1xuICAgICAgXTtcbiAgICAgIF9pID0gaSAtIDEgfCAwO1xuICAgICAgY29udGludWUgO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gdG9BcnJheSh4KSB7XG4gIHZhciBsZW4gPSBsZW5ndGgoeCk7XG4gIHZhciBhcnIgPSBuZXcgQXJyYXkobGVuKTtcbiAgZmlsbEF1eChhcnIsIDAsIHgpO1xuICByZXR1cm4gYXJyO1xufVxuXG5mdW5jdGlvbiBzaHVmZmxlKHhzKSB7XG4gIHZhciB2ID0gdG9BcnJheSh4cyk7XG4gIEJlbHRfQXJyYXkuc2h1ZmZsZUluUGxhY2Uodik7XG4gIHJldHVybiBmcm9tQXJyYXkodik7XG59XG5cbmZ1bmN0aW9uIHJldmVyc2VDb25jYXQoX2wxLCBfbDIpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBsMiA9IF9sMjtcbiAgICB2YXIgbDEgPSBfbDE7XG4gICAgaWYgKGwxKSB7XG4gICAgICBfbDIgPSAvKiA6OiAqL1tcbiAgICAgICAgbDFbMF0sXG4gICAgICAgIGwyXG4gICAgICBdO1xuICAgICAgX2wxID0gbDFbMV07XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiBsMjtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIHJldmVyc2UobCkge1xuICByZXR1cm4gcmV2ZXJzZUNvbmNhdChsLCAvKiBbXSAqLzApO1xufVxuXG5mdW5jdGlvbiBmbGF0dGVuQXV4KF9wcmVjLCBfeHMpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciB4cyA9IF94cztcbiAgICB2YXIgcHJlYyA9IF9wcmVjO1xuICAgIGlmICh4cykge1xuICAgICAgX3hzID0geHNbMV07XG4gICAgICBfcHJlYyA9IGNvcHlBdXhDb250KHhzWzBdLCBwcmVjKTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcHJlY1sxXSA9IC8qIFtdICovMDtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBmbGF0dGVuKF94cykge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHhzID0gX3hzO1xuICAgIGlmICh4cykge1xuICAgICAgdmFyIG1hdGNoID0geHNbMF07XG4gICAgICBpZiAobWF0Y2gpIHtcbiAgICAgICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgICAgICBtYXRjaFswXSxcbiAgICAgICAgICAvKiBbXSAqLzBcbiAgICAgICAgXTtcbiAgICAgICAgZmxhdHRlbkF1eChjb3B5QXV4Q29udChtYXRjaFsxXSwgY2VsbCksIHhzWzFdKTtcbiAgICAgICAgcmV0dXJuIGNlbGw7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfeHMgPSB4c1sxXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogW10gKi8wO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gY29uY2F0TWFueSh4cykge1xuICB2YXIgbGVuID0geHMubGVuZ3RoO1xuICBpZiAobGVuICE9PSAxKSB7XG4gICAgaWYgKGxlbiAhPT0gMCkge1xuICAgICAgdmFyIGxlbiQxID0geHMubGVuZ3RoO1xuICAgICAgdmFyIHYgPSB4c1tsZW4kMSAtIDEgfCAwXTtcbiAgICAgIGZvcih2YXIgaSA9IGxlbiQxIC0gMiB8IDA7IGkgPj0gMDsgLS1pKXtcbiAgICAgICAgdiA9IGNvbmNhdCh4c1tpXSwgdik7XG4gICAgICB9XG4gICAgICByZXR1cm4gdjtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qIFtdICovMDtcbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIHhzWzBdO1xuICB9XG59XG5cbmZ1bmN0aW9uIG1hcFJldmVyc2VVKGwsIGYpIHtcbiAgdmFyIGYkMSA9IGY7XG4gIHZhciBfYWNjdSA9IC8qIFtdICovMDtcbiAgdmFyIF94cyA9IGw7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgeHMgPSBfeHM7XG4gICAgdmFyIGFjY3UgPSBfYWNjdTtcbiAgICBpZiAoeHMpIHtcbiAgICAgIF94cyA9IHhzWzFdO1xuICAgICAgX2FjY3UgPSAvKiA6OiAqL1tcbiAgICAgICAgZiQxKHhzWzBdKSxcbiAgICAgICAgYWNjdVxuICAgICAgXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGFjY3U7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBtYXBSZXZlcnNlKGwsIGYpIHtcbiAgcmV0dXJuIG1hcFJldmVyc2VVKGwsIEN1cnJ5Ll9fMShmKSk7XG59XG5cbmZ1bmN0aW9uIGZvckVhY2hVKF94cywgZikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHhzID0gX3hzO1xuICAgIGlmICh4cykge1xuICAgICAgZih4c1swXSk7XG4gICAgICBfeHMgPSB4c1sxXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qICgpICovMDtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGZvckVhY2goeHMsIGYpIHtcbiAgcmV0dXJuIGZvckVhY2hVKHhzLCBDdXJyeS5fXzEoZikpO1xufVxuXG5mdW5jdGlvbiBmb3JFYWNoV2l0aEluZGV4VShsLCBmKSB7XG4gIHZhciBfeHMgPSBsO1xuICB2YXIgX2kgPSAwO1xuICB2YXIgZiQxID0gZjtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBpID0gX2k7XG4gICAgdmFyIHhzID0gX3hzO1xuICAgIGlmICh4cykge1xuICAgICAgZiQxKGksIHhzWzBdKTtcbiAgICAgIF9pID0gaSArIDEgfCAwO1xuICAgICAgX3hzID0geHNbMV07XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBmb3JFYWNoV2l0aEluZGV4KGwsIGYpIHtcbiAgcmV0dXJuIGZvckVhY2hXaXRoSW5kZXhVKGwsIEN1cnJ5Ll9fMihmKSk7XG59XG5cbmZ1bmN0aW9uIHJlZHVjZVUoX2wsIF9hY2N1LCBmKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgYWNjdSA9IF9hY2N1O1xuICAgIHZhciBsID0gX2w7XG4gICAgaWYgKGwpIHtcbiAgICAgIF9hY2N1ID0gZihhY2N1LCBsWzBdKTtcbiAgICAgIF9sID0gbFsxXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGFjY3U7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiByZWR1Y2UobCwgYWNjdSwgZikge1xuICByZXR1cm4gcmVkdWNlVShsLCBhY2N1LCBDdXJyeS5fXzIoZikpO1xufVxuXG5mdW5jdGlvbiByZWR1Y2VSZXZlcnNlVW5zYWZlVShsLCBhY2N1LCBmKSB7XG4gIGlmIChsKSB7XG4gICAgcmV0dXJuIGYocmVkdWNlUmV2ZXJzZVVuc2FmZVUobFsxXSwgYWNjdSwgZiksIGxbMF0pO1xuICB9IGVsc2Uge1xuICAgIHJldHVybiBhY2N1O1xuICB9XG59XG5cbmZ1bmN0aW9uIHJlZHVjZVJldmVyc2VVKGwsIGFjYywgZikge1xuICB2YXIgbGVuID0gbGVuZ3RoKGwpO1xuICBpZiAobGVuIDwgMTAwMCkge1xuICAgIHJldHVybiByZWR1Y2VSZXZlcnNlVW5zYWZlVShsLCBhY2MsIGYpO1xuICB9IGVsc2Uge1xuICAgIHJldHVybiBCZWx0X0FycmF5LnJlZHVjZVJldmVyc2VVKHRvQXJyYXkobCksIGFjYywgZik7XG4gIH1cbn1cblxuZnVuY3Rpb24gcmVkdWNlUmV2ZXJzZShsLCBhY2N1LCBmKSB7XG4gIHJldHVybiByZWR1Y2VSZXZlcnNlVShsLCBhY2N1LCBDdXJyeS5fXzIoZikpO1xufVxuXG5mdW5jdGlvbiBtYXBSZXZlcnNlMlUobDEsIGwyLCBmKSB7XG4gIHZhciBfbDEgPSBsMTtcbiAgdmFyIF9sMiA9IGwyO1xuICB2YXIgX2FjY3UgPSAvKiBbXSAqLzA7XG4gIHZhciBmJDEgPSBmO1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGFjY3UgPSBfYWNjdTtcbiAgICB2YXIgbDIkMSA9IF9sMjtcbiAgICB2YXIgbDEkMSA9IF9sMTtcbiAgICBpZiAobDEkMSAmJiBsMiQxKSB7XG4gICAgICBfYWNjdSA9IC8qIDo6ICovW1xuICAgICAgICBmJDEobDEkMVswXSwgbDIkMVswXSksXG4gICAgICAgIGFjY3VcbiAgICAgIF07XG4gICAgICBfbDIgPSBsMiQxWzFdO1xuICAgICAgX2wxID0gbDEkMVsxXTtcbiAgICAgIGNvbnRpbnVlIDtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGFjY3U7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBtYXBSZXZlcnNlMihsMSwgbDIsIGYpIHtcbiAgcmV0dXJuIG1hcFJldmVyc2UyVShsMSwgbDIsIEN1cnJ5Ll9fMihmKSk7XG59XG5cbmZ1bmN0aW9uIGZvckVhY2gyVShfbDEsIF9sMiwgZikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGwyID0gX2wyO1xuICAgIHZhciBsMSA9IF9sMTtcbiAgICBpZiAobDEgJiYgbDIpIHtcbiAgICAgIGYobDFbMF0sIGwyWzBdKTtcbiAgICAgIF9sMiA9IGwyWzFdO1xuICAgICAgX2wxID0gbDFbMV07XG4gICAgICBjb250aW51ZSA7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiAoKSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBmb3JFYWNoMihsMSwgbDIsIGYpIHtcbiAgcmV0dXJuIGZvckVhY2gyVShsMSwgbDIsIEN1cnJ5Ll9fMihmKSk7XG59XG5cbmZ1bmN0aW9uIHJlZHVjZTJVKF9sMSwgX2wyLCBfYWNjdSwgZikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGFjY3UgPSBfYWNjdTtcbiAgICB2YXIgbDIgPSBfbDI7XG4gICAgdmFyIGwxID0gX2wxO1xuICAgIGlmIChsMSAmJiBsMikge1xuICAgICAgX2FjY3UgPSBmKGFjY3UsIGwxWzBdLCBsMlswXSk7XG4gICAgICBfbDIgPSBsMlsxXTtcbiAgICAgIF9sMSA9IGwxWzFdO1xuICAgICAgY29udGludWUgO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gYWNjdTtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIHJlZHVjZTIobDEsIGwyLCBhY2MsIGYpIHtcbiAgcmV0dXJuIHJlZHVjZTJVKGwxLCBsMiwgYWNjLCBDdXJyeS5fXzMoZikpO1xufVxuXG5mdW5jdGlvbiByZWR1Y2VSZXZlcnNlMlVuc2FmZVUobDEsIGwyLCBhY2N1LCBmKSB7XG4gIGlmIChsMSAmJiBsMikge1xuICAgIHJldHVybiBmKHJlZHVjZVJldmVyc2UyVW5zYWZlVShsMVsxXSwgbDJbMV0sIGFjY3UsIGYpLCBsMVswXSwgbDJbMF0pO1xuICB9IGVsc2Uge1xuICAgIHJldHVybiBhY2N1O1xuICB9XG59XG5cbmZ1bmN0aW9uIHJlZHVjZVJldmVyc2UyVShsMSwgbDIsIGFjYywgZikge1xuICB2YXIgbGVuID0gbGVuZ3RoKGwxKTtcbiAgaWYgKGxlbiA8IDEwMDApIHtcbiAgICByZXR1cm4gcmVkdWNlUmV2ZXJzZTJVbnNhZmVVKGwxLCBsMiwgYWNjLCBmKTtcbiAgfSBlbHNlIHtcbiAgICByZXR1cm4gQmVsdF9BcnJheS5yZWR1Y2VSZXZlcnNlMlUodG9BcnJheShsMSksIHRvQXJyYXkobDIpLCBhY2MsIGYpO1xuICB9XG59XG5cbmZ1bmN0aW9uIHJlZHVjZVJldmVyc2UyKGwxLCBsMiwgYWNjLCBmKSB7XG4gIHJldHVybiByZWR1Y2VSZXZlcnNlMlUobDEsIGwyLCBhY2MsIEN1cnJ5Ll9fMyhmKSk7XG59XG5cbmZ1bmN0aW9uIGV2ZXJ5VShfeHMsIHApIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciB4cyA9IF94cztcbiAgICBpZiAoeHMpIHtcbiAgICAgIGlmIChwKHhzWzBdKSkge1xuICAgICAgICBfeHMgPSB4c1sxXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gdHJ1ZTtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGV2ZXJ5KHhzLCBwKSB7XG4gIHJldHVybiBldmVyeVUoeHMsIEN1cnJ5Ll9fMShwKSk7XG59XG5cbmZ1bmN0aW9uIHNvbWVVKF94cywgcCkge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHhzID0gX3hzO1xuICAgIGlmICh4cykge1xuICAgICAgaWYgKHAoeHNbMF0pKSB7XG4gICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgX3hzID0geHNbMV07XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gc29tZSh4cywgcCkge1xuICByZXR1cm4gc29tZVUoeHMsIEN1cnJ5Ll9fMShwKSk7XG59XG5cbmZ1bmN0aW9uIGV2ZXJ5MlUoX2wxLCBfbDIsIHApIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBsMiA9IF9sMjtcbiAgICB2YXIgbDEgPSBfbDE7XG4gICAgaWYgKGwxICYmIGwyKSB7XG4gICAgICBpZiAocChsMVswXSwgbDJbMF0pKSB7XG4gICAgICAgIF9sMiA9IGwyWzFdO1xuICAgICAgICBfbDEgPSBsMVsxXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gdHJ1ZTtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGV2ZXJ5MihsMSwgbDIsIHApIHtcbiAgcmV0dXJuIGV2ZXJ5MlUobDEsIGwyLCBDdXJyeS5fXzIocCkpO1xufVxuXG5mdW5jdGlvbiBjbXBCeUxlbmd0aChfbDEsIF9sMikge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGwyID0gX2wyO1xuICAgIHZhciBsMSA9IF9sMTtcbiAgICBpZiAobDEpIHtcbiAgICAgIGlmIChsMikge1xuICAgICAgICBfbDIgPSBsMlsxXTtcbiAgICAgICAgX2wxID0gbDFbMV07XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiAxO1xuICAgICAgfVxuICAgIH0gZWxzZSBpZiAobDIpIHtcbiAgICAgIHJldHVybiAtMTtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIDA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBjbXBVKF9sMSwgX2wyLCBwKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgbDIgPSBfbDI7XG4gICAgdmFyIGwxID0gX2wxO1xuICAgIGlmIChsMSkge1xuICAgICAgaWYgKGwyKSB7XG4gICAgICAgIHZhciBjID0gcChsMVswXSwgbDJbMF0pO1xuICAgICAgICBpZiAoYyA9PT0gMCkge1xuICAgICAgICAgIF9sMiA9IGwyWzFdO1xuICAgICAgICAgIF9sMSA9IGwxWzFdO1xuICAgICAgICAgIGNvbnRpbnVlIDtcbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICByZXR1cm4gYztcbiAgICAgICAgfVxuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIDE7XG4gICAgICB9XG4gICAgfSBlbHNlIGlmIChsMikge1xuICAgICAgcmV0dXJuIC0xO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gMDtcbiAgICB9XG4gIH07XG59XG5cbmZ1bmN0aW9uIGNtcChsMSwgbDIsIGYpIHtcbiAgcmV0dXJuIGNtcFUobDEsIGwyLCBDdXJyeS5fXzIoZikpO1xufVxuXG5mdW5jdGlvbiBlcVUoX2wxLCBfbDIsIHApIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciBsMiA9IF9sMjtcbiAgICB2YXIgbDEgPSBfbDE7XG4gICAgaWYgKGwxKSB7XG4gICAgICBpZiAobDIgJiYgcChsMVswXSwgbDJbMF0pKSB7XG4gICAgICAgIF9sMiA9IGwyWzFdO1xuICAgICAgICBfbDEgPSBsMVsxXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIGZhbHNlO1xuICAgICAgfVxuICAgIH0gZWxzZSBpZiAobDIpIHtcbiAgICAgIHJldHVybiBmYWxzZTtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIHRydWU7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBlcShsMSwgbDIsIGYpIHtcbiAgcmV0dXJuIGVxVShsMSwgbDIsIEN1cnJ5Ll9fMihmKSk7XG59XG5cbmZ1bmN0aW9uIHNvbWUyVShfbDEsIF9sMiwgcCkge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIGwyID0gX2wyO1xuICAgIHZhciBsMSA9IF9sMTtcbiAgICBpZiAobDEgJiYgbDIpIHtcbiAgICAgIGlmIChwKGwxWzBdLCBsMlswXSkpIHtcbiAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfbDIgPSBsMlsxXTtcbiAgICAgICAgX2wxID0gbDFbMV07XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gc29tZTIobDEsIGwyLCBwKSB7XG4gIHJldHVybiBzb21lMlUobDEsIGwyLCBDdXJyeS5fXzIocCkpO1xufVxuXG5mdW5jdGlvbiBoYXNVKF94cywgeCwgZXEpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciB4cyA9IF94cztcbiAgICBpZiAoeHMpIHtcbiAgICAgIGlmIChlcSh4c1swXSwgeCkpIHtcbiAgICAgICAgcmV0dXJuIHRydWU7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfeHMgPSB4c1sxXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gZmFsc2U7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBoYXMoeHMsIHgsIGVxKSB7XG4gIHJldHVybiBoYXNVKHhzLCB4LCBDdXJyeS5fXzIoZXEpKTtcbn1cblxuZnVuY3Rpb24gZ2V0QXNzb2NVKF94cywgeCwgZXEpIHtcbiAgd2hpbGUodHJ1ZSkge1xuICAgIHZhciB4cyA9IF94cztcbiAgICBpZiAoeHMpIHtcbiAgICAgIHZhciBtYXRjaCA9IHhzWzBdO1xuICAgICAgaWYgKGVxKG1hdGNoWzBdLCB4KSkge1xuICAgICAgICByZXR1cm4gLyogU29tZSAqL1ttYXRjaFsxXV07XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfeHMgPSB4c1sxXTtcbiAgICAgICAgY29udGludWUgO1xuICAgICAgfVxuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogTm9uZSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBnZXRBc3NvYyh4cywgeCwgZXEpIHtcbiAgcmV0dXJuIGdldEFzc29jVSh4cywgeCwgQ3VycnkuX18yKGVxKSk7XG59XG5cbmZ1bmN0aW9uIGhhc0Fzc29jVShfeHMsIHgsIGVxKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgeHMgPSBfeHM7XG4gICAgaWYgKHhzKSB7XG4gICAgICBpZiAoZXEoeHNbMF1bMF0sIHgpKSB7XG4gICAgICAgIHJldHVybiB0cnVlO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgX3hzID0geHNbMV07XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIGZhbHNlO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gaGFzQXNzb2MoeHMsIHgsIGVxKSB7XG4gIHJldHVybiBoYXNBc3NvY1UoeHMsIHgsIEN1cnJ5Ll9fMihlcSkpO1xufVxuXG5mdW5jdGlvbiByZW1vdmVBc3NvY1UoeHMsIHgsIGVxKSB7XG4gIGlmICh4cykge1xuICAgIHZhciBsID0geHNbMV07XG4gICAgdmFyIHBhaXIgPSB4c1swXTtcbiAgICBpZiAoZXEocGFpclswXSwgeCkpIHtcbiAgICAgIHJldHVybiBsO1xuICAgIH0gZWxzZSB7XG4gICAgICB2YXIgY2VsbCA9IC8qIDo6ICovW1xuICAgICAgICBwYWlyLFxuICAgICAgICAvKiBbXSAqLzBcbiAgICAgIF07XG4gICAgICB2YXIgcmVtb3ZlZCA9IHJlbW92ZUFzc29jQXV4V2l0aE1hcChsLCB4LCBjZWxsLCBlcSk7XG4gICAgICBpZiAocmVtb3ZlZCkge1xuICAgICAgICByZXR1cm4gY2VsbDtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiB4cztcbiAgICAgIH1cbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIC8qIFtdICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiByZW1vdmVBc3NvYyh4cywgeCwgZXEpIHtcbiAgcmV0dXJuIHJlbW92ZUFzc29jVSh4cywgeCwgQ3VycnkuX18yKGVxKSk7XG59XG5cbmZ1bmN0aW9uIHNldEFzc29jVSh4cywgeCwgaywgZXEpIHtcbiAgaWYgKHhzKSB7XG4gICAgdmFyIGwgPSB4c1sxXTtcbiAgICB2YXIgcGFpciA9IHhzWzBdO1xuICAgIGlmIChlcShwYWlyWzBdLCB4KSkge1xuICAgICAgcmV0dXJuIC8qIDo6ICovW1xuICAgICAgICAgICAgICAvKiB0dXBsZSAqL1tcbiAgICAgICAgICAgICAgICB4LFxuICAgICAgICAgICAgICAgIGtcbiAgICAgICAgICAgICAgXSxcbiAgICAgICAgICAgICAgbFxuICAgICAgICAgICAgXTtcbiAgICB9IGVsc2Uge1xuICAgICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgICAgcGFpcixcbiAgICAgICAgLyogW10gKi8wXG4gICAgICBdO1xuICAgICAgdmFyIHJlcGxhY2VkID0gc2V0QXNzb2NBdXhXaXRoTWFwKGwsIHgsIGssIGNlbGwsIGVxKTtcbiAgICAgIGlmIChyZXBsYWNlZCkge1xuICAgICAgICByZXR1cm4gY2VsbDtcbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiAvKiA6OiAqL1tcbiAgICAgICAgICAgICAgICAvKiB0dXBsZSAqL1tcbiAgICAgICAgICAgICAgICAgIHgsXG4gICAgICAgICAgICAgICAgICBrXG4gICAgICAgICAgICAgICAgXSxcbiAgICAgICAgICAgICAgICB4c1xuICAgICAgICAgICAgICBdO1xuICAgICAgfVxuICAgIH1cbiAgfSBlbHNlIHtcbiAgICByZXR1cm4gLyogOjogKi9bXG4gICAgICAgICAgICAvKiB0dXBsZSAqL1tcbiAgICAgICAgICAgICAgeCxcbiAgICAgICAgICAgICAga1xuICAgICAgICAgICAgXSxcbiAgICAgICAgICAgIC8qIFtdICovMFxuICAgICAgICAgIF07XG4gIH1cbn1cblxuZnVuY3Rpb24gc2V0QXNzb2MoeHMsIHgsIGssIGVxKSB7XG4gIHJldHVybiBzZXRBc3NvY1UoeHMsIHgsIGssIEN1cnJ5Ll9fMihlcSkpO1xufVxuXG5mdW5jdGlvbiBzb3J0VSh4cywgY21wKSB7XG4gIHZhciBhcnIgPSB0b0FycmF5KHhzKTtcbiAgQmVsdF9Tb3J0QXJyYXkuc3RhYmxlU29ydEluUGxhY2VCeVUoYXJyLCBjbXApO1xuICByZXR1cm4gZnJvbUFycmF5KGFycik7XG59XG5cbmZ1bmN0aW9uIHNvcnQoeHMsIGNtcCkge1xuICByZXR1cm4gc29ydFUoeHMsIEN1cnJ5Ll9fMihjbXApKTtcbn1cblxuZnVuY3Rpb24gZ2V0QnlVKF94cywgcCkge1xuICB3aGlsZSh0cnVlKSB7XG4gICAgdmFyIHhzID0gX3hzO1xuICAgIGlmICh4cykge1xuICAgICAgdmFyIHggPSB4c1swXTtcbiAgICAgIGlmIChwKHgpKSB7XG4gICAgICAgIHJldHVybiAvKiBTb21lICovW3hdO1xuICAgICAgfSBlbHNlIHtcbiAgICAgICAgX3hzID0geHNbMV07XG4gICAgICAgIGNvbnRpbnVlIDtcbiAgICAgIH1cbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qIE5vbmUgKi8wO1xuICAgIH1cbiAgfTtcbn1cblxuZnVuY3Rpb24gZ2V0QnkoeHMsIHApIHtcbiAgcmV0dXJuIGdldEJ5VSh4cywgQ3VycnkuX18xKHApKTtcbn1cblxuZnVuY3Rpb24ga2VlcFUoX3hzLCBwKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgeHMgPSBfeHM7XG4gICAgaWYgKHhzKSB7XG4gICAgICB2YXIgdCA9IHhzWzFdO1xuICAgICAgdmFyIGggPSB4c1swXTtcbiAgICAgIGlmIChwKGgpKSB7XG4gICAgICAgIHZhciBjZWxsID0gLyogOjogKi9bXG4gICAgICAgICAgaCxcbiAgICAgICAgICAvKiBbXSAqLzBcbiAgICAgICAgXTtcbiAgICAgICAgY29weUF1eFdpdEZpbHRlcihwLCB0LCBjZWxsKTtcbiAgICAgICAgcmV0dXJuIGNlbGw7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfeHMgPSB0O1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiBbXSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBrZWVwKHhzLCBwKSB7XG4gIHJldHVybiBrZWVwVSh4cywgQ3VycnkuX18xKHApKTtcbn1cblxuZnVuY3Rpb24ga2VlcE1hcFUoX3hzLCBwKSB7XG4gIHdoaWxlKHRydWUpIHtcbiAgICB2YXIgeHMgPSBfeHM7XG4gICAgaWYgKHhzKSB7XG4gICAgICB2YXIgdCA9IHhzWzFdO1xuICAgICAgdmFyIG1hdGNoID0gcCh4c1swXSk7XG4gICAgICBpZiAobWF0Y2gpIHtcbiAgICAgICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgICAgICBtYXRjaFswXSxcbiAgICAgICAgICAvKiBbXSAqLzBcbiAgICAgICAgXTtcbiAgICAgICAgY29weUF1eFdpdEZpbHRlck1hcChwLCB0LCBjZWxsKTtcbiAgICAgICAgcmV0dXJuIGNlbGw7XG4gICAgICB9IGVsc2Uge1xuICAgICAgICBfeHMgPSB0O1xuICAgICAgICBjb250aW51ZSA7XG4gICAgICB9XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiBbXSAqLzA7XG4gICAgfVxuICB9O1xufVxuXG5mdW5jdGlvbiBrZWVwTWFwKHhzLCBwKSB7XG4gIHJldHVybiBrZWVwTWFwVSh4cywgQ3VycnkuX18xKHApKTtcbn1cblxuZnVuY3Rpb24gcGFydGl0aW9uVShsLCBwKSB7XG4gIGlmIChsKSB7XG4gICAgdmFyIGggPSBsWzBdO1xuICAgIHZhciBuZXh0WCA9IC8qIDo6ICovW1xuICAgICAgaCxcbiAgICAgIC8qIFtdICovMFxuICAgIF07XG4gICAgdmFyIG5leHRZID0gLyogOjogKi9bXG4gICAgICBoLFxuICAgICAgLyogW10gKi8wXG4gICAgXTtcbiAgICB2YXIgYiA9IHAoaCk7XG4gICAgcGFydGl0aW9uQXV4KHAsIGxbMV0sIG5leHRYLCBuZXh0WSk7XG4gICAgaWYgKGIpIHtcbiAgICAgIHJldHVybiAvKiB0dXBsZSAqL1tcbiAgICAgICAgICAgICAgbmV4dFgsXG4gICAgICAgICAgICAgIG5leHRZWzFdXG4gICAgICAgICAgICBdO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gLyogdHVwbGUgKi9bXG4gICAgICAgICAgICAgIG5leHRYWzFdLFxuICAgICAgICAgICAgICBuZXh0WVxuICAgICAgICAgICAgXTtcbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIC8qIHR1cGxlICovW1xuICAgICAgICAgICAgLyogW10gKi8wLFxuICAgICAgICAgICAgLyogW10gKi8wXG4gICAgICAgICAgXTtcbiAgfVxufVxuXG5mdW5jdGlvbiBwYXJ0aXRpb24obCwgcCkge1xuICByZXR1cm4gcGFydGl0aW9uVShsLCBDdXJyeS5fXzEocCkpO1xufVxuXG5mdW5jdGlvbiB1bnppcCh4cykge1xuICBpZiAoeHMpIHtcbiAgICB2YXIgbWF0Y2ggPSB4c1swXTtcbiAgICB2YXIgY2VsbFggPSAvKiA6OiAqL1tcbiAgICAgIG1hdGNoWzBdLFxuICAgICAgLyogW10gKi8wXG4gICAgXTtcbiAgICB2YXIgY2VsbFkgPSAvKiA6OiAqL1tcbiAgICAgIG1hdGNoWzFdLFxuICAgICAgLyogW10gKi8wXG4gICAgXTtcbiAgICBzcGxpdEF1eCh4c1sxXSwgY2VsbFgsIGNlbGxZKTtcbiAgICByZXR1cm4gLyogdHVwbGUgKi9bXG4gICAgICAgICAgICBjZWxsWCxcbiAgICAgICAgICAgIGNlbGxZXG4gICAgICAgICAgXTtcbiAgfSBlbHNlIHtcbiAgICByZXR1cm4gLyogdHVwbGUgKi9bXG4gICAgICAgICAgICAvKiBbXSAqLzAsXG4gICAgICAgICAgICAvKiBbXSAqLzBcbiAgICAgICAgICBdO1xuICB9XG59XG5cbmZ1bmN0aW9uIHppcChsMSwgbDIpIHtcbiAgaWYgKGwxICYmIGwyKSB7XG4gICAgdmFyIGNlbGwgPSAvKiA6OiAqL1tcbiAgICAgIC8qIHR1cGxlICovW1xuICAgICAgICBsMVswXSxcbiAgICAgICAgbDJbMF1cbiAgICAgIF0sXG4gICAgICAvKiBbXSAqLzBcbiAgICBdO1xuICAgIHppcEF1eChsMVsxXSwgbDJbMV0sIGNlbGwpO1xuICAgIHJldHVybiBjZWxsO1xuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBbXSAqLzA7XG4gIH1cbn1cblxudmFyIHNpemUgPSBsZW5ndGg7XG5cbmV4cG9ydHMubGVuZ3RoID0gbGVuZ3RoO1xuZXhwb3J0cy5zaXplID0gc2l6ZTtcbmV4cG9ydHMuaGVhZCA9IGhlYWQ7XG5leHBvcnRzLmhlYWRFeG4gPSBoZWFkRXhuO1xuZXhwb3J0cy50YWlsID0gdGFpbDtcbmV4cG9ydHMudGFpbEV4biA9IHRhaWxFeG47XG5leHBvcnRzLmFkZCA9IGFkZDtcbmV4cG9ydHMuZ2V0ID0gZ2V0O1xuZXhwb3J0cy5nZXRFeG4gPSBnZXRFeG47XG5leHBvcnRzLm1ha2UgPSBtYWtlO1xuZXhwb3J0cy5tYWtlQnlVID0gbWFrZUJ5VTtcbmV4cG9ydHMubWFrZUJ5ID0gbWFrZUJ5O1xuZXhwb3J0cy5zaHVmZmxlID0gc2h1ZmZsZTtcbmV4cG9ydHMuZHJvcCA9IGRyb3A7XG5leHBvcnRzLnRha2UgPSB0YWtlO1xuZXhwb3J0cy5zcGxpdEF0ID0gc3BsaXRBdDtcbmV4cG9ydHMuY29uY2F0ID0gY29uY2F0O1xuZXhwb3J0cy5jb25jYXRNYW55ID0gY29uY2F0TWFueTtcbmV4cG9ydHMucmV2ZXJzZUNvbmNhdCA9IHJldmVyc2VDb25jYXQ7XG5leHBvcnRzLmZsYXR0ZW4gPSBmbGF0dGVuO1xuZXhwb3J0cy5tYXBVID0gbWFwVTtcbmV4cG9ydHMubWFwID0gbWFwO1xuZXhwb3J0cy56aXAgPSB6aXA7XG5leHBvcnRzLnppcEJ5VSA9IHppcEJ5VTtcbmV4cG9ydHMuemlwQnkgPSB6aXBCeTtcbmV4cG9ydHMubWFwV2l0aEluZGV4VSA9IG1hcFdpdGhJbmRleFU7XG5leHBvcnRzLm1hcFdpdGhJbmRleCA9IG1hcFdpdGhJbmRleDtcbmV4cG9ydHMuZnJvbUFycmF5ID0gZnJvbUFycmF5O1xuZXhwb3J0cy50b0FycmF5ID0gdG9BcnJheTtcbmV4cG9ydHMucmV2ZXJzZSA9IHJldmVyc2U7XG5leHBvcnRzLm1hcFJldmVyc2VVID0gbWFwUmV2ZXJzZVU7XG5leHBvcnRzLm1hcFJldmVyc2UgPSBtYXBSZXZlcnNlO1xuZXhwb3J0cy5mb3JFYWNoVSA9IGZvckVhY2hVO1xuZXhwb3J0cy5mb3JFYWNoID0gZm9yRWFjaDtcbmV4cG9ydHMuZm9yRWFjaFdpdGhJbmRleFUgPSBmb3JFYWNoV2l0aEluZGV4VTtcbmV4cG9ydHMuZm9yRWFjaFdpdGhJbmRleCA9IGZvckVhY2hXaXRoSW5kZXg7XG5leHBvcnRzLnJlZHVjZVUgPSByZWR1Y2VVO1xuZXhwb3J0cy5yZWR1Y2UgPSByZWR1Y2U7XG5leHBvcnRzLnJlZHVjZVJldmVyc2VVID0gcmVkdWNlUmV2ZXJzZVU7XG5leHBvcnRzLnJlZHVjZVJldmVyc2UgPSByZWR1Y2VSZXZlcnNlO1xuZXhwb3J0cy5tYXBSZXZlcnNlMlUgPSBtYXBSZXZlcnNlMlU7XG5leHBvcnRzLm1hcFJldmVyc2UyID0gbWFwUmV2ZXJzZTI7XG5leHBvcnRzLmZvckVhY2gyVSA9IGZvckVhY2gyVTtcbmV4cG9ydHMuZm9yRWFjaDIgPSBmb3JFYWNoMjtcbmV4cG9ydHMucmVkdWNlMlUgPSByZWR1Y2UyVTtcbmV4cG9ydHMucmVkdWNlMiA9IHJlZHVjZTI7XG5leHBvcnRzLnJlZHVjZVJldmVyc2UyVSA9IHJlZHVjZVJldmVyc2UyVTtcbmV4cG9ydHMucmVkdWNlUmV2ZXJzZTIgPSByZWR1Y2VSZXZlcnNlMjtcbmV4cG9ydHMuZXZlcnlVID0gZXZlcnlVO1xuZXhwb3J0cy5ldmVyeSA9IGV2ZXJ5O1xuZXhwb3J0cy5zb21lVSA9IHNvbWVVO1xuZXhwb3J0cy5zb21lID0gc29tZTtcbmV4cG9ydHMuZXZlcnkyVSA9IGV2ZXJ5MlU7XG5leHBvcnRzLmV2ZXJ5MiA9IGV2ZXJ5MjtcbmV4cG9ydHMuc29tZTJVID0gc29tZTJVO1xuZXhwb3J0cy5zb21lMiA9IHNvbWUyO1xuZXhwb3J0cy5jbXBCeUxlbmd0aCA9IGNtcEJ5TGVuZ3RoO1xuZXhwb3J0cy5jbXBVID0gY21wVTtcbmV4cG9ydHMuY21wID0gY21wO1xuZXhwb3J0cy5lcVUgPSBlcVU7XG5leHBvcnRzLmVxID0gZXE7XG5leHBvcnRzLmhhc1UgPSBoYXNVO1xuZXhwb3J0cy5oYXMgPSBoYXM7XG5leHBvcnRzLmdldEJ5VSA9IGdldEJ5VTtcbmV4cG9ydHMuZ2V0QnkgPSBnZXRCeTtcbmV4cG9ydHMua2VlcFUgPSBrZWVwVTtcbmV4cG9ydHMua2VlcCA9IGtlZXA7XG5leHBvcnRzLmtlZXBNYXBVID0ga2VlcE1hcFU7XG5leHBvcnRzLmtlZXBNYXAgPSBrZWVwTWFwO1xuZXhwb3J0cy5wYXJ0aXRpb25VID0gcGFydGl0aW9uVTtcbmV4cG9ydHMucGFydGl0aW9uID0gcGFydGl0aW9uO1xuZXhwb3J0cy51bnppcCA9IHVuemlwO1xuZXhwb3J0cy5nZXRBc3NvY1UgPSBnZXRBc3NvY1U7XG5leHBvcnRzLmdldEFzc29jID0gZ2V0QXNzb2M7XG5leHBvcnRzLmhhc0Fzc29jVSA9IGhhc0Fzc29jVTtcbmV4cG9ydHMuaGFzQXNzb2MgPSBoYXNBc3NvYztcbmV4cG9ydHMucmVtb3ZlQXNzb2NVID0gcmVtb3ZlQXNzb2NVO1xuZXhwb3J0cy5yZW1vdmVBc3NvYyA9IHJlbW92ZUFzc29jO1xuZXhwb3J0cy5zZXRBc3NvY1UgPSBzZXRBc3NvY1U7XG5leHBvcnRzLnNldEFzc29jID0gc2V0QXNzb2M7XG5leHBvcnRzLnNvcnRVID0gc29ydFU7XG5leHBvcnRzLnNvcnQgPSBzb3J0O1xuLyogTm8gc2lkZSBlZmZlY3QgKi9cbiIsIi8vIEdlbmVyYXRlZCBieSBCVUNLTEVTQ1JJUFQgVkVSU0lPTiAzLjEuNSwgUExFQVNFIEVESVQgV0lUSCBDQVJFXG4ndXNlIHN0cmljdCc7XG5cbnZhciBCbG9jayA9IHJlcXVpcmUoXCJicy1wbGF0Zm9ybS9saWIvanMvYmxvY2suanNcIik7XG52YXIgQmVsdF9MaXN0ID0gcmVxdWlyZShcImJzLXBsYXRmb3JtL2xpYi9qcy9iZWx0X0xpc3QuanNcIik7XG5cbmZ1bmN0aW9uIGZyb21MaXN0KHBhcnRzKSB7XG4gIGlmIChwYXJ0cykge1xuICAgIHZhciBhY2NvdW50TmFtZSA9IHBhcnRzWzBdO1xuICAgIHZhciBleGl0ID0gMDtcbiAgICBpZiAoYWNjb3VudE5hbWUgPT09IFwiYWJvdXRcIiAmJiAhcGFydHNbMV0pIHtcbiAgICAgIHJldHVybiAvKiBBYm91dCAqLzE7XG4gICAgfSBlbHNlIHtcbiAgICAgIGV4aXQgPSAxO1xuICAgIH1cbiAgICBpZiAoZXhpdCA9PT0gMSkge1xuICAgICAgdmFyIG1hdGNoID0gcGFydHNbMV07XG4gICAgICBpZiAobWF0Y2gpIHtcbiAgICAgICAgdmFyIG1hdGNoJDEgPSBtYXRjaFsxXTtcbiAgICAgICAgdmFyIHBvbGxJZCA9IG1hdGNoWzBdO1xuICAgICAgICBpZiAobWF0Y2gkMSkge1xuICAgICAgICAgIGlmIChtYXRjaCQxWzBdID09PSBcInJlc3VsdHNcIiAmJiAhbWF0Y2gkMVsxXSkge1xuICAgICAgICAgICAgcmV0dXJuIC8qIFBvbGxSZXN1bHRzICovQmxvY2suX18oMiwgW1xuICAgICAgICAgICAgICAgICAgICAgIGFjY291bnROYW1lLFxuICAgICAgICAgICAgICAgICAgICAgIHBvbGxJZFxuICAgICAgICAgICAgICAgICAgICBdKTtcbiAgICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgICAgcmV0dXJuIC8qIEhvbWUgKi8wO1xuICAgICAgICAgIH1cbiAgICAgICAgfSBlbHNlIHtcbiAgICAgICAgICByZXR1cm4gLyogUG9sbCAqL0Jsb2NrLl9fKDEsIFtcbiAgICAgICAgICAgICAgICAgICAgYWNjb3VudE5hbWUsXG4gICAgICAgICAgICAgICAgICAgIHBvbGxJZFxuICAgICAgICAgICAgICAgICAgXSk7XG4gICAgICAgIH1cbiAgICAgIH0gZWxzZSB7XG4gICAgICAgIHJldHVybiAvKiBQcm9maWxlICovQmxvY2suX18oMCwgW2FjY291bnROYW1lXSk7XG4gICAgICB9XG4gICAgfVxuICAgIFxuICB9IGVsc2Uge1xuICAgIHJldHVybiAvKiBIb21lICovMDtcbiAgfVxufVxuXG5mdW5jdGlvbiBmcm9tVXJsKHVybCkge1xuICByZXR1cm4gZnJvbUxpc3QodXJsWy8qIHBhdGggKi8wXSk7XG59XG5cbmZ1bmN0aW9uIGZyb21TdHJpbmcoc3RyKSB7XG4gIHJldHVybiBmcm9tTGlzdChCZWx0X0xpc3QuZnJvbUFycmF5KHN0ci5zcGxpdChcIi9cIikpKTtcbn1cblxuZnVuY3Rpb24gdG9TdHJpbmcocm91dGUpIHtcbiAgaWYgKHR5cGVvZiByb3V0ZSA9PT0gXCJudW1iZXJcIikge1xuICAgIGlmIChyb3V0ZSA9PT0gMCkge1xuICAgICAgcmV0dXJuIFwiL1wiO1xuICAgIH0gZWxzZSB7XG4gICAgICByZXR1cm4gXCIvYWJvdXRcIjtcbiAgICB9XG4gIH0gZWxzZSB7XG4gICAgc3dpdGNoIChyb3V0ZS50YWcgfCAwKSB7XG4gICAgICBjYXNlIDAgOiBcbiAgICAgICAgICByZXR1cm4gXCIvXCIgKyByb3V0ZVswXTtcbiAgICAgIGNhc2UgMSA6IFxuICAgICAgICAgIHJldHVybiBcIi9cIiArIChyb3V0ZVswXSArIChcIi9cIiArIHJvdXRlWzFdKSk7XG4gICAgICBjYXNlIDIgOiBcbiAgICAgICAgICByZXR1cm4gXCIvXCIgKyAocm91dGVbMF0gKyAoXCIvXCIgKyAocm91dGVbMV0gKyBcIi9yZXN1bHRzXCIpKSk7XG4gICAgICBcbiAgICB9XG4gIH1cbn1cblxuZXhwb3J0cy5mcm9tTGlzdCA9IGZyb21MaXN0O1xuZXhwb3J0cy5mcm9tVXJsID0gZnJvbVVybDtcbmV4cG9ydHMuZnJvbVN0cmluZyA9IGZyb21TdHJpbmc7XG5leHBvcnRzLnRvU3RyaW5nID0gdG9TdHJpbmc7XG4vKiBObyBzaWRlIGVmZmVjdCAqL1xuIl0sInNvdXJjZVJvb3QiOiIifQ==