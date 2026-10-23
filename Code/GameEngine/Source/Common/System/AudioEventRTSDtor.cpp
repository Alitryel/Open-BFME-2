// cl: /Ireference/shims/bfme2_ascii /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// ??1ShadowTypeInfo@Shadow@@QAE@XZ, retail 0x000793FA, 53 bytes. Dedicated
// TU (its file name is from the row's earlier, wrong AudioEventRTS name).
//
// Shadow::ShadowTypeInfo teardown destroys its two strings through the
// folded string teardown (0x36410 pin). The retail body follows that shape
// with the usual cookie and state transitions; the class view matches the
// constructor TU (AudioEventRTSCtor.cpp), which gives the identity evidence.
// The real AudioEventRTS has a virtual destructor elsewhere (pinned
// ??1AudioEventRTS@@UAE@XZ), so nothing here stands in for it.

#include "ascii_string.h"

class Shadow
{
public:
	struct ShadowTypeInfo
	{
		~ShadowTypeInfo();

		AsciiString m_first;
		AsciiString m_second;
	};
};

// ??1ShadowTypeInfo@Shadow@@QAE@XZ
Shadow::ShadowTypeInfo::~ShadowTypeInfo()
{
}

// ??1Rva0030AF8FAudioEventRTS@@QAE@XZ @0x0030AF8F 53B: byte-identical to ~ShadowTypeInfo above except its own EH handler
// (formerly the alias dup_0030af8f); its callers bind it through a pin by this name.
struct Rva0030AF8FAudioEventRTS
{
	~Rva0030AF8FAudioEventRTS();

	AsciiString m_first;
	AsciiString m_second;
};

Rva0030AF8FAudioEventRTS::~Rva0030AF8FAudioEventRTS()
{
}

// ??1Rva0046AA69Record@@QAE@XZ @0x00469DCE 53B: byte-identical to ~ShadowTypeInfo above except its own EH handler
// (formerly the alias dup_00469dce); its callers bind it through a pin by this name.
struct Rva0046AA69Record
{
	~Rva0046AA69Record();

	AsciiString m_first;
	AsciiString m_second;
};

Rva0046AA69Record::~Rva0046AA69Record()
{
}
