// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// STLport template bodies retail holds as one size-optimised (/O1) out-of-line copy each:
// vector<bool>::_M_fill_insert with its fill/fill_n helpers; vector<Drawable*>::_M_fill_insert;
// map<UnsignedShort UnsignedByte>::operator[] and its pair ctor.
// The pointer constants below only make this TU instantiate them; they are not retail data.
//
// Retail keeps one unsigned max, RVA 0x00013740 (the vendored STLport row). This unit's
// flags (/G7 /arch:SSE) compile a different copy, and retail kept another unit's. This unit-local
// overload keeps the inlined code and offers the link no second copy.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine
#include "Common/ActionManager.h"
#include "Common/DiscreteCircle.h"
#include "Common/GameEngine.h"
#include "Common/GameState.h"
#include "Common/MessageStream.h"
#include "Common/NameKeyGenerator.h"
#include "Common/PerfTimer.h"
#include "Common/Player.h"
#include "Common/PlayerList.h"
#include "Common/Radar.h"
#include "Common/ThingFactory.h"	// for bullet type hack
#include "Common/ThingTemplate.h"
#include "Common/Xfer.h"
#include "GameLogic/AIPathfind.h"
#include "GameLogic/GameLogic.h"
#include "GameLogic/Object.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/BodyModule.h"
#include "GameLogic/Module/CollideModule.h"
#include "GameLogic/Module/ContainModule.h"
#include "GameLogic/Module/StealthUpdate.h"
#include "GameLogic/PartitionManager.h"
#include "GameLogic/PolygonTrigger.h"
#include "GameLogic/Squad.h"
#include "GameLogic/GhostObject.h"
#include "GameClient/Line2D.h"
#include "GameClient/ControlBar.h"
#ifdef _DEBUG
#include "Common/PlayerList.h"
#endif
#ifdef PM_CACHE_TERRAIN_HEIGHT
#include "common/mapobject.h"
#include "../../../../../reference/shims/bfme_coord3d_construct_link/coord3d_construct_link.h"
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned short>::operator()(unsigned short const &x,unsigned short const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> Coord3D * __copy_backward<Coord3D *, Coord3D *, int>(Coord3D *, Coord3D *, Coord3D *, random_access_iterator_tag const &, int *); }
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> void fill<Coord3D *, Coord3D>(Coord3D *, Coord3D *, Coord3D const &); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void vector<Coord3D, allocator<Coord3D> >::_M_fill_insert(Coord3D *, unsigned int, Coord3D const &); }
// bfme link decl-only end
#endif
#ifdef DUMP_PERF_STATS
#endif 
#ifdef _INTERNAL
#endif
#define DISABLE_INVALID_PREVENTION	//Steven, I had to turn this off because it was causing problem with map border resizing (USA04). -MW

typedef std::vector<bool> BfmeBoolVector;
extern void (BfmeBoolVector::*const g_bfmeBoolVecFillInsertAnchor)(BfmeBoolVector::iterator, size_t, bool);
void (BfmeBoolVector::*const g_bfmeBoolVecFillInsertAnchor)(BfmeBoolVector::iterator, size_t, bool) = &BfmeBoolVector::_M_fill_insert;
class Drawable;
typedef std::vector<Drawable *> BfmeDrawablePtrVector;
extern void (BfmeDrawablePtrVector::*const g_bfmeDrawVecFillInsertAnchor)(BfmeDrawablePtrVector::iterator, size_t, Drawable *const &);
void (BfmeDrawablePtrVector::*const g_bfmeDrawVecFillInsertAnchor)(BfmeDrawablePtrVector::iterator, size_t, Drawable *const &) = &BfmeDrawablePtrVector::_M_fill_insert;
typedef std::vector<Coord3D> BfmeCoord3DVector;
extern void (BfmeCoord3DVector::*const g_bfmeCoordVecFillInsertAnchor)(BfmeCoord3DVector::iterator, size_t, const Coord3D &);
void (BfmeCoord3DVector::*const g_bfmeCoordVecFillInsertAnchor)(BfmeCoord3DVector::iterator, size_t, const Coord3D &) = &BfmeCoord3DVector::_M_fill_insert;
// insert_unique(v) in retail's layout (0x004D1BF7, rowed in
// StlO1UShortByteInsertUnique.cpp under _BFME_RETAIL_TREE_INSERT_LAYOUT):
// the leftmost fast path inserts at (y, y). This unit keeps the default
// spelling for its own rows, so it spells this one member out instead of
// emitting the default-layout copy the link would otherwise keep.
typedef _STL::_Rb_tree<unsigned short, _STL::pair<const unsigned short, unsigned char>, _STL::_Select1st<_STL::pair<const unsigned short, unsigned char> >, _STL::less<unsigned short>, _STL::allocator<_STL::pair<const unsigned short, unsigned char> > > BfmeUShortByteTree;
namespace _STL {
template <> inline pair<BfmeUShortByteTree::iterator, bool> BfmeUShortByteTree::insert_unique(const BfmeUShortByteTree::value_type &__v)
{
	_Link_type __y = this->_M_header._M_data;
	_Link_type __x = _M_root();
	bool __comp = true;
	while (__x != 0) {
		__y = __x;
		__comp = _M_key_compare(_Select1st<value_type>()(__v), _S_key(__x));
		__x = __comp ? _S_left(__x) : _S_right(__x);
	}
	iterator __j = iterator(__y);
	if (__comp && __j == begin())
		return pair<iterator, bool>(_M_insert(__y, __y, __v), true);
	if (__comp)
		--__j;
	if (_M_key_compare(_S_key(__j._M_node), _Select1st<value_type>()(__v)))
		return pair<iterator, bool>(_M_insert(__x, __y, __v), true);
	return pair<iterator, bool>(__j, false);
}
}typedef std::map<UnsignedShort, UnsignedByte> BfmeUShortByteMap;
extern UnsignedByte &(BfmeUShortByteMap::*const g_bfmeUShortByteMapIndexAnchor)(const UnsignedShort &);
UnsignedByte &(BfmeUShortByteMap::*const g_bfmeUShortByteMapIndexAnchor)(const UnsignedShort &) = &BfmeUShortByteMap::operator[];
