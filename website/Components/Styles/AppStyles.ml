open TypedGlamor


let sidebarWidth = pct 10.

let container = css [
  position absolute;
  width (pct 100.);
  height (pct 100.);
  overflow auto;
  display flex;
  flexDirection column;
]

let headerContainer = css [
  backgroundColor white;
  borderBottom3 (rem 0.1) solid (hex "ccc");
  borderTop3 (rem 0.2) solid (hex "ccc");
]

let header = css ~extend:CommonStyles.widthContainer [
  display flex;
  justifyContent spaceBetween;
  alignItems center;
  textAlign center;
  height (rem 6.);
  fontWeight _700;
  fontSize (rem 1.6);
]

let main = css ~extend:CommonStyles.widthContainer [
  flex3 ~grow:1. ~shrink:0. auto;
]

let appLogoIcon = css [
  height (rem 3.);
  width auto;
  unsafe "fill" "currentColor";
  display none;
]

let appLogo = css [
  display block;
  fontSize (rem 2.8);
  fontWeight _700;
]

let userNav = css [
  display flex;
  height (pct 100.);
  select "> *" [
    border3 zero solid (hex "ccc");
    borderRightWidth (rem 0.1);
    display flex;
    alignItems center;
    padding2 ~v:zero ~h:(rem 1.5);

    firstChild [
      borderLeftWidth (rem 0.1);
    ];
  ];

  select "& a" [
    cursor pointer;

    hover [
      backgroundColor (hex "292d801a");
      textDecoration none;
    ]
  ];
]

let userAvatar = css [
  border3 (rem 0.1) solid Theme.Color.link;
  borderRadius (pct 50.);
  width (rem 3.5);
  height (rem 3.5);
  marginRight (rem 1.);
]

let loginLink = css ~extend:CommonStyles.button []

let footerContainer = css [
  marginTop (rem 2.);
  backgroundColor white;
  fontSize (rem 1.4);
  padding (rem 2.);
  borderTop3 (rem 0.1) solid (hex "ccc");
  borderBottom3 (rem 0.2) solid (hex "ccc");
]

let footer = css ~extend:CommonStyles.widthContainer [
  flexShrink 0.;
  display flex;
  fontSize (rem 1.2);
  color (hex "525252");

  select "& > *" [
    flex_ (int 1);
    flexShrink 0.;
    padding2 (rem 2.) (rem 3.);
  ];

  select "& li" [
    display flex;
    justifyContent spaceBetween;
    padding2 ~v:(rem 0.25) ~h:zero;
  ];

  select "& h3" [
    marginBottom (rem 1.);
    color (hex "444");
    fontSize (rem 1.4);
  ]
]

let donateSection = css []

let donateForm = css [
  display flex;
  marginTop (rem 1.5);
]

let donateInput = css [
  borderTopLeftRadius Theme.borderRadius;
  borderBottomLeftRadius Theme.borderRadius;
  padding2 ~v:zero ~h:(rem 0.5);
  fontSize (rem 1.2);
  border3 (rem 0.1) solid (hex "ccc");
  borderRightWidth zero;
  width (rem 10.);
]

let donateButton = css ~extend:CommonStyles.button [
  borderTopLeftRadius zero;
  borderBottomLeftRadius zero;
  fontSize (rem 1.2);
  padding2 ~v:(rem 0.5) ~h:(rem 0.5);
]

let donators = css []
