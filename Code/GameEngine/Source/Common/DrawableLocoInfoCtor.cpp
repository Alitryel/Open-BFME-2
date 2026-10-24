// cl: /O1 /MD /arch:SSE
// ??0DrawableLocoInfo@@QAE@XZ @0x00270098 192B
// BFME2 DrawableLocoInfo ctor from BFME1 donor game/GameEngine/Source/GameClient/Drawable.cpp 249-274
// and layout game/GameEngine/Source/GameClient/DrawablePhysicsXformWheels.cpp 57-75.
// Evidence: vtable 0x007FAD38 with deleting dtor at 0x00272349; new 0x58 callers at 0x00270843 0x00272FE6 0x00276D2B 0x0027A5C9 0x0027B4AF;
// filename C:\projects\bfme2patch103\bfme2\Code\GameEngine\Source\GameClient\Drawable.cpp lines 325-326;
// wobble 1.0 at +0x30 yawModulator pitchModulator random 0-2PI at +0x34 +0x38 wheelInfo at +0x3C.
typedef int Int;
typedef float Real;
float __cdecl GetGameClientRandomValueReal(float lo, float hi, char *file, int line);

struct TWheelInfo
{
	Real m_frontLeftHeightOffset;
	Real m_frontRightHeightOffset;
	Real m_rearLeftHeightOffset;
	Real m_rearRightHeightOffset;
	Real m_wheelAngle;
	Int m_framesAirborneCounter;
	Int m_framesAirborne;
};

class DrawableLocoInfo
{
public:
	virtual ~DrawableLocoInfo() {}
	DrawableLocoInfo() throw();
	Real m_pitch;
	Real m_pitchRate;
	Real m_roll;
	Real m_rollRate;
	Real m_yaw;
	Real m_accelerationPitch;
	Real m_accelerationPitchRate;
	Real m_accelerationRoll;
	Real m_accelerationRollRate;
	Real m_overlapZVel;
	Real m_overlapZ;
	Real m_wobble;
	Real m_yawModulator;
	Real m_pitchModulator;
	TWheelInfo m_wheelInfo;
};

DrawableLocoInfo::DrawableLocoInfo() throw()
{
	m_pitch = 0.0f;
	m_pitchRate = 0.0f;
	m_roll = 0.0f;
	m_rollRate = 0.0f;
	m_yaw = 0.0f;
	m_accelerationPitch = 0.0f;
	m_accelerationPitchRate = 0.0f;
	m_accelerationRoll = 0.0f;
	m_accelerationRollRate = 0.0f;
	m_overlapZVel = 0.0f;
	m_overlapZ = 0.0f;
	m_wobble = 1.0f;
	m_wheelInfo.m_frontLeftHeightOffset = 0.0f;
	m_wheelInfo.m_frontRightHeightOffset = 0.0f;
	m_wheelInfo.m_rearLeftHeightOffset = 0.0f;
	m_wheelInfo.m_rearRightHeightOffset = 0.0f;
	m_wheelInfo.m_framesAirborneCounter = 0;
	m_wheelInfo.m_framesAirborne = 0;
	m_wheelInfo.m_wheelAngle = 0.0f;
	m_yawModulator = GetGameClientRandomValueReal(0.0f, 6.28318530717958647692f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable.cpp", 325);
	m_pitchModulator = GetGameClientRandomValueReal(0.0f, 6.28318530717958647692f, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameClient\\Drawable.cpp", 326);
}
