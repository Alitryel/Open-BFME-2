AsciiString list erase provider repair, 2026-10-18

Same-index ordinary legacy link_check: 0/3 clean, 0 bytes before;
2/3 clean, 308 nonpadding bytes after. Newly clean units are
stlport_list_asciistring_insert.cpp (222 B) and
stlport_list_asciistring_remove.cpp (86 B). GameSpyLoginPreferences.cpp
retains its independent tree/helper conflicts; its bytes are excluded.
No closed-strict link closure gain is claimed.

The index identifies exactly one wrong list<AsciiString>::erase(iterator)
COMDAT, in GameSpyLoginPreferences.cpp. The insert/remove units already emit
retail copies, with the existing compiler-symbol binding at RVA 0x000BC67A.
Declare that specialization alongside the existing create_node declaration
so preferences calls the verified provider rather than emitting its own.
No new pin, alias, class layout, throwing contract, or row is introduced.
This applies the established provider-binding technique directly; the BFME1
verified donor pointer 64d369b90170 remains unchanged.

./build.sh: all 62/62 rows across the three units exact, including native EH
relationships; 39 string refs and four imports pass. link_check.py
--prepare-current: same 62/62 exact with strict reusable receipts, explicitly
without a closure check. Source declaration guard passes. Paired preview
index 1a1c90e405 / census c2c5ac8c27 is unchanged. No full census or link cycle.
Logs: build/seat-asciilist-{before,after,gate,cohort-gate,strict}.log.

Independent iterator trial was reverted: extern-template member suppression
before locale still prevents required inlining and fails four of twenty rows.
Restored twenty-row gate passes; blocker recorded separately in re_attempts.
