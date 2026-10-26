class AptCIH;
void bfmeUnpackTwoColors1280(float *output, const unsigned int *colors);

class BfmeSubmitter1283
{
public:
	void *bfmeSubmit1283(AptCIH *a1, int a2, int a3, int a4, int a5, int a6, int a7,
		float *colors, int a9, int a10, int a11, int zero);
	void bfmeSubmitColors1283(int character, int depth, int pCharacter, int name, int parent, int replace, int clipDepth,
		const unsigned int *colors, int matrix, int actions, int ratio);
};

void BfmeSubmitter1283::bfmeSubmitColors1283(int character, int depth, int pCharacter, int name, int parent,
	int replace, int clipDepth, const unsigned int *colors, int matrix, int actions, int ratio)
{
	float unpacked[8];
	if (colors != 0) {
		bfmeUnpackTwoColors1280(unpacked, colors);
		bfmeSubmit1283((AptCIH *)character, depth, pCharacter, name, parent, replace, clipDepth, unpacked, matrix, actions, ratio, 0);
	} else {
		bfmeSubmit1283((AptCIH *)character, depth, pCharacter, name, parent, replace, clipDepth, 0, matrix, actions, ratio, 0);
	}
}
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
