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
/* connect to mongo */
/* listen for changes */
/* on 'create' action, add the new poll to the 'polls' mongo collection */
let onCreate = (client, fields: Contract.Create.t) =>
  client
  |. Mongo.Client.db(WebServerEnv.mongoAppDb)
  |. Mongo.Database.collection("polls")
  |. Mongo.Collection.save(
       Data.Poll.encode({
         creator: fields.creator,
         title: fields.title,
         description: fields.description,
         options: fields.options,
         whitelist: fields.whitelist,
         blacklist: fields.whitelist,
         minChoices: fields.minChoices,
         maxChoices: fields.maxChoices,
         openTime: fields.openTime,
         closeTime: fields.closeTime,
         createTime: 0,
         votes: [||],
         comments: [||],
       }),
     )
  |> ignore;

let onChange = (client, change) => {
  let fullDocument = change |. Mongo.ChangeEvent.fullDocument;
  let name = fullDocument |. Eos.Mongo.Action.name;
  let data = fullDocument |. Eos.Mongo.Action.data;
  /* switch (data) {
     | Contract.Action.Create(fields) => Js.log2("Create", fields)
     | Contract.Action.Vote(fields) => Js.log2("Vote", fields)
     | _ => Js.log2("something else", data)
     }; */
  switch (name) {
  | "create" =>
    Js.log2("Create", data |> Contract.Create.decode |> onCreate(client))
  | "vote" => Js.log2("Vote", data |. Contract.Vote.decode)
  | _ => Js.log2("something else", name)
  };
};

/* on 'vote' action, add the vote to the 'votes' mongo collection */
/* on 'destroy' action:

          - mark the poll as deleted in the 'polls' mongo collection
          - mark the poll's votes as deleted in the 'votes' mongo collection
   */
/* on 'close' action, mark the poll as closed in the 'polls' mongo collection */
let listen = () =>
  WebServerEnv.mongoUri
  |> Mongo.Client.make
  |> Js.Promise.then_(client => {
       Js.log("Connected to MongoDB!!!!!!!!!");
       client
       |. Mongo.Client.db(WebServerEnv.mongoEosDb)
       |. Mongo.Database.collection("actions")
       |. Mongo.Collection.watch([|
            Mongo.pipeline(
              ~match=
                Js.Dict.fromList([
                  ("fullDocument.account", WebServerEnv.contractAccount),
                ]),
              (),
            ),
          |])
       |. Mongo.ChangeStream.on(`change(onChange(client)))
       |> Js.Promise.resolve;
     });
/* on 'comment' action, add the comment to the 'comments' mongo collection */
