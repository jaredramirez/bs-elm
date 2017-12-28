[@bs.module] external elmApp : ReasonElm.elmApp = "../elm/Main.elm";

let instance = ReasonElm.make(~elmApp, ~moduleName="Main", ());

Js.log(instance);
/* switch instance { */
/* | Some(i) => Js.log(i##ports) */
/* | None => () */
/* }; */
