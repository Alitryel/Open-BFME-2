# Wall canMake: cleanup visibility and type controls

Target `?canMake@AIBuildableWallSegment@@UAEHPAVPlayer@@@Z`,
0x00596E15..0x00596EEF, 218 bytes including RET4. WB 0x015386C0 names
the method. Current owner, complete bank, all earlier log records and both
tracked October 19 handoffs were read. Production source and the existing
bank remain unchanged.

The corrected baseline, with its unused dead AsciiString dummy and `register`
zero removed and current failBuild spelling, reproduces 204 bytes. Its prefix
through the saved quote Boolean agrees, apart from the displaced early exit.
The residue remains the success/failure destructor merge: failure results
occupy EBX, sharing the constructor's zero; retail uses ESI on failure and a
separate success destructor followed by XOR EAX,EAX. Unpatched object bytes
and align_diff confirm this; explain_mismatch's positional relocation patching
after size divergence is not evidence for target operands in the tail.

New independent controls:

- Actual owned 26-byte Rva0039205C destructor body, including the real 28-byte
  element stride and delete[] operation, made visible with noinline, ordinary
  out-of-class definition, or forceinline. No new external dependency was
  invented. No-inline/ordinary settings remain 204 bytes. Ob2 and inline
  budgets 40/100/200 either leave it unchanged or inline the cleanup and grow
  to 242/299 bytes. The Elven Wood inlining-budget result does not transfer.
- Boolean flag fields, enum status and enum return controls, independently
  combined with the real opt-in Coord3D constructor/destructor header: all
  sixteen remain 204 bytes. Enum-return variants change the base method's
  mangling and leave that call unresolved; they are diagnostics, not proposed
  target identities or new pin candidates. No complete enum ABI is claimed.
- EHs, GX, EHa and EHsc- stay 204 bytes. Diagnostic nothrow/throw() on the
  quote destructor instead give 191 bytes and remove needed EH behavior.
  The real destruction chain reaches StringBase cleanup/lock acquisition;
  no new nonthrowing contract was established or applied to production.
- Quote construction in WB statement order, declaration order, or a member
  initializer list stays 204 bytes. The previously tried branch/scope spellings
  were not rerun.

These controls refute the concrete visibility, type, construction-order and
exception-setting explanations tested here. The old bank is preserved; this
is blocked work, not new C++ coverage. Replay drivers are the three sibling
wall-canmake-*-20261020.py.txt files. Full normal explain_mismatch outputs,
raw-byte inspection and align_diff are in build/wall-canmake-closure-oct20/.
BFME2 base 4b7d918216 plus the unchanged score-comparator notes commit;
BFME1 verified pointer 92f6bbe8e1dcdb46b5d27da0674313efc822b790.
O1/G7/SSE/MD/EHsc, MSVC 7.1; gpt-6.1-sol, about 8 minutes.
