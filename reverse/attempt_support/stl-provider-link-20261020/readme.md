# STL provider binding repair, 2026-10-20

Inputs: BFME2 cec1ad5f20dfa4ef7e880fc74edd49a523680bc6; unchanged published
retail-truth-2 census 3f413ed3ff (2026-10-20 18:52). BFME1 donor revision
4483e88da1c2f3b9a273f779baac7458bd8bb891 was already reviewed for the shared
STL ownership lane; no donor input or layout changes here.

Two existing typed consumers unnecessarily instantiated generic helpers whose
outlines differ from their independently rowed retail providers. Declare the
provider specializations before instantiation, leaving native calls and inlined
consumer behavior intact. No new identities, pins, data, rows or layout claims.

* Rva002081C7Xfer.cpp: list insert now binds to the existing37B provider at
  0x0020746B (stlport_list_pair_nocase4_insert.cpp). The native240B transfer and
  10B EH handler remain exact. The only previous losing COMDAT was this insert.
* stlport_rb_tree_hint_002a57bd.cpp: use the existing34B node factory at
  0x002A1516 (stlport_rb_tree_hint_002a40c6.cpp). Its retail allocator and
  construction calls are independently rowed; the generic catch wrapper and
  allocator copies disappear. The124B map subscript and10B handler remain exact.
  StlportMapSubscriptFamily.cpp already uses the same declarations for its three
  mapped types; no further change is required. Original mapped names remain
  structural views, as documented by the existing provider.

Acceptance: paired explicit link_check.py runs against the same frozen index
change the two consumers from0/384B to384/384B in the legacy prediction. The
provider/consumer pairs also link together. This is a legacy predicted gain,
with current self-strict byte receipts, not a measured closed-strict link cycle.
No full linker, census, nightly or boot runner was started. Authored C++ coverage
is unchanged. --prepare-current passes4/4 byte rows and all reference gates;
separate build.sh passes1/1 list-provider and6/6 tree-provider rows; eh_verify
reports EXACT1/1 for each consumer, with no baseline exceptions.

Reproduction (explicit paths below shortened to their basenames):

* link_check.py --prepare-current Rva002081C7Xfer.cpp stlport_rb_tree_hint_002a57bd.cpp
* link_check.py <consumer> <corresponding provider>
* ./build.sh <corresponding provider>
* eh_verify.py <consumer>

Exact bounded link results from before and after follow.

## seat-xfer-before.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/ScriptEngine/Rva002081C7Xfer.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 250)
  comdat      ?insert@?$list@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@_STL@@QAE?AU?$_List_iterator@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@_STL@@@2@@2@U32@ABU?$pair@$$CBVAsciiString@@UNoCaseTreeValue4@@@2@@Z  (retail: not retail's body)
link_check: 0 of 1 link cleanly; LINKED 0 -> 0 bytes (3.4s)
```

## seat-xfer-pair-after.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/GameEngine/Source/GameLogic/ScriptEngine/Rva002081C7Xfer.cpp: LINKS  LINKED 0 -> 250 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 250)
Code/Libraries/Source/WWVegas/WWLib/stlport_list_pair_nocase4_insert.cpp: LINKS  LINKED 37 -> 37 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 37)
link_check: 2 of 2 link cleanly; LINKED 37 -> 287 bytes (3.8s)
```

## seat-map-before.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_hint_002a57bd.cpp: does not link  LINKED 0 -> 0 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 134)
  comdat      ?allocate@?$allocator@U?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@_STL@@@_STL@@QBEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@2@IPBX@Z  (first: differs from the first copy in link order (no retail address))
  comdat      ?_M_create_node@?$_Rb_tree@VAsciiString@@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@U?$_Select1st@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@3@U?$less@VAsciiString@@@3@V?$allocator@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@3@@_STL@@IAEPAU?$_Rb_tree_node@U?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@_STL@@@2@ABU?$pair@$$CBVAsciiString@@UTreeHintPayload002A1D9D@@@2@@Z  (retail: not retail's body)
link_check: 0 of 1 link cleanly; LINKED 0 -> 0 bytes (3.4s)
```

## seat-map-pair-after.txt

```text
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Compile: 0 of 1 TU(s) (deps-cache: 1 current)
Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_hint_002a57bd.cpp: LINKS  LINKED 0 -> 134 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 134)
Code/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_hint_002a40c6.cpp: LINKS  LINKED 850 -> 850 bytes (census 2026-10-20 18:52 at 3f413ed3ff; file's own bytes 850)
link_check: 2 of 2 link cleanly; LINKED 850 -> 984 bytes (4.3s)
```
