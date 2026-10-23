// cl: /O1 /MD
//
// W3d_Shader_Reset, retail 0x001A441F, 58 bytes.

struct W3dShaderStruct
{
	unsigned char DepthCompare;
	unsigned char DepthMask;
	unsigned char ColorMask;
	unsigned char DestBlend;
	unsigned char FogFunc;
	unsigned char PriGradient;
	unsigned char SecGradient;
	unsigned char SrcBlend;
	unsigned char Texturing;
	unsigned char DetailColorFunc;
	unsigned char DetailAlphaFunc;
	unsigned char Pad0B;
	unsigned char AlphaTest;
	unsigned char PostDetailColorFunc;
	unsigned char PostDetailAlphaFunc;
	unsigned char Pad0F;
};

inline void W3d_Shader_Reset(W3dShaderStruct *w3dShader)
{
	unsigned char *p = (unsigned char *)w3dShader;
	p[0] = 3;
	p[1] = 1;
	p[2] = 0;
	p[3] = 0;
	p[4] = 0;
	p[5] = 1;
	p[6] = 0;
	p[7] = 1;
	p[8] = 0;
	p[9] = 0;
	p[10] = 0;
	p[11] = 0;
	p[12] = 0;
	p[13] = 0;
	p[14] = 0;
	p[15] = 0;
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. Taking each one's
// address keeps this unit's copy for its row; these pointers are not retail
// data.
void (*_bfmeInlineAnchor_W3d_Shader_Reset_0)(W3dShaderStruct *s) = &W3d_Shader_Reset;
