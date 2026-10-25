# Narrow-string selective emission

Inputs: BFME 2 babe21fbc5; BFME 1 donor 0bf534ea7ccde110c456edb9cd2dd5dae823c953; published retail-truth-4 index aa9aee26b4 (2026-10-25 06:47). Existing TU flags are unchanged.

The previous bank `narrow-string-link-20261025/readme.md` established that selective instantiation preserves six of the eight remaining rows; whole-class instantiation additionally emits incorrect `_M_compare` and `insert<char*>` copies. This attempt retains the two missing `char_traits<char>` static members by taking their addresses in a compiler-emission anchor. The donor header defines them as memcmp/memset wrappers; their unchanged compiled bodies match the existing target rows at 0x6F10 (28 B) and 0x1C680 (50 B). The anchor has no claimed retail identity and is marked absent-from-retail. No helper pin or class-layout identity is added.

The explicit rbegin/rend, mutable append, pointer swap and const reverse-iterator comparison instantiations preserve the other six rows. The existing explicit wide allocator-base constructor remains present for its fold proof. No declaration-only member-template trial or compiler workaround is repeated.

Acceptance:

- Before: current `link_check.py stlport_narrow_string.cpp` does not link, 0/396 B, with the two unwanted helpers as COMDAT and selected-definition blockers.
- After: the same preview LINKS 396/396 B; one unreferenced const-char copy diagnostic remains and is not a blocker.
- Normal `build.sh`: 8/8 rows exact, import/string/float checks pass.
- `link_check.py --prepare-current`: normal byte gate and strict reusable provider receipt pass. This is self-strict evidence, not closed-strict link closure.
- `find_declared_unmatched.py`: passes, with the one explicit absent-from-retail anchor.
- New-variant admission passes.

Measured improvement: +396 authored bytes linked in the bounded legacy preview, with zero new unique retail bytes. No census, full link cycle, nightly or runtime measurement was run. Published census status is unchanged. The indexed blocking-name sweep finds no other unit blocked on either removed copy.
