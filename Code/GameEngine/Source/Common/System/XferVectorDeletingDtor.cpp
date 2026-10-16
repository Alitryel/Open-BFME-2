// cl: /O1 /DNDEBUG /MD /EHsc
//
// Xfer's vector deleting destructor (??_E, 0x00005422, slot 0 of the vtable
// at 0x00BBB910), moved out of VectorDeletingDtorsV07.cpp. For an array delete
// (flag bit 1) it runs the eh vector destructor iterator (0x00629110) with the
// out-of-line copy of ~Xfer (0x000053E7) and the element size 4, then frees
// through operator delete[] (0x0002FD80); for a single object the destructor
// is inlined (one vptr store) before operator delete (0x0002FD60).
//
// Why a unit of its own: the vtable this TU emits has to be Xfer.cpp's 39
// slots, five of them _purecall, so this view is abstract like Xfer.cpp's
// and cannot be array-newed; naming the vector deleting destructor directly
// makes cl emit it all the same. cl then also emits ??_GXfer with the inlined
// destructor, which is not the ledger's ??_GXfer (0x0060C8B1 calls ~Xfer), and
// link.exe keeps the first ??_GXfer in link order. A unit placed by this body's
// address (0x00005422) sorts after Xfer.cpp (0x000053DE), so Xfer.cpp's copy is
// the one kept; V07, whose ModuleTemplate body sorts first, could not host it.

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

class Snapshot;
class AsciiString;
class UnicodeString;
class PooledString;
class Coord2D;
class XferUnknown11;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;

// upstream layout: Xfer.cpp's Xfer. Every virtual is declared in Xfer.cpp's
// order so this TU's vtable COMDAT is the same as Xfer.cpp's copy.
class Xfer
{
public:
	class Version;

	// The constructor stays Xfer.cpp's (0x000053DE): declared only, so this TU
	// emits no competing copy of it.
	Xfer();
	virtual ~Xfer() {}

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);

	virtual Xfer &XferEnum(const char *name, void *data, unsigned int size);

protected:
	virtual void XferData(unsigned int type, void *data, unsigned int size) = 0;
};

// ?<bfmeXferVectorDeleteAnchor> absent-from-retail
void bfmeXferVectorDeleteAnchor(Xfer *xfer)
{
	xfer->Xfer::__vecDelDtor(3);
}
