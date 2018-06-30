module type CollectionInfo = {let dbName: string; let collectionName: string;};

module type Collection = {
  include CollectionInfo;
  let db: Mongo.Client.t => Mongo.Database.t;
  let collection: Mongo.Client.t => Mongo.Collection.t;
  let findAll: Mongo.Client.t => Mongo.Cursor.t;
  let find: ('query, Mongo.Client.t) => Mongo.Cursor.t;
  let channel: string;
  let iterator: GraphQl.PubSub.t => GraphQl.PubSub.asyncIterable;
  let watch: (Mongo.Client.t, GraphQl.PubSub.t, 'document => 'query) => unit;
  let save:
    (Mongo.Client.t, 'document) => Js.Promise.t(Mongo.WriteOpResult.t);
};

module MakeCollection = (C: CollectionInfo) : Collection => {
  include C;
  let db = client => client |. Mongo.Client.db(dbName);
  let collection = client =>
    client |> db |. Mongo.Database.collection(collectionName);
  let findAll = client => client |> collection |. Mongo.Collection.findAll;
  let find = (query, client) =>
    client |> collection |. Mongo.Collection.find(query);
  let channel = {j|$dbName/$collectionName|j};
  let iterator = pubsub => pubsub |. GraphQl.PubSub.asyncIterator(channel);
  let watch = (mongo, pubsub, toQuery) =>
    mongo
    |> collection
    |. Mongo.Collection.watchAll
    |. Mongo.ChangeStream.on(
         `change(
           change =>
             change
             |. Mongo.ChangeEvent.fullDocument
             |> toQuery
             |> GraphQl.PubSub.publish(pubsub, channel),
         ),
       )
    |> ignore;
  let save = (mongo, document) =>
    mongo |> collection |. Mongo.Collection.save(document);
};

module Polls =
  MakeCollection(
    {
      let dbName = WebServerEnv.mongoAppDb;
      let collectionName = "polls";
    },
  );

module Votes =
  MakeCollection(
    {
      let dbName = WebServerEnv.mongoAppDb;
      let collectionName = "votes";
    },
  );

module Comments =
  MakeCollection(
    {
      let dbName = WebServerEnv.mongoAppDb;
      let collectionName = "comments";
    },
  );

module Blocks =
  MakeCollection(
    {
      let dbName = WebServerEnv.mongoAppDb;
      let collectionName = "blocks";
    },
  );

module Settings =
  MakeCollection(
    {
      let dbName = WebServerEnv.mongoAppDb;
      let collectionName = "settings";
    },
  );

module Eos = {
  module Actions =
    MakeCollection(
      {
        let dbName = WebServerEnv.mongoEosDb;
        let collectionName = "actions";
      },
    );
  module Blocks =
    MakeCollection(
      {
        let dbName = WebServerEnv.mongoEosDb;
        let collectionName = "blocks";
      },
    );
};
/* module Collection = {
     let get = (db, collection, mongo) =>
       mongo |. Mongo.Client.db(db) |. Mongo.Database.collection(collection);
     let findAll = (collection, _args) =>
       collection |. Mongo.Collection.findAll |. Mongo.Cursor.toArray;
     let findMany = (collection, _args, query) =>
       collection |. Mongo.Collection.find(query) |. Mongo.Cursor.toArray;
     let findOne = (collection, query) =>
       collection |. Mongo.Collection.find(query) |. Mongo.Cursor.next;
   };

   module Polls = {
     let collection = Collection.get(WebServerEnv.mongoAppDb, "polls");
     let findAll = collection |> Collection.findAll;
     let findMany = collection |> Collection.findMany;
     let findOne = collection |> Collection.findOne;
     /* let find = (~creator, ~id, ~version=1, ~mongo) =>
        mongo
        |> collection
        |> Collection.findOne({"creator": creator, "id": id, "version": version}); */
   };















































    */
