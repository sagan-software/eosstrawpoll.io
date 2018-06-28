type pollData = Api.Data.t(Api.Poll.t);

type state = {
  accountName: string,
  pollData,
  choices: Belt.Set.Int.t,
};

type action =
  | ChangePollData(pollData)
  | ToggleChoice(int);

let reducer = (action, state) =>
  switch (action) {
  | ChangePollData(pollData) => ReasonReact.Update({...state, pollData})
  | ToggleChoice(i) =>
    ReasonReact.Update({
      ...state,
      choices:
        Belt.Set.Int.has(state.choices, i) ?
          Belt.Set.Int.remove(state.choices, i) :
          Belt.Set.Int.add(state.choices, i),
    })
  };

let component = ReasonReact.reducerComponent("PollPage");

let eos = Util.loadEosReadOnly();

let renderOption = ({ReasonReact.state, send}, i, option) => {
  Js.log3("choices", state.choices, i);
  let isSelected = Belt.Set.Int.has(state.choices, i);
  let onClick = _e => send(ToggleChoice(i));
  <li key=(string_of_int(i)) onClick>
    (ReasonReact.string(option))
    (
      isSelected ?
        ReasonReact.string("(selected)") : ReasonReact.string("(unselected)")
    )
  </li>;
};

let castVote =
    (
      {ReasonReact.state} as self,
      context: Context.t,
      poll: Api.Poll.t,
      _event,
    ) =>
  switch (context.scatter) {
  | Some(scatter) =>
    Api.Contract.make(scatter)
    |> Js.Promise.then_(contract =>
         Js.Promise.resolve(
           Api.vote(
             contract,
             ~creator=poll.creator,
             ~pollId=poll.id,
             ~voter="alice",
             ~choices=Belt.Set.Int.toArray(self.state.choices),
           ),
         )
       )
    |> Js.Promise.then_(result => {
         Js.log2("Created", result);
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(error => {
         Js.log2("Error voting", error);
         Js.Promise.resolve();
       })
    |> ignore
  | None => Js.log("No scatter")
  };

let renderPoll =
    ({ReasonReact.state} as self, context: Context.t, poll: Api.Poll.t) => {
  let numVoters = Array.length(poll.votes);
  <div>
    <h1> (ReasonReact.string(poll.title)) </h1>
    <p> (ReasonReact.string({j|Voters: $numVoters|j})) </p>
    <ol>
      (poll.options |> Array.mapi(renderOption(self)) |> ReasonReact.array)
    </ol>
    <div>
      <button
        disabled=(context.scatter == None)
        onClick=(castVote(self, context, poll))>
        (ReasonReact.string("Vote"))
      </button>
      <Link route=(Route.PollResults(poll.creator, string_of_int(poll.id)))>
        (ReasonReact.string("Results"))
      </Link>
    </div>
  </div>;
  /* if there is a blacklist, check if the user is on it */
  /* if there is a whitelist, check if the user is on it */
  /* check if user is logged in */
  /* check if scatter is available */
};

let make = (~context: Context.t, ~accountName, ~pollId, _children) => {
  ...component,
  reducer,
  initialState: () => {
    accountName,
    pollData: Api.Data.Loading,
    choices: Belt.Set.Int.empty,
  },
  didMount: ({send}) =>
    pollId
    |> int_of_string
    |> Api.pollById(eos, accountName)
    |> Js.Promise.then_(result => {
         let pollData = Api.Data.fromResult(result);
         send(ChangePollData(pollData));
         Js.log2("got poll data", pollData);
         Js.Promise.resolve();
       })
    |> ignore,
  render: self =>
    switch (self.state.pollData) {
    | Api.Data.NotAsked => ReasonReact.string("")
    | Api.Data.Loading => ReasonReact.string("Loading...")
    | Api.Data.Success(poll) => renderPoll(self, context, poll)
    | Api.Data.Failure(message) => ReasonReact.string(message)
    },
};
