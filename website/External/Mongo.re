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

module AggregationCursor = {
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
};

module AggregationStage = {
  type t;
  /* match */
  external match_ : {. "$match": 'match} => t = "%identity";
  let match = obj => match({"$match": obj});
  /* sample */
  external sample_ : {. "$sample": 'sample} => t = "%identity";
  let sample = obj => sample_({"$sample": obj});
  /* lookup */
  external lookup_ : {. "$lookup": 'lookup} => t = "%identity";
  let lookup = obj => lookup_({"$lookup": obj});
  /* addFields */
  external addFields_ : {. "$addFields": 'fields} => t = "%identity";
  let addFields = obj => addFields_({"$addFields": obj});
  /* pow */
  external pow_ : {. "$pow": ('expr1, 'expr2)} => t = "%identity";
  let pow = (e1, e2) => pow_({"$pow": (e1, e2)});
  /* add */
  external add_ : {. "$add": ('expr1, 'expr2)} => t = "%identity";
  let add = (e1, e2) => add_({"$add": (e1, e2)});
  /* divide */
  external divide_ : {. "$divide": ('expr1, 'expr2)} => t = "%identity";
  let divide = (e1, e2) => divide_({"$divide": (e1, e2)});
  /* subtract */
  external subtract_ : {. "$subtract": ('expr1, 'expr2)} => t = "%identity";
  let subtract = (e1, e2) => subtract_({"$subtract": (e1, e2)});
  /* sort */
  external sort_ : {. "$sort": 'sort} => t = "%identity";
  let sort = obj => sort_({"$sort": obj});
  /* limit */
  external limit_ : {. "$limit": int} => t = "%identity";
  let limit = obj => limit_({"$limit": obj});
  /* gt */
  external gt_ : {. "$gt": float} => t = "%identity";
  let gt = obj => gt_({"$gt": obj});
  /* lt */
  external lt_ : {. "$lt": float} => t = "%identity";
  let lt = obj => lt_({"$lt": obj});
  /* size */
  external size_ : {. "$size": 'size} => t = "%identity";
  let size = obj => size_({"$size": obj});
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
  [@bs.send]
  external updateOne :
    (t('document), 'query, 'update, 'options) =>
    Js.Promise.t(
      {
        .
        "acknowledged": bool,
        "matchedCount": int,
        "modifiedCount": int,
        "upsertedId": Js.Null_undefined.t('objectId),
      },
    ) =
    "";
  [@bs.send]
  external aggregate :
    (t('document), array(AggregationStage.t)) =>
    AggregationCursor.t('document) =
    "";
  [@bs.send]
  external createIndex : (t('document), 'index) => Js.Promise.t(string) = "";
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
