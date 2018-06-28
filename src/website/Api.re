module Data = {
  type t('payload) =
    | NotAsked
    | Loading
    | Success('payload)
    | Failure(string);
  let fromResult = result =>
    switch (result) {
    | Belt.Result.Ok(payload) => Success(payload)
    | Belt.Result.Error(message) => Failure(message)
    };
};

module Contract = {
  type t;
  let make = scatter => {
    let eos =
      Scatter.eos(scatter, Env.network, Eos.make, Env.eosConfig, "http");
    Eos.contract(eos, Env.codeName);
  };
  [@bs.send]
  external create :
    (
      t,
      {
        .
        "creator": string,
        "title": string,
        "options": Js.Array.t(string),
        "whitelist": Js.Array.t(string),
        "blacklist": Js.Array.t(string),
        "min_num_choices": int,
        "max_num_choices": int,
        "open_time": int,
        "close_time": int,
      },
      Eos.Action.options
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send]
  external close :
    (
      t,
      {
        .
        "creator": string,
        "poll_id": int,
      },
      Eos.Action.options
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send]
  external destroy :
    (
      t,
      {
        .
        "creator": string,
        "poll_id": int,
      },
      Eos.Action.options
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send]
  external vote :
    (
      t,
      {
        .
        "creator": string,
        "poll_id": int,
        "voter": string,
        "choices": Js.Array.t(int),
      },
      Eos.Action.options
    ) =>
    Js.Promise.t(unit) =
    "";
};

let create =
    (
      contract,
      ~creator,
      ~title,
      ~options,
      ~whitelist=[||],
      ~blacklist=[||],
      ~minNumChoices=0,
      ~maxNumChoices=0,
      ~openTime=0,
      ~closeTime=0,
      (),
    ) =>
  Contract.create(
    contract,
    {
      "creator": creator,
      "title": title,
      "options": options,
      "whitelist": whitelist,
      "blacklist": blacklist,
      "min_num_choices": minNumChoices,
      "max_num_choices": maxNumChoices,
      "open_time": openTime,
      "close_time": closeTime,
    },
    Eos.Action.options(~authorization=[|{j|$creator@active|j}|], ()),
  );

let close = (contract, ~creator, ~pollId) =>
  Contract.close(
    contract,
    {"creator": creator, "poll_id": pollId},
    Eos.Action.options(~authorization=[|{j|$creator@active|j}|], ()),
  );

let destroy = (contract, ~creator, ~pollId) =>
  Contract.close(
    contract,
    {"creator": creator, "poll_id": pollId},
    Eos.Action.options(~authorization=[|{j|$creator@active|j}|], ()),
  );

let vote = (contract, ~creator, ~pollId, ~voter, ~choices) =>
  Contract.vote(
    contract,
    {
      "creator": creator,
      "poll_id": pollId,
      "voter": voter,
      "choices": choices,
    },
    Eos.Action.options(~authorization=[|{j|$voter@active|j}|], ()),
  );

module Vote = {
  type t = {
    voter: string,
    time: int,
    holdings: string,
    choices: array(int),
  };
  let decode = json =>
    Json.Decode.{
      voter: json |> field("voter", string),
      time: json |> field("time", int),
      holdings: json |> field("holdings", string),
      choices: json |> field("choices", array(int)),
    };
};

module VoteRef = {
  type t = {
    id: int,
    pollId: int,
    pollCreator: string,
    pollTitle: string,
    voter: string,
    choices: array(string),
    time: int,
  };
  let decode = j =>
    Json.Decode.{
      id: j |> field("id", int),
      pollId: j |> field("poll_id", int),
      pollCreator: j |> field("poll_creator", string),
      pollTitle: j |> field("poll_title", string),
      voter: j |> field("voter", string),
      choices: j |> field("choices", array(string)),
      time: j |> field("time", int),
    };
};

module Poll = {
  type t = {
    id: int,
    creator: string,
    title: string,
    options: array(string),
    votes: array(Vote.t),
    minNumChoices: int,
    maxNumChoices: int,
    whitelist: array(string),
    blacklist: array(string),
    createTime: int,
    openTime: int,
    closeTime: int,
  };
  let decode = json =>
    Json.Decode.{
      id: json |> field("id", int),
      creator: json |> field("creator", string),
      title: json |> field("title", string),
      options: json |> field("options", array(string)),
      votes: json |> field("votes", array(Vote.decode)),
      minNumChoices: json |> field("min_num_choices", int),
      maxNumChoices: json |> field("max_num_choices", int),
      whitelist: json |> field("whitelist", array(string)),
      blacklist: json |> field("blacklist", array(string)),
      createTime: json |> field("create_time", int),
      openTime: json |> field("open_time", int),
      closeTime: json |> field("close_time", int),
    };
};

module PollRef = {
  type t = {
    id: int,
    pollId: int,
    pollCreator: string,
    title: string,
    options: array(string),
    numVotes: int,
    popularity: string,
    whitelist: array(string),
    blacklist: array(string),
    createTime: int,
    openTime: int,
    closeTime: int,
  };
  let decode = j =>
    Json.Decode.{
      id: j |> field("id", int),
      pollId: j |> field("poll_id", int),
      pollCreator: j |> field("poll_creator", string),
      title: j |> field("title", string),
      options: j |> field("options", array(string)),
      numVotes: j |> field("num_votes", int),
      popularity: j |> field("popularity", string),
      whitelist: j |> field("whitelist", array(string)),
      blacklist: j |> field("blacklist", array(string)),
      createTime: j |> field("create_time", int),
      openTime: j |> field("open_time", int),
      closeTime: j |> field("close_time", int),
    };
};

let polls =
    (
      eos,
      creator,
      ~table="polls",
      ~lowerBound=0,
      ~upperBound=(-1),
      ~limit=50,
      (),
    ) =>
  Eos.getTableRows(
    eos,
    ~json=true,
    ~code=Env.codeName,
    ~scope=creator,
    ~table,
    ~tableKey="id",
    ~lowerBound,
    ~upperBound,
    ~limit,
  )
  |> Js.Promise.then_(result => {
       Js.log2("got poll data", result);
       let data = result |. Eos.TableRows.rows |> Array.map(Poll.decode);
       Js.Promise.resolve(Belt.Result.Ok(data));
     });

let pollRefs =
    (eos, creator, ~table, ~lowerBound=0, ~upperBound=(-1), ~limit=50, ()) =>
  Eos.getTableRows(
    eos,
    ~json=true,
    ~code=Env.codeName,
    ~scope=creator,
    ~table,
    ~tableKey="id",
    ~lowerBound,
    ~upperBound,
    ~limit,
  )
  |> Js.Promise.then_(result => {
       Js.log2("got poll refs data", result);
       let data = result |. Eos.TableRows.rows |> Array.map(PollRef.decode);
       Js.Promise.resolve(Belt.Result.Ok(data));
     });

let pollById = (eos, creator, id) =>
  polls(eos, creator, ~limit=1, ~lowerBound=id, ~upperBound=id + 1, ())
  |> Js.Promise.then_(pollData =>
       Js.Promise.resolve(
         switch (pollData) {
         | Belt.Result.Ok(polls) =>
           switch (Belt.Array.get(polls, 0)) {
           | Some(poll) => Belt.Result.Ok(poll)
           | None => Belt.Result.Error({j|Couldn't find poll with ID "$id"|j})
           }
         | _ => Belt.Result.Error({j|Couldn't find poll with ID "$id"|j})
         },
       )
     );

let voteRefs =
    (eos, creator, ~table, ~lowerBound=0, ~upperBound=(-1), ~limit=50, ()) =>
  Eos.getTableRows(
    eos,
    ~json=true,
    ~code=Env.codeName,
    ~scope=creator,
    ~table,
    ~tableKey="id",
    ~lowerBound,
    ~upperBound,
    ~limit,
  )
  |> Js.Promise.then_(result => {
       Js.log2("got vote refs data", result);
       let data = result |. Eos.TableRows.rows |> Array.map(VoteRef.decode);
       Js.Promise.resolve(Belt.Result.Ok(data));
     });
