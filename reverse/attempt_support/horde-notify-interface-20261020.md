# Horde death notification: correct interface receiver

Target `HordeContain::notifyOfMemberDeath`, RVA `0x004704E4`, whole extent
563 bytes through `0x00470717`, `ret 4`. The existing bank and all target
verdicts were reviewed. WorldBuilder `0x010B3BB0`, the secondary interface
and retail's negative member offsets retain the established identity and ABI.
Retail `0x0047068D/91` loads the vtable and receiver from ESI, the incoming
secondary pointer; EBX is the primary pointer, ESI minus `0x11C`.

The previous 563-byte bank explicitly called slot 96 on EBX through
`PrimarySlot96View`. That is a different object receiver, not an admissible
register-allocation alternative. The replacement bank removes that view and
calls the actual inherited `rva0046D3FC(0)` instead. It emits **567 bytes**,
all direct calls resolved. The first difference at `+0x1C` is a branch-length
consequence of the extra four bytes. The remaining call rematerializes the
secondary pointer instead of reusing incoming ESI. The overlapping 563-byte
relocation-resolved sequence ratio is 0.973357; this is not a full-body match.
The bank score is conservatively 0.97, and no C++ byte progress is claimed.

New hypothesis: keep the primary member-helper context that preserves EBX,
but pass the actual secondary interface separately from the caller. Nine normal
`explain_mismatch.py` builds include the honest 567-byte control, interface
pointer/reference, both argument orders and an entry capture. The explicit
dual-receiver forms emit 577, 579 or 590 bytes, with earlier allocation changes.
Eight further controls move the real owner-object/drawable lookup inside the
primary helper, using member/getter and direct/local forms. All emit 579 bytes.
Thus a dead helper `this` alone does not explain the allocation loss.

Native evidence rechecked: the drawable is loaded from the horde's own Object
at secondary offset `-0x114`, the refresh flag is drawable `+0x43C`, and the
virtual call uses secondary vtable byte offset `0x180`. Do not restore the
earlier wrong primary-pointer call or refresh the dying member's drawable.

No production source, row, pin, header, compiler flag or escape hatch changed.
The claimed body is released after recording this bank. The target still
requires the correct secondary receiver and the native primary-address CSE
in one emitted function; do not replay unchanged argument-order controls.

Inputs and complete outputs: `build/horde-notify-dual-receiver-oct20/`, including
`inputs.json`, `results.json`, `owner_results.json` and `wb-retail.txt`.
Replay drivers are retained beside this note as `.py.txt`; they read the bank,
resolve its intended relative includes against the real home, and compile only
isolated scratch files through normal `explain_mismatch.py`. Their original
input bank SHA is recorded in inputs.json; the new bank differs only by the
documented removal of the incorrect view/call and its obsolete commentary.

Time approximately 14 minutes, model gpt-6.1-sol.
