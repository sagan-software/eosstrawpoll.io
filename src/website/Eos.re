type t;

module Config = {
  [@bs.deriving abstract]
  type t = {verbose: bool};
};

[@bs.module] external make : Config.t => t = "eosjs";

[@bs.module "eosjs"] external localnet : Config.t => t = "Localnet";

module TableRows = {
  [@bs.deriving abstract]
  type t = {
    more: bool,
    rows: array(Js.Json.t),
  };
};

[@bs.send]
external getTableRows :
  (
    t,
    ~json: bool,
    ~code: string,
    ~scope: string,
    ~table: string,
    ~tableKey: string,
    ~lowerBound: int,
    ~upperBound: int,
    ~limit: int
  ) =>
  Js.Promise.t(TableRows.t) =
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
  [@bs.deriving abstract]
  type options = {
    [@bs.optional]
    authorization: array(string),
  };
};
