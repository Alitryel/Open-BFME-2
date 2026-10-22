PCA loader link helper trials, 2026-10-22
=======================================

BFME2 b68575f39f; retained BFME1 37c3022de1ab944c7ffe536440d637dc8199091c;
published index 08160bc2c9 (17:08 UTC). The original source and flags remain
the best candidate; all trials were reverted. Legacy current-object preview
holds 2362 B out on the narrow string constructor and string-base destructor.
No linked gain or false rejection is claimed.

The unit is StandingWaterAreaLoadPCA.cpp, native LoadPCAFile 3093F6..309CF8,
2306 B, /O1 /G7 /arch:SSE /MD /EHsc, static STLport and malloc allocator.
It also owns the 3080CE cleanup and compiler-emitted cleanup rows.

Trial 1 declared only the string(const char*, allocator&) constructor and
made the base destructor dllimport/forceinline with its vendor body and
throw(). The parent failed: native loop temporaries use [ebp-14h], while
the trial uses [ebp-10h], with corresponding lifetime/cleanup changes.
Several compiler-label cleanup rows also disappeared or were renumbered.

Trial 2 supplied the vendor string constructor body as dllimport/forceinline.
Declaring the destructor after it causes C2908 (already instantiated).
Ordering the base destructor first fixes that compiler error, but the third
build exposes an unresolved vector<string> allocator-only base constructor,
and the parent no longer proves the old funclet locations. The final patch
is preserved in visible-string.patch as diagnostic source, not a recovery.

Before another trial, investigate the constructor/base-constructor visibility
and parent lifetime relationship together. Do not repeat these suppressions
unchanged or add a pin merely to conceal the new unresolved helper.
