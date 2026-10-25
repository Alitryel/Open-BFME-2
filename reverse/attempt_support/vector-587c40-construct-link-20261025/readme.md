# Vector 0x00587C40 Construct link blocker

The measured trial ran at `0c6e5b14c8b7461ae4f8174bb8ce929ec0de9f09`,
not the later clean baseline `eb305fb1db3177049271705e739f709bc5cc8518`.
Both revisions commit BFME1 pin `0bf534ea7ccde110c456edb9cd2dd5dae823c953`.
Read-only tree comparison shows identical blobs for the two vector TUs,
`vendor/stlport/`, `reference/shims/bfmealloc/`, the inspected build and
verification tools, and `reverse/symbols.csv`; all four target ledger rows
are unchanged. Other rows in `reverse/functions.csv` did change, so this is
input-continuity evidence for the narrow source hypothesis, not a byte gate
or selected-link measurement at `eb305fb1`.

The matched 189-byte `vector<Rva00587375>::_M_insert_overflow` remains exact
in its published source. The two tested source shapes do not provide a retail-compatible
`_STL::_Construct<Rva00587375>` without breaking that owner:

| Primary source shape | Owner 0x00587C40 | Emitted Construct |
| --- | --- | --- |
| Member-only instantiation, potentially throwing copy declaration | 189/189 exact | 45-byte EH copy, nonretail |
| Member-only instantiation, copy declaration `throw()` | 192 bytes, changed calls and three nonretail tail bytes | 18-byte native body, calls 0x00587375 |

The second shape's ordinary `./build.sh` exited 1 on the owner mismatch. Its
guest compiler and transport exited 0; the 6194-byte object, sidecar, receipt,
raw channels, complete emitted-symbol inventory and host byte audit remain in
ignored `build/restart-bank/seat1-20261025/587c40-contract-pair-prep/actual-pair-01/primary/`.
The owner comparison covered all 189 bytes with no unresolved or masked
references. The tested copy clause changes the optimizer's exception summary:
it inlines the Construct null test and copy call into the owner rather than
retaining the retail call. The control TU was not compiled in this trial.
Both production sources were restored to their published blobs; the failed
object and sidecar are preserved as source-stale diagnostic evidence.

The native 18-byte operation at 0x00587410 null-checks the destination and
calls the 70-byte copy operation at 0x00587375. The ledger currently gives
0x00587410 the address-derived `Rva00587410Copy` body while `symbols.csv`
also pins the STL Construct spelling to that address. This is a naming and
ownership question, not evidence for adding a second real identity. The
control TU defines an inline field-copy constructor under `-Ob0`; its last
measured unmodified Construct was 29 bytes with an out-of-line placement-new
call. The two class views share the 60-byte stride but not a demonstrated
single definition/exception contract. Historical provider selection is not a
strict-current link result.

The actual STLport `_construct.h` defines generic Construct as placement-new
copy construction; it has no separate native helper body to import. The BFME1
`vector_ICoord2D_resize.cpp` donor supports the vector operation shape, but
does not declare this BFME2 address-derived element or establish its exception
contract. `docs/recipes.md` documents that a `throw()` declaration can change
MSVC EH-local aliasing; here the measured consequence also changes the rowed
owner's call shape, so the generic recipe is not a successful transfer.

An independent source-owner TU could in principle emit generic Construct
with the nonthrowing copy contract while the owner keeps its exact throwing
summary. That requires explicit scope for a provider/consumer identity and
emission audit: first reconcile the existing 0x00587410 row and pin under
normal naming rules, then prove a sole retail Construct definition and both
unchanged owner rows with full bytes, relocations, extents, EH and all emitted
symbols. Merely changing the primary copy clause, using extern-template
selection, or selecting the old 29/45-byte copy cannot pass. No such provider
edit or trial was performed here; no link or coverage gain is claimed.
