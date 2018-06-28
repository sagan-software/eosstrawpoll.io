module Vote = {
  type t = {
    voter: Eos.accountName,
    choices: array(int),
    holding: Eos.asset,
    time: int,
  };
  let decode = j =>
    Json.Decode.{
      voter: j |> field("voter", Eos.AccountName.decode),
      choices: j |> field("choices", array(int)),
      holding: j |> field("holding", Eos.Asset.decode),
      time: j |> field("time", int),
    };
  let encode = v =>
    Json.Encode.(
      object_([
        ("voter", v.voter |> Eos.AccountName.encode),
        ("choices", v.choices |> Js.Array.map(int) |> jsonArray),
        ("holding", v.holding |> Eos.Asset.encode),
        ("time", v.time |> int),
      ])
    );
};

module Comment = {
  type t = {
    commenter: Eos.accountName,
    content: string,
  };
  let decode = j =>
    Json.Decode.{
      commenter: j |> field("commenter", Eos.AccountName.decode),
      content: j |> field("content", string),
    };
  let encode = c =>
    Json.Encode.(
      object_([
        ("commenter", c.commenter |> Eos.AccountName.encode),
        ("content", c.content |> string),
      ])
    );
};

module Poll = {
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
    createTime: int,
    votes: array(Vote.t),
    comments: array(Comment.t),
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
      createTime: j |> field("create_time", int),
      votes: j |> field("votes", array(Vote.decode)),
      comments: j |> field("comments", array(Comment.decode)),
    };
  let encode = p =>
    Json.Encode.(
      object_([
        ("creator", p.creator |> Eos.AccountName.encode),
        ("title", p.title |> string),
        ("description", p.description |> string),
        ("options", p.options |> Js.Array.map(string) |> jsonArray),
        (
          "whitelist",
          p.whitelist |> Js.Array.map(Eos.AccountName.encode) |> jsonArray,
        ),
        (
          "blacklist",
          p.blacklist |> Js.Array.map(Eos.AccountName.encode) |> jsonArray,
        ),
        ("min_choices", p.minChoices |> int),
        ("max_choices", p.maxChoices |> int),
        ("open_time", p.openTime |> int),
        ("close_time", p.closeTime |> int),
        ("create_time", p.createTime |> int),
        ("votes", p.votes |> Js.Array.map(Vote.encode) |> jsonArray),
        (
          "comments",
          p.comments |> Js.Array.map(Comment.encode) |> jsonArray,
        ),
      ])
    );
};
