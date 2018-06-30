type t;

[@bs.module] external fromString : string => t = "moment";

[@bs.module] external fromDate : Js.Date.t => t = "moment";

[@bs.send] external format : t => string = "";

[@bs.send] external fromNow : t => string = "";
