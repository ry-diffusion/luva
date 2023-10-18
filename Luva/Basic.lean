namespace Loop
def RunMode.default : UInt32 := 0
def RunMode.once : UInt32 := 1
def RunMode.noWait : UInt32 := 2
end Loop

@[extern "luvaTestCls"] opaque testCls : (UInt32 →  UInt32) → IO UInt32