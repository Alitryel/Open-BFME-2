// cl: /O1 /MD /EHsc
// Native11178B-1117B4; called by WorldHeightMap tile reader ABEA0 after
// TileData constructor111850. Incoming reference is retained before the old
// reference is released. The caller releases its temporary reference after
// this call. No original method name is asserted.
// Semantic guide: ZH refcount.h REF_PTR_SET; target independently proves
// pointee virtualslot0 and reference count4; receiver's companion pointer2AB4.
// Share the destination's verified base, reference field and class declarations.
class RefCountClass
{
public:
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
public:

	void Release_Ref()
	{
		if (--m_numRefs == 0)
			Delete_This();
	}

	int m_numRefs;
};

class TileData : public RefCountClass
{
public:
	virtual ~TileData();
private:
	unsigned char m_data[0x2AB4 - 8];
private:
	RefCountClass *m_ref;
public:
	bool hasRGBDataForWidth(int width);
	void rva0011178B(TileData *value);
};

void TileData::rva0011178B(TileData *value)
{
    RefCountClass *incoming=value;
    if(incoming)++incoming->m_numRefs;
    RefCountClass *&slot=m_ref;
    if(slot)slot->Release_Ref();
    slot=incoming;
}
