W3D table consumer bindings, 2026-10-18

Three wrappers used undefined array symbols whose types included their private
virtual-call views. Bind the filter wrappers to W3DFilters, whose matched data
row owns VA DE1F2C (ten slots), and the shader notification to W3DShaders,
whose two-slot storage is defined in W3DShaderManager.cpp at VA DE1F24.
The manager init and shutdown establish these table entries; the already
repaired Rva00075725Check.cpp uses the same filter-table binding. Cast only at
the view use and preserve the volatile reload before each virtual call.

Current legacy link predictor across the same five units: 1322 -> 1466 B,
+144 B, with all three modified wrappers newly linking. SetShader and the
manager already linked and are included only as providers/comparison.
The source byte gate passes 3/3 rows. Self-strict provider preparation passes
14/14 rows and four data rows across the wrappers and shader manager. No
closed-strict or full link-cycle gain is claimed. No new authored bytes.
