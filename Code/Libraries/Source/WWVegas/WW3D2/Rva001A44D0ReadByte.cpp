// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Native 1A44D0..1A44D8 lies between the preceding setter RET and the
// next byte accessor. Cdecl pointer argument and unsigned EAX result are
// established by MOV EAX,[ESP+4]; MOVZX EAX,byte[EAX]; RET. Owner unproven.
unsigned int Rva001A44D0ReadByte(const unsigned char *value) { return *value; }
