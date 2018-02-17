## bs-elm

> Bindings for mounting and interacting with Elm applications in Reason.

### Motivation

Writing web applications in Elm is nice. It's type system and enforced architecture
are just a couple of the really cool things that it offers. The Elm ecosystem is
pretty small compared to the Javascript(JS) ecosystem, and this is a draw back
when coming from the world of JS. Interop with JS is possible, but it requires
writing regular JS code, which has none of Elm's safety. This is where Reason
enters the picture. Reason can communicate more direclty with JS with much more
type safety than vanilla JS. The possibility of writing an Elm app and handling
JS interop with Reason is pretty powerful. Having access to the entire JS
ecosytem in a (more) typesafe way is pretty exciting, so `bs-elm` was created.

### Getting Started

* Install
  * With yarn: `yarn add bs-elm`
  * With npm: `npm install --save bs-elm`
* Add `bs-elm` as a dependency in `bsconfig.json`

```
{
  ...
  "bs-dependencies": ["bs-elm"]
}
```

* Use `Elm`

```
module R = Js.Result;

[@bs.module]
external elmProgram : Elm.elmProgram = "path/to/App.elm";

let instance = Elm.mount(
  ~moduleName="App", /* Defaults to "Main" */
  elmProgram /* Must be last arguement */
);

switch instance {
| R.Ok(i) => Js.log("Elm is running.")
| R.Error(errorMessage) => Js.log(errorMessage)
};
```

To import Elm directly in Reason ->

* Look at this [repo using webpack](https://github.com/jaredramirez/reason-elm-example)
* Look at this [repo using parcel](https://github.com/splodingsocks/reasonable-app)

Checkout [this example](https://github.com/jaredramirez/bs-elm-example) that uses flags and ports!

### Docs

* [`elmProgramBase : type`](DOCS.md#elmProgramBase)
* [`elmProgram : type`](DOCS.md#elmProgram)
* [`elmProgramWithPorts : type`](DOCS.md#elmProgramWithPorts)
* [`portFromElm : type`](DOCS.md#portFromElm)
* [`portToElm : type`](DOCS.md#portToElm)
* [`elmInstance : type`](DOCS.md#elmInstance)
* [`elmInstanceWithPorts : type`](DOCS.md#elmInstanceWithPorts)
* [`mount : func`](DOCS.md#mount)

If you have any suggestions or run into any bugs, please open an issue!

### Roadmap

* Make interacting with ports nicer

  * Convert `Js.t` objects to OCaml records?
  * Subscribe to ports in a pipeline style?

### Change log

`v1.0.0` ->

* Rename project to `bs-elm`
* Changed exported module from `ReasonElm` to `Elm`
* Changed export port types to `elmOutPort` -> `portToElm` and `elmInPort` -> `portFromElm`
