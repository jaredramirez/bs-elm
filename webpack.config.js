'use strict';

const path = require('path');
const webpack = require('webpack');
const HtmlWebpackPlugin = require('html-webpack-plugin');

const resolvePath = relativePath => path.resolve(__dirname, relativePath);

module.exports = {
  devtool: 'cheap-module-source-map',

  entry: [resolvePath('src/reason/index.re'), resolvePath('src/main.js')],

  output: {
    path: resolvePath('lib'),
    filename: 'bundle.js',
  },

  module: {
    rules: [
      {test: /\.(js|jsx)$/, use: 'babel-loader'},
      {
        test: /\.(re|ml)$/,
        include: resolvePath('src/reason'),
        exclude: [/elm-stuff/, /node_modules/],
        use: 'bs-loader',
      },
      {
        test: /\.elm$/,
        include: resolvePath('src/elm'),
        exclude: [/elm-stuff/, /node_modules/],
        use: {
          loader: 'elm-loader',
          options: {
            cwd: resolvePath('.'),
            forceWatch: true,
            debug: true,
          },
        },
      },
    ],
  },

  resolve: {
    extensions: ['.js', '.jsx', '.re', '.ml', '.elm'],
  },

  plugins: [
    new HtmlWebpackPlugin({
      inject: true,
      template: resolvePath('public/index.html'),
    }),
  ],
};
