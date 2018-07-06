type t;

module Name = {
  type t = string;
  let decode = Json.Decode.string;
  let encode = Json.Encode.string;
  let possibleChars = "12345abcdefghijklmnopqrstuvwxyz";
  let possibleCharsLength = possibleChars |> Js.String.length;
  let random = () => {
    let chosenChars = [||];
    for (_i in 1 to 12) {
      let chosenIndex = Random.int(possibleCharsLength);
      let chosenChar = possibleChars |> Js.String.charAt(chosenIndex);
      chosenChars |> Js.Array.push(chosenChar) |> ignore;
    };
    chosenChars |> Js.Array.joinWith("");
  };
};

type accountName = Name.t;

module Asset = {
  type t = string;
  let decode = Json.Decode.string;
  let encode = Json.Encode.string;
};

type asset = Asset.t;

module TrxId = {
  type t = string;
  let decode = Json.Decode.string;
  let encode = Json.Encode.string;
};

type trxId = TrxId.t;

module Config = {
  [@bs.deriving abstract]
  type t = {
    httpEndpoint: string,
    [@bs.optional]
    verbose: bool,
    [@bs.optional]
    keyProvider: array(string),
    [@bs.optional]
    chainId: string,
    [@bs.optional]
    expireInSeconds: int,
    [@bs.optional]
    sign: bool,
  };
};

[@bs.module] external make : Config.t => t = "eosjs";

[@bs.module "eosjs"] external localnet : Config.t => t = "Localnet";

[@bs.send]
external getTableRows :
  (
    t,
    ~json: bool,
    ~code: string,
    ~scope: string,
    ~table: string,
    ~tableKey: string,
    ~lowerBound: string,
    ~upperBound: string,
    ~limit: int
  ) =>
  Js.Promise.t(
    {
      .
      "more": bool,
      "rows": array('row),
    },
  ) =
  "getTableRows";

module Account = {
  [@bs.deriving abstract]
  type t = {
    [@bs.as "account_name"]
    accountName: string,
  };
};

[@bs.send] external getAccount : (t, string) => Js.Promise.t(Account.t) = "";

[@bs.send] external contract : (t, string) => Js.Promise.t('contract) = "";

module Action = {
  type options = {. "authorization": array(string)};
};
