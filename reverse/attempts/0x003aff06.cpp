// ?rva003AFF06@Rva003AFF06@@UAEXPAX0@Z
// partial score=0.85 date=2026-10-14
// cl: /DNDEBUG /MD /EHsc
//
// 0x003AFF06 (28B): a vtable slot (wb_name_leads: vtable, no named caller)
// that forwards both of its arguments to the unrowed ParticleSystem member at
// 0x001F9BA4 through the system held at +0x4, when one is held. The slot is
// read through the same null-test-then-fallback smart pointer that
// ParticleSystem::destroy (0x001F462C) uses for its slave slot: the test goes
// through the conversion operator, the call through operator->, which falls
// back to the rowed null-system factory 0x001FCBD7. Retail re-reads +0x4 and
// re-tests it after the outer test, exactly as that sibling does. Class and
// method names are address-derived; the meaning is not recovered.

class ParticleSystem
{
public:
	void rva001F9BA4(void *a, void *b);			// 0x001F9BA4 (unrowed, pinned)
};

ParticleSystem *Make001FCBD7(void);				// 0x001FCBD7

class Rva003AFF06SystemPtr
{
public:
	operator ParticleSystem *(void) const
	{
		return m_target;
	}

	ParticleSystem *operator->(void) const
	{
		ParticleSystem *target = *(ParticleSystem *const volatile *)&m_target;
		if (!target)
			target = Make001FCBD7();
		return target;
	}

private:
	ParticleSystem *m_target;
};

class Rva003AFF06
{
public:
	virtual void rva003AFF06(void *a, void *b);

private:
	Rva003AFF06SystemPtr m_system;				///< +0x4
};

void Rva003AFF06::rva003AFF06(void *a, void *b)
{
	if (m_system != 0)
		m_system->rva001F9BA4(a, b);
}
