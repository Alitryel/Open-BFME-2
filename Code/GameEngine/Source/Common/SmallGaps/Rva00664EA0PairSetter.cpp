class Rva00664EA0PairView
{
public:
	void setPair(unsigned int first, unsigned int second);

private:
	unsigned char m_unknown[0x28];
	unsigned int m_first;
	unsigned int m_second;
};

void Rva00664EA0PairView::setPair(unsigned int first, unsigned int second)
{
	m_first = first;
	m_second = second;
}
