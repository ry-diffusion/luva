import Lake
open Lake DSL

package «luva»  {
  precompileModules := true
}


@[default_target]
lean_lib «Luva» where

target LuvaBindings.o pkg : FilePath := do
  let oFile := pkg.buildDir / "Luva" / "LuvaBindings.o"
  let srcJob ← inputFile <| pkg.dir / "Luva" / "Bindings.c"
  let weakArgs := #["-I", (← getLeanIncludeDir).toString]
  buildO "Bindings.c" oFile srcJob weakArgs #["-fPIC", "-luv", "-Wall", "-Werror", "-std=gnu11"] "gcc" getLeanTrace

extern_lib Bindings pkg := do 
  let name := nameToStaticLib "LuvaBindings"
  let obj ← fetch <| pkg.target ``LuvaBindings.o
  buildStaticLib (pkg.nativeLibDir / name) #[obj]