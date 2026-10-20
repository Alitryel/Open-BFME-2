# Shadow matrix provider binding (2026-10-20)

At BFME 2 1dbcc34b62 (plus the three retained local linking commits), using
published census 144ed0ccab, W3DVolumetricShadowCtor.cpp had one unresolved name:
`??0Matrix4x4@@QAE@XZ`. Retail's relocation targets RVA 0007671F. The existing
rowed provider is `??0Rva0007671F@@QAE@XZ`; its 64-byte storage ABI and four
16-byte element construction match this use. Its original class identity is
still unresolved. This change adopts the existing opaque name, not a new pin
or a claim that the donor's Matrix4x4 identity has been established.

Baseline link_check: 0/365 matched non-padding bytes link. After binding the
member type to the existing provider: 365/365 link in the legacy census
preview. Strict preparation verifies all three rows across consumer and
provider; the consumer's two rows, its float, and its EH table are exact.
This is self-strict byte evidence and a legacy preview gain, not a measured
closed-strict link-cycle result.

Two other candidates were restored and released before this repair:

* AITargetHeuristicBaseDefense.cpp (005737D6): declaring the empty filter base
  destructor out of line adds four cleanup calls and changes the parent.
  An imported forced-inline derived destructor preserves all three bodies but
  introduces an unresolved import and retains the losing deleting destructor.
  Remaining prerequisite: reconcile the filter destructor contract/provider.
* AptStrategicPlayerStatus.cpp (00523825): the existing unsigned-vector
  constructor/overflow specialization pattern changes the parent's stack
  frame from 0x50 to 0x58 and breaks 17 of 26 rows. Its native constructor
  target is 00211E58, whereas the plain outlined provider is 00025100.
  The inline lifetime shape must be retained. Restoring the source passes
  all 26 rows; no source change from this trial is retained.

The unchanged BFME 1 donor revision 92f6bbe8e1dcdb46b5d27da0674313efc822b790
was reviewed via the prior formation-preview handoff; it supplies no new
repair for these causes. Both rejected trials are recorded in re_attempts.log.

Recovery note: upstream 3c187b8bbb independently landed the same shadow
provider binding before this checkout was rebased. No additional linked-byte
gain is credited by this evidence-only recovery commit. The blocked trial
findings above remain useful handoff evidence.
