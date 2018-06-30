/*

 website_1       | CHANGED: { _id:                                                                         website_1       |    { _data:
 website_1       |       Binary {                                                                          website_1       |         _bsontype: 'Binary',
 website_1       |         sub_type: 0,                                                                    website_1       |         position: 49,
 website_1       |         buffer:                                                                         website_1       |          <Buffer 82 5b 33 ab f5 00 00 00 12 46 64 5f 69 64 00 64 5b 33 ab f5 b6 d4 5f 00
  01 11 e4 86 00 5a 10 04 f9 43 64 a2 ef c1 43 6c a9 43 f5 e4 19 ec fb 77 04> } },                         website_1       |   operationType: 'insert',
 website_1       |   fullDocument:                                                                         website_1       |    { _id: 5b33abf5b6d45f000111e486,
 website_1       |      action_num: 0,                                                                     website_1       |      trx_id:
 website_1       |       'd516c8b7c507d9109ac967cbf414401e2ccf2dddba574d3e46535aca634e3c10',               website_1       |      cfa: false,
 website_1       |      account: 'eosstrawpoll',                                                           website_1       |      name: 'create',
 website_1       |      authorization: [ [Object] ],                                                       website_1       |      data:
 website_1       |       { creator: 'carol',                                                               website_1       |         title: 'Nice poll title 2',
 website_1       |         description: 'Description D',                                                   website_1       |         options: [Array],
 website_1       |         whitelist: [],                                                                  website_1       |         blacklist: [],
 website_1       |         min_choices: 0,                                                                 website_1       |         max_choices: 0,
 website_1       |         open_time: 0,                                                                   website_1       |         close_time: 0 } },
 website_1       |   ns: { db: 'EOS', coll: 'actions' },
 */
let blockByTrxId = (mongo, trxId) =>
  mongo
  |> Db.Eos.Blocks.collection
  |. Mongo.Collection.find({"block.transactions.trx.id": trxId})
  |. Mongo.Cursor.limit(1)
  |. Mongo.Cursor.next;

/* connect to mongo */
/* listen for changes */
/* on 'create' action, add the new poll to the 'polls' mongo collection */
let onCreateAction = (mongo, trxId, block, fields) =>
  mongo
  |. Db.Polls.save({
       "id":
         fields##poll_creator
         ++ "_"
         ++ fields##poll_id
         ++ "_"
         ++ string_of_int(block##block_num),
       "pollId": fields##poll_id,
       "pollCreator": fields##poll_creator,
       "version": 1,
       "title": fields##title,
       "description": fields##description,
       "options": fields##options,
       "whitelist": fields##whitelist,
       "blacklist": fields##blacklist,
       "openTime": fields##open_time,
       "closeTime": fields##close_time,
       "blockId": block##block_id,
       "blockNum": block##block_num,
       "blockTime": block##block##timestamp,
       "trxId": trxId,
       "appLabel": fields##app_label,
     });

/* let onCloseAction = (mongo, block, fields) =>
   mongo
   |> Db.Polls.find({"creator": fields##creator, "id": fields##poll_id})
   |. Mongo.Cursor.next
   |> Js.Promise.then_(pollOpt =>
        switch (pollOpt) {
        | Some(poll) => Js.Promise.resolve(poll)
        | None => Js.Promise.reject(Not_found)
        }
      )
      |> Js.Promise.then_(poll =>
      mongo
      |> Db.Polls.collection
      |>
      ); */
let onVoteAction = (mongo, trxId, block, fields) =>
  mongo
  |. Db.Votes.save({
       "id":
         fields##poll_creator
         ++ "_"
         ++ fields##poll_id
         ++ "_"
         ++ fields##voter
         ++ "_"
         ++ string_of_int(block##block_num),
       "pollId": fields##poll_id,
       "pollCreator": fields##poll_creator,
       "pollVersion": 1,
       "voter": fields##voter,
       "choices": fields##choices,
       "blockId": block##block_id,
       "blockNum": block##block_num,
       "blockTime": block##block##timestamp,
       "trxId": trxId,
       "appLabel": fields##app_label,
     });

let onCommentAction = (mongo, trxId, block, fields) =>
  mongo
  |. Db.Comments.save({
       "id":
         fields##poll_creator
         ++ "_"
         ++ fields##poll_id
         ++ "_"
         ++ fields##commenter
         ++ "_"
         ++ string_of_int(block##block_num),
       "pollId": fields##poll_id,
       "pollCreator": fields##poll_creator,
       "pollVersion": 1,
       "commenter": fields##commenter,
       "content": fields##content,
       "blockId": block##block_id,
       "blockNum": block##block_num,
       "blockTime": block##block##timestamp,
       "trxId": trxId,
       "appLabel": fields##app_label,
     });

/* let onSettingsAction = (mongo, fields) =>
   mongo
   |. Db.Settings.save({
         "pollId": fields##poll_id,
         "pollCreator": fields##poll_creator,
         "pollVersion": 1,
         "commenter": fields##commenter,
         "content": fields##content,
         "blockId": block##block_id,
         "blockNum": block##block_num,
         "blockTime": block##block##timestamp,
         "trxId": trxId,
         "appLabel": fields##app_label,
       }); */
let onActionsChange = (client, change) => {
  let fullDocument = change |. Mongo.ChangeEvent.fullDocument;
  let name = fullDocument |. Eos.Mongo.Action.name;
  let data = fullDocument |. Eos.Mongo.Action.data;
  let trxId = fullDocument |. Eos.Mongo.Action.trxId;
  Js.log3("New action", name, fullDocument);
  /* switch (data) {
     | Contract.Action.Create(fields) => Js.log2("Create", fields)
     | Contract.Action.Vote(fields) => Js.log2("Vote", fields)
     | _ => Js.log2("something else", data)
     }; */
  Js.Global.setTimeout(
    () =>
      blockByTrxId(client, trxId)
      |> Js.Promise.then_(block => {
           let b =
             block
             |> Js.Nullable.toOption
             |> Js.Option.getWithDefault({
                  "block_num": (-1),
                  "block_id": "",
                  "block": {
                    "timestamp": "",
                  },
                });
           Js.log3("!!!!!! BLOaaCK", trxId, b);
           switch (name) {
           | "create" => data |> onCreateAction(client, trxId, b) |> ignore
           /* | "close" => data |> onCloseAction(client, trxId, b) |> ignore */
           | "vote" => data |> onVoteAction(client, trxId, b) |> ignore
           | _ => Js.log2("unknown action:", name)
           };
           Js.Promise.resolve();
         })
      |> Js.Promise.catch(e => {
           Js.log2("Error getting block ", e);
           Js.Promise.resolve();
         })
      |> ignore,
    750,
  )
  |> ignore;
};

let onBlocksChange = (mongo, change) => {
  let block = change |. Mongo.ChangeEvent.fullDocument;
  Js.log2("block change", block##block_num);
  mongo
  |. Db.Blocks.save({
       "id": block##block_id,
       "num": block##block_num,
       "time": block##block##timestamp,
     })
  |> ignore;
};

/* on 'vote' action, add the vote to the 'votes' mongo collection */
/* on 'destroy' action:

          - mark the poll as deleted in the 'polls' mongo collection
          - mark the poll's votes as deleted in the 'votes' mongo collection
   */
/* on 'close' action, mark the poll as closed in the 'polls' mongo collection */
let listenToActions = mongo =>
  mongo
  |> Db.Eos.Actions.collection
  |. Mongo.Collection.watch([|
       {
         "$match": {
           "operationType": "insert",
           "fullDocument.account": WebServerEnv.contractAccount,
         },
       },
     |])
  |. Mongo.ChangeStream.on(`change(onActionsChange(mongo)))
  |> Js.Promise.resolve;

let listenToBlocks = mongo =>
  mongo
  |> Db.Eos.Blocks.collection
  |. Mongo.Collection.watch([|{
                                "$match": {
                                  "operationType": "insert",
                                },
                              }|])
  |. Mongo.ChangeStream.on(`change(onBlocksChange(mongo)))
  |> Js.Promise.resolve;

let listen = mongo =>
  Js.Promise.all2((listenToActions(mongo), listenToBlocks(mongo)));
