// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// BFME2 View::View, retail RVA 0x0025EDE6 (271 bytes, RET).
// Target evidence: native 25EDE6..25EEF5 stores the View vftable 0x00BF6178,
// takes the id from View::m_idNext (0x00DBA970) and post-increments it, and
// zero/one-fills every field through +0xB0 (FOV 0.87266463 at +0x6C,
// 1.0 at +0x9C..+0xA8, bytes +0x44/+0x75 set).
// Donor: Zero Hour View::View supplies the class identity, the id allocation
// and the field names through the camera controls; fields past ZH's layout
// keep offset names. Structural inference from the WorldBuilder twin
// 0x00AA09F0 (unnamed, same stores in offset order): the position (+0x0C),
// guard-band bias (+0x78), the one-dword member at +0x80 and the triple at
// +0x8C are each set through an inline member call. Those inline members
// give retail's store schedule (the +0x8C address computed after the +0x80
// store). The member types are structural views, not recovered names.
class View {
public:
 virtual ~View();
 View();
protected:
 static unsigned m_idNext; // Zero Hour's protected static, defined in View.cpp
public:
 View *m_next;unsigned m_id;
 struct Position {float x,y,z; void set(){x=0;y=0;z=0;}} m_pos;
 int m_width,m_height,m_originX,m_originY;
 float m_angle,m_pitchAngle,m_maxZoom,m_minZoom,m_maxHeightAboveGround,m_minHeightAboveGround,m_zoom;
 bool m_zoomLimited;
 float m_defaultAngle,m_defaultPitchAngle,m_currentHeightAboveGround,m_terrainHeightUnderCamera;
 unsigned m_cameraLock;void *m_cameraLockDrawable;int m_lockType;float m_lockDist,m_heightAboveGround,m_FOV,m_unknown70;
 bool m_mouseLocked,m_okToAdjustHeight,m_snapImmediate;
 struct Bias {float x,y; void zero(){x=0;y=0;}} m_guardBandBias;
 struct Handle {void *p; Handle &operator=(void *v){p=v;return *this;}} m_unknown80;
 bool m_unknown84;unsigned m_unknown88;
 struct Triple {int x,y,z; void zero(){x=0;y=0;z=0;}} m_unknown8c;
 float m_unknown98,m_unknown9c,m_unknowna0,m_unknowna4,m_unknowna8,m_unknownac,m_unknownb0;
};
View::View() {
 m_next=0;m_id=m_idNext++;
 m_pos.set();
 m_width=0;m_height=0;m_originX=0;m_originY=0;
 m_angle=0;m_pitchAngle=0;m_maxZoom=0;m_minZoom=0;m_maxHeightAboveGround=0;m_minHeightAboveGround=0;m_zoom=0;
 m_zoomLimited=true;
 m_defaultAngle=0;m_defaultPitchAngle=0;m_currentHeightAboveGround=0;m_terrainHeightUnderCamera=0;
 m_cameraLock=0;m_cameraLockDrawable=0;m_lockType=0;m_lockDist=0;m_heightAboveGround=0;m_FOV=0.87266463f;m_unknown70=0;
 m_mouseLocked=false;m_okToAdjustHeight=true;m_snapImmediate=false;
 m_guardBandBias.zero();m_unknown80=0;m_unknown84=false;m_unknown88=0;
 m_unknown8c.zero();m_unknown98=0;m_unknown9c=1;m_unknowna0=1;m_unknowna4=1;m_unknowna8=1;m_unknownac=0;m_unknownb0=0;
}
