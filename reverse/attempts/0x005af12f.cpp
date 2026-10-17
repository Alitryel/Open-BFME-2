// ?ProcessGameSpyResponse@AptMessengerOnline@@QAE_NPAX@Z
// partial score=0.132 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small table-reached forwarders from .text gaps no ledger row covers
// (seat-3 batch D; see GapBodiesS3A.cpp). Each body is reached only through a
// retail table in .rdata; retail bytes establish every shape. The unrowed
// callees are pinned under address-derived names with the argument counts
// their own `ret` immediates prove.

// --- 0x0035A97E (22B): both arguments and the +0x08 word to the +0x04
// object's 0x0035A8D7 (ret 0xC).
class Rva0035A8D7
{
public:
	void rva0035A8D7(void *a, void *b, void *c);			// 0x0035A8D7
};

class Rva0035A97E
{
public:
	virtual void rva0035A97E(void *a, void *b);
private:
	Rva0035A8D7 *m_target;									// +0x04
	void *m_08;												// +0x08
};
#include <string.h>

class AsciiString;
class UnicodeString;
class AsciiUnicodePair;
class GameSpyGroupRoom;
class GameSpyStagingRoom;
class GameInfo;
class GameSlot;
class GameState;
struct GameSlotConnectInfo;

class AsciiString
{
public:
	AsciiString();
	AsciiString(const char *s);
	AsciiString(const AsciiString &o);
	~AsciiString();
	void set(const char *s);
	void translate(const char *s);
	void concat(const char *s, int n);
	int compare(const char *s) const;
	AsciiString& operator=(const AsciiString &o);
	const char *peek() const;
	char *m_data;
};

class UnicodeString
{
public:
	UnicodeString();
	UnicodeString(const unsigned short *s);
	UnicodeString(const UnicodeString &o);
	~UnicodeString();
	void set(const UnicodeString &o);
	void set(const unsigned short *s);
	void translate(const char *s);
	void format(const UnicodeString *fmt, ...);
	unsigned short *m_data;
};

struct AsciiUnicodePair
{
	AsciiUnicodePair(const AsciiUnicodePair &o);
	AsciiString m_ascii;
	UnicodeString m_uni;
};

class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom();
	~GameSpyGroupRoom();
	AsciiString m_name;
	UnicodeString m_desc;
	int m_a[8];
	int m_b[15];
};

class GameSpyStagingRoom
{
public:
	GameSpyStagingRoom();
	~GameSpyStagingRoom();
	void assign(UnicodeString s);
	void rva005AE5EE(const void *q);
	void rva00381D02(void *p);
	void rva004FDB57(AsciiString s);
	void rva0059F2EB(AsciiString s);
	void setMap(AsciiString s);
	void setInt(int v);
	GameSlot *getSlot(int i);
	char pad[0x1068];
};

class GameSlot
{
public:
	void setPlayerTemplate(int t);
	void setState(int st, UnicodeString s, const GameSlotConnectInfo *c);
	int m_pad[8];
	int m_val;
};

class GameInfo
{
public:
	void dummy();
};

void Rva00381C2DClear(unsigned int v);
void Rva00381C82AddChatText(int a, const UnicodeString &s, int b);
void ChatClear(int v);

class BfmeAptWindowManager
{
public:
	void bfmeSetText(const AsciiString &a, const UnicodeString &u, bool b);
	void rva00225375(const AsciiString &a, const AsciiString &b, bool c);
};

class GameState
{
public:
	AsciiString portableMapPathToRealMapPath(const AsciiString &a) const;
};

struct RespFull
{
	int m_type; // +0
	int m_04; // +4
	int m_08; // +8
	int m_0c; // +c
	int m_10; // +10
	unsigned char _p14[0x14];
	int m_28; // +28
	unsigned char _p2c[0x20];
	int m_4c; // +4c
	unsigned char _p50[0x8];
	int m_58; // +58
	unsigned char _p5c[0x8];
	int m_64; // +64
	unsigned char _p68[0x8];
	int m_70; // +70
	int m_74; // +74
	int m_78; // +78
	int m_7c; // +7c
	unsigned char _p80[0x8];
	int m_88; // +88
	unsigned char _p8c[0x80];
	int m_10c; // +10c
	int m_110; // +110
	int m_114; // +114
	int m_118; // +118
	int m_11c; // +11c
	int m_120; // +120
	unsigned char _p124[0x20];
	int m_144; // +144
	unsigned char _p148[0xC0];
	int m_208; int m_20c; int m_210; int m_214; int m_218;
	unsigned char m_21cbuf[0x28];
	int m_244;
	int m_134; // +spare
};

class AptMessengerOnline
{
public:
	bool ProcessGameSpyResponse(void *p);
};

extern GameInfo *g_GameSpyInfo;
extern BfmeAptWindowManager *g_AptMgr;
extern GameState *g_GameState;
extern int g_CurLobbyIdx;
extern AsciiString *g_JoinStr;
extern UnicodeString *g_EmptyUni;
extern int g_ChatCol;

bool AptMessengerOnline::ProcessGameSpyResponse(void *p)
{
	RespFull *s = (RespFull*)p;
	int t = s->m_type;
	if (t > 10) goto doJoin;
	if (t == 10) goto doJoin;
	if (t == 8 || t == 9) return false;
	switch (t) {
	case 8:
	case 9:
		return false;
	case 0: {
		{
		GameSpyGroupRoom room;
		int v10c = s->m_10c;
		int v114 = s->m_114;
		room.m_name.set((const char*)s->m_04);
		{
		UnicodeString u((const unsigned short*)0xc72870);
		room.m_desc.set(u);
		}
		if (0) throw 1;
		int v118 = s->m_118;
		int v11c = s->m_11c;
		int v110 = s->m_110;
		int v120 = s->m_120;
		{
		AsciiUnicodePair pr(*(AsciiUnicodePair*)&room);
		}
		*(volatile int*)&v10c;
		*(volatile int*)&v110;
		*(volatile int*)&v114;
		*(volatile int*)&v118;
		*(volatile int*)&v11c;
		*(volatile int*)&v120;
		}
		break;
	}
	case 1: {
		UnicodeString u((const unsigned short*)0xbc26dc);
		AsciiString a("APT:CurrentLobbyName");
		g_AptMgr->bfmeSetText(a, u, false);
		g_CurLobbyIdx = -1;
		ChatClear(1);
		break;
	}
	case 2: {
		g_CurLobbyIdx = 0;
		AsciiString a("APT:CurrentLobbyName");
		AsciiString b;
		g_AptMgr->rva00225375(a, b, false);
		ChatClear(1);
		break;
	}
	case 3: {
		break;
	}
	case 4: {
		if (*(char*)&s->m_110) {
			break;
		} else {
			break;
		}
	}
	case 5: {
		UnicodeString u((const unsigned short*)s->m_28);
		AsciiString a((const char*)s->m_10);
		break;
	}
	case 6: {
		break;
	}
	case 7: {
		GameSpyStagingRoom room;
		int v = s->m_110;
		if (v < 0) break;
		if (v > 1) {
			if (v == 2) goto stageCopy;
			if (v == 3) break;
			break;
		}
		if (s->m_214 == 100) {}
		{
			bool same = (s->m_74 - s->m_70) == 0;
			if (!same) {}
			AsciiString cur;
			int eq = cur.compare((const char*)0);
			if (eq) {}
		}
		{
			UnicodeString un((const unsigned short*)s->m_4c);
			room.assign(un);
			room.setInt(s->m_218);
			room.rva005AE5EE(&s->m_11c);
			room.rva00381D02(&s->m_134);
			AsciiString a2((const char*)s->m_58);
			room.rva004FDB57(a2);
			AsciiString a3((const char*)s->m_64);
			room.rva0059F2EB(a3);
			char tmp[0x28];
			memcpy(tmp, (void*)s->m_21cbuf, 0x28);
			AsciiString map((const char*)s->m_7c);
			AsciiString fixed;
			fixed = map;
			AsciiString slash("\\");
			const char *mp = map.peek();
			int len = mp ? (int)*(unsigned short*)(mp+4) : 0;
			for (int i = 0; i < len; ++i) {
				char ch = mp ? *(mp+8+i) : 0;
				if (ch == '/') ch = '\\';
				char b[2]; b[0]=ch; b[1]=0;
				slash.concat(b, 1);
			}
			AsciiString real = g_GameState->portableMapPathToRealMapPath(slash);
			room.setMap(real);
			for (int i = 0; i < 8; ++i) {
				GameSlot *slot = room.getSlot(i);
				if (!slot) continue;
			}
		}
stageCopy:
		{
			GameSpyStagingRoom c(room);
		}
		break;
	}
	default:
		if (t > 10) break;
		break;
	case 10:
		break;
	}
doJoin:
	{
		AsciiString j(*g_JoinStr);
	}
	return true;
}
