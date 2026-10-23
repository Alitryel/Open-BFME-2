# Narrow-record destructor link trial

Census c2c5ac8c27; source stlport_vector_narrowrecord_79c23_fill.cpp.
The implicit BfmeNarrowRecord00079C23 destructor is 68 bytes and calls the
string destructor three times. Its existing pin is native 0x79554, whose
86-byte destructor instead inlines three frees.

Removing the two declaration-only string destructors and retaining the char
proxy deallocate primary body with dllimport/forceinline preserves all five
matched rows and emits that 86-byte body. Paired legacy previews show the two
INI parsers would gain 177 + 197 bytes, while the provider still fails for an
additional non-retail String_base destructor copy. Imported-forceinline
String_base and basic_string destructor variants change inlining and introduce
an unresolved __imp destructor. Extern-template String_base does not suppress
its competing copy.

The candidate is NOT accepted: pin_admission.fold_proof_problems, called without
changing any pin, refuses the 86-byte destructor's DIR32 EH-handler binding:
its TU-local EH graph is not proven equal to Rva00079554RecordDtor.cpp's graph.
The native owner describes three vector buffers; the consumer describes three
narrow strings. Do not infer equivalent cleanup from masked body bytes.

Limiting vector instantiations and forwarding range destruction to the native
owner passes 5/5 and makes the provider's legacy preview link 370 bytes, but
removes the only old-name destructor definition needed by other callers.
That isolated gain would cause unresolved calls; this variant was discarded too.

All production edits were restored. Scratch baseline and variants remain in
build/narrowrecord-owner-link-20261018. A future repair needs supported cleanup
identity/layout reconciliation across the record family, including INI and
model-state callers; neither suppressing helpers nor the 374-byte legacy
preview is sufficient evidence.
