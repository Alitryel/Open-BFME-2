// cl: /O1 /MD /GX-
// ScriptList::clear, retail 0x003B7812 (36 B): swaps *this with a freshly
// constructed empty list and lets the temporary's destructor release the old
// contents (REL32 from SidesInfo::init 0x32CDD5).

class Rva003B761E
{
public:
	Rva003B761E();

private:
	char m_data[0x20];
};

class ScriptListBase
{
public:
	ScriptListBase();

private:
	void *m_vtable;
	void *m_firstGroup;
	void *m_firstScript;
};

class ScriptList : public ScriptListBase
{
public:
	ScriptList();
	~ScriptList();
	void clear();
	void swap(ScriptList *other);

private:
	Rva003B761E m_first;
	Rva003B761E m_second;
};

// Retail builds the empty list as an argument temporary whose constructor
// result is the receiver of swap (mov ecx,eax; a named local gives lea), and
// keeps 'this' unpushed until after that constructor call. Passing the
// temporary and 'this' to a forced-inline helper reproduces both.
static __forceinline void swapIn(ScriptList &t, ScriptList *o) { t.swap(o); }
void ScriptList::clear()
{
	swapIn(ScriptList(), this);
}
