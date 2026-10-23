// cl: /Oi-
//
// Retail six-byte `jmp dword ptr [IAT]` import thunks that gen-imports and the
// batch-2 stdcall emitter left behind: thunks outside the Ghidra inventory and
// C++-decorated msvcr71 exports. Written by hand in the same form: each
// ji_<rva> forwards to the
// export found at its retail IAT slot under that export's own convention, so
// the compiler emits the tail jump and the import reference gate checks the
// slot's name. fgetc and fputc each hold two retail IAT slots; each slot has
// its own thunk here.

extern "C" __declspec(dllimport) void _except_handler3();
extern "C" __declspec(dllimport) void setlocale();
extern "C" __declspec(dllimport) void fgetc();
extern "C" __declspec(dllimport) void fputc();

class __declspec(dllimport) exception
{
public:
	exception();
	exception(const exception &other);
	virtual ~exception();
	virtual const char *what() const;
};

class __declspec(dllimport) type_info
{
public:
	virtual ~type_info();
};

struct _EXCEPTION_POINTERS;
typedef void (__cdecl *_se_translator_function)(unsigned int, _EXCEPTION_POINTERS *);
__declspec(dllimport) void terminate();
__declspec(dllimport) _se_translator_function __cdecl _set_se_translator(_se_translator_function);
__declspec(dllimport) int __cdecl vswprintf(unsigned short *, unsigned int, const unsigned short *, char *);

void ji_00628ff0() { _except_handler3(); }
void ji_006296da() { setlocale(); }
void ji_00629820() { fgetc(); }
void ji_00629826() { fputc(); }
void ji_00629aa2() { fgetc(); }
void ji_00629aa8() { fputc(); }
void ji_00629bc0() { terminate(); }
_se_translator_function ji_006298f2(_se_translator_function f) { return _set_se_translator(f); }
int ji_006298e6(unsigned short *a0, unsigned int a1, const unsigned short *a2, char *a3) { return vswprintf(a0, a1, a2, a3); }

// The member thunks: a qualified call on this passes ecx through untouched.
// The constructors return void here so the call stays in tail position.
struct Ji_exception : exception
{
	void ji_00629856();
	void ji_0062986e();
	const char *ji_006299b8() const;
	void ji_006299be(const exception &other);
};
void Ji_exception::ji_00629856() { this->exception::~exception(); }
void Ji_exception::ji_0062986e() { this->exception::exception(); }
const char *Ji_exception::ji_006299b8() const { return this->exception::what(); }
void Ji_exception::ji_006299be(const exception &other) { this->exception::exception(other); }

struct Ji_type_info : type_info
{
	void ji_00629bba();
};
void Ji_type_info::ji_00629bba() { this->type_info::~type_info(); }
