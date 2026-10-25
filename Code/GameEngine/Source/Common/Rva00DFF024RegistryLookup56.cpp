// cl: /O1 /MD
//
// ?lookup56@Rva00DFF024Registry@@QAEPAXHH@Z
// RVA 0x002D2371 size 48. Pinned fallback lookup; tries (a 5) then (a 6) when
// b is -1 else (a b). Evidence: pin name; callers at 0x22329A (unclaimed) and
// 0x3163DA in parseWinClass; callee lookup at 0x2D225F via pin; neighbours in
// GameEngineDeletingBaseDerived.cpp share /O1 /MD.

enum NameKeyType { NAMEKEY_INVALID = 0 };

// The registry is TheFunctionLexicon; its lookup is FunctionLexicon::findFunction
// 0x002D225F (rowed in Common/System/FunctionLexicon.cpp), reached through
// this unit's forwarding view.
class WindowLayout;
typedef void (*WindowLayoutInitFunc)(WindowLayout *layout, void *userData);

class Rva00DFF024Registry;
class FunctionLexicon
{
public:
	struct TableEntry
	{
		NameKeyType key;
		const char *name;
		void *func;
	};

	enum TableIndex
	{
		TABLE_ANY = -1,
		TABLE_WIN_LAYOUT_INIT = 7,		// BFME2 slots, from winLayoutInitFunc
		TABLE_WIN_LAYOUT_DEVICEINIT = 8,
		MAX_FUNCTION_TABLES = 12		// BFME2: findFunction's loop bound
	};

	WindowLayoutInitFunc winLayoutInitFunc(NameKeyType key, TableIndex index = TABLE_ANY);

protected:
	friend class Rva00DFF024Registry;
	void *keyToFunc(NameKeyType key, TableEntry *table);
	void *findFunction(NameKeyType key, TableIndex index);

private:
	unsigned char m_subsystem[0xC];			// SubsystemInterface base (BFME2 size)
	TableEntry *m_tables[MAX_FUNCTION_TABLES];	// +0x0C
};

class Rva00DFF024Registry
{
public:
    __declspec(dllimport) __forceinline void *lookup(int a, int b) { return ((FunctionLexicon *)(void *)this)->findFunction((NameKeyType)a, (FunctionLexicon::TableIndex)b); }
    void *lookup56(int a, int b);
    void *lookup34(int a, int b);
};

void *Rva00DFF024Registry::lookup56(int a, int b)
{
    if (b == -1) {
        void *r = lookup(a, 5);
        if (r)
            return r;
        return lookup(a, 6);
    }
    return lookup(a, b);
}

void *Rva00DFF024Registry::lookup34(int a, int b)
{
    if (b == -1) {
        void *r = lookup(a, 3);
        if (r)
            return r;
        return lookup(a, 4);
    }
    return lookup(a, b);
}
