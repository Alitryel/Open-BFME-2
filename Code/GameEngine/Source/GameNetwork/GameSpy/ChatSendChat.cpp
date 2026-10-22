// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG
// stlport
// Recovery: retail 0x001EFD9C..0x001EFFC6, 554 bytes (exact).
// Shape follows the WorldBuilder twin GameSpyInfo::sendChat (WB 0xB01080,
// GameSpy/Chat.cpp): early `return false` for an empty message and for the
// room path, names declared at function scope after the selection test, one
// PlayerInfo pointer reused for the local lookup and the per-ID loop, and the
// loop skipping (continue) IDs with no player (WB asserts there, line 166).
// SelPair is only the witnessed begin/end prefix of profile-ID selections;
// no complete container layout, original class name, or capacity is asserted.
// Retail vtable VA0x00C19500 slot64 and WB callgraph identify sendChat;
// address-derived receiver name is retained. PlayerInfo exposes only its
// leading AsciiString. Request ctor/dtor: 0x1EF661/0x1EF723; action at +0x118.
#include <string>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"
// Suppress this TU's non-retail copy of ?length@?$__char_traits_base@GG@_STL@@SAIPBG@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned int __char_traits_base<unsigned short,unsigned short>::length(unsigned short const *); }
// Suppress this TU's non-retail copy of ?assign@?$__char_traits_base@GG@_STL@@SAXAAGABG@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void __char_traits_base<unsigned short,unsigned short>::assign(unsigned short &,unsigned short const &); }
// Suppress this TU's non-retail copy of ?move@?$__char_traits_base@GG@_STL@@SAPAGPAGPBGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short,unsigned short>::move(unsigned short *,unsigned short const *,unsigned int); }
// Suppress this TU's non-retail copy of ?erase@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAEPAGPAG0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::erase(unsigned short *,unsigned short *); }
// Suppress this TU's non-retail copy of ?_M_construct_null_aux@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEX:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::_M_construct_null_aux(unsigned short *,__true_type const &); }
// Suppress this TU's non-retail copy of ?_M_construct_null@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@AAEXPAG@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::_M_construct_null(unsigned short *); }
// Suppress this TU's non-retail copy of ?assign@?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAEAAV12@PBG0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> > & basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::assign(unsigned short const *,unsigned short const *); }
// Suppress this TU's non-retail copy of ?copy@?$__char_traits_base@GG@_STL@@SAPAGPAGPBGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short,unsigned short>::copy(unsigned short *,unsigned short const *,unsigned int); }
// Suppress this TU's non-retail copy of ?assign@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@PBD0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::assign(char const *,char const *); }
// Suppress this TU's non-retail copy of ?copy@?$__char_traits_base@DH@_STL@@SAPADPADPBDI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * __char_traits_base<char,int>::copy(char *,char const *,unsigned int); }
// Suppress this TU's non-retail copy of ??4?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV01@PBD@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<char,char_traits<char>,allocator<char> > & basic_string<char,char_traits<char>,allocator<char> >::operator=(char const *); }
// Suppress this TU's non-retail copy of ?deallocate@?$_STLP_alloc_proxy@PADDV?$allocator@D@_STL@@@_STL@@QAEXPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _STLP_alloc_proxy<char *,char,allocator<char> >::deallocate(char *,unsigned int); }
// Suppress this TU's non-retail copy of ?move@?$__char_traits_base@DH@_STL@@SAPADPADPBDI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * __char_traits_base<char,int>::move(char *,char const *,unsigned int); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@D@_STL@@QBEXPADI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<char>::deallocate(char *,unsigned int) const; }
// Suppress this TU's non-retail copy of ?erase@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEPADPAD0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> char * basic_string<char,char_traits<char>,allocator<char> >::erase(char *,char *); }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@G@_STL@@QBEPAGIPBX@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int,void const *) const; }
// Suppress this TU's non-retail copy of ?_M_deallocate_block@?$_String_base@DV?$allocator@D@_STL@@@_STL@@QAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void _String_base<char,allocator<char> >::_M_deallocate_block(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@G@_STL@@QBEXPAGI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> void allocator<unsigned short>::deallocate(unsigned short *,unsigned int) const; }
template<typename T> inline bool StringBase<T>::isEmpty() const throw() { return !m_data || !m_data->length; }

struct PeerRequest
{
	PeerRequest();
	~PeerRequest();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union
	{
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
		struct { bool action; } msgAction;
	};
};

struct PeerRequestQueue6
{
	virtual void f0();
	virtual void f1();
	virtual void f2();
	virtual void f3();
	virtual void f4();
	virtual void f5();
	virtual void addRequest(PeerRequest *rec);
};

class GameSpyPeerMessageQueueInterface;
extern GameSpyPeerMessageQueueInterface *TheGameSpyPeerMessageQueue;
#define TheGameSpyPeerMessageQueue ((PeerRequestQueue6 *)TheGameSpyPeerMessageQueue)


// Retail consumes begin/end pointers to profile IDs; the full selector type is unproven.
struct SelPair {
  int *first; int *last;
  int *begin() const { return first; }
  int *end() const { return last; }
  unsigned size() const { return last-first; }
  bool empty() const { return first==last; }
};

struct PlayerInfo
{
	AsciiString m_name;
};

class Rva001EFD9C
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d10(); virtual void d11();
	virtual int getCurrentGroupRoom();
	virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16();
	virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20();
	virtual void d21();
	virtual PlayerInfo *rva00382CCE(const char *name);
	virtual PlayerInfo *rva00382D0A(int profileID);
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28();
	virtual AsciiString getLocalName();
	bool rva001EFD9C(UnicodeString message, bool isAction, const SelPair *sels);
};

extern Rva001EFD9C *TheGameSpyInfo;

bool Rva001EFD9C::rva001EFD9C(UnicodeString message, bool isAction, const SelPair *sels)
{
	getCurrentGroupRoom();
	message.trim();
	if (message.isEmpty())
		return false;
	PeerRequest rec;
	rec.unknown_10 = message.str();
	if (sels == 0 || sels->size() == 0)
	{
		rec.msgAction.action = isAction;
		rec.unknown_00 = 3;
		TheGameSpyPeerMessageQueue->addRequest(&rec);
		return false;
	}
	AsciiString names;
	PlayerInfo *pi = TheGameSpyInfo->rva00382CCE(TheGameSpyInfo->getLocalName().str());
	if (pi)
		names.format("%s", pi->m_name.str());
	else
		names.format("%s", TheGameSpyInfo->getLocalName().str());
	for (int *it = sels->begin(); it != sels->end(); ++it)
	{
		pi = TheGameSpyInfo->rva00382D0A(*it);
		if (!pi)
			continue;
		AsciiString tmp;
		tmp.format(",%s", pi->m_name.str());
		names.concat(tmp);
	}
	if (!names.isEmpty())
	{
		rec.unknown_04 = names.str();
		rec.msgAction.action = isAction;
		rec.unknown_00 = 2;
		TheGameSpyPeerMessageQueue->addRequest(&rec);
	}
	return true;
}
