// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/open-bfme-1/inputs/reference/shims/sweep
// ?Write@Rva00594C12@@QAEHPBDHKG@Z @0x00594C12 109B UDP::Write donor shape via wsock32 sendto
// Evidence: IAT htons htonl sendto WSAGetLastError; callers 0x004D4CC0 0x00595208 0x005952B0; donor udp.cpp Write with retval=-1 giving or edi eax.
#include <winsock.h>

struct SockAddrIn
{
	short sin_family;
	unsigned short sin_port;
	unsigned long sin_addr;
	char sin_zero[8];
};

class Rva00594C12
{
public:
	int Write(const char *buf, int len, unsigned long addr, unsigned short port);
private:
	SOCKET m_socket;
	char m_pad[0x1C - 4];
	int m_lastError;
};
int Rva00594C12::Write(const char *buf, int len, unsigned long addr, unsigned short port)
{
	if (addr == 0 || port == 0)
		return -7;
	SockAddrIn sa;
	sa.sin_port = htons(port);
	sa.sin_addr = htonl(addr);
	sa.sin_family = 2;
	m_lastError = 0;
	int ret = sendto(m_socket, buf, len, 0, reinterpret_cast<const sockaddr *>(&sa), 16);
	if (ret == -1) {
		ret = -1;
		m_lastError = WSAGetLastError();
	}
	return ret;
}
