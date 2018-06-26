let component = ReasonReact.statelessComponent("Link");

let handleClick = (href, event) =>
  if (! ReactEventRe.Mouse.defaultPrevented(event)) {
    ReactEventRe.Mouse.preventDefault(event);
    ReasonReact.Router.push(href);
  };

let make = (~route, ~className="", children) => {
  ...component,
  render: _self =>
    ReasonReact.createDomElement(
      "a",
      ~props={
        "href": Route.toString(route),
        "className": className,
        "onClick": handleClick(Route.toString(route)),
      },
      children,
    ),
};
