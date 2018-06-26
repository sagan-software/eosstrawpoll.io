[@bs.val] external requireCSS : string => unit = "require";

let defaultEosConfig =
  Eos.Config.t(~httpEndpoint=Env.httpEndpoint, ~verbose=false, ());

let loadEosReadOnly = () => Eos.make(defaultEosConfig);

let loadScatterEos = scatter =>
  Scatter.eos(scatter, Env.network, Eos.make, defaultEosConfig, "http");
