// ?Rva006CFDF0DecRef@@YAHPAH@Z, retail 0x006CFDF0, 12 bytes.
//
// Reference-count decrement leaf for the Nugget-chain block family: loads
// the count, predecrements in a register, stores back, returns the new
// value. Spelled through an explicit local so MSVC emits
// load/dec/store/mov (8b 08/49/89 08/8b c1) instead of folding to a
// direct dec-mem (contrast the inlined 0x006D0F27 site, which discards the
// value and gets ff 08). Spelled as one anonymous expression: a named
// return local lets the backend anticipate the return into eax and the
// trailing mov vanishes. No calls, no // cl: line (defaults match).
int Rva006CFDF0DecRef(int *refCount)
{
	return --*refCount;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?decrement@Rva00894D90Accessor@@SAIPAI@Z=?Rva006CFDF0DecRef@@YAHPAH@Z")
#pragma comment(linker, "/alternatename:?decrement@Rva00894D90Accessor@@SAIPAH@Z=?Rva006CFDF0DecRef@@YAHPAH@Z")
#pragma comment(linker, "/alternatename:?bfmeDecVGO@@YAIPAI@Z=?Rva006CFDF0DecRef@@YAHPAH@Z")
