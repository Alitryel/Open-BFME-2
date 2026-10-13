// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /O1 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// HotKey.cpp -- HotKeyManager members at their WorldBuilder home
// (reverse/wb_name_leads.csv: WB's debug build names the file and
// HotKeyManager::translate, 0x01132720); retail supplies the bytes.
//
// Layout (target evidence): two STLport trees keyed by AsciiString at +0x0C
// and +0x18 (header node first, the node's action handle at +0x14), searched
// by the shared AsciiString _M_find worker 0x001F8437; the message-action map
// at +0x24, searched by the int _M_find worker 0x00388F63, whose operator[]
// (0x003596AD) yields the reference-counted action handle that the rowed
// handle assignment 0x002174A4 overwrites.
//
// Structure (donor and inference): Zero Hour's HotKeyTranslator turns a raw
// key-up into an AsciiString through Keyboard::getPrintableKey and runs the
// hot key bound to it; BFME 2 moved that into HotKeyManager::translate, lets
// message types bind actions directly and admits a shift-only chord. The
// action's three probes (vtable +4, +8, +0xC, each given the shift flag) are
// unnamed: the first skips the binding, the second runs it (false: the fail
// sound), the third asks for the success sound.
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/BfmeAudioEventPrefix136.h"
#include "../../Common/GameLogicObjectLookupView.h"
#include <map>

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

typedef int Int;
typedef bool Bool;
typedef unsigned char UnsignedByte;
typedef unsigned short WideChar;

enum GameMessageDisposition
{
	KEEP_MESSAGE,
	DESTROY_MESSAGE
};

extern GameLogic *TheGameLogic;

class InGameUI
{
public:
	virtual void v000(); virtual void v001(); virtual void v002(); virtual void v003();
	virtual void v004(); virtual void v005(); virtual void v006(); virtual void v007();
	virtual void v008(); virtual void v009(); virtual void v010(); virtual void v011();
	virtual void v012(); virtual void v013(); virtual void v014(); virtual void v015();
	virtual void v016(); virtual void v017(); virtual void v018(); virtual void v019();
	virtual void v020(); virtual void v021(); virtual void v022(); virtual void v023();
	virtual void v024(); virtual void v025(); virtual void v026(); virtual void v027();
	virtual void v028(); virtual void v029(); virtual void v030(); virtual void v031();
	virtual void v032(); virtual void v033(); virtual void v034(); virtual void v035();
	virtual void v036(); virtual void v037(); virtual void v038(); virtual void v039();
	virtual void v040(); virtual void v041(); virtual void v042(); virtual void v043();
	virtual void v044(); virtual void v045(); virtual void v046(); virtual void v047();
	virtual void v048(); virtual void v049(); virtual void v050(); virtual void v051();
	virtual void v052(); virtual void v053(); virtual void v054(); virtual void v055();
	virtual void v056(); virtual void v057(); virtual void v058(); virtual void v059();
	virtual void v060(); virtual void v061(); virtual void v062(); virtual void v063();
	virtual void v064(); virtual void v065(); virtual void v066(); virtual void v067();
	virtual void v068(); virtual void v069(); virtual void v070(); virtual void v071();
	virtual void v072(); virtual void v073(); virtual void v074(); virtual void v075();
	virtual void v076(); virtual void v077(); virtual void v078(); virtual void v079();
	virtual void v080(); virtual void v081(); virtual void v082(); virtual void v083();
	virtual void v084(); virtual void v085(); virtual void v086(); virtual void v087();
	virtual void v088(); virtual void v089(); virtual void v090(); virtual void v091();
	virtual void v092(); virtual void v093(); virtual void v094();
	// Slot 95 (+0x17C): true while a menu is up (parseSpellIndex_Thunk.cpp).
	virtual Bool vslot95();
	Bool getInputEnabled() { return m_engineInputEnabled && m_scriptInputEnabled; }
private:
	char m_pad04[0x15 - 0x04];
	Bool m_engineInputEnabled;		// +0x15
	Bool m_scriptInputEnabled;		// +0x16
};
extern InGameUI *TheInGameUI;

class Keyboard
{
public:
	WideChar getPrintableKey(UnsignedByte key, Int state);
};
extern Keyboard *TheKeyboard;

union GameMessageArgumentType
{
	Int integer;
};
class GameMessage
{
public:
	enum Type
	{
		MSG_RAW_KEY_UP = 22
	};
	Type getType() const { return m_type; }
	const GameMessageArgumentType *getArgument(Int argIndex) const;
private:
	char m_pad00[0x10];
	Type m_type;		// +0x10
};

// Zero Hour's KeyDefs.h key states.
enum
{
	KEY_STATE_CONTROL = 0x000C,
	KEY_STATE_ALT = 0x00C0,
	KEY_STATE_SHIFT = 0x0430
};
// Zero Hour's MetaEvent.h modifier mask bits.
enum
{
	CTRL = 0x04,
	SHIFT = 0x10,
	ALT = 0x40
};

// The bound action; slot 0 is the handle's deleting destructor.
class HotKeyAction
{
public:
	virtual void *destroy(unsigned flags);
	virtual Bool vslot01(Bool shift);		// +0x04
	virtual Bool vslot02(Bool shift);		// +0x08
	virtual Bool vslot03(Bool shift);		// +0x0C
	int references;
};

// The reference-counted action handle (rowed under this address name).
struct TreeHintRef00217D4C
{
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &that);	// 0x002174A4
	HotKeyAction *operator->() const { return m_ptr; }

	HotKeyAction *m_ptr;
};

struct HotKeyNode
{
	char m_links[0x10];
	AsciiString m_key;		// +0x10
	TreeHintRef00217D4C m_action;		// +0x14
};
struct HotKeyMessageActionNode
{
	char m_links[0x10];
	Int m_messageType;		// +0x10
	TreeHintRef00217D4C m_action;		// +0x14
};

// The AsciiString-keyed search is STLport's _M_find, rowed at 0x001F8437
// as the map<AsciiString,AsciiString> instantiation; this unit instantiates
// the same COMDAT (byte-identical to that row) through the tree's find.
typedef _STL::pair<const AsciiString, AsciiString> HotKeyStringValue;
typedef _STL::_Rb_tree<AsciiString, HotKeyStringValue, _STL::_Select1st<HotKeyStringValue>,
	_STL::less<AsciiString>, _STL::allocator<HotKeyStringValue> > HotKeyStringTreeView;
// The int-keyed search is STLport's _M_find, which retail folds for every
// int-keyed tree into 0x00388F63 (rowed as the map<int,int> instantiation);
// its body has to be visible here for the frame retail's translate has.
typedef _STL::map<int, int> HotKeyIntMapView;
// The message-action subscript 0x003596AD, rowed in Rva005C6CCC.cpp under
// this address-derived handle type; declared only.
struct TargetRef00217D4C;
struct TreeHintRef003596AD
{
	TargetRef00217D4C *m_ptr;
};
typedef _STL::map<int, TreeHintRef003596AD> TreeHintMap003596AD;
namespace _STL {
template <> TreeHintRef003596AD &TreeHintMap003596AD::operator[](const int &key);
}

class HotKeyMap
{
public:
	__forceinline HotKeyAction *findAction(const AsciiString &key)
	{
		HotKeyNode *node = (HotKeyNode *)((HotKeyStringTreeView *)this)->find(key)._M_node;
		return node == m_header ? 0 : node->m_action.operator->();
	}
private:
	HotKeyNode *m_header;		// +0x00
	int m_count;		// +0x04
	int m_compare;		// +0x08
};

// View of the STLport map from message type to action handle.
class HotKeyMessageActionMap
{
public:
	__forceinline TreeHintRef00217D4C &operator[](const Int &messageType)
	{
		return (TreeHintRef00217D4C &)((TreeHintMap003596AD *)this)->operator[](messageType);
	}
	HotKeyMessageActionNode *find(Int *messageType)
	{
		return (HotKeyMessageActionNode *)((HotKeyIntMapView *)this)->find(*messageType)._M_node;
	}
	HotKeyMessageActionNode *end() const { return m_header; }
private:
	HotKeyMessageActionNode *m_header;		// +0x00
	int m_count;		// +0x04
	int m_compare;		// +0x08
};

class HotKeyManager
{
public:
	Bool executeHotKey(const AsciiString &keyIn, Bool shift);
	GameMessageDisposition translate(const GameMessage *msg);
	void addMessageAction(const TreeHintRef00217D4C &action, Int messageType);
	void rva00358A53();
	void rva00358ACB();
private:
	unsigned char m_pad00[0x0c];
	HotKeyMap m_map;		// +0x0C
	HotKeyMap m_altMap;		// +0x18
	HotKeyMessageActionMap m_messageActionMap;		// +0x24
};

// The audio manager's misc sounds (+0x80 hot key ran, +0x84 hot key failed).
struct HotKeyMiscAudioView
{
	char m_pad00[0x80];
	OpaqueRefElement4 m_hotKeySuccess;		// +0x80
	OpaqueRefElement4 m_hotKeyFail;		// +0x84
};
class AudioManager;
extern AudioManager *TheAudio;
class HotKeyAudioView
{
public:
	virtual void slot0(); virtual void slot1(); virtual void slot2(); virtual void slot3();
	virtual void slot4(); virtual void slot5(); virtual void slot6(); virtual void slot7();
	virtual void slot8(); virtual void slot9(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24();
	// Slot 25 (+0x64), as Player_Radar posts its events.
	virtual void addAudioEvent(const BfmeAudioEventPrefix136 *);
	virtual void slot26(); virtual void slot27(); virtual void slot28(); virtual void slot29();
	virtual void slot30(); virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35(); virtual void slot36(); virtual void slot37();
	virtual void slot38(); virtual void slot39(); virtual void slot40(); virtual void slot41();
	virtual void slot42(); virtual void slot43(); virtual void slot44(); virtual void slot45();
	virtual void slot46(); virtual void slot47(); virtual void slot48(); virtual void slot49();
	virtual void slot50(); virtual void slot51(); virtual void slot52(); virtual void slot53();
	virtual void slot54(); virtual void slot55(); virtual void slot56(); virtual void slot57();
	virtual void slot58(); virtual void slot59(); virtual void slot60(); virtual void slot61();
	virtual void slot62(); virtual void slot63(); virtual void slot64(); virtual void slot65();
	virtual void slot66(); virtual void slot67(); virtual void slot68(); virtual void slot69();
	virtual void slot70(); virtual void slot71(); virtual void slot72(); virtual void slot73();
	virtual void slot74(); virtual void slot75(); virtual void slot76(); virtual void slot77();
	// Slot 78 (+0x138).
	virtual const HotKeyMiscAudioView *getMiscAudio();
};

// Retail 0x00358A53 (120 bytes): the sound of a hot key that ran.
void HotKeyManager::rva00358A53()
{
	if (TheAudio == 0)
		return;
	if (((HotKeyAudioView *)TheAudio)->getMiscAudio() == 0)
		return;
	BfmeAudioEventPrefix136 event(((HotKeyAudioView *)TheAudio)->getMiscAudio()->m_hotKeySuccess, 0);
	((HotKeyAudioView *)TheAudio)->addAudioEvent(&event);
}

// Retail 0x00358ACB (120 bytes): the sound of a hot key that failed.
void HotKeyManager::rva00358ACB()
{
	if (TheAudio == 0)
		return;
	if (((HotKeyAudioView *)TheAudio)->getMiscAudio() == 0)
		return;
	BfmeAudioEventPrefix136 event(((HotKeyAudioView *)TheAudio)->getMiscAudio()->m_hotKeyFail, 0);
	((HotKeyAudioView *)TheAudio)->addAudioEvent(&event);
}

// HotKeyManager::executeHotKey, retail 0x003593E8 (366 bytes; WB 0x01132020):
// the action bound to the key, lower case first, in the plain map and then
// the alternate one; an action that refuses in lower case is retried in
// upper case. Paused games, disabled input and open menus run nothing.
Bool HotKeyManager::executeHotKey(const AsciiString &keyIn, Bool shift)
{
	if (TheGameLogic->isGamePaused() || !TheInGameUI->getInputEnabled() || TheInGameUI->vslot95())
		return false;

	AsciiString key = keyIn;
	key.toLower();
	Bool executed = false;
	Bool failed = false;
	HotKeyAction *action = 0;

	action = m_map.findAction(key);
	if (!action)
		action = m_altMap.findAction(key);
	if (action && !action->vslot01(shift))
	{
		if (action->vslot02(shift))
			executed = true;
		else
			failed = true;
	}

	if (!executed)
	{
		key.toUpper();
		action = m_map.findAction(key);
		if (!action)
			action = m_altMap.findAction(key);
		if (action && !action->vslot01(shift))
		{
			if (action->vslot02(shift))
				executed = true;
			else
				failed = true;
		}
	}

	if (executed)
	{
		if (action->vslot03(shift))
			rva00358A53();
		return true;
	}
	if (failed)
		rva00358ACB();
	return false;
}

// HotKeyManager::translate, retail 0x00359556 (343 bytes; WB 0x01132720): a
// message type bound to an action runs it; otherwise a raw key-up without
// modifiers, or with shift alone, runs the hot key of its printable key.
GameMessageDisposition HotKeyManager::translate(const GameMessage *msg)
{
	Int type = msg->getType();
	HotKeyMessageActionNode *it = m_messageActionMap.find(&type);
	if (it != m_messageActionMap.end())
	{
		TreeHintRef00217D4C &action = it->m_action;
		if (!action->vslot01(false))
		{
			if (action->vslot02(false))
			{
				if (action->vslot03(false))
					rva00358A53();
			}
			else
				rva00358ACB();
			return DESTROY_MESSAGE;
		}
	}

	if (type == GameMessage::MSG_RAW_KEY_UP)
	{
		Int keyState = msg->getArgument(1)->integer;
		Int modState = 0;
		Bool shift = false;
		if (keyState & KEY_STATE_SHIFT)
		{
			modState |= SHIFT;
			shift = true;
		}
		if (keyState & KEY_STATE_CONTROL)
		{
			modState |= CTRL;
			shift = false;
		}
		if (keyState & KEY_STATE_ALT)
		{
			modState |= ALT;
			shift = false;
		}
		if (modState != 0 && !shift)
			return KEEP_MESSAGE;

		WideChar key = TheKeyboard->getPrintableKey((UnsignedByte)msg->getArgument(0)->integer, 0);
		UnicodeString uKey;
		uKey = key;
		AsciiString aKey;
		aKey.translate(uKey);
		if (executeHotKey(aKey, shift))
			return DESTROY_MESSAGE;
	}
	return KEEP_MESSAGE;
}

// HotKeyManager::addMessageAction, retail 0x003597A8 (27 bytes): the action
// is bound to the message type.
void HotKeyManager::addMessageAction(const TreeHintRef00217D4C &action, Int messageType)
{
	m_messageActionMap[messageType] = action;
}
