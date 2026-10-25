// ?rva00603CA3@Rva00603C0F@@QAE_NPBDPAUOut603CA3@@@Z
// partial score=0.95 date=2026-09-29
// ?rva00603CA3@Rva00603C0F@@QAE_NPBDPAUOut603CA3@@@Z
// partial score=0.95 date=2026-09-29
// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
extern "C" char *__cdecl strcpy(char *dest, const char *src);
char *__cdecl Rva00605365(char *);
struct Out603CA3 { unsigned int m_a; unsigned int m_b; unsigned int m_c; unsigned int m_d; };
// This caller only uses the lookup method. Keep its declaration compatible
// with Rva00603C5F.cpp; the lookup implementation owns the container layout.
class Rva00603C0F {
public:
  const void *rva00603C0F(const char *a, const char *b);
  bool rva00603CA3(const char *a, Out603CA3 *out);
};
bool Rva00603C0F::rva00603CA3(const char *a, Out603CA3 *out) {
  char buf[260];
  strcpy(buf, a);
  const char *n = Rva00605365(buf);
  const void *found = rva00603C0F(buf, n);
  if (!found) return false;
  if (!out) return true;
  out->m_a = 0;
  out->m_b = *(unsigned int*)((char*)found + 8);
  out->m_c = 0;
  out->m_d = 0;
  return true;
}
