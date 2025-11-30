# Blueprint Comments Template

Purpose: Standardize clear, consistent, beginner-friendly comments directly inside Blueprints (Comment nodes, Descriptions, Tooltips) across all DAI plugins.

Last Updated: November 4, 2025

---

## Audience & Goals

- Audience: Designers and developers with 0–6 months of Unreal Blueprint experience
- Goals:
  - Make nodes self-explanatory at a glance
  - Show what to do, when to use it, and expected ranges/units
  - Keep style consistent with:
    - docs/templates/Tooltip_Reference_Guide.md
    - docs/templates/Beginner_Friendly_Code_Comments_Template.md

---

## Core Principles

1) Lead with what it does
- Good: "Finds nearest valid target within Radius and line-of-sight."
- Bad: "Runs a loop over actors and traces..." (implementation first)

2) Be concise but complete
- Prefer 1–3 short lines. Add a second block for extra notes if needed.

3) Include units, ranges, and defaults
- Seconds, frames, cm (world units), percent 0–1.

4) State when-to-use for switches/flags
- "Enable to prevent AI from picking unreachable targets."

5) Consistent vocabulary
- Actor, Component, World units, Seconds, Hit points, Replicated, Authority/Client.

6) Avoid repeating the name
- Not helpful: "Radius variable." Prefer: "Maximum distance checked (world units)."

7) Call out networking/perf side-effects
- Use tags like [Authority], [Client], [Replicated], [Expensive], [Async].

---

## Formatting Conventions for Comment Nodes

- Title line: imperative, present tense
- Optional tags in square brackets at start
- Use bullet points for inputs/outputs when documenting a composite or function
- Keep line width readable (~90 chars)

Example skeleton:

[Authority] Apply Damage Over Time
- Ticks every 0.5s for Duration (seconds)
- Scales by Vulnerability (0–2), clamped
- Cancels if Source or Target becomes invalid

---

## Standard Tags

- [Authority] Runs only on the server
- [Client] Client-side effect (visual/audio only)
- [Replicated] Value replicated to clients
- [Async] Latent or asynchronous step (timeline, delay, async load)
- [Expensive] Heavy loop, trace, or allocation; avoid in tick
- [EditorOnly] Only used in editor (not runtime)
- [Experimental] Subject to change; do not rely on behavior
- [Deprecated] Use <New Name> instead

---

## Reusable Templates (Copy/Paste)

### A) Function/Macro Comment (Multi-line)

Use this on a Comment node that covers the whole function graph or macro body.

Find Nearest Valid Target
- Purpose: Returns closest Actor that matches Filter and is reachable
- Inputs:
  - Origin: Actor or Location
  - Radius: float (world units)
  - Team: GameplayTag (optional)
  - Require LOS: bool (true = do a visibility trace)
- Outputs:
  - Target: Actor (null if none found)
  - Distance: float (world units)
- Notes:
  - [Authority] For gameplay decisions; cosmetic-only on clients
  - [Expensive] Avoid large Radius in tick; prefer cached results

### B) Function/Macro Comment (Compact)

Find Nearest Target (reachable, LOS optional)
- In: Origin, Radius(cm), Team?, Require LOS
- Out: Target, Distance(cm)
- [Authority] Avoid calling per-frame with Radius > 5000

### C) Event Graph Banner

Player Character – Event Graph
- Input: Player input mapping (Move, Look, Jump, Interact)
- Systems: Movement, Camera, Interaction, Inventory
- Networking: [Authority] handles inventory changes; cosmetic VFX on client

### D) Region Header Comment

[Init]
- Cache components and default values
- Register with subsystems

[Runtime]
- Tick-driven updates and timers

[Events]
- Input bindings and overlap events

### E) Variable Description (used in Details panel)

- What it controls + units/range + when to change it.

Examples:
- "Max distance for interaction (world units, 0–5000)."
- "Time between burst shots (seconds, 0.02–0.5)."
- "Damage multiplier for headshots (0–5, 1 = default)."

### F) Interface Message Comment

IInteractable: TryInteract
- Purpose: Attempt to interact with this object
- Inputs: Interactor (Actor)
- Returns: Success (bool)
- Notes: Implement on actors that can be used by the player or AI

### G) Timeline/Latent Step Comment

[Async] Fade In
- Drives PostProcess weight from 0 → 1 over Duration (seconds)
- Cancels if Character dies or is destroyed

### H) Macro Library Entry Description

Clamp To Play Area
- Clamps Location to NavMesh bounds with Margin (world units)
- Returns clamped Location and whether clamping occurred

---

## Pin Tooltips (Inline Help)

Where supported, set pin tooltips to match the style:
- Inputs: "Maximum search distance (world units)."
- Outputs: "True if any target matched filters and LOS."

Consistency with C++: If a Blueprint function wraps C++, mirror the UFUNCTION meta ToolTip.

---

## Naming & Categories (Quick Rules)

- Categories: Use Title Case and group by feature ("Movement", "Combat", "UI")
- Functions: VerbObject ("FindTarget", "ApplyDamage", "OpenInventory")
- Events: OnSomething ("OnDeath", "OnItemPickedUp")
- Variables: Noun with units suffix when helpful ("RadiusCm", "CooldownSec")

---

## Quality Checklist

- Each public function/macro has a top Comment node with Purpose, Inputs, Outputs
- Variables exposed to designers have clear Descriptions with units and ranges
- Async steps are tagged [Async]; server-only logic tagged [Authority]
- Expensive loops/traces marked [Expensive] with guidance
- Regions are separated with header comments: [Init], [Runtime], [Events], [Debug]
- For replicated Blueprints, note what runs where (server vs client)
- Avoid repeating names; focus on what/when/units

---

## Worked Examples

### Example 1: Ability – Dash

[Async] Dash Ability
- Purpose: Propel character forward quickly; short invulnerability window
- Inputs: Distance (cm), Duration (s), Cooldown (s)
- Outputs: Success (bool)
- Notes:
  - [Authority] Applies cooldown and stamina cost
  - [Client] Plays trail VFX/SFX only
  - [Expensive] Capsule sweeps per frame; keep Duration short

Variable descriptions:
- DashDistanceCm: "Travel distance (world units, 0–3000)."
- DashDurationSec: "Time to reach target distance (seconds, 0.05–0.5)."
- IFramesSec: "Invulnerability duration during dash (seconds)."

### Example 2: AI – Find Patrol Point

Find Patrol Point
- Purpose: Choose next point from PatrolPath; wrap-around supported
- Inputs: CurrentIndex (int), Direction (+1/-1), RandomJitter (cm)
- Outputs: NextLocation (vector), NextIndex (int)
- Notes:
  - [Authority] Chooses point; clients only draw debug
  - Adds RandomJitter to reduce crowding

---

## Copy Blocks (ready to paste)

Comment Node – Full Function

<Title>
- Purpose: <One-line purpose>
- Inputs: <List with units>
- Outputs: <List with units>
- Notes: [Authority/Client/Replicated/Async/Expensive] <optional guidance>

Comment Node – Compact Function

<Title> (<short purpose>)
- In: <inputs>
- Out: <outputs>
- [Tags] <optional guidance>

Region Header

[Init] / [Runtime] / [Events] / [Debug]
- <1–3 bullets of what lives here>

Variable Description

"<What it controls> (<units and range>). <When to adjust>."

Timeline/Latent Step

[Async] <Name>
- <What changes over time> over Duration (seconds)
- Cancel conditions: <if any>

---

## Tips

- Prefer short lines; break long sentences into bullets
- Show default values and typical ranges to reduce guesswork
- Use the same words as the editor (Seconds, World units)
- If a comment becomes long, split into two stacked Comment nodes: Summary + Details

---
 
## Linking to Epic docs (local snapshots)

Include a short "See:" line at the end of a comment when pointing readers to UE documentation. Prefer the local snapshots in this repo so links work offline.

Patterns:
- See: UE Docs – <Topic> (local)  => reference file in "epic docs/" or docs/EpicReferences.md
- Optionally include the online URL in parentheses if helpful.

Examples:
- See: UE Docs – Replication Overview (local: epic docs/documentation-en-us-unreal-engine-networking-overview-*.html)
- See: UE Docs – Timelines (local: epic docs/documentation-en-us-unreal-engine-timelines-*.html)
- See: EpicReferences.md – Lighting & Sky subsection

Notes:
- Use EpicReferences.md in docs/ as an index to common topics captured in "epic docs/".
- Keep the reference on its own bullet at the bottom of the comment block.

## References

- docs/templates/Tooltip_Reference_Guide.md
- docs/templates/Beginner_Friendly_Code_Comments_Template.md
- docs/EpicReferences.md (curated links into local UE docs)
- epic docs/ (offline UE documentation snapshots used in this project)
