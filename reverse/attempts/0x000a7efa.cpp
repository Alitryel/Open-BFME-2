// ?requestFile@AudioFileCache@@QAE?AVRva00690FF0Handle@@ABVAsciiString@@H@Z
// partial score=0.6 date=2026-10-14
// ?requestFile@AudioFileCache@@QAE?AVRva00690FF0Handle@@ABVAsciiString@@H@Z
// partial score=0.6 date=2026-10-14
// cl: /O1 /arch:SSE /G7 /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?requestFile@AudioFileCache@@QAE?AVRva00690FF0Handle@@ABVAsciiString@@H@Z @0x000A7EFA 430B.
// By-name overload of the Miles file cache request (the event overload at 0x000A8241 forwards
// here). Under the cache mutex: an empty name yields the cache's empty handle; a name already
// in the cache gets its entry moved to the requested priority list (and out of the unused list
// when its count is zero) and a handle to it; a name in the failed set yields the empty
// handle; otherwise a new 0x54-byte entry is created, registered under its name, queued at
// the clamped priority and handed out through a temporary handle copy.
// Layout views follow AudioFileCacheLoader.cpp / AudioFileCacheRequestEvent.cpp.
#include <list>
#include <set>
#include "ascii_string.h"

namespace _STL {
template <> list<int, allocator<int> >::iterator list<int, allocator<int> >::erase(list<int, allocator<int> >::iterator);
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

class MilesMutexGuard {
public:
 MilesMutexGuard(void *,int); ~MilesMutexGuard();
private: void *m_mutex; bool m_flag;
};
class Rva00691110Handle {
public: Rva00691110Handle(const Rva00691110Handle&);
private: void *target;
};
class Rva00690FF0Handle {
public:
 Rva00690FF0Handle(const Rva00690FF0Handle& other) {
  ((Rva00691110Handle*)this)->Rva00691110Handle::Rva00691110Handle(*(const Rva00691110Handle*)&other);
 }
 ~Rva00690FF0Handle();
private: void *target;
};
class Gen0002857E;
class AudioFileContainer : public Rva00690FF0Handle {
public: AudioFileContainer(Gen0002857E *);
};
struct Rva000A7E9EInput;
class Rva000A7E9E {public: void freeUnusedSamples(); void rva000A7E9E(const Rva000A7E9EInput &);};
class Rva0010ED3D { public: void rva0010ED3D(int priority); };
class Rva000427195 { public: void *rva000A7B3C(const AsciiString *name); };
struct Rva0041534BNode { char pad[8]; Gen0002857E *file; };
struct Rva0041534BIter { Rva0041534BNode *node; int extra; };
class Rva00056F61 { public: Rva0041534BIter rva0041534B(const AsciiString *name); };
class FileActivity { public: virtual bool busy(int flags); };
class Gen0002857E {
public:
 Gen0002857E(Rva000A7E9E *owner, const AsciiString &name);
 char pad00[0x34];
 volatile int m_count;
 int pad38;
 int m_priority;
 int pad40;
 FileActivity m_activity;
 char pad48[0x0C];
};
class AudioFileCache {
public:
 Rva00690FF0Handle requestFile(const AsciiString &name, int priority);
private:
 char pad00[0x14];
 _STL::list<int,_STL::allocator<int> > m_pending[3];
 char unusedTree20[12];
 _STL::set<AsciiString,_STL::less<AsciiString>,_STL::allocator<AsciiString> > m_failed;
 char pad38[0x0C];
 Rva00690FF0Handle m_emptyFile;
 char pad48[8];
 void *m_mutex;
};

Rva00690FF0Handle AudioFileCache::requestFile(const AsciiString &name, int request)
{
	int priority = request;
	if (priority < 0)
		priority = 0;
	else if (priority >= 3)
		priority = 2;
	MilesMutexGuard guard(m_mutex, 0);
	if (name.isEmpty())
		return m_emptyFile;
	Rva0041534BIter found = ((Rva00056F61 *)this)->rva0041534B(&name);
	if (found.node)
	{
		Gen0002857E *file = found.node->file;
		if (file->m_count == 0)
			((Rva000A7E9E *)this)->rva000A7E9E(*(const Rva000A7E9EInput *)file);
		if (!file->m_activity.busy(0) && file->m_priority < priority)
		{
			_STL::list<int,_STL::allocator<int> > &from = m_pending[file->m_priority];
			_STL::list<int,_STL::allocator<int> >::iterator it = from.begin();
			for (; it != from.end(); ++it)
			{
				if (*it == (int)file)
				{
					from.erase(it);
					int value = (int)file;
					m_pending[priority].push_back(value);
					file = (Gen0002857E *)value;
					break;
				}
			}
		}
		((Rva0010ED3D *)file)->rva0010ED3D(priority);
		return AudioFileContainer(file);
	}
	if (m_failed.find(name) != m_failed.end())
		return m_emptyFile;
	Gen0002857E *created = new Gen0002857E((Rva000A7E9E *)this, name);
	AudioFileContainer container(created);
	*(Gen0002857E **)((Rva000427195 *)this)->rva000A7B3C(&name) = created;
	int value = (int)created;
	m_pending[priority].push_back(value);
	((Rva0010ED3D *)created)->rva0010ED3D(priority);
	return container;
}
