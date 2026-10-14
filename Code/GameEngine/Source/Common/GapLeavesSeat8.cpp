// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Leaf bodies from unrowed .text gaps (no calls), each bounded by its
// neighbour's ret or padding and its own ret. Retail bytes establish every
// shape; owning classes are not recovered, so each keeps an address-derived
// name and a view of only the members it touches. Each mirrors the
// instruction skeleton of an already matched twin named in its comment.

class LivingWorldManager;
extern LivingWorldManager *TheLivingWorldManager;
extern unsigned char g_00E01EA8;

// --- 0x0024C80D (12B): complement seven consecutive 32-bit words in place
// (twin: Rva00332E83BitWords::flip, four words).
class Rva0024C80DBitWords
{
public:
	void flip();
	unsigned int m_words[7];
};
void Rva0024C80DBitWords::flip()
{
	for (unsigned int i = 0; i < 7; ++i)
		m_words[i] = ~m_words[i];
}

// --- 0x002BE8ED (12B): the byte at +0x2C0 of TheLivingWorldManager (VA
// 0x00DFE1C8), ignoring the receiver (twin: Rva00DFE1C8Host::rva00210DC9).
struct Rva002BE8EDView
{
	char m_pad000[0x2C0];
	bool m_2C0;
};
class Rva002BE8EDHost
{
public:
	bool rva002BE8ED();
};
bool Rva002BE8EDHost::rva002BE8ED()
{
	return ((Rva002BE8EDView *)TheLivingWorldManager)->m_2C0;
}

// --- 0x0020483D (11B): clears the words at +4 and +0xC and returns this
// (twin: Rva002B599FZeroView::rva002B599F).
class Rva0020483DZeroView
{
public:
	Rva0020483DZeroView *rva0020483D();
private:
	unsigned int m_00;
	unsigned int m_04;
	unsigned int m_08;
	unsigned int m_0C;
};
Rva0020483DZeroView *Rva0020483DZeroView::rva0020483D()
{
	m_04 = 0;
	m_0C = 0;
	return this;
}

// --- 0x00215EEC (11B, RET4): the indexed float of the array at +0x3C
// (twin: Rva00427157::rva004270FA).
class Rva00215EECFloats
{
public:
	float rva00215EEC(int index);
private:
	char m_pad00[0x3C];
	float m_values[1];
};
float Rva00215EECFloats::rva00215EEC(int index)
{
	return m_values[index];
}

// --- 0x001E361A (10B, cdecl): stores the byte argument into the global byte
// at VA 0x00E01EA8 (twin: Rva00117A70SetFlag).
void Rva001E361ASetFlag(unsigned char value)
{
	g_00E01EA8 = value;
}

// --- 0x002041A2 (10B, RET8): returns the word at +8 of the first stack
// argument, ignoring the receiver and the second argument (twin:
// TerrainRoadCollection::nextRoad 0x00314C13).
struct Rva002041A2Item
{
	char m_pad00[8];
	void *m_08;
};
class Rva002041A2Host
{
public:
	void *rva002041A2(const Rva002041A2Item *item, int unused);
};
void *Rva002041A2Host::rva002041A2(const Rva002041A2Item *item, int)
{
	return item->m_08;
}

// --- 0x00210C7D (10B, RET4): the address of the indexed dword of the
// receiver (twin: Vector3::operator[] 0x007173D0).
class Rva00210C7DWords
{
public:
	int &rva00210C7D(int index);
	int m_words[1];
};
int &Rva00210C7DWords::rva00210C7D(int index)
{
	return m_words[index];
}

// --- 0x0023C3FA (10B, RET4): stores the byte argument at +0x6D (twin:
// DockUpdate::setDockCrippled).
class Rva0023C3FAFlag
{
public:
	void set(bool value);
private:
	char m_pad00[0x6D];
	bool m_6D;
};
void Rva0023C3FAFlag::set(bool value)
{
	m_6D = value;
}

// --- 0x0023D37F (10B): bit 0 of the dword at +0x94 (twin:
// SegmentedLineClass::Are_End_Caps_Enabled).
class Rva0023D37FFlags
{
public:
	int rva0023D37F() const;
private:
	char m_pad00[0x94];
	unsigned int m_flags;
};
int Rva0023D37FFlags::rva0023D37F() const
{
	return m_flags & 1;
}
