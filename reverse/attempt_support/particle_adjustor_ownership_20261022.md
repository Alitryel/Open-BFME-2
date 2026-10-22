# Particle Snapshot transfer adjustor: resolved ownership and vtables

The complete native entry `0x003ABAB3..0x003ABABB` subtracts 0x18 from
ECX and tail-jumps to the 21-byte two-Version1 transfer at 0x00560AE1.
It is not evidence that the containing particle owner is ObjectModule.
ObjectModule's existing provider and every existing caller retain their ABI.

Native constructors 0x003ACD71 and 0x003AE43F independently store the same
primary table at +0, category table at +0x14 and Snapshot table at +0x18.
The established address-derived Rva003AD273 view already owned the primary
deleting body and secondary deleting adjustor in those paired tables.
Extending that owner, rather than inventing an ObjectModule layout, gives:

| Interface | Native table VA | Verified prefix RVAs |
|---|---|---|
| Primary | 0x00C1CC28 | 3AD257, B3FD0, 3AE408, 560AE1 |
| Snapshot +0x18 | 0x00C1C324 | 3ABABB, B3FD0, 3ABAAD, 3ABAB3 |

The secondary table has exactly four entries. The primary table has eleven;
only its first four are modeled by this private view. The original containing
class name and remaining primary method identities remain unrecovered.

The canonical `reference/shims/moduledata/Common/Snapshot.h` already provides
the BFME2 destructor/load-post-process/name/transfer slot contract. Its FX
capitalized, non-const name and Xfer-reference switches match this family.
Raw BFME1/ZH Snapshot declarations have an incompatible ABI and were not used.
Both interfaces introduce the same transfer signature; MSVC naturally emits
the this-minus-0x18 adjustor. The two Version1 calls exactly reproduce the
existing provider, including both resolved call targets.

Five companion rows reproduce already-owned whole bodies: transfer 21B,
clone 55B, two empty hooks 1B each and name getter 6B. Clone allocation is 0x1C
and invokes the existing copy owner 0x003AE43F; its entire EH graph is exact.
The getter's complete 22-byte `DefaultDraw<CAT_DRAW>` string is verified.
These folds add no unique bytes and require no new pins.

The owner and its two old deleting rows were moved from the broad opaque
destructor batch into the existing FX constructor unit Rva003ABA83Ctor.cpp.
That unit's original 42-byte constructor and 44-byte explicit table remain
exact. The old already-marked absent-from-retail tag constructor moves with
the view; no new constructor anchor, export or global was added.

The two private ABI-only base views are novtable. Without that annotation,
their implicit constructors emit invented private base vtables and deleting
helpers, referencing unprovided base destructors. Suppressing those artifacts
does not define stub destructors or suppress the real derived tables.
Canonical Snapshot helper COMDATs match their existing retail owners.

Independent audits verified both 16-byte emitted prefixes, the eight relevant
code bodies, string data and clone EH graph. Normal production gates verify
42/42 code rows across the FX unit and remaining opaque batch, one existing
data row and EH EXACT 1. No undeclared functions remain; the placement sweep
found no additional bodies or pins.

Link preview refreshes both changed objects together. The FX unit links
cleanly, growing from 42 to 86 unique bytes: 8 newly recovered bytes plus
36 previously matched deleting bytes rehomed out of the blocked batch.
The remaining batch retains 23 unrelated unresolved destructors, down from
25 before this repair; its other 33 rows remain exact. This does not claim
that unrelated batch or all particle virtual methods are reconstructed.

This supersedes the section-5 ownership blocker in
`parallel_recovery_20261022.md`. Native addresses and ABI evidence establish
the partial owner relationship; they do not promote its placeholder name
to a recovered original C++ identity.
