// cl: /DNDEBUG /MD
// WW3D::Activate_Snapshot(bool), retail 0x00116E10 (10B): the Zero Hour
// ww3d.h inline, out of line -- stores its argument to WW3D::SnapshotActivated
// (VA 0x00DEC3FD). It sits in the int3-padded ww3d.cpp run; no direct caller
// reaches it in retail.
// upstream: GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/ww3d.h
class WW3D
{
public:
	static void Activate_Snapshot(bool b) { SnapshotActivated = b; }
private:
	static bool SnapshotActivated;
};

// Keeps the inline's select-any copy emitted here (not retail code).
extern void (*const g_bfmeWW3DActivateSnapshotAnchor)(bool);
void (*const g_bfmeWW3DActivateSnapshotAnchor)(bool) = &WW3D::Activate_Snapshot;
