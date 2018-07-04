module Cn = PollFormStyles;

module Form = {
  include Forms;
  type field =
    | PollId
    | Title
    | Description
    | Option(int)
    | AddOption
    | DelOption(int)
    | Options
    | Whitelist
    | Blacklist
    | MinChoices
    | MaxChoices
    | OpenTime
    | CloseTime;
  type state = {
    pollId: string,
    title: string,
    description: string,
    options: array(string),
    whitelist: string,
    blacklist: string,
    minChoices: int,
    maxChoices: int,
    openTime: string,
    closeTime: string,
  };
  let get = (field, state) =>
    switch (field) {
    | PollId => String(state.pollId)
    | Title => String(state.title)
    | Description => String(state.description)
    | Option(index) =>
      state.options
      |. Belt.Array.get(index)
      |. Belt.Option.getWithDefault("")
      |. String
    | DelOption(_index) => NoValue
    | AddOption => NoValue
    | Options => NoValue
    | Whitelist => String(state.whitelist)
    | Blacklist => String(state.blacklist)
    | MinChoices => Int(state.minChoices)
    | MaxChoices => Int(state.maxChoices)
    | OpenTime => String(state.openTime)
    | CloseTime => String(state.closeTime)
    };
  let update = ((field, value), state) =>
    switch (field, value) {
    | (PollId, String(value)) => {...state, pollId: value}
    | (Title, String(value)) => {...state, title: value}
    | (Description, String(value)) => {...state, description: value}
    | (Option(index), String(value)) =>
      state.options |. Belt.Array.set(index, value) |> ignore;
      state;
    | (AddOption, _value) =>
      state.options |> Js.Array.push("") |> ignore;
      state;
    | (DelOption(index), _novalue) => {
        ...state,
        options: state.options |> Js.Array.filteri((_o, i) => i != index),
      }
    | (Options, _novalue) => state
    | (Whitelist, String(value)) => {...state, whitelist: value}
    | (Blacklist, String(value)) => {...state, blacklist: value}
    | (MinChoices, Int(value)) => {...state, minChoices: value}
    | (MaxChoices, Int(value)) => {...state, maxChoices: value}
    | (OpenTime, String(value)) => {...state, openTime: value}
    | (CloseTime, String(value)) => {...state, closeTime: value}
    | _ => failwith("Config.update function received bad input")
    };
  module Validators =
    Formality.MakeValidators(
      {
        type t = field;
      },
    );
  type validators =
    Validators.t(Formality.validator(field, value, state, message));
  let baseValidators =
    Formality.(
      Validators.empty
      /* |> Validators.add(
           PollId,
           {
             strategy: Strategy.OnFirstChange,
             dependents: None,
             validate: isRequired |> thenValidate(isName),
           },
         ) */
      |> Validators.add(
           Title,
           {
             strategy: Strategy.OnFirstChange,
             dependents: None,
             validate: isRequired,
           },
         )
      |> Validators.add(
           Description,
           {
             strategy: Strategy.OnFirstChange,
             dependents: None,
             validate: atMost(10),
           },
         )
    );
  let validators =
    Formality.(
      Belt.Array.range(0, 100)
      |. Belt.Array.reduce(baseValidators, (result, i) =>
           result
           |> Validators.add(
                Option(i),
                {
                  strategy: Strategy.OnFirstChange,
                  dependents: None,
                  validate: atMost(80),
                },
              )
         )
    );
};

module Container = Formality.Make(Form);

let component = ReasonReact.statelessComponent(__MODULE__);

let randomPollId = () => {
  let possibleChars = "12345abcdefghijklmnopqrstuvwxyz";
  let possibleCharsLength = possibleChars |> Js.String.length;
  let chosenChars = [||];
  Belt.Array.range(0, 11)
  |. Belt.Array.forEach(_i => {
       let chosenIndex = Random.int(possibleCharsLength);
       let chosenChar = possibleChars |> Js.String.charAt(chosenIndex);
       chosenChars |> Js.Array.push(chosenChar) |> ignore;
     });
  chosenChars |> Js.Array.joinWith("");
};

Random.self_init();

let make = (~context: Context.t, _children) => {
  ...component,
  render: _self =>
    <Container
      initialState={
        pollId: "",
        title: "",
        description: "",
        options: [|"", "", ""|],
        whitelist: "",
        blacklist: "",
        minChoices: 1,
        maxChoices: 1,
        openTime: "",
        closeTime: "",
      }
      onSubmit=(
        (state, form) => {
          Js.log2("Called with:", state);
          let pollId =
            state.pollId |> String.trim |> String.length == 0 ?
              randomPollId() : state.pollId;
          switch (context.scatter, context.identity) {
          | (Some(scatter), Some(identity)) =>
            let pollCreator =
              (identity |. Scatter.Identity.accounts)[0]
              |. Scatter.Account.name;
            scatter
            |> Api.Contract.make
            |> Js.Promise.then_(contract =>
                 Api.Contract.create(
                   contract,
                   {
                     "poll_creator": pollCreator,
                     "poll_id": pollId,
                     "title": state.title,
                     "description": state.description,
                     "options":
                       state.options
                       |> Js.Array.filter(o =>
                            o |> String.trim |> String.length != 0
                          ),
                     "whitelist": [||],
                     "blacklist": [||],
                     "min_choices": state.minChoices,
                     "max_choices": state.maxChoices,
                     "open_time": 0,
                     "close_time": 0,
                     "app_label": "eosstrawpoll",
                   },
                   Eos.Action.options(
                     ~authorization=[|{j|$pollCreator@active|j}|],
                     (),
                   ),
                 )
               )
            |> Js.Promise.then_(_result =>
                 Js.Global.setTimeout(
                   () =>
                     Route.Poll(pollCreator, pollId)
                     |> Route.toString
                     |> ReasonReact.Router.push
                     |> ignore,
                   1000,
                 )
                 |> Js.Promise.resolve
               )
            |> ignore;
          | (_scatter, _identity) =>
            Js.log2(
              "tried to create a poll without scatter or without an identity",
              context,
            )
          };
        }
      )>
      ...(
           form =>
             <form
               className=(Cn.container |> TypedGlamor.toString)
               onSubmit=(form.submit |> Formality.Dom.preventDefault)>
               <div className=(Cn.fields |> TypedGlamor.toString)>
                 <div className=(Cn.titleField |> TypedGlamor.toString)>
                   <input
                     className=(Cn.titleInput |> TypedGlamor.toString)
                     placeholder="Title of your poll..."
                     value=form.state.title
                     disabled=form.submitting
                     autoComplete="off"
                     autoFocus=true
                     onChange=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnChange
                         |. Form.String
                         |> form.change(Form.Title)
                     )
                     onBlur=(
                       event =>
                         event
                         |> Formality.Dom.toValueOnBlur
                         |. Form.String
                         |> form.blur(Form.Title)
                     )
                   />
                   (
                     switch (Form.Title |> form.results) {
                     | Some(Invalid(message)) =>
                       <div className="failure">
                         (message |> ReasonReact.string)
                       </div>
                     | Some(Valid) =>
                       <div className="success">
                         ({j|✓|j} |> ReasonReact.string)
                       </div>
                     | None => ReasonReact.null
                     }
                   )
                 </div>
                 <div>
                   (
                     form.state.options
                     |> Array.mapi((i, value) =>
                          <div
                            key=(i |> string_of_int)
                            className=(Cn.optionField |> TypedGlamor.toString)>
                            <span
                              className=(Cn.optionNum |> TypedGlamor.toString)>
                              (i + 1 |> string_of_int |> ReasonReact.string)
                              ("." |> ReasonReact.string)
                            </span>
                            <input
                              className=(
                                Cn.optionInput |> TypedGlamor.toString
                              )
                              value
                              placeholder={j|Poll option...|j}
                              autoComplete="off"
                              onChange=(
                                event =>
                                  event
                                  |> Formality.Dom.toValueOnChange
                                  |. Form.String
                                  |> form.change(Form.Option(i))
                              )
                              onFocus=(
                                _event => {
                                  let lastOption =
                                    (form.state.options |> Array.length) - 1;
                                  let field =
                                    i >= lastOption ?
                                      Form.AddOption : Form.Options;
                                  form.change(field, NoValue);
                                }
                              )
                            />
                            (
                              form.state.options |> Array.length > 2 ?
                                <a
                                  className=(
                                    Cn.optionRemove |> TypedGlamor.toString
                                  )
                                  onClick=(
                                    _event =>
                                      form.change(DelOption(i), NoValue)
                                  )>
                                  Icon.minusSquare
                                </a> :
                                ReasonReact.string("")
                            )
                            (
                              switch (Form.Option(i) |> form.results) {
                              | Some(Invalid(message)) =>
                                <div className="failure">
                                  (message |> ReasonReact.string)
                                </div>
                              | Some(Valid) =>
                                <div className="success">
                                  ({j|✓|j} |> ReasonReact.string)
                                </div>
                              | None => ReasonReact.null
                              }
                            )
                          </div>
                        )
                     |> ReasonReact.array
                   )
                 </div>
                 /* <a onClick=(_event => form.change(AddOption, NoValue))>
                      ("Add option" |> ReasonReact.string)
                    </a>
                    <div className="form-row">
                      <label htmlFor="signup--title" className="label-lg">
                        ("Description" |> ReasonReact.string)
                      </label>
                      <input
                        id="signup--title"
                        type_="text"
                        value=form.state.description
                        disabled=form.submitting
                        onChange=(
                          event =>
                            event
                            |> Formality.Dom.toValueOnChange
                            |. Form.String
                            |> form.change(Form.Description)
                        )
                        onBlur=(
                          event =>
                            event
                            |> Formality.Dom.toValueOnBlur
                            |. Form.String
                            |> form.blur(Form.Description)
                        )
                      />
                      (
                        switch (Form.Description |> form.results) {
                        | Some(Invalid(message)) =>
                          <div className="failure">
                            (message |> ReasonReact.string)
                          </div>
                        | Some(Valid) =>
                          <div className="success">
                            ({j|✓|j} |> ReasonReact.string)
                          </div>
                        | None => ReasonReact.null
                        }
                      )
                    </div>
                    <div className="form-row">
                      <label htmlFor="signup--title" className="label-lg">
                        ("Min choices" |> ReasonReact.string)
                      </label>
                      <input
                        id="signup--title"
                        type_="text"
                        value=(form.state.minChoices |> string_of_int)
                        disabled=form.submitting
                        onChange=(
                          event =>
                            event
                            |> Formality.Dom.toValueOnChange
                            |. int_of_string
                            |. Form.Int
                            |> form.change(Form.MinChoices)
                        )
                        onBlur=(
                          event =>
                            event
                            |> Formality.Dom.toValueOnBlur
                            |. int_of_string
                            |. Form.Int
                            |> form.blur(Form.MinChoices)
                        )
                      />
                      (
                        switch (Form.MinChoices |> form.results) {
                        | Some(Invalid(message)) =>
                          <div className="failure">
                            (message |> ReasonReact.string)
                          </div>
                        | Some(Valid) =>
                          <div className="success">
                            ({j|✓|j} |> ReasonReact.string)
                          </div>
                        | None => ReasonReact.null
                        }
                      )
                    </div>
                    <div className="form-row">
                      <label htmlFor="signup--title" className="label-lg">
                        ("Poll ID" |> ReasonReact.string)
                      </label>
                      <input
                        id="signup--title"
                        type_="text"
                        value=form.state.pollId
                        disabled=form.submitting
                        onChange=(
                          event =>
                            event
                            |> Formality.Dom.toValueOnChange
                            |. Form.String
                            |> form.change(Form.PollId)
                        )
                        onBlur=(
                          event =>
                            event
                            |> Formality.Dom.toValueOnBlur
                            |. Form.String
                            |> form.blur(Form.PollId)
                        )
                      />
                      (
                        switch (Form.PollId |> form.results) {
                        | Some(Invalid(message)) =>
                          <div className="failure">
                            (message |> ReasonReact.string)
                          </div>
                        | Some(Valid) =>
                          <div className="success">
                            ({j|✓|j} |> ReasonReact.string)
                          </div>
                        | None => ReasonReact.null
                        }
                      )
                    </div> */
                 <button
                   type_="submit"
                   className=(Cn.submitButton |> TypedGlamor.toString)>
                   (ReasonReact.string("Create Poll"))
                 </button>
               </div>
             </form>
         )
    </Container>,
};
