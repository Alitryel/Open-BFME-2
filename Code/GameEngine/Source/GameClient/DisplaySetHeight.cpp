// cl: /DNDEBUG /MD /EHsc

// Target boundary 0x0025C378/25 (Ghidra). Retail stores the argument at
// Display+0x0C, then conditionally dispatches through TheMouse's vtable slot
// +0x58. The BFME1 Display::setHeight donor identifies that operation as
// updating m_height and calling Mouse::setMouseLimits; the field and call
// shape above are independently visible in BFME2 retail.

class Mouse
{
public:
#define V(n) virtual void pad##n();
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10)
	V(11) V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21)
#undef V
	virtual void setMouseLimits();
};
extern Mouse *TheMouse;


class W3DDisplay;

class Rva0025C6E2Elem
{
public:
	void rva0025C829(W3DDisplay *display, int arg);	// 0x0025C829

private:
	unsigned char m_data[0x18];
};

enum { MAX_STATIC_IMAGES = 3 };

class Display
{
public:
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void setWidth(unsigned int width);
	virtual void setHeight(unsigned int height);
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual bool getWindowed();
	virtual bool setDisplayMode(unsigned int xres, unsigned int yres, unsigned int bitdepth, bool windowed);
	void DrawStaticImage(int index, int arg);

private:
	unsigned char m_pad04[8];
	unsigned int m_height; // +0x0c
	unsigned int m_width; // +0x10
	unsigned char m_pad14[0x68 - 0x14];
	Rva0025C6E2Elem m_staticImages[MAX_STATIC_IMAGES]; // +0x68
};

void Display::setHeight(unsigned int height)
{
	m_height = height;
	Mouse *mouse = TheMouse;
	if (mouse)
		mouse->setMouseLimits();
}

// ?setWidth@Display@@UAEXI@Z retail 0x0025C391 25B.
// Width twin of setHeight storing at +0x10 then Mouse::setMouseLimits.
// Evidence: retail mov [ecx+0x10] then TheMouse 0x00DFDCA0 slot 0x58; BFME1 Display.h setWidth donor; gap between 0x0025C378 and 0x0025C46E.
void Display::setWidth(unsigned int width)
{
	m_width = width;
	Mouse *mouse = TheMouse;
	if (mouse)
		mouse->setMouseLimits();
}
