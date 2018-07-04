include Server_Database;

let blockByTrxId = (mongo, trxId) =>
  mongo
  |> EosBlocks.collection
  |. Mongo.Collection.find({"block.transactions.trx.id": trxId})
  |. Mongo.Cursor.limit(1)
  |. Mongo.Cursor.next;

/* connect to mongo */
/* listen for changes */
/* on 'create' action, add the new poll to the 'polls' mongo collection */
let onCreateAction = (mongo, trxId, block, data) =>
  Polls.save(
    mongo,
    {
      "id":
        data##poll_creator
        ++ "_"
        ++ data##poll_id
        ++ "_"
        ++ string_of_int(block##block_num),
      "pollId": data##poll_id,
      "pollCreator": data##poll_creator,
      "title": data##title,
      "description": data##description,
      "options": data##options,
      "whitelist": data##whitelist,
      "blacklist": data##blacklist,
      "minChoices": 0,
      "maxChoices": 0,
      "openTime": data##open_time,
      "closeTime": data##close_time,
      "blockId": block##block_id,
      "blockNum": block##block_num,
      "blockTime": block##block##timestamp,
      "trxId": trxId,
      "appLabel": data##app_label,
    },
  );

/* let onCloseAction = (mongo, block, data) =>
   mongo
   |> Polls.find({"creator": data##creator, "id": data##poll_id})
   |. Mongo.Cursor.next
   |> Js.Promise.then_(pollOpt =>
        switch (pollOpt) {
        | Some(poll) => Js.Promise.resolve(poll)
        | None => Js.Promise.reject(Not_found)
        }
      )
      |> Js.Promise.then_(poll =>
      mongo
      |> Polls.collection
      |>
      );  */
let onVoteAction = (mongo, trxId, block, data) =>
  Votes.save(
    mongo,
    {
      "id":
        data##poll_creator
        ++ "_"
        ++ data##poll_id
        ++ "_"
        ++ data##voter
        ++ "_"
        ++ string_of_int(block##block_num),
      "pollId": data##poll_id,
      "pollCreator": data##poll_creator,
      "voter": data##voter,
      "choices": data##choices,
      "blockId": block##block_id,
      "blockNum": block##block_num,
      "blockTime": block##block##timestamp,
      "trxId": trxId,
      "appLabel": data##app_label,
    },
  );

let onCommentAction = (mongo, trxId, block, data) =>
  Comments.save(
    mongo,
    {
      "id":
        data##poll_creator
        ++ "_"
        ++ data##poll_id
        ++ "_"
        ++ data##commenter
        ++ "_"
        ++ string_of_int(block##block_num),
      "pollId": data##poll_id,
      "pollCreator": data##poll_creator,
      "commenter": data##commenter,
      "content": data##content,
      "blockId": block##block_id,
      "blockNum": block##block_num,
      "blockTime": block##block##timestamp,
      "trxId": trxId,
      "appLabel": data##app_label,
    },
  );

let onSettingsAction = (mongo, data) =>
  Settings.save(mongo, {"id": data##account, "account": data##account});

let onActionsChange = (client, change) => {
  let action = change##fullDocument;
  let name = action##name;
  let data =
    action##data
    |> Js.Null_undefined.toOption
    |. Belt.Option.getWithDefault(Js.Json.null);
  let trxId = action##trx_id;
  Js.log3("New action", name, action);
  Js.Global.setTimeout(
    () =>
      blockByTrxId(client, trxId)
      |> Js.Promise.then_(block => {
           let b =
             block
             |> Js.Nullable.toOption
             |> Js.Option.getWithDefault(Model.EosBlock.empty);
           Js.log3("!!!!!! BLOaaCK", trxId, b);
           switch (name) {
           | "create" =>
             data
             |> Model.EosAction.Decode.create
             |> onCreateAction(client, trxId, b)
             |> ignore
           | "vote" =>
             data
             |> Model.EosAction.Decode.vote
             |> onVoteAction(client, trxId, b)
             |> ignore
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

let onBlocksChange = (~mongo, ~logger, change) => {
  let block = change##fullDocument;
  logger |. Winston.info("block change", {"block_num": block##block_num});
  Blocks.save(
    mongo,
    {
      "id": block##block_id,
      "num": block##block_num,
      "time": block##block##timestamp,
    },
  )
  |> ignore;
};

let listenToActions = (~mongo, ~logger) =>
  mongo
  |> EosActions.collection
  |. Mongo.Collection.watch([|
       {
         "$match": {
           "operationType": "insert",
           "fullDocument.account": Env.contractAccount,
         },
       },
     |])
  |. Mongo.ChangeStream.on(`change(onActionsChange(mongo)))
  |> Js.Promise.resolve;

let listenToBlocks = (~mongo, ~logger) =>
  mongo
  |> EosBlocks.collection
  |. Mongo.Collection.watch([|{
                                "$match": {
                                  "operationType": "insert",
                                },
                              }|])
  |. Mongo.ChangeStream.on(`change(onBlocksChange(~mongo, ~logger)))
  |> Js.Promise.resolve;

let start = (~mongo, ~logger) =>
  Js.Promise.all2((
    listenToActions(~mongo, ~logger),
    listenToBlocks(~mongo, ~logger),
  ));
