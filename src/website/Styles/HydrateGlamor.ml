external state : string array option = "_glam" [@@bs.val ][@@bs.scope "global"][@@bs.return nullable]

external rehydrate : string array -> unit = "" [@@bs.module "glamor"]

let _ =
  match state with
  | ((Some (s))[@explicit_arity ]) -> rehydrate s
  | None  -> ()
