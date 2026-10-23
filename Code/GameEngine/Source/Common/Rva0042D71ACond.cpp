class Rva0042D71A
{
public:
	int get() const;
	void *m_ptr;
};
int Rva0042D71A::get() const
{
	int x = *(int *)((char *)m_ptr + 0x30);
	int y = x + 4;
	return x ? y : 0;
}
