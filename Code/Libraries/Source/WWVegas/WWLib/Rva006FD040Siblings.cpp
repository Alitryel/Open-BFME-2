// cl: /DNDEBUG /MD /EHsc
// stlport

// 26 B forwarder of the __unguarded_insertion_sort shape at retail
// 0x006FD040: f(first, last, comp) -> g(first, last, (void *)0, comp). /O2
// emits the argument shuffle and the NULL type tag directly; the callee is the
// unrowed body at 0x006FC670, declared here as an opaque address-derived symbol
// and pinned. Call sites 0x006E5BB4 and 0x0070EE1C/0x0070EE51/0x0070EEC2 push
// three arguments and clean 0x0C, confirming the cdecl shape.

extern "C" void BfmeAux006FC670(void *first, void *last, void *sentinel, void *comp);

extern "C" void Rva006FD040(void *first, void *last, void *comp)
{
	BfmeAux006FC670(first, last, 0, comp);
}
