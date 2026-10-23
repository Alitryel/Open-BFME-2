// cl: /O1 /DNDEBUG /MD
//
// ?Peek_Head@?$RefMultiListClass@VRenderObjClass@@@@QAEPAVRenderObjClass@@XZ,
// retail 0x0006EFAD, 27 bytes. Dedicated TU: the caller (Reset_List) lives
// in RefMultiListRenderObjResetList.cpp, so the body lives here (a TU
// holding a row must not define that row's callees).
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/WWVegas/WWLib/multilist.h):
// GenericMultiListClass::Internal_Get_List_Head is header-inline (empty iff
// Head.Next == &Head, else Head.Next->Object); RefMultiListClass peek wraps
// it with a downcast. The -8 is the MultiListObjectClass subobject offset
// inside RenderObjClass (RefCount vptr+0, count+4, link+8); the null check
// rides the static_cast, matching the sibling TU's explicit ternary shape.

class MultiListObjectClass
{
public:
	void *ListNode;
};

struct MultiListNode
{
	MultiListNode *Prev;
	MultiListNode *Next;
	void *NextList;
	MultiListObjectClass *Object;
	void *List;
};

class GenericMultiListClass
{
public:
	MultiListObjectClass *Internal_Get_List_Head(void)
	{
		if (Head.Next == &Head)
			return 0;
		return Head.Next->Object;
	}

protected:
	void *m_vptr;
	MultiListNode Head; // +0x04
};

class RefCountClass
{
public:
	virtual void Delete_This(void);
	int RefCount;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
};

template <class T>
class RefMultiListClass : public GenericMultiListClass
{
public:
	T *Peek_Head(void);
};

inline RenderObjClass *RefMultiListClass<RenderObjClass>::Peek_Head(void)
{
	return (RenderObjClass *)Internal_Get_List_Head();
}

// This TU owns the row, but other TUs emit the same body as an inline copy,
// so a strong definition is a duplicate in the linked build. The anchor below
// emits the same copy as select-any with inlining off; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRefMultiListRenderObjPeekHead@@YAXPAV?$RefMultiListClass@VRenderObjClass@@@@@Z present-unmatched
void bfmeEmitRefMultiListRenderObjPeekHead(RefMultiListClass<RenderObjClass> *p)
{
	p->Peek_Head();
}
#pragma inline_depth()
