/* http://mongodb.github.io/node-mongodb-native/3.0/api/ */
[@bs.deriving abstract]
type pipeline = {
  [@bs.optional] [@bs.as "$match"]
  match: Js.Dict.t(string),
};

module ChangeEvent = {
  [@bs.deriving abstract]
  type t('document) = {
    operationType: string,
    fullDocument: 'document,
  };
};

module ChangeStream = {
  type t('document);
  [@bs.send]
  external on :
    (
      t('document),
      [@bs.string] [
        | `change(ChangeEvent.t('document) => unit)
        | `close(unit => unit)
        | [@bs.as "end"] `end_(unit => unit)
        | `error(Js.Exn.t => unit)
      ]
    ) =>
    t('document) =
    "";
};

module WriteOpResult = {
  [@bs.deriving abstract]
  type t = {
    ops: array(Js.Json.t),
    result: Js.Json.t,
  };
};

module Collection = {
  type t('document);
  [@bs.send]
  external watch :
    (t('document), array(pipeline)) => ChangeStream.t('document) =
    "";
  [@bs.send]
  external save : (t('document), 'document) => Js.Promise.t(WriteOpResult.t) =
    "";
};

module Database = {
  type t;
  [@bs.send]
  external collection : (t, string) => Collection.t('document) = "";
};

module Client = {
  type t;
  [@bs.module "mongodb"] [@bs.scope "MongoClient"]
  external make : string => Js.Promise.t(t) = "connect";
  [@bs.send] external db : (t, string) => Database.t = "";
};
