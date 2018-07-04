open TypedGlamor

include HydrateGlamor

let container = css ~extend:CommonStyles.pagePrimaryBox [ ]

let fields = css [
    maxWidth (pct 75.);
    margin2 ~v:zero ~h:auto;

    select "& input" [
        display block;

        select "&:focus" [
            borderColor Theme.Color.primary;
        ]
    ];
]

let field = css []

let label = css []

let input = css []

let errors = css []

let titleField = css [
]

let titleInput = css [
    width (pct 100.);
    fontSize (rem 2.4);
    fontWeight _700;
    marginBottom (rem 1.);
    border3 (rem 0.3) solid (hex "ccc");
    borderRadius Theme.borderRadius;
    padding2 ~v:(rem 1.5) ~h:(rem 2.);
    unsafe "backgroundImage" "none !important";
]

let optionField = css [
    display flex;
    fontSize (rem 1.6);
    height (rem 4.);
    alignItems center;
    marginBottom (rem 1.);
    borderStyle solid;
    borderColor (hex "ccc");
    borderWidth zero;
    borderBottomWidth (rem 0.2);
]

let optionNum = css [
    fontWeight bold;
    width (rem 2.);
    textAlign center;
    lineHeight (rem 3.);
    borderRadius (pct 50.);
]

let optionInput = css [
    width (pct 100.);
    height (pct 100.);
    borderWidth zero;
    margin zero;
    flex_ (int 1);
    padding2 ~v:zero ~h:(rem 1.);
    borderWidth zero;
    fontSize (rem 1.6);
]

let optionRemove = css [
    fontWeight bold;
    textAlign center;
    cursor pointer;
    color Theme.Color.primary;

    select "& svg" [
        display block;
        margin2 ~v:zero ~h:auto;
    ]
]

let submitButton = css ~extend:CommonStyles.button [
    margin3 ~top:(rem 2.5) ~h:auto ~bottom:zero;
    display block;
    fontSize (rem 2.4);
    fontWeight _700;
    padding2 ~v:(rem 1.) ~h:(rem 2.);
]
