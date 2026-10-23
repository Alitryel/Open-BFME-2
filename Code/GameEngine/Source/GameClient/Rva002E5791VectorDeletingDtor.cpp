// cl: /O1 /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ??_ERva002E5791@@QAEPAXI@Z 0x002E5E5A 75B
// Evidence: chain from 0x002E5791 landing; size 8 cookie at [esi-4]; calls rowed ??1Rva002E5791 0x002E5791 plus ??_M ??_V ??3.
void operator delete[](void *p);

template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	T *m_data;
};

class Rva002E5791
{
public:
	~Rva002E5791();

private:
	StringBase<char> m_narrow;
	StringBase<unsigned short> m_wide;
};

// ?Rva002E5791DeleteArray@@YAXPAVRva002E5791@@@Z present-unmatched
void Rva002E5791DeleteArray(Rva002E5791 *array)
{
	delete[] array;
}
