
import «Luva».Basic
import «Luva».Loop

import «Luva».FileSystem
import «Luva».Buffer


@[extern "luvaInitializeNative"]
private opaque luvaInitializeNative : IO Unit
builtin_initialize luvaInitializeNative