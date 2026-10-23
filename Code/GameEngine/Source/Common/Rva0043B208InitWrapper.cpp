// ?rva0043B208@Rva0043B208@@QAEPAV1@XZ @0x0043B208 12B
// Forwarder to pinned init 0x00263895 on same object, returns this.
// Evidence: calls init@Rva00263895Member (pin-only 2 pins), mov eax,esi return;
// callers at 0x43B88E/0x43B97C/0x50B198 construct stack temps. Honest Rva name.
class Rva00263895Member
{
public:
	void init();
};

class Rva0043B208
{
public:
	Rva0043B208 *rva0043B208();
private:
	Rva00263895Member m_member;
};

Rva0043B208 *Rva0043B208::rva0043B208()
{
	m_member.init();
	return this;
}
