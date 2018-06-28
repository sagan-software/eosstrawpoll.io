type uuid = int;

module Create = {
  type t = {
    creator: Eos.accountName,
    title: string,
    description: string,
    options: array(string),
    whitelist: array(Eos.accountName),
    blacklist: array(Eos.accountName),
    minChoices: int,
    maxChoices: int,
    openTime: int,
    closeTime: int,
  };
  let decode = j =>
    Json.Decode.{
      creator: j |> field("creator", Eos.AccountName.decode),
      title: j |> field("title", string),
      description: j |> field("description", string),
      options: j |> field("options", array(string)),
      whitelist: j |> field("whitelist", array(Eos.AccountName.decode)),
      blacklist: j |> field("blacklist", array(Eos.AccountName.decode)),
      minChoices: j |> field("min_choices", int),
      maxChoices: j |> field("max_choices", int),
      openTime: j |> field("open_time", int),
      closeTime: j |> field("close_time", int),
    };
};

module Close = {
  type t = {
    creator: Eos.accountName,
    pollId: uuid,
  };
  let decode = j =>
    Json.Decode.{
      creator: j |> field("creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", int),
    };
};

module Destroy = {
  type t = {
    creator: Eos.accountName,
    pollId: uuid,
  };
  let decode = j =>
    Json.Decode.{
      creator: j |> field("creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", int),
    };
};

module Vote = {
  type t = {
    creator: Eos.accountName,
    pollId: uuid,
    voter: Eos.accountName,
    choices: array(int),
  };
  let decode = j =>
    Json.Decode.{
      creator: j |> field("creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", int),
      voter: j |> field("voter", Eos.AccountName.decode),
      choices: j |> field("choices", array(int)),
    };
};

module Comment = {
  type t = {
    creator: Eos.accountName,
    pollId: uuid,
    commenter: Eos.accountName,
    content: string,
  };
  let decode = j =>
    Json.Decode.{
      creator: j |> field("creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", int),
      commenter: j |> field("voter", Eos.AccountName.decode),
      content: j |> field("choices", string),
    };
};

module Update = {
  type t = {
    creator: Eos.accountName,
    pollId: uuid,
    newDescription: string,
  };
  let decode = j =>
    Json.Decode.{
      creator: j |> field("creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", int),
      newDescription: j |> field("choices", string),
    };
};

module Action = {
  type t =
    | Create(Create.t)
    | Destroy(Destroy.t)
    | Vote(Vote.t)
    | Comment(Comment.t)
    | Update(Update.t);
};
