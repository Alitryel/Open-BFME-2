// cl: /DNDEBUG /MD
// ??0Rva0060C5FA@@QAE@PAX00@Z @0x0060C5FA (47B):
// Xfer-family ctor with manual vtable: currentBlock -1 at +1c, +4/+8/+0c
// from arg1/arg3/arg2, vtable 0x00C7AF18 stored 5th, then zeroes for the
// Xfer isLoading/stream/blockCount slots at +10/+14/+18. No virtuals
// (manual void* vtable, absolute VA per Snapshot precedent) so no implicit
// vptr store and the retail order falls out of body assignments. Caller
// 0x00409A0C destroys the object via ??1Xfer, so the class dtor is
// implicit. Eight ctor callers. Honest-address name.

// The retail table at RVA 0x0087AF18: 39 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GXfer@@UAEPAXI@Z")();
void __identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?beginBlock@Xfer@@UAEHPBD@Z")();
void __identifier("?endBlock@Xfer@@UAEXXZ")();
void __identifier("?skipBlock@Xfer@@UAEXPBD@Z")();
void __identifier("?skipBadBlock@BlockStreamReader@@QAEXPAXH@Z")();
void __identifier("?XferRawBytes@Xfer@@UAEAAV1@PAXI@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAVVersion@0@@Z")();
void __identifier("??4?$CategoryModuleClassBase@$00$00@FXParticleSystem@@QAEAAV01@ABV01@@Z")();
void __identifier("?bfmeAttach@Gen009D8BD0@@QAEPAV1@PAVBfmePeer@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAURGBAColorInt@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAURGBAColorReal@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAURGBColor@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAURealRange@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAUIRegion2D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAURegion2D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAUICoord2D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAVCoord2D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAUIRegion3D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAURegion3D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAUICoord3D@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAUCoord3DBase@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAVPooledString@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAVUnicodeString@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAVAsciiString@@@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAM@Z")();
void __identifier("??8Xfer@@UAEAAV0@AA_J@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAI@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAH@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAG@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAF@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAE@Z")();
void __identifier("??8Xfer@@UAEAAV0@AAD@Z")();
void __identifier("??8Xfer@@UAEAAV0@AA_N@Z")();
void __identifier("?XferEnum@Xfer@@UAEAAV1@PBDPAXI@Z")();
void __identifier("?XferImpl@XferLoad@@UAEXIPAXI@Z")();
}
extern const void *const g_00C7AF18[39] = {
	(const void *)&__identifier("??_GXfer@@UAEPAXI@Z"), // slot 0 0x0060C8B1
	(const void *)&__identifier("?rva0050B5C6@Rva0050B5C6@@QAE_NXZ"), // slot 1 0x0050B5C6
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 2 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 3 0x0047A699
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 4 0x0047A699
	(const void *)&__identifier("?beginBlock@Xfer@@UAEHPBD@Z"), // slot 5 0x0060C629
	(const void *)&__identifier("?endBlock@Xfer@@UAEXXZ"), // slot 6 0x0060C469
	(const void *)&__identifier("?skipBlock@Xfer@@UAEXPBD@Z"), // slot 7 0x0060C6F6
	(const void *)&__identifier("?skipBadBlock@BlockStreamReader@@QAEXPAXH@Z"), // slot 8 0x0060C4EA
	(const void *)&__identifier("?XferRawBytes@Xfer@@UAEAAV1@PAXI@Z"), // slot 9 0x0060B886
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAVVersion@0@@Z"), // slot 10 0x0060B8D9
	(const void *)&__identifier("??4?$CategoryModuleClassBase@$00$00@FXParticleSystem@@QAEAAV01@ABV01@@Z"), // slot 11 0x001FD28E
	(const void *)&__identifier("?bfmeAttach@Gen009D8BD0@@QAEPAV1@PAVBfmePeer@@@Z"), // slot 12 0x0060C549
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAURGBAColorInt@@@Z"), // slot 13 0x0060BBA9
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAURGBAColorReal@@@Z"), // slot 14 0x0060BB7D
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAURGBColor@@@Z"), // slot 15 0x0060BB51
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAURealRange@@@Z"), // slot 16 0x0060BB25
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAUIRegion2D@@@Z"), // slot 17 0x0060BAE4
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAURegion2D@@@Z"), // slot 18 0x0060BAA3
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAUICoord2D@@@Z"), // slot 19 0x0060BA77
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAVCoord2D@@@Z"), // slot 20 0x0060BA4B
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAUIRegion3D@@@Z"), // slot 21 0x0060BA0A
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAURegion3D@@@Z"), // slot 22 0x0060B9C9
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAUICoord3D@@@Z"), // slot 23 0x0060B99D
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAUCoord3DBase@@@Z"), // slot 24 0x0060B971
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAVPooledString@@@Z"), // slot 25 0x0060C0A0
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAVUnicodeString@@@Z"), // slot 26 0x0060BF9E
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAVAsciiString@@@Z"), // slot 27 0x0060BEA4
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAM@Z"), // slot 28 0x0000554C
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AA_J@Z"), // slot 29 0x000054DC
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAI@Z"), // slot 30 0x000054F8
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAH@Z"), // slot 31 0x000054C0
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAG@Z"), // slot 32 0x00005530
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAF@Z"), // slot 33 0x00005514
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAE@Z"), // slot 34 0x00005488
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AAD@Z"), // slot 35 0x0000546C
	(const void *)&__identifier("??8Xfer@@UAEAAV0@AA_N@Z"), // slot 36 0x000054A4
	(const void *)&__identifier("?XferEnum@Xfer@@UAEAAV1@PBDPAXI@Z"), // slot 37 0x0060BBD5
	(const void *)&__identifier("?XferImpl@XferLoad@@UAEXIPAXI@Z"), // slot 38 0x0060C7AD
};

class Rva0060C5FA
{
public:
	Rva0060C5FA(void *a1, void *a2, void *a3);

private:
	void *m_vtable;
	void *m_04;
	void *m_08;
	void *m_0c;
	bool m_isLoading;
	unsigned char m_pad11[3];
	void *m_stream;
	int m_blockCount;
	int m_currentBlock;
};

Rva0060C5FA::Rva0060C5FA(void *a1, void *a2, void *a3)
{
	m_currentBlock = -1;
	m_04 = a1;
	m_08 = a3;
	m_0c = a2;
	m_vtable = (void *)g_00C7AF18;
	m_isLoading = false;
	m_stream = 0;
	m_blockCount = 0;
}
