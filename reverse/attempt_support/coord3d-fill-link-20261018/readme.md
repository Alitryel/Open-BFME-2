# Coord3D fill-insert link blocker, 2026-10-18

Current original Coord3DVectorFillInsertO1.cpp passes 1/1 at 0x4E29C8,
227 bytes. With the canonical Coord3D overflow provider current, legacy link
prediction still refuses its private allocation/overflow copies and parent.

One declaration-only trial for vector<Coord3D>::_M_insert_overflow removes its
visible body analysis and changes the parent to 232 bytes: callee-save pushes
move and the empty dispatch argument receives a zero-byte initialization.
The byte gate refuses it. Original source restored and rebuilt 1/1 exact.

Retail's last call at 0x4E2A9F targets 0x2A1C02; the canonical Coord3D overflow
name owns 0x2CDF8A. A declaration alone cannot establish the native variant or
preserve the optimizer's dispatch-tag context. Requires provider identity and
ABI reconciliation, not a pin or unchecked alias. No change to Code, new
matched rows or link gain. Claim released. t=5min.
