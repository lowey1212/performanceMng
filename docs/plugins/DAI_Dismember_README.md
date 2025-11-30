# DAI Dismember — Quick Start

- Add `DAI Performance Bridge` component to your character.
- To sever via console: `DAI.Dismember.Sever <ActorName> <LimbID>`
- To restore all: `DAI.Dismember.RestoreAll [ActorName]`
- To combine meshes (Mutable):
  - Console: `DAI.Dismember.CombineToSingleMaterial <ActorName> [MaterialPath] [Priority]`
  - Blueprint: `CombineActorMeshesToSingleMaterial`
  - For frequent changes: `MarkEquipmentChanged` or `ScheduleMutableCombine`
- Status: `DAI.Dismember.CombineStatus <ActorName>`

Setup tips:
- Project Settings → DAI Dismember:
  - Enable Mutable Updates
  - Mutable Combine State Name (if using a State Node)
  - Mutable Combiner Service Class (BP/C++)
- See detailed docs: `DAI_Dismember.md` and `DAI_Dismember_MutableService_BP.md`.

---

Last updated: October 6, 2025
