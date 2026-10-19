// cl: /DNDEBUG /DWIN32 /MD /D_STLP_USE_STATIC_LIB /EHsc
// ?rva002E6431@Rva002E6431@@QAEXXZ 0x002E6431 32B
// Evidence: chain from 0x002E6158; clears +0x30 GameTextTable ptr via dtor plus scalar delete; callers none yet.
class Rva002E5791
{
public:
	~Rva002E5791();
};

class GameTextTable
{
public:
	~GameTextTable();
};

class Rva002E6431
{
public:
	void rva002E6431();

private:
	char m_pad[0x30];
	GameTextTable *m_ptr30;
};

void Rva002E6431::rva002E6431()
{
	GameTextTable *ptr = m_ptr30;
	if (ptr)
	{
		ptr->~GameTextTable();
		::operator delete(ptr);
		m_ptr30 = 0;
	}
}
