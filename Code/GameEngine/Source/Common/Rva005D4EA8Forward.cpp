// cl: /MD
// 0x0057C499 is matched as the constructor AptLoadMovieFrame(int, const AsciiString &).
class AsciiString;
class AptLoadMovieFrame
{
public:
	AptLoadMovieFrame(int a1, const AsciiString &a2);
};
class Rva005D4EA8
{
public:
	void *rva005D4EA8(int a1, int a2);
private:
	char m_00[8];
	int m_08;
	int m_0C;
};
void *Rva005D4EA8::rva005D4EA8(int a1, int a2)
{
	((AptLoadMovieFrame *)this)->AptLoadMovieFrame::AptLoadMovieFrame(a1, *(const AsciiString *)a2);
	m_08 = 0;
	m_0C = 0;
	return this;
}
