let component = ReasonReact.statelessComponent("Link");

let handleClick = (route, event) =>
  if (! ReactEventRe.Mouse.defaultPrevented(event)) {
    ReactEventRe.Mouse.preventDefault(event);
    Route.redirectTo(route);
  };

let make = (~route, ~className="", children) => {
  ...component,
  render: _self =>
    ReasonReact.createDomElement(
      "a",
      ~props={
        "href": Route.toString(route),
        "className": className,
        "onClick": handleClick(route),
      },
      children,
    ),
};
