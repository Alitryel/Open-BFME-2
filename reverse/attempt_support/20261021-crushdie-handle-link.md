# CrushDie sound-reference link repair

At BFME2 parent 7dd0c9f3d5 (plus queued 4ec5200859), with census d08db10acb
(2026-10-21 18:42), the current CrushDieModuleDataCtor unit fails legacy
link_check: unresolved `??0AudioEventRTS@@QAE@XZ`, 0/168 nonpadding bytes.

Target evidence: constructor 0x2539B3 pushes callback VAs 0x726BE6/0x50F149,
element size 4 and count 4 for the member at +0x38. Destructor 0x2550B3
passes the same destructor, size and count. The callbacks respectively clear
the first pointer and conditionally tail-call OpaqueRefCounted::Release_Ref
(0x50ED3). These are the existing Rva0010F149Handle providers, not a full
AudioEventRTS. The old comment incorrectly borrowed Shadow::ShadowTypeInfo's
constructor/destructor (0x79514/0x793FA); neither callback reaches them.
The handle's original identity remains unknown. The donor supplies only
m_crushSounds and the percent-loop structure; target bytes prove the view.

Replace this unit's incorrect private AudioEventRTS member declaration with
the existing four-byte counted-handle declaration. No new pin, alias, body,
or global. The earlier BFME1 linking review at cea1e973 remains applicable:
this repair is target-specific, with no additional donor/header change.

Acceptance:
- ./build.sh <unit>: 3/3 rows pass (82+58+28=168 bytes), string/float/import pass.
- link_check.py <unit>: legacy 0/168 -> 168/168, sole unresolved removed.
- link_check.py --prepare-current <unit>: all three rows verified using a
  strict reusable compiler receipt. This does not measure self-strict or
  closed-strict link closure; neither gain is claimed.
- find_declared_unmatched.py <unit>: all definitions already matched.

Local raw evidence: build/link-seat-20261021e/next-before.log,
crush-after-build.log, crush-after-link.log and crush-after-strict.log.
