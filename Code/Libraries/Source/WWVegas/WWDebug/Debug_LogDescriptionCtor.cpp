// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Debug::LogDescription::LogDescription, retail 0x00038410 (35 bytes).
// Ported from Open-BFME-1 WWDebug/debug_debug.cpp LogDescription (a memberless
// 2-arg ctor forwarding to AddLogGroup), with the BFME2 adaptation proven by
// retail bytes: AddLogGroup is virtual at vtable slot 0xB4 (45), reached
// through the theDebug singleton pointer (see profile_cmd_run_result_functions
// and debug_notify_windowed for the shared convention), so Debug is declared
// with 45 placeholder slots here exactly as in Debug_AddFrameEntry.cpp.
// Dedicated TU so the other Debug TUs keep their matched bodies.

class Debug
{
public:
	// 45 placeholder virtuals place AddLogGroup at slot 0xB4.
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual const char *AddLogGroup(const char *fileOrGroup, const char *descr);

	class LogDescription
	{
	public:
		LogDescription(const char *fileOrGroup, const char *description);
	};
};

extern Debug *theDebug;  // defined in DebugPreStaticInit.cpp


// ??0LogDescription@Debug@@QAE@PBD0@Z
Debug::LogDescription::LogDescription(const char *fileOrGroup, const char *description)
{
	theDebug->AddLogGroup(fileOrGroup, description);
}
