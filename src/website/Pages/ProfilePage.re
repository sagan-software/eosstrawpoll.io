let renderPost = (poll: Api.Poll.t) =>
  <div key=(string_of_int(poll.id))>
    <Link route=(Route.Poll(poll.creator, poll.id |> string_of_int))>
      (ReasonReact.string(poll.title))
    </Link>
  </div>;

type pollData = Api.Data.t(array(Api.Poll.t));

type action =
  | ChangePollData(pollData);

type state = {
  accountName: string,
  pollData,
};

let reducer = (action, state) =>
  switch (action) {
  | ChangePollData(pollData) => ReasonReact.Update({...state, pollData})
  };

let component = ReasonReact.reducerComponent("ProfilePage");

let numPerPage = 20;

let eos = Util.loadEosReadOnly();

let tmp = [%bs.raw {| window.eos = eos |}];

let make = (~context: Context.t, ~accountName, _children) => {
  ...component,
  reducer,
  initialState: () => {accountName, pollData: Api.Data.Loading},
  didMount: self =>
    Api.polls(eos, accountName, ~limit=numPerPage, ())
    |> Js.Promise.then_(result => {
         let pollData = Api.Data.fromResult(result);
         self.send(ChangePollData(pollData));
         Js.Promise.resolve();
       })
    |> ignore,
  render: self =>
    <div>
      <h1> (ReasonReact.string(accountName)) </h1>
      (ReasonReact.string("Profile"))
      <div>
        (
          switch (self.state.pollData) {
          | Api.Data.NotAsked => ReasonReact.string("")
          | Api.Data.Loading => ReasonReact.string("Loading...")
          | Api.Data.Success(polls) =>
            <div> (polls |> Array.map(renderPost) |> ReasonReact.array) </div>
          | Api.Data.Failure(_message) =>
            ReasonReact.string("Failed to load")
          }
        )
      </div>
    </div>,
};
