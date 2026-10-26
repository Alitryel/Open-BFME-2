// Shared BFME 2 receiver for Keyboard.cpp and the key-list resync donor.
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
