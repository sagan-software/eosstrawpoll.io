type t = {
  scatter: option(Scatter.Instance.t),
  identity: option(Scatter.Identity.t),
  language: Intl.language,
};

let initial = {scatter: None, identity: None, language: Intl.English};
