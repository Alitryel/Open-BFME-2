# BitFlags clear ownership correction, 2026-10-23

The existing row ?clear@?$BitFlags@$0HE@@@QAEXXZ at 0x00666E80 is 14 bytes
of ordinary C++: BitFlags<116> owns one STLport bitset and clear calls reset,
which clears its four words. EA's reference Common/BitFlags.h supplies the
field and implementation; the former owner already emitted that exact symbol.
This is not a newly discovered function or a new algorithm reconstruction.

The former SupplyTruckAIUpdate.cpp owned only this ledger row and no data row.
It also contained a separate unverified naked privateIdle byte spray. The
progress scanner's conservative single-row/single-naked-body rule therefore
classified the clear row as assembly, although clear itself comes from C++.

The dedicated BitFlagsClear.cpp preserves the same bitset field and reset
expression in a limited class view and explicitly instantiates only clear.
Its region default is O2/G7/x87; no new flag override is needed. Isolated O2
and the normal production gate reproduce all 14 bytes with no relocations.
The retired source is preserved here as SupplyTruckAIUpdate.cpp.txt, including
its original comments and licensing. It no longer contributes unverified code
to Code/ and does not leave a zero-row source in the build. No header changed.

add_match --replace-existing verifies the repointed row normally. The native
identity, address, extent and behavior stay fixed. The coverage attribution
can gain 14 C++ bytes; report that as an ownership correction, not a newly
reconstructed function. This also removes the unrelated assembly spray from
compiled source rather than claiming it as a recovery.

Definition check: the shadow gate reports a divergent clear COMDAT whose kept
copy is in DumbProjectileBehavior.cpp. This predates the move: the former
SupplyTruck owner and the new owner both emit exactly
33c0890189410489410889410cc3 with zero relocations. Repeating dup_defs.analyse
with the old owner restored in the same link-order slot reports the same four
copies, two variants and the same wrong kept copy. This change introduces no
new byte variant and claims no linked-byte improvement; the existing kept-copy
conflict is separate linking debt.
