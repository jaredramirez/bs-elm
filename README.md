## Reason-Elm
> Bindings for mounting and interacting with Elm applications in Reason.

### Motivation
Writing web applications in Elm is nice. It's type system and enforced architecture
are just a couple of the really cool things that offers. The Elm ecosystem is
pretty small compared to the Javascript(JS) ecosystem, and this is a draw back
when coming from the world of JS. Interop with JS is possible, but it requires
writing regular JS code, which has none of the safely of Elm. This is where Reason
enters the picture. Reason can communicate more direclty with JS, with much more
type safety than vanilla JS. The possibility of writing an Elm app, and handling
JS interop with Reason, is pretty powerful. Having access to the entire JS
ecosytem in a (more) typesafe way is pretty exciting, and so Reason-Elm was created.

### Getting Started
Install with yarn:
`yarn add reason-elm`

Install with npm:
`npm install --save reason-elm`

Add `reason-elm` as a dependency in `bsconfig.json`
```
{
  ...
  "bs-dependencies": ["reason-elm", ...],
}
```

Use `ReasonElm` :
```
module R = Js.Result;

[@bs.module]
external elmProgram : ReasonElm.elmProgram = "path/to/elm/Main.elm";

let instance = ReasonElm.mount(elmProgram);

switch instance {
| R.Ok(i) => Js.log("Elm is running.")
| R.Error(errorMessage) => Js.log(errorMessage)
};
```

Checkout an [example](https://github.com/jaredramirez/reason-elm-example)!

### Docs
* [`elmProgramBase : type`](DOCS.md#elmProgramBase)
* [`elmProgram : type`](DOCS.md#elmProgram)
* [`elmProgramWithPorts : type`](DOCS.md#elmProgramWithPorts)
* [`elmInPort : type`](DOCS.md#elmInPort)
* [`elmOutPort : type`](DOCS.md#elmOutPort)
* [`elmInstance : type`](DOCS.md#elmInstance)
* [`elmInstanceWithPorts : type`](DOCS.md#elmInstanceWithPorts)
* [`mount : func`](DOCS.md#mount)

### Roadmap
* Support nested elm module
  * Currently only `Elm.Module` is supported. (`Elm.My.Module` will not work)
* Convert `Js.t` objects to OCaml records
  * Currently the Elm 'instance & 'ports are `Js.t` objects
