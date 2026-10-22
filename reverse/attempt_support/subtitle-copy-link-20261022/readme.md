# Subtitle placement-copy providers

At BFME2 723cbf85ce, the subtitle scan unit and two STLport copy/fill loop
units emit competing _Construct specializations for three address-derived
8-byte element views. Their pinned native callee is 0x0026061A. Its existing
typed owner Rva0026061AConstruct takes BfmeStringRecord005DDD40 and performs
the null-guarded placement copy, invoking the record's native copy constructor.
See placement-copy-family-20261020.md for independent whole-body/EH proof.
The subtitle unit already constructs the same UnicodeString/word record and
casts it to its stride view; plain word copying loses string ownership.

Each imported force-inline specialization calls the existing typed owner
through that proven record view. This emits a direct call to the real provider,
removes each wrong COMDAT, and introduces no symbol pin, linker alias or new
out-of-line body. Application element names remain uncertain; the change does
not promote the artificial POD/virtual element declarations into target facts.
The filled/copied values use their existing proven stride and native callee.

The /Ob0 fill-loop trial emitted an indirect import call and failed its byte
row; /Ob1 allows the forwarding body to inline and preserves the original
37-byte loop. The other two units passed their first scoped byte checks.
Combined result: 9/9 rows exact, including five parent-EH-derived cleanups.

Paired current previews against census ae3b3e68e2 (2026-10-22 11:05 UTC):
subtitle 0 -> 537 B, uninitialized_copy 0 -> 38 B, uninitialized_fill_n
0 -> 37 B; unchanged typed provider stays 1,097 B. Net new linked matched
bytes: 612. No authored C++ byte growth. The broader push_back/overflow
families contain declaration-only uses and independent blockers, so they are
not edited merely to replace unresolved aliases without a measured gain.

Checks: build.sh 9/9, strings/floats/imports; strict reusable source receipts
for all three consumers; new-COMDAT-variant check; declared-definition gate.
Commit hook additionally checks EH and normal class/data/code integrity.
These are legacy current-object link previews plus self-strict source gates;
closed-strict closure is unavailable with the published index's 3,469 missing
current-ledger provider objects. No census/full link cycle was run. BFME1
inputs remain verified pointer 37c3022de1, with no unverified donor transfer.
