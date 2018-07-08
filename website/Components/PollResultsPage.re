type state =
  | EqualVotes
  | StakedVotes
  | InstantRunoff;

type action =
  | ChangeState(state);

let reducer = (action, _state) =>
  switch (action) {
  | ChangeState(state) => ReasonReact.Update(state)
  };

let renderOption = (poll, option) =>
  <li>
    <span> (ReasonReact.string(option)) </span>
    <span> (ReasonReact.string("0 Votes")) </span>
    <span> (ReasonReact.string("0%")) </span>
  </li>;

let getResults = poll => {
  let dict =
    Js.Array.reduce(
      (results, vote) => {
        Js.Array.forEachi(
          (choice, rank) => {
            let key = choice |> string_of_int;
            let votes =
              results |. Js.Dict.get(key) |> Js.Option.getWithDefault([||]);
            let vote = {
              "voter": vote##voter,
              "rank": rank,
              "staked": vote##voterStaked,
            };
            votes |> Js.Array.push(vote) |> ignore;
            results |. Js.Dict.set(key, votes);
          },
          vote##choices,
        );
        results;
      },
      Js.Dict.empty(),
      poll##votes,
    );
  poll##options
  |> Js.Array.mapi((label, index) => {
       let indexStr = index |> string_of_int;
       let votes =
         dict |. Js.Dict.get(indexStr) |> Js.Option.getWithDefault([||]);
       {"label": label, "votes": votes};
     });
};

let renderResult = (totalResults, result) => {
  let percent =
    (result##votes |> Js.Array.length |> float_of_int)
    /. totalResults##numVotes
    *. 100.;
  <li key=result##label>
    (result##label |> ReasonReact.string)
    <span>
      (" | " |> ReasonReact.string)
      (result##votes |> Js.Array.length |> string_of_int |> ReasonReact.string)
      (" votes" |> ReasonReact.string)
      (" | " |> ReasonReact.string)
      (percent |> string_of_float |> ReasonReact.string)
      ("%" |> ReasonReact.string)
    </span>
  </li>;
};

let renderResults = poll => {
  let results =
    poll
    |> getResults
    |> Js.Array.sortInPlaceWith((a, b) =>
         Js.Array.length(b##votes) - Js.Array.length(a##votes)
       );
  let totalResults = {
    "numVotes":
      Js.Array.reduce(
        (total, option) => total + Js.Array.length(option##votes),
        0,
        results,
      )
      |> float_of_int,
  };
  Js.log2("RESULTS!!!", {"results": results, "votes": poll##votes});
  <ol>
    (
      results |> Js.Array.map(renderResult(totalResults)) |> ReasonReact.array
    )
  </ol>;
};

let component = ReasonReact.reducerComponent(__MODULE__);

let make = (~context: Context.t, ~accountName, ~pollName, _children) => {
  ...component,
  reducer,
  initialState: () => EqualVotes,
  render: _self => {
    let pollData =
      PollPage.PollData.make(~creator=accountName, ~id=pollName, ());
    <PollPage.PollDataQuery variables=pollData##variables>
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
                   (poll |> renderResults)
                   <div>
                     <Link
                       route=(Route.Poll(poll##pollCreator, poll##pollName))>
                       (ReasonReact.string("Vote"))
                     </Link>
                   </div>
                 </div>
               | None => ReasonReact.string("Couldn't find poll")
               }
             }
         )
    </PollPage.PollDataQuery>;
  },
};
