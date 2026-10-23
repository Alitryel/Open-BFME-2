# Helper binding link repairs, 2026-10-20

Input tree: bfccc2efe4. Published census: b73720bed9, 2026-10-20
05:34, retail-truth-2 legacy predictor. BFME 1 donor pointer reviewed:
a2c8039e61ad4dfb20c095d8eafe048248d31f25. Its declaration-binding repairs
(including 51b97cd79) supply the approach, not BFME 2 identity or layout
proof. No donor source, header, pointer, pin, alias or baseline was changed.

Three existing units move from zero to 243 linked matched bytes in paired
`link_check.py --refresh` previews against the same census and input tree:

| Unit | Existing matched bytes | Repair |
| --- | ---: | --- |
| stlport_vector_scalar_copy.cpp | 67 | Use the existing vendor COPY_TRIVIAL_EXTERN switch to bind retail's shared copy helper. |
| FunctorRefInvoke005D388B.cpp | 61 | Declare the exception copy constructor so throw metadata uses the kept common implementation. |
| EmotionTrackerUpdateRva004B0DAC.cpp | 115 | Give the existing inline x87 rounding helper local linkage. |

The vector copy's native body and established pointer layout are unchanged.
The exception view remains 12 bytes: virtual pointer and the exception's
pointer/flag storage; the kept opaque copy transfers the same two words.
The emotion update retains the same inline fld/fistp sequence. These are
target/compiler facts; no new target identity or layout is inferred from
the donor repair pattern.

`--prepare-current` succeeds for the three original sources and again for
the three edited sources: three strict reusable compiler receipts and 3/3
ordinary full-byte rows, including extent and reference checks. The normal
gates reuse those exact receipts. Frozen-file checks, check_csv and EH
verification pass (the three final units have no EH-bearing rows). The
code-identity and definition checks report zero new findings for the three
final units. The attached paired previews refresh changed provider
definitions; the initial refresh also compiled/restored 3,544 stale objects.
The measured gain is legacy prediction, with strict compiler/byte evidence
for the three edited units. No closed-strict placement or closure gain, new
authored C++ bytes, census update or full link cycle is claimed.

Three unsuccessful investigations were restored and their file/RVA claims
released. LocomotorSetDoXfer's declaration-only overflow plus copy-helper
binding shifts its 413-byte body's frame from 0x1c to 0x20 and four stack
homes; an imported free-inline redeclaration is rejected C2375. It needs
emission control preserving the pointer temporary's lifetime. CreateAHero
assignment's implicit pair-destructor specialization passes 7/7 native
rows but leaves the COMDAT conflict; the existing CreateAHero copy/dtor
views and retail SkirmishAI/map-subscript provider need reconciliation.
The vector destructor trial also passed its byte and EH gates and appeared
to free 63 bytes in the legacy predictor, but the shadow code-identity gate
flagged its remaining destroyer provider as wrong at 0x5F97BC. The existing
alternatename does not establish that provider's retail body. The trial was
restored and superseded by a blocked log entry; those 63 bytes are excluded.
These blockers are not reopened by a model change.

Other checks this session: link_rank top 30 and near 2, class_views blockers,
repair_queue link, and name_globals dry run (zero rewrites). Current probes
show the pod-map and tree-copy units already link (661 and 404 bytes), so
they are not counted as this session's repairs. Rva004F60AAInit still has
the selected destroyer blocker; StrategicVeterancy also needs its real
AutoResolve destructor. Large vector-E16 and DamageInfo repairs belong to
other live claims. The BFME 1 upstream fetch found a newer data-only EDI
label commit, 0dc8a26a9c6041c73dc564754cd059dc54faa72a; the verified donor
pointer is retained and no new freshness success is recorded.
