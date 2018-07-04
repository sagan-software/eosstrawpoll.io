/* http://mongodb.github.io/node-mongodb-native/3.0/api/ */
module ChangeEvent = {
  type t('document) = {
    .
    "operationType": string,
    "fullDocument": 'document,
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

module Cursor = {
  type t('document);
  [@bs.send] external limit : (t('document), int) => t('document) = "";
  [@bs.send]
  external toArray : t('document) => Js.Promise.t(array('document)) = "";
  [@bs.send]
  external next : t('document) => Js.Promise.t(Js.Nullable.t('document)) =
    "";
  [@bs.send]
  external sort : (t('document), 'keyOrList, int) => t('document) = "";
  [@bs.send] external limit : (t('document), int) => t('document) = "";
  [@bs.send] external count : t('document) => Js.Promise.t(int) = "";
};

module Collection = {
  type t('document);
  [@bs.send]
  external watch : (t('document), 'query) => ChangeStream.t('document) = "";
  [@bs.send]
  external watchAll : t('document) => ChangeStream.t('document) = "watch";
  [@bs.send]
  external save : (t('document), 'document) => Js.Promise.t(WriteOpResult.t) =
    "";
  [@bs.send]
  external find : (t('document), 'query) => Cursor.t('document) = "";
  [@bs.send] external findAll : t('document) => Cursor.t('document) = "find";
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
