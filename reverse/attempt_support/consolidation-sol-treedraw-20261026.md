# W3DTreeDraw declaration prerequisite, 2026-10-26

Seat codexb, allocated family B shard 0. Runner consolidation queue authorized
this unheld destination. Current tu_skeleton --plan rebuilds the stale map in
memory: nine approved rows; two mixed donors and two protected donors remain.
No move, ledger repoint or committed TU-map regeneration is made here.

The original seed has no W3DTreeDraw::getModuleNameKey declaration. Ordinary
merge dry-run rejects its real name-key donor with C2039, while the module-data
destructor donor loses bytes. Adding the donor's virtual method alone is wrong:
the seed's empty non-polymorphic DrawModule base is moved to +4 and the constructor
grows from 28 to 31 bytes. The existing matched DrawModule constructor and
destructor declarations establish a polymorphic base, including its protected
virtual destructor (ledger destructor 0x000CEB6F, existing BoatWake fold proof).
Declare that destructor in the seed's local view and add the existing method
and enum declarations. Do not add fields, implement new bodies or invent names.

Standalone ./build.sh on the seed and name-key donor verifies 4/4 rows; both
frozen-file checks and class_gate pass. EH verifies its one table EXACT. Scoped
code_identity_gate checks four rows before and after, with no problems or notes
in shadow. No identity key is retired. data_check reports the unchanged static
name-key local as wrong-name; the donor's complete object is byte-for-byte
identical to its saved baseline. No data debt is claimed fixed.

The baseline and repaired seed have identical contents/flags in every object
section. For both sources, every external code/data body, size, relocation
referent, section flag, COMDAT selection and external reference is identical.
No vtable or destructor provider is newly emitted. Saved baseline objects and
the supported Obj-based comparison are under build/sol-tree-draw-before-*.obj
and build/sol-tree-draw-bindings.py.

The repaired ordinary --merge --dry-run accepts the seed and name-key donor,
four rows across two sources; the baseline accepted no merge. Two donor rows
are newly compatible. The module-data destructor donor remains rejected for
bytes, and the two mixed Common donors and two protected donors remain outside
this repair. Leave the compatible merge for Luna: no downstream landing is
confirmed here. This repair removes no files, recovers no C++ bytes and retires
no code-identity or data debt.

Final composed object build/tu_skeleton/8b486965652a15d7.obj preserves the complete
union of both baseline objects' external code/data definitions, raw bytes,
sizes, relocation referents, section flags, COMDAT selections and external
references. No provider is missing, added or changed; no consumer reference is
added or removed. python3 build/sol-tree-draw-bindings.py
build/sol-tree-draw-after.txt reproduces the supported Obj-based comparison.
The supported eh_verify.verify_row API also verifies the composed name-key
function's full EH graph EXACT (build/sol-tree-draw-trial-eh.txt), including
its renumbered cleanup labels and table references.
This establishes this trial's provider and binding stability, not a full-link
result. link_check --new-variants --staged-peers --shadow returns zero with no
new variants. Microsoft-header scan: two files, zero local Microsoft names,
zero failed scans. Neither source has an existing header/MS-header queue key.

Receipts: build/sol-tree-draw-{before,after,before-build,after-build,
identity-before,identity-after,link,headers,bindings}.txt. ./build.sh,
find_declared_unmatched.py, class_gate.py, eh_verify.py and data_check.py were
run on W3DTreeDraw.cpp and W3DTreeDrawModuleNameKey.cpp in the destination's
Draw/ directory. Planner: build/consolidation/sol-draw-20261026, refreshed
after temporary compiler trials; original-path evidence and alternatives do
not approve a merge. Current --plan is the move authority; the TU map is not
regenerated on disk.

Publication audit covers the inherited results-attempt evidence commit plus
this source edit and handoff. git diff --name-status --find-renames
origin/master..HEAD also displays incoming family-A commits fetched by the
claim tools; origin/master...HEAD isolates the actual pending commits. There
are no source path moves, deletions, absorbed donors, new headers or include
changes in this outgoing batch. Active tools, hooks, workflows, includes,
build inputs and registries need no repointing. Historical EA paths and all
protected registers remain intact. Pending publication retains the seed,
name-key donor and this handoff's file scopes, plus the inherited results
handoff's scope. Release those scopes after confirmed publication.
