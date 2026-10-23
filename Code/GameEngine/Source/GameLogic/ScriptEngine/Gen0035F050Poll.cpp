// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/ScriptEngine

// 0x00542890 is rowed as XmlNameSlotList::finish.
class XmlNameSlotList
{
public:
	int finish(void);
};

class Gen0035F050
{
public:
	bool poll(int a, int limit, int c, int d, int e);

private:
	void *m_unused0;
	int m_value;
};

bool Gen0035F050::poll(int, int limit, int, int, int)
{
	if (m_value > limit)
	{
		do
		{
			if (!((XmlNameSlotList *)this)->finish())
				return false;
		} while (m_value > limit);
	}
	return true;
}
