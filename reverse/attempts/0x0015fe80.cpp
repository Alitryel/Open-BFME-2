// ?rva0015FE80@Rva0015F920@@QAEXABUGapVec3@@@Z
// partial score=0.9520060433103912 date=2026-10-15
// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Native15FE80..15FFC2 RET4: full322-byte quaternion/translation update.
// Native adjacent constructors15F920/15F9A0 and composition15F9E0 prove
// quaternion XYZ/W at0..C plus translation XYZ at10..18 (28-byte receiver).
// BFME1 a7c38d3b quat.h Rotate_Vector is the semantic guide; the arithmetic
// and grouping below are adapted from target bytes, not a donor byte match.
// Receiver and argument spellings are structural, not original-name claims.
// Port the three added inline adapters and this method into the current
// Code/GameEngine/Source/Common/GapBodiesGE47.cpp owner; do not replace its
// unrelated matched methods. R10 current owner gate passes8/8. This reduced
// bank reproduces the same322-byte body without unrelated gap functions.
// Residue: target hoists quaternion-X into XMM5 before the dot product and
// adds (W*rx-X*rw); compiler forms the reversed term and subtracts it. Y/Z
// and return match. No calls, relocations, EH, new pins or assembly.
struct GapVec3;
struct GapQuat
{
	float x;
	float y;
	float z;
	float w;
 void Rotate(const GapVec3&,GapVec3*) const;
};

struct GapVec3
{
 GapVec3() {}
 GapVec3(float ax,float ay,float az):x(ax),y(ay),z(az) {}
 GapVec3&operator=(const GapVec3&v) {x=v.x;y=v.y;z=v.z;return *this;}
 GapVec3&operator+=(const GapVec3&v) {x+=v.x;y+=v.y;z+=v.z;return *this;}
	float x;
	float y;
	float z;
};

class Rva0015F920
{
public:
	Rva0015F920(bool identity);
	Rva0015F920(const GapQuat &q, const GapVec3 &t);
 void rva0015FE80(const GapVec3 &);
private:
	GapQuat m_q;
	GapVec3 m_t;
};


// ?GapQuat::Rotate absent-from-retail
inline void GapQuat::Rotate(const GapVec3&v,GapVec3*out) const {
 float rx=(y*v.z-v.y*z)+v.x*w;
 float ry=v.y*w-(x*v.z-v.x*z);
 float rz=(v.y*x-y*v.x)+v.z*w;
 float rw=-((v.x*x+v.y*y)+v.z*z);
 out->x=(y*rz-z*ry)-(x*rw-w*rx);
 out->y=(w*ry-y*rw)-(x*rz-z*rx);
 out->z=(w*rz-z*rw)+(x*ry-y*rx);
}
void Rva0015F920::rva0015FE80(const GapVec3&v) {GapVec3 t;m_q.Rotate(v,&t);m_t+=t;}
