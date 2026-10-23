// Clean C++ donor: Open-BFME/Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69,
// game/GameEngine/Source/Common/UnclaimedKeyedRecordFinds.cpp (base compiler flags).
// Each BFME2 body independently has an aligned entry after int3 padding,
// returns with ret 4, and ends before int3 padding. Target bytes prove an
// array pointer at this+0, a count at +4, a dword comparison at record+8,
// and record strides 0x30, 0x80, or 0x40. The loop returns the first matching
// record or null; there are no calls or image-address references.
// Donor source supplies this typed loop; native bytes independently constrain
// every used offset and stride. Signedness and the untouched field types are
// structural representations, not recovered class identities. All names use
// the BFME2 body address; the donor's BFME1 address names are not target facts.

#define BFME_KEYED_RECORD_FIND( NAME, RECORD, SIZE )                         \
	struct RECORD                                                            \
	{                                                                        \
		int  m_lead[ 2 ];                                                    \
		int  m_key;                                                          \
		char m_rest[ SIZE - 12 ];                                            \
	};                                                                       \
	class NAME                                                               \
	{                                                                        \
	public:                                                                  \
		RECORD *find( int key ) const;                                       \
                                                                             \
		RECORD *m_records;                                                   \
		int     m_count;                                                     \
	};                                                                       \
	RECORD *NAME::find( int key ) const                                      \
	{                                                                        \
		RECORD *end = m_records + m_count;                                   \
		for ( RECORD *record = m_records; record < end; ++record )           \
		{                                                                    \
			if ( record->m_key == key )                                      \
				return record;                                               \
		}                                                                    \
		return 0;                                                            \
	}

BFME_KEYED_RECORD_FIND( Rva0066D840Table, Rva0066D840Record, 0x30 )
BFME_KEYED_RECORD_FIND( Rva0066EAF0Table, Rva0066EAF0Record, 0x80 )
BFME_KEYED_RECORD_FIND( Rva00663320Table, Rva00663320Record, 0x40 )
