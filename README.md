# DAI Performance Manager Example Project

This repository contains the **DAI Performance Manager Example Project** for Unreal Engine 5.5. It showcases the **DAI_PerfMngr** plugin in a concrete project, alongside the broader DAI (Dynamic AI) plugin ecosystem.

- Engine: **Unreal Engine 5.5**
- Primary focus: **Runtime performance management, significance-based scaling, and budget-driven systems**
- Key plugin: **DAI_PerfMngr** (Performance Manager)

## Repository Layout

- `Performance/` – Unreal example project using the DAI plugins
  - `Plugins/DAI_PerfMngr/` – Performance Manager plugin (source, resources, in-plugin docs)
- `docs/` – Central documentation index and cross-plugin docs
  - `plugins/` – Per-plugin documentation (including `DAI_PerfMngr.md`)

## DAI_PerfMngr Overview

`DAI_PerfMngr` is a world-level performance coordination plugin that builds on Unreal's Significance Manager and timing/budget primitives. It provides:

- **Performance budgeting** – per-category ms budgets (Rendering, AI, Physics, etc.)
- **Significance-based scaling** – distance/importance aware actor significance
- **Adaptive LOD hooks** – helpers for LOD decisions based on performance/
- **Budget-aware operations** – Blueprint/C++ helpers to gate expensive work
- **Integration hooks** – intended to coordinate with other DAI plugins (UltraSky, Spawner, AI, Dismember, etc.)

For a full conceptual overview of the plugin:
- See `docs/plugins/DAI_PerfMngr.md`

For in-plugin documentation (shipped with the plugin itself):
- See `Performance/Plugins/DAI_PerfMngr/Docs/`
  - `DAI_PerfMngr_Guide.md` – high-level usage guide
  - `DAI_PerfMngr_API.md` – focused API reference
  - `DAI_PerfMngr_PerformanceProfiles.md` – tuning and budget profiles

## Getting Started

1. **Clone the repo**
   ```powershell
   git clone https://github.com/<owner>/performanceMng.git
   cd performanceMng
   ```

2. **Open the project**
   - Open `Performance/Performance.uproject` in Unreal Engine 5.5.
   - Let Unreal compile modules when prompted.

3. **Enable plugins (if needed)**
   - In Unreal, go to **Edit → Plugins**.
   - Ensure **DAI_PerfMngr** and any required DAI plugins are enabled.

4. **Explore examples**
   - Look for sample levels and Blueprints demonstrating performance budgeting, significance-based scaling, and adaptive LOD usage.

## Documentation

Central documentation entry point:
- `docs/README.md` – DAI system overview and plugin index.

Notable related docs:
- `docs/plugins/DAI_PerfMngr.md` – high-level PerfMngr design and feature set.
- `docs/Optimization_Notes.md` – UltraSky optimization and general performance patterns.
- `docs/Console_Command_Index.md` – runtime console command index across plugins.

## Contributing

- Follow standard Unreal C++ style and the existing DAI plugin patterns.
- Keep public APIs and docs in sync (update both `docs/plugins` and in-plugin `Docs/` where relevant).
- Prefer performance-oriented implementations and budget-aware patterns when adding new systems.

## License & Ownership

- This repository is an **example Unreal Engine 5 project** intended to demonstrate how to integrate and drive the DAI Performance Manager plugin in a real game project.
- The **DAI_PerfMngr plugin itself is a separate, owned plugin**. You must legally own/access that plugin (e.g., from its distribution channel or private license) to use it beyond this example.
- The plugin source is currently present in this project only to allow **automatic documentation generation and validation** and may be removed from the repository shortly after docs are finalized. Future clones of this repo may ship **without the plugin source**, expecting you to drop in your licensed copy under `Performance/Plugins/`.

This project is built on **Unreal Engine 5.5** and is subject to the standard **Unreal Engine End User License Agreement (EULA)**. Use of Unreal Engine binaries, headers, and associated content must comply with the official Epic Games license terms:

- See the official Unreal Engine EULA at: https://www.unrealengine.com/eula

Any additional licensing terms for the DAI_PerfMngr plugin or related DAI plugins are governed by their own agreements and are **separate from** the Unreal Engine EULA.

---
_Last updated: November 30, 2025_  
_Compatible with: Unreal Engine 5.5_