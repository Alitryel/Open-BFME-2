// ?resolveHostAddress@@YGHPBD@Z
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)
struct Rva00885430Hostent { char* h_name; char** h_aliases; short h_addrtype; short h_length; char** h_addr_list; };
extern "C" Rva00885430Hostent* __stdcall gethostbyname(const char* name);
extern int Rva00885430Resolved;
// Rva00885430Resolved: matched references place it at VA 0xe0c78c (zero-filled .bss).
int Rva00885430Resolved;
// Rva00885430Address: matched references place it at VA 0xe0c780; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
char Rva00885430Address[12];
int __stdcall resolveHostAddress(const char* name)
{
	Rva00885430Hostent* host = gethostbyname(name);
	Rva00885430Resolved = 1;
	if (host)
		memcpy(Rva00885430Address, host->h_addr_list[0], host->h_length);
	else
		Rva00885430Address[0] = 0;
	return 0;
}
