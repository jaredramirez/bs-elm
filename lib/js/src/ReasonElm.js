'use strict';

var Block = require("bs-platform/lib/js/block.js");

function mount(flags, elementId, elmProgram) {
  var maybeModule = elmProgram["Main"];
  if (maybeModule !== undefined) {
    var maybeFlags = flags;
    var maybeElementId = elementId;
    var module_ = maybeModule;
    if (maybeElementId) {
      var elementId$1 = maybeElementId[0];
      var maybeElement = document.getElementById(elementId$1);
      if (maybeElement == null) {
        return /* Error */Block.__(1, ["ReasonElm Error: Failed to DOM find element named '" + (elementId$1 + "' to embed.")]);
      } else if (maybeFlags) {
        return /* Ok */Block.__(0, [module_.embed(maybeElement, maybeFlags[0])]);
      } else {
        return /* Ok */Block.__(0, [module_.embed(maybeElement)]);
      }
    } else if (maybeFlags) {
      return /* Ok */Block.__(0, [module_.fullscreen(maybeFlags[0])]);
    } else {
      return /* Ok */Block.__(0, [module_.fullscreen()]);
    }
  } else {
    return /* Error */Block.__(1, ["Module not found."]);
  }
}

var R = 0;

exports.R     = R;
exports.mount = mount;
/* No side effect */
