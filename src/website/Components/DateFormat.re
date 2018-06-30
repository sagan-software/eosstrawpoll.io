let component = ReasonReact.statelessComponent("TimeFormat");

let make = (~date, _children) => {
  ...component,
  render: _self =>
    <time>
      (date |> Moment.fromDate |. Moment.fromNow |> ReasonReact.string)
    </time>,
};
