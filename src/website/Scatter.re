module Protocol = {
  [@bs.string]
  type t = [ | `http | `https];
  let toString = t =>
    switch (t) {
    | `http => "http"
    | `https => "https"
    };
};

module Blockchain = {
  [@bs.string]
  type t = [ | `eos | `eth];
  let toString = t =>
    switch (t) {
    | `eos => "eos"
    | `eth => "eth"
    };
};

module Network = {
  [@bs.deriving abstract]
  type t = {
    protocol: string,
    blockchain: string,
    host: string,
    port: int,
    [@bs.optional]
    chainId: string,
  };
  let make = (~protocol, ~blockchain, ~host, ~port) =>
    t(
      ~protocol=Protocol.toString(protocol),
      ~blockchain=Blockchain.toString(blockchain),
      ~host,
      ~port,
      (),
    );
};

module Account = {
  [@bs.deriving abstract]
  type t = {
    name: string,
    authority: string,
    blockchain: string,
  };
};

module Identity = {
  [@bs.deriving abstract]
  type t = {
    hash: string,
    kyc: bool,
    name: string,
    publicKey: string,
    [@bs.nullable]
    accounts: array(Account.t),
  };
};

module PersonalField = {
  type t = [ | `firstname | `lastname | `email | `birthdate];
  let toString = t =>
    switch (t) {
    | `firstname => "firstname"
    | `lastname => "lastname"
    | `email => "email"
    | `birthdate => "birthdate"
    };
};

module LocationField = {
  type t = [ | `phone | `address | `city | `state | `country | `zipcode];
  let toString = t =>
    switch (t) {
    | `phone => "phone"
    | `address => "address"
    | `city => "city"
    | `state => "state"
    | `country => "country"
    | `zipcode => "zipcode"
    };
};

[@bs.val] [@bs.scope "scatter"]
external suggestNetwork : Network.t => Js.Promise.t(bool) = "";

[@bs.val] [@bs.scope "scatter"]
external eos :
  (Network.t, Eos.Config.t => Eos.t, Eos.Config.t, string) => Eos.t =
  "";

[@bs.val] [@bs.scope "scatter"]
external getIdentity_ :
  {
    .
    "accounts": Js.Array.t(Network.t),
    "personal": Js.Array.t(string),
    "location": Js.Array.t(string),
  } =>
  Js.Promise.t(Identity.t) =
  "getIdentity";

let getIdentity =
    (
      ~accounts=?,
      ~personal: option(array(PersonalField.t))=?,
      ~location: option(array(LocationField.t))=?,
      (),
    ) =>
  getIdentity_({
    "accounts": accounts |> Js.Option.getWithDefault([||]),
    "personal":
      personal
      |> Js.Option.getWithDefault([||])
      |> Array.map(PersonalField.toString),
    "location":
      location
      |> Js.Option.getWithDefault([||])
      |> Array.map(LocationField.toString),
  });

/* [@bs.val] [@bs.scope "scatter"] external identity : option(Identity.t) = ""; */
[@bs.val] [@bs.scope "scatter"]
external forgetIdentity : unit => Js.Promise.t(bool) = "";
