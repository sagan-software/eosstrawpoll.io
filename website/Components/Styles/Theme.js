// Generated by BUCKLESCRIPT VERSION 3.1.5, PLEASE EDIT WITH CARE
'use strict';

var TypedGlamor = require("bs-typed-glamor/src/TypedGlamor.bs.js");

var primary = TypedGlamor.hex("292D80");

var secondary = TypedGlamor.hex("f74a95");

var tertiary = TypedGlamor.hex("e2c0b5");

var darkBackground = TypedGlamor.hex("ececec");

var text = TypedGlamor.hex("444");

var Color = /* module */[
  /* primary */primary,
  /* secondary */secondary,
  /* tertiary */tertiary,
  /* background */TypedGlamor.whitesmoke,
  /* darkBackground */darkBackground,
  /* text */text,
  /* link */primary
];

var Color$1 = /* module */[/* background */TypedGlamor.white];

var Panel = /* module */[/* Color */Color$1];

var block = TypedGlamor.rgba(255, 255, 255, 0.1);

var highlightedBlock = TypedGlamor.rgba(255, 255, 255, 0.2);

var Color$2 = /* module */[
  /* background */primary,
  /* text */TypedGlamor.white,
  /* block */block,
  /* highlightedBlock */highlightedBlock
];

var Inverted = /* module */[/* Color */Color$2];

var overlay = TypedGlamor.shadow(TypedGlamor.ex(1), TypedGlamor.ex(1), /* Some */[TypedGlamor.em(1)], /* None */0, /* None */0, TypedGlamor.rgba(0, 0, 0, 0.1));

var panel = TypedGlamor.shadow(TypedGlamor.px(1), TypedGlamor.px(1), /* None */0, /* Some */[TypedGlamor.px(1)], /* None */0, TypedGlamor.rgba(0, 0, 0, 0.05));

var Shadow = /* module */[
  /* overlay */overlay,
  /* panel */panel
];

var borderRadius = TypedGlamor.rem(0.3);

exports.Color = Color;
exports.Panel = Panel;
exports.Inverted = Inverted;
exports.Shadow = Shadow;
exports.borderRadius = borderRadius;
/* primary Not a pure module */
