// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ?Rva00217870Fill@@YAPAUFileInfoStruct@MixFileCreator@@PAU12@IABU12@@Z @0x00217870 37B
// Unlock counted uninitialized_fill loop stride 0x10 calling rowed placement-copy helper
// at 0x0021781D. Evidence: test edi jbe plus dec edi jne; same family as the
// 0x0021784A copy loop; caller at 0x00218B8B.
// Typed placement-copy owner Rva0021781DConstruct at 0x0021781D.
class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		unsigned char m_data[0x10];
	};
};

void Rva0021781DConstruct(MixFileCreator::FileInfoStruct *, const MixFileCreator::FileInfoStruct &);


MixFileCreator::FileInfoStruct *Rva00217870Fill(MixFileCreator::FileInfoStruct *first, unsigned int count,
	const MixFileCreator::FileInfoStruct &value)
{
	MixFileCreator::FileInfoStruct *cur = first;
	for (; count > 0; --count, ++cur)
		Rva0021781DConstruct(cur, value);
	return cur;
}
