// cl: /Ireference/shims/bfme2_ascii /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??1Rva00427311@@UAE@XZ @0x00427311 129B
// Dtor storing vtable 0x0083C5DC frees WindowVideoMap at +0xc then base.
// Evidence: calls rowed begin 0x00427195 and iterator inc 0x0041E832 releaseBuffer 0x00036410 delete 0x0002FD60 hashtable dtor 0x004271D9 base dtor 0x001B4E74 caller 0x004274AB deleting dtor.
// Link: declare ~AsciiString only (the shim's documented per-unit switch) so this TU calls the out-of-line
// retail destructor instead of emitting a non-retail ??_GAsciiString copy; the // cl: line is untouched.
#ifndef BFME_ASCII_DTOR_DECL
#define BFME_ASCII_DTOR_DECL
#endif
#include <hash_map>
#include "ascii_string.h"
// bfme link decl-only begin
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end

class GameWindow;
class WindowVideo;

class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
	{
		size_t operator()(const GameWindow *const &) const;
	};
};

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
class SubsystemInterface
{
public:
	SubsystemInterface();
	virtual ~SubsystemInterface();
};

// The rowed empty-map constructor at 0x00427507 uses this neutral element
// view. This call establishes neither an element identity nor a map-use layout.
struct Rva00427507Element { char bytes[1]; bool operator<(const Rva00427507Element &) const; bool operator==(const Rva00427507Element &) const; };
typedef _STL::hash_map<int, Rva00427507Element> RowedMapCtor00427507;
namespace _STL { template <> RowedMapCtor00427507::hash_map(); }

class Rva004271D9
{
public:
	__declspec(dllimport) __forceinline Rva004271D9()
	{ ((RowedMapCtor00427507 *)this)->RowedMapCtor00427507::hash_map(); }
	~Rva004271D9();
private:
	char m_pad[4];
	void *m_start;
	void *m_finish;
	void *m_end;
};

typedef std::hash_map<const GameWindow *, WindowVideo *,
	WindowVideoManager::hashConstGameWindowPtr,
	std::equal_to<const GameWindow *> > Rva00427311Map;

// Bind the iterator helper to the kept copy rather than emitting a losing one.
namespace _STL {
template <> size_t hashtable<
	pair<const GameWindow *const, WindowVideo *>, const GameWindow *,
	WindowVideoManager::hashConstGameWindowPtr,
	_Select1st<pair<const GameWindow *const, WindowVideo *> >,
	equal_to<const GameWindow *>,
	allocator<pair<const GameWindow *const, WindowVideo *> >
	>::_M_bkt_num_key(const GameWindow *const &) const;
}

class Rva00427311 : public SubsystemInterface
{
public:
	Rva00427311();
	virtual ~Rva00427311();
private:
	char m_pad[8];
	Rva004271D9 m_playingVideos;
};

Rva00427311::Rva00427311()
{
}

Rva00427311::~Rva00427311()
{
	Rva00427311Map &map = (Rva00427311Map &)m_playingVideos;
	Rva00427311Map::iterator it = map.begin();
	while (it != map.end())
	{
		AsciiString *asciiString = (AsciiString *)it->second;
		if (asciiString)
			delete asciiString;
		++it;
	}
}
