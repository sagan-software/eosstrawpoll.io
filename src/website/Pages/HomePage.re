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
};

type action =
  | SetInputs(inputs)
  | SetOption(int, string)
  | RemoveOption(int)
  | ToggleAdvanced;

let reducer = (action, state) =>
  switch (action) {
  | SetInputs(inputs) => ReasonReact.Update({...state, inputs})
  | SetOption(i, option) =>
    state.options[i] = option;
    ReasonReact.Update(state);
  | RemoveOption(i) => ReasonReact.Update(state)
  | ToggleAdvanced =>
    ReasonReact.Update({...state, showAdvanced: ! state.showAdvanced})
  };

let onInputChange = ({ReasonReact.state} as self, name, event) => {
  let obj = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event));
  let value = obj##value;
  let inputs = setInputValue(self.state.inputs, name, value);
  self.send(SetInputs(inputs));
};

let component = ReasonReact.reducerComponent("HomePage");

let eos = Util.loadEosReadOnly();

module GetPolls = [%graphql
  {|
  query polls {
    polls {
      id
      pollId
      pollCreator
      title
      whitelist
      blacklist
      openTime
      closeTime
      options
      blockTime
    }
  }
|}
];

module GetPollsQuery = ReasonApollo.CreateQuery(GetPolls);

/* module EverySecond = [%graphql {|
     subscription {
       everySecond
     }
   |}];

   module EverySecondSubscription = ReasonApollo.CreateSubscription(EverySecond); */
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
  },
  render: self =>
    <main className=(Styles.main |> TypedGlamor.toString)>
      <Helmet>
        <title> (ReasonReact.string("Home page")) </title>
        <meta property="og:title" content="EOS Straw Poll" />
        <meta property="og:description" content="Home page!!!" />
      </Helmet>
      <div className=(Styles.form |> TypedGlamor.toString)>
        <h1> (ReasonReact.string("Create a poll")) </h1>
        /* <EverySecondSubscription>
             ...(
                  ({result}) =>
                    switch (result) {
                    | Error(_e) =>
                      Js.log(_e);
                      "Something went wrong" |> ReasonReact.string;
                    | Loading => "Loading" |> ReasonReact.string
                    | Data(response) =>
                      response##everySecond
                      |> string_of_float
                      |> ReasonReact.string

                    }
                )
           </EverySecondSubscription> */
        <PollForm />
      </div>
      <aside className=(Styles.sidebar |> TypedGlamor.toString)>
        <div className=(Styles.poll |> TypedGlamor.toString)>
          <h2 className=(Styles.pollTitle |> TypedGlamor.toString)>
            (ReasonReact.string("New Polls"))
          </h2>
          <GetPollsQuery>
            ...(
                 ({result}) =>
                   switch (result) {
                   | Loading => ReasonReact.string("Loading...")
                   | Error(error) => ReasonReact.string(error##message)
                   | Data(response) =>
                     <ul>
                       (
                         response##polls
                         |> Js.Array.mapi((p, i) => {
                              let date =
                                p##blockTime ++ "Z" |> Js.Date.fromString;
                              <li key=p##id>
                                <h3>
                                  <Link
                                    route=(
                                      Route.Poll(p##pollCreator, p##pollId)
                                    )>
                                    (ReasonReact.string(p##title))
                                  </Link>
                                </h3>
                                <p>
                                  <DateFormat date />
                                  (ReasonReact.string(" by "))
                                  <Link route=(Route.Profile(p##pollCreator))>
                                    (ReasonReact.string(p##pollCreator))
                                  </Link>
                                </p>
                              </li>;
                            })
                         |> ReasonReact.array
                       )
                     </ul>
                   }
               )
          </GetPollsQuery>
        </div>
      </aside>
    </main>,
};
