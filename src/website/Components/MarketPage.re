let component = ReasonReact.statelessComponent("MarketPage");

module Styles = MarketPageStyles;

[@bs.deriving abstract]
type hit = {
  id: string,
  name: string,
};

[@bs.deriving abstract]
type hitResult = {hit};

let hitComponent = hitResult => {
  let hit = hitResult |. hit;
  Js.log(hit);
  <div className="hit">
    <h3> <Algolia.Highlight attribute="name" hit /> </h3>
  </div>;
};

/*

 Categories

 */
let make = _children => {
  ...component,
  render: _self =>
    <Algolia.InstantSearch
      appId="X0210UMLR1"
      apiKey="5085ce346201999ee5e28e32380ceab1"
      indexName="dev_market">
      <aside className=(Styles.filters |> TypedGlamor.toString)>
        <Algolia.Panel header="Categories">
          <Algolia.HierarchicalMenu
            attributes=[|"category.lvl0", "category.lvl1"|]
          />
        </Algolia.Panel>
      </aside>
      <main className=(Styles.main |> TypedGlamor.toString)>
        <Algolia.Breadcrumb attributes=[|"category.lvl0", "category.lvl1"|] />
        <Algolia.SearchBox />
        <Algolia.Stats />
        <Algolia.Hits hitComponent />
      </main>
    </Algolia.InstantSearch>,
};
