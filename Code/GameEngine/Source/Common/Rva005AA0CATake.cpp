// ?rva005AA0CA@Rva005AA0CA@@QAEPAURva005AA0CAEntry@@XZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Retail 0x005AA0CA..0x005AA0D8 (14 bytes): hands out the next 12-byte
// entry of a count (+0) / storage (+4) pool. Retail stores the bumped count
// before it reads the storage pointer; reading the storage through a bound
// reference keeps that order (a direct member read is hoisted above the
// store).
struct Rva005AA0CAEntry
{
	int m_data[3];
};

class Rva005AA0CA
{
public:
	Rva005AA0CAEntry *rva005AA0CA();
private:
	int m_count;
	Rva005AA0CAEntry *m_storage;
};

Rva005AA0CAEntry *Rva005AA0CA::rva005AA0CA()
{
	int index = m_count++;
	Rva005AA0CAEntry *const &storage = m_storage;
	return &storage[index];
}
