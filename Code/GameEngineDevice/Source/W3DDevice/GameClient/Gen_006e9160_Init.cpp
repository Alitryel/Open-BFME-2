// Retail 0x006E9160.  Fill the three-dword output with the three fixed
// runtime values returned by the neighboring global accessors.

namespace Debug_Statistics
{
	int Get_DX8_Vertices( void );
	int Get_DX8_Skin_Vertices( void );
	int Get_Sorting_Vertices( void );
}

struct Gen_006e9160_Triple
{
	int m_0;
	int m_4;
	int m_8;
};

void __stdcall Rva006E9160Init( Gen_006e9160_Triple *output )
{
	output->m_0 = Debug_Statistics::Get_DX8_Vertices();
	output->m_4 = Debug_Statistics::Get_DX8_Skin_Vertices();
	output->m_8 = Debug_Statistics::Get_Sorting_Vertices();
}
