// cl: /DNDEBUG /MD
// ?rva000B3E96@W3DScriptedModelDraw@@QAEHH@Z retail 0x000B3E96 29B
// Random start frame over rowed GetGameClientRandomValue 0x0023404A: return
// GetGameClientRandomValue(0 arg-1 file 0x28F8). Evidence: mov eax-esp+4
// push 0x28f8 push 0xBC9C40 dec eax push eax push 0 E8 then add esp-0x10
// ret 4; callee YAHHHPADH int-int-char*-int. Thiscall member of the draw
// module: the sole caller (adjustAnimation 0x000BEE25 at 0x000BF5DC) loads
// ECX with the module before the call; the body leaves ECX unused.
int GetGameClientRandomValue(int lo, int hi, char *file, int line);
class W3DScriptedModelDraw
{
public:
	int rva000B3E96(int n);
};
int W3DScriptedModelDraw::rva000B3E96(int n)
{
	return GetGameClientRandomValue(0, n - 1, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngineDevice\\Source\\W3DDevice\\GameClient\\Drawable\\W3DScriptedModelDraw.cpp", 0x28F8);
}
