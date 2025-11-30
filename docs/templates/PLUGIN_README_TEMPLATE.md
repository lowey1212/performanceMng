# {PLUGIN_NAME}

Short description: What this plugin does in 1-2 sentences.

## Overview
- Purpose and core value
- Key features (3-7 bullets)
- Module breakdown (Runtime, Editor, Tests if any)

## Setup
- Enable in `.uproject` Plugins
- Project Settings page (if applicable)
- Required engine/project settings (if any)

## Logging
- Single log category: `{LOG_CATEGORY}`
- Example:
  - `UE_LOG({LOG_CATEGORY}, Log, TEXT("..."));`

## Developer Settings
- Path: Project Settings → Game → {PLUGIN_NAME_SHORT}
- Important fields and defaults

## Blueprint APIs
- Top-level Blueprint library or components
- Important functions with 1-line summaries

## Console Commands
- `{cvar.or.command}` – short description

## Save/Load (Optional)
- Save fragment provider (if implemented)
- JSON shape example and versioning note

## Optional Integrations
- List soft/optional dependencies and how they’re detected

## Testing
- Where tests live and how to run

## Notes
- Avoid raw TODO in code; prefer "Note:" or "Future:"
- Follow per-module logging category; avoid LogTemp in shipping code

---
_Last updated: {DATE}_