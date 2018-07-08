module PollData = [%graphql
  {|
query pollData($creator: String!, $id: String!) {
  poll(creator:$creator,id:$id) {
    id
    pollName
    pollCreator
    title
    description
    options
    whitelist
    blacklist
    minChoices
    maxChoices
    openTime
    closeTime
    blockId
    blockNum
    blockTime
    trxId
    metadata
    votes {
      id
      voter
      voterStaked
      choices
      blockNum
      blockTime
      trxId
      metadata
    }
    comments {
      id
      commenter
      content
      blockTime
      trxId
      metadata
    }
  }
}
|}
];

module PollDataQuery = ReasonApollo.CreateQuery(PollData);

type state = {choices: Belt.Set.Int.t};

type action =
  | ToggleChoice(int);

let reducer = (action, state) =>
  switch (action) {
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

let renderOption = ({ReasonReact.state, send}, vote, i: int, option) => {
  let isSelected =
    Belt.Set.Int.has(state.choices, i)
    || vote
    |> Js.Option.map((. vote) => Js.Array.includes(i, vote##choices))
    |> Js.Option.getWithDefault(false);
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
    ({ReasonReact.state} as self, context: Context.t, poll, _event) =>
  switch (context.scatter) {
  | Some(scatter) =>
    scatter
    |> Contract.fromScatter
    |> Js.Promise.then_(contract =>
         contract
         |. Contract.vote(
              {
                "poll_creator": poll##pollCreator,
                "poll_name": poll##pollName,
                "voter": "alice",
                "choices": Belt.Set.Int.toArray(self.state.choices),
                "metadata": Env.metadata,
              },
              {"authorization": [|"alice@active"|]},
            )
       )
    |> Js.Promise.then_(result => {
         Js.log2("Created", result);
         Route.redirectTo(
           Route.PollResults(poll##pollCreator, poll##pollName),
         );
         Js.Promise.resolve();
       })
    |> Js.Promise.catch(error => {
         Js.log2("Error voting", error);
         Js.Promise.resolve();
       })
    |> ignore
  | None => Js.log("No scatter")
  };

let getVote = (context, poll) =>
  context
  |. Context.accountName
  |> Js.Option.andThen((. accountName) =>
       poll##votes
       |> Js.Array.filter(v => v##voter == accountName)
       |. Belt.Array.get(0)
     );

let make = (~context: Context.t, ~accountName, ~pollName, _children) => {
  ...component,
  reducer,
  initialState: () => {choices: Belt.Set.Int.empty},
  render: self => {
    let pollData = PollData.make(~creator=accountName, ~id=pollName, ());
    <PollDataQuery variables=pollData##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => ReasonReact.string("Loading...")
             | Error(error) => ReasonReact.string(error##message)
             | Data(response) =>
               switch (response##poll) {
               | Some(poll) =>
                 let vote = getVote(context, poll);
                 let minChoices = poll##minChoices;
                 let maxChoices = poll##maxChoices;
                 <div className=(AppStyles.main |> TypedGlamor.toString)>
                   <h1
                     className=(
                       CommonStyles.pageHeader |> TypedGlamor.toString
                     )>
                     (ReasonReact.string(poll##title))
                   </h1>
                   <div
                     className=(
                       CommonStyles.pagePrimaryBox |> TypedGlamor.toString
                     )>
                     <p>
                       (
                         (
                           minChoices == maxChoices ?
                             {j|Select $minChoices choices|j} :
                             {j|Select $minChoices to $maxChoices choices|j}
                         )
                         |> ReasonReact.string
                       )
                     </p>
                     <ul>
                       (
                         poll##options
                         |> Array.mapi(renderOption(self, vote))
                         |> ReasonReact.array
                       )
                     </ul>
                     <div>
                       <button
                         className=(
                           CommonStyles.button |> TypedGlamor.toString
                         )
                         disabled=(context.scatter == None)
                         onClick=(castVote(self, context, poll))>
                         (
                           (vote == None ? "Vote" : "Change Vote")
                           |> ReasonReact.string
                         )
                       </button>
                       <Link
                         route=(
                           Route.PollResults(
                             poll##pollCreator,
                             poll##pollName,
                           )
                         )>
                         (ReasonReact.string("Results"))
                       </Link>
                     </div>
                   </div>
                 </div>;
               | None => ReasonReact.string("Couldn't find poll")
               }
             }
         )
    </PollDataQuery>;
  },
};
