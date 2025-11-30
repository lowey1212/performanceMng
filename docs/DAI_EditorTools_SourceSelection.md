# DAI Editor Tools — Source Selection (EUW)

This editor-only tool streamlines building DataTables from DataAssets and optionally creates Mutable Customizable Objects (CO) per asset from a template. It also auto-detects textures from meshes/materials and populates matching texture columns in your DataTable.

## Overview

Key features:
- Discover and filter DataAssets by class and path (include/exclude).
- Choose DataTable-safe properties to export and preview the result.
- Export to CSV or a target DataTable (rebuild or update modes).
- Create a new DataTable directly from the tool (path, name, RowStruct).
- Create CO assets from a template using the pattern `CO_<AssetName>`.
- CO conflict policy (Skip/UniqueName) to handle naming collisions.
- Auto texture extraction and mapping into RowStruct texture columns.
- Optional Texture Mapping with token-based control and validation.
- Presets to save and restore configuration.

## Getting started

1. Open the Source Selection tool in the editor.
2. Pick a DataAsset class to scan.
3. Select Include/Exclude paths to scope the search.
4. Choose properties to export.
5. Pick a target DataTable, or create a new one.
6. Click Build Preview to see rows, values, and validation notes.
7. Export CSV or Export To DataTable.

If using Mutable CO creation, configure the CO section and click either:
- Create COs From Template
- Create COs + Export DataTable

## UI guide

### UI Density
Choose Compact, Cozy, or Comfortable to adjust control and list heights.

### Class/Include/Exclude pickers
- Class: The DataAsset class to scan.
- Include paths: Only assets under these paths are considered.
- Exclude paths: Assets under these paths are filtered out.

### Properties and Summary
- Properties list includes DataTable-friendly fields.
- Summary shows counts and basic hints based on your selection.

### DataTable picker
- Pick an existing DataTable to write to.
- Export Mode:
  - Rebuild: Clears the DataTable and writes all rows.
  - Update: Only adds/updates rows; controlled by Conflict Policy.
- Conflict Policy (DataTable):
  - Overwrite: Replace existing rows.
  - Skip: Keep existing rows; do not overwrite.

### Create New DataTable
- Path: Package path for the new asset (e.g. `/Game/DAI/Generated/DataTables`).
- Name: Asset name (e.g. `DT_FromSelection`).
- RowStruct (name): Optional string, but prefer picking a RowStruct via the asset picker.
- RowStruct picker: Choose the row struct the DataTable should use.

### Row Key
Controls how the row name (key) is computed:
- AssetName: Uses the asset’s name.
- AssetPath: Uses the asset’s path.
- Property: Uses the string value of the selected property.

### Assets list
- Shows matched DataAssets.
- You can multi-select to scope CO creation to a subset (export still uses all preview rows).

### Customizable Object (Mutable)
- CO Output Path: Where to place created CO assets (e.g. `/Game/DAI/Generated/CO`).
- Template CO: Pick a template Customizable Object (duplicated per selected/all assets).
- CO Conflict Policy:
  - Skip: Do not create if a conflicting asset exists.
  - UniqueName: Append a numeric suffix to avoid conflicts.
- Actions:
  - Create COs From Template
  - Create COs + Export DataTable

### Texture Mapping (optional)
This helps the tool auto-populate texture columns in your DataTable row struct.

- Prefer parameter mapping: Prioritize mapping by material instance texture parameter names.
- Mapping lines: One per row-struct column.
  - Syntax: `Column=keyword1|keyword2|keyword3`
  - Column must match a texture property name on the RowStruct (UTexture or UTexture2D; hard or soft object).
  - Tokens are matched case-insensitively against:
    1) Material instance texture parameter names (if Prefer parameter mapping is enabled).
    2) Texture asset names.
    3) Fallback heuristic using the column name.

Examples:
```
BaseColor=base|albedo|diffuse
Normal=normal|nrm
ORM=occlusion|rough|metal
Emissive=emi|glow
```

- Validate Mapping button: Computes coverage across preview rows and shows a summary like `Mapping coverage: 12/20 rows fully mapped; 8 missing cells.`
- Per-row status: The Status column includes `[<Column> unmapped]` if there are tokens for a column but no match was found for that row.

### Preview and export
- Build Preview: Scans assets, collects selected properties, extracts textures, and applies mapping.
- Export CSV: Writes the union of selected properties and detected texture columns.
- Export To DataTable: Writes rows to the target DataTable according to mode and conflict policy.

## Presets
- Save Preset / Load Preset stores most settings to Saved/DAI_EditorTools/Presets.
- Preserved fields include:
  - Selected class, include/exclude paths, selected properties
  - Target DataTable and RowStruct
  - Export mode, conflict policy, row key mode/property
  - New DataTable path/name/RowStruct name
  - CO output path, template CO, CO conflict policy
  - TextureMappingCSV and Prefer parameter mapping

## Tips and best practices
- RowStruct setup: Ensure texture columns are UTexture or UTexture2D (hard or soft object) for auto-population.
- Parameter names: Prefer material instances with explicit texture parameters for best mapping results.
- Large batches: Consider narrowing include paths to limit scanning and speed up preview.
- DataTable update: Set Update + Skip to avoid clobbering existing rows; use Rebuild to regenerate entirely.
- CO naming: COs are named `CO_<AssetName>` and placed under the configured output path.

## Troubleshooting
- Build/link errors while the editor is open: close Unreal Editor before compiling the plugin to avoid DLL lock issues.
- Empty texture fields:
  - Check that your RowStruct column names match the mapping Column keys exactly.
  - Verify materials are material instances with TextureParameterValues if relying on parameter mapping.
  - Add more tokens that match your team’s naming conventions.
- DataTable errors: Ensure the target DataTable’s RowStruct matches the intended struct with the property names you export.
- No assets listed: Verify class selection and include/exclude paths. Try rebuilding the preview.

## FAQ
- Do I need mapping for textures?
  - No. The tool falls back to best-effort name heuristics by column name and texture asset names.
- Can I use only a subset of assets for CO creation?
  - Yes. Select rows in the Assets list to scope CO creation; preview/export still uses the full set unless you also filter paths or class.
- Where are presets saved?
  - Under `Saved/DAI_EditorTools/Presets` with the selected class embedded in the filename.

## Version
- Engine: UE 5.5
- Module: DAI_EditorTools
- Date: 2025-10-08
