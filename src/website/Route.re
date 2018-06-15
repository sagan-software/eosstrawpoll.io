type route =
  | Home
  | Market
  | Treasury
  | Governance
  | Stats
  | About;

let fromUrl = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Home
  | ["market"] => Market
  | ["treasury"] => Treasury
  | ["governance"] => Governance
  | ["stats"] => Stats
  | ["about"] => About
  | _ => Home
  };

let toString = route =>
  switch (route) {
  | Home => "/"
  | Market => "/market"
  | Treasury => "/treasury"
  | Governance => "/governance"
  | Stats => "/stats"
  | About => "/about"
  };
