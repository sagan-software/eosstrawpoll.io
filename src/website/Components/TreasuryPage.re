let component = ReasonReact.statelessComponent("TreasuryPage");

let make = _children => {
  ...component,
  render: _self => <div> (ReasonReact.string("Treasury")) </div>,
};
