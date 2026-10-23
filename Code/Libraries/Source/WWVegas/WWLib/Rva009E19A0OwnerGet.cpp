// cl: /DNDEBUG /MD /EHsc
// Carried from the Open-BFME-1 donor at submodule revision 5cae4bdf
// (game/Libraries/Source/WWVegas/WWLib/chunkio.cpp). Target evidence: the 22B
// body places uniquely in BFME2 .text at 0x006154B0 (donor b1 0x009E19A0)
// though BFME1 ICF-folded it across six addresses. The name is the carried
// donor name; the empty-string data reference keeps its donor address token.


struct Rva009E19A0Owner {
	int unknown_00;
	struct Slot {
		int unknown_00;
		char * volatile value;
	} *slot;

	char *get();
};

char *Rva009E19A0Owner::get()
{
	// Preserve the pointer-to-field step that emits retail's add +4 and load.
	char * volatile *value_address = &slot->value;
	char *value = *value_address;
	if (value != 0) {
		return value + 8;
	}
	return (char *)"";
}
