// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva004D6FC4@Rva004D6FC4@@QAEXPAX@Z @0x004D6FC4 273B: xfer of a damage record: nothing for a
// light CRC; then a version block (1, 3), an ObjectID at +4, the +8 field, the damage,
// damage-FX, damage sub and death type enums at +0xC..+0x18, fields at +0x1C..+0x48 (+0x30 through
// the 0x60 slot), the byte flag at +0x21 from version 2 and the +0x64 field from version 3.
// Every call chains the xfer returned by the previous one; the labelled-enum helpers return it
// in EAX. Field types behind the numbered slots are not established.
typedef unsigned char UnsignedByte;

class XferVersion
{
public:
	XferVersion(UnsignedByte first, UnsignedByte version) : m_first(first), m_version(version) {}
	UnsignedByte m_first;
	UnsignedByte m_version;
};

enum ObjectID { INVALID_ID = 0 };

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool slot1(); virtual bool slot2(); virtual bool slot3();
	virtual bool isLightCRC();
	virtual void slot5(); virtual void slot6(); virtual void slot7(); virtual void slot8(); virtual void slot9();
	virtual Xfer &xferVersion(XferVersion *version);
	virtual void slot11(); virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19(); virtual void slot20();
	virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual Xfer &xferSlot24(void *value);
	virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual Xfer &xferSlot28(void *value);
	virtual void slot29();
	virtual Xfer &xferSlot30(void *value);
	virtual void slot31(); virtual void slot32(); virtual void slot33();
	virtual void slot34(); virtual void slot35();
	virtual Xfer &xferSlot36(void *value);
};

void XferObjectID(Xfer *xfer, ObjectID *id);
void XferDamageFXType(Xfer *xfer, int *value);
void XferDamageType(Xfer *xfer, int *value);
void XferDamageSubType(Xfer *xfer, int *value);
void XferDeathType(Xfer *xfer, int *value);
void XferFXTrigger(Xfer *xfer, int *value);

typedef Xfer *(*XferHelperFn)(Xfer *, void *);

class Rva004D6FC4
{
public:
	void rva004D6FC4(void *context);
private:
	int m_00;
	ObjectID m_04;
	int m_08;
	int m_0C, m_10, m_14, m_18;
	int m_1C;
	UnsignedByte m_20, m_21, m_pad22[2];
	int m_24;
	int m_28;
	ObjectID m_2C;
	int m_30;
	int m_pad34[2];
	int m_3C, m_40, m_44, m_48;
	int m_pad4C[6];
	int m_64;
};

void Rva004D6FC4::rva004D6FC4(void *context)
{
	Xfer *xfer = static_cast<Xfer *>(context);
	if (xfer->isLightCRC())
		return;
	XferVersion version(1, 3);
	Xfer *x = ((XferHelperFn)XferDeathType)(
		((XferHelperFn)XferDamageSubType)(
			((XferHelperFn)XferDamageFXType)(
				((XferHelperFn)XferDamageType)(
					&((XferHelperFn)XferObjectID)(&xfer->xferVersion(&version), &m_04)->xferSlot30(&m_08),
					&m_0C),
				&m_10),
			&m_14),
		&m_18);
	x = &x->xferSlot28(&m_1C);
	x = &x->xferSlot36(&m_20);
	x = ((XferHelperFn)XferObjectID)(((XferHelperFn)XferFXTrigger)(&x->xferSlot28(&m_24), &m_28), &m_2C);
	x = &x->xferSlot24(&m_30);
	x = &x->xferSlot28(&m_3C);
	x = &x->xferSlot28(&m_40);
	x = &x->xferSlot28(&m_44);
	x = &x->xferSlot28(&m_48);
	if (version.m_version >= 2)
		xfer->xferSlot36(&m_21);
	if (version.m_version >= 3)
		xfer->xferSlot28(&m_64);
}
