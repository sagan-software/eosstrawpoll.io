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
    ({ReasonReact.state} as self, context: Context.t, poll, _event) =>
  switch (context.scatter) {
  | Some(scatter) =>
    Api.Contract.make(scatter)
    |> Js.Promise.then_(contract =>
         Js.Promise.resolve(
           Api.vote(
             contract,
             ~pollCreator=poll##pollCreator,
             ~pollId=poll##pollId,
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

module PollData = [%graphql
  {|
  query pollData($creator: String!, $id: String!) {
    poll(creator:$creator,id:$id) {
      id
      pollId
      pollCreator
      title
      description
      options
      whitelist
      blacklist
      openTime
      closeTime
      blockId
      blockNum
      blockTime
      trxId
      appLabel
      votes {
        id
        voter
        choices
        blockNum
        blockTime
        trxId
        appLabel
      }
      comments {
        id
        commenter
        content
        blockTime
        trxId
        appLabel
      }
    }
  }
|}
];

module PollDataQuery = ReasonApollo.CreateQuery(PollData);

let make = (~context: Context.t, ~accountName, ~pollId, _children) => {
  ...component,
  reducer,
  initialState: () => {choices: Belt.Set.Int.empty},
  render: self => {
    let pollData = PollData.make(~creator=accountName, ~id=pollId, ());
    <PollDataQuery variables=pollData##variables>
      ...(
           ({result}) =>
             switch (result) {
             | Loading => ReasonReact.string("Loading...")
             | Error(error) => ReasonReact.string(error##message)
             | Data(response) =>
               switch (response##poll) {
               | Some(poll) =>
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
                     <ol>
                       (
                         poll##options
                         |> Array.mapi(renderOption(self))
                         |> ReasonReact.array
                       )
                     </ol>
                     <div>
                       <button
                         disabled=(context.scatter == None)
                         onClick=(castVote(self, context, poll))>
                         (ReasonReact.string("Vote"))
                       </button>
                       <Link
                         route=(
                           Route.PollResults(poll##pollCreator, poll##pollId)
                         )>
                         (ReasonReact.string("Results"))
                       </Link>
                     </div>
                   </div>
                 </div>
               | None => ReasonReact.string("Couldn't find poll")
               }
             }
         )
    </PollDataQuery>;
  },
};
