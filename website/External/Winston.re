module Format = {
  type t;
  [@bs.module "winston"] [@bs.scope "format"] external json : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"] external simple : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"]
  external timestamp : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"]
  external prettyPrint : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"] external ms : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"]
  external colorize : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"] external cli : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"] external splat : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"] external align : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"]
  external padLevels : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"]
  external metadata : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"]
  external logstash : unit => t = "";
  [@bs.module "winston"] [@bs.scope "format"] [@bs.val]
  external combine_ : 'fn = "combine";
  let combine = formats =>
    Obj.magic(combine_)##apply(Js.Nullable.null, formats);
};

module Transports = {
  type t;
  module Console = {
    [@bs.module "winston"] [@bs.scope "transports"] [@bs.new]
    external make : {. "format": Format.t} => t = "Console";
  };
};

let console = (~format) => Transports.Console.make({"format": format});

type t;

[@bs.module "winston"]
external make_ :
  {
    .
    "level": string,
    "transports": array(Transports.t),
  } =>
  t =
  "createLogger";

let make = (~level, ~transports) =>
  make_({"level": level, "transports": transports});

[@bs.send] external debug : (t, string, 'data) => unit = "";

[@bs.send] external info : (t, string, 'data) => unit = "";

[@bs.send] external warn : (t, string, 'data) => unit = "";

[@bs.send] external clear : t => t = "";

[@bs.send] external add : (t, Transports.t) => t = "";

[@bs.send] external remove : (t, Transports.t) => t = "";

[@bs.send] external error : (t, string, 'data) => unit = "";
