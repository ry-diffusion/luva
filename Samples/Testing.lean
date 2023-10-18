import «Luva»

def main : IO Unit := do
  let loop := ← Loop.mk
  let y ← loop.run Loop.RunMode.default
  IO.println s!"bye! with return: {y}" 
  
