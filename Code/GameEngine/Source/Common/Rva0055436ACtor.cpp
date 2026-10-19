// cl: /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ??0Rva0055436A@@QAE@PAX@Z @0x0055436A 79B
// Thread-subclass ctor: ThreadClass(0) base plus int-pointer map at +0x5C
// plus arg store at +0x68 and zero bytes/dword at +0x50 +0x51 +0x54 +0x58.
// Evidence: new(0x6C) plus lea +0x9C push at caller 0x0055443F; rowed
// ThreadClass ctor 0x00610430 map ctor 0x0033C432; vtable 0x0086B0D0;
// size 0x6C matches allocation.
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree_base<pair<int const, void *>, allocator<pair<int const, void *> > >::_Rb_tree_base(allocator<pair<int const, void *> > const &); }
namespace _STL { template <> _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::~_Rb_tree(); }
namespace _STL { template <> void _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::_M_erase(_Rb_tree_node<pair<int const, void *> > *); }
// bfme link decl-only end
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
protected:
	virtual void Thread_Function() = 0;
private:
	char m_name[0x40];
	unsigned int m_threadId;
	void *m_handle;
	int m_priority;
};
class Rva0055436A : public ThreadClass
{
public:
	Rva0055436A(void *arg);
private:
	bool m_50;
	bool m_51;
	int m_54;
	bool m_58;
	_STL::map<int, void *> m_5C;
	void *m_68;
};
Rva0055436A::Rva0055436A(void *arg) : ThreadClass(0)
{
	m_68 = arg;
	m_51 = false;
	m_58 = false;
	m_50 = false;
	m_54 = 0;
}
