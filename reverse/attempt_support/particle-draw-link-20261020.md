# Particle draw helper ownership

Inputs: BFME2 ebfb4fa883; unchanged retail-truth-2 census 03035cf02c,
2026-10-20 22:09. BFME1 pointer remains the verified 68c5ce2789 revision.
Reviewed upstream 93a40127 callback-provider and c8e7e6c6 pool-pointer repairs:
their ownership principle applies; no target-specific code was imported.
The newer donor pointer still needs the separately required comparative full gate.

QuadDrawModuleDoParticles uses the existing bfme_vp_math Vector4 header before
native matrix4.h. Its imported force-inline float constructor preserves the
native inlined stores and leaves external ownership with the existing row at
0x006D8A30 in matrix3d.cpp. No new pin or alias. LightningDrawModuleDoParticles
uses the same inline-only ShaderClass copy-constructor declaration already
verified in StreakDrawModuleDoParticles and binds its type-2 preset through
that unit's BfmeParticleType2ShaderBits owner (data row 0x009B6250, value
0x00194033). The shader's four-byte view and the target relocation remain
unchanged; this removes the alternate address-named global spelling.

Paired current-object LEGACY predictions against the same frozen census:

| Unit | Before | After |
| --- | ---: | ---: |
| QuadDrawModuleDoParticles | 0 | 2,120 B |
| LightningDrawModuleDoParticles | 0 | 1,740 B |
| Total | 0 | 3,860 B |

All five ledger rows pass the ordinary byte gate, including the Quad cleanup
funclet whose compiler label renumbered while its parent EH graph stayed exact.
Both EH graphs verify EXACT. Lightning also passes prepare-current with a strict
reusable compiler receipt. Quad's existing WWMath include graph cannot receive
a strict reusable receipt: include inventory reports an unknown macro/parent
search root and an out-of-inventory header. Adding a direct Lib include root
and replacing its relative RGBColor include did not repair this, so that trial
was reverted. No self-strict placement or closed-strict gain is claimed.
Unreferenced Matrix4x4 and ShaderClass assignment differences are diagnostic
only under retail-truth-2 and were left alone.

Local diagnostic logs: build/seat8-{quad,lightning}-before.log,
seat8-particles-after.log, seat8-particles-byte-final.log,
seat8-{quad,lightning}-eh.log and seat8-lightning-strict.log.
Other indexed ShaderClass-copy consumers retain unrelated blockers; no
unmeasured suppression sweep was made. Current Object-vector destructor leads
were checked against the existing 20261020 handoff and were not retried.
