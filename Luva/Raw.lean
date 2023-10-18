opaque UvLoop.Nonempty : NonemptyType
def UvLoop : Type := UvLoop.Nonempty.type

@[extern "luvaCreateLoop"]
opaque uv_create_loop : IO UvLoop
