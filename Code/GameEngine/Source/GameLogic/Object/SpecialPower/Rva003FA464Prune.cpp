// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native119B two-word callback; slot0 of C378B4. First argument unused.
#include "../../../../Include/Common/Rva003FA62B.h"

class Rva003FA464Object { public: virtual ~Rva003FA464Object(); };
namespace _STL { template <> BfmePod8 *vector<BfmePod8>::erase(BfmePod8 *); }
void Rva003FA62B::BeginTurn(int, int value)
{
 unsigned bit=(unsigned)value;
 for(int i=(int)m_records04.size()-1;i>=0;--i) {
  BfmePod8 &item=m_records04[i];
  if(!(*(const unsigned*)((const char*)&item.m_val+(bit>>5)*4)&(1U<<(bit&31)))) {
   ::delete (Rva003FA464Object*)item.m_ptr;
   m_records04.erase(&m_records04[i]);
  }
 }
}
