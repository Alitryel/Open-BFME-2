// cl: /Od /Gy /GF
// Open-BFME5 conversions.

#pragma comment(linker, "/alternatename:?bfmeFwdSWA@BfmeThingSWA@@QAEXH@Z=?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD@Z")

// STLport 4.6 stl/debug/_debug.c defines the same 27 messages, in this
// order, as __stl_debug_engine<_Dummy>::_Message_table. Retail RVA
// 0x009A71A8 contains all 27 pointers; the following word is outside the
// table. Retain the ledger name; the target template argument is unknown.
void *g_bfmeTableSWA[27] = {
    (void *)"\n%s(%d): STL error: %s\n",
    (void *)"%s(%d): STL assertion failure : %s\n",
    (void *)"\n%s(%d): STL error : %s\n%s(%d): STL assertion failure:     %s \n",
    (void *)"Invalid argument to operation (see operation documentation)",
    (void *)"Taking an iterator out of destroyed (or otherwise corrupted) container",
    (void *)"Trying to extract an object out from empty container",
    (void *)"Past-the-end iterator could not be erased",
    (void *)"Index out of bounds",
    (void *)"Container doesn't own the iterator",
    (void *)"Uninitialized or invalidated (by mutating operation) iterator used",
    (void *)"Uninitialized or invalidated (by mutating operation) lefthand iterator in expression",
    (void *)"Uninitialized or invalidated (by mutating operation) righthand iterator in expression",
    (void *)"Iterators used in expression are from different owners",
    (void *)"Iterator could not be dereferenced (past-the-end ?)",
    (void *)"Range [first,last) is invalid",
    (void *)"Iterator is not in range [first,last)",
    (void *)"Range [first,last) is not in range [start,finish)",
    (void *)"The advance would produce invalid iterator",
    (void *)"Iterator is singular (advanced beyond the bounds ?)",
    (void *)"Memory block deallocated twice",
    (void *)"Deallocating a block that was never allocated",
    (void *)"Deallocating a memory block allocated for another type",
    (void *)"Size of block passed to deallocate() doesn't match block size",
    (void *)"Pointer underrun - safety margin at front of memory block overwritten",
    (void *)"Pointer overrrun - safety margin at back of memory block overwritten",
    (void *)"Attempt to dereference null pointer returned by auto_ptr::get()",
    (void *)"Unknown problem",
};

void bfmeWriteSWA(void *sink, int a, int b, void *tag);

void bfmeGoSWA(int a, int b, int c)
{
	bfmeWriteSWA(g_bfmeTableSWA[0], b, c, g_bfmeTableSWA[a]);
}

class BfmeThingSWA
{
public:
	void bfmePassSWA(int a);
	void bfmeFwdSWA(int a);
};

void BfmeThingSWA::bfmePassSWA(int a)
{
	char m_bfmeScratch[0x48];
	bfmeFwdSWA(a);
}
