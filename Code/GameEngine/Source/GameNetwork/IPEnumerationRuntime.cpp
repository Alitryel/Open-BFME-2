// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// IPEnumeration destructor: shut down Winsock and release the address list.
// Only WSACleanup is used here; startup and hostname lookup belong to the
// machine-name and address-enumeration bodies.

extern "C" __declspec(dllimport) int __stdcall WSACleanup(void);

void __cdecl operator delete(void *);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/AsciiString.h
// Retail's AsciiString derives from StringBase<char>: its own copy ctor is the
// forwarder at 0x0005EE50 and it holds nothing of its own, so a caller that
// copies a string encodes the base body at 0x00887B60 directly. The delegation
// has to be visible here for this TU to encode the same call.
#include "string_base.h"

#include "ascii_string.h"

// BFME enumeration nodes omit the pooled base word present in Zero Hour;
// their next pointer is at +0x08.
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class EnumeratedIP
{
public:
	EnumeratedIP *getNext() const { return m_next; }

private:
	AsciiString m_text;
	unsigned int m_address;
	EnumeratedIP *m_next;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/IPEnumeration.h
class IPEnumeration
{
public:
	~IPEnumeration();
	AsciiString getMachineName(void);

private:
	EnumeratedIP *m_IPlist;
	bool m_isWinsockInitialized;
};

// IPEnumeration::getMachineName: defined in IPEnumerationGetMachineName.cpp (its row's unit).

IPEnumeration::~IPEnumeration()
{
	if (m_isWinsockInitialized)
	{
		WSACleanup();
		m_isWinsockInitialized = false;
	}

	EnumeratedIP *ip = m_IPlist;
	while (ip != 0)
	{
		ip = ip->getNext();
		delete m_IPlist;
		m_IPlist = ip;
	}
}
