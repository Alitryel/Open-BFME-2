// ?rva00424E77@FormationAssistant@@QAEPAVFormation@@HPAVRva001EB130Holder@@PBUCoord3D@@@Z
// partial score=0.75 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP=
// FormationAssistant formation build: turns a formation template and a set
// of objects into a Formation (a vector of 32-byte placement records).
//
// ?rva00424E77@FormationAssistant@@QAEPAVFormation@@HPAVRva001EB130Holder@@PBUCoord3D@@@Z
// @0x00424E77 845B. Identity: AIGroup formation move 0x00372571 calls it on
// TheFormationAssistant with the formation type, its valid-object list and
// the destination (REL32 at 0x00372767) and hands the result to the
// formation optimizer.
// Target evidence (retail body and its EH tables 0x00D3460C): the template
// is read from the 4-byte deque at 0x00E03174 (size via _M_subtract 0x00051A98,
// element via the rowed iterator operator[] 0x00422D82); the usable objects
// (not flagged at Object +0x438 bit 0) are copied into a pooled list<Object *>
// that is sorted by distance to the destination (0x00423D2F) or reassigned
// from the source list (0x00423D92); every 24-byte template row is filled by
// 0x0042481E, then refilled while any pooled object still passes the row's
// filter (0x00421A57). The rows are then laid out centre-out: each slot's
// x is the running width (slot width plus the +0x28 column spacing), rows are
// centred on half their width and stacked by the tallest slot plus the +0x24
// row spacing; occupied slots become 0x00421764 records pushed onto the new
// Formation. Unwind states: 0 row list (0x00424A09), 1 pooled list
// (0x001EB940), 2 centre table (0x0007FAB3).
// No WorldBuilder or ZH counterpart of this helper is known; names of the
// views below are structural, not recovered identities.

typedef bool Bool;
typedef int Int;
typedef float Real;

class Object;
class Rva001EB130Holder;
struct Coord3D;

void __cdecl Rva00030830GameFree(void *);

class FreelistProxyHead
{
public:
	void setup(const void *alloc, void *data);
};
class FreelistPool
{
public:
	void *pop();
};
extern FreelistPool g_freelistPool00DB8FEC;

// Object +0x438 private status byte (bit 0: object is being destroyed).
struct FormationObjectStatusView
{
	unsigned char m_pad000[0x438];
	unsigned char m_privateStatus; // +0x438
};

// One placed slot (16 bytes): candidate, object and its footprint.
struct BfmeE16
{
	void *m_candidate;
	Object *m_object;
	Int m_width;
	Int m_depth;
};

// The 32-byte placement record the Formation stores.
struct BfmePod32
{
	int a[8];
};

class Rva00421764
{
public:
	Rva00421764(const void *a, int b, const void *c);
	operator const BfmePod32 &() const { return *(const BfmePod32 *)this; }

private:
	int m_data[8];
};

namespace _STL
{
template <class _Tp> class allocator
{
public:
	allocator() {}
	static char *allocate(unsigned int n, const void *hint);
};

template <class _Value, class _Tp, class _MaybeReboundAlloc> class _STLP_alloc_proxy : public _MaybeReboundAlloc
{
public:
	_STLP_alloc_proxy(const _MaybeReboundAlloc &a, _Value p);
	_Value _M_data;
};

template <class _Tp, class _Alloc> class _Vector_base
{
public:
	__declspec(noinline) _Vector_base(const _Alloc &a) : _M_start(0), _M_finish(0), _M_end_of_storage(a, 0) {}
	_Tp *_M_start;
	_Tp *_M_finish;
	_STLP_alloc_proxy<_Tp *, _Tp, _Alloc> _M_end_of_storage;
};

template <class _Tp, class _Alloc = allocator<_Tp> > class vector : public _Vector_base<_Tp, _Alloc>
{
public:
	vector() : _Vector_base<_Tp, _Alloc>(_Alloc()) {}
	explicit vector(unsigned int n);
	~vector()
	{
		if (this->_M_start)
			Rva00030830GameFree(this->_M_start);
	}
	unsigned int size() const { return this->_M_finish - this->_M_start; }
	_Tp &operator[](unsigned int i) { return this->_M_start[i]; }
	void reserve(unsigned int n);
	void push_back(const _Tp &x);
};

struct _List_node_base
{
	_List_node_base *_M_next;
	_List_node_base *_M_prev;
};
template <class _Tp> struct _List_node : public _List_node_base
{
	_Tp _M_data;
};

template <class _Tp> struct _Nonconst_traits;
template <class _Tp> struct _Const_traits;
template <class _Tp, class _Traits> struct _List_iterator
{
	_List_iterator(_List_node_base *x) : _M_node(x) {}
	_List_iterator(const _List_iterator<_Tp, _Nonconst_traits<_Tp> > &x) : _M_node(x._M_node) {}
	_Tp &operator*() const { return ((_List_node<_Tp> *)_M_node)->_M_data; }
	_List_iterator &operator++()
	{
		_M_node = _M_node->_M_next;
		return *this;
	}
	bool operator==(const _List_iterator &x) const { return _M_node == x._M_node; }
	bool operator!=(const _List_iterator &x) const { return _M_node != x._M_node; }
	_List_node_base *_M_node;
};
struct __false_type
{
	__false_type() {}
};

template <class _Tp, class _Alloc> class _List_base
{
public:
	__declspec(noinline) _List_base(const _Alloc &a)
	{
		char proxy;
		((FreelistProxyHead *)this)->setup(&proxy, 0);
		_List_node_base *node = (_List_node_base *)g_freelistPool00DB8FEC.pop();
		node->_M_next = node;
		node->_M_prev = node;
		_M_node = node;
	}
	_List_node_base *_M_node;
};

template <class _Tp, class _Alloc = allocator<_Tp> > class list : public _List_base<_Tp, _Alloc>
{
public:
	typedef _List_iterator<_Tp, _Nonconst_traits<_Tp> > iterator;
	iterator begin() { return iterator(this->_M_node->_M_next); }
	iterator end() { return iterator(this->_M_node); }
	iterator insert(iterator position, const _Tp &x);
	void push_back(const _Tp &x) { insert(end(), x); }
};

template <class _Tp, class _Alloc> class deque;
template <class _Tp> struct _Deque_iterator_base
{
	int _M_subtract(const _Deque_iterator_base &x) const;
	_Tp *_M_cur;
	_Tp *_M_first;
	_Tp *_M_last;
	_Tp **_M_node;
};
template <class _Tp, class _Traits> struct _Deque_iterator : public _Deque_iterator_base<_Tp>
{
	_Tp &operator[](int n) const;
};
}

class Formation : public _STL::vector<BfmePod32>
{
public:
	__declspec(noinline) Formation() throw() {}
};

// One template row (24 bytes): its cell candidates and filters.
class FormationTemplateRows
{
public:
	char m_data[0x18];
};

struct FormationTemplate
{
	FormationTemplateRows *m_rowsBegin;
	FormationTemplateRows *m_rowsEnd;
	Int getRowCount() const { return m_rowsEnd - m_rowsBegin; }
};

struct Rva00422D82Element
{
	FormationTemplate *m_template;
};

// The formation template table at 0x00E03174 (deque<FormationTemplate *>).
struct FormationTemplateDeque
{
	_STL::_Deque_iterator<Rva00422D82Element, _STL::_Nonconst_traits<Rva00422D82Element> > m_start;
	_STL::_Deque_iterator_base<void *> m_finish;
	unsigned int size() const { return m_finish._M_subtract(*(const _STL::_Deque_iterator_base<void *> *)&m_start); }
};
extern unsigned int g_Va00E03174;

// list<vector<BfmeE16> >: the rows built so far. The list base constructor
// is the folded 41-byte allocator<char> node constructor 0x00280A8D, and the
// out-of-line dtor 0x00424A09 tail-jumps to the list clear 0x000799D0.
typedef _STL::vector<BfmeE16> BfmeE16Vector;

namespace _STL
{
template <> class _List_base<BfmeE16Vector, allocator<BfmeE16Vector> >
{
public:
	__declspec(noinline) _List_base(const allocator<BfmeE16Vector> &a)
	{
		char proxy;
		((FreelistProxyHead *)this)->setup(&proxy, 0);
		_List_node_base *node = (_List_node_base *)allocator<char>::allocate(sizeof(_List_node<BfmeE16Vector>), 0);
		node->_M_next = node;
		node->_M_prev = node;
		_M_node = node;
	}
	_List_node_base *_M_node;
};
}

class Rva000799D0
{
public:
	void rva000799D0();
};

class FormationRowList : public _STL::_List_base<BfmeE16Vector, _STL::allocator<BfmeE16Vector> >
{
public:
	__forceinline explicit FormationRowList(const _STL::allocator<BfmeE16Vector> &a) : _STL::_List_base<BfmeE16Vector, _STL::allocator<BfmeE16Vector> >(a) {}
	~FormationRowList() { ((Rva000799D0 *)this)->rva000799D0(); }
	Bool empty() const { return _M_node->_M_next == _M_node; }
	unsigned int size() const
	{
		unsigned int n = 0;
		for (_STL::_List_node_base *p = _M_node->_M_next; p != _M_node; p = p->_M_next)
			++n;
		return n;
	}
	BfmeE16Vector &front() { return ((_STL::_List_node<BfmeE16Vector> *)_M_node->_M_next)->_M_data; }
};

// The pooled list<Object *>: its out-of-line ~_List_base is 0x001EB769 and
// the unwind funclet calls the out-of-line complete dtor 0x001EB940.
class Gen_uwm_001eb769
{
public:
	~Gen_uwm_001eb769() throw();
};

typedef _STL::list<Object *> ObjectList;

class Rva001EB940 : public _STL::_List_base<Object *, _STL::allocator<Object *> >
{
public:
	__forceinline explicit Rva001EB940(const _STL::allocator<Object *> &a) : _STL::_List_base<Object *, _STL::allocator<Object *> >(a) {}
	~Rva001EB940() { ((Gen_uwm_001eb769 *)this)->~Gen_uwm_001eb769(); }
};

class FormationObjectList;

class Rva00421A16
{
public:
	__forceinline ~Rva00421A16() {}
	__forceinline Rva00421A16(const Rva00421A16 &r) : x(r.x), y(r.y), z(r.z) {}
	float x, y, z;
};
class Rva00423D2FOwner
{
public:
	void rva00423D2F(Rva00421A16 comp);
};

typedef _STL::_List_iterator<Object *, _STL::_Const_traits<Object *> > ObjectListConstIter;
class GameWindow;
typedef _STL::_List_iterator<GameWindow *, _STL::_Const_traits<GameWindow *> > GWListConstIter;
class Rva00423D92
{
public:
	void rva00423D92(GWListConstIter a, GWListConstIter b, const _STL::__false_type &c);
};

class Rva00421A57
{
public:
	bool rva00421A57(int v);
};

template <class T> inline const T &formationMax(const T &a, const T &b)
{
	return a < b ? b : a;
}

class FormationAssistant
{
public:
	Bool rva0042481E(FormationRowList *rows, const FormationTemplateRows *cells, FormationObjectList *objects);
	Formation *rva00424E77(Int formationType, Rva001EB130Holder *objects, const Coord3D *pos);

	char m_pad00[0x24];
	Real m_rowSpacing; // +0x24
	Real m_columnSpacing; // +0x28
};

template <class _It> inline int fmDistance(const _It &first, const _It &last, const _STL::__false_type &)
{
	int n = 0;
	_It it(first);
	while (it != last)
	{
		++it;
		++n;
	}
	return n;
}
typedef _STL::_List_iterator<BfmeE16Vector, _STL::_Nonconst_traits<BfmeE16Vector> > RowIter;
Formation *FormationAssistant::rva00424E77(Int formationType, Rva001EB130Holder *objects, const Coord3D *pos)
{
	if (formationType == -1 || formationType < 0)
		return 0;
	FormationTemplateDeque &templates = *(FormationTemplateDeque *)&g_Va00E03174;
	if ((unsigned int)formationType > templates.size())
		return 0;
	FormationTemplate *tmpl = templates.m_start[formationType].m_template;
	if (!tmpl)
		return 0;

	FormationRowList rows((_STL::allocator<BfmeE16Vector>()));
	Rva001EB940 pool((_STL::allocator<Object *>()));
	ObjectList &source = *(ObjectList *)objects;
	for (ObjectList::iterator it = source.begin(); it != source.end(); ++it)
	{
		Object *obj = *it;
		if (obj && !(((FormationObjectStatusView *)obj)->m_privateStatus & 1))
			((ObjectList *)&pool)->push_back(obj);
	}
	if (pos)
		((Rva00423D2FOwner *)&pool)->rva00423D2F(*(const Rva00421A16 *)pos);
	else
	{
		_STL::_List_node_base *end = *(_STL::_List_node_base **)objects;
		((Rva00423D92 *)&pool)->rva00423D92(GWListConstIter(end->_M_next), GWListConstIter(end), _STL::__false_type());
	}

	for (Int i = 0; i < tmpl->getRowCount(); ++i)
	{
		FormationTemplateRows *row = &tmpl->m_rowsBegin[i];
		if (rva0042481E(&rows, row, (FormationObjectList *)&pool))
		{
			for (;;)
			{
				_STL::_List_node_base *it;
				for (it = pool._M_node->_M_next; it != pool._M_node; it = it->_M_next)
				{
					if (((Rva00421A57 *)row)->rva00421A57((int)((_STL::_List_node<Object *> *)it)->_M_data))
						break;
				}
				if (it == pool._M_node)
					break;
				rva0042481E(&rows, row, (FormationObjectList *)&pool);
			}
		}
	}

	_STL::_List_node_base *head = rows._M_node;
	if (head->_M_next == head)
		return 0;

	Formation *formation = new Formation;
	RowIter end(head);
	unsigned int count = fmDistance(RowIter(head->_M_next), RowIter(head), _STL::__false_type());
	formation->reserve(((_STL::_List_node<BfmeE16Vector> *)head->_M_next)->_M_data.size() * count);
	_STL::vector<unsigned int> centers(((_STL::_List_node<BfmeE16Vector> *)head->_M_next)->_M_data.size() + 1);
	Int rowY = 0;
	for (RowIter it(head->_M_next); it != end; ++it)
	{
		BfmeE16Vector &slots = *it;
		Int maxDepth = 0;
		Int x = 0;
		for (unsigned int j = 0; j < slots.size(); ++j)
		{
			BfmeE16 &slot = slots[j];
			if (slot.m_object)
			{
				centers[j] = slot.m_width / 2 + x;
				x = (Int)((Real)slot.m_width + (Real)x + m_columnSpacing);
				maxDepth = formationMax(maxDepth, slot.m_depth);
			}
		}
		Int half = (Int)(((Real)x - m_columnSpacing) * 0.5f);
		Int step = 1;
		Int sign = 1;
		unsigned int idx = (slots.size() - 1) / 2;
		for (Int n = slots.size(); n > 0; --n)
		{
			BfmeE16 &slot = slots[idx];
			Int cx = centers[idx] - half;
			if (slot.m_object)
			{
				Int pt[2];
				pt[0] = cx;
				pt[1] = rowY;
				formation->push_back(Rva00421764(slot.m_object, (int)slot.m_candidate, pt));
			}
			idx += sign * step;
			sign = -sign;
			++step;
		}
		rowY = (Int)((Real)maxDepth + (Real)rowY + m_rowSpacing);
	}
	return formation;
}
