// cl: /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Native constructor ownership supplies the derived type and layout.
// The factory parses its field table, then copies end frame into frame length.

struct FieldParse;
class INI
{
public:
    void initFromINI(void *, const FieldParse *);
};
struct Gen_00489270 { void m(int); };

class Rva001DBAA4
{
public:
    Rva001DBAA4();
    virtual ~Rva001DBAA4();
    int m_4;
    bool m_8, m_9, m_A;
    int m_C;
};

class MainMenuMediumScaleUpTransition : public Rva001DBAA4
{
public:
    MainMenuMediumScaleUpTransition();
    virtual ~MainMenuMediumScaleUpTransition();
    int m_10;
    int m_14;
    int m_18;
    int m_1C;
    int m_20;
    int m_24;
    int m_28;
    int m_2C;
    int m_30;
    int m_34;
    int m_38;
    int m_3C;
    int m_40;
    int m_44;
};

extern const FieldParse CountUpTransitionFields[];

void s4parse0059E290(INI *ini, Gen_00489270 *sink)
{
    MainMenuMediumScaleUpTransition *t = new MainMenuMediumScaleUpTransition;
    ini->initFromINI(t, CountUpTransitionFields);
    t->m_4 = t->m_14;
    sink->m((int)t);
}
