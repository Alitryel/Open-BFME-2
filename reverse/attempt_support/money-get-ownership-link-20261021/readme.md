# Narrow money-get ownership repair, 2026-10-21

Instantiate only the existing rowed long-double overload instead of the whole
money_get<char> class. Whole-class instantiation also emitted a constructor and
vtable that referenced the separate string-parser provider. The matched overload
uses virtual dispatch and has no relocation to that parser; the unrelated vtable
was its sole legacy link blocker. Parser semantics, ABI and flags are unchanged.

The complete 277-byte row passes the byte, relocation, string, float and import
gates with a self-strict reusable receipt. All 556 retained COMDAT digests are
identical, with no COMDAT added. proof.json records object/index hashes, removed
names and paired blockers for seven related current objects. Against the same
published index the cohort changes 0 -> 1 linked units, exactly +277 nonpadding
matched bytes. The six peers retain independent blockers. In particular, the
wide long-double unit owns a matched constructor and must retain its vtable;
this narrowing alone cannot fix it. No closed-strict or runtime gain is claimed.
Frozen-file and new-variant checks pass; no pin, identity, extent or layout edit.

Donor review reuses the unchanged BFME1
5987fd1b859e86801d093256eadc6fb63d87785f ownership review in
../link-seat-20261021/readme.md. No donor addresses or layouts are transferred.

The E16 deque prerequisite audit recorded with this repair is blocked on wrong
map-initializer and iterator-subtract providers; suppressing unused methods
cannot repair those actual calls. No source edit or claim was made for it.
