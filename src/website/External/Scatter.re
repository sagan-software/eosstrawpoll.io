open Webapi.Dom;

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

module Instance = {
  type t;
  [@bs.send]
  external suggestNetwork : (t, Network.t) => Js.Promise.t(bool) = "";
  [@bs.send]
  external eos :
    (t, Network.t, Eos.Config.t => Eos.t, Eos.Config.t, string) => Eos.t =
    "";
  [@bs.send]
  external getIdentity :
    (
      t,
      {
        .
        "accounts": array(Network.t),
        "personal": array(string),
        "location": array(string),
      }
    ) =>
    Js.Promise.t(Identity.t) =
    "";
  [@bs.get] [@bs.return nullable]
  external identity : t => option(Identity.t) = "";
  [@bs.send] external forgetIdentity : t => Js.Promise.t(bool) = "";
};

type t = Instance.t;

let suggestNetwork = Instance.suggestNetwork;

let eos = Instance.eos;

let getIdentity =
    (instance, ~accounts=[||], ~personal=[||], ~location=[||], ()) =>
  Instance.getIdentity(
    instance,
    {
      "accounts": accounts,
      "personal": personal |> Array.map(PersonalField.toString),
      "location": location |> Array.map(LocationField.toString),
    },
  );

let identity = Instance.identity;

let forgetIdentity = Instance.forgetIdentity;

[@bs.val] [@bs.scope "window"] [@bs.return nullable]
external instance : option(t) = "scatter";

let onLoad = callback =>
  Document.addEventListener("scatterLoaded", callback, document);
