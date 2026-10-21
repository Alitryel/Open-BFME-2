# Asset collector link attempt, 2026-10-21

Input: BFME2 7c06faa3fc; BFME1 verified pointer 68c5ce27; MSVC 7.1
`/O1 /Oy- /G7 /arch:SSE /MD /EHsc`, retail-insert layout. Baseline and
restored source pass both rows (542B collector and 10B EH handler) and the
literal check. Legacy published-census preview at 2b4d1fb42a holds 552B for
iterator-base equality and AsciiString set `_M_find`; no gain claimed.

The collector calls `_M_find` out of line (relocation +323); the existing
pin resolves it to 0x1F8437. An exact-traits node-equality overload is the
established sibling recipe. Adding a declaration-only member-template
specialization for `_M_find` with two `template<>` headers crashes MSVC
C1001 at vendor/stlport/stl/_tree.h:482, including through a typedef (the
syntax used by AiOrdersManager). One template header is rejected C2910 / C1506.
Three compiler failures; source restored and claim released. The saved
candidate is diagnostic, never a compiled source. Next work needs a supported
way to declare this private member template without the compiler ICE, or an
independent search-provider repair; do not repeat the declaration variants.

Scratch diagnostics: build/seat-collect-{before-byte,before-link,trial1-byte,
trial2-byte,trial3-byte,restored-byte}.txt. No pin, baseline or tool edits.
