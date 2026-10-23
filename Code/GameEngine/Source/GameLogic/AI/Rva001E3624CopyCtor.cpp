// cl: /DNDEBUG /MD
// ??0Overridable@@QAE@ABV0@@Z 0x003664DD 23B copy ctor that resets to defaults ignoring source; vtable 0x00BDDC48 shared with dtor 0x001E3624 and Overridable ctor 0x001E35CA; callers 0x001E4E01 0x001FE369 0x0020D9A3 pass source through; layout +4 0 +8 byte 0 +0xC -1 per RankInfo Rva003B1101 Rva0035CC36 precedents
class Overridable
{
public:
	virtual ~Overridable();
	Overridable(const Overridable &that);
private:
	void *m_next04;
	unsigned char m_alloc08;
	int m_extra0C;
};

Overridable::Overridable(const Overridable &) : m_next04(0), m_alloc08(0), m_extra0C(-1)
{
}
