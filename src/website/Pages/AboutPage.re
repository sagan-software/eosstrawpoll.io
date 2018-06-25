let component = ReasonReact.statelessComponent("AboutPage");

let make = _children => {
  ...component,
  render: _self => <div> (ReasonReact.string("About!")) </div>,
};
