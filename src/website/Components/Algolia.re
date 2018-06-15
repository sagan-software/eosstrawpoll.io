module InstantSearch = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "InstantSearch";
  [@bs.deriving abstract]
  type jsProps = {
    apiKey: string,
    appId: string,
    indexName: string,
  };
  let make = (~apiKey, ~appId, ~indexName, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~apiKey, ~appId, ~indexName),
      children,
    );
};

module Stats = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "Stats";
  let make = children =>
    ReasonReact.wrapJsForReason(~reactClass, ~props=(), children);
};

module SearchBox = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "SearchBox";
  [@bs.deriving abstract]
  type jsProps = {searchAsYouType: bool};
  let make = (~searchAsYouType=true, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~searchAsYouType),
      children,
    );
};

module Hits = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "Hits";
  [@bs.deriving abstract]
  type jsProps('a) = {hitComponent: 'a => ReasonReact.reactElement};
  let make = (~hitComponent, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~hitComponent),
      children,
    );
};

module Pagination = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "Pagination";
  let make = children =>
    ReasonReact.wrapJsForReason(~reactClass, ~props=(), children);
};

module HierarchicalMenu = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "HierarchicalMenu";
  [@bs.deriving abstract]
  type jsProps = {attributes: array(string)};
  let make = (~attributes, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~attributes),
      children,
    );
};

module Breadcrumb = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "Breadcrumb";
  [@bs.deriving abstract]
  type jsProps = {attributes: array(string)};
  let make = (~attributes, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~attributes),
      children,
    );
};

module Highlight = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "Highlight";
  [@bs.deriving abstract]
  type jsProps('a) = {
    attribute: string,
    hit: 'a,
  };
  let make = (~attribute, ~hit, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~attribute, ~hit),
      children,
    );
};

module SortBy = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "SortBy";
  [@bs.deriving abstract]
  type item = {
    value: string,
    label: string,
  };
  [@bs.deriving abstract]
  type jsProps = {
    items: array(item),
    defaultRefinement: string,
  };
  let make = (~items, ~defaultRefinement, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=jsProps(~items, ~defaultRefinement),
      children,
    );
};

module Panel = {
  [@bs.module "react-instantsearch/dom"]
  external reactClass : ReasonReact.reactClass = "Panel";
  [@bs.deriving abstract]
  type jsProps = {
    className: Js.Nullable.t(string),
    header: Js.Nullable.t(string),
    footer: Js.Nullable.t(string),
  };
  let make = (~className=?, ~header=?, ~footer=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass,
      ~props=
        jsProps(
          ~className=Js.Nullable.fromOption(className),
          ~header=Js.Nullable.fromOption(header),
          ~footer=Js.Nullable.fromOption(footer),
        ),
      children,
    );
};
