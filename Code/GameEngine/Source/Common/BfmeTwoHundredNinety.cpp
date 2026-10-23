// cl: /Od
// A block asked for and, when one comes back, given the caller's byte as its
// only content. What the choice yields is never read. Built without
// optimisation; the callee is pinned by address.

void *__cdecl operator new(unsigned int size, void *placement);

class BfmeThingQF
{
public:
	void bfmeMakeQF(unsigned int bytes, const char *from);
};

void BfmeThingQF::bfmeMakeQF(unsigned int bytes, const char *from)
{
	char *got = (char *)::operator new(1, (void *)bytes);

	(got != 0) ? (*got = *from, (void *)got) : (void *)0;
}
