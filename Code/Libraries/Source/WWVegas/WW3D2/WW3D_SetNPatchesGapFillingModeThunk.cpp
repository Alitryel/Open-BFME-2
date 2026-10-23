// cl: /DNDEBUG /MD /EHsc
// Clean C++ donor: Open-BFME/Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69,
// game/Libraries/Source/WWVegas/WW3D2/WW3D_SetNPatchesGapFillingModeThunk.cpp.
// Native BFME2 0x00116E50 has a padded 31B boundary and precedes the rowed
// Set_NPatches_Level at 0x00116E70. It compares/stores VA 0x00DB5F90 and
// calls the rowed DX8MeshRendererClass::Invalidate (0x00145FA0) with false
// on the renderer pointer at 0x00DF363C, as the level setter also does.
// Those bytes, shared renderer/callee and sibling flow support donor identity.
// Enum names/values remain donor facts; the native body only copies its value.
// Reference source supplies the unchanged-if-equal behavior. The mode uses
// WW3D's existing static member defined in ww3d.cpp, keeping one real provider.

class DX8MeshRendererClass
{
public:
	void Invalidate( bool shutdown );
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;


// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	enum NPatchesGapFillingModeEnum {
		NPATCHES_GAP_FILLING_DISABLED,
		NPATCHES_GAP_FILLING_ENABLED,
		NPATCHES_GAP_FILLING_FORCE
	};

	static void Set_NPatches_Gap_Filling_Mode( NPatchesGapFillingModeEnum mode );
private:
	static NPatchesGapFillingModeEnum NPatchesGapFillingMode;
};

void WW3D::Set_NPatches_Gap_Filling_Mode( NPatchesGapFillingModeEnum mode )
{
	if( NPatchesGapFillingMode != mode ) {
		NPatchesGapFillingMode = mode;
		TheDX8MeshRenderer->Invalidate( false );
	}
}
