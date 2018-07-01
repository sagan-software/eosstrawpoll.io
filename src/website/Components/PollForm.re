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
      |> Validators.add(
           PollId,
           {
             strategy: Strategy.OnFirstChange,
             dependents: None,
             validate: isRequired |> thenValidate(isName),
           },
         )
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
      |> Validators.add(
           MinChoices,
           {
             strategy: Strategy.OnFirstChange,
             dependents: None,
             validate: (value, _) =>
               switch (value) {
               | Int(1) => Valid
               | _ => Invalid("min choices must be 1 (testing)")
               },
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
                  validate: isBetween(1, 10),
                },
              )
         )
    );
};

module Container = Formality.Make(Form);

let component = ReasonReact.statelessComponent(__MODULE__);

let make = _children => {
  ...component,
  render: _self =>
    <Container
      initialState={
        pollId: "",
        title: "",
        description: "",
        options: [|"", ""|],
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
          Js.Global.setTimeout(
            () => {
              form.notifyOnSuccess(None);
              Js.Global.setTimeout(form.reset, 3000) |> ignore;
            },
            500,
          )
          |> ignore;
        }
      )>
      ...(
           form =>
             <form
               className="form"
               onSubmit=(form.submit |> Formality.Dom.preventDefault)>
               <h1> ("New Poll" |> ReasonReact.string) </h1>
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
               </div>
               <div className="form-row">
                 <label htmlFor="signup--title" className="label-lg">
                   ("Title" |> ReasonReact.string)
                 </label>
                 <input
                   id="signup--title"
                   type_="text"
                   value=form.state.title
                   disabled=form.submitting
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
               <ol>
                 (
                   form.state.options
                   |> Array.mapi((i, value) =>
                        <li key=(i |> string_of_int)>
                          <input
                            value
                            onChange=(
                              event =>
                                event
                                |> Formality.Dom.toValueOnChange
                                |. Form.String
                                |> form.change(Form.Option(i))
                            )
                          />
                          (
                            i >= 2 ?
                              <a
                                onClick=(
                                  _event =>
                                    form.change(DelOption(i), NoValue)
                                )>
                                ("[-]" |> ReasonReact.string)
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
                        </li>
                      )
                   |> ReasonReact.array
                 )
               </ol>
               <a onClick=(_event => form.change(AddOption, NoValue))>
                 ("Add option" |> ReasonReact.string)
               </a>
               <button type_="reset"> (ReasonReact.string("Reset")) </button>
               <button type_="submit">
                 (ReasonReact.string("Create Poll"))
               </button>
             </form>
         )
    </Container>,
};
