// cl: /MD /EHsc
// ??1Rva0078D310Host@@UAE@XZ @ 0x00104E03 (66B).
// Dtor with vptr 0x007CF818 then clear +0x04 then member dtor at +0x218 via pin
// 0x00104DB0 then base GameWindow dtor via rowed 0x00314A0C with EH state 0 to -1.
// Evidence: mov [esi] vtable then and [esi+4] 0 then lea [esi+0x218] call pin
// then mov ecx esi call rowed base; ret no args; caller deleting dtor 0x00104F16.
class Rva00104DB0
{
public:
	virtual ~Rva00104DB0();
};

class GameWindow
{
protected:
	virtual ~GameWindow();
public:
	int m_04;
private:
	char m_pad[0x218 - 8];
};

class Rva0078D310Host : public GameWindow
{
public:
	virtual ~Rva0078D310Host();

private:
	Rva00104DB0 m_member;
};

Rva0078D310Host::~Rva0078D310Host()
{
	m_04 = 0;
}
