// cl: /O1 /MD
//
// ??0Rva00336BE4Key@@QAE@XZ, retail 0x00326BE6 (6 bytes, shared by ICF with
// AsciiString's default constructor and the other null-pointer constructors).
// LuaScriptEngine::ProcessScriptedEvent (0x00336BE4) constructs its 4-byte
// scripted-event key record by this name before setting it from the event's
// name. Compiled in its own unit: a definition beside its caller changes the
// caller's register allocation. The record type name is structural.
struct Rva00336BE4Key
{
	unsigned key;
	Rva00336BE4Key();
};

Rva00336BE4Key::Rva00336BE4Key() : key(0) {}
