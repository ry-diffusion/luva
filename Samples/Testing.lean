import «Luva»


def main : IO Unit := do
  let loop := ← Loop.mk
  let returnStatus ← loop.run Loop.RunMode.default
  let nul ← testCls (λx => x + 2) 
  IO.println s!"bye! with return: {returnStatus} {nul}" 

  
