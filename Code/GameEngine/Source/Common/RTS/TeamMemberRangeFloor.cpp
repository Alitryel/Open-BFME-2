// cl: /O1 /DNDEBUG /MD /arch:SSE
// ?rva0039E84B@Team@@QAEMPAVObject@@@Z, retail 0x0039E84B, 160 bytes (RET4).
// Target evidence: the argument Object's +0x258 range provider (rowed
// 0x002627E8) gives the starting range, else the default at VA 0x00C1ADB8;
// the team member walk (iterate 0x00263864 / advance 0x00263526) lowers it to
// the smallest member range (fld best / fcomip / jbe: a min, not a max), and
// the result is the larger of that minimum and a quarter of the starting
// range (0.25f literal at VA 0x00BBB8D4). Neighbours 0x0039E815/0x0039E8EB.
// Identity: semantic names only; the original Team method is unproven.
class Object;
template<class OBJCLASS>
class DLINK_ITERATOR
{
private:
	OBJCLASS *m_cur;
	unsigned char m_targetAbiState[20];
public:
	void advance();
	bool done() const { return m_cur == 0; }
	OBJCLASS *cur() const { return m_cur; }
};
class Rva002627E8 {
public:
	float rva002627E8() const;
};
class ObjectWithRange {
public:
	char m_pad[0x258];
	Rva002627E8 *m_range;
};
const float g_00C1ADB8 = 999999.0f;  // retail 0x0081ADB8
class Team {
public:
	DLINK_ITERATOR<Object> iterate_TeamMemberList() const;
	float rva0039E84B(Object *obj);
};
float Team::rva0039E84B(Object *obj)
{
	float f = g_00C1ADB8;
	Rva002627E8 *p = ((ObjectWithRange *)obj)->m_range;
	if (p)
		f = p->rva002627E8();
	float best = f;
	for (DLINK_ITERATOR<Object> iter = iterate_TeamMemberList(); !iter.done(); iter.advance()) {
		Object *cur = iter.cur();
		Rva002627E8 *rp = ((ObjectWithRange *)cur)->m_range;
		if (rp == 0)
			continue;
		if (rp->rva002627E8() < best)
			best = rp->rva002627E8();
	}
	float scaled = f * 0.25f;
	f = scaled > best ? scaled : best;
	return f;
}
