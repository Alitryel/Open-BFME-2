// ?rva003ECAB3@Rva003ECAB3@@QAEPAV1@M@Z
// partial score=0.96 date=2026-10-14
// cl: /O1 /arch:SSE /G7 /MD /DNDEBUG /DWIN32 /D_WINDOWS
class Rva003ECAB3 {
public:
	Rva003ECAB3 *rva003ECAB3(float scale);
private:
	float m[17];
};
Rva003ECAB3 *Rva003ECAB3::rva003ECAB3(float scale)
{
	m[0] *= scale;
	int n = 16;
	float *p = &m[1];
	do { *p *= scale; ++p; } while (--n != 0);
	return this;
}
