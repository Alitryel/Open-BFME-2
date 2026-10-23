// cl: /DNDEBUG /MD /EHsc
//
// ??_GBase64Pipe@@UAEPAXI@Z, retail 0x00615D70, 30 bytes: slot 0 of the
// Base64Pipe vtable 0x0087C230, whose other slots are the rowed
// Base64Pipe::Flush / Put and the inherited Pipe::Put_To, in Zero Hour's
// Pipe declaration order (~Pipe, Flush, End, Put_To, Put). BFME1 matched the
// same name at the same 30 bytes (0x009E2500) from its
// Base64DeletingDestructors.cpp, the pattern used here: the vtable is only
// emitted where the class is constructed.
//
// ??1Base64Pipe@@UAE@XZ, retail 0x00615900, 5 bytes: the destructor that
// scalar-deleting destructor calls, and nothing else does -- a tail jump to
// the rowed Pipe::~Pipe (0x0061B0A0). Zero Hour's Base64Pipe declares no
// destructor, and only the implicit one compiles to the bare jump (a
// user-declared empty one also restores the vptr first).

class Pipe
{
public:
	Pipe();
	virtual ~Pipe(void);
	virtual int Flush(void);
	virtual int End(void);
	virtual void Put_To(Pipe *pipe);
	virtual int Put(void const *source, int slen);

private:
	Pipe *ChainTo;
	Pipe *ChainFrom;
};

class Base64Pipe : public Pipe
{
public:
	virtual int Flush(void);
	virtual int Put(void const *source, int slen);

private:
	int Control;
	int Counter;
	char CBuffer[4];
	char PBuffer[3];
};

void forceBase64PipeDeletingDestructor(void)
{
	Base64Pipe pipe;
}
