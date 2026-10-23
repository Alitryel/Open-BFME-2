# Audio float helper link binding

Base: `722087ac4e8ea4640befcaf7a1f8483723196a46`.

Retail `0x00210C91..0x00210CA2` is a complete 17-byte SSE float store to
ECX+0x98 followed by RET4. The render-object method already owns the different
13-byte integer-MOV store at `0x000E43E7`. An additive pin named that render
method at the SSE body, masking incorrect helper bindings in the audio override
setter (`0x00433498`, 23 bytes) and transfer routine (`0x004331C6`, 458 bytes).
The strict link truth resolves the render method through its ledger owner and
correctly rejected both callers.

Replace the old gen-alias row with a real, neutral C++ float setter in the
existing Disp32FloatFieldSetters.cpp family. Bind both audio calls to this
provider and remove the obsolete pin. Retail call operands at 0x004334A8 and
0x433359 independently establish the target; proof.py derives these offsets
from object relocations and checks the image. Original owner and field name
remain unresolved. Ambient max-range terminology comes from the existing
ZH/BFME1-guided consumer, not from byte identity alone.

## Paired evidence

Frozen index receipt: `ac77c85054`, 2026-10-15 14:25. SHA256:
`a56a77c2b6ade796640ae98e6b02aaa5f1b51cac34e0b31c2f115caf5cda9da3`.
This is a local link preview with self-strict current objects. The unchanged
index is loaded separately for the saved baseline and repaired cohort. Neither
the census index nor link_status.csv was modified.

The cohort improves from **1/4 to 4/4 clean**, clearing **5 findings**:

- Float setter family: clean before and after; 147 to 164 nonpadding bytes.
- Override setter: COMDAT/selected findings cleared; 23 bytes newly link cleanly.
- DynamicAudioEventInfoXferNoName: COMDAT/selected findings cleared; 500 existing
  nonpadding bytes newly link cleanly (includes the existing bit setter).
- Rva00433796AmbientProps: selected override-setter finding cleared; 897 existing
  nonpadding bytes newly link cleanly.

Thus **1,420 existing nonpadding bytes** are unblocked, with another **17 bytes**
recovered from a generated alias. The preview total is 147 to 1,584 bytes.
Closed-strict closure and full-link gains remain unmeasured; no full runner or
census was started. The unchanged measured progress card cannot show this local
link improvement until a subsequent census.

proof.py verifies the provider's nine retained COMDATs, every retained nondebug
section in all four units, data bindings, and the two changed external REL32
referents. Caller instruction bytes stay identical; the consumer is entirely
unchanged. The new helper has exact retail bytes, no relocations and a retail
link-truth verdict. Data findings: zero. Saved before objects/sources are in
ignored build/audio-float-binding-20261015/before; the committed JSON preserves
hashes, index receipt and findings. Replaying the paired script requires that
local baseline and the same index.

Acceptance: strict preparation and normal build gates pass 14/14 matched rows
across four sources; local link_check passes 4/4; EH gate passes its one EH row;
string/float/import checks pass; pin consistency, class gate, undeclared-function
check, check_csv and diff whitespace check pass. No new pin, global alias, inline
assembly, shared header or verifier change.

## Reference review and handoff

Reviewed donor `363b11ce5ffda35ebbf8a41f87dbdd3273a3f8af` (display zero-provider
binding) and `121fc40f6a502481e19d1b9fa7964248edcefd97` (queued-download lifetime
reconciliation). Existing BFME2 EAString binding evidence was also reviewed.
Only the principle of using the independently established target provider is
applicable; no donor audio layout or address is imported. Broader unchanged
COMDAT/layout blockers were not retried.

BFME1 checkout and committed pointer remain
`a7c38d3b2597121f178ab5190b3062478823257d`; official master fetched as
`95eeb3bef370a7cd730b0ad5f228c317c8756e72`. Another seat holds the reference-scope
claim, and controlled old/new-input full byte comparison remains outstanding.
No successful freshness stamp was recorded and no donor pointer was advanced.
