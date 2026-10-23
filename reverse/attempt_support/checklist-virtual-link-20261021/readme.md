# Checklist destructor ABI reconciliation

Native ctor 0x0057AA45 sets table VA 0x00C6F098; its slot 0 calls the
28-byte deleting destructor 0x0057AAD5, which directly calls 0x0057A4E7.
The ctor's existing class declaration and actual emitted virtual scalar destructor
establish the virtual relationship independently of a byte placement.
The destructor's former member view incorrectly spelled that destructor QAE.
Application class identity remains address-derived; no donor class name is inferred.

The corrected destructor uses a polymorphic 8-byte base and string at +8.
The native destructor resets neither vptr; novtable makes those stores agree.
Existing base destructor UAE pin resolves 0x0022167C. No new pin or data owner.
The exit callback makes a qualified virtual-destructor call to retain the direct
native tail jump. The constructor already emits the correct virtual deleting
copy, so the separate nonvirtual delete-anchor unit is removed and its row moved.
The compiler's actual native-graph cleanup label replaces a legacy object-symbol
alias. No new coverage or retail extent is claimed.

Acceptance at BFME2 ea3f923c5a with published legacy census 03035cf02c
(2026-10-20 22:09):

| Current-object legacy preview | Before | After |
| --- | ---: | ---: |
| destructor provider | 53 | 53 |
| constructor and scalar destructor | 0 | 182 |
| retired scalar-only unit | 28 | removed |
| exit callback family | 0 | 0 |
| Total | 81 | 235 |

Net **+154 existing nonpadding bytes**. The 28 moved bytes were linked already
and are subtracted. The exit unit retains the same unresolved GeometryContactSphere
in this census preview (a data-row provider exists in current Rva007B6610.cpp;
this is not evidence of a current closure failure). No closed-strict claim.
Self-strict bounded preparation: before 102/102 rows across 4 units; after 102/102
across 3. Ordinary destructor gate 3/3, all strings/floats/imports verified;
converged data check 0 second names; new-variants accepts all three consumers.
Frozen-source checks and check_csv pass.

Donor review: BFME1 pointer 68c5ce2789e974f36b6c742d57437d157bc159e9,
reviewed linking repair b0af542b78951e41043ada1f57d047f2ac5d370a: binding legacy
names to the existing rowed owner is applicable as a technique; that commit's
ILT names and addresses are inapplicable. This repair uses target constructor,
vtable, destructor and EH evidence, not a donor layout assumption.

Isolated exploratory virtual-view build first lacked the target /O1/G7/SSE flags
and emitted a 76-byte SEH shape. With the matched flags it is exactly 53 bytes;
the actual Code unit's normal region flags produce the same whole-body match.
No failed reconstruction remains under Code.
