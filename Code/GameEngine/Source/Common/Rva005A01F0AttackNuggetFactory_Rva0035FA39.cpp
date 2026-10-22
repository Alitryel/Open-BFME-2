// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// TextOnFrameTransition factory: parse the shared frame fields, then
// synchronize the transition length with its end frame.

struct FieldParse;

class INI
{
public:
	void initFromINI(void *what, const FieldParse *table);
};

struct Gen_00489270
{
	void m(int a);
};

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();
	int m_4;
	bool m_8, m_9, m_A;
	unsigned char m_pad0B;
	int m_C;
};

extern const FieldParse CountUpTransitionFields[];

class TextOnFrameTransition : public Rva001DBAA4
{
public:
	virtual ~TextOnFrameTransition();
	virtual void init(class GameWindow *win);
	virtual void update(int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	TextOnFrameTransition();

	int m_startFrame;
	int m_endFrame;
};

void s4ParseFieldsRva005A01F0(INI *ini, Gen_00489270 *sink)
{
	TextOnFrameTransition *t = new TextOnFrameTransition;

	ini->initFromINI(t, CountUpTransitionFields);
	t->m_4 = t->m_endFrame;

	sink->m((int)t);
}
