const webpack = require('webpack')
const path = require('path')
const HtmlWebpackPlugin = require('html-webpack-plugin')
const { CleanWebpackPlugin } = require('clean-webpack-plugin')

module.exports = {
  entry: {myAppName: path.resolve(__dirname, './src/index.js')},
  output: {
    path: path.resolve(__dirname, './dist'),
    filename: '[name].bundle.js',
    publicPath: '/'
  },
  plugins: [
    new CleanWebpackPlugin(),
    new HtmlWebpackPlugin({
      template: './src/index.html',
    }),


  ],
  module: {
    rules: [
      {
        test: /\.css$/,
        use: [
          'style-loader',
          {
            loader: 'css-loader',
            options: {
              modules: true, // default is false
              sourceMap: true,
              importLoaders: 1,
              modules : {
                localIdentName: '[name]--[local]--[hash:base64:8]'
              }
            }
          },
          'postcss-loader'
        ]
      },
      {
        test: /\.(ts|js)x?$/,
        exclude: /node_modules/,
        use: ['babel-loader']
      },
    ],
  },
  devServer:{
    port: 2301,
    hot: true,
    historyApiFallback: true,
  },
  resolve: {
    extensions: ['.js', '.jsx', '*', '.ts', '.tsx']
  }
}
