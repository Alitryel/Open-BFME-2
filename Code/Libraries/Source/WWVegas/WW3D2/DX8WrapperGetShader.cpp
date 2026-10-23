// cl: /DNDEBUG /MD
// DX8Wrapper::Get_Shader(ShaderClass&), retail 0x0010852B (13B): the Zero
// Hour dx8wrapper.h inline, out of line -- copies render_state.shader
// (DX8Wrapper::render_state at VA 0x00DEE5D8, whose first member is the
// shader) to the caller's ShaderClass. It sits in the shadow-code run, where
// a unit took it out of line; no direct caller reaches it in retail.
// upstream: GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.h
class ShaderClass
{
public:
	unsigned int ShaderBits;
};

struct RenderStateStruct
{
	ShaderClass shader;
};

class DX8Wrapper
{
public:
	static void Get_Shader(ShaderClass &shader);
protected:
	static RenderStateStruct render_state;
};

// The inline is emitted as the select-any copy other units can also emit;
// this anchor keeps it emitted here (it is not retail code).
inline void DX8Wrapper::Get_Shader(ShaderClass &shader)
{
	// Copy the single word directly; no competing ShaderClass assignment body.
	shader.ShaderBits = render_state.shader.ShaderBits;
}

extern void (*const g_bfmeDX8GetShaderAnchor)(ShaderClass &);
void (*const g_bfmeDX8GetShaderAnchor)(ShaderClass &) = &DX8Wrapper::Get_Shader;
