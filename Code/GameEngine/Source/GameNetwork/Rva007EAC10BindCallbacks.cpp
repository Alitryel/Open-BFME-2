// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/Rva007EAC10BindCallbacks.cpp;
// bfme1_sweep ambiguous: byte-identical bodies placed by the BFME1->BFME2 address map at 0x00657BB0, 0x00657CB0, 0x00657D40.
// Addresses in the donor text are BFME1.
class Rva007E9FC0Owner
{
public:
    void begin(int count, void *peer);
};
class Rva007EA320Owner
{
public:
    void bind(void *first, void *second);
};
class Rva007EA380Owner
{
public:
    void bind(void *first, void *second);
};

void __cdecl rva007EAC10BeginCallback(Rva007E9FC0Owner *owner, int count, void *peer)
{
    owner->begin(count, peer);
}

void __cdecl rva007EAD10BindCallback(Rva007EA320Owner *owner, void *first, void *second)
{
    owner->bind(first, second);
}

void __cdecl rva007EADA0BindCallback(Rva007EA380Owner *owner, void *first, void *second)
{
    owner->bind(first, second);
}
