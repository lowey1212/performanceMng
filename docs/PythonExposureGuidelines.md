# Python Exposure Guidelines

Purpose: Prevent naming collisions, ambiguous overloads, and unstable API surfaces when exposing C++ types/functions to Unreal’s Python layer. Applies to all DAI_* plugins.

## Core Principles
1. Stable Script Names: Every `UFUNCTION`/`UPROPERTY` likely accessed from Python either uses a unique natural C++ name or specifies `meta = (ScriptName = "...")` when conflicts are possible.
2. Avoid Overload Ambiguity: Prefer distinct function names instead of overloading; Python binding generation can collapse overloads unpredictably.
3. Deterministic Delegate Names: Multicast delegates exposed to Python must have globally unique type names (prefix with plugin or feature) – prevents cross‑plugin collisions like the meteor task issue we resolved.
4. Explicit Initialization: All USTRUCT primitive fields must be initialized in their default constructor to ensure predictable values when inspected via Python.
5. No Hidden Overrides: If implementing soft interface bridges, include dual stub signatures only when required to silence MSVC warnings; do not mark unnecessary duplicates as BlueprintCallable (keeps Python surface minimal).

## Metadata Checklist
For any reflected field/function intended for Python:
- Has unique name OR ScriptName override.
- Not deprecated; if superseded, prefer removing the Python-exposed symbol in favor of the new one. If deprecation is unavoidable, use C++ `UE_DEPRECATED` (avoid Blueprint `DeprecationMessage` metadata).
- Parameters have clear types (avoid `int32` vs `int` mixing in docs; Python sees an int either way but clarity matters).
- Bool properties start with b and avoid shadowing (e.g., prefer `bEnableFeature` not `bFeatureEnabled` if a `EnableFeature()` function also exists).

## Delegate Pattern
Preferred naming: `F<PluginFeature><Event>` e.g., `FUltraSkyLightningStrike`, `FMapFogSectionsRevealed`.
If a base engine delegate signature is mirrored, still rename with feature prefix to avoid collisions.

## Example Fix (Implemented)
Problem: `bOverrideStyle` property and `OverrideStyle` function caused Python exposure name collision. Resolution: Added `ScriptName` metadata to at least one symbol to disambiguate.

## Verification Flow
1. Run editor: `py` console -> attempt `import unreal; dir(unreal)` scan for new symbols.
2. Ensure no warnings in log referencing Script export duplicates.
3. For new delegates, confirm Python can bind: `unreal.get_editor_subsystem(...).my_delegate.add_callable(py_fn)` (adapt to actual subsystem).

## Pre-Merge Checklist
- [ ] New reflected types reviewed for naming collisions.
- [ ] Delegates prefixed & unique.
- [ ] Added/updated automated doc index if new Python-centric docs mirrored.
- [ ] Changelog / README Further Reading updated if Python integration affected.

## Future Enhancements
- Static script validation: a lightweight scan comparing UHT JSON (if exported) against a previous snapshot.
- Auto-generation of a Python API diff in CI.
