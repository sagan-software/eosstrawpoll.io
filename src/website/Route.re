type route =
  | Home
  | About
  | Profile(string)
  | Post(string, string);

let fromUrl = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | [] => Home
  | ["about"] => About
  | [accountName] => Profile(accountName)
  | [accountName, postId] => Post(accountName, postId)
  | _ => Home
  };

let toString = route =>
  switch (route) {
  | Home => "/"
  | About => "/about"
  | Profile(accountName) => "/" ++ accountName
  | Post(accountName, postId) => "/" ++ accountName ++ "/" ++ postId
  };
