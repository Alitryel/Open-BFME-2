# Vector 001504A1 provider binding, 2026-10-21

Parent 45f75f73b4; published census e20daa4e78, 2026-10-21 21:42.
The source already recovers the STLport4.5.3 overflow and two non-trivial
uninitialized helpers for an opaque 76-byte record. No application identity
or new class-layout claim is made by this repair.

Native REL32 edges independently establish:
- 001504F7, 0014F9F5 and 0014F687 call 0014F647, the rowed placement-copy
  owner _Construct<Rva0014F647Element> in StlportConstructFamilyW3G15.cpp.
- 0015053A calls 0014F8C6, the rowed Rva0014F8C6::rva0014F8C6 cleanup in
  Rva0014F3E7Destroy.cpp. This performs range destruction through the native
  virtual slot and frees storage. Instantiating the opaque record vector's
  own cleanup instead emitted unresolved static destructor references.

Forward the two template dependencies to these established providers. Keep
all three authored bodies, their boundaries, flags and layout unchanged.
No new pins, aliases, generated code or unmatched annotations.

Acceptance: link_check.py before 0/258 B, after **258/258 B legacy preview**;
./build.sh and --prepare-current 3/3 rows exact, literal/import checks pass,
strict reusable source receipt. find_declared_unmatched.py passes. All three
emitted bodies' native REL32 edges were decoded again after the change.
Closed-strict closure remains unmeasured, not claimed.

Same-cause sweep: Rva00150959Insert.cpp is the only other source using this
opaque vector. It still has an unprovided copy constructor Rva0014F699 at
0014F4E3 and an imported allocator, plus its own competing Construct/clear.
No change or linked-byte credit is taken for that consumer. The rowed
placement provider's pinned element copy is distinct from the consumer's
unprovided real thiscall name; resolving it needs independent code recovery
or a proven identity repair. The 258-byte unit's native body is unchanged.
