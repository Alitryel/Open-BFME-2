# dx8webbrowser declaration prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2. Runner allocation authorizes
Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp. No merge applied.

The Is_Browser_Open donor defines DX8WebBrowser inline without the existing
CreateBrowser and static hWnd declarations. The composer retains this class
view for its body, leaving the seed body unable to name its members (C2039
CreateBrowser, C2065 hWnd). Add the seed's exact static declarations and
HWND__/IDispatch forward declarations to this donor. No field, layout,
virtual slot, method body, name, global, include, flag or hatch changes.

## Evidence and acceptance

Reviewed the fresh planner under Code/Libraries/Source/WWVegas/WW3D2/.
Its source packet preserves same-name ZH hints and the stale TU-map warning;
these are not target proof. The current in-memory TU map approves the three
whole donors; mixed wrappers/Initialize/Common sources remain separate.
The original-path inventory and alternatives were reviewed without upgrading
same-name or path evidence to BFME 2 identity.

Commands:

    python3 tools/tu_skeleton.py --plan Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp
    python3 tools/tu_skeleton.py --merge Code/Libraries/Source/WWVegas/WW3D2/dx8webbrowser.cpp --dry-run

Before: CreateBrowser only, 6 verified rows. After: CreateBrowser plus
DX8WebBrowser_Is_Browser_Open.cpp, 9 verified rows. The added compatible
rows are Is_Browser_Open 0x00177710 (135B), its unwind 0x00767F70 (8B),
and handler 0x00767F78 (10B): 153 existing bytes, no recovered bytes.
Receipts: build/sol-b5-browser-fresh-before-trial.log and
build/sol-b5-browser-final-trial.log. Leave these donors for Luna; this is a
demonstrated prerequisite unblock, not a confirmed downstream merge.

## Verification and provider/consumer evidence

Before and after ./build.sh on CreateBrowser, Is_Browser_Open and
GameNetwork/WOLBrowser/Rva001776a0Cluster.cpp: 10/10 exact; zero
string/float/import failures. find_declared_unmatched.py: all definitions
matched. eh_verify.py: EXACT 3, no missing objects or EH debt. class_gate.py
passes. allowed_symbols.py: zero wrong bindings.

build/sol-b5-browser-proof.py compares these objects using allowed_symbols
load/scan, _object_defs, Obj, link_census._comdat_selections and
data_check.object_facts. All 16 external code definitions, code
hashes/extents, COMDAT selection/section flags, undefined symbols, data facts
and 23 relocation bindings are unchanged. Local label numbering is normalized
only after the parent EH verifier places the same funclets exactly. No
changed shared provider or consumer binding needs a replacement witness.
This proves the authored prerequisite; a later merge still needs its own
composition and batch link audit.

data_check.py: 3 findings, all in the existing baseline; no new findings.
--converged: 10 addresses, no second names or unjudged rows. Data, header,
MS-header and code-identity debt remain accounted for at existing owners.
No protected register is edited or debt retired. The future merge proposes
carrying two data keys and existing hatch counts; it must preserve these.

## Remaining prerequisites and publication audit

Rva001776a0Cluster remains rejected. Adding its existing one-string invoke
declaration to the seed removes the initial arity diagnostic but reaches
C2664 when the competing BfmeObjECFPtr views select Rva00958E30 instead of
Rva00958D30 (BfmeBstrVGP versus _bstr_t). That trial was fully reverted;
no changes to the seed, wrapper lifetime behavior or global aliases remain.
Do not guess a union or interpret equal argument bytes as identity proof.
Initialize is held by another worker; mixed Common donors are cross-family.

At audit the outgoing merge-base diff is empty, and the staged batch
changes one source plus this handoff. The two-dot origin/master..HEAD diff
also shows incoming GameFont/Common changes fetched by claims; these are
not authored changes in this batch. No pending source paths move, disappear, or alter
include/build inputs; no path consumer needs repointing in active tools,
hooks, workflows, includes, build configurations or registries. Historical
EA paths and the committed TU map are untouched. File reduction, identity
debt retirement and recovered C++ bytes are each zero.

Inherited five commits are confirmed on origin/master (rebased SHAs
 a749e7ba91, 37a9787e12, 240f0974b1, bfce63ba4c, 1b0163d262); their 14 file
claims were released. Current browser scope claims remain until publication.

BFME 1 freshness was checked again against official upstream: clean pinned
ff391a5e versus cbc06db8. Keep verified inputs: full before/after reference
update verification is not completed, and no success receipt was written.
No maintainer-only measurement, link cycle or smoke runner was started.
