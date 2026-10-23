// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /MD /EHsc
// stlport
// Native5EFD8F..5EFDDB76B; WB1618180 same allocation/member-store flow.
// Class owner from existing destructor5EFDDB and vtableC78964. Impl64B
// allocation and constructor5EF92D proven by this caller; the constructor is rowed as
// StrategicHUD::RegionDetailsArmiesMovieClip::Impl (ArmyCommandPointsMovieClipConstructor.cpp).
#include "RegionDetailsArmiesClipImplView.h"
typedef StrategicHUD::RegionDetailsArmiesMovieClip::Impl Rva005EF92D;
class Rva005EFDDB {public:Rva005EFDDB(unsigned,const void *,int);virtual ~Rva005EFDDB();private:Rva005EF92D *impl;};
Rva005EFDDB::Rva005EFDDB(unsigned level,const void *name,int color):impl(new Rva005EF92D(level,*(const AsciiString *)name,color)){}
