# DAI Faction — Quick Start

- Add `Faction Component Multi Tag` to your character.
- Configure a `Faction Catalog` data asset (factions + relationships) and assign it at runtime via `SetFactionCatalog` (Blueprint library) or on BeginPlay.
- Common operations:
  - Check hostility: `DAI.Faction.AreHostile <ActorA> <ActorB>`
  - Adjust reputation: `DAI.Faction.AdjustRep <ActorName> <FactionTag> <Delta>`
  - From BP: use `FactionLibrary` nodes (AdjustRep, AreHostile, GetRelationBetweenActors, GetReputation, GetActorFactionTags, ActorBelongsToFaction).
- Listen to events on `FactionServiceSubsystem`: `OnReputationChanged`, `OnRelationshipChanged`, `OnFactionMembershipChanged`.

See `DAI_Faction.md` for details.

---

Last updated: October 6, 2025
