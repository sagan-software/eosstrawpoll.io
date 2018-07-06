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
    "metadata": string,
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
    "metadata": "",
  };
};

module Vote = {
  type t = {
    .
    "id": string,
    "pollRef": string,
    "pollId": string,
    "pollCreator": string,
    "voter": string,
    "choices": array(int),
    "blockId": string,
    "blockNum": int,
    "blockTime": string,
    "trxId": string,
    "metadata": string,
  };
  let empty: t = {
    "id": "",
    "pollRef": "",
    "pollId": "",
    "pollCreator": "",
    "voter": "",
    "choices": [||],
    "blockId": "",
    "blockNum": 0,
    "blockTime": "",
    "trxId": "",
    "metadata": "",
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
    "metadata": string,
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
    "metadata": "",
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
    "numPolls": int,
    "numCloses": int,
    "numVotes": int,
    "numComments": int,
    "numReactions": int,
    "numDonations": int,
  };
  let empty: t = {
    "id": "",
    "num": 0,
    "time": "",
    "numPolls": 0,
    "numCloses": 0,
    "numVotes": 0,
    "numComments": 0,
    "numReactions": 0,
    "numDonations": 0,
  };
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
  type create = {
    .
    "poll_creator": string,
    "poll_id": string,
    "title": string,
    "description": string,
    "options": array(string),
    "whitelist": array(string),
    "blacklist": array(string),
    "min_choices": int,
    "max_choices": int,
    "open_time": int,
    "close_time": int,
    "metadata": string,
  };
  external asCreate : Js.Json.t => create = "%identity";
  type close = {
    .
    "poll_creator": string,
    "poll_id": int,
    "metadata": string,
  };
  external asClose : Js.Json.t => close = "%identity";
  type vote = {
    .
    "poll_creator": string,
    "poll_id": string,
    "voter": string,
    "choices": array(int),
    "metadata": string,
  };
  external asVote : Js.Json.t => vote = "%identity";
  type comment = {
    .
    "poll_creator": string,
    "poll_id": string,
    "commenter": string,
    "content": string,
    "metadata": string,
  };
  external asComment : Js.Json.t => comment = "%identity";
  type data =
    | Create(create)
    | Close(close)
    | Vote(vote)
    | Comment(comment);
  let getData = action =>
    if (action##account == Env.contractAccount) {
      switch (action##name, action##data |. Js.Nullable.toOption) {
      | ("create", Some(data)) => data |. asCreate |. Create |. Some
      | ("close", Some(data)) => data |. asClose |. Close |. Some
      | ("vote", Some(data)) => data |. asVote |. Vote |. Some
      | ("comment", Some(data)) => data |. asComment |. Comment |. Some
      | _ => None
      };
    } else {
      None;
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
      "transactions":
        array(
          {
            .
            "status": string,
            "cpu_usage_us": int,
            "net_usage_words": int,
            "trx": {
              .
              "id": string,
              "signatures": array(string),
              "compression": string,
              "packed_context_free_data": string,
              "context_free_data": string,
              "packed_trx": string,
              "transaction": {
                .
                "expiration": string,
                "ref_block_num": int,
                "max_net_usage_words": int,
                "max_cpu_usage_ms": int,
                "delay_sec": int,
                "actions":
                  array(
                    {
                      .
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
                      "data": string,
                    },
                  ),
              },
            },
          },
        ),
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
      "transactions": [||],
    },
  };
};
