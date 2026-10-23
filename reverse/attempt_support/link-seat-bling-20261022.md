# Hero bling predicate binding, 2026-10-22

Inputs: BFME2 parent 12f02ac7cb; published link index 08160bc2c9,
2026-10-22 17:08; verified BFME1 pointer 37c3022de1. Upstream donor
3cef00d2 was reviewed read-only; another seat owns its pointer update.

ConstructHeroBlingList called the pinned but undefined private spelling
CreateAHeroAward::rva0040AA27. The owning 76-byte row in Common/Rva0040AA27.cpp
is int Rva0040AA27::rva0040AA27(int): retail's array predicate receives the hero
context as one word and returns 0 or 1. Bind that owner explicitly and preserve
the caller's low-byte test. The opaque owner/context spelling is retained;
no new class identity, pin, alias or data-layout claim is introduced.

Acceptance:
- find_declared_unmatched: all definitions matched.
- ./build.sh Code/GameEngine/Source/GameLogic/Object/CreateAHeroHeroBlingList.cpp:
  3/3 rows exact, including parent EH and renumbered unwind label.
- link_check.py on that unit plus Common/Rva004079D5.cpp and
  Common/Rva0040AA27.cpp: before 248 B linked (builder 0), after 713 B
  (builder 465). The same current providers were used on both sides.
- --prepare-current on those three providers: strict reusable receipts,
  all 7/7 rows and reference gates pass. This is self verification;
  +465 B is a legacy current-object preview, not closed-strict evidence.

The original lookup spelling is already supplied by the unchanged
Rva004079D5.cpp provider's existing alias. Its 31-byte gain relative to the
old index is inherited and excluded from this repair's credit.

Cause sweep: CreateAHeroHero.cpp is the only other source using the old award
predicate spelling. Current four-provider preview leaves that unit at 0/5256 B:
its element destructor, uint/bool RB-tree destructor, map operator[] and
rva00407C6B definitions also block it. No change was made to that unit.
