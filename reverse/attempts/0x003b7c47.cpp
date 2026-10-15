// ?rva003B7C47@Rva003B573E@@QAEHABV?$StringBase@D@@@Z
// partial score=0.93 date=2026-10-15
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 0x003B7C47..0x003B7D90 329B: add-or-ref a key in the sorted string
// record table (lower_bound 0x003B573E, rowed compare/set/push_back/reserve/
// insert). Clean rebuild, no barrier/equal-arm hacks: frame, EH, position
// spill [ebp-0x14], index spill [ebp-0x10] and the shared index*20 tail in EBX
// all match retail. Only residue: retail passes &index's own slot to insert;
// here the cast to the ModuleData* payload materialises a copy in [ebp+8]
// (335B). A direct reference bind (reinterpret_cast / vector<long>) makes index
// address-taken everywhere and the found path stores it (frame 0x18).
#include <vector>
#include "ascii_string.h"
class ModuleData;
struct BfmeStringRecord003B3F78 {
	unsigned int word0, word1;
	AsciiString text;
	unsigned char flag;
	unsigned short short0;
	unsigned int word2;
	BfmeStringRecord003B3F78(const BfmeStringRecord003B3F78 &);
	BfmeStringRecord003B3F78() : word2(0) {}
};
namespace _STL {
	template<> void vector<const ModuleData *>::reserve(unsigned int);
	template<> vector<const ModuleData *>::iterator vector<const ModuleData *>::insert(vector<const ModuleData *>::iterator, const ModuleData *const &);
	template<> void vector<BfmeStringRecord003B3F78>::push_back(const BfmeStringRecord003B3F78 &);
}
class Rva003B573E {
	_STL::vector<const ModuleData *> m_sorted;
	_STL::vector<BfmeStringRecord003B3F78> m_records;
	int m_freeHead;
	int m_tail;
public:
	int rva003B573E(const StringBase<char> &);
	int rva003B7C47(const StringBase<char> &);
};

// ?rva003B7C47@Rva003B573E@@QAEHABV?$StringBase@D@@@Z
int Rva003B573E::rva003B7C47(const StringBase<char> &key)
{
	unsigned int position = rva003B573E(key);
	int index;
	if (position < m_sorted.size() &&
		((const StringBase<char> &)m_records[(int)m_sorted[position]].text).compare(key) == 0) {
		index = (int)m_sorted[position];
		if (!m_records[index].flag)
			return -1;
	} else {
		unsigned int wanted = m_sorted.size() + 1;
		if (wanted > m_sorted.capacity())
			m_sorted.reserve(wanted + (wanted >> 1) + 8);
		if (m_freeHead == -1) {
			int freeIndex = m_records.size();
			m_records.push_back(BfmeStringRecord003B3F78());
			m_records.back().word0 = -1;
			m_freeHead = freeIndex;
		}
		index = m_freeHead;
		BfmeStringRecord003B3F78 &record = m_records[index];
		((StringBase<char> &)record.text).set(key);
		m_sorted.insert(m_sorted.begin() + position, (const ModuleData *)index);
		m_freeHead = record.word0;
		if (m_tail != -1)
			m_records[m_tail].word1 = index;
		record.word0 = m_tail;
		record.word1 = -1;
		m_tail = index;
		record.short0 = 0;
	}
	BfmeStringRecord003B3F78 &record = m_records[index];
	++record.short0;
	record.flag = 0;
	return index;
}
