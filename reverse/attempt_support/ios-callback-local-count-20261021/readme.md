# ios callback: initialized-local count is inert

Native 0x0001C090..0x0001C114 is 132 bytes and ends RET 8. The entire served
five-body dump and complete existing C++ bank were read. The other four bodies
already have clean owners. Existing provider, ABI, type, visibility and source
shape findings remain those in ../0x0001c090_register_callback.md.

The newly documented initialized-local-numbering lever was tested with k=0..128
`int unusedN = 0;` locals at entry, using ordinary tools/explain_mismatch.py on
129 distinct scratch sources. Every trial succeeds as a diagnostic but emits
the same 132-byte body and relocations. All retain the same stderr ECX/EDX
temporary discrepancy, first differing byte +0x66. No exact body or improved
bank resulted; the stronger existing bank is unchanged. No production edit,
pin or verifier change was made. results.json contains the input hash and
body/relocation equality proof; measure.py.txt replays the isolated trials.

Full-header follow-up: all 408 lines of the real STLport _ios_base.h and the
147B grow-array provider were reviewed. Six isolated full-header builds use
the real ios_base class, native field types, actual stdio header and callback
pair, with Ob0/1/2 and default-plus-field or value construction. Ob1/2
still emit132B with unchanged first66 ECX/EDX residue; Ob0 emits an
unresolved real pair-constructor call and is not a match. No full-header
context improvement. full-header-results.json and full-header.py.txt retain
the replay and measurements; the original stronger bank stays unchanged.

## Real pair return: isolated exact candidate

The full-header check exposed the remaining ABI representation issue. Returning
the genuine non-POD pair<Callback *,unsigned> from the grow helper introduces
the native hidden output argument through C++ itself. Six Ob1/Ob2 controls,
using direct construction, a named result or branch-local results, all produce
the complete147B native helper. Each caller is132B with every patched byte
exact once its actual helper is diagnostically bound to the proven1BEC0 target.
No pin or ledger mutation was used for that experiment. This is an isolated
candidate until ordinary add_match admission and the normal gates pass.

The proper iword/pword home was read and reconstructed in scratch with the real
vendored ios_base definition. ios-home-full.cpp.txt emits all four bodies
exactly: iword117, pword117, grow147 and register_callback132. The helper's
entire raw code and every relocation equal the existing explicit-output
Callback grow owner; no extra instruction or extent is masked. The helper-only
stage explicitly instantiates the real pair version and retains both117B
siblings exactly, allowing the helper alias and public callback to be banked
as separate commits. The helper spelling is inherited from the existing
recovery; native evidence proves purpose and ABI, not its original spelling.

ios-home-proof.json records those checks. The body is real C++ with actual
vendor types, no dead padding, barriers, volatile or emitted bytes. The old
0.977 bank remains until normal admission replaces the generated dump row.
The ongoing paired BFME1 comparison must finish before editing Code/ so both
reference revisions are judged at the same BFME2 source/ledger state.

The retained full/helper candidates use `T zero=T()` to make value
initialization explicit; this retains every raw byte and relocation in the
147B helper and leaves all four native bodies exact. The old explicit-output
bank is retained separately so the negative controls remain reproducible
after add_match eventually removes its attempts/ stash.

## Normal admission

The real grow instantiation was admitted with add_match --icf-owner and its
complete fold proof, then committed separately. The public callback was
admitted with add_match --replace-rva0x0001C090. It replaces the generated ASM
row with real C++ in the existing iword/pword home; the orphaned ASM PROC was
left unchanged. The obsolete0.977 attempts/ bank was cleared by add_match;
its historical source remains in old-explicit-output.cpp.txt.

The final whole unit passes ordinary build.sh4/4, every definition is rowed,
all three literals and seven imports verify, and its EH check reports no EH
data or missing objects. The source links in the published-census preview
(232->510 non-padding bytes); no full-game census or runtime was run. A
placement rescan at min5 finds zero extra bodies and pins. admission.json
records actual source/log hashes and the132 unique C++-byte conversion.

For diagnostic replay from the repository root, copy ios-home-full.cpp.txt to
build/resume-eh-local/turn60-stlport-ios-home.cpp and ios-home-helper.cpp.txt to
build/resume-eh-local/turn60-ios-helper-only.cpp. Compile each through ordinary
tools/explain_mismatch.py using the iword name, RVA0x1BF90 and size117, then run
audit-home.py.txt with Python. It only checks scoped objects with an in-memory
diagnostic binding; ordinary admission and the normal hooks remain authoritative.
