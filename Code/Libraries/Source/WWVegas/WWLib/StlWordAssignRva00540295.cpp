// cl: /O1 /EHsc /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>

struct Rva00540295Words { unsigned words[10];
 // ?Rva00540295Words::operator= present-unmatched
 Rva00540295Words&operator=(const Rva00540295Words&s){words[0]=s.words[0];words[1]=s.words[1];words[2]=s.words[2];words[3]=s.words[3];words[4]=s.words[4];words[5]=s.words[5];words[6]=s.words[6];words[7]=s.words[7];words[8]=s.words[8];words[9]=s.words[9];return *this;} };
template _STL::vector<Rva00540295Words>::vector(const _STL::vector<Rva00540295Words> &);
// Reference STLport4.5.3; native extent and pointer arithmetic establish
// record width40. Explicit scalar assignment form is target-supported
// for this helper shape; no application record identity or field names inferred.
