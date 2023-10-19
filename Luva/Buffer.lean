opaque Buffer.Nonempty : NonemptyType
def Buffer : Type := Buffer.Nonempty.type
instance : Nonempty Buffer := Buffer.Nonempty.property

namespace Buffer

@[extern "luvaCreateBuffer"]
opaque mk : UInt64 → IO Buffer

@[extern "luvaBufferFromByteArray"]
opaque fromByteArray : ByteArray → IO Buffer

@[extern "luvaBufferAsArray"]
/- Converts current buffer into a bytearray.
   WARNING THIS COPY THE WHOLE BUFFER -/
opaque asByteArray (buffer: @&Buffer): IO ByteArray

end Buffer
