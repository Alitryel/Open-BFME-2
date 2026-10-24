// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva0055CFF0@Rva0055CFF0@@QAEXMMM@Z @0x0055CFF0 229B: draw 4 vertical box edges via TacticalView.
// Evidence: thiscall retC 3 floats vslot4 of BoxEmissionVolumeModule; rowed TheTacticalView; color 0xCCAFFFFF; 0 callers.

struct MiniBox
{
	float x;
	float y;
	float z;
};

class TacticalView
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10();
	virtual void drawBox(const MiniBox *a, const MiniBox *b, int color);
};

extern class View *TheTacticalView;

class Rva0055CFF0
{
public:
	void rva0055CFF0(float x, float y, float z);
	char m_pad[0x24];
	float m_halfSizeX;
	float m_halfSizeY;
	float m_halfSizeZ;
};

void Rva0055CFF0::rva0055CFF0(float x, float y, float z)
{
	int color = 0xCCAAFFFF;
	MiniBox top;
	MiniBox bottom;
	top.x = x + m_halfSizeX;
	top.y = y + m_halfSizeY;
	top.z = z + m_halfSizeZ;
	bottom.x = x + m_halfSizeX;
	bottom.y = y + m_halfSizeY;
	bottom.z = z - m_halfSizeZ;
	((TacticalView *)TheTacticalView)->drawBox(&top, &bottom, color);
	top.x = x - m_halfSizeX;
	bottom.x = x - m_halfSizeX;
	((TacticalView *)TheTacticalView)->drawBox(&top, &bottom, color);
	top.y = y - m_halfSizeY;
	bottom.y = y - m_halfSizeY;
	((TacticalView *)TheTacticalView)->drawBox(&top, &bottom, color);
	top.x = x + m_halfSizeX;
	bottom.x = x + m_halfSizeX;
	((TacticalView *)TheTacticalView)->drawBox(&top, &bottom, color);
}
