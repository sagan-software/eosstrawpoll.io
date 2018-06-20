type t = {
  accountName: string,
  publicKey: string,
};
/*
 let fromScatter = scatterIdentity =>
   switch (scatterIdentity |. Scatter.accounts) {
   | None => None
   | Some([||]) => None
   | Some([|account|]) =>
     Some({
       accountName: account |. Scatter.accountName,
       publicKey: scatterIdentity |. Scatter.publicKey,
     })
   }; */
