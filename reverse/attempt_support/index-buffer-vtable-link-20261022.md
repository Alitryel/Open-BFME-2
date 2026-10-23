Index-buffer emitter views, 2026-10-22
====================================

At HEAD 35ae27ea90, census 08160bc2c9 (2026-10-22 17:08), current
FamilyDeletingDtorsO2.cpp linked 251 B and dx8indexbuffer.cpp linked 0/2391 B.
The latter's only blockers were the two index-buffer vtables: the family
emitter declared each class with just a virtual destructor.

Target destructor vptr stores identify tables VA BD2EF4 and BD2EFC. Both
start with VA 46CE57 (RefCountClass::Delete_This), followed by their deleting
destructor, VA 539200 or 539220. The donor refcount/index-buffer declarations
independently give the same inherited slot order. This is target slot evidence;
the donor supplies the class relationship already used by dx8indexbuffer.cpp.

Declare that base relationship in the family emitter, with an out-of-line
base constructor declaration. Without that declaration MSVC synthesizes a
wrong RefCountClass constructor and deleting destructor. No source row, pin,
alias or matched body changes. Both emitted tables are now 8 bytes, with
identical relocation names and offsets in the provider and consumer.

Acceptance: build.sh passes 43/43 rows across the pair; literal/import checks
pass. find_declared_unmatched accepts the edited family unit. The same pair
passes --prepare-current with strict reusable receipts (self-strict only).
Legacy link_check before 251 B, after 2642 B: +2391 B newly linked. No
closed-strict or link.exe measurement was run or claimed.
