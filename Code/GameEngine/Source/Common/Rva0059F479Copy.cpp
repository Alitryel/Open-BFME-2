// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// ??0Rva0059F479@@QAE@ABV0@@Z @ 0x0059F479 (29B).
// Copy ctor: int at +0 plus Open2Rec3A4420 at +4 via rowed copy 0x0059F1B8.
// Returns receiver (mov eax esi ret 4) like Open2Records siblings. Caller
// 0x0059FCBB.
class Open2Rec3A4420
{
public:
	Open2Rec3A4420(const Open2Rec3A4420 &other);
};

class Rva0059F479
{
public:
	Rva0059F479(const Rva0059F479 &other);

private:
	int m_00;
	Open2Rec3A4420 m_04;
};

Rva0059F479::Rva0059F479(const Rva0059F479 &other)
	: m_00(other.m_00)
	, m_04(other.m_04)
{
}
