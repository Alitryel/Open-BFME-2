// cl: /O1 /arch:SSE /G7 /MD
// ?invoke@Rva0041E6EB@@QAEXXZ, retail 0x0041E6EB (8 bytes): call the bound
// single-inheritance member pointer at +0x10 on the object at +0x0C with no
// arguments, as a tail jump; the no-argument shape of the rowed delegate
// invoke 0x005B4C73 (Rva00579E47Delegate.cpp). The owner and the bound
// method's identity are not established; names are address-derived.
class __single_inheritance Rva0041E6EBTarget;
typedef void (Rva0041E6EBTarget::*Rva0041E6EBMethod)();

class Rva0041E6EB
{
public:
	void invoke();
private:
	char m_pad00[0x0C];
	void *m_object;		// +0x0C
	void *m_method;		// +0x10
};

void Rva0041E6EB::invoke()
{
	union
	{
		void *code;
		Rva0041E6EBMethod method;
	} binding;
	binding.code = m_method;
	(static_cast<Rva0041E6EBTarget *>(m_object)->*binding.method)();
}
