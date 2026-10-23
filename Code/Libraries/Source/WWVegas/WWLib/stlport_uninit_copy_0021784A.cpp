// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
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


// ?Rva0021784ACopy@@YAPAUFileInfoStruct@MixFileCreator@@PAU12@00@Z @0x0021784A 38B
// Unlock uninitialized_copy loop stride 0x10 calling rowed placement-copy helper at
// 0x0021781D. Evidence: pushes plus call plus pop ecx interleaved adds; same
// family as rowed __uninitialized_copy 0x000C2438 38B; callers at 0x00218B5E.
// True __uninitialized_copy name spent at 0x000642AF so land honest free name;
// Placement-copy callee is called through its typed ledger name.
MixFileCreator::FileInfoStruct *Rva0021784ACopy(MixFileCreator::FileInfoStruct *first,
	MixFileCreator::FileInfoStruct *last, MixFileCreator::FileInfoStruct *result)
{
	MixFileCreator::FileInfoStruct *cur = result;
	for (; first != last; ++first, ++cur)
		Rva0021781DConstruct(cur, *first);
	return cur;
}
