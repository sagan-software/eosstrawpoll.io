let component = ReasonReact.statelessComponent(__MODULE__);

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
  render: _self => {
    let pollData =
      PollPage.PollData.make(~creator=accountName, ~id=pollId, ());
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
                   <div>
                     <Link
                       route=(
                         Route.PollResults(poll##pollCreator, poll##pollId)
                       )>
                       (ReasonReact.string("Results"))
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
