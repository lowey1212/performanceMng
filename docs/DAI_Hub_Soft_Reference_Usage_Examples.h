#pragma once

/**
 * USAGE EXAMPLES FOR DAI_HUB SOFT REFERENCES
 * ==========================================
 *
 * This file demonstrates how to use the UDAIHubSoftReference utility class
 * to safely interface with DAI_Hub from other plugins without creating hard dependencies.
 *
 * Key Benefits:
 * - Other plugins can compile and run even if DAI_Hub is not present
 * - No hard linking or module dependencies required
 * - Graceful fallback when hub functionality is unavailable
 * - Uses UE5 recommended soft reference patterns
 */

// Example 1: Basic Hub Availability Check
// =======================================
void ExampleCheckHubAvailability(const UObject *WorldContext)
{
    // Safe to call even if DAI_Hub plugin is not loaded
    if (UDAIHubSoftReference::IsHubAvailableSoftRef(WorldContext))
    {
        UE_LOG(LogTemp, Log, TEXT("DAI_Hub is available and ready for use"));
    }
    else
    {
        UE_LOG(LogTemp, Log, TEXT("DAI_Hub is not available - operating in standalone mode"));
    }
}

// Example 2: Service Registration Pattern
// =======================================
class MYDAIPLUGIN_API AMyServiceActor : public AActor
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override
    {
        Super::BeginPlay();

        // Try to register with hub if available
        RegisterWithHub();
    }

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override
    {
        // Always clean up registration
        UnregisterFromHub();

        Super::EndPlay(EndPlayReason);
    }

private:
    void RegisterWithHub()
    {
        // This call is completely safe even if DAI_Hub is not present
        if (UDAIHubSoftReference::RegisterWithHubSoftRef(this, this))
        {
            UE_LOG(LogTemp, Log, TEXT("Successfully registered %s with DAI_Hub"), *GetName());
            bRegisteredWithHub = true;
        }
        else
        {
            UE_LOG(LogTemp, Log, TEXT("DAI_Hub not available - %s running in standalone mode"), *GetName());
            bRegisteredWithHub = false;
        }
    }

    void UnregisterFromHub()
    {
        if (bRegisteredWithHub)
        {
            UDAIHubSoftReference::UnregisterFromHubSoftRef(this, this);
            bRegisteredWithHub = false;
        }
    }

    bool bRegisteredWithHub = false;
};

// Example 3: Interface Discovery Pattern
// =======================================
void ExampleFindInterfaceImplementers(const UObject *WorldContext)
{
    // Find all smart object providers in the world
    TArray<UObject *> SmartObjects = UDAIHubSoftReference::FindImplementersOfInterfaceSoftRef(
        WorldContext,
        TEXT("DAI_SmartObjectProvider"));

    for (UObject *SmartObject : SmartObjects)
    {
        UE_LOG(LogTemp, Log, TEXT("Found smart object: %s"), *SmartObject->GetName());

        // You can then cast and use the interface safely:
        // if (IDAI_SmartObjectProvider* Provider = Cast<IDAI_SmartObjectProvider>(SmartObject))
        // {
        //     Provider->DoSomething();
        // }
    }

    // Example: Find all navigation consumers (replace with an interface present in your project)
    TArray<UObject *> NavConsumers = UDAIHubSoftReference::FindImplementersOfInterfaceSoftRef(
        WorldContext,
        TEXT("DAI_NavigationConsumer"));

    UE_LOG(LogTemp, Log, TEXT("Found %d navigation consumers in the world"), NavConsumers.Num());
}

// Example 4: Blueprint Usage Pattern
// ==================================
UCLASS(BlueprintType)
class MYDAIPLUGIN_API UMyBlueprintComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "DAI Plugin Example")
    bool TryConnectToHub()
    {
        // This function can be called from Blueprint and will safely handle
        // hub availability without causing crashes or compilation errors
        return UDAIHubSoftReference::IsHubAvailableSoftRef(GetOwner());
    }

    UFUNCTION(BlueprintCallable, Category = "DAI Plugin Example")
    void RegisterMyServiceWithHub()
    {
        if (UDAIHubSoftReference::RegisterWithHubSoftRef(GetOwner(), GetOwner()))
        {
            // Hub registration successful
            OnHubRegistrationSuccess();
        }
        else
        {
            // Hub not available or registration failed
            OnHubRegistrationFailed();
        }
    }

    UFUNCTION(BlueprintImplementableEvent, Category = "DAI Plugin Example")
    void OnHubRegistrationSuccess();

    UFUNCTION(BlueprintImplementableEvent, Category = "DAI Plugin Example")
    void OnHubRegistrationFailed();
};

// Example 5: Module Initialization Pattern
// =======================================
class FMyDAIPluginModule : public IModuleInterface
{
public:
    virtual void StartupModule() override
    {
        // Module can start up completely independently of DAI_Hub
        UE_LOG(LogTemp, Log, TEXT("MyDAIPlugin starting up..."));

        // Optional: Check if hub is available during startup
        // Note: Hub might not be loaded yet during module startup
        // Better to check during gameplay when needed
    }

    virtual void ShutdownModule() override
    {
        // Clean shutdown regardless of hub availability
        UE_LOG(LogTemp, Log, TEXT("MyDAIPlugin shutting down..."));
    }
};

// Example 6: Build.cs Configuration
// =================================
/*
In your plugin's Build.cs file, you do NOT need to add DAI_Hub as a dependency:

public class MyDAIPlugin : ModuleRules
{
    public MyDAIPlugin(ReadOnlyTargetRules Target) : base(Target)
    {
        PublicDependencyModuleNames.AddRange(new string[] {
            "Core",
            "CoreUObject",
            "Engine"
            // Do NOT add "DAI_Hub" here - that would create hard dependency
        });

        // If you want to include the soft reference utility, you can add it optionally:
        if (Target.bBuildEditor)
        {
            // Only add this if DAI_Hub is known to be available in the project
            // Or use dynamic loading patterns instead
        }
    }
}
*/

// Example 7: Error Handling and Fallbacks
// =======================================
class MYDAIPLUGIN_API UMySystemManager : public UObject
{
public:
    void InitializeSystem(const UObject *WorldContext)
    {
        // Always try hub integration first
        if (UDAIHubSoftReference::IsHubAvailableSoftRef(WorldContext))
        {
            InitializeWithHub(WorldContext);
        }
        else
        {
            InitializeStandalone();
        }
    }

private:
    void InitializeWithHub(const UObject *WorldContext)
    {
        UE_LOG(LogTemp, Log, TEXT("Initializing with DAI_Hub integration"));

        // Register services, find interfaces, etc.
        UDAIHubSoftReference::RegisterWithHubSoftRef(WorldContext, this);

        // Find other hub services to interact with
        auto SmartObjects = UDAIHubSoftReference::FindImplementersOfInterfaceSoftRef(
            WorldContext, TEXT("DAI_SmartObjectProvider"));

        // Set up hub-aware behavior
        bUsingHubIntegration = true;
    }

    void InitializeStandalone()
    {
        UE_LOG(LogTemp, Log, TEXT("Initializing in standalone mode"));

        // Set up self-contained behavior without hub dependencies
        // This ensures the plugin works even without DAI_Hub
        bUsingHubIntegration = false;
    }

    bool bUsingHubIntegration = false;
};

/**
 * BEST PRACTICES SUMMARY:
 * =======================
 *
 * 1. Always check hub availability before attempting to use it
 * 2. Design your plugin to work standalone without DAI_Hub
 * 3. Use soft reference utility functions instead of direct hub calls
 * 4. Handle graceful fallbacks when hub is unavailable
 * 5. Don't add DAI_Hub as a hard dependency in Build.cs files
 * 6. Test your plugin with and without DAI_Hub present
 * 7. Use hub integration as an enhancement, not a requirement
 *
 * INTEGRATION TESTING:
 * ===================
 *
 * To test soft reference behavior:
 * 1. Build project with all plugins including DAI_Hub
 * 2. Test that your plugin registers and works with hub
 * 3. Disable DAI_Hub plugin in .uproject file
 * 4. Rebuild and test that your plugin still works standalone
 * 5. Re-enable DAI_Hub and verify integration works again
 */