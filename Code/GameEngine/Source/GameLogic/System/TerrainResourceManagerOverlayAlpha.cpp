// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Retail 0x0035A61F..0x0035A8D7 (696 bytes, ret 0x10).
// WorldBuilder 0x00E61580 has the same thirteen isCellClaimable calls
// (WB 0x00E61100) and neighbour alpha weights. Its divisions are expressions
// at each call, not cached coordinate locals. Letting MSVC share those
// expressions reproduces the retail prologue and all following instructions.
// Target constants: centre weight 12; edges 4; diagonals 2/3; outer cells 1.
// Method name is address-derived; owner identity follows the named WB callee
// and TerrainResourceManager neighbours. Colour is a packed ARGB dword.
// ?rva0035A61F@TerrainResourceManager@@QAEXPAIHHH@Z
typedef unsigned int Rva0035A61FColor;

class TerrainResourceManager
{
public:
	bool isCellClaimable(int, int, int, int, bool, int);
	void rva0035A61F(Rva0035A61FColor *color, int x, int y, int claimant);
private:
	__forceinline bool isClaimable(int cx, int cy, int claimant)
	{
		return isCellClaimable(cx, cy, 0, 0, false, claimant);
	}
};

void TerrainResourceManager::rva0035A61F(Rva0035A61FColor *color, int x, int y, int claimant)
{
	if (!isClaimable((x / 2), (y / 2), claimant))
	{
		*color = 0;
	}
	else
	{
	float weight = 12.0f;
	if (!isClaimable(((x + 1) / 2), (y / 2), claimant))
		weight -= 4.0f;
	if (!isClaimable((x / 2), ((y + 1) / 2), claimant))
		weight -= 4.0f;
	if (!isClaimable(((x - 1) / 2), (y / 2), claimant))
		weight -= 4.0f;
	if (!isClaimable((x / 2), ((y - 1) / 2), claimant))
		weight -= 4.0f;
	if (!isClaimable(((x + 1) / 2), ((y + 1) / 2), claimant))
		weight -= 2.0f;
	if (!isClaimable(((x - 1) / 2), ((y - 1) / 2), claimant))
		weight -= 2.0f;
	if (!isClaimable(((x - 1) / 2), ((y + 1) / 2), claimant))
		weight -= 3.0f;
	if (!isClaimable(((x + 1) / 2), ((y - 1) / 2), claimant))
		weight -= 3.0f;
	if (!isClaimable((x + 2) / 2, (y / 2), claimant))
		weight -= 1.0f;
	if (!isClaimable((x - 2) / 2, (y / 2), claimant))
		weight -= 1.0f;
	if (!isClaimable((x / 2), (y + 2) / 2, claimant))
		weight -= 1.0f;
	if (!isClaimable((x / 2), (y - 2) / 2, claimant))
		weight -= 1.0f;
	if (weight <= 0.0f)
	{
		*color = 0;
	}
	else if (weight < 12.0f)
	{
		float alpha = (float)((unsigned char *)color)[3];
		*color = (*color & 0x00FFFFFF) | ((int)(alpha * (weight / 12.0f)) << 24);
	}
}
}
