// ?rva000ABA2F@@YAXXZ
// partial score=0.97 date=2026-10-16
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva000ABA2F@@YAXXZ @0x000ABA2F 339B: the W3D Apt host installs its gAptFuncs
// callbacks (slots VA E17728..E177CC, data ledger names) and calls the 0x006CD1F0
// hook with 0; WB 0x8A5550 (345B) has the same stores in order.
// Finding (target bytes): retail stores every slot as mov [slot],imm32, even the
// nine slots holding 0x4B3FD0 (empty ret) and the two holding 0x4A91D8. MSVC 7.1
// CSEs one repeated symbol into a register (296B with one empty function, 334B
// with AptFree reused), so each slot names a distinct source callback that the
// linker ICF-folded. With distinct symbols this body compiles to retail's 339B
// exactly (relocations aside). Landing needs: a row for 0xAB96D (LoadAnimation),
// and ICF-twin rows for the placeholder callbacks below (nine at 0x000B3FD0,
// one at 0x000A91D8, one at 0x000D43D0, one at 0x000910FB).
class BfmeRefVGO; class Gen0002AB5D; struct Rva000AAD88Arg; class Rva000A923EString;
class BfmeT982; class Rva00786BD0Owner; class Rva007882F0PointerMap;
struct AptRenderTransform; class AptRenderingUnit; class AptValue; struct AptMatrix;
void *Rva000A91D3AptAlloc(unsigned int);
void Rva000A91D8AptFree(void *);
void Rva00783F90StorePackedColor(unsigned int);
void Rva000AB96DLoadAnimation(const char *, BfmeRefVGO);
void Rva007889D0(Gen0002AB5D *);
void Rva000A91DDOnCommand(const char *, int);
void *Rva000A91F1EmptyValue();
void Rva000A91FDSetExtern(const char *, int);
void *rva000A9211(void *);
void *w3dAllocateString(Rva000AAD88Arg *);
void Rva000A923EReleaseString(Rva000A923EString *, unsigned int);
void bfmeGo982C(BfmeT982 *);
void *Rva00786C70Find(Rva00786BD0Owner *, unsigned int);
void Rva00788A00Assign(Rva007882F0PointerMap *, unsigned int, unsigned int);
void *Rva000AA8C3LoadRenderingUnit(Rva00786BD0Owner *, unsigned int);
void Rva000A92B0SetMatrix(const AptRenderTransform *);
void Rva000A994CSetColor(const float *);
void w3dDrawRenderingUnit(AptRenderingUnit *, int);
void w3dCustomControlRender(const char *, int, AptRenderingUnit *, int);
float Rva000A92A2Get();
float Rva000A92A9Get();
// Placeholder ICF twins (no rows yet): retail stores the folded address.
void Rva000B3FD0AptAssertFail(const char *, const char *, int);	// 0x000B3FD0
void Rva000B3FD0AptDebugPrint(const char *, const char *);	// 0x000B3FD0
void Rva000B3FD0AptDebugAddSavedInput();	// 0x000B3FD0
void Rva000B3FD0AptDebugSetScreenGrabPending();	// 0x000B3FD0
void Rva000B3FD0AptFreeSound();	// 0x000B3FD0
void Rva000B3FD0AptStartSound(void *, int);	// 0x000B3FD0
void Rva000B3FD0AptStartSoundStream();	// 0x000B3FD0
void Rva000B3FD0AptFreeTexture();	// 0x000B3FD0
void Rva000B3FD0AptFreeRenderingUnit();	// 0x000B3FD0
void Rva000A91D8AptFreeConstantTable(void *);	// 0x000A91D8
int Rva000D43D0AptLoadSound();	// 0x000D43D0 (ControlBarInput fold)
int Rva000910FBAptPointHitTest();	// 0x000910FB (GameFileClass::Create fold)
void Rva006CD1F0Set(int);

extern void *(__cdecl *g_bfmeAptAllocAtE17728)(unsigned int);
extern void (__cdecl *g_aptFreeCallback)(void *);
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern void (__cdecl *g_aptBackgroundCallback)(int);
extern "C" void (__cdecl *g_bfmeAptLogAtE1773C)(const char *, const char *);
extern "C" void *Rva00891FA0SendRecord;
extern "C" void *Rva00891FA0SendText;
extern void *g_aptLoadAnimationSlot;
extern void *g_aptFreeAnimationSlot;
extern void *g_aptFreeConstantTableSlot;
extern void (__cdecl *g_bfmeAptCommandAtE17758)(const char *, const char *);
extern AptValue *(__cdecl *g_bfmeAptLoadVariablesAtE1775C)(const char *);
extern void (__cdecl *g_bfmeAptSetExternAtE17764)(const char *, const char *);
extern AptValue *(__cdecl *g_bfmeAptGetExternAtE17768)(const char *);
extern void *g_aptAllocateStringSlot;
extern void (__cdecl *g_00E17774)(void *, int);
extern void *g_aptDrawStringSlot;
extern void *g_aptLoadSoundSlot;
extern void *g_aptFreeSoundSlot;
extern void (__cdecl *g_bfmeAptFreeAtE17784)(void *, int);
extern void *g_aptStartSoundStreamSlot;
extern void *g_aptLoadTextureSlot;
extern void *g_aptFreeTextureSlot;
extern void (__cdecl *g_AptBindTexture)(void *, int, void *);
extern void *g_aptLoadRenderingUnitSlot;
extern void *g_aptFreeRenderingUnitSlot;
extern void (__cdecl *g_bfmeAptMatrixCallbackAtE177A0)(AptMatrix *);
extern "C" void *bfmeNotify1209Callback;
extern void *g_aptDrawRenderingUnitSlot;
extern void *g_aptCustomControlRenderSlot;
extern "C" void *pointHitTestCallback;
extern void *g_aptGetStageHeightSlot;
extern void *g_aptGetStageWidthSlot;

void rva000ABA2F()
{
	g_bfmeAptAllocAtE17728 = Rva000A91D3AptAlloc;
	g_aptFreeCallback = Rva000A91D8AptFree;
	g_bfmeAptAssertAtE17734 = Rva000B3FD0AptAssertFail;
	g_aptBackgroundCallback = (void (__cdecl *)(int))Rva00783F90StorePackedColor;
	g_bfmeAptLogAtE1773C = Rva000B3FD0AptDebugPrint;
	Rva00891FA0SendRecord = (void *)Rva000B3FD0AptDebugAddSavedInput;
	Rva00891FA0SendText = (void *)Rva000B3FD0AptDebugSetScreenGrabPending;
	g_aptLoadAnimationSlot = (void *)Rva000AB96DLoadAnimation;
	g_aptFreeAnimationSlot = (void *)Rva007889D0;
	g_aptFreeConstantTableSlot = (void *)Rva000A91D8AptFreeConstantTable;
	g_bfmeAptCommandAtE17758 = (void (__cdecl *)(const char *, const char *))Rva000A91DDOnCommand;
	g_bfmeAptLoadVariablesAtE1775C = (AptValue *(__cdecl *)(const char *))Rva000A91F1EmptyValue;
	g_bfmeAptSetExternAtE17764 = (void (__cdecl *)(const char *, const char *))Rva000A91FDSetExtern;
	g_bfmeAptGetExternAtE17768 = (AptValue *(__cdecl *)(const char *))rva000A9211;
	g_aptAllocateStringSlot = (void *)w3dAllocateString;
	g_00E17774 = (void (__cdecl *)(void *, int))Rva000A923EReleaseString;
	g_aptDrawStringSlot = (void *)bfmeGo982C;
	g_aptLoadSoundSlot = (void *)Rva000D43D0AptLoadSound;
	g_aptFreeSoundSlot = (void *)Rva000B3FD0AptFreeSound;
	g_bfmeAptFreeAtE17784 = Rva000B3FD0AptStartSound;
	g_aptStartSoundStreamSlot = (void *)Rva000B3FD0AptStartSoundStream;
	g_aptLoadTextureSlot = (void *)Rva00786C70Find;
	g_aptFreeTextureSlot = (void *)Rva000B3FD0AptFreeTexture;
	g_AptBindTexture = (void (__cdecl *)(void *, int, void *))Rva00788A00Assign;
	g_aptLoadRenderingUnitSlot = (void *)Rva000AA8C3LoadRenderingUnit;
	g_aptFreeRenderingUnitSlot = (void *)Rva000B3FD0AptFreeRenderingUnit;
	g_bfmeAptMatrixCallbackAtE177A0 = (void (__cdecl *)(AptMatrix *))Rva000A92B0SetMatrix;
	bfmeNotify1209Callback = (void *)Rva000A994CSetColor;
	g_aptDrawRenderingUnitSlot = (void *)w3dDrawRenderingUnit;
	g_aptCustomControlRenderSlot = (void *)w3dCustomControlRender;
	pointHitTestCallback = (void *)Rva000910FBAptPointHitTest;
	g_aptGetStageHeightSlot = (void *)Rva000A92A2Get;
	g_aptGetStageWidthSlot = (void *)Rva000A92A9Get;
	Rva006CD1F0Set(0);
}
