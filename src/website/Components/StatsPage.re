let component = ReasonReact.statelessComponent("StatsPage");

let make = _children => {
  ...component,
  render: _self => <div> (ReasonReact.string("Stats")) </div>,
};
