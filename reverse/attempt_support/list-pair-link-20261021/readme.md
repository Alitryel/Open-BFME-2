List-pair destructor binding sweep
=================================

Inputs: BFME2 e78bfb197c, published census c7845fd6e7 (2026-10-21
15:41), BFME1 00c2ffbb23e9154fbe9970954afacb04e4943dd7, existing MSVC
7.1/STLport flags unchanged.

The three list-valued AsciiString tree units lost their implicit pair
cleanup COMDAT against the kept copy. The established row 0x005C9ED3
belongs to GameSpyLoginPreferences.cpp; native tree erase and subscript
calls already target that address. No new class identity or target layout
is inferred here: the existing STLport pair specialization keeps its const
AsciiString key followed by list<AsciiString>, and the construct unit keeps
the same memberwise two-value constructor.

A member-only destructor specialization declaration passed the byte gate
but MSVC still emitted the implicit destructor and linked zero bytes.
Declaring the destructor in an explicit class specialization suppresses
that copy. This uses the native cleanup provider without an alias, pin,
import wrapper or compiler-setting change.

Paired explicit link_check.py against the same frozen index:

- stlport_string_list_pair_cleanup.cpp: 0 -> 53 B
- stlport_string_list_pair_construct.cpp: 0 -> 216 B
- stlport_string_list_tree_erase.cpp: 0 -> 127 B
- Total: 0 -> 396 B, all three units LINKS.

./build.sh: 8/8 rows exact, string/float/import checks pass.
eh_verify.py: 2 EH graphs EXACT, no baseline or missing object.
find_declared_unmatched.py: all definitions matched.
link_check.py --prepare-current: strict reusable receipts and normal byte
gates pass for all touched units. Link gains above are legacy frozen-index
predictions, not a measured closed-strict link cycle.

Independent blocked candidate: StlSweepR3Rva00289FBC.cpp's native element
assignment call at 0x289FEE reaches rowed 0x289902. Two forceinline bridges
(return *this and return the cast callee result) both kept the 115B length
but changed EBX/EDI allocation and push/add ordering; an emitted bridge
also conflicts with the old operator= pin. Source restored, claim released,
blocked verdict recorded. No failed C++ reconstruction retained in Code/.
