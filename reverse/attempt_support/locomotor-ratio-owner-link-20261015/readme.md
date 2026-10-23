Locomotor ratio helper ownership repair

BFME2 base: e37dfae48666c890a4489b0fe61c48ac7f1d1299. Measurement/index:
ac77c85054, 2026-10-15 14:25 UTC. proof.json records its SHA256 and the
before/after source, object and dependency-receipt hashes. No per-row data-back
artifact was available or used to manufacture a ranking.

Both Rva001E3F08Calc.cpp and Rva001E4073Ratio.cpp emitted an exclusive
definition of the existing 31-byte helper at 0x001E3F08. Both units therefore
failed the local link check solely on that duplicate. Ratio already needs the
visible noinline helper to preserve its verified EDX register-use analysis.
Move the helper's ledger ownership to Ratio and remove the redundant Calc
definition. Keep the 31-byte sibling at 0x001E3F2E in Calc and the 102-byte
caller at 0x001E4073 in Ratio. No new identity or layout claim: these remain
address-derived names with unproven owner identity.

Before and after, link_check.py --prepare-current on the two explicit owned
sources passes all three rows (164 unique retail bytes) and produces strict
reusable receipts. The source/object/receipt snapshots and proof script are
under build/locomotor-ratio-owner-link-20261015. The proof compares every retained
nondebug section's bytes, flags, external definitions and symbolic relocations:
all are unchanged. The sole removed section is the duplicate 31-byte helper;
its whole section is identical to the retained Ratio copy. Exclusive definitions
and COMDAT copies change only by that removal; undefined/weak bindings stay
unchanged. proof.json includes the removed section and paired findings.

The paired preview replaces the two owned objects in separate in-memory copies
of the identical index: legacy local clean units 0/2 -> 2/2, predicted LINKED
0 -> 164 existing matched bytes. Both edited units are self-strict. This is not
a closed-strict or measured census gain; authored C++ byte growth is zero.
The index and reverse/link_status.csv are unchanged.

Four related provider/consumer objects were also refreshed identically into
both previews. Their findings are unchanged. Rva001E7CDFWings,
LocomotorRva001E9A00AerialMove and LocomotorGetMaxTurnRate remain locally clean.
LocomotorMoveTowardsAngle still lacks rva001E7ECA and rva001E9083; it is not
repaired here. Only GetMaxTurnRate among those four has a self-strict receipt;
the other peer results are legacy, as recorded individually in proof.json.
The ordinary six-source local check reports 5/6 clean, 2083 -> 2247 bytes.

Dedicated donor review: verified BFME1 checkout remains
a7c38d3b2597121f178ab5190b3062478823257d. Read-only upstream review through
7afa50f4cfe2205fab66de58312bc722dccf8cbe includes 4966496c5ae401ec877a044e1ae6dd04f9d9f65c
(AsciiString alternate inline emission), de59a7e9f891b3ed2d4221d151ca881f4b75a583
(Apt expression convergence), and b66f793f3d886b07b8698ff04aa5ce9707eb896a
(duplicate body removal while retaining dependent emitters). The ownership
principle is applicable; no donor ABI/layout was imported. BFME1 freshness
update remains blocked by the other worker's file:reference/open-bfme-1 claim
and the required controlled old/new full-byte comparison. The verified pointer
and headers were preserved; no success stamp was written.

Acceptance: full affected-source byte gate 3/3; find_declared_unmatched,
class_gate, enforced data_check, converged data_check (8 addresses, no second
names), eh_verify (no EH rows), placement (0 bodies/0 pins), and local link
checks pass for the touched units. Staged variant, ledger and whitespace checks
are run before commit and hooks repeat the required acceptance checks.
No full census, link cycle, nightly, boot or scheduler runner was invoked.
