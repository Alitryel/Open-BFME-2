// cl: /MD
// Native433498..4334AF: set bit40 at ECX+C4, then forward the float to
// the SSE store at210C91. That helper's original owner/name is unresolved;
// RenderObjClass::_bfme_ro_set_98 instead owns the distinct body at E43E7.
class Rva00210C91FloatField
{
public:
  void set(float v);
};
class Rva00433498
{
public:
  void rva00433498(float v);
private:
  char _pad[0xC4];
  int m_flags;
};
void Rva00433498::rva00433498(float v)
{
  m_flags |= 0x40;
  ((Rva00210C91FloatField *)this)->Rva00210C91FloatField::set(v);
}
