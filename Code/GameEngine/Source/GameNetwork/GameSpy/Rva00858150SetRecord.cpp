// cl: /DNDEBUG /MD /EHsc
//
// BFME 1 donor game/GameEngine/Source/GameNetwork/GameSpy/Rva00858150SmallBodies.cpp,
// body at b1 0x00858150: byte-identical in game.dat once relocation slots are set
// aside, so this is the donor compiled unchanged.
//
// WHAT THE BYTES SHOW (retail 0x00699710, 32 bytes):
//   mov eax,[esp+4] / mov ecx,[esp+8] / mov [eax+0xB48],ecx / mov ecx,[eax+0xAF0]
//   test ecx,ecx / je +7 / push eax / call 0x006A7610 / pop ecx / ret
// The owner is a GameSpy connection whose +0xAF0 record pointer decides whether the
// state-changed notification runs after the +0xB48 field is stored; the callee is a
// cdecl one-argument call to the body this repo already matches at 0x006A7610
// (peer/peerSendStateChanged.c), so it is named by its matched name here rather than
// pinned a second time.
//
// IDENTITY IS NOT RECOVERED for the owner or this setter; the name is derived from
// the BFME 1 address, as the donor itself records. The three sibling bodies of that
// donor are already landed elsewhere: 0x00861050 and 0x00861510 are the chat
// "SETGROUP %s %s" and "KICK %s %s :%s" formatters held by _chatSetChannelGroupA
// (0x006A1F50) and _chatKickUserA (0x006A2410) in GameSpy/chat/chatMain.c, and
// 0x00861020 was under the sweep's size floor and is not served.

extern "C" void piSendStateChanged(void *peer);

struct Rva00858150Owner
{
	char m_head[0xAF0];					// +0x000
	void *m_AF0;						// +0xAF0
	char m_tail[0xB48 - 0xAF4];			// +0xAF4
	void *m_B48;						// +0xB48
};

// decorated name: ?dup_00858150@@YAXPAURva00858150Owner@@PAX@Z
void dup_00858150(Rva00858150Owner *owner, void *value)
{
	owner->m_B48 = value;
	void *record = owner->m_AF0;
	if (record)
		piSendStateChanged(owner);
}
