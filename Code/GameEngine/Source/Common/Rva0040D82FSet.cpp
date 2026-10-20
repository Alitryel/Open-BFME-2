// ?setFrom@Rva0040D82FHost@@QAEXPAURva0040D82FArg@@@Z
// partial score=0.95 date=2026-10-05
// cl: /O1 /G7 /arch:SSE /MD
//
// Find-then-erase at retail 0x0040D82F (57B): looks the argument's +0x1C id
// up in the host's +0x14 vector and erases it when found. A thiscall with one
// stack pointer (ret 4): the GameLogic forwarder 0x0023D007 tail-jumps here
// without setting EDX, so the old __fastcall spelling with an unused EDX
// argument was a byte twin, not the contract. Matches under the /O1 /G7
// /arch:SSE of its ArmySummarySystem siblings. Names are address-derived.
class Rva0040D82FSub
{
public:
	int m_first;
};

// The callees are the rowed STLport find<CreateAHeroData **, CreateAHeroData *>
// (0x0060E873) and vector<ObjectID>::erase(iterator) (0x0025BF5D).
class CreateAHeroData;
enum ObjectID { INVALID_ID_0040D82F = 0 };
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

struct Rva0040D82FArg
{
	char m_00[0x1C];
	int m_1C;
};

class Rva0040D82FHost
{
public:
	void setFrom(Rva0040D82FArg *arg); // retail 0x0040D82F

private:
	char m_00[0x14];
	Rva0040D82FSub m_14; // +0x14
	int m_18; // +0x18 current value
};

void Rva0040D82FHost::setFrom(Rva0040D82FArg *arg)
{
	if (arg != 0) {
		int cur = m_18;
		int tmp = arg->m_1C;
		int r = (int)_STL::find<CreateAHeroData **, CreateAHeroData *>((CreateAHeroData **)m_14.m_first, (CreateAHeroData **)cur, *(CreateAHeroData *const *)&tmp);
		if (r != cur) {
			((_STL::vector<ObjectID> *)&m_14)->erase((ObjectID *)r);
		}
	}
}
