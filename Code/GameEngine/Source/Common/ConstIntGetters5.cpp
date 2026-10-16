// Cold-slice B8-imm32 const-int returners without vtable carriage (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters4.cpp (mov eax,<IMM32> / ret) but for
// bodies with no .rdata vtable slot, no direct callers and no branch sources:
// each follows a ret-imm (C2-04-00) and is an unclaimed leaf, so the opaque
// address-derived name witnesses only the address and the returned constant.
// Kept in a fresh TU so this batch does not contend with the hot
// ConstIntGetters4 appends on origin/master. No // cl: line (defaults match
// the frameless 6-byte shape).

// ?Rva00062A52Get@@YAHXZ @ 0x00062a52 (6B): returns 0x0000ffff.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00062A52Get(void)
{
	return 0x0000ffff;
}

// ?Rva0028C77DGet@@YAHXZ @ 0x0028c77d (6B): returns 0x0000009a.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0028C77DGet(void)
{
	return 0x0000009a;
}

// ?Rva004CFAE5Get@@YAHXZ @ 0x004cfae5 (6B): returns 0x00010000.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva004CFAE5Get(void)
{
	return 0x00010000;
}

// ?Rva00007450Get@@YAHXZ @ 0x00007450 (6B): returns -2.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00007450Get(void)
{
	return -2;
}

// ?Rva00018080Get@@YAHXZ @ 0x00018080 (6B): returns INT_MIN.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018080Get(void)
{
	return (int)0x80000000;
}

// ?Rva00018610Get@@YAHXZ @ 0x00018610 (6B): returns INT_MAX.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00018610Get(void)
{
	return 0x7fffffff;
}

// ?Rva00019B50Get@@YAHXZ @ 0x00019b50 (6B): returns 0x7ffffffe.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00019B50Get(void)
{
	return 0x7ffffffe;
}

// ?Rva000454EDGet@@YAHXZ @ 0x000454ed (6B): returns 0x0000024f.
// Follows an idiv helper tail. No direct callers. Opaque address-derived
// name.
int Rva000454EDGet(void)
{
	return 0x0000024f;
}

// ?Rva0024A8D6Get@@YAHXZ @ 0x0024a8d6 (6B): returns 132.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024A8D6Get(void)
{
	return 132;
}

// ?Rva0024B43DGet@@YAHXZ @ 0x0024b43d (6B): returns 135.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024B43DGet(void)
{
	return 135;
}

// ?Rva0024B507Get@@YAHXZ @ 0x0024b507 (6B): returns 142.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024B507Get(void)
{
	return 142;
}

// ?Rva0024C32DGet@@YAHXZ @ 0x0024c32d (6B): returns 133.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024C32DGet(void)
{
	return 133;
}

// ?Rva0024C775Get@@YAHXZ @ 0x0024c775 (6B): returns 8192.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024C775Get(void)
{
	return 8192;
}

// ?Rva0024D51CGet@@YAHXZ @ 0x0024d51c (6B): returns 2048.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024D51CGet(void)
{
	return 2048;
}

// ?Rva0024DCDDGet@@YAHXZ @ 0x0024dcdd (6B): returns 256.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024DCDDGet(void)
{
	return 256;
}

// ?Rva0024DCE3Get@@YAHXZ @ 0x0024dce3 (6B): returns 257.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva0024DCE3Get(void)
{
	return 257;
}

// ?Rva0024FB41Get@@YAHXZ @ 0x0024fb41 (6B): returns 513.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva0024FB41Get(void)
{
	return 513;
}

// ?Rva00250722Get@@YAHXZ @ 0x00250722 (6B): returns 140.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva00250722Get(void)
{
	return 140;
}

// ?Rva002507ECGet@@YAHXZ @ 0x002507ec (6B): returns 131.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva002507ECGet(void)
{
	return 131;
}

// ?Rva00252165Get@@YAHXZ @ 0x00252165 (6B): returns 273.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva00252165Get(void)
{
	return 273;
}

// ?Rva00285B54Get@@YAHXZ @ 0x00285b54 (6B): returns 4095.
// Follows a lea plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00285B54Get(void)
{
	return 4095;
}

// ?Rva00285B5AGet@@YAHXZ @ 0x00285b5a (6B): returns 1023.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00285B5AGet(void)
{
	return 1023;
}

// ?Rva00285B60Get@@YAHXZ @ 0x00285b60 (6B): returns 255.
// Abuts the twin getter above. No direct callers. Opaque
// address-derived name.
int Rva00285B60Get(void)
{
	return 255;
}

// ?Rva002AA2C9Get@@YAHXZ @ 0x002aa2c9 (6B): returns 218.
// Follows an idiv helper tail. No direct callers. Opaque
// address-derived name.
int Rva002AA2C9Get(void)
{
	return 218;
}

// ?Rva0041F286Get@@YAHXZ @ 0x0041f286 (6B): returns 0x00c3b000.
// Follows an x87-load plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0041F286Get(void)
{
	return 0x00c3b000;
}

// ?Rva004D949FGet@@YAHXZ @ 0x004d949f (6B): returns INT_MIN.
// Follows a byte-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva004D949FGet(void)
{
	return (int)0x80000000;
}

// ?Rva00619FF0Get@@YAHXZ @ 0x00619ff0 (6B): returns -17.
// Follows a ret-12 plus int3 run. No direct callers. Opaque
// address-derived name.
int Rva00619FF0Get(void)
{
	return -17;
}

// ?Rva00620170Get@@YAHXZ @ 0x00620170 (6B): returns 32.
// Follows a sar plus ret plus int3 run. No direct callers. Opaque
// address-derived name.
int Rva00620170Get(void)
{
	return 32;
}

// The table addresses below have owned definitions in the data ledger.
// Keep each getter's address-derived identity; no return type is inferred.
extern const char *const ModelConditionNames[];
extern const char *BodyStateNames[];
extern const char *VeterancyLevelNames[];
extern const char *SpecialPowerNames[];
extern const char *g_Va00DD263CNames[];
extern const char *EmotionNames[];
struct FieldParse;
extern const FieldParse g_00C64D60[];

// ?Rva0004546DGet@@YAHXZ @ 0x0004546d (6B): returns 0x00dbaa98.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva0004546DGet(void)
{
	return (int)&ModelConditionNames;
}

// ?Rva000454CEGet@@YAHXZ @ 0x000454ce (6B): returns 0x00da5f30.
// Follows a tiny mov-al returner. No direct callers.
// Opaque address-derived name.
int Rva000454CEGet(void)
{
	return (int)&BodyStateNames;
}

// ?Rva002532CEGet@@YAHXZ @ 0x002532ce (6B): returns 0x00dbaa40.
// Follows an SEH epilogue plus leave plus ret. No direct callers.
// Opaque address-derived name.
int Rva002532CEGet(void)
{
	return (int)&VeterancyLevelNames;
}

// ?Rva003B0FA6Get@@YAHXZ @ 0x003b0fa6 (6B): returns 0x00dc0b40.
// Follows a leave plus ret-4 tail. No direct callers. Opaque
// address-derived name.
int Rva003B0FA6Get(void)
{
	return (int)&SpecialPowerNames;
}

// ?Rva003B31C1Get@@YAHXZ @ 0x003b31c1 (6B): returns 0x00dd263c.
// Follows a pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva003B31C1Get(void)
{
	return (int)&g_Va00DD263CNames;
}

// ?Rva003B321BGet@@YAHXZ @ 0x003b321b (6B): returns 0x00dba9c8.
// Follows a pop plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva003B321BGet(void)
{
	return (int)&EmotionNames;
}

// ?Rva0050B5C9Get@@YAHXZ @ 0x0050b5c9 (6B): returns 0x00c64d60.
// Follows a mov-al plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0050B5C9Get(void)
{
	return (int)&g_00C64D60;
}


// The two field-table addresses below now have named providers. These
// data-only declarations make no claim about either manager instance layout.
// BF1 575ba2b uses the same named-table declaration pattern in
// Rva000C25F0Get.cpp and the related field-table getter units.
struct FieldParse;
class MultiplayerSettings { public: static const FieldParse m_multiplayerSettingsFieldParseTable[]; };
class ShellMenuSchemeManager { public: static const FieldParse m_shellMenuSchemeFieldParseTable[]; };

// ?Rva001EF361Get@@YAHXZ @ 0x001ef361 (6B): returns 0x00c18fb0.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001EF361Get(void)
{
	return reinterpret_cast<int>(MultiplayerSettings::m_multiplayerSettingsFieldParseTable);
}

// ?Rva0020049BGet@@YAHXZ @ 0x0020049b (6B): returns 0x00be29ec.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva0020049BGet(void)
{
	return reinterpret_cast<int>(ShellMenuSchemeManager::m_shellMenuSchemeFieldParseTable);
}

// Moved back from ConstIntGetters5Addr.cpp: their constants now name the globals the
// ledger defines there (declaration-only views; no layout is asserted).
extern const FieldParse TheFXListFieldParse[];
extern const FieldParse CombatChainDefinitionFieldParse[];
extern const FieldParse BrutalDifficultyCheatsFieldParse[];
extern const FieldParse DifficultyTuningFieldParse[];
extern const FieldParse BfmeBonusForLevelFieldTable[];
extern const FieldParse Rva00418AC6FieldParseTable[];
extern const FieldParse FieldTable002CC8A4[];
extern const FieldParse g_00C3BC20[];
class Rva00534E13
{
public:
    static const FieldParse fieldTable[];
};
class WaterSetting
{
public:
    static const FieldParse m_waterSettingFieldParseTable[];
};
struct SaveDate;
extern SaveDate BfmeINIReadTimestamp;
struct _GUID;
extern _GUID g_bfmeIidTSA;
class Dict;
class MapObject
{
public:
    static Dict TheWorldDict;
};

// ?Rva001DFAA0Get@@YAHXZ @ 0x001dfaa0 (6B): returns 0x00bdc720.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva001DFAA0Get(void)
{
	return (int)TheFXListFieldParse;
}

// ?Rva002A8922Get@@YAHXZ @ 0x002a8922 (6B): returns 0x00bfd804.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva002A8922Get(void)
{
	return (int)CombatChainDefinitionFieldParse;
}

// ?Rva002A893FGet@@YAHXZ @ 0x002a893f (6B): returns 0x00bfd85c.
// Follows a near ret (BrutalDifficultyCheats ctor tail), no .rdata vtable
// slot, no direct callers, no branch sources. Opaque address-derived name.
// The constant is the BrutalDifficultyCheats sub-table also pushed as an
// immediate by the rowed parser at 0x002a898a.
int Rva002A893FGet(void)
{
	return (int)BrutalDifficultyCheatsFieldParse;
}

// ?Rva002A88BBGet@@YAHXZ @ 0x002a88bb (6B): returns 0x00bfd768.
// Abuts the probability parser at 0x002a8845 (ends +118) and a twin getter
// below. Opaque address-derived name. The constant is the DifficultyTuning
// sub-table also pushed as an immediate by the rowed parser at 0x002a89d2.
int Rva002A88BBGet(void)
{
	return (int)DifficultyTuningFieldParse;
}

// ?Rva00417AE3Get@@YAHXZ @ 0x00417ae3 (6B): returns 0x00c3a658.
// Follows an SSE-store plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00417AE3Get(void)
{
	return (int)BfmeBonusForLevelFieldTable;
}

// ?Rva004186DAGet@@YAHXZ @ 0x004186da (6B): returns 0x00c3a8b0.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva004186DAGet(void)
{
	return (int)Rva00418AC6FieldParseTable;
}

// ?Rva00509DA5Get@@YAHXZ @ 0x00509da5 (6B): returns 0x00c64810.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00509DA5Get(void)
{
	return (int)FieldTable002CC8A4;
}

// ?Rva00420965Get@@YAHXZ @ 0x00420965 (6B): returns 0x00c3bc20.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00420965Get(void)
{
	return (int)g_00C3BC20;
}

// ?Rva00534B22Get@@YAHXZ @ 0x00534b22 (6B): returns 0x00c68ae8.
// Follows a ret-4 (prev C2-04-00), no .rdata vtable slot, no direct callers,
// no branch sources. Opaque address-derived name.
int Rva00534B22Get(void)
{
	return (int)Rva00534E13::fieldTable;
}

// ?Rva00200BB4Get@@YAHXZ @ 0x00200bb4 (6B): returns 0x00c07fe0.
// Follows a leave plus ret tail. No direct callers. Opaque
// address-derived name.
int Rva00200BB4Get(void)
{
	return (int)WaterSetting::m_waterSettingFieldParseTable;
}

// ?Rva0002BBC3Get@@YAHXZ @ 0x0002bbc3 (6B): returns 0x00ddf5b8.
// Follows a ret tail, next function starts with mov ecx plus call.
// No direct callers. Opaque address-derived name.
int Rva0002BBC3Get(void)
{
	return (int)&BfmeINIReadTimestamp;
}

// ?Rva00176E30Get@@YAHXZ @ 0x00176e30 (6B): returns 0x00bd4e3c.
// int3-padded both sides, no direct callers. Opaque address-derived name.
int Rva00176E30Get(void)
{
	return (int)&g_bfmeIidTSA;
}

// ?Rva0008514EGet@@YAHXZ @ 0x0008514e (6B): returns 0x00e00944.
// Follows a ret tail. No direct callers. Opaque address-derived name.
int Rva0008514EGet(void)
{
	return (int)&MapObject::TheWorldDict;
}

// Also moved back: the terrain bridge field table TerrainRoads.cpp defines.
class TerrainRoadType
{
public:
    static const FieldParse m_terrainBridgeFieldParseTable[];
};

// ?Rva001DAEB2Get@@YAHXZ @ 0x001daeb2 (6B): returns 0x00c03a28.
// Preceded by int3 padding. No direct callers. Opaque address-derived name.
int Rva001DAEB2Get(void)
{
	return (int)TerrainRoadType::m_terrainBridgeFieldParseTable;
}
