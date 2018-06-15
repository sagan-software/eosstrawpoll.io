const CleanWebpackPlugin = require("clean-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const MiniCssExtractPlugin = require("mini-css-extract-plugin");
const path = require("path");

const DIST_DIR = path.resolve(__dirname, "dist/website");
const IS_PROD = process.env.NODE_ENV === "production";

console.log("PRODUCTION?", IS_PROD);

const config = {
	mode: IS_PROD ? "production" : "development",
	devtool: IS_PROD ? undefined : "inline-source-map",
	entry: "./src/website/Index.js",
	output: {
		path: DIST_DIR,
		filename: "[name].bundle.js",
	},
	resolve: {
		extensions: [".js"],
	},
	performance: {
		hints: IS_PROD ? "error" : false,
	},
	module: {
		rules: [
			{
				test: /\.pug$/,
				use: ["pug-loader"],
				exclude: /node_modules/,
			},
		],
	},
	devServer: {
		contentBase: DIST_DIR,
		compress: true,
		port: 9000,
		historyApiFallback: true,
	},
	plugins: [
		new CleanWebpackPlugin(["dist/website"], {
			verbose: true,
		}),
		new HtmlWebpackPlugin({
			template: "src/website/Index.pug",
			filename: "index.html",
		}),
		new MiniCssExtractPlugin(),
	],
};

module.exports = config;
