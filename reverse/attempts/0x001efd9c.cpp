// ?rva001EFD9C@Rva001EFD9C@@QAE_NVUnicodeString@@_NPBUSelPair@@@Z
// partial score=0.9747292418772563 date=2026-10-20
// ?rva001EFD9C@Rva001EFD9C@@QAE_NVUnicodeString@@_NPBUSelPair@@@Z
// partial score=0.9747292418772563 date=2026-10-19
// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /DNDEBUG
// stlport
// Banked recovery: retail 0x001EFD9C..0x001EFFC6, 554 bytes.
// Same resolved 14-byte stack-home swap as the prior best bank, now with
// ordinary count/iterator methods instead of an equal-arm conditional artifact.
// SelPair is only the witnessed begin/end prefix of profile-ID selections;
// no complete container layout, original class name, or capacity is asserted.
// Retail vtable VA0x00C19500 slot64 and WB callgraph identify sendChat;
// address-derived receiver name is retained. PlayerInfo exposes only its
// leading AsciiString. Request ctor/dtor: 0x1EF661/0x1EF723; action at +0x118.
// message.str() must reload after request construction; retail does so.
// Native names uses ebp-0x10, transient strings reuse dead sels at ebp+0x10;
// this bank chooses the opposite homes. All other resolved bytes agree.
// Handoff: reverse/attempt_support/chat-prefix-20261020/readme.md.
#include <string>
#include <vector>

#include "ascii_string.h"
#include "unicode_string.h"
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
	bool ok;
	getCurrentGroupRoom();
	message.trim();
	if (message.isEmpty())
		ok = false;
	else {
		PeerRequest rec;
		rec.unknown_10 = message.str();
		if (sels == 0
			|| sels->size() == 0)
		{
			rec.msgAction.action = isAction;
			rec.unknown_00 = 3;
			TheGameSpyPeerMessageQueue->addRequest(&rec);
			ok = false;
		}
		else
		{
			{
				AsciiString names;
				PlayerInfo *found = TheGameSpyInfo->rva00382CCE(TheGameSpyInfo->getLocalName().str());
				if (found)
					names.format("%s", found->m_name.str());
				else
					names.format("%s", TheGameSpyInfo->getLocalName().str());
				for (int *p = sels->begin(); p != sels->end(); ++p)
				{
					PlayerInfo *info = TheGameSpyInfo->rva00382D0A(*p);
					if (info)
					{
						AsciiString tmp;
						tmp.format(",%s", info->m_name.str());
						names.concat(tmp);
					}
				}
				if (!names.isEmpty())
				{
					rec.unknown_04 = names.str();
					rec.msgAction.action = isAction;
					rec.unknown_00 = 2;
					TheGameSpyPeerMessageQueue->addRequest(&rec);
				}
			}
			ok = true;
		}
	}
	return ok;
}
