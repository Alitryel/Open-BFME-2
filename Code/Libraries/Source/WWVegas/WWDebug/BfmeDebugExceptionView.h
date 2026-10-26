#pragma once

// Local view for the debug_except retail TU. These declarations combine the
// already-byte-verified exception record, x86 context and BFME 2 Debug views
// from its exception-reporting donors. This is not a donor header
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

struct DebugIOInterface
{
	enum StringType { Assert, Check, Crash, Exception };
};

// Local ABI view of the BFME Debug interface. MSVC places an overload
// group at its first slot in reverse declaration order, so the stream
// writers land at 0x1C (double) through 0x38 (const char *), matching the
// retail vtable; SetPrefixAndRadix sits at 0x50.
class Debug
{
public:
	class RepeatChar
	{
		char m_char;
		int m_count;

	public:
		RepeatChar(char ch, int count) : m_char(ch), m_count(count) {}
	};

	class MemDump
	{
		const unsigned char *m_startPtr;
		unsigned m_numItems;
		unsigned m_bytePerItem;
		bool m_absAddr;
		bool m_withChars;

		MemDump(const void *startPtr, unsigned numItems, unsigned bytePerItem, bool absAddr,
			bool withChars)
			: m_startPtr((const unsigned char *)startPtr), m_numItems(numItems),
			  m_bytePerItem(bytePerItem), m_absAddr(absAddr), m_withChars(withChars)
		{
		}

	public:
		static MemDump Char(const void *startPtr, unsigned numItems)
		{
			return MemDump(startPtr, numItems, 1, true, true);
		}
	};

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

	virtual ~Debug();
	virtual Debug &operator<<(const RepeatChar &);
	virtual Debug &operator<<(const char *);
	virtual Debug &operator<<(int);
	virtual Debug &operator<<(unsigned);
	virtual Debug &operator<<(long);
	virtual Debug &operator<<(unsigned long);
	virtual Debug &operator<<(bool);
	virtual Debug &operator<<(float);
	virtual Debug &operator<<(double);
	virtual Debug &operator<<(short);
	virtual Debug &operator<<(unsigned short);
	virtual Debug &operator<<(__int64);
	virtual Debug &operator<<(unsigned __int64);
	virtual Debug &operator<<(const void *);
	virtual Debug &operator<<(const MemDump &);
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void SetPrefixAndRadix(const char *, int);
	// The exception-filter donor supplies these output slots.
	virtual void WriteBuildInfo(); // 0x54
private:
	virtual void StartOutput(DebugIOInterface::StringType, const char *, ...);
	virtual void FlushOutput(bool);
public:
	virtual void pad24(); virtual void pad25(); virtual void pad26(); virtual void pad27();
	virtual void pad28(); virtual void pad29(); virtual void pad30(); virtual void pad31();
	virtual void pad32(); virtual void pad33(); virtual void pad34(); virtual void pad35();
	virtual void pad36(); virtual void pad37(); virtual void pad38(); virtual void pad39();
	// The clipboard-report donor supplies the later build-info slots.
	virtual const char *GetVersion();         // 0xA0
	virtual const char *GetInternalVersion(); // 0xA4
	virtual const char *GetBuildDate();       // 0xA8

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

	const char *GetOutputBuffer(DebugIOInterface::StringType) const;

private:
	friend class DebugExceptionhandler;
	struct IOBuffer
	{
		char *buffer;
		unsigned used;
		unsigned alloc;
		bool lastWasCR;
	};
	unsigned char m_pad04[0x9C80];
	IOBuffer ioBuffer[7];                // +0x9C84
	int curType;                        // +0x9CF4
	char curSource[256];                // +0x9CF8
	long disableAssertsEtc;             // +0x9DF8
	unsigned char m_pad9DFC[0x154];
	int m_width;                       // +0x9F50
	char m_fillChar;                    // +0x9F54
	unsigned char m_pad9F55;
	bool m_fullMiniDump;                // +0x9F56
	unsigned char m_pad9F57[0xD];
	bool m_inAssertDialog;              // +0x9F64
};

class DebugExceptionhandler
{
public:
	static const char *GetExceptionType(_EXCEPTION_POINTERS *, char *);
	static long __stdcall ExceptionFilter(_EXCEPTION_POINTERS *);

private:
	static void LogFPURegisters(Debug &, _EXCEPTION_POINTERS *);
	static void LogRegisters(Debug &, _EXCEPTION_POINTERS *);
};
