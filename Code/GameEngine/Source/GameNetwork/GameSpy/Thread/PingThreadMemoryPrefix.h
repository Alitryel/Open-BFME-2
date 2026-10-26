#pragma once

// Keep the game's throwing C-linkage free declaration ahead of STL allocator
// headers when the PingThread donors are composed into their retail TU.
// The existing call sites target the game wrapper at RVA 0x00030830.
#include <stdlib.h>
namespace GameMemory { extern "C" void __cdecl free(void *) throw(...); }
#define free GameMemory::free
