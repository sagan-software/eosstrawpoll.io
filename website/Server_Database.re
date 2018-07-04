module type CollectionInfo = {let dbName: string; let collectionName: string;};

module type Collection =
  (M: Model.T, C: CollectionInfo) =>
  {
    let db: Mongo.Client.t => Mongo.Database.t;
    let collection: Mongo.Client.t => Mongo.Collection.t(M.t);
    let findAll: Mongo.Client.t => Mongo.Cursor.t(M.t);
    let find: ('query, Mongo.Client.t) => Mongo.Cursor.t(M.t);
    let channel: string;
    let iterator: GraphQl.PubSub.t => GraphQl.PubSub.asyncIterable;
    let watch: (Mongo.Client.t, GraphQl.PubSub.t, M.t => 'query) => unit;
    let save: (Mongo.Client.t, M.t) => Js.Promise.t(Mongo.WriteOpResult.t);
  };

module MakeCollection: Collection =
  (M: Model.T, C: CollectionInfo) => {
    let db = client => client |. Mongo.Client.db(C.dbName);
    let collection = client =>
      client |> db |. Mongo.Database.collection(C.collectionName);
    let findAll = client => client |> collection |. Mongo.Collection.findAll;
    let countAll = client => client |> findAll |. Mongo.Cursor.count;
    let find = (query, client) =>
      client |> collection |. Mongo.Collection.find(query);
    let channel = C.dbName ++ "/" ++ C.collectionName;
    let iterator = pubsub => pubsub |. GraphQl.PubSub.asyncIterator(channel);
    let watch = (mongo, pubsub, toQuery) =>
      mongo
      |> collection
      |. Mongo.Collection.watchAll
      |. Mongo.ChangeStream.on(
           `change(
             change =>
               change##fullDocument
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
    Model.Poll,
    {
      let dbName = Env.mongoAppDb;
      let collectionName = "polls";
    },
  );

module Votes =
  MakeCollection(
    Model.Vote,
    {
      let dbName = Env.mongoAppDb;
      let collectionName = "votes";
    },
  );

module Comments =
  MakeCollection(
    Model.Comment,
    {
      let dbName = Env.mongoAppDb;
      let collectionName = "comments";
    },
  );

module Blocks = {
  include
    MakeCollection(
      Model.Block,
      {
        let dbName = Env.mongoAppDb;
        let collectionName = "blocks";
      },
    );
  let numPolls = (client, block) =>
    client |> Polls.find({"blockNum": block##num}) |. Mongo.Cursor.count;
};

module Settings =
  MakeCollection(
    Model.Settings,
    {
      let dbName = Env.mongoAppDb;
      let collectionName = "settings";
    },
  );

module EosActions =
  MakeCollection(
    Model.EosAction,
    {
      let dbName = Env.mongoEosDb;
      let collectionName = "actions";
    },
  );

module EosBlocks =
  MakeCollection(
    Model.EosBlock,
    {
      let dbName = Env.mongoEosDb;
      let collectionName = "blocks";
    },
  );
