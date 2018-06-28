open TypedGlamor

include HydrateGlamor
include GlobalStyles

let sidebarWidth = pct 20.

(* A basic style definition *)
let container = css ~extend:CommonStyles.html [
  position absolute;
  width (pct 100.);
  height (pct 100.);
  overflow auto;
  display flex;
  flexDirection column;
]

let header = css [
  display flex;
  height (px 50);
  justifyContent spaceBetween;
  alignItems center;
  textAlign center;
]

let main = css [
  flex3 1. 0. auto;
]

let footer = css [
  flexShrink 0.;
  textAlign center;
]

let appLogo = css [
  width sidebarWidth
]

let primaryNav = css [
  flex_ (int 1);
  display flex;
]

let secondaryNav = css [
  flex_ (int 1);
  display flex;
  justifyContent flexEnd;
]

let appLink = fun ~isSelected -> css [
  padding (px 10);

  fontWeight (
    if isSelected then
      bold
    else
      normal
  )
]

let userNav = css [
  width sidebarWidth
]

let loginLink = css []

(* ml *)
(* The OCaml syntax is recommended with this DSL for improved readability, and will be shown here.
   Reason users can use a separate .ml file alongside each component file, for eaxample if the
   component is in `Foo.re`, you could have a `FooStyles.ml` alongside it and then refer to 
   `FooStyles.myStyle` in the component *)

(* triangle *)
let cube = css [
  (* style definitions can have labels which will be included in the generated classnames to aid debugging *)
  label "thing";
  
  (* multi-argument properties are suffixed with the number of arguments they take, and are labeled when there's confusion *)
  padding2 ~v:(em 0.75) ~h:(em 1.5);
  
  (* single-argument properties are not *)
  padding zero;
  
  (* properties that can take any number of arguments are pluralized and take a list *)
  transitions [
    (AnimatableProperty.opacity, ms 500, linear, ms 0);
    (AnimatableProperty.height, ms 300, linear, ms 200);
  ];
  
  (* they'll still have a non-pluralized variant which can take a single argument however,
      and which will still override the pluralzied variant *)
  transition unset;
  
  (* if a value and property name conflict by having the same name, the property name is "mangled" *)
  display flex;
  flex_ (int 1);

  (* `select`, given a css selector where `&` is substituted with the current element,
      will apply the given styles to the sub selection *)
  select "& > .title" [
    fontSize larger;
  ];
  
  (* `&` is implied at the start *)
  select "> .subtitle" [
    fontSize smaller;
  ];
  
  (* `:hover` and other pseudo-classes are all available statically typed  *)
  hover [
    background plum;
  ];
  
  (* media queries are not statically typed (yet), but can be stringly typed in a `select` *)
  select "@media (max-width: 600px)" [
    select "& > .subtitle" [
      display none;
    ];
  ];
]


(* Global style declarations are supported through `global`.  *)
let _global = begin
  global "html" [
    fontSize (px 15);
    lineHeight (em 1.25);
  ];

  global "html, body" [
    backgroundColor white;
    minHeight (pct 100.);
  ];
end
