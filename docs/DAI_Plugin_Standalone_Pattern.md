# DAI Plugin Standalone Pattern Implementation

This document outlines the pattern used to make DAI_Navigation plugin (previously DAI__Navigation) standalone, which can be applied to other DAI plugins.

## Problem Statement
The DAI_Navigation plugin previously had a hard compile-time dependency on DAI_SmartObject, preventing it from functioning independently. This violated the plugin architecture requirement for optional integration.

## Solution Pattern

### 1. Remove Compile-Time Dependencies

**File**: `[Plugin].Build.cs`
```csharp
// BEFORE: Hard dependency
PublicDependencyModuleNames.AddRange(new[] {
    "DAI_SmartObject" // Hard dependency - causes compile failure if missing
});

// AFTER: Optional integration
PublicDependencyModuleNames.AddRange(new[] {
    // DAI_SmartObject removed - integration now optional via runtime loading
});
```

### 2. Update Plugin Descriptor

**File**: `[Plugin].uplugin`
```json
// BEFORE: Enabled by default
{ "Name": "DAI_SmartObject", "Enabled": true, "Optional": true }

// AFTER: Disabled by default, truly optional
{ "Name": "DAI_SmartObject", "Enabled": false, "Optional": true }
```

### 3. Replace Direct Includes with Forward Declarations

**File**: Integration header files
```cpp
// BEFORE: Direct include creates hard dependency
#include "DAISmartObjectComponent.h"

// AFTER: Forward declaration only
class UDAISmartObjectComponent; // Forward declare without including
```

### 4. Implement Runtime Plugin Detection

**File**: Integration implementation files
```cpp
// Add runtime plugin availability checking
static bool IsTargetPluginLoaded()
{
    static bool bChecked = false;
    static bool bIsLoaded = false;
    
    if (!bChecked)
    {
        bChecked = true;
        bIsLoaded = FModuleManager::Get().IsModuleLoaded("TargetPluginModule");
    }
    
    return bIsLoaded;
}

// Add reflection-based class access
static UClass* GetTargetComponentClass()
{
    if (!IsTargetPluginLoaded())
        return nullptr;
    
    static UClass* TargetClass = nullptr;
    if (!TargetClass)
    {
        TargetClass = FindObject<UClass>(nullptr, TEXT("/Script/TargetPlugin.TargetComponent"));
    }
    
    return TargetClass;
}
```

### 5. Implement Graceful Function Degradation

```cpp
bool IntegrationFunction(/* parameters */)
{
    // Early exit if target plugin not available
    if (!IsTargetPluginAvailable())
    {
        UE_LOG(LogTemp, Warning, TEXT("Target plugin not available"));
        return false;
    }
    
    // Use reflection to access functionality
    UClass* TargetClass = GetTargetComponentClass();
    if (!TargetClass)
        return false;
    
    // Implementation using reflection instead of direct calls
    // ...
}
```

### 6. Add Plugin Availability Check Function

```cpp
// In header file
UFUNCTION(BlueprintPure, Category = "Integration")
static bool IsTargetPluginAvailable();

// In implementation
bool MyLibrary::IsTargetPluginAvailable()
{
    return IsTargetPluginLoaded() && GetTargetComponentClass() != nullptr;
}
```

## Benefits of This Pattern

1. **True Independence**: Plugin functions without any other DAI plugins
2. **Optional Integration**: Integration works when target plugins are available
3. **Graceful Degradation**: Functions fail safely with clear error messages
4. **Runtime Flexibility**: Users can enable/disable integration plugins as needed
5. **Blueprint Friendly**: Provides runtime checks for conditional Blueprint logic

## Verification Checklist

- [ ] Build.cs has no hard dependencies on other DAI plugins
- [ ] .uplugin has optional plugins disabled by default
- [ ] No direct #include statements for optional plugin headers
- [ ] Integration functions check plugin availability before use
- [ ] Plugin availability check function provided for Blueprints
- [ ] Documentation updated to reflect standalone nature
- [ ] All functions gracefully handle missing optional plugins

## Example Usage in Blueprints

```cpp
// Check availability before using integration features
if (IsTargetPluginAvailable())
{
    // Use integration functions
    UseIntegrationFeature();
}
else
{
    // Use fallback behavior or inform user
    ShowMessage("Target plugin not available");
}
```

This pattern ensures plugins remain modular and independent while still providing rich integration when possible.