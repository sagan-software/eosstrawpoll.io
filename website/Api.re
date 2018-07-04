module Contract = {
  type t;
  let make = scatter => {
    let eos =
      Scatter.eos(
        scatter,
        Env.scatterNetwork,
        Eos.make,
        Env.eosConfig,
        "http",
      );
    Eos.contract(eos, Env.contractAccount);
  };
  [@bs.send]
  external create :
    (
      t,
      {
        .
        "poll_creator": string,
        "poll_id": string,
        "title": string,
        "description": string,
        "options": Js.Array.t(string),
        "whitelist": Js.Array.t(string),
        "blacklist": Js.Array.t(string),
        "min_choices": int,
        "max_choices": int,
        "open_time": int,
        "close_time": int,
        "app_label": string,
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
        "poll_creator": string,
        "poll_id": int,
        "app_label": string,
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
        "poll_creator": string,
        "poll_id": string,
        "voter": string,
        "choices": Js.Array.t(int),
        "app_label": string,
      },
      Eos.Action.options
    ) =>
    Js.Promise.t(unit) =
    "";
  [@bs.send]
  external comment :
    (
      t,
      {
        .
        "poll_creator": string,
        "poll_id": string,
        "commenter": string,
        "content": string,
        "app_label": string,
      },
      Eos.Action.options
    ) =>
    Js.Promise.t(unit) =
    "";
};

let create =
    (
      contract,
      ~pollCreator,
      ~pollId,
      ~title,
      ~description="",
      ~options,
      ~whitelist=[||],
      ~blacklist=[||],
      ~minChoices=0,
      ~maxChoices=0,
      ~openTime=0,
      ~closeTime=0,
      (),
    ) =>
  Contract.create(
    contract,
    {
      "poll_creator": pollCreator,
      "poll_id": pollId,
      "title": title,
      "description": description,
      "options": options,
      "whitelist": whitelist,
      "blacklist": blacklist,
      "min_choices": minChoices,
      "max_choices": maxChoices,
      "open_time": openTime,
      "close_time": closeTime,
      "app_label": Env.appLabel,
    },
    Eos.Action.options(~authorization=[|{j|$pollCreator@active|j}|], ()),
  );

let close = (contract, ~pollCreator, ~pollId) =>
  Contract.close(
    contract,
    {
      "poll_creator": pollCreator,
      "poll_id": pollId,
      "app_label": Env.appLabel,
    },
    Eos.Action.options(~authorization=[|{j|$pollCreator@active|j}|], ()),
  );

let vote = (contract, ~pollCreator, ~pollId, ~voter, ~choices) =>
  Contract.vote(
    contract,
    {
      "poll_creator": pollCreator,
      "poll_id": pollId,
      "voter": voter,
      "choices": choices,
      "app_label": Env.appLabel,
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
      creator: json |> field("poll_creator", string),
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
