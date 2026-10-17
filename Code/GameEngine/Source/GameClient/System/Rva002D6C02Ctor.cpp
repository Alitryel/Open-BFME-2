// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// ??0Rva002D6C02@@QAE@XZ @0x002D6C02 26B via baseConstruct pattern from Rva0026201C; callees rowed 0x001B4E63; caller 0x0023A30B; neighbours Anim2D cluster.

// The retail table at RVA 0x0080331C: 14 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva002D6C1C@@UAEPAXI@Z")();
void __identifier("?Rva002D75C6@@YAXXZ")();
void __identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
void __identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?update@Anim2DCollection@@UAEXXZ")();
}
extern "C" const void *const vtbl_00C0331C[14] = {
	(const void *)&__identifier("??_GRva002D6C1C@@UAEPAXI@Z"), // slot 0 0x002D724B
	(const void *)&__identifier("?Rva002D75C6@@YAXXZ"), // slot 1 0x002D75C6
	(const void *)&__identifier("?loadIniFilesFromLegend@SubsystemInterface@@UAE_NXZ"), // slot 2 0x001B5384
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 3 0x000B3FD0
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 4 0x005CB9FF
	(const void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"), // slot 5 0x0047A699
	(const void *)&__identifier("?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z"), // slot 6 0x000D43D0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 7 0x0047A69C
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 8 0x000B3FD0
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 9 0x000B3FD0
	(const void *)&__identifier("?update@Anim2DCollection@@UAEXXZ"), // slot 10 0x002D7267
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 11 0x005CB9FF
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 12 0x000B3FD0
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 13 0x0047A69C
};

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class Rva002D6C02
{
	int m_pad00[3];
	int m_0C;
	int m_10;
public:
	Rva002D6C02();
};

Rva002D6C02::Rva002D6C02()
{
	reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface();
	m_0C = 0;
	m_10 = 0;
	*(void **)this = (void *)((unsigned int)vtbl_00C0331C);
}
