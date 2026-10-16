// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
//
// ?processGameSpyStatsAuthKeyCommand@BFMEConnectionManager@@QAEXPAX@Z
// retail 0x004CFE24, 149 bytes. Dedicated TU ported from the Open-BFME-1
// donor game/GameEngine/Source/GameNetwork/ConnectionManager_processGameSpyStatsAuthKey.cpp (reference/open-bfme-1 @ 6d943426).
// The donor body does not place at BFME 1's flags; compiled /Os it is
// byte-identical to retail once relocations are masked (unique hit on
// unclaimed .text). Only the placed body is defined here.

typedef unsigned int UnsignedInt;

template <typename T> class StringBase
{
	friend class BFMEConnectionManager;
	friend class GameSpyGameSlot;
	friend class BFMENetGameSpyStatsAuthKeyCommandMsg;

public:
	int getLength() const { return m_data ? m_data->length : 0; }

private:
	StringBase( const StringBase<T> &source );
	~StringBase();

	struct Header
	{
		int refCount;
		unsigned short length;
		unsigned short capacity;
		T data[ 1 ];
	};

	Header *m_data;
};

typedef StringBase<char> AsciiString;

class GameSpyGameSlot
{
public:
	AsciiString getLoginName() const;
	void setLoginName( AsciiString name );
	void setLocale( AsciiString name );
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/GameSpy/StagingRoomGameInfo.h
class GameSpyStagingRoom
{
public:
	GameSpyGameSlot *getGameSpySlot( int index );
};

extern GameSpyStagingRoom *TheGameSpyGame;

class BFMENetGameSpyStatsAuthKeyCommandMsg
{
public:
	UnsignedInt getPlayerID() const { return m_playerID; }
	AsciiString getText1C();
	AsciiString getText20();

private:
	char m_unmodelled_00[ 0x0C ];
	UnsignedInt m_playerID;
};

class BFMEConnectionManager
{
public:
	void processGameSpyStatsAuthKeyCommand( void *command );
};

void BFMEConnectionManager::processGameSpyStatsAuthKeyCommand( void *command )
{
	BFMENetGameSpyStatsAuthKeyCommandMsg *message =
		(BFMENetGameSpyStatsAuthKeyCommandMsg *)command;

	if( message->getPlayerID() < 8 )
	{
		GameSpyGameSlot *slot = TheGameSpyGame->getGameSpySlot( message->getPlayerID() );
		if( slot && slot->getLoginName().getLength() == 0 )
		{
			slot->setLoginName( message->getText1C() );
			slot->setLocale( message->getText20() );
		}
	}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x004CFBC2 reads ?rva004CFBC2@Rva004CFBC2AsciiField@@QAEXVAsciiString@@@Z
#pragma comment(linker, "/alternatename:?setLocale@GameSpyGameSlot@@QAEXV?$StringBase@D@@@Z=?rva004CFBC2@Rva004CFBC2AsciiField@@QAEXVAsciiString@@@Z")
//   0x002D9BC1 reads ?get@Rva002D9BC1AsciiField@@QBE?AVAsciiString@@XZ
#pragma comment(linker, "/alternatename:?getText20@BFMENetGameSpyStatsAuthKeyCommandMsg@@QAE?AV?$StringBase@D@@XZ=?get@Rva002D9BC1AsciiField@@QBE?AVAsciiString@@XZ")
//   0x004CFB8B reads ?rva004CFB8B@Rva004CFB6DAsciiField@@QAEXVAsciiString@@@Z
#pragma comment(linker, "/alternatename:?setLoginName@GameSpyGameSlot@@QAEXV?$StringBase@D@@@Z=?rva004CFB8B@Rva004CFB6DAsciiField@@QAEXVAsciiString@@@Z")
//   0x002D9BA6 reads ?getPath@CDDrive@@UAE?AVAsciiString@@XZ
#pragma comment(linker, "/alternatename:?getText1C@BFMENetGameSpyStatsAuthKeyCommandMsg@@QAE?AV?$StringBase@D@@XZ=?getPath@CDDrive@@UAE?AVAsciiString@@XZ")
//   0x004CFB6D reads ?get@Rva004CFB6DAsciiField@@QBE?AVAsciiString@@XZ
#pragma comment(linker, "/alternatename:?getLoginName@GameSpyGameSlot@@QBE?AV?$StringBase@D@@XZ=?get@Rva004CFB6DAsciiField@@QBE?AVAsciiString@@XZ")
