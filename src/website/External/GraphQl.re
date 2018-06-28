module Resolver = {
  type t('out) = (Js.Json.t, Js.Json.t, Js.Json.t, Js.Json.t) => 'out;
};

type resolver('out) = Resolver.t('out);

module PubSub = {
  type t;
  [@bs.module "graphql-subscriptions"] [@bs.new]
  external make : unit => t = "PubSub";
  type asyncIterable;
  [@bs.send] external asyncIterator : (t, string) => asyncIterable = "";
  [@bs.send] external publish : (t, string, 'payload) => unit = "";
};

module Schema = {
  type t;
  [@bs.module "graphql-tools"]
  external make_ :
    {
      .
      "typeDefs": string,
      "resolvers": 'resolvers,
    } =>
    t =
    "makeExecutableSchema";
  let make = (~typeDefs, ~resolvers) =>
    make_({"typeDefs": typeDefs, "resolvers": resolvers});
};

type schema = Schema.t;

type executeT;

[@bs.module "graphql"] [@bs.val] external execute : executeT = "";

type subscribeT;

[@bs.module "graphql"] [@bs.val] external subscribe : subscribeT = "";
