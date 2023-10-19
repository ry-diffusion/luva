import Lake

open Lake DSL

require luva from ".."
package «luvaSamples» where
  moreLinkArgs := #["-Wl,--allow-shlib-undefined", "-luv"]
  

@[default_target]
lean_exe «testing» where
  
  root := `Testing
  -- Enables the use of the Lean interpreter by the executable (e.g.,
  -- `runFrontend`) at the expense of increased binary size on Linux.
  -- Remove this line if you do not need such functionality.
  supportInterpreter := true


lean_exe «cat» where
  root := `Cat
  -- Enables the use of the Lean interpreter by the executable (e.g.,
  -- `runFrontend`) at the expense of increased binary size on Linux.
  -- Remove this line if you do not need such functionality.
  supportInterpreter := true
