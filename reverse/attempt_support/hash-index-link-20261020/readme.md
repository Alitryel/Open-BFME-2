# Native hash-index helper ownership

At base 4a31eab426, Rva00461BF0HashIndex emits a non-retail _M_insert
specialization pinned to 410E23, blocking 155 authored bytes. Its find reference
also uses the donor name for the native provider at 41534B. Retail calls and the
existing owner rows establish these two provider addresses and their ABI.

Keep the donor hash-map operator[] symbol and construction/cleanup semantics,
but specialize that operation to call the actual rowed find and insert owners.
No out-of-line adapter, additional alias, or new pin. Retire the two now-unused
donor helper pins and lower their hatch counts. Native pointer/iterator views
follow the provider declarations already used by Rva00410DDFInsert and
MilesAudioCache. The insert payload stays opaque: the 12-byte node provider is
not evidence that the donor's full value class has that identity or layout.
Donor 6d9434269164392c5ba62aaa7c15a86b5b020d76 and the existing /O1 compiler
settings remain the basis of the parent reconstruction. The current BFME1
reference 4483e88da1c2 and its linking ownership repairs were reviewed.

Paired saved-current before object and after object, one unchanged census index:
0 -> 155 authored bytes link. Restoring the two original pins in the after
measurement still yields 155, proving this is not a gain from making the old
COMDAT unaddressed. Existing insert and find-provider units stay linked at 68
and 842 bytes. The proof records source/object/index hashes and full verdicts.
This is a bounded legacy preview with self-strict byte receipts, not a
closed-strict gain or a full link-cycle measurement.

Acceptance: build.sh 4/4 rows, including both renumbered EH funclets through
parent EH evidence; link_check --prepare-current passes; allowed_symbols 9
references, zero wrong bindings; find_declared_unmatched passes; pin consistency
passes. No maintainer-only verification runner was started.

Trials: declaration-only insert had no compatible provider; an inline adapter
matched but retained an unrowed helper and the old find binding. The direct
specialization initially emitted no body; explicit instantiation restores the
existing row symbol and gives the exact parent and cleanup bytes.
