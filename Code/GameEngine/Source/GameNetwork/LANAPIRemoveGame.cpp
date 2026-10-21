// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x00449913, 86 bytes. BFME1 LANAPI::removeGame supplies the linked
// list operation. Target evidence gives the LANAPI game-list head at +0x10,
// LANGameInfo next at +0xF5C, and an additional pointer cleared when it equals
// the removed game. That pointer remains address-derived at 0x00E02EEC.

typedef unsigned char UnsignedByte;
typedef bool Bool;

class LANGameInfo
{
public:
	UnsignedByte m_prefix[0xF5C];
	LANGameInfo *m_next;

	LANGameInfo *getNext( void ) const { return m_next; }
	void setNext( LANGameInfo *next ) { m_next = next; }
};

extern class GameInfo *TheGameInfo;

class LANAPI
{
public:
	virtual void vft( void ) = 0;
	UnsignedByte m_prefix[0x0C];
	LANGameInfo *m_games;

protected:
	void removeGame( LANGameInfo *game );
	Bool ValidateGameInfo( LANGameInfo *game );
};

void LANAPI::removeGame( LANGameInfo *game )
{
	if( (*(LANGameInfo **)&TheGameInfo) == game )
		(*(LANGameInfo **)&TheGameInfo) = 0;

	LANGameInfo *lANGameInfo = m_games;
	if( !game || !lANGameInfo )
		return;
	else if( lANGameInfo == game )
		m_games = lANGameInfo->getNext();
	else
	{
		while( lANGameInfo->getNext() && lANGameInfo->getNext() != game )
			lANGameInfo = lANGameInfo->getNext();
		if( lANGameInfo->getNext() == game )
			lANGameInfo->setNext( game->getNext() );
	}
}

// Retail 0x00449969, 37 bytes. LANAPI game-list membership test over the
// same +0x10 head and +0xF5C next proven by removeGame above. Honest
// address name (protected like removeGame/addGame); three callers in
// unclaimed lobby/game bodies. Unlock lane.
Bool LANAPI::ValidateGameInfo( LANGameInfo *game )
{
	if( game == 0 )
		return false;
	for( LANGameInfo *lANGameInfo = m_games; lANGameInfo != 0; lANGameInfo = lANGameInfo->m_next )
	{
		if( lANGameInfo == game )
			return true;
	}
	return false;
}
