# FadeInTextRender duplicate LoadAssets removal

At b633136247, the two FadeInTextRender units emit competing strong LoadAssets
definitions. The dedicated initializer uses the canonical frame-rate global;
the draw unit also carries an unused older initializer with g_009BA4E8.
The draw body does not call that initializer. Remove only its duplicate body
and obsolete global declaration, retaining the virtual declaration and dedicated
provider. No class layout, method identity, pin, flags or ledger changes.

Checks:

- Before/after explicit bounded link_check --prepare-current: all 5 rows exact,
  strict reusable receipts; 1 string and 11 floating literals verified.
- Same published index c2c5ac8c27, both current objects refreshed in memory:
  2 blocked -> 2 clean, 0 -> 822 source bytes linked (341 + 481).
  The 386-byte published rank for the initializer includes 45 funclet bytes;
  the paired source-byte measure excludes generated funclets.
- All retained named code bodies and relocations are unchanged, allowing only
  renumbered compiler $T/$L local labels. Removed named bodies are LoadAssets,
  its EH handler, fadeTextBase, and its now-unused AsciiString ctor/dtor copies.
  Aggregate .text/.text$x sections shrink with these definitions and cleanups.
- EH verifier before/after: 2 EXACT, 0 missing, 0 baselined. Declared-definition
  check, CSV check and git diff --check pass.

This is a self-strict paired legacy-index preview, not closed-strict or a fresh
census. The index/status/history are unchanged. The whole-tree current-ledger
preview remains blocked by 46 missing objects; no full runner was started.
BFME1 donor provenance stays as documented in the sources (dedicated initializer
and draw body): this change does not transfer a new donor layout or identity.
The committed verified donor pointer remains 64d369b90170; the newer upstream
pointer and submodule freshness repair are owned by another seat.

Other attempted causes in this batch were restored, logged and released:
virtual-base deleting helper (EH shape), ostreambuf iterator assignment (inlining),
bridge duplicate (SSE register allocation), unsigned-vector allocator ctor
(nested constructor inlining). Refreshed key-copy duplicate rankings were stale;
their current baseline already links, so no repair is claimed there.
