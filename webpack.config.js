const CleanWebpackPlugin = require("clean-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const path = require("path");

const IS_PROD = process.env.NODE_ENV === "production";

console.log("PRODUCTION?", IS_PROD);

const webConfig = {
	target: "web",
	mode: IS_PROD ? "production" : "development",
	devtool: IS_PROD ? undefined : "inline-source-map",
	entry: "./src/website/WebClient.js",
	output: {
		path: path.resolve(__dirname, "dist/website"),
		filename: "client.js",
		publicPath: "/",
	},
	performance: {
		hints: IS_PROD ? "error" : false,
	},
	devServer: {
		// contentBase: path.resolve(__dirname, "dist/website"),
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
		new CleanWebpackPlugin(["dist/website/client.js"], {
			verbose: true,
		}),
		new MiniCssExtractPlugin(),
	],
};

const nodeConfig = {
	target: "node",
	mode: IS_PROD ? "production" : "development",
	entry: "./src/website/WebServer.js",
	output: {
		path: path.resolve(__dirname, "dist/website"),
		filename: "server.js",
	},
	plugins: [
		// new CleanWebpackPlugin(["dist/web-server"], {
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
