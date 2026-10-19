// ?evaluate@Rva00160150@@QAEXAAURva00160240Pose@@MAAMMPAPAE@Z
// partial score=0.82 date=2026-10-16
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
//
// ?rva00160150@Rva00160150@@QBEXPAMHH@Z, retail 0x00160150 (113 bytes,
// RET 0x0C): a three-channel vector read placed after
// MotionChannelClass::Get_Vector_As_Quat in the raw-animation code. Each of
// the X/Y/Z channel pointers (+0/+4/+8) fills its component of the output
// through its slot 3 (+0x0C) with the frame and the extra word; a missing
// channel leaves 0. No direct caller or table slot was found, so the owner
// and channel interface keep address-derived names.
#include "quat.h"
class ChunkLoadClass;
class BFME2MotionChannel {
public:
 virtual bool Load(ChunkLoadClass &);
 virtual ~BFME2MotionChannel();
 virtual int UnknownSlot2();
 virtual void UnknownSlot3(float,float *,unsigned char **);
 virtual void UnknownSlot4(float,Vector3 *,unsigned char **);
 virtual void UnknownSlot5(float,Quaternion *,unsigned char **);
 virtual int UnknownSlot6();
 int Type,Pivot,Count,Components;
};
struct Rva00160240Pose {
 Quaternion Rotation;
 Vector3 Position;
 __forceinline Vector3 rotate(const Vector3 &v) const {
  const Quaternion &q=Rotation;
  float x=(q.Y*v.Z-q.Z*v.Y)+q.W*v.X;
  float y=q.W*v.Y-(q.X*v.Z-q.Z*v.X);
  float z=(q.X*v.Y-q.Y*v.X)+q.W*v.Z;
  float w=0.0f-(q.Y*v.Y+q.X*v.X+q.Z*v.Z);
  return Vector3((q.Y*z-q.Z*y)+(q.W*x-q.X*w),
    (q.W*y-q.Y*w)-(q.X*z-q.Z*x),
    (q.X*y-q.Y*x)+(q.W*z-q.Z*w));
 }
 __forceinline void Translate(const Vector3 &v){ Position+=rotate(v); }
 __forceinline void Rotate(const Quaternion &q){
  Quaternion saved(Rotation);
  Rotation.X=(saved.Y*q.Z-q.Y*saved.Z)+q.W*saved.X+saved.W*q.X;
  Rotation.Y=q.W*saved.Y+saved.W*q.Y-(saved.X*q.Z-q.X*saved.Z);
  Rotation.Z=(saved.X*q.Y-q.X*saved.Y)+q.W*saved.Z+saved.W*q.Z;
  Rotation.W=q.W*saved.W-(q.Z*saved.Z+q.Y*saved.Y+q.X*saved.X);
 }
};

class Rva00160150Channel
{
public:
	virtual void s00(); virtual void s01(); virtual void s02();
	virtual void getValue(int frame, float *out, int extra);	// +0x0C
	virtual void s04();
	virtual void getValues(int frame, float *out, int extra);	// +0x14
};

class Rva00160150
{
public:
	void evaluate(Rva00160240Pose &pose,float scale,float &fade,float frame,unsigned char **cursor);
	void rva00160150(float *out, int frame, int extra) const;
	bool rva001601D0(float *out, int frame, int extra) const;
	void rva00160200(float *out, int frame, int extra) const;
private:
	Rva00160150Channel *m_x;	// +0x00
	Rva00160150Channel *m_y;	// +0x04
	Rva00160150Channel *m_z;	// +0x08
	Rva00160150Channel *m_rotation;	// +0x0C
	Rva00160150Channel *m_scale;	// +0x10
};

void Rva00160150::rva00160150(float *out, int frame, int extra) const
{
	if (m_x)
		m_x->getValue(frame, &out[0], extra);
	else
		out[0] = 0.0f;
	if (m_y)
		m_y->getValue(frame, &out[1], extra);
	else
		out[1] = 0.0f;
	if (m_z)
		m_z->getValue(frame, &out[2], extra);
	else
		out[2] = 0.0f;
}

// Retail 0x001601D0 (39 bytes) and 0x00160200 (51 bytes), the next two readers of the same
// record: the +0x0C channel fills a multi-component value through its slot 5 (+0x14) and
// reports whether the channel exists; the +0x10 channel fills one float through slot 3, or
// leaves 1.0 when it is missing. Neither has a direct caller or table slot.
bool Rva00160150::rva001601D0(float *out, int frame, int extra) const
{
	if (!m_rotation)
		return false;
	m_rotation->getValues(frame, out, extra);
	return true;
}

void Rva00160150::rva00160200(float *out, int frame, int extra) const
{
	if (!m_scale) {
		*out = 1.0f;
		return;
	}
	m_scale->getValue(frame, out, extra);
}

void Rva00160150::evaluate(Rva00160240Pose &pose,float scale,float &fade,float frame,unsigned char **cursor)
{

 struct { Quaternion rotation; Vector3 translation; } s;
 if(((BFME2MotionChannel*)m_x))((BFME2MotionChannel*)m_x)->UnknownSlot3(frame,&s.translation.X,cursor);else s.translation.X=0;
 if(((BFME2MotionChannel*)m_y))((BFME2MotionChannel*)m_y)->UnknownSlot3(frame,&s.translation.Y,cursor);else s.translation.Y=0;
 if(((BFME2MotionChannel*)m_z))((BFME2MotionChannel*)m_z)->UnknownSlot3(frame,&s.translation.Z,cursor);else s.translation.Z=0;
 s.translation*=scale;
 if(((BFME2MotionChannel*)m_rotation)){
  ((BFME2MotionChannel*)m_rotation)->UnknownSlot5(frame,&s.rotation,cursor);
  pose.Translate(s.translation);
  pose.Rotate(s.rotation);
 }else pose.Translate(s.translation);
 if(((BFME2MotionChannel*)m_scale))((BFME2MotionChannel*)m_scale)->UnknownSlot3(frame,&fade,cursor);else fade=1.0f;
}
