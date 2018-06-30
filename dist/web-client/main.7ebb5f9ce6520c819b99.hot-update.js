webpackHotUpdate("main",{

/***/ "./src/web-client/Route.js":
/*!*********************************!*\
  !*** ./src/web-client/Route.js ***!
  \*********************************/
/*! no static exports found */
/***/ (function(module, exports, __webpack_require__) {

"use strict";
// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE


var Block = __webpack_require__(/*! bs-platform/lib/js/block.js */ "./node_modules/bs-platform/lib/js/block.js");

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
        var match$2 = match$1[1];
        var pollId = match$1[0];
        if (match$2) {
          if (match$2[0] === "results" && !match$2[1]) {
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

function fromString(str) {
  var match = str.split("/");
  var len = match.length;
  if (len !== 1) {
    if (len !== 0) {
      return /* Profile */Block.__(0, ["alice"]);
    } else {
      return /* Home */0;
    }
  } else {
    var match$1 = match[0];
    if (match$1 === "about") {
      return /* About */1;
    } else {
      return /* Profile */Block.__(0, ["alice"]);
    }
  }
}

exports.fromUrl = fromUrl;
exports.toString = toString;
exports.fromString = fromString;
/* No side effect */


/***/ })

})
//# sourceMappingURL=data:application/json;charset=utf-8;base64,eyJ2ZXJzaW9uIjozLCJzb3VyY2VzIjpbIndlYnBhY2s6Ly8vLi9zcmMvd2ViLWNsaWVudC9Sb3V0ZS5qcyJdLCJuYW1lcyI6W10sIm1hcHBpbmdzIjoiOzs7Ozs7Ozs7O0FBQUE7QUFDQTs7QUFFQTs7QUFFQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLEtBQUs7QUFDTDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBLFdBQVc7QUFDWDtBQUNBO0FBQ0EsU0FBUztBQUNUO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQSxPQUFPO0FBQ1A7QUFDQTtBQUNBOztBQUVBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQSxLQUFLO0FBQ0w7QUFDQTtBQUNBLEdBQUc7QUFDSDtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0E7QUFDQTs7QUFFQTtBQUNBO0FBQ0E7O0FBRUE7QUFDQTtBQUNBO0FBQ0E7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQSxHQUFHO0FBQ0g7QUFDQTtBQUNBO0FBQ0EsS0FBSztBQUNMO0FBQ0E7QUFDQTtBQUNBOztBQUVBO0FBQ0E7QUFDQTtBQUNBIiwiZmlsZSI6Im1haW4uN2ViYjVmOWNlNjUyMGM4MTliOTkuaG90LXVwZGF0ZS5qcyIsInNvdXJjZXNDb250ZW50IjpbIi8vIEdlbmVyYXRlZCBieSBCVUNLTEVTQ1JJUFQgVkVSU0lPTiAzLjEuNSwgUExFQVNFIEVESVQgV0lUSCBDQVJFXG4ndXNlIHN0cmljdCc7XG5cbnZhciBCbG9jayA9IHJlcXVpcmUoXCJicy1wbGF0Zm9ybS9saWIvanMvYmxvY2suanNcIik7XG5cbmZ1bmN0aW9uIGZyb21VcmwodXJsKSB7XG4gIHZhciBtYXRjaCA9IHVybFsvKiBwYXRoICovMF07XG4gIGlmIChtYXRjaCkge1xuICAgIHZhciBhY2NvdW50TmFtZSA9IG1hdGNoWzBdO1xuICAgIHZhciBleGl0ID0gMDtcbiAgICBpZiAoYWNjb3VudE5hbWUgPT09IFwiYWJvdXRcIiAmJiAhbWF0Y2hbMV0pIHtcbiAgICAgIHJldHVybiAvKiBBYm91dCAqLzE7XG4gICAgfSBlbHNlIHtcbiAgICAgIGV4aXQgPSAxO1xuICAgIH1cbiAgICBpZiAoZXhpdCA9PT0gMSkge1xuICAgICAgdmFyIG1hdGNoJDEgPSBtYXRjaFsxXTtcbiAgICAgIGlmIChtYXRjaCQxKSB7XG4gICAgICAgIHZhciBtYXRjaCQyID0gbWF0Y2gkMVsxXTtcbiAgICAgICAgdmFyIHBvbGxJZCA9IG1hdGNoJDFbMF07XG4gICAgICAgIGlmIChtYXRjaCQyKSB7XG4gICAgICAgICAgaWYgKG1hdGNoJDJbMF0gPT09IFwicmVzdWx0c1wiICYmICFtYXRjaCQyWzFdKSB7XG4gICAgICAgICAgICByZXR1cm4gLyogUG9sbFJlc3VsdHMgKi9CbG9jay5fXygyLCBbXG4gICAgICAgICAgICAgICAgICAgICAgYWNjb3VudE5hbWUsXG4gICAgICAgICAgICAgICAgICAgICAgcG9sbElkXG4gICAgICAgICAgICAgICAgICAgIF0pO1xuICAgICAgICAgIH0gZWxzZSB7XG4gICAgICAgICAgICByZXR1cm4gLyogSG9tZSAqLzA7XG4gICAgICAgICAgfVxuICAgICAgICB9IGVsc2Uge1xuICAgICAgICAgIHJldHVybiAvKiBQb2xsICovQmxvY2suX18oMSwgW1xuICAgICAgICAgICAgICAgICAgICBhY2NvdW50TmFtZSxcbiAgICAgICAgICAgICAgICAgICAgcG9sbElkXG4gICAgICAgICAgICAgICAgICBdKTtcbiAgICAgICAgfVxuICAgICAgfSBlbHNlIHtcbiAgICAgICAgcmV0dXJuIC8qIFByb2ZpbGUgKi9CbG9jay5fXygwLCBbYWNjb3VudE5hbWVdKTtcbiAgICAgIH1cbiAgICB9XG4gICAgXG4gIH0gZWxzZSB7XG4gICAgcmV0dXJuIC8qIEhvbWUgKi8wO1xuICB9XG59XG5cbmZ1bmN0aW9uIHRvU3RyaW5nKHJvdXRlKSB7XG4gIGlmICh0eXBlb2Ygcm91dGUgPT09IFwibnVtYmVyXCIpIHtcbiAgICBpZiAocm91dGUgPT09IDApIHtcbiAgICAgIHJldHVybiBcIi9cIjtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIFwiL2Fib3V0XCI7XG4gICAgfVxuICB9IGVsc2Uge1xuICAgIHN3aXRjaCAocm91dGUudGFnIHwgMCkge1xuICAgICAgY2FzZSAwIDogXG4gICAgICAgICAgcmV0dXJuIFwiL1wiICsgcm91dGVbMF07XG4gICAgICBjYXNlIDEgOiBcbiAgICAgICAgICByZXR1cm4gXCIvXCIgKyAocm91dGVbMF0gKyAoXCIvXCIgKyByb3V0ZVsxXSkpO1xuICAgICAgY2FzZSAyIDogXG4gICAgICAgICAgcmV0dXJuIFwiL1wiICsgKHJvdXRlWzBdICsgKFwiL1wiICsgKHJvdXRlWzFdICsgXCIvcmVzdWx0c1wiKSkpO1xuICAgICAgXG4gICAgfVxuICB9XG59XG5cbmZ1bmN0aW9uIGZyb21TdHJpbmcoc3RyKSB7XG4gIHZhciBtYXRjaCA9IHN0ci5zcGxpdChcIi9cIik7XG4gIHZhciBsZW4gPSBtYXRjaC5sZW5ndGg7XG4gIGlmIChsZW4gIT09IDEpIHtcbiAgICBpZiAobGVuICE9PSAwKSB7XG4gICAgICByZXR1cm4gLyogUHJvZmlsZSAqL0Jsb2NrLl9fKDAsIFtcImFsaWNlXCJdKTtcbiAgICB9IGVsc2Uge1xuICAgICAgcmV0dXJuIC8qIEhvbWUgKi8wO1xuICAgIH1cbiAgfSBlbHNlIHtcbiAgICB2YXIgbWF0Y2gkMSA9IG1hdGNoWzBdO1xuICAgIGlmIChtYXRjaCQxID09PSBcImFib3V0XCIpIHtcbiAgICAgIHJldHVybiAvKiBBYm91dCAqLzE7XG4gICAgfSBlbHNlIHtcbiAgICAgIHJldHVybiAvKiBQcm9maWxlICovQmxvY2suX18oMCwgW1wiYWxpY2VcIl0pO1xuICAgIH1cbiAgfVxufVxuXG5leHBvcnRzLmZyb21VcmwgPSBmcm9tVXJsO1xuZXhwb3J0cy50b1N0cmluZyA9IHRvU3RyaW5nO1xuZXhwb3J0cy5mcm9tU3RyaW5nID0gZnJvbVN0cmluZztcbi8qIE5vIHNpZGUgZWZmZWN0ICovXG4iXSwic291cmNlUm9vdCI6IiJ9