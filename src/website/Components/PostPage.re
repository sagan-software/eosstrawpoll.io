let component = ReasonReact.statelessComponent("PostPage");

let make = (~accountName, ~postId, _children) => {
  ...component,
  render: _self =>
    <div>
      <h1> (ReasonReact.string(accountName)) </h1>
      <h2> (ReasonReact.string(postId)) </h2>
      (ReasonReact.string("Post"))
    </div>,
};
