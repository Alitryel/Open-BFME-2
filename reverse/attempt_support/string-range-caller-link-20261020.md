# Range insertion caller link repair

Base d970ad83b1; published census 3f413ed3ff (2026-10-20 18:52).
The old BfmeStrV44::bfmeImplV44 pin targets 0x00028820. That whole
740-byte body is now recovered as Rva008314E0String::insertRange, guided
by BFME 1 92f6bbe8e1dcdb46b5d27da0674313efc822b790. The caller's native
arguments independently show three pointers and an address of its empty
iterator-category tag. Change only the declaration and assembly call name
to the existing provider. No bytes, aliases, pins or hatches are added.

Before, current-object legacy preview links 0 bytes; the old spelling is
the sole unresolved name. After, the same caller/provider preview links
the caller's 282 census bytes. The current function row verifies all 285
bytes (the census has older extent accounting). Normal byte gate 1/1,
string/float/import reference checks and find_declared_unmatched pass.
link_check --prepare-current also passes the caller's strict reusable
receipt gate. The only occurrence of the old call spelling was this caller.

This is a legacy preview improvement with self-strict caller evidence,
not closed-strict closure. The provider retains its separate unresolved
Rva0069E440Destroy and non-retail erase, replaceBase and mutable-copy
COMDAT blockers. Those need their own compiler-context/identity repairs.

Other insertion callers at 0x000297D0 and 0x0002A140 were inspected but
left unchanged: their newly recovered 0x00029530 provider is absent from
this census, so link_check cannot measure a repair. Both blocked notes
are in re_attempts.log, and their claims are released.
