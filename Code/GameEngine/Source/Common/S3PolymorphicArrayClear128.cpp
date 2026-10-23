// Stride-128 sibling of the S3PolymorphicArrayClear family (see
// S3PolymorphicArrayClear.cpp for the full byte analysis). The four landed
// siblings use strides 28/64/48/56; this TU holds only the 128-byte row
// (?clear@Rva00802A10 @0x66EB40, 81B: 3 bytes longer because `add ebx,0x80`
// needs an imm32). Separate TU because the hook requires a ledger row per
// defined function and the family TU deliberately omits this row.
//
// IDENTITY IS NOT RECOVERED (same caveat as the family TU): the loop calls
// each element's first virtual with a zero flag; whether that destroys or
// resets is not decided by the bytes.

class GenAlloc
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void release( void *block, int flags );
};

extern GenAlloc *Gen007EFFC0();

#define S3_ARRAY_CLEAR( NAME, SIZE )                                      \
	class NAME##Elem                                                      \
	{                                                                     \
	public:                                                               \
		virtual void step( int flags );                                   \
		char m_pad[ SIZE - 4 ];                                           \
	};                                                                    \
	class NAME                                                            \
	{                                                                     \
	public:                                                               \
		void clear();                                                     \
		NAME##Elem *m_array;                                              \
		int m_count;                                                      \
	};                                                                    \
	void NAME::clear()                                                    \
	{                                                                     \
		if( m_array )                                                     \
		{                                                                 \
			for( int i = 0; i < m_count; ++i )                            \
				m_array[ i ].step( 0 );                                   \
			Gen007EFFC0()->release( m_array, 0 );                         \
			m_array = 0;                                                  \
		}                                                                 \
		m_count = 0;                                                      \
	}

S3_ARRAY_CLEAR( Rva00802A10, 128 )

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeRva0066EB40@BfmeSubBZC@@QAEXXZ=?clear@Rva00802A10@@QAEXXZ")
