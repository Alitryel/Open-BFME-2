// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/System

// BFMECRCWriter::BFMECRCWriter(bool) from the donor GameLogicCRC.cpp. The base
// block-writer ctor is retail 0x0060D1F7 (the donor's own comment fixes the
// ctor/dtor RVAs 0x0060D1F7/0x0060D0B3); full lands at +0x40 and crc at +0x44
// after the base's vptr + 0x3C bytes. Only the target ctor is emitted here; the
// donor's GameLogic::getCRC body is omitted.
class BfmeByteStream;

class XferSave
{
public:
	XferSave();
	virtual ~XferSave();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();

private:
	char data[0x3c];
};

class BFMECRCWriter : public XferSave
{
public:
	BFMECRCWriter( bool full );

	bool full;			// +0x40
	unsigned int crc;	// +0x44
};

BFMECRCWriter::BFMECRCWriter( bool full ) : full( full ), crc( 0 )
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot1@XferSave@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot2@XferSave@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot3@XferSave@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
#pragma comment(linker, "/alternatename:?slot4@XferSave@@UAEXXZ=?IsCRC@Xfer@@UBE_NXZ")
