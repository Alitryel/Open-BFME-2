// cl: /MD
// The +0x34 setter at 0x0031404A is now GameWindow::winSetWindowId in
// GameClient/GUI/GameWindowFields.cpp, identified by the script and Apt callers.
// ?rva003140CF@Rva003140CF@@QAEHH@Z, retail 0x003140CF, 21 bytes.
// Same file: null-guarded self-or-arg setter at +0x44 returning 0; unlocks nine
// callers with four becoming ready.

class Rva003140CF
{
public:
	int rva003140CF(int v);

private:
	char m_pad[0x44];
	int m_44;
};

int Rva003140CF::rva003140CF(int v)
{
	if (!v)
		m_44 = (int)this;
	else
		m_44 = v;
	return 0;
}
