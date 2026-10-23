# Fold the existing audio reference setter

Base checkout: 334ba8b14727c60b979bd95975cdc49e05e46ed4.
Discovery: repair_queue.py link, link_rank.py --kind D, followed by current
local previews. The owner Rva000A8CE5SetRef.cpp still had one live duplicate:
its exclusive setter definition collided with GameClientXfer.cpp's identical
inline noinline copy. The other leading duplicate entries were mostly already
repaired in current source; no stale queue improvement is counted.

Make the existing owner definition inline noinline. This retains its call and
makes the definition selectable like the existing caller copy. The target's
38-byte setter, pointer-at-zero view, +4 reference count and InterlockedIncrement
IAT call are established by the existing row and target evidence. No donor type,
layout or identity is imported. No header, pin, alias, ledger row, compiler flags,
baseline or census metadata changes. The whole owner file is verified, including
its 84-byte rebind caller and two generated EH rows.

The frozen index measures a2839ea429 at 2026-10-15 13:35, based on census
5986a99448 at 04:52. context.json pins its SHA256. The committed link status is
only discovery evidence. The paired proof refreshes the same two explicit
objects separately before and after, in memory; it never rewrites the index.

Acceptance:

- Bounded link_check.py --prepare-current before and after: 5/5 rows across
  owner and caller, strict reusable current receipts. Two strings and one named
  import verified, zero floats, zero baselined or skipped references.
- Independent ./build.sh owner: 4/4 exact. EH before and after: 2/2 EXACT,
  zero missing objects or baselines.
- proof.py proves all nondebug section bytes, flags, definitions and normalized
  relocations unchanged in both objects. All 75 emitted COMDAT bodies and
  extents retain their digests. The sole COFF selection change is the setter,
  NODUPLICATES (1) -> ANY (2). Both setter copies have the same complete body
  and symbolic relocations and are independently judged retail-true.
- Paired local findings: owner 1 -> 0, GameClientXfer 10 -> 9, removing exactly
  the setter duplicate in each. Every other finding is unchanged. Owner legacy
  predicted LINKED bytes 0 -> 122; GameClientXfer remains blocked. The ordinary
  two-file local preview agrees. New-COMDAT-variant admission passes.
- Data check --enforce: zero findings; --converged: eight addresses, zero second
  names or unjudged rows. Class, declared-definition, CSV and whitespace checks
  pass. Affected placement resweep: zero bodies and zero pins.

This is self-strict byte acceptance and a LEGACY local link prediction. New
authored C++ bytes are zero. No closed-strict gain, executable placement or
runtime result is claimed. GameClientXfer retains nine findings: its duplicate
xfer owner, four COMDAT conflicts and four selected-definition conflicts;
link-after.txt lists the precise names. No maintainer-only runner was started.

Before source/object/dependency snapshots remain in ignored
build/audio-ref-setter-link-20261015/before. To reproduce at the same index,
prepare the two paths from context.json on the base revision, save those files
there, apply the source change, prepare again, then run proof.py from the root.
The checked-in script writes its report only under that build directory.

Reference review: verified BFME1 checkout/gitlink remain
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor provider-ownership
repair d003077f0b7ce97622adb7a53f1fe76653433c5c and emission repair
66b19a8e95a4add525ef808fcea088e306798e2b. They supply the ownership/emission
principle, not this target's ABI or body; the immediate target sibling is the
existing GameClientXfer copy. Official master fetched as
e082760734795655f086939df77b393f4b728375. Updating the reference remains blocked
by its foreign file claim and outstanding controlled old/new full verification.
The verified checkout is preserved; no freshness-success stamp is written.
