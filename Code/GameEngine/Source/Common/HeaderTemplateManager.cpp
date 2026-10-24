// cl: /Ireference/shims/bfmelist /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// Retail manager teardown owns the canonical HeaderTemplate pointer list.
#include "../GameClient/GUI/HeaderTemplateView.h"

// Retain bfmealloc's native null-checked free and proxy forwarding inline.
// The matched bodies already inline these STLport ownership wrappers.
namespace _STL {
template<> __declspec(dllimport) __forceinline
_List_node<HeaderTemplate *> *allocator<_List_node<HeaderTemplate *> >::allocate(size_type n, const void *p) const
{ return n != 0 ? (_List_node<HeaderTemplate *> *)allocator<char>::allocate(n * sizeof(value_type), 0) : 0; }
template<> __declspec(dllimport) __forceinline
_List_node<HeaderTemplate *> *_STLP_alloc_proxy<_List_node<HeaderTemplate *>*, _List_node<HeaderTemplate *>, allocator<_List_node<HeaderTemplate *> > >::allocate(size_t n)
{ return __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<HeaderTemplate *>*)0).allocate(n, 0); }
template<> __declspec(dllimport) __forceinline
void allocator<_List_node<HeaderTemplate *> >::deallocate(pointer p, size_type n) const
{ if (p != 0) ::free((void*)p); }
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<HeaderTemplate *>*, _List_node<HeaderTemplate *>, allocator<_List_node<HeaderTemplate *> > >::deallocate(_List_node<HeaderTemplate *>* p, size_t n)
{ __stl_alloc_rebind(static_cast<_Base&>(*this), (_List_node<HeaderTemplate *>*)0).deallocate(p, n); }
}

class Rva0048C200Owner
{
public:
	~Rva0048C200Owner();
};

HeaderTemplateManager::HeaderTemplateManager()
{
}

HeaderTemplateManager::~HeaderTemplateManager()
{
	for (HeaderTemplateList::iterator it = m_headerTemplateList.begin(); it._M_node != m_headerTemplateList.end()._M_node;)
	{
		HeaderTemplate *v = *it;
		if (v != 0)
		{
			Rva0048C200Owner *o = (Rva0048C200Owner *)v;
			*(void **)o = 0;
			delete o;
		}
		it = m_headerTemplateList.erase(it);
	}
}
