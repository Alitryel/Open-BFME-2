# Apt text-predicate provider binding

BFME2 base: `27683550e3e154b7ef9dcdbf66ca52f7e14c8d32`.
Discovery used `repair_queue.py link`, `link_rank.py`, and the receipt-current
EAString consumer sweep from the preceding session. No ledger rows, boundaries,
layouts or compiler flags change; authored C++ growth is zero.

## Repair and target evidence

The path builder at 0x006FF980 calls 0x006E02B0 at offsets 116 and 245; the
variable lookup at 0x006FFD80 calls it at offset 200. Both used a bool-returning
local declaration, leaving the QBE_N name unresolved even though the existing
75-byte provider in AptValueTypePredicatesBFME2.cpp defines the QBEH name at
that address. Use that provider's declaration and explicitly retain the native
AL test. This reconciles the current C++ binding; it does not establish the
original source return type. The matched provider returns zero or one.

The path builder's inline isTextInst adapter previously also emitted a five-byte
out-of-line jump to the missing name. Suppress that competing external adapter
with inline-import/forceinline, as in the prior verified EAString repair. No
import reference is emitted. The old bool pin is unused after the two consumer
repairs and is removed. A Code-wide search found no further bool declarations
of this predicate. Existing int-declaring consumers need no edit.

proof.py checks the complete 682- and 781-byte parent bodies, every relocation,
all retained COMDATs, and every nondebug section against saved pre-edit objects.
Only the three REL32 referent names change; the five-byte adapter disappears.
The provider object is identical. Data findings are identical and no new link
finding or COMDAT variant is introduced. Saved before objects and sources remain
in ignored `build/apt-text-predicate-link-20261015/before/`.

## Paired local result and limits

The frozen index receipt is `a2839ea429`, 2026-10-15 13:35; underlying census
`5986a99448`, 2026-10-15 04:52. Its SHA256 is
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
The committed link-status discovery measurement is `4b7e7091c4`.

Both sides refresh the same three strict-current objects into separate in-memory
copies of this unchanged index. Findings improve by three: both missing bool
names and the adapter's COMDAT loser disappear. The path-builder unit becomes
clean; the provider stays clean. Clean units improve **1/3 to 2/3**, local
non-padding linked bytes **2,690 to 3,378 (+688)**. These are existing bytes.

GetVariable retains only the legacy index's missing findChild name. Its matched
1101-byte provider in AptValue.cpp passes strict preparation and ordinary byte
gates, but is absent from this index. It was neither appended to a handcrafted
index nor excused. Closure needs the runner's next index refresh/measurement.
This is a bounded legacy-index preview with self-strict object evidence, not a
new self-strict or closed-strict census gain. No link cycle, full census,
nightly, boot or scheduler runner was started.

## Acceptance

- `link_check.py --prepare-current` on both consumers, the predicate provider,
  and AptValue.cpp: **38/38 exact**, all four strict reusable receipts current;
  92 string literals verified, zero skipped/baselined strings or imports.
- `./build.sh` on the edited consumers: **3/3 exact**.
- Three-source `link_check.py`: path builder and predicate provider LINKS;
  GetVariable retains only the out-of-index findChild finding (expected exit 1).
- Paired proof: all object/section/relocation and no-new-finding assertions pass.
- `eh_verify.py`: **2 EXACT**, zero baselined/missing.
- `data_check.py --enforce`: zero findings; `--converged`: eight addresses,
  zero second names and zero unjudged rows.
- `link_check.py --new-variants`, `find_declared_unmatched.py`, `class_gate.py`,
  `pin_consistency.py --check`, `check_csv.py`, and `git diff --check`: pass.
- Affected-unit `place_bodies.py` resweep: zero bodies, zero pins.

## Reference review and handoff

Reviewed BFME1 repair `d003077f0b7ce97622adb7a53f1fe76653433c5c` for binding a
consumer directly to an existing provider and
`66b19a8e95a4add525ef808fcea088e306798e2b` for suppressing competing inline
copies. The techniques apply; no donor layout or body is imported. The BFME2
providers and retail call sites supply the target facts.

The clean donor checkout/gitlink remains
`a7c38d3b2597121f178ab5190b3062478823257d`; official master fetched as
`e082760734795655f086939df77b393f4b728375`. The live foreign
`file:reference/open-bfme-1` claim and unfinished controlled old/new-input
verification block the reference update. Its stale success stamp is unchanged.
Do not repeat that update in parallel with its owner.

The Apt render/display-list dependency at 0x006F7720 remains deferred on the
recorded register-allocation residue and unrowed flags global. It was not
claimed or retried. AptValueVector's separate subscript ownership issue also
remains outside this repair.
