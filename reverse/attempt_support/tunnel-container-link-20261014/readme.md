# Tunnel container accessor link repair

BFME2 base: 624568625fc70cbaa42e515bcf5e6b2e09da7d26. Runner index:
147cfae2cb, 2026-10-14 07:27 UTC; SHA256 and source/object hashes are in
object-proof.json. Committed link_status.csv (67e1365aa9) was used only for
discovery. Index, census status/history, ledger, pins and baselines unchanged.

Rva004F571BReplaceContainedOwner.cpp inlines Object's container field at
+0x274 in the previously verified 129-byte body, native4F571B..4F579C RET4.
Its surplus generic getContainedBy COMDAT was 8b8174020000c3. The index keeps
StealthUpdate.cpp's +0x1B0 copy, 8b81b0010000c3 (first-view.json confirms
its current bytes/digest agree with the index). The generic name has no
retail address; these layouts cannot share an out-of-line accessor.

Rename this implementation helper to tunnelContainer and its one inline use.
This preserves the existing target layout, behavior, external methods and
neutral owner identity. It supplies no new retail identity or private class.
Target identity/layout remain those established by the original body and its
callers; the ZH TunnelTracker semantic lead is unchanged.

Acceptance:

- Bounded link_check --prepare-current before/after passes1/1 and proves strict
  reusable compiler receipts. Final build.sh also passes1/1, with no skipped
  or baselined literals/imports. These are self-strict object checks, not
  proof of dependency closure or link.exe placement.
- Complete paired objects retain19 identical COMDAT bodies/extents/digests
  and relocation facts. Renamed accessor bytes/relocations are identical.
  All nondebug ordinary sections, full relocations, external bindings and
  escape-hatch counts stay equal. Backups and executable proof remain under
  build/tunnel-container-link-20261014.
- Same-index legacy before/after preview changes one losing COMDAT to none:
  consumer LINKS0->129 existing bytes. Indexed generic keeper is unchanged;
  new helper has no other indexed providers/consumers. Other generic copies
  agree with the keeper; no further same-cause losing consumer is served.
- Frozen-definition, class, EH, data, converged-data and new-variant checks
  pass; no applicable EH rows, no data findings or second names. Placement
  resweep finds0 bodies and0 pins. Check transcripts are attached.

+0 authored C++ bytes; +129 locally linkable existing bytes in legacy preview.
No closed-strict, maintained census or actual placement gain is claimed.
No maintainer-only runner was started.

Reference review reuses the prior linking review at the clean verified BFME1
pointer23b143233b5a8664a3bdf8572df6d905c310a5a1 (freshness stamp2026-10-14
08:17 UTC). Donor d2e21369067f2f2c762c1c7ec2792c75f1ecf53d retires conflicting
local emissions; de59a7e9f891b3ed2d4221d151ca881f4b75a583 reconciles private
inline copies. The collision diagnosis applies; their pins, aliases and
layouts do not establish BFME2 facts. This change imports no donor code.

## Rejected RvaF6Ret suppression trial

Before this repair, inspected the still-conflicting counted-help handle and
Recorder's AsciiString return view. A single dllimport+forceinline destructor
trial in Rva0052B045.cpp passed3/3 byte rows and removed its12-byte surplus
COMDAT, but local link_check reported unresolved __imp_??1RvaF6Ret@@QAE@XZ
from EH cleanup. Reverted the source; restored byte gate passes3/3. No trial
gain claimed. Do not apply this suppression to the other eight consumers.
A proper string-return/view reconciliation touches forwarder003113DD, held
by another worker when checked; provider0030FA44 already has the real
GameMessage::getCommandTypeAsAsciiString identity. All trial claims released;
blocked record is in re_attempts.log. Snapshots remain under
build/f6ret-inline-link-20261014 for inspection.
