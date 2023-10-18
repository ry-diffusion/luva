import «Luva»

def main : IO Unit := do
  let x := (← uv_create_loop)
  IO.println "bye!" 
  
