# Apt owning-list member link repair

Base: 27dd681fd2; census: 456ce161c5 (2026-10-23 06:28).
BFME 1 donor revision reviewed: 96c88c73a; the opaque Apt member has no
supported same-name donor repair. This change uses target evidence only.

Rva005B5420Dtor.cpp previously declared its member at +0x1c as a map of
Rva0040A603Record. Its tree clear pin points at 0x0040a59b, whose rowed body
is an owning CreateAHeroData pointer-list clear, not a tree clear. The complete
56-byte destructor at 0x0040a603 and its EH graph are independently recovered
as Rva0040A530 in 0CreateAHeroManager21FE49.cpp (attempt-log entries 58484
and 60500). Its base holds three pointers and an ownership byte. Reuse that
existing class view and declared destructor; no new name, pin or layout is
inferred from a byte match. The unchanged native 101-byte Apt destructor and
its 10-byte EH handler bind this cleanup, while the unrelated 8-byte callback
also remains exact.

Paired link_check.py on the consumer and 0CreateAHeroManager21FE49.cpp:
before 430 -> 430 bytes (consumer 0/109, non-retail tree clear); after
430 -> 539 bytes (consumer 109/109). This is a legacy preview gain of 109 B,
not a closed-strict census measurement. The provider remains 430/430.
--prepare-current on both units passed all 26/26 rows and strict reusable
compiler receipts; normal consumer byte gate passed 3/3; literal, float and
import gates passed. find_declared_unmatched is clean.

Cause sweep: the only remaining consumers of Rva0040A603Record are
Rva0021FFEEDtor.cpp and StlSweepR3Rva0040A603.cpp. The former already links
485/485 paired with the real provider, so it was left unchanged. The latter
owns historical tree-named rows and needs separate identity reconciliation;
no aliases or further pins were introduced. No closed-strict gain is claimed.
