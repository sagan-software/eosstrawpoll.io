include Belt;

module Styles = HomePageStyles;

type name = [
  | `title
  | `minNumChoices
  | `maxNumChoices
  | `openTime
  | `closeTime
  | `whitelist
  | `blacklist
];

let nameToString = name =>
  switch (name) {
  | `title => "title"
  | `minNumChoices => "min_num_choices"
  | `maxNumChoices => "max_num_choices"
  | `openTime => "open_time"
  | `closeTime => "close_time"
  | `whitelist => "whitelist"
  | `blacklist => "blacklist"
  };

type inputs = {
  title: string,
  minNumChoices: int,
  maxNumChoices: int,
  openTime: option(Js.Date.t),
  closeTime: option(Js.Date.t),
  whitelist: array(string),
  blacklist: array(string),
};

let setTitle = (inputs, value) => {...inputs, title: value};

let getTitle = state => state.title;

let setMinNumChoices = (inputs, value) => {
  let minNumChoices = int_of_string(value);
  let maxNumChoices = int_of_string(value);
  {...inputs, minNumChoices, maxNumChoices};
};

let getMinNumChoices = state => state.minNumChoices |> string_of_int;

let setMaxNumChoices = (inputs, value) => {
  let minNumChoices = int_of_string(value);
  let maxNumChoices = int_of_string(value);
  {...inputs, minNumChoices, maxNumChoices};
};

let getMaxNumChoices = state => state.maxNumChoices |> string_of_int;

let setOpenTime = (inputs, value) => {
  let openTime = Some(Js.Date.fromString(value));
  {...inputs, openTime};
};

let getOpenTime = state =>
  Belt.Option.mapWithDefault(state.openTime, "", Js.Date.toISOString);

let setCloseTime = (inputs, value) => {
  let closeTime = Some(Js.Date.fromString(value));
  {...inputs, closeTime};
};

let getCloseTime = inputs =>
  Belt.Option.mapWithDefault(inputs.closeTime, "", Js.Date.toISOString);

let setWhitelist = (inputs, value) => {
  let whitelist = Js.String.split(",", value);
  {...inputs, whitelist};
};

let getWhitelist = inputs => Js.Array.joinWith(", ", inputs.whitelist);

let setBlacklist = (inputs, value) => {
  let blacklist = Js.String.split(",", value);
  {...inputs, blacklist};
};

let getBlacklist = inputs => Js.Array.joinWith(", ", inputs.blacklist);

let getInputValue = (inputs, name) =>
  switch (name) {
  | `title => getTitle(inputs)
  | `minNumChoices => getMinNumChoices(inputs)
  | `maxNumChoices => getMaxNumChoices(inputs)
  | `openTime => getOpenTime(inputs)
  | `closeTime => getCloseTime(inputs)
  | `whitelist => getWhitelist(inputs)
  | `blacklist => getBlacklist(inputs)
  };

let setInputValue = (inputs, name, value) =>
  switch (name) {
  | `title => setTitle(inputs, value)
  | `minNumChoices => setMinNumChoices(inputs, value)
  | `maxNumChoices => setMaxNumChoices(inputs, value)
  | `openTime => setOpenTime(inputs, value)
  | `closeTime => setCloseTime(inputs, value)
  | `whitelist => setWhitelist(inputs, value)
  | `blacklist => setBlacklist(inputs, value)
  };

type state = {
  inputs,
  inputErrors: Js.Dict.t(string),
  options: array(string),
  optionErrors: array(string),
  showAdvanced: bool,
  recentPolls: Api.Data.t(array(Api.PollRef.t)),
  popularPolls: Api.Data.t(array(Api.PollRef.t)),
  recentVotes: Api.Data.t(array(Api.VoteRef.t)),
};

type action =
  | SetInputs(inputs)
  | SetOption(int, string)
  | RemoveOption(int)
  | ToggleAdvanced
  | ChangeRecentPolls(Api.Data.t(array(Api.PollRef.t)))
  | ChangePopularPolls(Api.Data.t(array(Api.PollRef.t)))
  | ChangeRecentVotes(Api.Data.t(array(Api.VoteRef.t)));

let reducer = (action, state) =>
  switch (action) {
  | SetInputs(inputs) => ReasonReact.Update({...state, inputs})
  | SetOption(i, option) =>
    state.options[i] = option;
    ReasonReact.Update(state);
  | RemoveOption(i) => ReasonReact.Update(state)
  | ToggleAdvanced =>
    ReasonReact.Update({...state, showAdvanced: ! state.showAdvanced})
  | ChangeRecentPolls(recentPolls) =>
    ReasonReact.Update({...state, recentPolls})
  | ChangePopularPolls(popularPolls) =>
    ReasonReact.Update({...state, popularPolls})
  | ChangeRecentVotes(recentVotes) =>
    ReasonReact.Update({...state, recentVotes})
  };

let onInputChange = ({ReasonReact.state} as self, name, event) => {
  let obj = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event));
  let value = obj##value;
  let inputs = setInputValue(self.state.inputs, name, value);
  self.send(SetInputs(inputs));
};

let component = ReasonReact.reducerComponent("HomePage");

let eos = Util.loadEosReadOnly();

/* let setInput = ({ReasonReact.state} as self, name, event) => {
     let obj = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event));
     let value = obj##value;
     Js.log3("Set input", name, value);
     self.send(SetInput(name, value));
   };

   let getValue = ({ReasonReact.state} as self, name) =>
     Js.Dict.get(self.state.inputs, nameToString(name))
     |> Js.Option.getWithDefault(""); */
let make = (~context: Context.t, _children) => {
  ...component,
  reducer,
  initialState: () => {
    inputs: {
      title: "",
      minNumChoices: 1,
      maxNumChoices: 1,
      openTime: None,
      closeTime: None,
      whitelist: [||],
      blacklist: [||],
    },
    inputErrors: Js.Dict.empty(),
    options: [|"", ""|],
    optionErrors: [||],
    showAdvanced: false,
    recentPolls: Api.Data.NotAsked,
    popularPolls: Api.Data.NotAsked,
    recentVotes: Api.Data.NotAsked,
  },
  didMount: self =>
    Js.Promise.all3((
      Api.pollRefs(eos, Env.codeName, ~table="recentpolls", ()),
      Api.pollRefs(eos, Env.codeName, ~table="popularpolls", ()),
      Api.voteRefs(eos, Env.codeName, ~table="recentvotes", ()),
    ))
    |> Js.Promise.then_(((recentPolls, popularPolls, recentVotes)) => {
         self.send(ChangeRecentPolls(Api.Data.fromResult(recentPolls)));
         self.send(ChangePopularPolls(Api.Data.fromResult(popularPolls)));
         self.send(ChangeRecentVotes(Api.Data.fromResult(recentVotes)));
         Js.Promise.resolve();
       })
    |> ignore,
  render: self =>
    <main className=(Styles.main |> TypedGlamor.toString)>
      <form className=(Styles.form |> TypedGlamor.toString)>
        <h1> (ReasonReact.string("Create a poll")) </h1>
        <label>
          <input
            placeholder="Type your question here"
            required=true
            value=(getInputValue(self.state.inputs, `title))
            onChange=(onInputChange(self, `title))
          />
        </label>
        <fieldset className=(Styles.optionList |> TypedGlamor.toString)>
          <legend> (ReasonReact.string("Options")) </legend>
          <label className=(Styles.option |> TypedGlamor.toString)>
            <input
              className=(Styles.optionInput |> TypedGlamor.toString)
              placeholder="Enter poll option"
              required=true
            />
          </label>
          <label>
            <input placeholder="Enter poll option" required=true />
          </label>
          <label> <input placeholder="Enter poll option" /> </label>
        </fieldset>
        <fieldset>
          <legend onClick=(_e => self.send(ToggleAdvanced))>
            (ReasonReact.string("Advanced"))
          </legend>
          (
            self.state.showAdvanced ?
              <div>
                <label>
                  (ReasonReact.string("Min choices"))
                  <input
                    type_="number"
                    min=1
                    max=(self.state.options |> Array.length |> string_of_int)
                    value=(getInputValue(self.state.inputs, `minNumChoices))
                    onChange=(onInputChange(self, `minNumChoices))
                  />
                </label>
                <label>
                  (ReasonReact.string("Max choices"))
                  <input
                    type_="number"
                    min=1
                    max=(self.state.options |> Array.length |> string_of_int)
                    value=(getInputValue(self.state.inputs, `maxNumChoices))
                    onChange=(onInputChange(self, `maxNumChoices))
                  />
                </label>
                <label>
                  (ReasonReact.string("Open time"))
                  <input
                    type_="datetime-local"
                    value=(getInputValue(self.state.inputs, `openTime))
                    onChange=(onInputChange(self, `openTime))
                  />
                </label>
                <label>
                  (ReasonReact.string("Close time"))
                  <input
                    type_="datetime-local"
                    value=(getInputValue(self.state.inputs, `closeTime))
                    onChange=(onInputChange(self, `closeTime))
                  />
                </label>
                <label>
                  (ReasonReact.string("Whitelist"))
                  <input
                    placeholder="alice, bob, janice"
                    pattern="([\\w+]{1,12}(\\.\\w+)?)(,\\s*([\\w+]{1,12}(\\.\\w+)?))*"
                    value=(getInputValue(self.state.inputs, `whitelist))
                    onChange=(onInputChange(self, `whitelist))
                  />
                </label>
                <label>
                  (ReasonReact.string("Blacklist"))
                  <input
                    placeholder="carol, jim, dan"
                    pattern="([\\w+]{1,12}(\\.\\w+)?)(,\\s*([\\w+]{1,12}(\\.\\w+)?))*"
                    value=(getInputValue(self.state.inputs, `blacklist))
                    onChange=(onInputChange(self, `blacklist))
                  />
                </label>
              </div> :
              <div />
          )
        </fieldset>
        <button type_="reset"> (ReasonReact.string("Reset")) </button>
        <button type_="submit" disabled=(context.scatter == None)>
          (ReasonReact.string("Create Poll"))
        </button>
      </form>
      <aside className=(Styles.sidebar |> TypedGlamor.toString)>
        <div className=(Styles.poll |> TypedGlamor.toString)>
          <h2 className=(Styles.pollTitle |> TypedGlamor.toString)>
            (ReasonReact.string("Popular Polls"))
          </h2>
          (
            switch (self.state.popularPolls) {
            | Api.Data.NotAsked => ReasonReact.string("")
            | Api.Data.Loading => ReasonReact.string("Loading...")
            | Api.Data.Success(polls) =>
              <ul>
                (
                  Array.map(polls, p =>
                    <li key={j|$p.creator_$p.id|j}>
                      <Link
                        route=(
                          Route.Poll(p.pollCreator, string_of_int(p.pollId))
                        )>
                        (ReasonReact.string(p.title))
                      </Link>
                    </li>
                  )
                  |> ReasonReact.array
                )
              </ul>
            | Api.Data.Failure(_message) =>
              ReasonReact.string("Failed to load")
            }
          )
        </div>
        <div>
          <h2 className=(Styles.pollTitle |> TypedGlamor.toString)>
            (ReasonReact.string("Recent Polls"))
          </h2>
          (
            switch (self.state.recentPolls) {
            | Api.Data.NotAsked => ReasonReact.string("")
            | Api.Data.Loading => ReasonReact.string("Loading...")
            | Api.Data.Success(polls) =>
              <ul>
                (
                  Array.map(polls, p =>
                    <li key={j|$p.creator_$p.id|j}>
                      <Link
                        route=(
                          Route.Poll(p.pollCreator, string_of_int(p.pollId))
                        )>
                        (ReasonReact.string(p.title))
                      </Link>
                    </li>
                  )
                  |> ReasonReact.array
                )
              </ul>
            | Api.Data.Failure(_message) =>
              ReasonReact.string("Failed to load")
            }
          )
        </div>
        <div>
          <h2 className=(Styles.pollTitle |> TypedGlamor.toString)>
            (ReasonReact.string("Recent Votes"))
          </h2>
          (
            switch (self.state.recentVotes) {
            | Api.Data.NotAsked => ReasonReact.string("")
            | Api.Data.Loading => ReasonReact.string("Loading...")
            | Api.Data.Success(votes) =>
              <ul>
                (
                  Array.map(votes, v =>
                    <li key={j|$v.pollCreator_$v.pollId_$v.voter|j}>
                      (ReasonReact.string(v.voter))
                      (ReasonReact.string(" voted on "))
                      <Link
                        route=(
                          Route.Poll(v.pollCreator, string_of_int(v.pollId))
                        )>
                        (ReasonReact.string(v.pollTitle))
                      </Link>
                    </li>
                  )
                  |> ReasonReact.array
                )
              </ul>
            | Api.Data.Failure(_message) =>
              ReasonReact.string("Failed to load")
            }
          )
        </div>
      </aside>
    </main>,
};
