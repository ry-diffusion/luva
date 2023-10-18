import «Luva»

def appMain (path: String) : IO UInt32 := do
  let req ← FileSystem.Request.mk
  let loop ← Loop.mk
  return ← loop.run Loop.RunMode.once

def main (args: List String) : IO UInt32 := match (args) with
  | arg :: _ => appMain arg
  | [] => do 
    IO.println "No arguments baby? Come back when you have an argument."
    return 1
   
