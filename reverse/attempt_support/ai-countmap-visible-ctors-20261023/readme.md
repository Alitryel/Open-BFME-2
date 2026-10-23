# AI count-map constructor visibility trial

Seat astra-s5; model gpt-6-astra; input HEAD 7eba3f860d, toolchain/flags from StlSweepW4Rva004E02B8.cpp (/Og /Os /Ob1 /EHsc /MD, STLport 4.5.3). No production source changes retained. This extends the earlier ai-countmap-constructor-link-20261022 and rva16e400-hash-ctor-link-20261022 evidence.

AIStatCollector currently has an unresolved default hash_map<int,int> constructor, fold-pinned to RVA 0x004E02B8 (31 bytes). The existing provider explicitly instantiates that constructor but earlier declaration-only specializations suppress it and its hashtable constructor.

Trials with tools/variant.py:

1. Removing only the map constructor suppression emits 39 bytes rather than 31: an allocator byte is zeroed with STOSB and the three temporary references use separate stack slots.
2. Also removing the hashtable constructor suppression emits the correct 31-byte map instruction body, pending the hashtable call relocation. Its newly emitted hashtable constructor is 77 bytes rather than native 64 (extra allocator cleanup/EH state).
3. Also removing declaration-only vector<void*> and _Vector_base<void*> allocator constructors and allocator<void*> destructor yields a 64-byte table constructor with the native instructions apart from relocation operands. The attached patch preserves this best diagnostic trial; it is not a landed implementation.

Remaining prerequisite: native table constructor RVA 0x004E007A calls bucket initialization at RVA 0x00148DDF (59 bytes). The actual int-pair specialization emitted by this trial calls its already rowed _M_initialize_buckets at RVA 0x00622410 (106 bytes, stlport_hash_map_int.cpp). These are different implementations, so the 64-byte instruction resemblance does not prove the table or map fold. Do not assign the int-pair initializer a second RVA or mask the call.

Type identity also needs reassessment: the existing 4E007A/4E02B8 owner uses an opaque eight-byte Rva004E007AElement, whereas AIStatCollector's private view uses int. The map provider comment attributes node+8 evidence to Register, but the current Register implementation is a listener callback. Reconcile actual container uses and ownership before changing the class view. Callee visibility explains the stack/EH deltas; it does not settle that semantic identity. No donor source was imported. No exact link gain claimed.
