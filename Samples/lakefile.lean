import Lake

open Lake DSL

package «luvaSamples» where

require luva from ".."

@[default_target]
lean_exe «testing» where
  root := `Testing
  -- Enables the use of the Lean interpreter by the executable (e.g.,
  -- `runFrontend`) at the expense of increased binary size on Linux.
  -- Remove this line if you do not need such functionality.
  supportInterpreter := true
