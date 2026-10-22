// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// ??0Rva007401F6@@QAE@XZ, retail 0x007401E5..0x007401F6 (17 B): the default
// constructor of the class whose rowed destructor (0x007401F6) and deleting
// destructor (0x00740226) sit right after it. Target facts: it stores the
// class vtable 0x00CF15E8 (the table whose first slot is ??_G 0x00740226),
// sets +4 to -1 and clears the string handle at +8. The base constructor's own
// vptr store is dead and removed; the base supplies the -1 at +4.
class Xfer;
class Rva007401F6Base
{
public:
	Rva007401F6Base() : m_04(-1) {}
	virtual ~Rva007401F6Base();
	// Retail vtable 0x00CF15E8 holds __purecall in all three Snapshot slots.
	virtual void crc(Xfer *xfer) = 0;
	virtual void xfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
protected:
	int m_04;
};
struct Rva007401F6Name
{
	Rva007401F6Name() : m_data(0) {}
	~Rva007401F6Name();
	void *m_data;
};
class Rva007401F6 : public Rva007401F6Base
{
public:
	Rva007401F6();
	virtual ~Rva007401F6();
private:
	Rva007401F6Name m_str08;
};
Rva007401F6::Rva007401F6()
{
}
