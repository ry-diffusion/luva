-- This module serves as the root of the `Luva` library.
-- Import modules here that should be built as part of the library.
import «Luva».Basic
import «Luva».Loop

@[extern "luvaInitializeNative"]
private opaque luvaInitializeNative : IO Unit
builtin_initialize luvaInitializeNative