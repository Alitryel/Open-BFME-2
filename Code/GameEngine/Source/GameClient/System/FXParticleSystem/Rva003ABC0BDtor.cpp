// cl: /MD
// ??1Rva005FEA50Base@FXParticleSystem@@UAE@XZ @0x003ABC0B 22B
// Leaf dtor restoring one vptr at +0x1c with null-guarded store then tail-jmp
// to rowed base ??1Rva003AEEB3 0x003A5817. Evidence: neg sbb and idiom matches
// sibling Rva003A5817Dtor plus V3InlineTemplateDtor; caller ??_G deleting dtor.
extern const void *const g_00BBB554[];
class Rva003AEEB3
{
public:
	virtual ~Rva003AEEB3();
};
// FXParticleSystem::Rva005FEA50Base: its constructor 0x003A5856 installs
// the tables 0x0081B5A8 (+0) and 0x0081B598 (+0x1C) whose deleting dtor
// 0x003AEFF6 and adjustor 0x003A588E reach this body.
namespace FXParticleSystem {
class __declspec(novtable) Rva005FEA50Base : public Rva003AEEB3
{
public:
	virtual ~Rva005FEA50Base();
};
}
FXParticleSystem::Rva005FEA50Base::~Rva005FEA50Base()
{
	unsigned char *b1C = this ? (unsigned char *)this + 0x1C : 0;
	*(volatile unsigned int *)b1C = (unsigned int)g_00BBB554;
}
