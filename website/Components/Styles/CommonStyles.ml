open TypedGlamor

(* This needs be referred to in somthing that's actually used to be included in the css bundle *)
include GlobalStyles 

let widthContainer = css [
  margin2 ~v:zero ~h:auto;
  maxWidth (rem 85.);
  minWidth (rem 30.);
  width (pct 100.);
]

let button = css [
  backgroundColor Theme.Color.link;
  border3 (rem 0.1) solid (rgba 0 0 0 0.8);
  color Theme.Color.background;
  padding2 ~v:(rem 1.) ~h:(rem 1.);
  borderWidth zero;
  borderRadius (rem 0.3);
  fontWeight bold;
  fontSize (rem 1.6);
  cursor pointer;
  unsafe "textShadow" "1px 1px 0 rgba(0, 0, 0, 0.8)";
]

let pageHeader = css [
  padding2 ~v:(rem 3.5) ~h:zero;
  textAlign center;
  fontSize (rem 3.8);
  unsafe "textShadow" "1px 1px 0 white";
]

let pagePrimaryBox = css [
  backgroundColor white;
  borderRadius Theme.borderRadius;
  padding (rem 4.);
  border3 (rem 0.1) solid (hex "e6e6e6");
]

let pageSecondaryBox = css []
