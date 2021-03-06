open MaterialUi;
open MaterialUIIcons;

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
    Formality.MakeValidators({
      type t = field;
    });
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
               | _ => failwith("options validator received bad input")
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

let renderOption = (form: Container.interface, optionsResults, i, value) => {
  let field = Form.Option(i);
  let results = field |> form.results;
  let valid = isValid(results) && isValid(optionsResults);
  let canDelete = form.state.options |> Array.length > 2;
  <div key=(i |> string_of_int)>

      <TextField
        error=(! valid)
        value=(`String(value))
        margin=`Normal
        label=(
          (
            switch (optionsResults) {
            | Some(Formality.Invalid(message)) => message
            | _ => "Poll Option"
            }
          )
          |> ReasonReact.string
        )
        onChange=(
          event => {
            event
            |> Formality.Dom.toValueOnChange
            |. Form.String
            |> form.change(field);
            switch (optionsResults) {
            | Some(Formality.Invalid(_message)) =>
              form.change(Form.Options, StringArray(form.state.options))
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
      <IconButton
        disabled=(! canDelete)
        onClick=(
          _event => {
            form.change(DelOption(i), NoValue);
            switch (optionsResults) {
            | Some(Formality.Invalid(_message)) =>
              form.change(Form.Options, StringArray(form.state.options))
            | _ => ()
            };
          }
        )>
        <SvgIcon color=(canDelete ? `Error : `Disabled)> <Delete /> </SvgIcon>
      </IconButton>
    </div>;
    /* <Icon >
         ("star" |> ReasonReact.string)
       </Icon> */
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
               noValidate=true
               autoComplete="off"
               onSubmit=(form.submit |> Formality.Dom.preventDefault)>
               <Paper>
                 <Stepper activeStep=(`Int(0)) orientation=`Vertical>
                   <Step key="required">
                     <StepLabel>
                       ("Required Fields" |> ReasonReact.string)
                     </StepLabel>
                     <StepContent>
                       <div>
                         <TextField
                           required=true
                           label=(
                             (
                               switch (Form.Title |> form.results) {
                               | Some(Formality.Invalid(message)) => message
                               | _ => "Title"
                               }
                             )
                             |> ReasonReact.string
                           )
                           value=(`String(form.state.title))
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
                       </div>
                       <div>
                         (
                           form.state.options
                           |> Array.mapi(
                                renderOption(
                                  form,
                                  Form.Options |> form.results,
                                ),
                              )
                           |> ReasonReact.array
                         )
                       </div>
                     </StepContent>
                   </Step>
                   <Step key="optional">
                     <StepLabel>
                       ("Optional Fields" |> ReasonReact.string)
                     </StepLabel>
                     <StepContent>
                       <Grid container=true>
                         <Grid item=true>
                           <TextField
                             label=("Min choices" |> ReasonReact.string)
                             type_="number"
                             value=(`Int(form.state.minChoices))
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
                         </Grid>
                         <Grid item=true>
                           <TextField
                             label=("Max choices" |> ReasonReact.string)
                             type_="number"
                             value=(`Int(form.state.maxChoices))
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
                         </Grid>
                       </Grid>
                       <Grid container=true>
                         <Grid item=true>
                           <TextField
                             label=("Open time" |> ReasonReact.string)
                             type_="datetime-local"
                             value=(
                                     `String(
                                       form.state.openTime
                                       |> Js.Date.toISOString
                                       |> Js.String.slice(~from=0, ~to_=-1),
                                     )
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
                         </Grid>
                         <Grid item=true>
                           <TextField
                             label=("Close time" |> ReasonReact.string)
                             type_="datetime-local"
                             value=(
                                     `String(
                                       form.state.closeTime
                                       |> Js.Date.toISOString
                                       |> Js.String.slice(~from=0, ~to_=-1),
                                     )
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
                         </Grid>
                       </Grid>
                       <div>
                         <TextField
                           label=("Poll Name" |> ReasonReact.string)
                           value=(`String(form.state.pollName))
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
                         <TextField
                           label=("Whitelist" |> ReasonReact.string)
                           value=(
                                   `Array(
                                     form.state.whitelist
                                     |> Js.Array.map(a => `String(a)),
                                   )
                                 )
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
                         <TextField
                           label=("Blacklist" |> ReasonReact.string)
                           value=(
                                   `Array(
                                     form.state.blacklist
                                     |> Js.Array.map(a => `String(a)),
                                   )
                                 )
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
                     </StepContent>
                   </Step>
                 </Stepper>
                 <Button
                   type_="submit"
                   variant=`Contained
                   size=`Large
                   color=`Primary>
                   (ReasonReact.string("Create Poll"))
                 </Button>
               </Paper>
             </form>
         )
    </Container>,
};
