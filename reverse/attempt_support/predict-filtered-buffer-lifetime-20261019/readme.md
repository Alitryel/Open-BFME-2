# Predictor buffer and motion lifetime follow-up

Approved clean-room spec reverse/vp6_cleanroom/specs/001c5e30.md and complete
retail 001C5E30..001C6130 (768 bytes) only, together with this repository.
The entire current bank, every RVA attempt and linked semantic-repair handoff
were read first; body reservation was pushed before trials. No decoder source
was read. Inputs are BFME2 6fb7a42ec1d54c2c7bb074a16772909d7c0757c9 and verified
BFME1 6b9d92bf92debd03e4357462bab41f701651e67c; original /O2 /G6 /DNDEBUG /MD.

Native filtered setup loads its working buffer into ESI before motion loads,
uses EBP for the block index, and separately preserves the raw short Y and its
promoted integer magnitude. Test genuine earlier buffer/setup lifetimes and
later Y promotion. The five initial trials cover three independent buffer
orders plus motion value/reference representations; six follow-ups separate
short-Y phase use from promoted-Y magnitude use. hypotheses.md records each
reason before its trial. All twelve sources (baseline plus eleven trials) were
compiled through normal explain_mismatch with unique source/cache paths.

Baseline remains 769 bytes, nine mnemonic-alignment structural regions,
16 nonrelocation memory and ten register operand differences. Early base is
769 bytes/eight regions/17 memory/eight register. Early base with Y promotion
after phase is 773 bytes/seven regions/14 memory/eight register. The local
extent-fenced aligner credits 638,644,655 bytes respectively of the true768;
it ignores branch/relocation noise, and is diagnostic, not the byte gate or
the older bank's scoring system. One value-copy variant regresses to a larger
stack frame; references and buffer-before-phase are unchanged. The other Y
variants are 761..778 bytes. No exact match.

The earlier base assignment restores the native ESI buffer load. It still
assigns the filtered block index to EBX rather than EBP. The Y-promotion variant
also restores the mask reload to ECX, but changes load/store scheduling and
keeps different short/int stack homes. Unfiltered setup and dispatch residue
remain too. The original complete769-byte bank is preserved: the773-byte
alternative is not uniformly stronger. Both useful alternatives are patches
against that bank; no failed reconstruction is left in Code/.

The existing independent retail dispatch oracle passes all1238 cases for BOTH
alternatives: callback arguments, decoder instance, cdecl stack and saved
registers. It covers all256 threshold bytes, vector signs, profile/mode/variance
boundaries and a builder mutating motion vectors. Pixel callees remain stubbed;
no pixel-decoding equivalence, new matched bytes or linking gain is claimed.
The reports include source/native/compiled hashes. Unicorn2.1.4 is the existing
build/resume-oct18-emulator-deps installation; no gate or oracle was changed.

The patches use zero context to preserve source tabs without patch-context
whitespace warnings. Copy the unchanged bank into an isolated build directory
as baseline.cpp, then run git -C that-directory apply --no-index --unidiff-zero
with the absolute patch path. patch-replay.json proves that both patches replay
the exact compiled candidate bytes without editing the bank. Then run the standard
explain_mismatch command with the existing mangled name, --rva 0x001C5E30,
--size 768 and --source pointing at the isolated candidate. Run the tracked
predict-filtered-bank-repair-20261018/oracle.py with that source as its argument.
Compiler scripts, raw complete diffs and metrics remain under
build/predict-buffer-lifetime-oct19. Further unchanged store/declaration sweeps
are not justified by this result; seek a new supported allocation explanation.
No game source, ledger row, pin, alias, barrier or verifier change. t=8min,
model=gpt-6.1-sol.
