# MessageStream propagation consolidation blocker

The scoped Common planner and current approved TU plan retain the MessageStream.cpp
destination. Earlier directive and scalar-argument prerequisites are already fixed:
the ordinary merge dry run accepts the seed and GameMessageIntWideArgs.cpp, with
14 non-alias addresses. No source move or authored-byte increase is claimed here.

The propagation donor initially fails compilation because its MessageTranslatorNode
pointer cannot receive the header's nested MessageStream::TranslatorData pointer.
A donor-only trial using the existing nested name and five-word layout preserved
its standalone 101-byte row, but the ordinary complete composition still rejected
it for bytes. The attempted source edit was reverted.

Read-only inspection of the generated trial object identifies the remaining
boundary. In build/tu_skeleton/3d5fe4ed491ed5ea.obj the first translator load is
[ebp+0x10], the first message load is [ebp+8], and the final stores use +8/+0xC.
Retail 0x00310FF5 uses +0x14, +0xC and +0xC/+0x10 respectively. Other instructions
have the same shape; relocations remain subject to normal verification. The
standalone matching object build/tu_skeleton/51303f33d7ac0e70.obj has the retail
offsets. The destination header's GameMessageList inherits the sweep shim's
SubsystemInterface; blindly reconciling the nested node cannot fix its base size.
This is a target-byte/layout conflict, not proof that a donor layout or name is
correct. Canonical SubsystemInterface lives under Code/Libraries/, outside this
seat's pool; coordinate any base/header adoption with that pool and preserve all
existing seed rows. No shared header was changed.

Receipts: build/codex-message-propagate-{before,after,dryrun}.txt and
build/codex-messagestream-{plan,dryrun}.txt. Official build before and during the
trial preserved 1/1 row (101 bytes); declared-unmatched passed. The full supported
dry run still accepts only the seed and scalar donor. Coordinate-header,
GameMessage destructor-field, MessageStream destructor and CommandList byte
blockers are independent; mixed/protected sources remain untouched.

No source paths, include consumers, protected registers, debt keys or hatches
changed. The outgoing path audit is empty. Both MessageStream file claims are
released after this blocked handoff; compatible scalar work remains for Luna.
