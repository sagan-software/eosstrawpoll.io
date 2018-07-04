[@bs.val] [@bs.module "glamor/server"]
external renderStatic :
  (unit => string) =>
  {
    .
    "html": string,
    "css": string,
    "ids": Js.Json.t,
  } =
  "";
