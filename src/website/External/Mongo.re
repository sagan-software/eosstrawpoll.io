/* http://mongodb.github.io/node-mongodb-native/3.0/api/ */
module ChangeEvent = {
  [@bs.deriving abstract]
  type t('document) = {
    operationType: string,
    fullDocument: 'document,
  };
};

module ChangeStream = {
  type t;
  [@bs.send]
  external on :
    (
      t,
      [@bs.string] [
        | `change(ChangeEvent.t('document) => unit)
        | `close(unit => unit)
        | [@bs.as "end"] `end_(unit => unit)
        | `error(Js.Exn.t => unit)
      ]
    ) =>
    t =
    "";
};

module WriteOpResult = {
  [@bs.deriving abstract]
  type t = {
    ops: array(Js.Json.t),
    result: Js.Json.t,
  };
};

module Cursor = {
  type t;
  [@bs.send] external limit : (t, int) => t = "";
  [@bs.send] external toArray : t => Js.Promise.t(array('document)) = "";
  [@bs.send]
  external next : t => Js.Promise.t(Js.Nullable.t('document)) = "";
  [@bs.send] external sort : (t, 'keyOrList, int) => t = "";
  [@bs.send] external limit : (t, int) => t = "";
};

module Collection = {
  type t;
  [@bs.send] external watch : (t, 'query) => ChangeStream.t = "";
  [@bs.send] external watchAll : t => ChangeStream.t = "watch";
  [@bs.send]
  external save : (t, 'document) => Js.Promise.t(WriteOpResult.t) = "";
  [@bs.send] external find : (t, 'query) => Cursor.t = "";
  [@bs.send] external findAll : t => Cursor.t = "find";
};

module Database = {
  type t;
  [@bs.send] external collection : (t, string) => Collection.t = "";
};

module Client = {
  type t;
  [@bs.module "mongodb"] [@bs.scope "MongoClient"]
  external make : string => Js.Promise.t(t) = "connect";
  [@bs.send] external db : (t, string) => Database.t = "";
};
