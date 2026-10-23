// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// Retail 0x00433F7F (94 bytes), AptSaveLoad: the item data of the selected
// entry of the first list box (+0x288), falling back to the second list box
// (+0x28C) when nothing is selected there. WorldBuilder's debug body
// (0x012AEB20, unnamed) returns zero without the first list box and the last
// GadgetListBoxGetItemData result otherwise; the callers (Delete, Load,
// SetDefaultFileName, 0x004340AC) test that result as a pointer.

class GameWindow;
void GadgetListBoxGetSelected(GameWindow *listbox, int *selectList);
void *GadgetListBoxGetItemData(GameWindow *window, int a, int b);

class AptSaveLoad
{
public:
	int rva00433F7F();

private:
	unsigned char m_pad000[0x288];
	GameWindow *m_primaryList;
	GameWindow *m_secondaryList;
};

int AptSaveLoad::rva00433F7F()
{
	int selected;
	void *data;
	if (m_primaryList == 0)
		return 0;
	GadgetListBoxGetSelected(m_primaryList, &selected);
	data = GadgetListBoxGetItemData(m_primaryList, selected, 0);
	if (selected < 0 && m_secondaryList != 0)
	{
		GadgetListBoxGetSelected(m_secondaryList, &selected);
		data = GadgetListBoxGetItemData(m_secondaryList, selected, 0);
	}
	return (int)data;
}
