module Cn = PollFormStyles;

let clamp = (min, max, v) =>
  v |> Js.Math.max_int(min) |> Js.Math.min_int(max);

module Form = {
  include Forms;
  type field =
    | PollName
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
    | CloseTime
    | NoField;
  type state = {
    pollName: string,
    title: string,
    description: string,
    options: array(string),
    whitelist: array(string),
    blacklist: array(string),
    minChoices: int,
    maxChoices: int,
    openTime: Js.Date.t,
    closeTime: Js.Date.t,
  };
  let get = (field, state) =>
    switch (field) {
    | PollName => String(state.pollName)
    | Title => String(state.title)
    | Description => String(state.description)
    | Option(index) =>
      state.options
      |. Belt.Array.get(index)
      |. Belt.Option.getWithDefault("")
      |. String
    | DelOption(_index) => NoValue
    | AddOption => NoValue
    | Options => StringArray(state.options)
    | Whitelist => StringArray(state.whitelist)
    | Blacklist => StringArray(state.blacklist)
    | MinChoices => Int(state.minChoices)
    | MaxChoices => Int(state.maxChoices)
    | OpenTime => Date(state.openTime)
    | CloseTime => Date(state.closeTime)
    | NoField => NoValue
    };
  let update = ((field, value), state) =>
    switch (field, value) {
    | (PollName, String(value)) => {...state, pollName: value}
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
    | (Options, _novalue) =>
      let numOptions = state.options |> Js.Array.length;
      let minChoices = state.minChoices |> clamp(1, numOptions);
      let maxChoices = state.maxChoices |> clamp(1, numOptions);
      {...state, minChoices, maxChoices};
    | (Whitelist, String(value)) => {
        ...state,
        whitelist:
          value |> Js.String.split(",") |> Js.Array.map(Js.String.trim),
      }
    | (Whitelist, StringArray(whitelist)) => {...state, whitelist}
    | (Blacklist, String(value)) => {
        ...state,
        blacklist:
          value |> Js.String.split(",") |> Js.Array.map(Js.String.trim),
      }
    | (Blacklist, StringArray(blacklist)) => {...state, blacklist}
    | (MinChoices, Int(value)) =>
      let numOptions = state.options |> Js.Array.length;
      let minChoices = value |> clamp(1, numOptions);
      let maxChoices = state.maxChoices |> clamp(minChoices, numOptions);
      {...state, minChoices, maxChoices};
    | (MaxChoices, Int(value)) =>
      let numOptions = state.options |> Js.Array.length;
      let maxChoices = value |> clamp(1, numOptions);
      let minChoices = state.minChoices |> clamp(1, maxChoices);
      {...state, maxChoices, minChoices};
    | (OpenTime, String(value)) => {
        ...state,
        openTime: Js.Date.fromString(value),
      }
    | (OpenTime, Date(value)) => {...state, openTime: value}
    | (CloseTime, String(value)) => {
        ...state,
        closeTime: Js.Date.fromString(value),
      }
    | (CloseTime, Date(value)) => {...state, closeTime: value}
    | (NoField, _novalue) => state
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
           PollName,
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
      |> Validators.add(
           Options,
           {
             strategy: Strategy.OnFirstChange,
             dependents:
               Belt.Array.range(0, 100)
               |> Js.Array.map(i => Option(i))
               |. Belt.List.fromArray
               |. Some,
             validate: (value, _) =>
               switch (value) {
               | StringArray(value) =>
                 let numOptions =
                   value
                   |> Js.Array.filter(v => v |> Js.String.trim !== "")
                   |> Js.Array.length;
                 if (numOptions < 2) {
                   Formality.Invalid("Must have at least 2 or more options");
                 } else {
                   Formality.Valid;
                 };
               | _ =>
                 Js.log2("WTF?????", value);
                 failwith("options validator received bad input");
               },
           },
         )
    );
};

module Container = Formality.Make(Form);

let component = ReasonReact.statelessComponent(__MODULE__);

Random.self_init();

let isValid = result =>
  switch (result) {
  | Some(Formality.Valid) => true
  | None => true
  | _ => false
  };

module Field = {
  let component = ReasonReact.statelessComponent(__MODULE__);
  let make = (~form: Container.interface, ~field, children) => {
    ...component,
    render: _self => {
      let results = field |> form.results;
      <div className=(Cn.field |> TypedGlamor.toString)>
        (children(results))
        (
          switch (results) {
          | Some(Formality.Invalid(message)) =>
            <div className=(Cn.invalid |> TypedGlamor.toString)>
              Icon.exclamation
              (message |> ReasonReact.string)
            </div>
          | Some(Formality.Valid) =>
            <div className=(Cn.valid |> TypedGlamor.toString)>
              Icon.checkCircle
            </div>
          | None => ReasonReact.null
          }
        )
      </div>;
    },
  };
};

let renderOption = (form: Container.interface, optionsResults, i, value) => {
  let field = Form.Option(i);
  <Field form field>
    ...(
         results => {
           let valid = isValid(results) && isValid(optionsResults);
           <div
             key=(i |> string_of_int)
             className=(valid |> Cn.optionField |> TypedGlamor.toString)>
             <span className=(Cn.optionNum |> TypedGlamor.toString)>
               (i + 1 |> string_of_int |> ReasonReact.string)
             </span>
             <input
               className=(valid |> Cn.optionInput |> TypedGlamor.toString)
               value
               placeholder=(
                 switch (optionsResults) {
                 | Some(Formality.Invalid(message)) => message
                 | _ => "Poll option..."
                 }
               )
               autoComplete="off"
               onChange=(
                 event => {
                   event
                   |> Formality.Dom.toValueOnChange
                   |. Form.String
                   |> form.change(field);
                   switch (optionsResults) {
                   | Some(Formality.Invalid(_message)) =>
                     form.change(
                       Form.Options,
                       StringArray(form.state.options),
                     )
                   | _ => ()
                   };
                 }
               )
               onFocus=(
                 _event => {
                   let lastOption = (form.state.options |> Array.length) - 1;
                   if (i >= lastOption) {
                     form.change(Form.AddOption, NoValue);
                   };
                 }
               )
             />
             (
               form.state.options |> Array.length > 2 ?
                 <a
                   className=(Cn.optionRemove |> TypedGlamor.toString)
                   onClick=(
                     _event => {
                       form.change(DelOption(i), NoValue);
                       switch (optionsResults) {
                       | Some(Formality.Invalid(_message)) =>
                         form.change(
                           Form.Options,
                           StringArray(form.state.options),
                         )
                       | _ => ()
                       };
                     }
                   )>
                   Icon.minusSquare
                 </a> :
                 ReasonReact.string("")
             )
           </div>;
         }
       )
  </Field>;
};

let make = (~context: Context.t, _children) => {
  ...component,
  render: _self =>
    <Container
      initialState={
        pollName: Eos.Name.random(),
        title: "",
        description: "",
        options: [|"", "", ""|],
        whitelist: [||],
        blacklist: [||],
        minChoices: 1,
        maxChoices: 1,
        openTime: Js.Date.make(),
        closeTime:
          Js.Date.now() +. 60. *. 60. *. 24. *. 1000. |> Js.Date.fromFloat,
      }
      onSubmit=(
        (state, form) => {
          Js.log2("Called with:", state);
          switch (context.scatter, context.identity) {
          | (Some(scatter), Some(identity)) =>
            let pollCreator =
              (identity |. Scatter.Identity.accounts)[0]
              |. Scatter.Account.name;
            scatter
            |> Contract.fromScatter
            |> Js.Promise.then_(contract =>
                 Contract.create(
                   contract,
                   {
                     "poll_creator": pollCreator,
                     "poll_name": state.pollName,
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
                     "metadata": Env.metadata,
                   },
                   {"authorization": [|{j|$pollCreator@active|j}|]},
                 )
               )
            |> Js.Promise.then_(_result =>
                 Js.Global.setTimeout(
                   () =>
                     Route.Poll(pollCreator, state.pollName)
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
                 <Field form field=Form.Title>
                   ...(
                        results =>
                          <div>
                            <input
                              className=(
                                results
                                |> isValid
                                |> Cn.titleInput
                                |> TypedGlamor.toString
                              )
                              placeholder=(
                                switch (results) {
                                | Some(Formality.Invalid(message)) => message
                                | _ => "Title of your poll..."
                                }
                              )
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
                          </div>
                      )
                 </Field>
                 <Field form field=Form.Options>
                   ...(
                        results =>
                          <div>
                            (
                              form.state.options
                              |> Array.mapi(renderOption(form, results))
                              |> ReasonReact.array
                            )
                          </div>
                      )
                 </Field>
                 <div className=(Cn.advancedFields |> TypedGlamor.toString)>
                   <div>
                     <label htmlFor="signup--title" className="label-lg">
                       ("Min choices" |> ReasonReact.string)
                     </label>
                     <input
                       type_="number"
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
                   </div>
                   <div>
                     <label htmlFor="signup--title" className="label-lg">
                       ("Max choices" |> ReasonReact.string)
                     </label>
                     <input
                       type_="number"
                       value=(form.state.maxChoices |> string_of_int)
                       disabled=form.submitting
                       onChange=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnChange
                           |. int_of_string
                           |. Form.Int
                           |> form.change(Form.MaxChoices)
                       )
                       onBlur=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnBlur
                           |. int_of_string
                           |. Form.Int
                           |> form.blur(Form.MaxChoices)
                       )
                     />
                   </div>
                   <div>
                     <label> ("Open time" |> ReasonReact.string) </label>
                     <input
                       type_="datetime-local"
                       value=(
                         form.state.openTime
                         |> Js.Date.toISOString
                         |> Js.String.slice(~from=0, ~to_=-1)
                       )
                       disabled=form.submitting
                       onChange=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnChange
                           |. Form.String
                           |> form.change(Form.OpenTime)
                       )
                       onBlur=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnBlur
                           |. Form.String
                           |> form.blur(Form.OpenTime)
                       )
                     />
                   </div>
                   <div>
                     <label> ("Close time" |> ReasonReact.string) </label>
                     <input
                       type_="datetime-local"
                       value=(
                         form.state.closeTime
                         |> Js.Date.toISOString
                         |> Js.String.slice(~from=0, ~to_=-1)
                       )
                       disabled=form.submitting
                       onChange=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnChange
                           |. Form.String
                           |> form.change(Form.CloseTime)
                       )
                       onBlur=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnBlur
                           |. Form.String
                           |> form.blur(Form.CloseTime)
                       )
                     />
                   </div>
                   <div className="form-row">
                     <label htmlFor="signup--title" className="label-lg">
                       ("Poll Name" |> ReasonReact.string)
                     </label>
                     <input
                       id="signup--title"
                       type_="text"
                       value=form.state.pollName
                       disabled=form.submitting
                       onChange=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnChange
                           |. Form.String
                           |> form.change(Form.PollName)
                       )
                       onBlur=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnBlur
                           |. Form.String
                           |> form.blur(Form.PollName)
                       )
                     />
                   </div>
                   <div>
                     <label> ("Whitelist" |> ReasonReact.string) </label>
                     <input
                       value=(form.state.whitelist |> Js.Array.joinWith(", "))
                       disabled=form.submitting
                       onChange=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnChange
                           |. Form.String
                           |> form.change(Form.Whitelist)
                       )
                       onBlur=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnBlur
                           |. Form.String
                           |> form.blur(Form.Whitelist)
                       )
                     />
                   </div>
                   <div>
                     <label> ("Blacklist" |> ReasonReact.string) </label>
                     <input
                       value=(form.state.blacklist |> Js.Array.joinWith(", "))
                       disabled=form.submitting
                       onChange=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnChange
                           |. Form.String
                           |> form.change(Form.Blacklist)
                       )
                       onBlur=(
                         event =>
                           event
                           |> Formality.Dom.toValueOnBlur
                           |. Form.String
                           |> form.blur(Form.Blacklist)
                       )
                     />
                   </div>
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
                            Icon.exclamation (message |> ReasonReact.string)
                          </div>
                        | Some(Valid) =>
                          <div className="success">
                            Icon.checkCircle
                          </div>
                        | None => ReasonReact.null
                        }
                      )
                    </div>

                      (
                        switch (Form.PollName |> form.results) {
                        | Some(Invalid(message)) =>
                          <div className="failure">
                            Icon.exclamation (message |> ReasonReact.string)
                          </div>
                        | Some(Valid) =>
                          <div className="success">
                            Icon.checkCircle
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
