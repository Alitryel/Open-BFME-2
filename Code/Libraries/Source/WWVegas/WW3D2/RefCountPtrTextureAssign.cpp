// cl: /DNDEBUG
//
// RefCountPtr<TextureClass>::operator= at 0x000424D0 (40 B), split out of
// TextureStatisticsVector.cpp: retail built the TextureStatistics vector
// family (Resize 0x00129990, the struct assignment 0x00129770, Add) with
// /G7 -- add reg,1 where the default build writes inc -- while this
// out-of-line copy is the default build's. Views as in
// TextureStatisticsVector.cpp (ZH texture.h / ref_ptr.h layouts).

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/texture.h
class TextureClass : public TextureBaseClass
{
};

inline void TextureBaseClass::Add_Ref()
{
	++*reinterpret_cast<unsigned short *>(reinterpret_cast<char *>(this) + 4);
}

template<class T>
// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ref_ptr.h
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other)
	{
		if (other.Referent != 0)
			other.Referent->Add_Ref();
		if (Referent != 0)
			Referent->Release_Ref();
		Referent = other.Referent;
		return *this;
	}

private:
	T *Referent;
};

template RefCountPtr<TextureClass> const &RefCountPtr<TextureClass>::operator=(RefCountPtr<TextureClass> const &);
