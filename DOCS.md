## Reason-Elm Docs

<a name="elmProgramBase"></a>
### `elmProgramBase('instance) : type`
Type to represent the compiled & imported version of an Elm application. It has
an arugement `'instance`, that is the shape of the running elm application.

<a name="elmProgram"></a>
### `elmProgram : type`
Of the type [`elmProgramBase`](DOCS.md#elmProgramBase), with [`elmInstance`](DOCS.md#elmInstance)
applied as the arguement.

<a name="elmProgramWithPorts"></a>
### `elmProgramWithPorts('ports) : type`
Of the type [`elmProgramBase`](DOCS.md#elmProgramBase), with [`elmInstanceWithPorts`](DOCS.md#elmInstanceWithPorts)
applied as the arguement.  It takes the arguement `'ports` arguement which represent
the shape of the ports object on the Elm app instance.

<a name="elmInPort"></a>
### `elmInPort('data) : type`
Predefined type for a data-in Elm port. It takes the arguement `'data`, which is
the type of the arguement passed to the `subscribe` callback.
It's type signature is:
```
type elmInPort('data) = {
  .
  [@bs.meth] "subscribe": ('data => unit) => unit,
  [@bs.meth] "unsubscribe": unit => unit
};
```

<a name="elmOutPort"></a>
### `elmOutPort('data) : type`
Predefined type for a data-out Elm port. It takes the arguement `'data`, which is
the type of the arguement passed to the `subscribe` callback.
It's type signature is:
```
type elmOutPort('data) = {. [@bs.meth] "send": 'data => unit};
```

<a name="elmInstance"></a>
### `elmInstance : type`
The type returned from [`mount`](DOCS.md#mount) when ports are not used. This is
an empty object. It's type signature is:
```
type elmInstance = {.};
```

<a name="elmInstanceWithPorts"></a>
### `elmInstanceWithPorts('ports) : type`
The type returned from [`mount`](DOCS.md#mount) when ports are used. This is
an object with the property `ports`. It's type signature is:
```
type elmInstanceWithPorts('ports) = {. "ports": 'ports};
```

<a name="mount"></a>
### `mount : func`
This is the function that takes either [`elmProgram`](DOCS.md#elmProgram) or [`elmProgramWithPorts`](DOCS.md#elmProgram), and options.
There are a few important things to note with `mount`:
  * If you use any of the labled aruements, `elmProgram` must be the last arguement
  * The arguement `moduleName` defaults to `"Main"`. If you have a nested module, you can define `moduleName` like `"My.Nested.Module"`
  * If the `elementId` is invalid, the mounting will fail. ReasonElm DOES NOT fallback to fullscreen.

It's type signature is:
```
let mount:
  (
    ~flags: 'flags=?,
    ~elementId: string=?,
    ~moduleName: string="Main",
    elmProgramBase('instance)
  )
  => R.t('instance, string);
```
