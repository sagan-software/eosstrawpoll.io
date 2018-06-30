type uuid = string;

module Create = {
  type t = {
    pollCreator: Eos.accountName,
    pollId: uuid,
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
      pollCreator: j |> field("poll_creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", string),
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
    pollCreator: Eos.accountName,
    pollId: uuid,
  };
  let decode = j =>
    Json.Decode.{
      pollCreator: j |> field("poll_creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", string),
    };
};

module Destroy = {
  type t = {
    pollCreator: Eos.accountName,
    pollId: uuid,
  };
  let decode = j =>
    Json.Decode.{
      pollCreator: j |> field("poll_creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", string),
    };
};

module Vote = {
  type t = {
    pollCreator: Eos.accountName,
    pollId: uuid,
    voter: Eos.accountName,
    choices: array(int),
  };
  let decode = j =>
    Json.Decode.{
      pollCreator: j |> field("poll_creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", string),
      voter: j |> field("voter", Eos.AccountName.decode),
      choices: j |> field("choices", array(int)),
    };
};

module Comment = {
  type t = {
    pollCreator: Eos.accountName,
    pollId: uuid,
    commenter: Eos.accountName,
    content: string,
  };
  let decode = j =>
    Json.Decode.{
      pollCreator: j |> field("poll_creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", string),
      commenter: j |> field("voter", Eos.AccountName.decode),
      content: j |> field("choices", string),
    };
};

module Update = {
  type t = {
    pollCreator: Eos.accountName,
    pollId: uuid,
    newDescription: string,
  };
  let decode = j =>
    Json.Decode.{
      pollCreator: j |> field("poll_creator", Eos.AccountName.decode),
      pollId: j |> field("poll_id", string),
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
