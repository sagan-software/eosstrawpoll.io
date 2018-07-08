open TypedGlamor

include HydrateGlamor

let main = css ~extend:AppStyles.main [
]

let slogan = css ~extend:CommonStyles.pageHeader [ ]

let content = css [
    display flex;
    flexDirection column;
]

let form = css [
    flex_ auto;
    marginBottom (rem 2.);
]

let pollLists = css [
    display flex;
    flexDirection row;
    backgroundColor white;
    borderRadius Theme.borderRadius;
    border3 (rem 0.1) solid (hex "e6e6e6");
    margin2 ~v:(rem 1.) ~h:zero;
]

let pollList = css [
    flex_ (int 1);
    paddingBottom (rem 1.);

    select ":not(:last-of-type)" [
        borderRight3 (rem 0.1) solid (hex "e6e6e6");
    ]
]

let pollListTitle = css [
    fontSize (rem 2.);
    padding2 ~v:(rem 1.5) ~h:(rem 2.);
]

let pollListItems = css []

let poll = css [
    padding2 ~v:(rem 0.) ~h:(rem 2.);
    fontSize (rem 1.4);
    marginBottom (rem 1.);
]

let pollTitle = css [
    fontSize (rem 1.4);
]

let pollInfo = css [
    opacity 0.75;
    fontSize (rem 1.2);
]

let pollCreator = css []

let pollTime = css []

let pollStats = css []
