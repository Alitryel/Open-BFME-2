// cl: /O1 /G7 /DNDEBUG /MD /EHsc
//
// Keyboard constructor (retail 0x00232920, 86 bytes), destructor
// ??1Keyboard@@UAE@XZ (0x00232976, 65 bytes), its scalar deleting
// destructor (0x002329B7, 28 bytes) and Keyboard::isShift (0x00232683,
// 19 bytes). These rows were labelled AIPlayer until the vtable they install,
// 0x00BE81F0, was identified as Keyboard's: its slots 1/10/15 are the matched
// Keyboard::init/update/createStreamMessages (KeyboardInitUpdate.cpp), slots
// 14 and 16 are pure (Zero Hour's getCapsState and getKey), and the derived
// table 0x00BC8688 (DirectInputKeyboard, Win32DIKeyboard.cpp) fills them with
// GetKeyState(VK_CAPITAL) and the DirectInput getKey. The real AIPlayer is the
// vtable 0x00C62DC8 family at 0x004F....
//
// Layout (read off retail; member names are Zero Hour's
// GameEngine/Include/GameClient/Keyboard.h, matched by role):
// - +0x0C m_modifiers (KEY_STATE_* word; the DirectInputKeyboard constructor
//   sets KEY_STATE_CAPSLOCK 0x0200 there), +0x0E m_shift2Key.
// - +0x10 the key list. Zero Hour has KeyboardIO m_keys[256]; BFME2 keeps a
//   vector instead (createStreamMessages walks +0x10..+0x14 and
//   checkKeyRepeat push_backs 8-byte KeyboardIO records). It is modelled as
//   its _Vector_base subobject with a minimal local allocator: retail inlines
//   vector() and only the _Base call (folded 0x00211E58) remains out of line.
//   The allocator needs a user-provided empty constructor; an implicit one
//   makes the compiler zero the stack temp (extra stosb plus a frame). The
//   element type keeps its pinned placeholder spelling (BfmeE16).
// - +0x1C m_keyStatus[256] (8-byte KeyboardIO), +0x81C m_keyNames[256]
//   (three WideChars each), +0xE1C m_inputFrame.
// - The destructor frees the vector's start pointer with the C++-linkage free
//   (0x00030830): the inlined POD-vector deallocate. It then chains to the
//   SubsystemInterface destructor (ledger SubsystemInterface,
//   0x001B4E74). The C++ linkage is load-bearing: it emits the unwind state
//   stores retail carries, while an extern "C" import would call through
//   the IAT.
// - isShift is Zero Hour's (LSHIFT 0x10 | RSHIFT 0x20, or SHIFT2 0x0400);
//   the name is inferred from that body shape, and BFME2 returns a byte bool
//   here where Zero Hour's Bool is an Int.
// - translateKey (0x00232763, 445 bytes) is Zero Hour's Keyboard::translateKey
//   with BFME2's offsets: modifier scancode switch, shift2 key, then the
//   shifted2 / shifted / standard key name. Two retail facts shape it:
//   getKeyStateBit(key, bit) is Zero Hour's out-of-line (state & bit) ? 1 : 0
//   (retail 0x0023262C, rowed as a gap body), auto-inlined here, which gives
//   retail's shr/test bit tests; and isShift must be compiled in this unit
//   before translateKey: the compiler then knows isShift leaves ecx intact
//   and calls getCapsState (vtable slot 14, pure in Keyboard) without
//   reloading this, as retail does.

// ??0?$allocator@UBfmeE16@@@_STL@@QAE@XZ present-unmatched
extern "C" void *memset(void *s, int c, unsigned n) throw();
extern "C" void __cdecl free(void *block) throw(...);

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

// Ledger name of SubsystemInterface (vptr, +0x04, AsciiString at +0x08).
class SubsystemInterface
{
public:
	SubsystemInterface() throw();
	virtual ~SubsystemInterface();

private:
	char m_pad04[4];
	AsciiStringMember m_member08;
};

#include "../../../../Libraries/Include/Lib/BfmeE16.h"

namespace _STL
{

template <class Element> class allocator
{
public:
	allocator() {}
};

template <class Item, class Alloc> class _Vector_base
{
public:
	_Vector_base(const Alloc &alloc) throw();
	void *_M_start;
	void *_M_finish;
	void *_M_end;
};

}

typedef unsigned char UnsignedByte;
typedef unsigned short UnsignedShort;
typedef unsigned int UnsignedInt;
typedef unsigned short WideChar;
typedef int Int;

// Zero Hour's GameClient/Keyboard.h KeyboardIO (8 bytes).
struct KeyboardIO
{
	enum StatusType
	{
		STATUS_UNUSED = 0x00,
		STATUS_USED = 0x01
	};

	UnsignedByte key;
	UnsignedByte status;
	UnsignedShort state;
	UnsignedInt sequence;
};

enum
{
	KEY_STATE_NONE = 0x0000,
	KEY_STATE_DOWN = 0x0002,
	KEY_STATE_LCONTROL = 0x0004,
	KEY_STATE_RCONTROL = 0x0008,
	KEY_STATE_LALT = 0x0040,
	KEY_STATE_RALT = 0x0080,
	KEY_STATE_LSHIFT = 0x0010,
	KEY_STATE_RSHIFT = 0x0020,
	KEY_STATE_CAPSLOCK = 0x0200,
	KEY_STATE_SHIFT2 = 0x0400
};

// Zero Hour's KeyDefType scancodes (the values retail's dispatch tests).
enum
{
	KEY_NONE = 0x00,
	KEY_LCTRL = 0x1D,
	KEY_LSHIFT = 0x2A,
	KEY_RSHIFT = 0x36,
	KEY_LALT = 0x38,
	KEY_CAPS = 0x3A,
	KEY_RCTRL = 0x9D,
	KEY_RALT = 0xB8
};

extern "C" __declspec(dllimport) int __cdecl iswalpha(WideChar c);

// Slot view for Keyboard's pure getCapsState (vtable slot 14, +0x38);
// DirectInputKeyboard fills it with GetKeyState(VK_CAPITAL). Only the slot
// is used; nothing here is defined or emitted.
class KeyboardCapsView
{
public:
#define V(n) virtual void pad##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07)
	V(08) V(09) V(10) V(11) V(12) V(13)
#undef V
	virtual bool getCapsState();
};

class Keyboard : public SubsystemInterface
{
public:
	Keyboard();
	virtual ~Keyboard();

	bool isShift();
	bool isCtrl();
	bool isAlt();
	WideChar translateKey(WideChar keyCode);

	// Zero Hour's accessors; retail emits them out of line (0x00232620,
	// 0x0023262C, 0x00232660) and inlines them here.
	// 0x00232620 (12B, RET4): the status byte (+1) of m_keyStatus[key] at +0x1C;
	// this inline copy is retail's out-of-line body.
	UnsignedByte getKeyStatusData(UnsignedByte key) { return m_keyStatus[key].status; }
	bool getKeyStateBit(UnsignedByte key, Int bit) { return (m_keyStatus[key].state & bit) ? 1 : 0; }
	void setKeyStatusData(UnsignedByte key, UnsignedByte data) { m_keyStatus[key].status = data; }

protected:
	unsigned short m_modifiers;									// +0x0C
	unsigned char m_shift2Key;									// +0x0E
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_keys;	// +0x10
	KeyboardIO m_keyStatus[256];								// +0x1C
	struct
	{
		WideChar stdKey;
		WideChar shifted;
		WideChar shifted2;
	} m_keyNames[256];											// +0x81C
	int m_inputFrame;											// +0xE1C
};

Keyboard::Keyboard()
	: SubsystemInterface(), m_keys(_STL::allocator<BfmeE16>())
{
	memset(m_keyStatus, 0, sizeof(m_keyStatus));
	m_modifiers = KEY_STATE_NONE;
	m_shift2Key = KEY_NONE;
	memset(m_keyNames, 0, sizeof(m_keyNames));
	m_inputFrame = 0;
}

Keyboard::~Keyboard()
{
	if (m_keys._M_start)
		free(m_keys._M_start);
}

bool Keyboard::isShift()
{
	unsigned short modifiers = m_modifiers;
	if (((modifiers & (KEY_STATE_LSHIFT | KEY_STATE_RSHIFT)) != 0) || ((modifiers & KEY_STATE_SHIFT2) != 0))
		return true;
	return false;
}

// ZH Keyboard.cpp isCtrl/isAlt guide; native232696..2326AE independently
// tests the left/right modifier bits at0C, with the same two-exit Bool ABI
// as the rowed isShift sibling. WB E9B1A0/E9B1D0 confirm the two word masks.
// The names are inferred from established Keyboard identity and modifier role.
bool Keyboard::isCtrl()
{
 unsigned short modifiers=m_modifiers;
 if ((modifiers & KEY_STATE_LCONTROL) || (modifiers & KEY_STATE_RCONTROL))
  return true;
 return false;
}
bool Keyboard::isAlt()
{
 unsigned short modifiers=m_modifiers;
 if ((modifiers & KEY_STATE_LALT) || (modifiers & KEY_STATE_RALT))
  return true;
 return false;
}

WideChar Keyboard::translateKey(WideChar keyCode)
{
	if (keyCode > 0x00FF)
		return keyCode;

	UnsignedByte ubKeyCode = (UnsignedByte)keyCode;
	switch (ubKeyCode)
	{
		case KEY_CAPS:
			if (getKeyStatusData(KEY_CAPS) == KeyboardIO::STATUS_UNUSED)
			{
				if (getKeyStateBit(KEY_CAPS, KEY_STATE_DOWN))
				{
					if (m_modifiers & KEY_STATE_CAPSLOCK)
						m_modifiers &= ~KEY_STATE_CAPSLOCK;
					else
						m_modifiers |= KEY_STATE_CAPSLOCK;
				}
				setKeyStatusData(KEY_CAPS, KeyboardIO::STATUS_USED);
			}
			return 0;

		case KEY_LSHIFT:
			if (getKeyStateBit(KEY_LSHIFT, KEY_STATE_DOWN))
				m_modifiers |= KEY_STATE_LSHIFT;
			else
				m_modifiers &= ~KEY_STATE_LSHIFT;
			return 0;

		case KEY_RSHIFT:
			if (getKeyStateBit(KEY_RSHIFT, KEY_STATE_DOWN))
				m_modifiers |= KEY_STATE_RSHIFT;
			else
				m_modifiers &= ~KEY_STATE_RSHIFT;
			return 0;

		case KEY_LCTRL:
			if (getKeyStateBit(KEY_LCTRL, KEY_STATE_DOWN))
				m_modifiers |= KEY_STATE_LCONTROL;
			else
				m_modifiers &= ~KEY_STATE_LCONTROL;
			return 0;

		case KEY_RCTRL:
			if (getKeyStateBit(KEY_RCTRL, KEY_STATE_DOWN))
				m_modifiers |= KEY_STATE_RCONTROL;
			else
				m_modifiers &= ~KEY_STATE_RCONTROL;
			return 0;

		case KEY_LALT:
			if (getKeyStateBit(KEY_LALT, KEY_STATE_DOWN))
				m_modifiers |= KEY_STATE_LALT;
			else
				m_modifiers &= ~KEY_STATE_LALT;
			return 0;

		case KEY_RALT:
			if (getKeyStateBit(KEY_RALT, KEY_STATE_DOWN))
				m_modifiers |= KEY_STATE_RALT;
			else
				m_modifiers &= ~KEY_STATE_RALT;
			return 0;

		default:
			if (ubKeyCode == m_shift2Key)
			{
				if (getKeyStateBit(m_shift2Key, KEY_STATE_DOWN))
					m_modifiers |= KEY_STATE_SHIFT2;
				else
					m_modifiers &= ~KEY_STATE_SHIFT2;
				return 0;
			}

			if (m_modifiers & KEY_STATE_SHIFT2)
				return m_keyNames[ubKeyCode].shifted2;

			if (isShift() || ((KeyboardCapsView *)this)->getCapsState() && iswalpha(m_keyNames[ubKeyCode].stdKey))
				return m_keyNames[ubKeyCode].shifted;

			return m_keyNames[ubKeyCode].stdKey;
	}
}
