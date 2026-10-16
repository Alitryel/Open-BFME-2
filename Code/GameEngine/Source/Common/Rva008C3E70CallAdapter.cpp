// Open-BFME5: clean C++ conversion of the stdcall-to-cdecl adapter.
// Its target 0x006EE6C0 is the rowed AptCharacter property-set worker.

class AptValue;
class EAStringC;
bool rva006EE6C0(AptValue *target, const EAStringC *name, AptValue *value);

void __stdcall rva008C3E70Adapter(int first, int second, int third)
{
	rva006EE6C0((AptValue *)first, (const EAStringC *)second, (AptValue *)third);
}
