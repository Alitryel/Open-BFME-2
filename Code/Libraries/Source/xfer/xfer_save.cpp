// cl: /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN
#include <vector>
namespace _STL {
template <> __declspec(dllimport) __forceinline void **vector<void *>::begin() { return this->_M_start; }
template <> __declspec(dllimport) __forceinline size_t vector<void *>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void * &vector<void *>::operator[](size_t n) { return *(this->_M_start + n); }
}
#include <hash_map>
// STLport 4.5.3 reference implementation; key/payload types follow retail.
// Pointer keys and four-byte offsets are native facts; signedness and the
// concrete template spelling remain reconstruction choices.
typedef _STL::pair<const char *, int> XferKeyOffsetPair;
typedef _STL::hashtable<XferKeyOffsetPair, const char *, _STL::hash<const char *>, _STL::_Select1st<XferKeyOffsetPair>, _STL::equal_to<const char *>, _STL::allocator<XferKeyOffsetPair> > XferKeyOffsetTable;
// The separate retail resize provider retains the visible vector operations.
namespace _STL { template <> void XferKeyOffsetTable::resize(unsigned int); }
// Save-side stream transfer and block finalization. The slot-11 recovery
// resumes reverse/attempt_support/0x0060ce41-w4-20261020.md; helper identity
// corrections are documented in xfer-save-60ce41-identity-20261020.md.

extern "C" unsigned int __cdecl strlen(const char *);

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();

	void *text;
	int tag;
};


class BfmeByteStream
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual int write(const void *buffer, int size);
	virtual int skip(int count, int flag);
};

class BfmePositionVector
{
public:
	int *m_begin;
	int *m_end;
	int *m_capacity;

	int &back()
	{
		return m_end[-1];
	}

	void pop_back()
	{
		--m_end;
	}
};

// Interned-string to saved-offset table at +0x2C, proven by native hashing,
// pointer comparison and the four-byte node payload.
// A char-pointer-keyed STLport hash_map; its _M_find, find and operator[]
// bodies are visible, as in retail's TU, so the slot-11 key stays unaliased.
namespace _STL
{
unsigned int __stl_hash_string(const char *str);
}

struct Rva0060CB2BNode
{
	Rva0060CB2BNode *m_next;
	const char *m_key;
	int m_offset;
};

struct Rva0060CB2BIterator
{
	Rva0060CB2BNode *m_cur;
	const void *m_ht;

	Rva0060CB2BIterator(Rva0060CB2BNode *cur, const void *ht)
		: m_cur(cur), m_ht(ht)
	{
	}
};

struct Rva0060CB2BBuckets
{
	void **_M_start;
	void **_M_finish;
	void **_M_end;

	unsigned int size() const
	{
		return (unsigned int)(_M_finish - _M_start);
	}
	void *operator[](unsigned int n) const
	{
		return _M_start[n];
	}
};

class Rva0060CB2B
{
public:
	Rva0060CB2BNode *rva0060CB2B(const char * const &key) const;
	Rva0060CB2BIterator rva0060CB7C(const char * const &key);
	Rva0060CB2BIterator rva0060CC85(const char * const &key);
	int &rva0060CDFD(const char * const &key);

	unsigned int size() const
	{
		return m_numElements;
	}

private:
	int m_00;
	Rva0060CB2BBuckets m_buckets;
	unsigned int m_numElements;
};

__declspec(noinline) inline Rva0060CB2BNode *Rva0060CB2B::rva0060CB2B(const char * const &key) const
{
	const char *k = key;
	unsigned int h = _STL::__stl_hash_string(k);
	unsigned int n = h % m_buckets.size();
	Rva0060CB2BNode *first = (Rva0060CB2BNode *)m_buckets[n];
	for (; first && first->m_key != k; first = first->m_next)
	{
	}
	return first;
}

__declspec(noinline) inline Rva0060CB2BIterator Rva0060CB2B::rva0060CB7C(const char * const &key)
{
	return Rva0060CB2BIterator(rva0060CB2B(key), this);
}

// Retail 0060CC85: map-level iterator forwarding wrapper (ret 8, 20 B).
Rva0060CB2BIterator Rva0060CB2B::rva0060CC85(const char * const &key)
{
	return rva0060CB7C(key);
}

// STLport hash_map::operator[]: find, else insert (key, 0).
__declspec(noinline) inline int &Rva0060CB2B::rva0060CDFD(const char * const &key)
{
	Rva0060CB2BIterator it = rva0060CB7C(key);
	return it.m_cur == 0 ? reinterpret_cast<XferKeyOffsetTable *>(this)->_M_insert(XferKeyOffsetPair(key, int())).second : it.m_cur->m_offset;
}

class Xfer;

// Unidentified slot-11 argument: retail reads only its first field, an
// interned (pointer-compared) string.
class Rva0060CE41Argument
{
public:
	const char *m_text;
};

class XferSave
{
public:
	virtual void XferEnum(void *context, const void *bytes, unsigned int count);
	virtual void endBlock();
	virtual Xfer &rva0060CE41(Rva0060CE41Argument &str);

private:
	BfmeByteStream * volatile m_stream;
	bool m_flag;
	unsigned char m_pad09[3];
	BfmePositionVector m_positions;
	unsigned char m_pad18[0x28 - 0x18];
	int m_28;
	Rva0060CB2B m_table;	// +0x2C
};

void XferSave::XferEnum(void *context, const void *bytes, unsigned int count)
{
	if (m_stream == 0)
		return;

	register const void *block = bytes;
	register unsigned int n = count;
	if (n != 0 && block == 0)
		return;

	if (m_flag && context != 0)
	{
		if (m_stream->write(&context, 4) != 4)
		{
			throw XferException(1, 0);
		}
	}

	if (n != 0)
	{
		if (m_stream->write(block, static_cast<int>(n)) != static_cast<int>(n))
		{
			throw XferException(1, 0);
		}
	}
}

void XferSave::endBlock()
{
	if (m_stream == 0)
		return;
	if (m_positions.m_begin == m_positions.m_end)
		return;

	if (m_flag)
	{
		int marker = 0x45424c4b;
		if (m_stream->write(&marker, 4) != 4)
		{
			throw XferException(1, 0);
		}
	}

	int blockSize = m_positions.back();
	m_positions.pop_back();

	int position = m_stream->skip(0, 1);
	if (position == -1)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(blockSize, 0) != blockSize)
	{
		throw XferException(1, 0);
	}

	if (m_stream->write(&position, 4) != 4)
	{
		throw XferException(1, 0);
	}

	if (m_stream->skip(position, 0) != position)
	{
		throw XferException(1, 0);
	}
}

// XferSave slot 11, retail 0x0060CE41 (281 bytes, ret 4): with a stream and
// the tagged flag set, a non-empty interned string is written after the
// 'RCSD' marker either as 0xFF plus the offset already recorded for it in
// the +0x2C table, or as a length byte (at most 254) and its characters,
// recording +0x28 plus +0x3C as its offset. Any short write throws
// XferException(1, 0).
// Slot 11 of XferSave's vtable 0x0087B010, not the PooledString slot 25, so the
// name stays address-derived; +0x3C is the table's element count.
Xfer &XferSave::rva0060CE41(Rva0060CE41Argument &str)
{
	if (m_stream == 0)
		return *(Xfer *)this;
	if (!m_flag || str.m_text == 0 || *str.m_text == 0)
		return *(Xfer *)this;

	int marker = 0x44534352;
	if (m_stream->write(&marker, 4) != 4)
		throw XferException(1, 0);

	const char *key = str.m_text;
	Rva0060CB2BNode *found = m_table.rva0060CB2B(key);
	if (found != 0)
	{
		unsigned char escape = 0xFF;
		if (m_stream->write(&escape, 1) != 1)
			throw XferException(1, 0);
		if (m_stream->write(&found->m_offset, 4) != 4)
			throw XferException(1, 0);
	}
	else
	{
		unsigned int length = strlen(key);
		if (length > 0xFE)
			length = 0xFE;
		if (m_stream->write(&length, 1) != 1)
			throw XferException(1, 0);
		if (m_stream->write(key, length) != (int)length)
			throw XferException(1, 0);
		int count = m_table.size();
		int base = m_28;
		m_table.rva0060CDFD(key) = base + count;
	}
	return *(Xfer *)this;
}
