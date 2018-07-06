type t;

let fromScatter = scatter =>
  Scatter.eos(scatter, Env.scatterNetwork, Eos.make, Env.eosConfig, "http")
  |. Eos.contract(Env.contractAccount);

let fromEos = eos => eos |. Eos.contract(Env.contractAccount);

[@bs.send]
external create :
  (t, Model.EosAction.create, Eos.Action.options) => Js.Promise.t(unit) =
  "";

[@bs.send]
external close :
  (t, Model.EosAction.close, Eos.Action.options) => Js.Promise.t(unit) =
  "";

[@bs.send]
external vote :
  (t, Model.EosAction.vote, Eos.Action.options) => Js.Promise.t(unit) =
  "";

[@bs.send]
external comment :
  (t, Model.EosAction.comment, Eos.Action.options) => Js.Promise.t(unit) =
  "";
