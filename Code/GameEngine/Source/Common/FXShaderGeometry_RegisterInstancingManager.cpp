// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?RegisterInstancingManager@FXShaderGeometry@@SAXPAX@Z @0x0018C0E7 10B: store arg to g_00DFCEBC caller 0x0041FD27 passes edi
extern int g_00DFCEBC;

class FXShaderGeometry
{
public:
	static void RegisterInstancingManager(void *p);
};
// WorldBuilder FXShaderGeometry::RegisterInstancingManager, WB VA 0x00A3A8C0 (callsite lead, score 1.0).
void __cdecl FXShaderGeometry::RegisterInstancingManager(void *p)
{
	g_00DFCEBC = (int)p;
}
