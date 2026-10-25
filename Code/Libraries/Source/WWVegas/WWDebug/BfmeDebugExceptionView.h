#pragma once

// Local view for the debug_except retail TU. These declarations combine the
// already-byte-verified exception record, x86 context and BFME 2 Debug views
// from its three exception-reporting donors. This is not a donor header
// asserted as BFME 2 source. FloatSave begins at +0x1C, SegGs at +0x8C;
// Debug's width/fill fields remain at +0x9F50/+0x9F54.

struct _EXCEPTION_RECORD
{
    unsigned long ExceptionCode;
    unsigned long ExceptionFlags;
    _EXCEPTION_RECORD *ExceptionRecord;
    void *ExceptionAddress;
    unsigned long NumberParameters;
    unsigned long ExceptionInformation[15];
};

struct FLOATING_SAVE_AREA
{
	unsigned long ControlWord;
	unsigned long StatusWord;
	unsigned long TagWord;
	unsigned long ErrorOffset;
	unsigned long ErrorSelector;
	unsigned long DataOffset;
	unsigned long DataSelector;
	unsigned char RegisterArea[80];
	unsigned long Cr0NpxState;
};

struct _CONTEXT
{
	unsigned long ContextFlags;
	unsigned long Dr[6];
	FLOATING_SAVE_AREA FloatSave;
	unsigned long SegGs;      // 0x8C
	unsigned long SegFs;      // 0x90
	unsigned long SegEs;      // 0x94
	unsigned long SegDs;      // 0x98
	unsigned long Edi;        // 0x9C
	unsigned long Esi;        // 0xA0
	unsigned long Ebx;        // 0xA4
	unsigned long Edx;        // 0xA8
	unsigned long Ecx;        // 0xAC
	unsigned long Eax;        // 0xB0
	unsigned long Ebp;        // 0xB4
	unsigned long Eip;        // 0xB8
	unsigned long SegCs;      // 0xBC
	unsigned long EFlags;     // 0xC0
	unsigned long Esp;        // 0xC4
	unsigned long SegSs;      // 0xC8
};

struct _EXCEPTION_POINTERS
{
	_EXCEPTION_RECORD *ExceptionRecord;
	_CONTEXT *ContextRecord;
};

// Local ABI view of the BFME Debug interface. MSVC places an overload
// group at its first slot in reverse declaration order, so the stream
// writers land at 0x1C (double) through 0x38 (const char *), matching the
// retail vtable; SetPrefixAndRadix sits at 0x50.
class Debug
{
public:
	class Hex {};
	class Dec {};
	class Bin {};

	class Width
	{
		friend class Debug;
		int m_width;

	public:
		explicit Width(int width) : m_width(width) {}
	};

	class FillChar
	{
		friend class Debug;
		char m_fill;

	public:
		explicit FillChar(char fill = ' ') : m_fill(fill) {}
	};

	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual Debug &operator<<(const char *);
	virtual Debug &operator<<(int);
	virtual Debug &operator<<(unsigned);
	virtual Debug &operator<<(long);
	virtual Debug &operator<<(unsigned long);
	virtual Debug &operator<<(bool);
	virtual Debug &operator<<(float);
	virtual Debug &operator<<(double);
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void SetPrefixAndRadix(const char *, int);

	Debug &operator<<(const Hex &)
	{
		SetPrefixAndRadix("0x", 16);
		return *this;
	}

	Debug &operator<<(const Dec &)
	{
		SetPrefixAndRadix("", 10);
		return *this;
	}

	Debug &operator<<(const Bin &)
	{
		SetPrefixAndRadix("%", 2);
		return *this;
	}

	Debug &operator<<(const Width &width)
	{
		m_width = width.m_width;
		return *this;
	}

	Debug &operator<<(const FillChar &fill)
	{
		m_fillChar = fill.m_fill;
		return *this;
	}

private:
	unsigned char m_pad[0x9f4c];
	int m_width;                         // +0x9F50
	char m_fillChar;                     // +0x9F54
};

class DebugExceptionhandler
{
public:
	static const char *GetExceptionType(_EXCEPTION_POINTERS *, char *);

private:
	static void LogFPURegisters(Debug &, _EXCEPTION_POINTERS *);
	static void LogRegisters(Debug &, _EXCEPTION_POINTERS *);
};
