// cl: /O1 /MD /Oi-
// ?Rva00542425Skip@@YAPADPAD@Z @0x00542425 36B
// Identifier-char skip: advances past [A-Za-z0-9_] via isalnum IAT and '_' check
// returning first non-ident pointer. Evidence: retail bytes unlock lane plus two
// callers in 0x005424C4 and isalnum import and underscore literal.
// Static with internal caller in same TU restores compiler-private EAX-to-ESI
// handoff (mov esi eax). Precedent static intToHexDigit rowed in
// quoted_printable.cpp and shape-lever EAX-to-ESI handoff. Caller stub keeps the
// static emitted with EAX ABI until real 0x005424C4 lands here.
extern "C" __declspec(dllimport) int __cdecl isalnum(int c);

static char *Rva00542425Skip(char *p)
{
	char *s = p;
	for (;;) {
		char c = *s;
		if (c == 0)
			break;
		if (isalnum(c)) {
			s++;
			continue;
		}
		if (*s == '_') {
			s++;
			continue;
		}
		break;
	}
	return s;
}

// ?Rva00542449Find@@YAPADPADD@Z @0x00542449 16B
// Character find: advances until NUL or the stack-passed character, returning
// the stop pointer. Same EAX-pointer private convention as Rva00542425Skip
// directly before it (retail bytes: live-in eax, char at [esp+4], plain ret).
static char *Rva00542449Find(char *p, char c)
{
	char *s = p;
	for (;;) {
		char ch = *s;
		if (ch == 0)
			break;
		if (ch == c)
			break;
		s++;
	}
	return s;
}

// ?Rva00542425Caller@@YAPADPAD@Z present-unmatched
char *Rva00542425Caller(char *p)
{
	char *q = Rva00542425Skip(p);
	q = Rva00542449Find(q, ',');
	return Rva00542425Skip(q);
}
