Scene rescale linkage, 2026-10-21

Published census 2b4d1fb42a: SceneSpatialRescale_Unresolved.cpp has 207
nonpadding bytes held by _STL::_Slist_base<int,allocator<int> > destructor.
The provider SceneNodeListProviders.cpp has the complete retail 9B destructor
at 0x6FB50 and 45B erase at 0x6FABF. Both sources passed --prepare-current
before trials (six rows, including caller EH action); no source changes retained.

Two scoped specialization trials with the current /O2 caller settings:
1. dllimport __forceinline destructor with STLport's original body
   {_M_erase_after(&_M_head._M_data,0);} keeps the 197B parent and handler
   exact but removes the rowed 8B cleanup action (gate: symbol not found).
   The imported outlined destructor cannot supply that original direct cleanup.
2. Declaration-only destructor preserves the cleanup target, but the parent
   loses the inline pool recycling loop. Initialization changes from two memory
   zero stores to xor eax/eax plus stores; normal exit becomes a direct dtor
   call with explicit EH state instead of the native loop. Parent gate fails.

The conflict is between inline cleanup visibility and the separately rowed
/O1 destructor, not a missing provider. Existing imported forceinline erase
and constructor are necessary for the caller. Further work needs a supported
compiler/ownership solution preserving both the main body and direct EH action.
No false-reject asserted: the emitted conflicting destructor really differs.
Inputs: BFME1 verified pointer 5987fd1b859e86801d093256eadc6fb63d87785f;
BFME2 b65eb7b004; native boundaries 141F90..142055 and 766120..766128.
Diagnostics remain locally in build/scene-rescale-link/{gate-1,gate-2}.log.
