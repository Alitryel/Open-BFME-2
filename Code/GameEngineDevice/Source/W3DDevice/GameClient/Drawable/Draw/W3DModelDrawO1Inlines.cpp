// cl: /FIzh_ascii.h /Ireference/shims/sparse_public /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// Size-optimised (/O1) emission of W3DModelDraw header inlines and templates retail keeps out of line.
//
#define DEFINE_W3DANIMMODE_NAMES
#define DEFINE_WEAPONSLOTTYPE_NAMES
#define NO_DEBUG_CRC
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include "Common/CRC.h"
#include "Common/CRCDebug.h"
#include "Common/GameState.h"
#include "Common/GlobalData.h"
#include "Common/PerfTimer.h"
#include "Common/RandomValue.h"
#include "Common/ThingTemplate.h"
#include "Common/GameLOD.h"
#include "Common/Xfer.h"
#include "Common/GameState.h"
#include "Common/QuickTrig.h"
#include "GameClient/Drawable.h"
#include "GameClient/FXList.h"
#include "GameClient/Shadow.h"
#include "GameLogic/GameLogic.h"		// for real-time frame
#include "GameLogic/Object.h"
#include "GameLogic/WeaponSet.h"
#include "GameLogic/FPUControl.h"
#include "GameLogic/Module/AIUpdate.h"
#include "GameLogic/Module/PhysicsUpdate.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"
#include "W3DDevice/GameClient/W3DAssetManager.h"
#include "W3DDevice/GameClient/W3DDisplay.h"
#include "W3DDevice/GameClient/W3DScene.h"
#include "W3DDevice/GameClient/W3DShadow.h"
#include "W3DDevice/GameClient/W3DTerrainTracks.h"
#include "W3DDevice/GameClient/WorldHeightMap.h"
#include "WW3D2/HAnim.h"
#include "WW3D2/HLod.h"
#include "WW3D2/RendObj.h"
#include "WW3D2/Mesh.h"
#include "WW3D2/MeshMdl.h"
#include "Common/BitFlagsIO.h"
// bfme link decl-only begin
namespace _STL { template <> unsigned long _Base_bitset<4>::_S_maskbit(unsigned int); }
// bfme link decl-only end

// Use the rowed 104-bit comparator at 0x0033AD13. Its source in
// SparseMatchFinderModelConditionCompare117.cpp owns the out-of-line copy.
template<> bool SparseMatchFinder<ModelConditionInfo, ModelConditionFlags>::MapHelper::operator()(const ModelConditionFlags &, const ModelConditionFlags &) const;

// Use the rowed four-word SWAR intersection counters from
// BitFlags117CountInverseIntersection.cpp (inverse: 0x0033AE53), not ZH COMDATs.
template<> int BitFlags<117>::countIntersection(const BitFlags<117> &that) const;
template<> int BitFlags<117>::countInverseIntersection(const BitFlags<117> &that) const;

// bfme link decl-only begin
// The ModelCondition SparseMatchFinder comparator and slow path are owned by
// SparseMatchFinderModelConditionCompare117.cpp (0x0033AD13) and
// SparseMatchFinderModelConditionBestInfoSlow117.cpp (0x0033BDF8), and the
// map/tree/pair bodies the /O1 instantiation emits here are owned
// retail-identically by ModelConditionMap117InsertUnique.cpp (0x0033D142 and
// its tree) and Rva0033D142Permuted.cpp; this TU's copies are the first in link
// order and split them, so declaration-only specializations stop it emitting
// (and referencing) its own. findBestInfo 0x0033D46A, the 2-arg pair
// constructor 0x005EEF13 and countConditionInverseIntersection 0x0033B74A are
// this TU's own rows and stay.
typedef _STL::pair<const BitFlags<117>, const ModelConditionInfo *> BfmeLinkMCPair;
namespace _STL {
typedef _Rb_tree<const BitFlags<117>, BfmeLinkMCPair, _Select1st<BfmeLinkMCPair>, SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::MapHelper, allocator<BfmeLinkMCPair> > BfmeLinkMCTree;
typedef map<const BitFlags<117>, const ModelConditionInfo *, SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::MapHelper, allocator<BfmeLinkMCPair> > BfmeLinkMCMap;
template <> BfmeLinkMCPair::pair(const BfmeLinkMCPair &);
template <> void _Construct<BfmeLinkMCPair, BfmeLinkMCPair>(BfmeLinkMCPair *, const BfmeLinkMCPair &);
template <> const ModelConditionInfo *& BfmeLinkMCMap::operator[](const BitFlags<117> &);
template <> BfmeLinkMCTree::iterator BfmeLinkMCTree::insert_unique(BfmeLinkMCTree::iterator, const BfmeLinkMCPair &);
template <> pair<BfmeLinkMCTree::iterator, bool> BfmeLinkMCTree::insert_unique(const BfmeLinkMCPair &);
}
template <> bool SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::MapHelper::operator()(const BitFlags<117> &, const BitFlags<117> &) const;
template <> const ModelConditionInfo *SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::findBestInfoSlow(const _STL::vector<ModelConditionInfo, _STL::allocator<ModelConditionInfo> > &, const BitFlags<117> &) const;
// The rowed inverse-intersection counter was instantiated only as a side effect
// of findBestInfoSlow's body above; keep it with an explicit instantiation.
template int SparseMatchFinder<ModelConditionInfo, BitFlags<117> >::countConditionInverseIntersection(const BitFlags<117> &, const BitFlags<117> &);
// bfme link decl-only end
#ifdef _INTERNAL
#endif

// _Rb_tree_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
// TRANSITIVE anchor (no <map>/<set> include in this TU).
namespace _STL {
template <class _RbVal, class _RbLeft, class _RbRight>
static inline bool operator!=(const _Rb_tree_iterator<_RbVal, _RbLeft> &a,
                              const _Rb_tree_iterator<_RbVal, _RbRight> &b)
{ return a._M_node != b._M_node; }
}

typedef std::pair<const ModelConditionFlags, const ModelConditionInfo *> BfmeModelConditionPair;
#pragma inline_depth(0)
// ?_bfmeModelDrawO1Anchor@@ absent-from-retail
const ModelConditionInfo *_bfmeModelDrawO1Anchor(ModelConditionInfo::WeaponBarrelInfo *w, const W3DModelDrawModuleData *d, const ModelConditionFlags &c, PristineBoneInfoMap *m, BfmeModelConditionPair *mp, const ModelConditionInfo *const &info)
{
	w->ModelConditionInfo::WeaponBarrelInfo::WeaponBarrelInfo();
	m->PristineBoneInfoMap::map();
	mp->BfmeModelConditionPair::pair(c, info);
	return d->m_conditionStateMap.findBestInfo(d->m_conditionStates, c);
}
#pragma inline_depth()

// PristineBoneInfo's implicit copy constructor only comes out of line through
// the map element assignment path.
// ?_bfmePristineBoneAnchor@@ absent-from-retail
void _bfmePristineBoneAnchor(PristineBoneInfoMap *m, NameKeyType k, const PristineBoneInfo &q)
{
	(*m)[k] = q;
}