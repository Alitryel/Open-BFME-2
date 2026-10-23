Quick-horde update link repair, 2026-10-20

Paired legacy preview against the same retail-truth-2 index 5366c4f808
(2026-10-20 12:21) changes this unit from blocked to LINKS, gaining 2,594
existing nonpadding matched bytes. No authored C++ byte growth. The complete
2,598-byte retail body at 0x0026C4EB remains exact.

The private identity Matrix3D constructor keeps its inline semantics while
an imported-forceinline definition suppresses its nonretail external COMDAT.
The two calls to Object::rva0028B525 now name the rowed displacement-view
setter Rva0028B525DwordSlot::set at 0x0028B525. This preserves the thiscall
ABI and established +0x40C dword write without inventing an Object method
identity. Setter provider and consumer are both current and byte-verified.
The main COMDAT raw bytes are identical; its only relocation referent changes
are these two setter calls. One helper COMDAT is removed, none is added;
all other retained COMDATs, including the setter provider, are identical.

Acceptance: ./build.sh and link_check.py --prepare-current pass 117/117
rows across the consumer and provider, including float/string/import checks.
link_check.py reports both units LINKS, 1,507 -> 4,101 bytes. Paired JSON
records strict current receipts, hashes and exact before/after findings.
find_declared_unmatched.py, check_csv.py and git diff --check pass.
Closed-strict gains were not measured. No pins, ledger, shared header or
verifier code change, and no census or full link cycle.

Sweep: this was the only census consumer with the unresolved setter name.
Other Matrix3D-constructor consumers have independent blockers or active
claims. Existing getPathExtraDistance/maxOf unreferenced differences are
diagnostic only under retail-truth-2 and are left alone. BFME1 92f6bbe8 donor
link repairs were reviewed this session; see formation-preview-link-20261020.
