namespace FileSystem

opaque Request.Nonempty : NonemptyType
def Request : Type := Request.Nonempty.type
instance : Nonempty Request := Request.Nonempty.property


@[extern "luvaMakeRequest"] opaque Request.mk : IO Request
@[extern "luvaMakeBuffer"] opaque Buffer.mk :IO UInt64
@[extern "luvaOpenFile"] opaque openFile : IO UInt32
end FileSystem