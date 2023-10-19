import «Luva»

def onOpen (req: FileSystem.Request) := do
  let result ← req.result 
  IO.println s!"open file! result: {result}"

def appMain (path: String) : IO UInt32 := do
  let req ← FileSystem.Request.mk
  let loop ← Loop.mk
  let buff ← Buffer.fromByteArray (ByteArray.mk #[1, 2, 3, 4, 5])
  let byteArray ← buff.asByteArray
  IO.println s!"buffer {byteArray}"
  let _ := ← loop.openFile path req FileSystem.Flags.readOnly 
          FileSystem.Mode.default onOpen
  
  loop.run Loop.RunMode.once

def main (args: List String) : IO UInt32 := match (args) with
  | arg :: _ => appMain arg
  | [] => do 
    IO.println "No arguments baby? Come back when you have an argument."
    return 1
   
