// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /EHs /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// EmotionNugget::OnDeactivation @ 0x004DD2C0 (457B). Identity: WorldBuilder
// EmotionNugget.cpp OnDeactivation (WB 0x010EAAC0, callgraph lead).
// Model condition 200 is cleared through Object's ModelConditionFlags words at
// +0x10C (WB inlines BitFlags::test/ClearBit; retail tests byte +0x125 bit 0).
// The attribute gate reads TheGameLogic->getFrame() and the entry delay
// through inline getters, as the WB body does (frame read first).
// Deactivation: folds entry delays into local frames through TheGameLogic,
// plays entry FX, nudges AI, applies weapon-set/condition changes and applies
// the entry attribute modifier by name. Evidence: callers at 0x004B0E12,
// 0x004B0EB2, 0x004B15F2, 0x004B1689 pass [EmotionTrackerUpdate+0x7c] as this;
// callees rowed map<int,int>::operator[] 0x0028932C, map<ushort,int> 0x004DD277,
// Object::rva0029439D, GameLogic::findObjectByID 0x00049DC5,
// FXList::doFXObj 0x000B2235, AIUpdateInterface::rva002632E1,
// Object::clearAndSetModelConditionFlagsForHorde/0x0028CFB2/0x0028AE6D, AsciiField::get 0x004DC8E7,
// StringBase::isEmpty 0x00001E2F/releaseBuffer 0x00036410,
// Object::addAttributeModifierToPool (pin); TheGameLogic 0x009FE78C.

#include <map>
#include "ascii_string.h"
template <typename T>
inline bool StringBase<T>::isEmpty() const
{
    return m_data == 0 || m_data->length == 0;
}


struct Gen_lt_00940b40 : public _STL::less<unsigned short> {};

class Object;
class FXList;
class AIUpdateInterface;

#include "../../../Common/GameLogicObjectLookupView.h"
// Suppress this TU's non-retail copy of ??F?$_Rb_tree_iterator@U?$pair@$$CBHH@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHH@_STL@@@2@@_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > > & _Rb_tree_iterator<pair<int const ,int>,_Nonconst_traits<pair<int const ,int> > >::operator--(); }
// Suppress this TU's non-retail copy of ??0?$pair@$$CBGH@_STL@@QAE@ABGABH@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> pair<unsigned short const ,int>::pair(unsigned short const &,int const &); }
// Suppress this TU's non-retail copy of ??R?$less@H@_STL@@QBE_NABH0@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> bool less<int>::operator()(int const &,int const &) const; }
// Suppress this TU's non-retail copy of ?insert_unique@?$_Rb_tree@GU?$pair@$$CBGH@_STL@@U?$_Select1st@U?$pair@$$CBGH@_STL@@@2@UGen:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Gen_lt_00940b40;
namespace _STL { template <> pair<_Rb_tree_iterator<pair<unsigned short const ,int>,_Nonconst_traits<pair<unsigned short const ,int> > >,bool> _Rb_tree<unsigned short,pair<unsigned short const ,int>,_Select1st<pair<unsigned short const ,int> >,Gen_lt_00940b40,allocator<pair<unsigned short const ,int> > >::insert_unique(pair<unsigned short const ,int> const &); }

extern GameLogic *TheGameLogic;

class FXList
{
public:
	void doFXObj(const Object *primary, const Object *secondary) const;
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class AIUpdateInterface
{
public:
	void rva002632E1();
public:
	char m_pad00[0x3C5];
	unsigned char m_byte3C5;
};

class Rva0029439DIface
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual Object *v19();
};

struct ModelConditionFlags
{
	unsigned int m_bits[19];
	// Returns the masked word (WB's BitFlags::test compares it with zero).
	unsigned int test(size_t pos) const { return m_bits[pos / 32] & (1UL << (pos % 32)); }
	void clear(int bit) { m_bits[bit >> 5] &= ~(1 << (bit & 0x1f)); }
};

class Object
{
public:
	void *rva0029439D();
	void clearAndSetModelConditionFlagsForHorde(const int *a, const int *b);
	void rva0028CFB2(const int *a, const int *b);
	void rva0028AE6D();
	bool addAttributeModifierToPool(const AsciiString &name, int value);
public:
	char m_pad00[0x10C];
	ModelConditionFlags m_modelConditionFlags;
	char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai258;
};

class Rva004DC8E7AsciiField
{
public:
	AsciiString get() const;
	int getDelay() const { return m_40; }
public:
	char m_pad00[0x10];
	int m_10;
	int m_14;
	int m_18;
	char m_pad1C[0x38 - 0x1C];
	const FXList *m_fx38;
	AsciiString m_str3C;
	int m_40;
	unsigned char m_flag44;
	char m_pad45[3];
	int m_48;
	int m_4C;
	char m_pad50[0xA0 - 0x50];
	int m_a0;
	char m_padA4[0x138 - 0xA4];
	int m_138;
	char m_pad13C[0x184 - 0x13C];
	unsigned char m_184;
};

class EmotionNugget
{
public:
	void OnDeactivation();
private:
	Object *m_object;
	Rva004DC8E7AsciiField *m_entry;
	int m_id08;
	unsigned short m_key0C;
	char m_pad0E[2];
	unsigned int m_frame10;
	_STL::map<int, int> m_map14;
	_STL::map<unsigned short, int, Gen_lt_00940b40> m_map20;
	int m_2C;
	unsigned int m_start30;
};

void EmotionNugget::OnDeactivation()
{
	if (m_entry->m_10)
		m_frame10 = TheGameLogic->getFrame() + m_entry->m_10;
	if (m_entry->m_14 && m_id08)
	{
		unsigned frame = TheGameLogic->getFrame();
		int duration = m_entry->m_14;
		m_map14[m_id08] = frame + duration;
	}
	if (m_entry->m_18 && m_key0C)
	{
		unsigned int frame = TheGameLogic->getFrame();
		int duration = m_entry->m_18;
		m_map20[m_key0C] = duration + frame;
	}
	if (m_entry->m_fx38)
	{
		Object *obj = m_object;
		void *iface = obj->rva0029439D();
		if (iface)
			obj = ((Rva0029439DIface *)iface)->v19();
		int id = m_id08;
		Object *found = TheGameLogic->findObjectByID((ObjectID)id);
		if (found || !id)
		{
			if (!obj)
				obj = m_object;
			FXList::doFXObj((m_object ? (m_entry->m_fx38) : (m_entry->m_fx38)), obj, found);
		}
	}
	AIUpdateInterface *ai = m_object->m_ai258;
	if (ai)
	{
		int kind = m_entry->m_4C;
		if (!kind || (kind > 1 && kind <= 5))
		{
			ai->rva002632E1();
			if (m_entry->m_184)
				ai->m_byte3C5 = 0;
		}
	{
		void *iface = m_object->rva0029439D();
		if (iface)
			m_object->clearAndSetModelConditionFlagsForHorde(&m_entry->m_a0, &m_entry->m_138);
		else
			m_object->rva0028CFB2(&m_entry->m_a0, &m_entry->m_138);
		Object *object = m_object;
		if (object->m_modelConditionFlags.test(200))
		{
			object->m_modelConditionFlags.clear(200);
			object->rva0028AE6D();
		}
	}
	if (!((const StringBase<char> &)(m_entry->get())).isEmpty() && TheGameLogic->getFrame() >= m_start30 + m_entry->getDelay() && m_entry->m_flag44)
	{
		m_object->addAttributeModifierToPool(m_entry->get(), m_entry->m_48);
	}
	}
}
