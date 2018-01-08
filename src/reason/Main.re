module R = Js.Result;

[@bs.module] external elmProgram : ReasonElm.elmProgram = "../elm/Main.elm";

let instance = ReasonElm.mount(~flags={"hello": "world"}, elmProgram);

switch instance {
| R.Ok(i) => Js.log(i)
| R.Error(message) => Js.log(message)
};
