char g_00DB5A34;

// cl: /MD
// ?Rva000F5B43Get@@YAHXZ @0x000F5B43 19B; two-global init.
// Retail: xor eax,eax / inc eax / mov [0x00DE1F28],(unsigned int)&g_00DB5A34 / mov [0x00DE1F20],eax / ret.
// Target facts: sets data 0x009E1F28 to data 0x009B5A34 and data 0x009E1F20 to 1 then returns 1.
// Callers: none; callees: none.
// The two stored slots are W3DShaders[1] (VA 0x00DE1F28) and
// W3DShadersPassCount[1] (VA 0x00DE1F20), the tables W3DShaderManager.cpp
// defines (its ctor 0x00075480 zeroes both); the stored value is the shroud
// texture shader instance (ShroudTextureShaderSet.cpp: this is that shader's
// init slot), which no unit defines yet, so it stays a literal.
// Not established: owning class name; the function name is address-derived.
class ShaderInterface;
extern ShaderInterface *W3DShaders[2];
extern int W3DShadersPassCount[2];

int Rva000F5B43Get(void)
{
	*(unsigned int *)&W3DShaders[1] = (unsigned int)&g_00DB5A34;
	W3DShadersPassCount[1] = 1;
	return 1;
}
