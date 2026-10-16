// cl: /DNDEBUG /MD /EHsc
// ?cellCallback@Rva002E7261Info@@QAEHPAVPathfindCell@@0HH@Z @0x002E7261 53B
// Cell-line walk callback (previous cell, current cell, x, y) of the walker
// 0x002E8045 in PathfinderCellLineWalks.cpp, which calls it by this pinned name.
// Returns 0 when inner 0x28 matches m_04 else stores word and two ints; caller at 0x002E810A.

class PathfindCell;

struct _Rva002E7261Inner
{
	char m_pad[0x28];
	int m_28;
};

struct _Rva002E7261Arg
{
	_Rva002E7261Inner *m_ptr;
	int m_pad04;
	unsigned short m_w08;
};

class Rva002E7261Info
{
public:
	int cellCallback(PathfindCell *previous, PathfindCell *current, int a, int b);
private:
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

int Rva002E7261Info::cellCallback(PathfindCell *previous, PathfindCell *current, int a, int b)
{
	const _Rva002E7261Arg *p = (const _Rva002E7261Arg *)current;
	int v = p->m_ptr ? p->m_ptr->m_28 : 0;
	if (v != m_04)
	{
		m_08 = p->m_w08;
		m_0C = a;
		m_10 = b;
		return 1;
	}
	return 0;
}
