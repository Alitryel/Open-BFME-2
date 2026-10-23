// cl: /MD
//
// ?rva001DB66A@MetaMap@@QAEPAXI@Z retail 0x001DB66A 28B. Deleting helper
// for the rowed vtable dtor 0x001DB60F: destroys via that dtor then frees with
// rowed operator delete when flags bit0 is set. Evidence: chain caller of
// landed 0x001DB60F plus vtable slot 0 of 0x007DBA7C plus rowed delete
// 0x0002FD60. Honest address name on proven owner.
void __cdecl operator delete(void *p);

class MetaMap
{
public:
	virtual ~MetaMap();
	void *rva001DB66A(unsigned int flags);
};

void *MetaMap::rva001DB66A(unsigned int flags)
{
	this->MetaMap::~MetaMap();
	if (flags & 1)
		::operator delete(this);
	return this;
}
