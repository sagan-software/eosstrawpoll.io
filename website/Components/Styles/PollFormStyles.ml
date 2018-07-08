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

let field = css [
    position relative;
]


let invalid = css [
    backgroundColor red;
    color white;
    position absolute;
    display none;
]

let valid = css [
    display none;
]

let label = css []

let input = css []

let errors = css []

let titleField = css [
]

let titleInput = fun isValid -> css [
    width (pct 100.);
    fontSize (rem 2.4);
    fontWeight _700;
    marginBottom (rem 1.);
    borderStyle solid;
    borderWidth (rem 0.3);
    borderColor (if isValid then hex "ccc" else hex "d60000");
    borderRadius Theme.borderRadius;
    padding2 ~v:(rem 1.5) ~h:(rem 2.);
    unsafe "backgroundImage" "none !important";

    select "&::placeholder" [
        color (if isValid then hex "ccc" else hex "d60000");
    ];

    select "&:focus" [
        select "&::placeholder" [
            color (hex "ccc");
        ];
    ];

]

let optionField = fun isValid -> css [
    display flex;
    fontSize (rem 1.6);
    height (rem 4.);
    alignItems center;
    marginBottom (rem 1.);
    color (hex (if isValid then "333" else "d60000"));
]

let optionNum = css [
    fontWeight bold;
    width (rem 2.);
    textAlign center;
    lineHeight (rem 3.);
    borderRadius (pct 50.);
]

let optionInput = fun isValid -> css [
    width (pct 100.);
    height (pct 100.);
    (* margin zero; *)
    flex_ (int 1);
    margin2 ~v:zero ~h:(rem 1.);
    fontSize (rem 1.6);
    borderStyle solid;
    borderColor (if isValid then hex "ccc" else hex "d60000");
    borderWidth zero;
    borderBottomWidth (rem 0.3);

    select "&::placeholder" [
        color (if isValid then hex "ccc" else hex "d60000");
    ];

    select "&:focus" [
        select "&::placeholder" [
            color (hex "ccc");
        ];
    ];
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

let advancedFields = css []
