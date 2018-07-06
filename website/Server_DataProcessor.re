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
let onCreateAction = (~mongo, ~logger, ~trxId, ~block, data) => {
  let id =
    data##poll_creator
    ++ "_"
    ++ data##poll_id
    ++ "_"
    ++ string_of_int(block##block_num);
  let poll = {
    "id": id,
    "pollId": data##poll_id,
    "pollCreator": data##poll_creator,
    "title": data##title,
    "description": data##description,
    "options": data##options,
    "whitelist": data##whitelist,
    "blacklist": data##blacklist,
    "minChoices": data##min_choices,
    "maxChoices": data##max_choices,
    "openTime": data##open_time,
    "closeTime": data##close_time,
    "blockId": block##block_id,
    "blockNum": block##block_num,
    "blockTime": block##block##timestamp,
    "trxId": trxId,
    "metadata": data##metadata,
  };
  mongo
  |. Polls.save(poll)
  |> Js.Promise.then_(_result =>
       logger |. Winston.info("saved poll", {"id": id}) |. Js.Promise.resolve
     )
  |> Js.Promise.catch(error =>
       logger
       |. Winston.error("error saving vote", {"error": error, "poll": poll})
       |. Js.Promise.resolve
     );
};

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
let onVoteAction = (~mongo, ~logger, ~trxId, ~block, data) =>
  mongo
  |> Polls.find({"pollId": data##poll_id, "pollCreator": data##poll_creator})
  |. Mongo.Cursor.sort("blockTime", -1)
  |. Mongo.Cursor.next
  |> Js.Promise.then_(poll =>
       switch (poll |> Js.Null_undefined.toOption) {
       | Some(poll) =>
         let id = poll##id ++ "_" ++ data##voter;
         let vote = {
           "id": id,
           "pollRef": poll##id,
           "pollId": data##poll_id,
           "pollCreator": data##poll_creator,
           "voter": data##voter,
           "choices": data##choices,
           "blockId": block##block_id,
           "blockNum": block##block_num,
           "blockTime": block##block##timestamp,
           "trxId": trxId,
           "metadata": data##metadata,
         };
         mongo
         |. Votes.collection
         |. Mongo.Collection.updateOne(
              {"id": id},
              {"$set": vote},
              {"upsert": true},
            )
         |> Js.Promise.then_(_result =>
              logger
              |. Winston.info(
                   "saved vote",
                   {"blockNum": block##block_num, "id": id},
                 )
              |. Js.Promise.resolve
            )
         |> Js.Promise.catch(error =>
              logger
              |. Winston.error(
                   "error saving vote",
                   {"error": error, "vote": vote},
                 )
              |. Js.Promise.resolve
            );
       | None =>
         logger
         |. Winston.warn(
              "couldn't find poll for vote",
              {"pollId": data##poll_id, "pollCreator": data##poll_creator},
            )
         |. Js.Promise.resolve
       }
     );

let onCommentAction = (~mongo, ~logger, ~trxId, ~block, data) => {
  let id =
    data##poll_creator
    ++ "_"
    ++ data##poll_id
    ++ "_"
    ++ data##commenter
    ++ "_"
    ++ string_of_int(block##block_num);
  let comment = {
    "id": id,
    "pollId": data##poll_id,
    "pollCreator": data##poll_creator,
    "commenter": data##commenter,
    "content": data##content,
    "blockId": block##block_id,
    "blockNum": block##block_num,
    "blockTime": block##block##timestamp,
    "trxId": trxId,
    "metadata": data##metadata,
  };
  mongo
  |. Comments.save(comment)
  |> Js.Promise.then_(_result =>
       logger
       |. Winston.info(
            "saved comment",
            {"blockNum": block##block_num, "id": id},
          )
       |. Js.Promise.resolve
     )
  |> Js.Promise.catch(error =>
       logger
       |. Winston.error(
            "error saving comment",
            {"error": error, "comment": comment},
          )
       |. Js.Promise.resolve
     );
};

let onSettingsAction = (~mongo, ~logger, data) =>
  mongo
  |. Settings.collection
  |. Mongo.Collection.updateOne(
       {"id": data##account},
       {
         "$set": {
           "id": data##account,
           "account": data##account,
         },
       },
       {"upsert": true},
     );

let onActionsChange = (~mongo, ~logger, change) => {
  let action = change##fullDocument;
  let data = Model.EosAction.getData(action);
  let trxId = action##trx_id;
  logger
  |. Winston.debug(
       "new action",
       {"account": action##account, "name": action##name},
     );
  Js.Global.setTimeout(
    () =>
      blockByTrxId(mongo, trxId)
      |> Js.Promise.then_(block => {
           switch (block |. Js.Nullable.toOption, data) {
           | (Some(block), Some(Model.EosAction.Create(data))) =>
             data |> onCreateAction(~mongo, ~logger, ~trxId, ~block) |> ignore
           | (Some(block), Some(Model.EosAction.Vote(data))) =>
             data |> onVoteAction(~mongo, ~logger, ~trxId, ~block) |> ignore
           | (Some(block), Some(Model.EosAction.Comment(data))) =>
             data
             |> onCommentAction(~mongo, ~logger, ~trxId, ~block)
             |> ignore
           | _ =>
             if (action##account == Env.contractAccount) {
               logger
               |. Winston.warn(
                    "unhandled action from our contract's account",
                    {"action": action},
                  );
             }
           };
           Js.Promise.resolve();
         })
      |> Js.Promise.catch(error => {
           logger
           |. Winston.error(
                "error getting block for action change",
                {"error": error, "action": action},
              );
           Js.Promise.resolve();
         })
      |> ignore,
    750,
  )
  |> ignore;
};

let start = (~mongo, ~logger) =>
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
  |. Mongo.ChangeStream.on(`change(onActionsChange(~mongo, ~logger)))
  |> Js.Promise.resolve;
