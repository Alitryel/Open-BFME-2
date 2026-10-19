// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

struct Rva00160A00Node
{
	char pad[0x0C];
	Rva00160A00Node *m_0C;
	Rva00160A00Node *m_10;
};

class AIPlayer
{
	char pad[8];
	Rva00160A00Node *m_08;

public:
	void flip();
};

void AIPlayer::flip()
{
	Rva00160A00Node *p = m_08;
	Rva00160A00Node *last = 0;
	if (p)
	{
		do
		{
			Rva00160A00Node *a = p->m_0C;
			Rva00160A00Node *b = p->m_10;
			p->m_10 = a;
			p->m_0C = b;
			last = p;
			p = b;
		} while (p);
	}
	m_08 = last;
}
