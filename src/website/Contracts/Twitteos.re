type t;

module Create = {
  [@bs.deriving abstract]
  type t = {
    author: string,
    text: string,
  };
};

[@bs.send]
external create : (t, Create.t, Eos.Action.options) => Js.Promise.t(unit) =
  "";
