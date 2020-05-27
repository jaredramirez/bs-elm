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

- Install
  - With yarn: `yarn add bs-elm`
  - With npm: `npm install --save bs-elm`
- Add `bs-elm` as a dependency in `bsconfig.json`

```
{
  ...
  "bs-dependencies": ["bs-elm"]
}
```

- Use the `Elm` module in reason

```
module R = Belt.Result;

type ports = {
  infoForReason: Elm.elmToReasonPort(string),
  infoForElm: Elm.reasonToElmPort(string),
};

[@bs.val] external elmProgram: Elm.elmProgramWithPorts(ports) = "Elm";
/* Or if using a bundler.
  [@bs.module]
  external elmProgram : Elm.elmProgramWithPorts(ports) = "path/to/App.elm";
*/

type flags = {...};

let resultRuntime =
  Elm.mount(
    ~flags={..}, /* Optional, defaults to Nothing */
    ~moduleName="Other.Main", /* Optional, defaults to "Main" */
    elmProgram,
  );

switch (resultRuntime) {
| R.Ok(runtime) =>
  runtime.ports.infoForReason.subscribe(info =>
    runtime.ports.infoForElm.send("You pressed " ++ info)
  )
| R.Error(message) => Js.log(message)
};
```

Checkout the [`example/`](example)!
Checkout this [repo using webpack](https://github.com/jaredramirez/bs-elm-example)!

### Docs

Checkout the [rei](src/Elm.rei) file for documenation.

If you have any suggestions or run into any bugs, please open an issue!

### Change log

`v3.0.0` ->

- Upgrade to bsb 7.3.2
- Improve interop with new bsb records <-> js object compatability

`v2.0.0` ->

- Drop support for 0.18
- Add support for 0.19

`v1.0.2` ->

- Compile reason modules in-source

`v1.0.1` ->

- Upgrade to bs-platform@3.0.0 (No change in the generated code)
- Generate files with the suffix `.bs.js` instead of `.js`
- NOTE: If using webpack this, changes how the project must be built. Please refer to [jaredramirez/bs-elm-example](https://github.com/jaredramirez/bs-elm-example) for an example.

`v1.0.0` ->

- Rename project to `bs-elm`
- Changed exported module from `ReasonElm` to `Elm`
- Changed export port types to `elmOutPort` -> `portToElm` and `elmInPort` -> `portFromElm`
