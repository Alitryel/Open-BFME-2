// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// rva0014921e at 0x0014921E, 38 bytes. Address-derived free function; identity
// is not recovered. It calls the container's erase(begin,end) over the whole
// 4-byte-element buffer at +0/+4 (the ICF-folded STLport vector erase pinned at
// 0x00532803) and then hands (arg1, 0, buffer, arg4) to the unpinned worker at
// 0x00149002. The class name and the worker name are address-derived.

enum ParticleSystemID { INVALID_PARTICLE_SYSTEM_ID_14921E };
namespace _STL {
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	T *erase(T *first, T *last);
};
}

class Rva0014921EVector
{
public:
	int *m_begin; // +0
	int *m_end;   // +4

};

void rva00149002(int a, int b, Rva0014921EVector *buffer, int d);

void rva0014921e(int a, int b, Rva0014921EVector *buffer, int d)
{
	((_STL::vector<ParticleSystemID, _STL::allocator<ParticleSystemID> > *)buffer)->erase((ParticleSystemID *)buffer->m_begin, (ParticleSystemID *)buffer->m_end);
	rva00149002(a, 0, buffer, d);
}
