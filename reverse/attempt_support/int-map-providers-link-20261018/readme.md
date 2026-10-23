Int-map iterator and provider consolidation, 2026-10-18

Base: 1e4aa6349f2edba2f026a182b0f9f546462a2572. Published index: 2d2ca9cd35, 2026-10-18
18:45, retail-truth-2. proof.json records the index hash and both object hashes.

Nine consumers emit incompatible size-profile prefix-increment wrappers for
STLport map<int,int>::iterator. TU-local imported forceinline specializations
preserve the unchanged STLport 4.5.3 expression while leaving the callable
20-byte native provider at 0x169ED0 in stlport_map_int_int.cpp. The same method
already works in AIGroupChain00472B54.cpp; no new identity, ABI, pin or alias.

The main speed-profile int-map unit also emits non-retail clear, tree assignment
and map assignment. Declarations retire the assignment copies in favor of the
existing native owners at 0x2CF742 and 0x2CF9CA. clear needs the unchanged vendor
body visible inline: declaration-only changes the matched range erase. The
imported inline definition preserves that erase and removes the external copy,
leaving the native owner at 0x6AA1C. Removing assignment also removes incidental
minimum/maximum leaf emissions. Their existing full 26-byte rows move through
verified add_match to StlSweepR3Rva00156FA0.cpp, which already emits both native
bodies. Its source is unchanged. Imported assignment visibility did not retain
those leaves and was discarded. No forced dead call or fabricated emitter.

Paired current-object legacy preview across twelve consumer/provider units:
20 local blocker findings removed, none added; the main int-map provider becomes
clean. Original source ownership has 136 linked nonpadding bytes; final ownership
has 691 (+555). Of that, 503 bytes belong to the repaired provider, and 52 are
the two unchanged leaves now owned by an already-clean unit. All 1,203 retained
COMDAT bodies and normalized relocation digests agree. Strong binding sets are
unchanged, no new import references appear, and removed exports create no newly
missing matched foreign callers in the same-index graph. Other nine consumers
retain unrelated blockers. No closed-strict, full census or link.exe result.

Acceptance: ordinary byte gate 96/96 across twelve sources; EH 10/10 EXACT;
strict reusable receipts 78/78 across nine compatible sources. The other three
have existing include-inventory limitations and are accepted by the ordinary
byte gate, not claimed strict. All affected sources pass the frozen-definition
check. Placement rescans find zero bodies and zero pins. C++ exact coverage
is unchanged: these are linkage and ownership repairs. Normal hooks run.

Reference lanes refreshed at verified BFME1 a18d9ed5: ranked zero donors and ZH
zero packets; near/lift leads reviewed against prior recorded blockers. ZH
compiled inputs unchanged. Reviewed BFME1 helper-ownership repair 67f4eab2:
its private rename is only a technique lead; this repair uses the existing BFME2
inline-preserving specialization and target providers, not a donor class layout.
No reference pointer, shared header, verifier, baseline or generated source edit.

The published iterator cohort also contains four larger units (PeerThread,
LivingWorldLogic, CreateAHeroHero, CastleBehaviorRegisterOwnedObject). They were
outside this bounded source batch and are not claimed repaired or exhausted.
Scratch objects and proof script remain in build/local-macos/int-map-link-20261018.
