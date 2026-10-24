// cl: /GX-
// ?shutdown@AIUpgradeScienceBuilder@@UAEXXZ @0x00597B32 162B: vslot2 of 0x00870C18 clearing two voidptr vectors with slot0+delete then hero remove via TheSkirmishAIManager and ScienceType clear; callers 0x00597BFE
class Player;
class CreateAHeroData;

class Rva002A8F24
{
public:
	void *rva002A8F24(Player *player);
};

class Rva004DFB55
{
public:
	void rva004DFB55(CreateAHeroData *p);
};

extern Rva002A8F24 *TheSkirmishAIManager;

enum ScienceType
{
	SCIENCE_INVALID = 0
};

namespace _STL
{

template <class _Tp> class allocator
{
};

template <class _Tp, class _Alloc> class vector
{
public:
	_Tp *erase(_Tp *first, _Tp *last);
	_Tp *m_start;
	_Tp *m_finish;
	_Tp *m_end;
};

}

class Elem
{
public:
	virtual void *slot0(int x);
};

void __cdecl operator delete(void *p);

class Object;
class BaseA
{
public:
    virtual void Register(Object *, void *) = 0;
    virtual void UnRegister(Object *) = 0;
    virtual ~BaseA();
    int m_04;
    int m_08;
};

class Rva00506B1B
{
public:
    virtual ~Rva00506B1B();
    virtual void rva00597fc5() = 0;
    virtual void shutdown() = 0;
    bool m_04;
};

class AIUpgradeScienceBuilder : public BaseA, public Rva00506B1B
{
public:
    virtual void Register(Object *, void *);
    virtual void UnRegister(Object *);
    virtual ~AIUpgradeScienceBuilder();
    virtual void rva00597fc5();
    virtual void shutdown();
private:
	Player *m_player14;
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > m_sci18;
	_STL::vector<void *, _STL::allocator<void *> > m_upgrades24;
	_STL::vector<void *, _STL::allocator<void *> > m_buildings30;
	int m_tail3c;
};

void AIUpgradeScienceBuilder::shutdown()
{
	void **it = m_upgrades24.m_start;
	void **finish = m_upgrades24.m_finish;
	while (it != finish)
	{
		void *p = *it;
		void *q = 0;
		if (p != 0)
			q = ((Elem *)p)->slot0(0);
		::operator delete(q);
		++it;
	}
	{
		_STL::vector<void *, _STL::allocator<void *> > &r1 = m_upgrades24;
		r1.erase(r1.m_start, r1.m_finish);
	}

	it = m_buildings30.m_start;
	finish = m_buildings30.m_finish;
	while (it != finish)
	{
		void *p = *it;
		void *q = 0;
		if (p != 0)
			q = ((Elem *)p)->slot0(0);
		::operator delete(q);
		++it;
	}
	{
		_STL::vector<void *, _STL::allocator<void *> > &r2 = m_buildings30;
		r2.erase(r2.m_start, r2.m_finish);
	}

	Player *pl = m_player14;
	void *store = TheSkirmishAIManager->rva002A8F24(pl);
	((Rva004DFB55 *)store)->rva004DFB55((CreateAHeroData *)this);
	_STL::vector<ScienceType, _STL::allocator<ScienceType> > *vs = &m_sci18;
	vs->erase(vs->m_start, vs->m_finish);
}
