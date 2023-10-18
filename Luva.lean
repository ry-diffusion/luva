-- This module serves as the root of the `Luva` library.
-- Import modules here that should be built as part of the library.
import «Luva».Raw

@[extern "luvaInitializeNative"]
private opaque luvaInitializeNative : IO Unit
builtin_initialize luvaInitializeNative