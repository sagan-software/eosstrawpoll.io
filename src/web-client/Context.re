type t = {
  scatter: option(Scatter.Instance.t),
  identity: option(Scatter.Identity.t),
  language: Words.language,
};

let empty = {scatter: None, identity: None, language: Words.English};
