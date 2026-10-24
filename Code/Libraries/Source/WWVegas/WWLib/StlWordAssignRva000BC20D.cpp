// cl: /O1 /EHsc /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include "../../../../../vendor/stlport/stl/_uninitialized.h"
#include <vector>

struct Rva000BC20DWords { unsigned words[6];
 // ?Rva000BC20DWords::operator= present-unmatched
 Rva000BC20DWords&operator=(const Rva000BC20DWords&s){words[0]=s.words[0];words[1]=s.words[1];words[2]=s.words[2];words[3]=s.words[3];words[4]=s.words[4];words[5]=s.words[5];return *this;} };
template _STL::vector<Rva000BC20DWords>& _STL::vector<Rva000BC20DWords>::operator=(const _STL::vector<Rva000BC20DWords> &);
// Reference STLport4.5.3; native extent and pointer arithmetic establish
// record width24. Explicit scalar assignment form is target-supported
// for this helper shape; no application record identity or field names inferred.
