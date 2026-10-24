// cl: /MD
// ?Rva004DF8D8Test@@YA_NPBUVec2@@00MMMM@Z @0x004DF8D8 133B
// Evidence: EBP-frame SSE comiss/divss/mulss shape; 3 Vec2 ptrs + 4 floats; dot/cross/sum-squared test; caller at 0x0028F38A.
struct Vec2
{
	float x;
	float y;
};
bool __cdecl Rva004DF8D8Test(const Vec2 *vec2, const Vec2 *b, const Vec2 *dir, float f1, float lateralScale, float rearScale, float f4)
{
	float dx = vec2->x - b->x;
	float dy = vec2->y - b->y;
	float dot = dir->x * dx + dy * dir->y;
	float cross = dx * dir->y - dir->x * dy;
	cross /= lateralScale;
	if (dot < 0.0f)
		dot /= rearScale;
	float sum = f1 + f4;
	float tot = cross * cross + dot * dot;
	float ss = sum * sum;
	if (tot < ss)
		return true;
	return false;
}
