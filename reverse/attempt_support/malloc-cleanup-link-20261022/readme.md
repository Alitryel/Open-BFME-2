Malloc allocator cleanup selection, 2026-10-22

The wide monetary formatter (lowest RVA 0xDF20) emitted a malloc allocator
cleanup calling its C++ free declaration. This copy is not retail's 18-byte
import-free body at 0x23A70 and appeared ahead of its exact /Od provider.
Preserve the vendor expression and all inline expansions using the established
import/forceinline specialization; this removes only that out-of-line COMDAT.
Every retained COMDAT has identical bytes/relocation digest. All ten formatter
rows including its EH graph and all six measured consumer rows pass byte gates.

Paired frozen-index legacy preview: 0 -> 118 nonpadding matched bytes,
STLMallocAlloc0Deallocate (18) and stlport_construct_deque_string (100).
Four measured objects have strict compiler receipts; no closed-strict closure
or new census is claimed. The provider still has unrelated string/locale
blockers. GameResults sendGameResults also has a duplicate strong queue helper,
so its 197 bytes do not count in this gain. Other same-name consumers retain
unrelated prerequisites; no changes made to those units.

Source: existing STLport _alloc.h implementation, verified donor pointer
37c3022de1. Target: retained formatter bytes, native 0x23A70 provider and all
retail relocations pass ordinary gates. See proof.json for object/index hashes,
paired blocker lists, and proof.py.txt for the bounded measurement.
