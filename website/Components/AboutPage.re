let component = ReasonReact.statelessComponent("AboutPage");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <Helmet> <title> (ReasonReact.string("About")) </title> </Helmet>
      (ReasonReact.string("About!"))
    </div>,
};
