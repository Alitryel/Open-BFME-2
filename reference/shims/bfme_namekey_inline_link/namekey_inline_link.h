// Link view of NAMEKEY(const char *) from Common/NameKeyGenerator.h (Zero Hour reference).
// Consumers include it before any game header. Retail has one out-of-line NAMEKEY, the /O1
// body at 0x000788E8 (rowed in RadarNewMap.cpp); every other use is inlined. An /O2 unit
// that only inlines NAMEKEY still emits an /O2-shaped COMDAT copy (mov eax,[esp+4];
// push eax) that differs from retail's (push [esp+4]) and, first in link order, makes
// every unit sharing the name lose it. Declared imported and forceinline here, the
// header's inline definition still expands at each use, but the unit emits no copy.
#ifndef BFME_NAMEKEY_INLINE_LINK_H
#define BFME_NAMEKEY_INLINE_LINK_H

enum NameKeyType;
__declspec(dllimport) __forceinline NameKeyType NAMEKEY(const char *name);

#endif
