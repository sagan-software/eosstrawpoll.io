type t = {
  scatter: option(Scatter.Instance.t),
  identity: option(Scatter.Identity.t),
  language: Intl.language,
};

let initial = {scatter: None, identity: None, language: Intl.English};

let accountName = t =>
  t.identity
  |> Js.Option.andThen((. identity) =>
       identity |. Scatter.Identity.accounts |. Belt.Array.get(0)
     )
  |. Belt.Option.map(Scatter.Account.name);
