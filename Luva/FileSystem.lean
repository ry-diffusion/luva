import Luva.Loop

namespace FileSystem

opaque Request.Nonempty : NonemptyType
def Request : Type := Request.Nonempty.type
instance : Nonempty Request := Request.Nonempty.property

def FilesystemContinue := Request → IO Unit

namespace Request
@[extern "luvaMakeRequest"] opaque mk : IO Request
@[extern "luvaRequestSetData"] opaque setData : @&Request → α → IO Unit
@[extern "luvaRequestGetData"] opaque data : @&Request → (α : Type) → IO α
@[extern "luvaRequestResult"] opaque result : @&Request → IO Int
end Request


namespace Flags
def readOnly : UInt32 := 00
def writeOnly : UInt32 := 01
def readWrite : UInt32 := 02
end Flags

namespace Mode
def default : UInt32 := 0
end Mode

end FileSystem

namespace Loop
@[extern "luvaOpenFile"] opaque openFile (loop: @&Loop) (path: String) (request: FileSystem.Request)
                        (flags: UInt32) (mode: UInt32) (next: FileSystemContinue): IO UInt32
end Loop
