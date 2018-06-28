type pollData = Api.Data.t(Api.Poll.t);

type state = {
  accountName: string,
  pollData,
};

type action =
  | ChangePollData(pollData);

let reducer = (action, state) =>
  switch (action) {
  | ChangePollData(pollData) => ReasonReact.Update({...state, pollData})
  };

let component = ReasonReact.reducerComponent("PollResultsPage");

let eos = Util.loadEosReadOnly();

let renderOption = (poll, option) =>
  <li>
    <span> (ReasonReact.string(option)) </span>
    <span> (ReasonReact.string("0 Votes")) </span>
    <span> (ReasonReact.string("0%")) </span>
  </li>;

let renderPoll = (poll: Api.Poll.t) =>
  <div>
    <h1> (ReasonReact.string(poll.title)) </h1>
    <ol>
      (poll.options |> Array.map(renderOption(poll)) |> ReasonReact.array)
    </ol>
    <div>
      <Link route=(Route.Poll(poll.creator, string_of_int(poll.id)))>
        (ReasonReact.string("Vote"))
      </Link>
    </div>
  </div>;

/* let results =
   Js.Array.reduce(
     (result, vote: Api.Vote.t) => {
       Js.Array.forEach(
         choice =>
           result[choice] =
             Belt.Option.getWithDefault(Belt.Array.get(result, choice), 0)
             + 1,
         vote.choices,
       );
       result;
     },
     [||],
     poll.votes,
   ); */
let make = (~context: Context.t, ~accountName, ~pollId, _children) => {
  ...component,
  reducer,
  initialState: () => {accountName, pollData: NotAsked},
  didMount: self => {
    self.send(ChangePollData(Api.Data.Loading));
    let id = int_of_string(pollId);
    Api.pollById(eos, accountName, id)
    |> Js.Promise.then_(result => {
         let pollData = Api.Data.fromResult(result);
         self.send(ChangePollData(pollData));
         Js.Promise.resolve();
       })
    |> ignore;
  },
  render: self =>
    switch (self.state.pollData) {
    | Api.Data.NotAsked => ReasonReact.string("")
    | Api.Data.Loading => ReasonReact.string("Loading...")
    | Api.Data.Success(poll) => renderPoll(poll)
    | Api.Data.Failure(message) => ReasonReact.string(message)
    },
};
