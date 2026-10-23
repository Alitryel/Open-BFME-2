// cl: /MD
// Sibling of rowed _M_construct_null_aux at 0x00019950 (12B), matched on
// mnemonic shape only -- the identity differs. Retail 0x00038780 (13B)
// stores the byte 1 at +0x9F58 of the singleton whose pointer lives at
// 0x00DE0880. The global reference is a masked DIR32 relocation.
struct Gen_00DE0880
{
	char m_pad[0x9f58];
	unsigned char m_flag;
};

extern "C" Gen_00DE0880 *g_bfme00DE0880;

void __cdecl rva0038780()
{
	g_bfme00DE0880->m_flag = 1;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:_g_bfme00DE0880=?theDebug@@3PAVDebug@@A")
