# STLport cached-grouping assignment repair (s6, 2026-10-23)

Scope: the two 238-byte basic_ios::imbue bodies, their emitted string helpers,
and the generic-widening initializer that formerly selected a wrong narrow imbue.
SureForge Light: bounded template-emission repair, with retail-byte, EH, data and
combined-provider link checks. Base 8cf1898df425a1f5c6c7a64a9ae3574ba62c68e3.
BFME1 reference remains 138757e9b74645fbcbb7724a7af2764e34931e11;
the semantic donor is the unchanged vendored STLport 4.5.3 stl/_ios.c:71-85
and stl/_string.h:304-308, not a BFME1 linking claim.

## Cause and repair

The original imbue instantiations emit a 36-byte narrow string copy operator,
while its retail owner at 0x120C0 is 41 bytes (extra empty-tag value initialization).
Keep the vendor imbue body, expanding only cached-grouping copy assignment into a
TU-local forceinline helper: self-check and assign(source.begin(), source.end()).
Const casts restore the original char* range type; no source buffer is modified.
Binding grouping() as a const-ref argument preserves its full-expression lifetime
and returned pointer register. Declaration-only copy-assignment specialization
leaves the external operator to its verified owner. No shared headers or flags change.

The explicit imbue specializations are inline, followed by explicit instantiation.
This retains SELECT_ANY template emission: a strong narrow specialization collided
with the incidental copy in stlport_narrow_ostringstream_dtor.cpp. Inline alone (and
inline+noinline) omitted the body; inline plus explicit instantiation preserves all
238 bytes and permits the verified copy to be selected. Both twins use this form.
The public begin/end helper form was chosen over a protected-access macro or a base
reinterpret cast; its two getter COMDATs are harmless in the combined link preview.

The initializer now declares narrow imbue instead of emitting its longer nonretail
copy. Four existing helper bodies are explicitly instantiated there. Five helpers
already emitted byte-exactly by narrow imbue move there through add_match, with
unchanged names, addresses and extents: 0x13720/7, 0x7810/13, 0x13740/17,
0x13270/13, 0x15E50/27. The assign row at 0x13270 had redundant gen-alias and
object-symbol=self annotations; the row is directly resolved to the same vendor
symbol and has no second row at its address. No new name, pin or alias was added.
These source-only rehomes recover no new unique bytes.

## Verification and limits

27/27 rows: wide 1, narrow 10, initializer 16. Scoped build logs accompany this
record. raw-extents.txt independently reads each full imbue symbol: exactly238,
retail-equal resolved bytes, zero unresolved relocations. All three EH graphs are
EXACT; enforced data_check has zero findings. The source editability checks pass.

Combined in-memory preview against published index456ce161c5 (2026-10-23 06:28):
narrow0->325 and wide0->238 linked bytes, +563 total. The assignment owner stays
41->41 and FstreamDefaultProtectionNameCtors stays528->528; neither is new credit.
Initializer remains0->0: unresolved ctype<char>::scan_not and wrong __find_if copy.
Its prerequisite repair is not a full link success. No census, link.exe, data-back
or boot run was performed; placement claims remain preview-only until an authorized
census. No gate, baseline, hook, shared header or pin edits.

expression-trials.md/results and annotation-trials.md preserve the unsuccessful
lifetime, dispatch scheduling and dllimport variants. Their production wording
refers to the original scratch snapshot; this readme and final logs describe the
delivered inline-instantiation form. Larger diagnostic objects remain ignored under
build/wide-imbue-clean-s6 and build/wide-imbue-parent-s6.
