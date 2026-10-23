// cl: /O1 /DNDEBUG /MD
//
// RefMultiListClass<RenderObjClass>::Remove, retail 0x0006EF4E, 47 bytes.
// Dedicated TU so multilist.cpp cannot see this body. Internal_Remove is
// already landed; Release_Ref is inlined as dec-at-+4 then vtable slot 0.

class MultiListObjectClass
{
};

class RefCountClass
{
public:
	virtual void Delete_This();
	int RefCount;
};

class RenderObjClass : public RefCountClass, public MultiListObjectClass
{
};

class GenericMultiListClass
{
protected:
	bool Internal_Remove(MultiListObjectClass *obj);
	MultiListObjectClass *Internal_Remove_List_Head(void);
};

template <class T>
class RefMultiListClass : public GenericMultiListClass
{
public:
	bool Remove(T *obj);
	bool Release_Head(void);
};

inline bool RefMultiListClass<RenderObjClass>::Remove(RenderObjClass *obj)
{
	bool result = Internal_Remove(obj);
	if (result)
	{
		if (--obj->RefCount == 0)
			obj->Delete_This();
	}
	return result;
}

// Sibling of the matched Remove above (0x0006EF4E, 47B): same Release_Ref
// shape (dec at +4 then vtable slot 0) and same bool return in al, but for
// the list head via Internal_Remove_List_Head (already matched at 0x6109A0).
// Retail 0x0006EF8C, 33 bytes.
inline bool RefMultiListClass<RenderObjClass>::Release_Head(void)
{
	RenderObjClass *headObject = (RenderObjClass *)Internal_Remove_List_Head();
	if (headObject != 0) {
		if (--headObject->RefCount == 0)
			headObject->Delete_This();
		return true;
	}
	return false;
}

// Both members are header inlines elsewhere: other units emit select-any
// copies, so strong definitions here were duplicate symbols in the linked
// build. This anchor only makes this unit emit its copies for the ledger
// rows; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRefMultiListRenderObjRemove@@YAXPAV?$RefMultiListClass@VRenderObjClass@@@@PAVRenderObjClass@@@Z present-unmatched
void bfmeEmitRefMultiListRenderObjRemove(RefMultiListClass<RenderObjClass> *p, RenderObjClass *obj)
{
	p->Remove(obj);
	p->Release_Head();
}
#pragma inline_depth()
