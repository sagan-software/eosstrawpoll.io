const CleanWebpackPlugin = require("clean-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const webpack = require("webpack");
const path = require("path");

const IS_PROD = process.env.NODE_ENV === "production";

console.log("PRODUCTION?", IS_PROD);

const webConfig = {
  target: "web",
  mode: IS_PROD ? "production" : "development",
  devtool: IS_PROD ? undefined : "inline-source-map",
  entry: "./website/Browser.js",
  output: {
    path: path.resolve(__dirname, "build/website"),
    filename: "client.js",
    publicPath: "/",
  },
  performance: {
    hints: IS_PROD ? "error" : false,
  },
  devServer: {
    // contentBase: path.resolve(__dirname, "build/website"),
    contentBase: false,
    compress: true,
    port: 9001,
    index: "",
    hot: true,
    inline: true,
    host: "localhost",
    proxy: {
      "**": {
        context: () => true,
        target: "http://localhost:3001",
        changeOrigin: true,
        secure: false,
      },
    },
  },
  plugins: [
    new CleanWebpackPlugin(["build/website/client.js"], {
      verbose: true,
    }),
    new MiniCssExtractPlugin(),
    new webpack.EnvironmentPlugin([
      "APP_LABEL",
      "TWITTER_NAME",
      "GITHUB_NAME",
      "SITE_URL",
      "SITE_WS_URL",
      "STATIC_URL",
      "EOS_URL",
      "CONTRACT_ACCOUNT",
    ]),
  ],
};

const nodeConfig = {
  target: "node",
  mode: IS_PROD ? "production" : "development",
  entry: "./website/Server.js",
  output: {
    path: path.resolve(__dirname, "build/website"),
    filename: "server.js",
  },
  plugins: [
    // new CleanWebpackPlugin(["build/web-server"], {
    // 	verbose: true,
    // }),
    // new WriteFilePlugin(),
  ],
};

const TARGET =
  process.env.TARGET === "web"
    ? "web"
    : process.env.TARGET === "node"
      ? "node"
      : "all";

module.exports = () => {
  console.log(`Targeting ${TARGET} files`);
  switch (TARGET) {
    case "web":
      return webConfig;
    case "node":
      return nodeConfig;
    default:
      [webConfig, nodeConfig];
  }
};
