import «Luva»

def appMain (path: String) : IO UInt32 := do
  let req ← FileSystem.Request.mk
  let loop ← Loop.mk
  let buff ← Buffer.fromByteArray (ByteArray.mk #[1, 2, 3, 4, 5])
  let byteArray ← buff.asByteArray()
  ← IO.println s!"buffer {byteArray}"
  return ← loop.run Loop.RunMode.once

def main (args: List String) : IO UInt32 := match (args) with
  | arg :: _ => appMain arg
  | [] => do 
    IO.println "No arguments baby? Come back when you have an argument."
    return 1
   
