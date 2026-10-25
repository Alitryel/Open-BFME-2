# Forty-byte deque iterator linking repair

Inputs: BFME2 ce1b975697, clean verified BFME1 gitlink
0bf534ea7ccde110c456edb9cd2dd5dae823c953, published retail-truth-4 index
3bdfeee392 dated2026-10-25 00:45. Source semantics remain STLport4.5.3.
The BFME1 c20e733a declaration/emission reconciliation principle was reviewed;
this repair instead follows independently verified BFME2 element/owner evidence.

## Ownership and change

StlportDeque40Iterators.cpp still claimed two masked-placement cleanup wrappers:
__destroy at0041A42C/45B and _Destroy at0041A4C8/41B. Those wrappers forward
16-byte iterator values without establishing the element stride. Their actual
33-byte worker0041A382 destroys the28-byte record through0041A200 and advances
through00419DD2. The correct wrappers and worker already belong to the verified
NarrowStringRecord28DequeDestroy.cpp, with the original record name unknown.

The40-byte instantiation instead emitted an incompatible trivial cleanup loop
and a40-byte increment under names pinned to those other routines. Its increment
pin00421B1E names the independently verified12-byte increment. These are concrete
inherited type/ownership conflicts; declaration-only suppression would conceal
them rather than establish the right element identity.

Withdraw only the two unsupported duplicate40-byte ledger rows and their one
explicit _Destroy<Iterator40> instantiation. The seven independently verified
40-byte stride/iterator operations remain. The28-byte provider is unchanged.
No type/name substitution, shared header, pin, alias, ABI, flag, gate or baseline
was added or changed. Existing proper owners retain all unique byte coverage.

## Verification and paired measurement

- Before: normal two-unit gate14/14, including the two duplicate identities.
- After: normal two-unit gate12/12; literals, floats and named imports all pass.
- Scoped EH: one row has EH data, EXACT; no missing object or baseline debt.
- Scoped enforced data ownership: two sources, zero findings.
- Same current two-unit link prediction before/after, same census and provider:
  iterator unit0 ->201 nonpadding bytes; existing28-byte provider215 ->215.
  Total215 ->416, a net predicted LINKED gain of201 existing bytes.

The outputs are retained in before.txt, after.txt and eh.json. This is a paired
current-object prediction, not a new census, closed-strict result or runtime test.
No authored C++ exact-byte coverage gain is claimed. The index's older changes
already making the renderer and deferred vector units link are excluded.

## Separate read-only narrow-string finding

Current stlport_narrow_string.cpp still fails on its sole natural-name
_M_compare copy and insert<char*> copy. The former's135-byte native owner is
bfmeDoPW at00024FC0. The latter's old pin001EC1B4 now names a proven349-byte
LinearCampaignCarryoverInsert over172-byte records, not a byte-string insertion.
No source or pin edit was attempted there. Reconcile the actual identities and
providers before attempting declaration-only helper suppression. Its previous
ForwardIterator specialization bank is still useful, but the source now owns
only eight rows after earlier rehomes; stale21-row diagnostics are not current.
