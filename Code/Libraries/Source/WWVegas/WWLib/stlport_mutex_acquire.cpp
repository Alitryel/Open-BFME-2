// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport 4.5.3 _STLP_mutex_base::_M_acquire_lock - eight bytes that hand the
// address of the lock word to the spin lock at 0x00007690 and return. The lock
// word is the whole of the object, so `this` is the argument.

typedef long __stl_atomic_t;

namespace _STL
{

template <int __inst>
struct _STLP_mutex_spin
{
	static void __cdecl _M_do_lock(volatile __stl_atomic_t *lock);
};

class _STLP_mutex_base
{
public:
	void _M_acquire_lock();

	volatile __stl_atomic_t _M_lock;
};

inline void _STLP_mutex_base::_M_acquire_lock()
{
	_STLP_mutex_spin<0>::_M_do_lock(&_M_lock);
}

}

// _M_acquire_lock is a header inline in STLport (stl/_threads.h): four other units emit
// select-any copies of it, so a strong definition here was a duplicate symbol in the linked
// build. This anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitMutexAcquireLock@@YAXPAV_STLP_mutex_base@_STL@@@Z present-unmatched
void bfmeEmitMutexAcquireLock(_STL::_STLP_mutex_base *mutex)
{
	mutex->_M_acquire_lock();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?_M_acquire_lock@NodeAllocMutex@_STL@@QAEXXZ=?_M_acquire_lock@_STLP_mutex_base@_STL@@QAEXXZ")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeInitVLY@BfmeRegVLY@@QAEXXZ=?_M_acquire_lock@_STLP_mutex_base@_STL@@QAEXXZ")
#pragma comment(linker, "/alternatename:?bfmeInitVLZ@BfmeRegVLZ@@QAEXXZ=?_M_acquire_lock@_STLP_mutex_base@_STL@@QAEXXZ")
