# Optional Dependency & Soft-Include Pattern

This project enforces that feature plugins (Map, Save, Spawner, MagGrab, PerfMngr, etc.) have **no hard compile-time dependency** on CoreContracts (or other sibling plugins). The pattern below standardizes how to *optionally* integrate when another plugin is present, while compiling cleanly (and behaving safely) when it is absent.

---
## Goals
- Zero hard dependencies between gameplay feature plugins.
- Preserve UHT (UnrealHeaderTool) stability: no duplicate basenames, no conditional `UINTERFACE` declarations.
- Provide graceful, no-op fallbacks when a system is missing.
- Allow features to “light up” automatically when the related plugin is added to the project later—no code changes required.

---
## Core Techniques
### 1. `__has_include` Gating
Use `__has_include("Path/To/Header.h")` to probe for the presence of an optional plugin header at compile time.
```cpp
#if __has_include("DAI_CoreContracts/Public/Interfaces/DAISaveService.h")
#include "DAI_CoreContracts/Public/Interfaces/DAISaveService.h"
#define DAI_HAS_SAVE_SERVICE 1
#else
#define DAI_HAS_SAVE_SERVICE 0
#endif
```
Always define a macro (`DAI_HAS_*`) so later code can branch uniformly.

### 2. Stable Bridge UINTERFACEs
Never wrap `UINTERFACE` inside preprocessor conditionals. Instead:
```cpp
UINTERFACE(BlueprintType)
class DAI_MAP_API UDAILocalMapSaveFragmentProviderBridge : public UInterface
{ GENERATED_BODY() };

class DAI_MAP_API IDAILocalMapSaveFragmentProviderBridge
{ GENERATED_BODY() public:
    virtual bool GatherSaveFragment(const FName&, TSharedPtr<class FJsonObject>&) const { return false; }
    virtual void ApplySaveFragment(const FName&, const TSharedPtr<class FJsonObject>&) {}
};

#if __has_include("DAI_CoreContracts/Public/Interfaces/DAISaveFragmentProvider.h")
#include "DAI_CoreContracts/Public/Interfaces/DAISaveFragmentProvider.h"
using TDAISaveFragmentProviderInterface = IDAISaveFragmentProvider; // real
#else
using TDAISaveFragmentProviderInterface = IDAILocalMapSaveFragmentProviderBridge; // fallback
#endif
```
Your subsystem then implements `TDAISaveFragmentProviderInterface`—automatically binding to the real interface when available.

### 3. Dual Fallback Signatures (Warning Suppression)
If the real interface has different method signatures (e.g., extra `FName` parameter), provide *both* fallback versions to prevent MSVC warnings (`C4263`, `C4264`).
```cpp
// In the #else fallback section
void ApplySaveFragment(const TSharedPtr<FJsonObject>&) { /* legacy no-op */ }
void ApplySaveFragment(const FName&, const TSharedPtr<FJsonObject>&) { /* bridge signature no-op */ }
```

### 4. Message / Event Bus Optionality
Wrap bus usage behind a feature macro with a default:
```cpp
#ifndef DAI_ENABLE_GAMEPLAY_MESSAGE_BUS
#define DAI_ENABLE_GAMEPLAY_MESSAGE_BUS 0
#endif
#if DAI_ENABLE_GAMEPLAY_MESSAGE_BUS && __has_include("DAIMessageBridge.h")
#include "DAIMessageBridge.h"
#define DAI_HAS_MESSAGE_BRIDGE 1
#else
#define DAI_HAS_MESSAGE_BRIDGE 0
#endif
```
Then gate all broadcasts:
```cpp
#if DAI_HAS_MESSAGE_BRIDGE
    DAIMessageBridge::Broadcast(this, DAIEventTags::MapSectionsRevealed(), Payload);
#endif
```

### 5. Soft Hub Integration (Reflection)
Use `UClass::TryFindTypeSlow` + `ProcessEvent` for optional hub-style communication—no includes, no link dependency. Always use the fully qualified script path to avoid short-name warnings emitted by UE ("Short type name provided for TryFindType").
```cpp
// Correct: Fully qualified path, avoids LogClass short-name warnings
UClass* HubCls = UClass::TryFindTypeSlow<UClass>(TEXT("/Script/DAI_Hub.DAI_HubSubsystem"));
if (HubCls) { /* locate subsystem & invoke reflected function */ }
```
Historically a fallback to the short name `"DAI_HubSubsystem"` was attempted; this was removed to eliminate warning spam. If you rename or relocate the hub class, update the literal path here accordingly.

### 6. No Duplicate Basenames
When creating bridge headers, give them *unique* names: e.g. `DAILocalSaveServiceBridge.h` instead of copying `DAISaveService.h` into another plugin. UHT requires distinct basenames across the full project include set.

### 7. Fallback Implementations = Pure No-Ops
Return safe defaults (nullptr, false, empty arrays) and avoid side effects—calling code should tolerate absence transparently.

---
## Minimal Checklist for a New Optional Integration
1. Create a uniquely named bridge header with unconditional `UINTERFACE`.
2. Add `__has_include` detection + macro (`DAI_HAS_*`).
3. Provide fallback interface / methods with safe stubs.
4. In consuming code, branch on the macro—not on build target modules.
5. Avoid `#ifdef` around class inheritance; abstract via `using` alias.
6. If signatures differ -> supply dual fallback overloads.
7. Document the feature macro in this file or a plugin README.

---
## Example: Subsystem Header Snippet
```cpp
class UMyFeatureSubsystem : public UWorldSubsystem, public TDAISaveFragmentProviderInterface
{
    GENERATED_BODY()
#if DAI_HAS_SAVE_FRAGMENT_PROVIDER
    virtual FName GetFragmentId() const override;
    virtual TSharedPtr<FJsonObject> GetSaveFragment() const override;
    virtual void ApplySaveFragment(const TSharedPtr<FJsonObject>& Fragment) override;
#else
    FName GetFragmentId() const { return FName("MyFeature"); }
    TSharedPtr<FJsonObject> GetSaveFragment() const { return nullptr; }
    void ApplySaveFragment(const TSharedPtr<FJsonObject>&) {}
    void ApplySaveFragment(const FName&, const TSharedPtr<FJsonObject>&) {}
#endif
};
```

---
## Troubleshooting
| Symptom | Likely Cause | Fix |
|---------|--------------|-----|
| UHT duplicate header error | Copied original interface filename into another plugin | Rename to unique *Bridge* header |
| C4263 / C4264 warnings | Signature mismatch in fallback | Add overload matching real signature |
| Undefined symbol at link | Declared method but removed its implementation during refactor | Re-add (even as no-op) |
| Broadcast macro undefined | Feature macro not defaulted | Add `#ifndef` guard with default value |

---
## When To Extend
Add richer fallbacks only if they enable meaningful offline testing without the core plugin. Otherwise keep stubs minimal to reduce maintenance.

---
## Summary
This pattern keeps each plugin self-sufficient while enabling organic feature composition. Add new optional links by following the checklist and copying an existing bridge header as a template.
