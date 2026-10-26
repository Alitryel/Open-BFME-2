// Shared BFME 2 receiver for Keyboard and its resync/repeat/key-name donors.
// Layout and names retain Keyboard.cpp's retail/donor evidence. This view
// deliberately leaves the other vector and virtual-slot donors unreconciled.
#ifndef BFME2_KEYBOARD_VIEW_H
#define BFME2_KEYBOARD_VIEW_H

#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"
#include "../../../../Libraries/Include/Lib/BfmeE16.h"

class AsciiStringMember
{
public:
	~AsciiStringMember();
};

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

enum
{
	KEY_STATE_NONE = 0x0000,
	KEY_STATE_DOWN = 0x0002,
	KEY_STATE_AUTOREPEAT = 0x0100,
	KEY_STATE_LCONTROL = 0x0004,
	KEY_STATE_RCONTROL = 0x0008,
	KEY_STATE_LALT = 0x0040,
	KEY_STATE_RALT = 0x0080,
	KEY_STATE_LSHIFT = 0x0010,
	KEY_STATE_RSHIFT = 0x0020,
	KEY_STATE_CAPSLOCK = 0x0200,
	KEY_STATE_SHIFT2 = 0x0400
};

// Zero Hour KeyDefs.h values, already used by the retail key-name body.
enum KeyDefType
{
	KEY_NONE = 0x00,
	KEY_ESC = 0x01, KEY_1 = 0x02, KEY_2 = 0x03, KEY_3 = 0x04, KEY_4 = 0x05,
	KEY_5 = 0x06, KEY_6 = 0x07, KEY_7 = 0x08, KEY_8 = 0x09, KEY_9 = 0x0A,
	KEY_0 = 0x0B, KEY_MINUS = 0x0C, KEY_EQUAL = 0x0D, KEY_BACKSPACE = 0x0E,
	KEY_TAB = 0x0F, KEY_Q = 0x10, KEY_W = 0x11, KEY_E = 0x12, KEY_R = 0x13,
	KEY_T = 0x14, KEY_Y = 0x15, KEY_U = 0x16, KEY_I = 0x17, KEY_O = 0x18,
	KEY_P = 0x19, KEY_LBRACKET = 0x1A, KEY_RBRACKET = 0x1B, KEY_ENTER = 0x1C,
	KEY_LCTRL = 0x1D, KEY_A = 0x1E, KEY_S = 0x1F, KEY_D = 0x20, KEY_F = 0x21,
	KEY_G = 0x22, KEY_H = 0x23, KEY_J = 0x24, KEY_K = 0x25, KEY_L = 0x26,
	KEY_SEMICOLON = 0x27, KEY_APOSTROPHE = 0x28, KEY_TICK = 0x29,
	KEY_LSHIFT = 0x2A, KEY_BACKSLASH = 0x2B, KEY_Z = 0x2C, KEY_X = 0x2D,
	KEY_C = 0x2E, KEY_V = 0x2F, KEY_B = 0x30, KEY_N = 0x31, KEY_M = 0x32,
	KEY_COMMA = 0x33, KEY_PERIOD = 0x34, KEY_SLASH = 0x35, KEY_RSHIFT = 0x36,
	KEY_KPSTAR = 0x37, KEY_LALT = 0x38, KEY_SPACE = 0x39, KEY_CAPS = 0x3A,
	KEY_F1 = 0x3B, KEY_F2 = 0x3C, KEY_F3 = 0x3D, KEY_F4 = 0x3E, KEY_F5 = 0x3F,
	KEY_F6 = 0x40, KEY_F7 = 0x41, KEY_F8 = 0x42, KEY_F9 = 0x43, KEY_F10 = 0x44,
	KEY_NUM = 0x45, KEY_SCROLL = 0x46, KEY_KP7 = 0x47, KEY_KP8 = 0x48,
	KEY_KP9 = 0x49, KEY_KPMINUS = 0x4A, KEY_KP4 = 0x4B, KEY_KP5 = 0x4C,
	KEY_KP6 = 0x4D, KEY_KPPLUS = 0x4E, KEY_KP1 = 0x4F, KEY_KP2 = 0x50,
	KEY_KP3 = 0x51, KEY_KP0 = 0x52, KEY_KPDEL = 0x53, KEY_102 = 0x56,
	KEY_F11 = 0x57, KEY_F12 = 0x58, KEY_KPENTER = 0x9C, KEY_RCTRL = 0x9D,
	KEY_KPSLASH = 0xB5, KEY_SYSREQ = 0xB7, KEY_RALT = 0xB8, KEY_HOME = 0xC7,
	KEY_UP = 0xC8, KEY_PGUP = 0xC9, KEY_LEFT = 0xCB, KEY_RIGHT = 0xCD,
	KEY_END = 0xCF, KEY_DOWN = 0xD0, KEY_PGDN = 0xD1, KEY_INS = 0xD2,
	KEY_DEL = 0xD3
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

class Keyboard : public SubsystemInterface
{
public:
	void initKeyNames();
public:
	Keyboard();
public:
	virtual ~Keyboard();
public:
	bool isShift();
public:
	bool isCtrl();
public:
	bool isAlt();
public:
	WideChar translateKey(WideChar keyCode);
public:
	UnsignedByte getKeyStatusData(UnsignedByte key) { return m_keyStatus[key].status; }
public:
	bool getKeyStateBit(UnsignedByte key, Int bit) { return (m_keyStatus[key].state & bit) ? 1 : 0; }
public:
	void setKeyStatusData(UnsignedByte key, UnsignedByte data) { m_keyStatus[key].status = data; }
protected:
	unsigned short m_modifiers;
protected:
	unsigned char m_shift2Key;
protected:
	_STL::_Vector_base<BfmeE16, _STL::allocator<BfmeE16> > m_keys;
protected:
	KeyboardIO m_keyStatus[256];
protected:
	struct
	{
		WideChar stdKey;
		WideChar shifted;
		WideChar shifted2;
	} m_keyNames[256];
protected:
	int m_inputFrame;
public:
	enum { MAX_KEY_STATES = 3 };
public:
	enum { KEY_NAMES_COUNT = 256 };
public:
	WideChar getPrintableKey(UnsignedByte key, Int state);
public:
	bool rva00232643(UnsignedByte key);
public:
	void resetKeys();
public:
	void rva00232A42();
public:
	void rva00232B7B();
protected:
	bool checkKeyRepeat();
private:
	void rva00232AE8();
};

#endif // BFME2_KEYBOARD_VIEW_H
