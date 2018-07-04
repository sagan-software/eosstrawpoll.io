module type T = {type t; let empty: t;};

module Poll = {
  type t = {
    .
    "id": string,
    "pollId": string,
    "pollCreator": string,
    "title": string,
    "description": string,
    "options": array(string),
    "whitelist": array(string),
    "blacklist": array(string),
    "minChoices": int,
    "maxChoices": int,
    "openTime": int,
    "closeTime": int,
    "blockId": string,
    "blockNum": int,
    "blockTime": string,
    "trxId": string,
    "appLabel": string,
  };
  let empty: t = {
    "id": "",
    "pollId": "",
    "pollCreator": "",
    "title": "",
    "description": "",
    "options": [||],
    "whitelist": [||],
    "blacklist": [||],
    "minChoices": 0,
    "maxChoices": 0,
    "openTime": 0,
    "closeTime": 0,
    "blockId": "",
    "blockNum": 0,
    "blockTime": "",
    "trxId": "",
    "appLabel": "",
  };
};

module Vote = {
  type t = {
    .
    "id": string,
    "pollId": string,
    "pollCreator": string,
    "voter": string,
    "choices": array(int),
    "blockId": string,
    "blockNum": int,
    "blockTime": string,
    "trxId": string,
    "appLabel": string,
  };
  let empty: t = {
    "id": "",
    "pollId": "",
    "pollCreator": "",
    "voter": "",
    "choices": [||],
    "blockId": "",
    "blockNum": 0,
    "blockTime": "",
    "trxId": "",
    "appLabel": "",
  };
};

module Comment = {
  type t = {
    .
    "id": string,
    "pollId": string,
    "pollCreator": string,
    "commenter": string,
    "content": string,
    "blockId": string,
    "blockNum": int,
    "blockTime": string,
    "trxId": string,
    "appLabel": string,
  };
  let empty: t = {
    "id": "",
    "pollId": "",
    "pollCreator": "",
    "commenter": "",
    "content": "",
    "blockId": "",
    "blockNum": 0,
    "blockTime": "",
    "trxId": "",
    "appLabel": "",
  };
};

module Settings = {
  type t = {
    .
    "id": string,
    "account": string,
  };
  let empty: t = {"id": "", "account": ""};
};

module Block = {
  type t = {
    .
    "id": string,
    "num": int,
    "time": string,
  };
  let empty: t = {"id": "", "num": 0, "time": ""};
};

module EosAction = {
  type t = {
    .
    "action_num": int,
    "trx_id": string,
    "cfa": bool,
    "account": string,
    "name": string,
    "authorization":
      array(
        {
          .
          "actor": string,
          "permission": string,
        },
      ),
    "hex_data": string,
    "data": Js.Null_undefined.t(Js.Json.t),
  };
  let empty: t = {
    "action_num": 0,
    "trx_id": "",
    "cfa": false,
    "account": "",
    "name": "",
    "authorization": [||],
    "hex_data": "",
    "data": Js.Null_undefined.null,
  };
  module Decode = {
    include Json.Decode;
    let create = j => {
      "poll_creator": j |> field("poll_creator", string),
      "poll_id": j |> field("poll_id", string),
      "title": j |> field("title", string),
      "description": j |> field("description", string),
      "options": j |> field("options", array(string)),
      "whitelist": j |> field("whitelist", array(string)),
      "blacklist": j |> field("blacklist", array(string)),
      "min_choices": j |> field("min_choices", int),
      "max_choices": j |> field("max_choices", int),
      "open_time": j |> field("open_time", int),
      "close_time": j |> field("close_time", int),
      "app_label": j |> field("app_label", string),
    };
    let vote = j => {
      "poll_creator": j |> field("poll_creator", string),
      "poll_id": j |> field("poll_id", string),
      "voter": j |> field("voter", string),
      "choices": j |> field("choices", array(int)),
      "app_label": j |> field("app_label", string),
    };
  };
};

module EosBlock = {
  type t = {
    .
    "block_num": int,
    "block_id": string,
    "irreversible": bool,
    "block": {
      .
      "timestamp": string,
      "producer": string,
      "confirmed": int,
      "previous": string,
      "transaction_mroot": string,
      "action_mroot": string,
      "schedule_version": int,
      "producer_signature": string,
    },
  };
  let empty: t = {
    "block_num": 0,
    "block_id": "",
    "irreversible": false,
    "block": {
      "timestamp": "",
      "producer": "",
      "confirmed": 0,
      "previous": "",
      "transaction_mroot": "",
      "action_mroot": "",
      "schedule_version": 0,
      "producer_signature": "",
    },
  };
};
