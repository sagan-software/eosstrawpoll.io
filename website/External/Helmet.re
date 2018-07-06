[@bs.module "react-helmet"]
external reactClass : ReasonReact.reactClass = "Helmet";

let make = children =>
  ReasonReact.wrapJsForReason(~reactClass, ~props=(), children);

module Property = {
  type t;
  [@bs.send] external toString : t => string = "";
};

let toString = Property.toString;

[@bs.deriving abstract]
type t = {
  base: Property.t,
  bodyAttributes: Property.t,
  htmlAttributes: Property.t,
  link: Property.t,
  meta: Property.t,
  noscript: Property.t,
  script: Property.t,
  style: Property.t,
  title: Property.t,
};

[@bs.module "react-helmet"] [@bs.scope "Helmet"] external renderStatic : unit => t = "";
