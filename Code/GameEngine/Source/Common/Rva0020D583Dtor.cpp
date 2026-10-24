// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1Rva0020D583@@UAE@XZ 0x0020D583 99B evidence: dtor with vptr 0x007E3F98 plus 5 StringBase D releaseBuffer rowed; caller Unwind deleting dtor; prev ConstZeroGetters
template <typename T> class StringBase {
public: StringBase() { m_data = 0; }
        ~StringBase() { releaseBuffer(); }
        void set(const char *s);
private: void releaseBuffer();
         T *m_data; };

// The narrow teardown is rowed at 0x00036410 (StringBaseWideReleaseBuffer.cpp).
template <> StringBase<char>::~StringBase();

class Rva0020D583 {
public: Rva0020D583();
        virtual ~Rva0020D583();
private: StringBase<char> m_04;
         StringBase<char> m_08;
         StringBase<char> m_0c;
         StringBase<char> m_10;
         StringBase<char> m_14; };
Rva0020D583::~Rva0020D583() {}

// ??0Rva0020D583@@QAE@XZ 0x0020D4E3 132B evidence: ctor vptr 0x007E3F98 plus 5 StringBase D set rowed with TSMorning literals; caller 0x0020D6F5
Rva0020D583::Rva0020D583()
{
    m_04.set("TSMorningN.tga");
    m_08.set("TSMorningE.tga");
    m_0c.set("TSMorningS.tga");
    m_10.set("TSMorningW.tga");
    m_14.set("TSMorningT.tga");
}
