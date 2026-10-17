// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// Complete boundaries: 427F14..427F46 (50B), 427F46..427F75 (47B).
// The two complete retail returns call rowed VersionBlockParser lookup
// 427EDA, then construct the caller's return storage with rowed STLport
// narrow-string constructor 9100. Key/default arguments expose only word 0;
// their original C++ wrapper types and these method spellings are unknown.
// stlport
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char, allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::~basic_string(); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}
typedef std::string NarrowString;
struct Rva00427F14KeyPrefix {
    const char *first;
    const char *text() const { return first; }
};
class VersionBlockParser {
public:
    const char *lookupVersionValue(const char *, const char *);
    NarrowString rva00427F14Text(const Rva00427F14KeyPrefix &key);
    NarrowString rva00427F46Text(const Rva00427F14KeyPrefix &key,
                               const Rva00427F14KeyPrefix &fallback);
};
NarrowString VersionBlockParser::rva00427F14Text(const Rva00427F14KeyPrefix &key) {
    const char *text = lookupVersionValue(key.text(), 0);
    if (!text) text = "";
    return NarrowString(text);
}
NarrowString VersionBlockParser::rva00427F46Text(const Rva00427F14KeyPrefix &key,
                                               const Rva00427F14KeyPrefix &fallback) {
    return NarrowString(lookupVersionValue(key.text(), fallback.text()));
}
