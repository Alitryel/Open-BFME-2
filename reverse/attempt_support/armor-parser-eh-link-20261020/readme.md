# Armor parser cleanup prerequisites and duplicate repair

The now-rowed ArmorStore::parseArmorDefinition at1D9484 is397 bytes; WBABCAB0
and the Armor field table establish its identity. The BFME1 near lane still
serves25-byte76962A from Fade0060F010. The native parent graph, rather than
that donor's frame coincidence, establishes the cleanup ownership:
handler769643 -> FuncInfo90E5F8, nine states, unwind map90E5B0. The complete
parent and EH graph are EXACT. Actions7695EA/7695F4/76960D/769615/769620/
76962A have extents10/25/8/11/10/25;769643 is the10-byte handler. Internal
labels76960C and769642 are return instructions inside conditional actions,
not separate bodies. No overlapping row or new cleanup claim was added.

## Verified repair retained

Armor.cpp retained the obsolete Zero Hour ArmorStore::parseArmorDefinition,
which takes an ArmorTemplate value from a different map representation and
lacks BFME2's override/pending branches. It collided with the now-proven
ArmorStoreParse.cpp definition. Remove that obsolete duplicate, retaining
the INI forwarding wrapper. Explicitly instantiate the existing table's
_M_find<NameKeyType> and resize, the two rowed helpers whose emission formerly
depended on the obsolete body. The actual comparison type is rts::equal_to,
not _STL::equal_to: a trial with the latter emitted different names and was
corrected. All nine existing rows remain exact; native hashtable EH also
remains EXACT, and find_declared_unmatched passes. This repair removes the
parser duplicate; it does not claim the full legacy unit now links.

## Concrete remaining prerequisite

ArmorStoreParse.cpp still emits conflicting STLport void-pointer vector,
allocator, proxy, max and hash COMDATs. Its 397-byte parent matching does not
prove its nested operator[] fold after a source change. Explicitly rerun
pin_admission.fold_proof_problems against every owner of the chain addresses
41F4E5,148B27,53F3B1,53F1EC,5571B,3ED191,60C9D9; do not rely only on the
unchanged pin or parent byte gate.

A declaration-only/import trial makes the parser preview LINKS397 bytes,
but changes its recursively proven resize helper from184 to220 bytes. A
forced-inline variant changes it to302 bytes. Preserving native calls to
vector get_allocator23B50, constructor26A40 and swap26B60 improves that to
215 bytes but leaves imported destructor references. None is a valid repair.
The first failed trial is preserved as a diagnostic patch, never production.

The allocator<void*> and alloc-proxy destructors in this optimized unit are
one-byte RETs, while the first kept /Od providers emit ten-byte frame-bearing
empty destructors. The vector destructor likewise has an optimized conditional
free locally and a much larger /Od/EH provider. These shared provider/consumer
contracts need reconciliation while keeping resize's full184-byte fold and
all provider rows exact. No new pragma, alias, pin, baseline or shared-header
escape was introduced. An /EHs control preserves parent, EH and recursive
fold but leaves the same conflicts. Disabling template exports and extern
class instantiations also leave the offending copies; not retained.

The parser is restored byte-for-byte to its published source. All seven
cleanup RVAs remain deferred until that prerequisite is resolved. Inputs:
BFME2 3d751c752df; BFME1 verified pointer0dc8a26a9c6041c73dc564754cd059dc54faa72a;
MSVC7.1 13.10.3077, existing per-source flags. The whole source files and all
prior76962A attempts were reviewed. Replay under build/next-batch-oct20a:
armor-parent*.txt, armor-combined*.txt, resize-base.txt, armor-fold.py,
armor-dtors.py and source variants. Model:gpt-6.1-sol; t=18min.
