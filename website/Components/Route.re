type route =
  | Home
  | About
  | Profile(string)
  | Poll(string, string)
  | PollResults(string, string);

let fromList = parts =>
  switch (parts) {
  | [] => Home
  | ["about"] => About
  | [accountName] => Profile(accountName)
  | [accountName, pollName] => Poll(accountName, pollName)
  | [accountName, pollName, "results"] => PollResults(accountName, pollName)
  | _ => Home
  };

let fromUrl = (url: ReasonReact.Router.url) => fromList(url.path);

let fromString = str =>
  str
  |> Js.String.split("/")
  |> Belt.List.fromArray
  |> Js.List.filter((. str) => str != "")
  |> fromList;

let toString = route =>
  switch (route) {
  | Home => "/"
  | About => "/about"
  | Profile(accountName) => "/" ++ accountName
  | Poll(accountName, pollName) => "/" ++ accountName ++ "/" ++ pollName
  | PollResults(accountName, pollName) =>
    "/" ++ accountName ++ "/" ++ pollName ++ "/results"
  };

let toAbsolute = route => Env.siteUrl ++ toString(route);

let redirectTo = route => route |. toString |. ReasonReact.Router.push;
