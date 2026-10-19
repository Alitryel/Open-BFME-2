// cl: /DNDEBUG /MD /EHsc /Od

// Retail 0x0082C580 is STLport's
//   _STL::__malloc_alloc<0>::allocate(size_t)
// (?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z).
// The body below is verbatim from vendor/stlport/stl/_alloc.h; it is emitted
// under the object symbol the ledger pins for this row.
//
// Retail built the STLport alloc helpers unoptimised, hence /Od above:
// __result lives on the stack ([ebp-4]) rather than in a register.

extern "C" __declspec(dllimport) void* __cdecl malloc(unsigned int);
extern "C" void* __cdecl bfme_MallocAlloc0Allocate_82C580(unsigned int);

// The same body is also instantiated under its real name: this unit sorts
// first among its definers in link order, so its select-any copy is the one
// every caller of __malloc_alloc<0>::allocate gets.
namespace _STL {
template <int _Inst> class __malloc_alloc
{
private:
	static void *_S_oom_malloc(unsigned int);
	friend void *::bfme_MallocAlloc0Allocate_82C580(unsigned int);
public:
	static void *allocate(unsigned int __n)
	{
		void* __result = malloc(__n);
		if (0 == __result)
			__result = _S_oom_malloc(__n);
		return __result;
	}
};
template class __malloc_alloc<0>;
}

extern "C" void* __cdecl
bfme_MallocAlloc0Allocate_82C580(unsigned int __n)
{
  void* __result = malloc(__n);
  if (0 == __result)
    __result = _STL::__malloc_alloc<0>::_S_oom_malloc(__n);
  return __result;
}
