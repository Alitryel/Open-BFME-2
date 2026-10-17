// ?rva001DE9C4@Eva@@QAEHPBD@Z
// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
#include "ascii_string.h"
class Rva00056F61;
struct Rva0041534BIter
{
	void *m_node;
	Rva00056F61 *m_table;
	Rva0041534BIter(void *n, Rva00056F61 *t) : m_node(n), m_table(t) {}
};
class Rva00056F61
{
public:
	void *rva00056F61(const AsciiString *key) throw();
	void *m_unused;
	void *m_begin;
	void *m_end;
};
class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &other);
	~INIException();
	char *mFailureMessage;
	int m_argCount;
};
extern "C" __declspec(dllimport) int __cdecl _strcmpi(const char *a, const char *b);
class Eva
{
public:
	int rva001DE78E(const AsciiString *key) throw();
	int rva001DE9C4(const char *key);
private:
	char m_pad[0x34];
	Rva00056F61 m_table34;
	int m_pad40;
	int m_flag44;
	Rva00056F61 m_table48;
};
int Eva::rva001DE9C4(const char *key)
{
	if (_strcmpi("None", key) == 0)
		return -1;
	int id;
	if (m_flag44 == 0)
	{
		Rva0041534BIter it(0, &m_table48);
		{
			AsciiString tmp(key);
			it = Rva0041534BIter(m_table48.rva00056F61(&tmp), &m_table48);
		}
		if (it.m_node == 0)
			id = -1;
		else
		{
			char *node = (char *)it.m_node;
			int *value = (int *)(node + 8);
			id = *value;
		}
	}
	else
	{
		AsciiString tmp(key);
		id = rva001DE78E(&tmp);
	}
	if (id == -1)
		throw INIException(3, "Expected a recognized Eva event name or 'None'; got '%s'", key);
	return id;
}
