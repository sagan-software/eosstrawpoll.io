let component = ReasonReact.statelessComponent("GovernancePage");

let make = _children => {
  ...component,
  render: _self => <div> (ReasonReact.string("Governance")) </div>,
};
