# Separate the UTF16 word-buffer and signed-remap families

This repairs the constructor ownership and two conflicting pins that blocked
the shader's signed-short empty vector constructor. It adds no unique retail
coverage. Input master: `1c014bb0f2`; verified BFME 1 reference remains
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`.

## Target facts and source views

The complete native filename consumer 513ED1 is 415 bytes. Its two-byte buffer
is copied from UnicodeString storage, filtered through an unsigned-short API
and passed to the unsigned-short UnicodeString setter. Its count constructor
513DD0 (51 B) calls base 513D55 (58 B) and fill AD8C9 (34 B). The base calls
proxy 7410 (11 B) and allocator 17710 (29 B). These edges were read from the
native displacements, not inferred merely from matching element widths.

Shader Init's signed remap is a different chain: its empty constructor 211E58
(29 B) calls proxy 14F3C4 (11 B), and the signed allocator already owned at
AD722 is 27 B. The two proxies have identical instructions but distinct
addresses. Their address identity must remain separate.

The original scalar spelling of the filename buffer remains uncertain.
`unsigned short` is the STLport storage view whose complete current consumer,
constructors and already established word allocator/fill providers reproduce
this target family. This does not claim independent source evidence that the
original author wrote that spelling instead of a compatible wide-character
type. The standard template names describe actual compiled instantiations;
no new application class or private allocator identity is invented.

## New control and repair

Earlier nominal/custom allocator controls are documented in
`fxinit-utf16-family-20261020/readme.md`. This pass first tested the actual
native `__wchar_t` type and `/Zc:wchar_t`: both change the consumer to 412 B
and fail an existing unwind funclet. They are rejected. A simple standard
`vector<unsigned short>` control preserves all 415 bytes except its unresolved
count-constructor edge; all other 17 consumer-unit rows stay exact.

The existing canonical unsigned-word unit emits the exact 58-byte base with
both native callees already resolved. Its 51-byte count constructor has the
native fill edge and only needs that base owner. Therefore this repair:

- Reassigns the old signed count/base rows at 513DD0/513D55 to their actual
  compiled unsigned-word instantiations in `stlport_vector_word_o1.cpp`.
- Changes only the filename's buffer element view to unsigned short; no
  allocator wrapper, extra operation or lifetime padding is needed.
- Deletes the signed allocator's false 17710 pin, retaining its real AD722
  owner, and deletes the signed proxy's false 7410 pin.
- Admits the signed proxy at 14F3C4 through ordinary recursive fold proof in
  `pin_admission.py --add`, using the complete emitted 11-byte body.
- Rows the real signed empty constructor at 211E58 with `add_match` against
  the existing int-vector ICF owner. Its whole 29 bytes and proxy relocation
  are exact. This is a shared existing body, not new recovered coverage.

The first coordinated byte gate passes **31/31** affected rows; the signed
empty-constructor admission passes **7/7** in that unit. Pin consistency
passes with no new multi-address conflict. The pin admission tool records its
checked grant in `reverse/hatch_baseline.tsv`; the commit trailer explains
that generated baseline update. No verifier code or refusal rule is changed.

All exploratory sources, native edge listings, full constructor disassembly,
rejected controls, backups and gate logs live under the ignored
`build/utf16-native-wchar-oct20/`. Production rows were rewritten with
terminator-preserving ledger helpers; all unrelated records retain their raw
bytes. Normal hooks remain enabled.
