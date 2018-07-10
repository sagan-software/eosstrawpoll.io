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
  external getIdentity_ :
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
    "getIdentity";

  let dispatchEvent = eventName =>
    document
    |> Document.documentElement
    |> Element.asEventTarget
    |> EventTarget.dispatchEvent(Event.make(eventName))
    |> ignore;

  let getIdentity = (t, fields) =>
    t
    |. getIdentity_(fields)
    |> Js.Promise.then_(identity => {
         dispatchEvent("scatterLogin");
         Js.Promise.resolve(identity);
       });

  [@bs.send]
  external forgetIdentity_ : t => Js.Promise.t(bool) = "forgetIdentity";

  let forgetIdentity = t =>
    t
    |. forgetIdentity_
    |> Js.Promise.then_(loggedOut => {
         dispatchEvent("scatterLogout");
         Js.Promise.resolve(loggedOut);
       });

  [@bs.get] [@bs.return nullable]
  external identity : t => option(Identity.t) = "";

  let accountName = t =>
    t
    |> identity
    |> Js.Option.andThen((. identity) =>
         identity |. Identity.accounts |. Belt.Array.get(0)
       )
    |. Belt.Option.map(Account.name);
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

let accountName = Instance.accountName;

[@bs.val] [@bs.scope "window"] [@bs.return nullable]
external instance : option(t) = "scatter";

let onLoad = callback =>
  Document.addEventListener("scatterLoaded", callback, document);

let onLogin = callback =>
  document
  |> Document.documentElement
  |> Element.asEventTarget
  |> EventTarget.addEventListener("scatterLogin", callback);

let onLogout = callback =>
  document
  |> Document.documentElement
  |> Element.asEventTarget
  |> EventTarget.addEventListener("scatterLogout", callback);
