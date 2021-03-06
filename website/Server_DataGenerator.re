module Db = Server_Database;

let pollTitles = [|
  "What is your favorite color?",
  "How much RAM should be added with every block?",
  "Is RAM overpriced?",
  "What should the EOS Straw Poll team be working on?",
  "What will the price of EOS be at the end of 2018?",
  "The solution to RAM?",
  "What is your age?",
  "What is your gender?",
  "What is your favorite digital camera brand?",
  "What matters most to you when voting for BPs?",
  "How did you hear about EOS Straw Poll?",
  "What do you do for a living?",
  "What kind of dApps are you looking forward to???",
  "what is love",
|];

let accounts =
  Env.devAccounts
  |> Js.String.split(",")
  |. Belt.Array.map(a => String.trim(a))
  |> Js.Array.filter(a => a != "");

let choose = (array, d) =>
  array
  |. Belt.Array.length
  |. Random.int
  |> Belt.Array.get(array)
  |. Belt.Option.getWithDefault(d);

let chooseAccount = () => choose(accounts, "alice");

let generatePoll = (~contract, ~logger) => {
  logger |. Winston.debug("generating poll...", ());
  let title = choose(pollTitles, "");
  let options =
    Belt.Array.range(1, 15 |. Random.int |. max(2))
    |. Belt.Array.map(i => {j|Choice #$i|j});
  let numOptions = Belt.Array.length(options);
  let minChoices = 1 + Random.int(numOptions);
  let maxChoices = minChoices + Random.int(numOptions - minChoices + 1);
  let openTime = (Js.Date.now() /. 1000. |> truncate) + 10 + Random.int(120);
  let closeTime = openTime + 60 + Random.int(60 * 60 * 24);
  let pollCreator = chooseAccount();
  let poll = {
    "poll_creator": pollCreator,
    "poll_name": Eos.Name.random(),
    "title": title,
    "description": "",
    "options": options,
    "whitelist": [||],
    "blacklist": [||],
    "min_choices": minChoices,
    "max_choices": maxChoices,
    "open_time": openTime,
    "close_time": closeTime,
    "metadata": Env.metadata,
  };
  Contract.create(
    contract,
    poll,
    {"authorization": [|{j|$pollCreator@active|j}|]},
  )
  |> Js.Promise.then_(() =>
       logger |. Winston.debug("generated poll", poll) |. Js.Promise.resolve
     )
  |> Js.Promise.catch(_e =>
       logger
       |. Winston.error("error generating poll", poll)
       |. Js.Promise.resolve
     );
};

let getRandomPoll = mongo =>
  mongo
  |. Db.Polls.collection
  |. Mongo.Collection.aggregate([|
       Mongo.AggregationStage.match({
         "openTime": {
           "$lt": Js.Date.now() /. 1000. |. truncate,
         },
         "closeTime": {
           "$gt": Js.Date.now() /. 1000. |. truncate,
         },
       }),
       Mongo.AggregationStage.sample({"size": 1}),
     |])
  |. Mongo.AggregationCursor.next
  |> Js.Promise.then_(poll =>
       poll |> Js.Nullable.toOption |> Js.Promise.resolve
     );

let generateVote = (~contract, ~mongo, ~logger) =>
  mongo
  |> getRandomPoll
  |> Js.Promise.then_(poll =>
       switch (poll) {
       | Some(poll) =>
         logger |. Winston.debug("generating vote...", {"pollId": poll##id});
         let voter = chooseAccount();
         let choices = [||];
         let numChoices =
           poll##minChoices == 0 ?
             1 :
             poll##minChoices
             + Random.int(poll##maxChoices - poll##minChoices + 1);
         while (choices |. Belt.Array.length < numChoices) {
           let choice = Random.int(poll##options |. Belt.Array.length);
           if (choice |. Js.Array.includes(choices) |. (!)) {
             choices |> Js.Array.push(choice) |> ignore;
           };
         };
         let vote = {
           "poll_creator": poll##pollCreator,
           "poll_name": poll##pollName,
           "voter": voter,
           "choices": choices,
           "metadata": Env.metadata,
         };
         Contract.vote(
           contract,
           vote,
           {"authorization": [|{j|$voter@active|j}|]},
         )
         |> Js.Promise.then_(() =>
              logger
              |. Winston.debug("generated vote", vote)
              |. Js.Promise.resolve
            )
         |> Js.Promise.catch(_e =>
              logger
              |. Winston.error(
                   "error generating vote",
                   {"vote": vote, "poll": poll},
                 )
              |. Js.Promise.resolve
            );
       | None =>
         logger
         |. Winston.warn(
              "couldn't generate vote because no polls were found",
              (),
            )
         |. Js.Promise.resolve
       }
     );

let generateComment = (~contract, ~mongo, ~logger) =>
  mongo
  |> getRandomPoll
  |> Js.Promise.then_(poll =>
       switch (poll) {
       | Some(poll) =>
         logger
         |. Winston.debug("generating comment...", {"pollId": poll##id});
         let comment = {
           "poll_creator": poll##pollCreator,
           "poll_name": poll##pollName,
           "commenter": "bob",
           "content": "this is a comment",
           "metadata": Env.metadata,
         };
         Contract.comment(
           contract,
           comment,
           {"authorization": [|"bob@active"|]},
         )
         |> Js.Promise.then_(() =>
              logger
              |. Winston.debug("generated comment", comment)
              |. Js.Promise.resolve
            )
         |> Js.Promise.catch(_e =>
              logger
              |. Winston.error(
                   "error generating comment",
                   {"comment": comment, "poll": poll},
                 )
              |. Js.Promise.resolve
            );
       | None =>
         logger
         |. Winston.warn(
              "couldn't generate comment because no polls were found",
              (),
            )
         |. Js.Promise.resolve
       }
     );

let startGenerating = (minSeconds, maxSeconds, fn) => {
  let rec generate = () =>
    Js.Global.setTimeout(
      () => {
        fn() |> ignore;
        generate() |> ignore;
      },
      minSeconds + Random.int(maxSeconds) * 1000,
    );
  generate() |> ignore;
};

let startGeneratingPolls = (~contract, ~logger) =>
  startGenerating(90, 120, () => generatePoll(~contract, ~logger) |> ignore);

let startGeneratingVotes = (~contract, ~mongo, ~logger) =>
  startGenerating(1, 10, () =>
    generateVote(~contract, ~mongo, ~logger) |> ignore
  );

let startGeneratingComments = (~contract, ~mongo, ~logger) =>
  startGenerating(15, 120, () =>
    generateComment(~contract, ~mongo, ~logger) |> ignore
  );

let seed = (~contract, ~mongo, ~logger) =>
  Js.Promise.all([|generatePoll(~contract, ~logger)|])
  |> Js.Promise.then_(_result => {
       logger |. Winston.info("done creating initial polls", ());
       let votes =
         1
         |> Belt.Array.range(0)
         |> Js.Array.map(_i => generateVote(~contract, ~mongo, ~logger));
       let comments =
         1
         |> Belt.Array.range(0)
         |> Js.Array.map(_i => generateComment(~contract, ~mongo, ~logger));
       Js.Array.concat(votes, comments) |> Js.Promise.all;
     });

let start = (~mongo, ~logger) =>
  Eos.Config.t(
    ~httpEndpoint=Env.eosUrl,
    ~verbose=false,
    ~keyProvider=[|Env.devPrivKey|],
    (),
  )
  |. Eos.make
  |. Contract.fromEos
  |> Js.Promise.then_(contract => {
       logger |. Winston.info("seeding...", ());
       seed(~contract, ~mongo, ~logger)
       |> Js.Promise.then_(_r =>
            Js.Promise.make((~resolve, ~reject as _) =>
              Js.Global.setTimeout(() => resolve(. contract), 5 * 1000)
              |> ignore
            )
          );
     })
  |> Js.Promise.then_(contract => {
       logger |. Winston.info("starting to generate fake data", ());
       startGeneratingPolls(~contract, ~logger);
       startGeneratingVotes(~contract, ~mongo, ~logger);
       startGeneratingComments(~contract, ~mongo, ~logger);
       Js.Promise.resolve();
     });
