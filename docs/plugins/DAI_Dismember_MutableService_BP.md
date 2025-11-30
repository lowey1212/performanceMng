# DAI Dismember: Blueprint Mutable Combiner Service (State Node)

This guide shows how to build a pure-Blueprint implementation of the `DAI_MutableCombinerService` interface using a Mutable State Node approach. Designers can switch to a specific state (e.g., `SingleMaterial`) and notify completion back to the Perf Bridge. The service must be available at runtime (not Editor-only) if you want this in packaged builds.

## Prerequisites
- Your character/asset uses a Mutable graph with a State node that outputs a combined single mesh/material. Note the state name (default suggested: `SingleMaterial`).
- The owning actor has a `DAI_PerfBridgeComponent` attached.
- In Project Settings → DAI Dismember, set:
  - Enable Mutable Updates = true
  - Mutable Combine State Name = your state (e.g., `SingleMaterial`)
  - Mutable Combiner Service Class = your BP service from this guide

## Blueprint: Create the Service
1. Create a new Blueprint (Blueprint Class → All Classes → pick `ActorComponent` or `Object`). Name it `BP_DAI_MutableCombinerService`.
2. In Class Settings → Interfaces, add `DAI_MutableCombinerService`.
3. Implement event `Combine Actor To Single Mesh` (from the interface):
   - Inputs: Actor, SingleMaterialOverride, Priority
   - Return: boolean (Success)

### Example Flow
- Validate Actor is valid. Get the `DAI_PerfBridgeComponent` from Actor.
- Get the desired state name from settings:
  - Call `Get Default DAI_DismemberDeveloperSettings` then `MutableCombineStateName`.
- Find your Mutable component/CO instance on the Actor (project-specific). Common patterns:
  - If using a CO instance component, get it and call a function like `Set State (by Name)`.
  - Optionally push a parameter for `SingleMaterialOverride` if your Mutable graph supports it.
- Trigger the update (async). When the update finishes, call `Notify Mutable Combine Complete` on the Perf Bridge component to signal success.
- Return true immediately if the request was accepted. If you detect a hard failure, return false.

### Minimal Node Outline
- Branch: `Actor Is Valid` → True
- `Get Component by Class (DAI_PerfBridgeComponent)` → Perf
- `Get Default DAI_DismemberDeveloperSettings` → Settings → `MutableCombineStateName`
- Get your Mutable instance (e.g., `Get Component by Class (YourMutableComponent)`)
- Set State By Name (Settings.MutableCombineStateName)
- If supported, set material override parameter on the instance
- Start Update (async)
- Bind On Update Completed → call `Notify Mutable Combine Complete(Perf, true)`
- Return true (from the interface function)

Notes:
- Ensure the Blueprint asset resides in a runtime-loaded module or game content (not Editor-only) for packaged builds.
- If the update fails or times out, call `Notify Mutable Combine Complete(false)`; the Perf Bridge also has a watchdog and will fail-safe if not notified.

## Using It
- In-game, call one of:
  - Perf Bridge → `Schedule Mutable Combine`
  - Perf Bridge → `Mark Equipment Changed`
  - Console: `DAI.Dismember.CombineToSingleMaterial <ActorName> [MaterialPath] [Priority]`
- Bind to `OnMutableCombineCompleted` to know when it’s done.

## Troubleshooting
- If your service isn’t invoked, verify Project Settings → DAI Dismember → `MutableCombinerServiceClass` points to your BP.
- Ensure `Enable Mutable Updates` is checked.
- Watch the log category `LogDAIDismember` for messages.
- Adjust runtime CVars:
  - `dai.Dismember.MutableCombineCooldown`
  - `dai.Dismember.MutableCombineWatchdog`

---

Last updated: October 6, 2025
