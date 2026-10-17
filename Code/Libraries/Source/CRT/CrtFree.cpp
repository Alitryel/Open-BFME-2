// cl: /O2 /G6 /Ob2 /DNDEBUG /MD
// Retail 00628F98..00628F9D is FF25 through IAT 00BBA6E8:
// PE import msvcr71.dll!free, cdecl void(void *).
// CrtFree is this project's typed name for that import veneer, distinguishing
// it from the game's memory-pool free at 00030830. No original C++ name is
// inferred. The generated placeholder's complete six-byte body is preserved.
extern "C" __declspec(dllimport) void __cdecl free(void *block);

void __cdecl CrtFree(void *block)
{
    free(block);
}
