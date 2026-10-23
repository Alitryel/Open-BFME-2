// cl: /DNDEBUG /MD /Oi-
// Retail RVA 0x00001158: ordinary cdecl tail forwarder to the abs import
// thunk at 0x0062909A (MSVCR71, IAT VA 0x00BBA6D8).
// The descriptive wrapper name is inferred; the callee identity and int(int)
// ABI come from the named import and the bundled MSVC CRT declaration.
extern "C" int __cdecl abs(int);

int absForwarder(int value)
{
    return abs(value);
}
