// cl: /DNDEBUG /MD /GX- /O2 /Ob2
// ?Release_Ref@TextureClass@@QAEXXZ at retail 0x0061ED10 (36 bytes): the
// texture handle release that TextureClass callers name directly (symbols.csv
// pin; Open-BFME-1 rows it under this name). Retail folds it with the
// identical TextureBaseClass::Release_Ref body that holds the address's row
// (TextureBaseReleaseRefThunk.cpp, the model and flags for this unit), so it
// lands as that row's ICF alias: WORD refcount at +4 with flag bits, virtual
// Delete_This at slot 8 when the count hits zero with 0x1000000 set.

class TextureClass
{
public:
	void Release_Ref();
	virtual void v00();
	virtual void v04();
	virtual void v08();
	virtual void v0c();
	virtual void v10();
	virtual void v14();
	virtual void v18();
	virtual void v1c();
	virtual void Delete_This();

private:
	unsigned int m_refBits;
};

// ?Release_Ref@TextureClass@@QAEXXZ
void TextureClass::Release_Ref()
{
	if ((m_refBits & 0xffff) == 0)
		return;
	*reinterpret_cast<unsigned short *>(&m_refBits) =
		static_cast<unsigned short>(*reinterpret_cast<unsigned short *>(&m_refBits) - 1);
	if ((m_refBits & 0xffff) != 0)
		return;
	if ((m_refBits & 0x1000000) == 0)
		return;
	Delete_This();
}
