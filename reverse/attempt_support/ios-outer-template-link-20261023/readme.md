# IOS imbue member-template declaration trial

At d4fa46f19a, index b711de3634 (retail-truth-4), the current narrow/wide
imbue cohort has one conflicting public mutable-char assign-dispatch and
links 0/563 nonpadding bytes. Prior full-specialization declarations ICE.

The attached outer-class-only specialization retains an iterator template
parameter, following the successful MultiByteToWideCharSingleLine repair.
This compiles without C1001, but the ordinary assign wrapper now stores the
empty tag byte and changes temporary homes. A second trial calls dispatch
with a default-initialized named tag, removing the store and restoring the
238-byte extent, but four LEA displacements still exchange EBP/ESP homes:
old-locale and buffer temporary slots no longer coincide with retail. This
also removes four rowed helpers (capacity, distance, max, char_traits assign).
The native grouping assignment call itself still resolves to 120F0.

Neither trial passed the byte gate; neither is retained in Code. Original
sources restored and the combined normal build passes 11/11, strings, floats
and imports. Legacy baseline has zero session gain; no strict or closed-strict
gain claimed. A future attempt needs a byte-safe temporary-lifetime solution
and relocation of genuinely emitted rowed helpers, rather than repeating the
full-specialization declaration that ICEs. Compiler flags and dependencies
unchanged. Trial patch is diagnostic only. t=8 model=gpt-6.1-sol.
