// cl: /O1 /MD
//
// ?xfer@Locomotor@@MAEXPAVXfer@@@Z, retail 0x00341E2D, 27 bytes: Locomotor's
// snapshot xfer (vtable slot 3, protected virtual as Locomotor.h declares it),
// identical-code-folded with Rva00341E22::xfer (Rva00341E22Xfer.cpp). BFME2's
// Locomotor keeps no xfer state: IsLightCRC early-out via Xfer slot 0x10, then
// Version1 (0x000053EE). Zero Hour's member-by-member body in Locomotor.cpp is
// not retail's. Same flags and Xfer view as the fold owner.

class Xfer
{
public:
	virtual ~Xfer();
	void Version1();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
};

class Locomotor
{
protected:
	virtual void xfer(Xfer *xfer);
};

void Locomotor::xfer(Xfer *xfer)
{
	if (xfer->IsLightCRC())
		return;
	xfer->Version1();
}
