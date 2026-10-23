// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// Native complete20B forwards two cdecl pointer arguments to independently named and rowed xferThingTemplateCountMap55AC77 then returns original first argument. ZH/BFME1 count-map transfer semantics and provider ThingTemplateCountMap.cpp establish argument types; forwarding helper original identity remains address-derived. Gap real_bytes19 incorrectly drops displacement byteCC; complete extent20 used.
// Reference revision: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d.
class Xfer;
struct TemplateCountKey;
namespace _STL {template<class T>struct less;template<class T>class allocator;template<class A,class B>struct pair;template<class Key,class Value,class Compare,class Alloc>class map;}
typedef _STL::map<TemplateCountKey,int,_STL::less<TemplateCountKey>,_STL::allocator<_STL::pair<const TemplateCountKey,int> > > ObjectCountMap;
void xferThingTemplateCountMap(Xfer*,ObjectCountMap*);
extern "C" Xfer *Rva004EDFD6Xfer(Xfer *xfer,ObjectCountMap *map){xferThingTemplateCountMap(xfer,map);return xfer;}
