// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme_obbox_transform_link /DBFME_WEAPON_BARREL_INLINE_ONLY /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/w3dmodeldraw8 /DWIN32 /D_WINDOWS /D_CRTIMP= /D_STLP_USE_MALLOC /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims/bfme_matrix3d_copy_link
// stlport

// ??A?$map@W4NameKeyType@@UPristineBoneInfo@@U?$less@W4NameKeyType@@@_STL@@V?$allocator@U?$pair@$$CBW4NameKeyType@@UPristineBoneInfo@@@_STL@@@4@@_STL@@QAEAAUPristineBoneInfo@@ABW4NameKeyType@@@Z
// retail 0x000BCF68, 80 bytes. PristineBoneInfoMap::operator[]: lower_bound on the key (retail
// shares the int/int _M_lower_bound 0x00382A92), and on a miss insert (hint, pair(key, default
// PristineBoneInfo)) through the rowed insert 0x000BC1A5, the rowed pair constructor 0x000B642A
// and the rowed PristineBoneInfo default constructor 0x000423C5. The unchecked-STL flags
// (/EHs, _STLP_NO_EXCEPTIONS) give retail's ebp frame and register roles. Evidence: target bytes and the
// rowed callees; the callers (doSingleBoneName 0x000BD2BF) use the returned reference.
#include "matrix3d_copy_link.h"
#include "Common/CRC.h"
#include "W3DDevice/GameClient/Module/W3DModelDraw.h"

typedef char BfmePristineMatrixSize[(sizeof(Matrix3D) == 48) ? 1 : -1];
typedef char BfmePristineBoneSize[(sizeof(PristineBoneInfo) == 52) ? 1 : -1];

// Native 0x000423C5 constructs only the three matrix rows.
// Keep boneIndex uninitialized until the bone lookup supplies it.
PristineBoneInfo::PristineBoneInfo()
{
}

struct Rva000B642A
{
	Rva000B642A(const int *p, const PristineBoneInfo &q);
	int m_0;
	PristineBoneInfo m_4;
};

static __forceinline const PristineBoneInfoMap::value_type &asPair(const Rva000B642A &entry)
{
	return *(const PristineBoneInfoMap::value_type *)&entry;
}
typedef _STL::map<int, int> BoneIntMap;

// Retail shares one out-of-line int/int _M_lower_bound (0x00382A92) across the integer-keyed trees.
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > BoneIntTree;
template<> BoneIntTree::_Link_type BoneIntTree::_M_lower_bound(const int &) const;

template<> PristineBoneInfoMap::iterator PristineBoneInfoMap::insert(PristineBoneInfoMap::iterator, const PristineBoneInfoMap::value_type &);

template<> PristineBoneInfo &PristineBoneInfoMap::operator[](const NameKeyType &key)
{
	BoneIntMap::iterator found = ((BoneIntMap *)this)->lower_bound(*(const int *)&key);
	iterator i = *(iterator *)&found;
	if (i == end() || key < (*i).first)
	{
		i = insert(i, asPair(Rva000B642A((const int *)&key, PristineBoneInfo())));
	}
	return (*i).second;
}

// Keeps the specialization referenced so its (inline) body is emitted.
// ?_bfmePristineSubscriptAnchor@@ absent-from-retail
PristineBoneInfo &_bfmePristineSubscriptAnchor(PristineBoneInfoMap *m, const NameKeyType &k)
{
	return (*m)[k];
}
