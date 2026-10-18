#pragma once
// Native string-record hash ABI. The insertion at 0x00418A12 compares the key through
// StringBase<char>; copy at 0x0041890F constructs it before the verified 32-byte value.
// Node creator at 0x004189ED allocates 40 bytes and constructs the 36-byte record at +4.
// Original application identities and field meanings remain unasserted.
#include "ascii_string.h"

// The 12-byte member is a view of retail's STLport tree value: its copy is the
// native 165-byte _Rb_tree copy rowed at 0x004186F2, reached directly by the
// record copies, and its teardown is retail's 5-byte forwarder rowed at
// 0x0022CCE5 (the funclet of the record copy 0x004188B6 jumps there). Declare
// the tree type with exactly those two operations so both calls bind to rowed
// definitions instead of address-only placeholder names no object defines. The
// body keeps only the 12 bytes the surrounding records lay out.
class Rva0022CCE5
{
public:
	void rva0022CCE5();
};
struct Rva004186F2Element;
namespace _STL {
template <class _Tp> struct _Identity;
template <class _Tp> struct less;
template <class _Tp> class allocator;
template <class _Tp, class _Val, class _Key, class _Compare, class _Alloc>
class _Rb_tree
{
public:
	_Rb_tree(const _Rb_tree &other);
	~_Rb_tree() { ((Rva0022CCE5 *)this)->rva0022CCE5(); }

private:
	char m_pad[0xC];
};
}
typedef _STL::_Rb_tree<Rva004186F2Element, Rva004186F2Element,
	_STL::_Identity<Rva004186F2Element>, _STL::less<Rva004186F2Element>,
	_STL::allocator<Rva004186F2Element> > Rva004186F2;

// Each 12-byte member is reached through an inline copy of a holder,
// which gives retail's lea/lea/push argument order at +0xC.
struct Rva004188B6Part
{
	__forceinline Rva004188B6Part(const Rva004188B6Part &other) : m_value(other.m_value) {}

	Rva004186F2 m_value;
};

struct Rva004188B6
{
	Rva004188B6(const Rva004188B6 &other);
	~Rva004188B6();

	Rva004188B6Part m_00;
	Rva004188B6Part m_0C;
	AsciiString m_18;
	char m_1C;
	char m_1D;
};


struct Rva0041890FRecord
{
    Rva0041890FRecord(const Rva0041890FRecord &other);
    Rva0041890FRecord(const AsciiString &name, const Rva004188B6 &mapped);
    AsciiString key;
    Rva004188B6 value;
};
struct Rva00418A12Node
{
    Rva00418A12Node *next;
    Rva0041890FRecord value;
};
struct Rva00418A12Result
{
    Rva00418A12Node *node;
    void *table;
    bool inserted;
};
class Rva00418A8EHost
{
public:
    int outer(int outputAddress, int recordAddress);
    Rva00418A12Result *apply(Rva00418A12Result *output, const Rva0041890FRecord &record);
    Rva00418A12Node *newNode(const Rva0041890FRecord &record);
private:
    void *m_unused00;
    Rva00418A12Node **m_buckets;
    Rva00418A12Node **m_end;
    int m_unused0C;
    int m_size;
};
typedef char VerifyStringRecord32[(sizeof(Rva004188B6)==32)?1:-1];
typedef char VerifyStringHashValue36[(sizeof(Rva0041890FRecord)==36)?1:-1];
typedef char VerifyStringHashNode40[(sizeof(Rva00418A12Node)==40)?1:-1];
typedef char VerifyStringHashResult12[(sizeof(Rva00418A12Result)==12)?1:-1];
