# Allocator guard verification before release

The complete native body at `0x006C3180..0x006C3216` is 150 bytes, RET4.
Its existing address-derived identity is retained. The failure string names
the guard check; it does not establish an original public name for the entire
release routine.

The former MASM fallback reported an unreachable EBP register allocation.
Reconstructing the actual pointer and helper contracts reproduces the full
body in ordinary C++, including that register allocation:

- The chunk has two header words. The builder receives the address of the
  data at header+8, rather than a pointer loaded from that location.
- The guard builder takes six arguments, including its output length. Its
  returned run is capped at 64 bytes and clamped above the payload's first
  eight bytes before checking the allocator's guard-fill value at +0x50B.
- The failure reporter receives the chunk address followed by the complete
  failure literal. Delayed-fill verification and `(chunk, bool)` metrics use
  their real existing providers; the payload then goes to the base free call.

All 150 bytes agree with retail, with no unresolved or masked references.
The six REL32 targets are 6C25F0, 30E20, 6C2FB0, 6C30C0, 6C26F0 and 33150.
The complete 48-byte failure string, including NUL, agrees at RVA8E7C0C.
`allocator-guard-release-006c3180-proof.json` records the live source/object
hashes and independent strict-byte proof.

The body belongs with the existing allocation workers in
`Rva006C33D0Purge_Rva006C1CC0.cpp`. The original verifier unit remains
unchanged. The worker's empty base remains empty; a scoped physical view
reads the independently established +0x50B/+0x514 fields without moving its
derived classes. All four worker rows pass the normal byte gate. The normal
flag-proposal tool proves an `/O2` override: the region's added `/arch:SSE`
otherwise selects a CMOV and loses this row.

Linking limitation: base free at 33150 still has no recovered provider, so
the worker family remains outside linked coverage. Its older allocation
helpers already have unresolved providers. The separate verifier retains
its existing 429 linked bytes. No linked-byte gain is claimed, and the
unsupported `__assume` in the existing 33150 attempt is not used.
