// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva003E40AF@ScriptConditions@@QAEHH@Z @0x003E40AF 35B switch 0 to 1 plus 1 to 2 plus 2 to 4 else minus 1.
// Evidence: callers 0x003E56FC (ScriptConditions::evaluateEnemySighted) and 0x003E687D (ScriptConditions::rva003E6835) load this into ECX before the call; ret 4, ECX unused.
class ScriptConditions
{
public:
	int rva003E40AF(int v);
};

int ScriptConditions::rva003E40AF(int v)
{
	switch (v)
	{
	case 0:
		return 1;
	case 2:
		return 4;
	case 1:
		return 2;
	default:
		return -1;
	}
}
