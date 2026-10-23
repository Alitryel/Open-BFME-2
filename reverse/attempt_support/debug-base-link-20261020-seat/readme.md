# Debug abstract-base emission repair: +499 B legacy linked

Paired current-object previews against frozen published census 5366c4f808
(October 20, 12:21) change GlobalChainCleanup from 0 to 449 B and
Rva007ACBC0Ww3dCmdGroup from 0 to 50 B. No census change, closed-strict gain
or link.exe placement is claimed. Both units independently pass self-strict
preparation; all 18 matched bodies, relocations and two string references
verify exactly, with no EH-bearing rows. The frozen-source check passes.

The debug header is used only for ProfileCmdInterface's base in the cleanup
unit. A scoped import/novtable annotation preserves the visible constructor
and omits its incompatible two-slot base table and empty constructor copy.
In the WW3D initializer, novtable omits only the abstract base table; the
existing empty virtual destructor becomes imported-forceinline to bind to its
retail owner without emitting a competing destructor. The derived target
table and initializer bytes remain exact. These are existing class views;
no shared header, ABI, compiler flag, pin, alias or verifier is changed.
Only these two units have the base-table conflict in the frozen rank.

The cleanup's existing g_Va00DFEBE4 reference lacked an owner. Its native
007B77EC body loads VA 00DFEBE4 and calls rowed Release_Ref. Define its four-byte
storage and record RVA 009FEBE4 in data_rows.csv; the data verifier confirms
its loader-zero value in the virtual tail of .data. The original global
identity remains unknown. No second owner or converged datum exists there.

Prior attempt 65620 split the constructor and lost instruction scheduling;
this trial retains that body and its header. A novtable-only trial exposed
an empty constructor conflict in cleanup and a destructor conflict in WW3D;
the accepted imported-inline variants remove those copies without changing
native code. Donor-method review is inherited from preceding allocator repair
(BFME1 92f6bbe8, visible-body/unique-owner commit 51b97cd796); target bytes
and data independently establish the accepted local repairs.
