opaque Loop.Nonempty : NonemptyType
def Loop : Type := Loop.Nonempty.type
instance : Nonempty Loop := Loop.Nonempty.property

namespace Loop
/- Creates a new loop -/
@[extern "luvaCreateLoop"] opaque mk : IO Loop

/- Runs a loop -/
@[extern "luvaRunLoop"] opaque run (loop: Loop) (runMode: UInt32): IO UInt32
end Loop


