import «Luva»

def main : IO Unit := do
  let binding := ← salude "hey"
  IO.println s!"From C: {binding}"
