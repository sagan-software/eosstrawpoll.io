type t;

[@bs.module "http"] external createServer : Express.App.t => t = "";

[@bs.send] external listen : (t, 'port, Js.Exn.t => unit) => unit = "";
