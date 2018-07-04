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
  | [accountName, pollId] => Poll(accountName, pollId)
  | [accountName, pollId, "results"] => PollResults(accountName, pollId)
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
  | Poll(accountName, pollId) => "/" ++ accountName ++ "/" ++ pollId
  | PollResults(accountName, pollId) =>
    "/" ++ accountName ++ "/" ++ pollId ++ "/results"
  };

let toAbsolute = route => Env.siteUrl ++ toString(route);
