// cl: /O1 /DNDEBUG /MD
//
// ?rva002E10BD@Rva002E10BDOwner@@QAEXPAVCreateAHeroData@@@Z @0x002E10BD 65B:
// vector find-erase-forward (thiscall, 1 arg, void). Finds the arg in
// m_1b8 via the rowed _STL::find<CreateAHeroData **> (0x0020E873); if
// present erases it via the rowed vector<void *>::erase (0x001FF51F, the
// ICF-shared erase address) and forwards [arg+0x78] through the rowed
// GameLogic 0x0023D007. Plain begin/end struct to avoid STL codegen
// variance. Exact identities unproven.
class CreateAHeroData;

namespace _STL
{
template <class It, class T> It find(It first, It last, const T &value);
template <class T> class allocator;
template <class T, class A = allocator<T> > class vector
{
public:
	T *erase(T *position);
};
}

class GameLogic
{
public:
	void rva0023D007(int x);
};
extern GameLogic *TheGameLogic;

struct Rva002E10BDVec
{
	void *m_begin;
	void *m_end;
};

class Rva002E10BDOwner
{
public:
	void rva002E10BD(CreateAHeroData *o);
	void rva002E10FE(int p);

private:
	char m_pad[0x1b8];
	Rva002E10BDVec m_1b8;
};

// ?rva002E10BD@Rva002E10BDOwner@@QAEXPAVCreateAHeroData@@@Z
void Rva002E10BDOwner::rva002E10BD(CreateAHeroData *o)
{
	void *end = *(void **)((char *)this + 0x1bc);
	Rva002E10BDVec *v = &m_1b8;
	CreateAHeroData **it = _STL::find<CreateAHeroData **, CreateAHeroData *>((CreateAHeroData **)v->m_begin, (CreateAHeroData **)end, o);
	if (it == end)
		return;
	((_STL::vector<void *> *)v)->erase((void **)it);
	TheGameLogic->rva0023D007(*(const int *)((const char *)o + 0x78));
}

// ?rva002E10FE@Rva002E10BDOwner@@QAEXH@Z
void Rva002E10BDOwner::rva002E10FE(int p)
{
	int o = **(int **)p;
	TheGameLogic->rva0023D007(*(const int *)(o + 0x78));
	Rva002E10BDVec *v = &m_1b8;
	((_STL::vector<void *> *)v)->erase(*(void ***)p);
}
