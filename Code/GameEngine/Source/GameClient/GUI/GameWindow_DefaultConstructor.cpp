// cl: /Ob1 /GF /Gy /MD /EHsc /GR /DNDEBUG /DWIN32 /D_WINDOWS

// Byte-exact BFME reconstruction of ??0GameWindow@@QAE@XZ.  The BFME layout
// is kept TU-local because the ordinary GameWindow reference header has the
// Zero Hour offsets; these fields are corroborated by the BFME accessors and
// neighboring constructors.  Member names follow GameWindow.cpp's view of the
// class (same offsets): +0x04 m_positionSink, +0x1E0/+0x1E8/+0x1EC the input,
// draw and tooltip callbacks, +0x210 m_210.

typedef int Int;

class WinInstanceData
{
public:
	WinInstanceData();
	unsigned char m_pad00[0x0C];
	unsigned m_style;
	unsigned char m_pad10[0x15C - 0x10];
	int m_enabledColor;
	int m_enabledBorderColor;
	int m_disabledColor;
	int m_disabledBorderColor;
	int m_hiliteColor;
	int m_hiliteBorderColor;
	int m_imecompositeColor;
	int m_imecompositeBorderColor;
	unsigned char m_pad17C[0x1A8 - 0x17C];
};

class GameWindowChild;

class Gadget210;

class GameWindow
{
protected:
	virtual ~GameWindow();
public:
	GameWindow();
	virtual void vslot1() = 0;
	virtual void vslot2() = 0;
	virtual Int draw(void *);
	virtual void vslot4() = 0;
	virtual Int rva0009FD78();
	virtual void vslot6() = 0;
	virtual void *fetchCreateInstance() = 0;
	virtual void vslot8() = 0;
	virtual void vslot9() = 0;
	virtual void vslot10() = 0;

private:
	GameWindowChild *m_positionSink;
	int m_status;
	int m_sizeX;
	int m_sizeY;
	int m_regionLoX;
	int m_regionLoY;
	int m_regionHiX;
	int m_regionHiY;
	int m_cursorX;
	int m_cursorY;
	void *m_userData;
	WinInstanceData m_instData;
	void *m_inputData;
	void *m_bfmeInputExtra;
	void *m_inputFunc;
	void *m_system;
	void *m_drawFunc;
	void *m_tooltipFunc;
	void *m_bfmeCallbackExtra;
	int m_bfmeCallbackExtra2;
	GameWindow *m_next;
	GameWindow *m_prev;
	GameWindow *m_parent;
	GameWindow *m_child;
	void *m_nextLayout;
	void *m_prevLayout;
	Gadget210 *m_210;
	void *m_editData;
};

GameWindow::GameWindow( void )
{
	m_positionSink = 0;
	m_status = 0;
	m_sizeX = 0;
	m_sizeY = 0;
	m_regionLoX = 0;
	m_regionLoY = 0;
	m_regionHiX = 0;
	m_regionHiY = 0;
	m_cursorX = 0;
	m_cursorY = 0;
	m_userData = 0;
	m_inputData = 0;
	m_bfmeInputExtra = 0;
	m_inputFunc = 0;
	m_system = 0;
	m_drawFunc = 0;
	m_tooltipFunc = 0;
	m_bfmeCallbackExtra = 0;
	m_next = 0;
	m_prev = 0;
	m_parent = 0;
	m_child = 0;
	m_nextLayout = 0;
	m_prevLayout = 0;
	m_210 = 0;
	m_editData = 0;
	m_bfmeCallbackExtra2 = 1;
}
