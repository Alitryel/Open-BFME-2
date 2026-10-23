# STLport factory link repair, 2026-10-18

At BFME2 094c6ea08b, the paired legacy preview newly links 4,139 existing retail bytes in stlport_create_filebuf.cpp. The stdio provider maps four additional row bytes at an already owned ICF address; unique authored C++ coverage grows by zero. No closed-strict gain is claimed.

Target identity for stdio_ostreambuf::showmanyc is RTTI class identity at vtable RVA 0x7BBCA8 and slot 5 pointing to the entire four-byte return-minus-one body at 0x13B5E0. That slot index comes from the existing STLport class contract. STLport 4.5.3 and BFME1 64d369b9 stdio_streambuf_setbuf.cpp supply return-minus-one semantics. The existing narrow streambuf underflow owns the same physical body. No new pin or separate address was introduced.

Declare wide filebuf close, destructor and buffer allocation specializations instead of emitting competing copies. Their rowed providers remain unchanged. The proof compares before/after objects against the same c2c5ac8c27 index and current providers: every retained COMDAT digest is unchanged, the factory loses its blockers, and provider findings are unchanged. The provider addition changes only the four-byte showmanyc definition. Factory 25/25 and stdio 12/12 rows pass the normal full-byte gates. Frozen-file and CSV checks pass.

Strict preparation of the factory is refused because its macro/parent-traversing includes have no strict reusable dependency inventory. This is a receipt limitation, not a closed-strict or self-strict success. Normal scoped byte verification and the explicitly paired legacy result are the acceptance evidence.

The stdio provider alone passes strict reusable receipt preparation and its 12/12 byte gate. That command does not check closure or update the census; it does not establish a closed-strict gain for the factory.

## Reference freshness and donor repair review

Fetched official BFME1 master 5518b5bd81bf3d12665178044e9be98dc0850df9; previous verified pointer was 64d369b90170b7e9ec917d646f020b11f13eb0d5. The clean reference checkout was preserved and both revisions received a complete full byte gate at fixed BFME2 094c6ea08b. Both verify 96,630 function rows and 896 data rows. Both fail only the pre-existing DIR32 inconsistency: Rva0007DF07 vtable is used at BC6F20 and C7A630 by three button constructors. Those files and the shared provider are foreign claimed. Retained the previous pointer, released the reference claim, recorded the blocker, and did not write a success stamp.

The existing layout resolver maps WWLib to game/Libraries/Source/WWVegas/WWLib, ZH WW3D2 to inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2, and psplayerstats to inputs/reference/shims/psplayerstats. All three directories and vector.h, static_sort_list.h and PersistentStorageThread.h were checked physically, rather than relying on MSVC ignoring missing includes. The only changed dependency header is the PSRequest copy-constructor declaration.

Reviewed donor repairs through 5518b5bd: 06a23066 UnicodeString destructor convergence, 3a377aac PSRequest copy declaration, e1bf2108 ModelConditionFlags emitter suppression, 4f7c322c AI createGroup suppression, and 5518b5bd getFinalOverride recursion. Their provider-binding principle applies to the factory repair; no target layout, identity or body was inferred from a donor linking result. PSRequest header update remains blocked with freshness; the other named families do not remove a current sole blocker in the inspected queue.

## Independent vector trial handed back

VectorClass<Vector3> constructor 0xF0D2F has a five-slot table due to its nonvirtual destructor workaround. Declaring it virtual fixes the table but emits a 28-byte deleting destructor instead of the kept 71-byte copy. Including reference vector.h retains all four byte-exact rows but emits Clear 37 versus 39 bytes and deleting destructor 34 versus 71. Restored the source after two failed link trials, recorded evidence and released all five claims. Compiler/inlining reconciliation remains prerequisite; no link gain is counted.

Read-only triage also confirmed stale entries: current StaticSortListClass tables are identical (e4008abdb4d7), and current Rva003A393A constructor is retail (87d4b1c0c954). Those are not new repairs. name_globals dry-run kept zero rewrites; rehome_rows could not rank because the published census.log is missing. No census or full link runner was started.
