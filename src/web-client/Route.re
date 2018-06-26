type route =
  | Home
  | About
  | Profile(string)
  | Poll(string, string)
  | PollResults(string, string);

let fromUrl = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Home
  | ["about"] => About
  | [accountName] => Profile(accountName)
  | [accountName, pollId] => Poll(accountName, pollId)
  | [accountName, pollId, "results"] => PollResults(accountName, pollId)
  | _ => Home
  };

let toString = route =>
  switch (route) {
  | Home => "/"
  | About => "/about"
  | Profile(accountName) => "/" ++ accountName
  | Poll(accountName, pollId) => "/" ++ accountName ++ "/" ++ pollId
  | PollResults(accountName, pollId) =>
    "/" ++ accountName ++ "/" ++ pollId ++ "/results"
  };
