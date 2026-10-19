// ?getPosition@LightningEmissionModule@FXParticleSystem@@UAE?AUCoord3D@@MMHH@Z
// partial score=0.55 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /ICode/Libraries/Include /Ireference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib
#define COORD3D_VIEW_DTOR
#include "Lib/Coord3DCtorView.h"
#include "matrix3d.h"
#include "wwmath.h"

class GameClientRandomVariable
{
public:
	float getValue() const;
private:
	int m_type;
	float m_low;
	float m_high;
};

class ParticleSystem;

class RvaSmartPtr12
{
public:
	void rva0004CBC0() throw();
	~RvaSmartPtr12() throw()
	{
		if (m_ptr != 0)
			rva0004CBC0();
	}
	ParticleSystem *m_ptr;
	int m_04;
	int m_08;
};

class Rva0055DDB6SmartField
{
public:
	RvaSmartPtr12 get() const throw();
};

ParticleSystem *Make001FCBD7();


static __forceinline void InvXform(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	float dx = in.X - A[0][3];
	float dy = in.Y - A[1][3];
	float dz = in.Z - A[2][3];
	out->X = A[0][0] * dx + A[1][0] * dy + A[2][0] * dz;
	out->Y = A[0][1] * dx + A[1][1] * dy + A[2][1] * dz;
	out->Z = A[0][2] * dx + A[1][2] * dy + A[2][2] * dz;
}

struct ParticleSystemView
{
	char pad[0xBC];
	Matrix3D m_transform;
	char pad2[0x188 - 0xBC - sizeof(Matrix3D)];
	Vector3 m_position;
	bool m_isLocal;
};

namespace FXParticleSystem
{

class __declspec(novtable) ParticleModulePrimary
{
public:
	virtual ~ParticleModulePrimary() = 0;

private:
	unsigned char m_state[0x10];
};

class __declspec(novtable) ParticleModuleClassInterface
{
public:
	virtual void *getModuleClass() const = 0;
};

class __declspec(novtable) EmissionVolumeModuleInterface
{
public:
	virtual Coord3D getVelocity(const Coord3D *, float, float) = 0;
};

template <int Category>
class DefaultParticleModule
	: public ParticleModulePrimary,
	  public ParticleModuleClassInterface,
	  public EmissionVolumeModuleInterface
{
};

class __declspec(novtable) EmissionVolumeInfo
{
public:
	virtual ~EmissionVolumeInfo() = 0;

protected:
	bool m_is_hollow;
	unsigned char m_alignment[3];
};

class LightningEmissionInfo : public EmissionVolumeInfo
{
protected:
	Coord3D m_start;
	Coord3D m_end;
	GameClientRandomVariable m_amplitude1;
	GameClientRandomVariable m_frequency1;
	GameClientRandomVariable m_phase1;
	GameClientRandomVariable m_amplitude2;
	GameClientRandomVariable m_frequency2;
	GameClientRandomVariable m_phase2;
	GameClientRandomVariable m_amplitude3;
	GameClientRandomVariable m_frequency3;
	GameClientRandomVariable m_phase3;
};

class LightningEmissionModule
	: public DefaultParticleModule<5>, public LightningEmissionInfo
{
public:
	virtual Coord3D getPosition(float, float, int, int);
};

Coord3D LightningEmissionModule::getPosition(float, float, int index, int count)
{
	Coord3D result;
	if (count > 1 && count < 30)
	{
		static Coord3D s_points[30];
		if (index == 0)
		{
			Coord3D start;
			Coord3D end;
			start = m_start;
			end = m_end;
			RvaSmartPtr12 handle = ((const Rva0055DDB6SmartField *)this)->get();
			ParticleSystem *sys = handle.m_ptr;
			if (!sys)
				sys = Make001FCBD7();
			if (((ParticleSystemView *)sys)->m_isLocal)
			{
				ParticleSystem *ps = handle.m_ptr;
				if (!ps)
					ps = Make001FCBD7();
				const Matrix3D &m = ((ParticleSystemView *)ps)->m_transform;
				Vector3 a;
				InvXform(m, m.Get_Translation(), &a);
				start = *(Coord3D *)&a;
				ParticleSystem *pe = handle.m_ptr;
				if (!pe)
					pe = Make001FCBD7();
				const Vector3 *p = &((ParticleSystemView *)pe)->m_position;
				Vector3 b;
				InvXform(m, Vector3(p->X, p->Y, p->Z), &b);
				end = *(Coord3D *)&b;
			}
			Coord3D delta;
			delta.x = end.x - start.x;
			delta.y = end.y - start.y;
			delta.z = end.z - start.z;
			float amplitude1 = m_amplitude1.getValue();
			float frequency1 = m_frequency1.getValue();
			float phase1 = m_phase1.getValue();
			float amplitude2 = m_amplitude2.getValue();
			float frequency2 = m_frequency2.getValue();
			float phase2 = m_phase2.getValue();
			float amplitude3 = m_amplitude3.getValue();
			float frequency3 = m_frequency3.getValue();
			float phase3 = m_phase3.getValue();
			Coord3D dir;
			dir.x = delta.x;
			dir.y = delta.y;
			dir.z = delta.z;
			dir.normalize();
			Coord3D up(0.0f, 0.0f, 1.0f);
			Coord3D perp;
			perp.x = up.y * dir.z - up.z * dir.y;
			perp.y = up.z * dir.x - up.x * dir.z;
			perp.z = up.x * dir.y - up.y * dir.x;
			float step = 1.0f / (float)(count - 1);
			float t = 0.0f;
			for (int i = 0; i < count; ++i)
			{
				float envelope = 0.5f - WWMath::Fabs(0.5f - t);
				float s1 = WWMath::Sin(t * frequency1 + phase1) * envelope * amplitude1;
				float s2 = WWMath::Sin(t * frequency2 + phase2) * envelope * amplitude2;
				float s3 = WWMath::Sin(t * frequency3 + phase3) * envelope * amplitude3;
				float x = t * delta.x + start.x;
				x += perp.x * s1;
				x += perp.x * s2;
				x += perp.x * s3;
				s_points[i].x = x;
				float y = t * delta.y + start.y;
				y += perp.y * s1;
				y += perp.y * s2;
				y += perp.y * s3;
				s_points[i].y = y;
				float z = t * delta.z + start.z;
				z += perp.z * s1;
				z += perp.z * s2;
				z += perp.z * s3;
				s_points[i].z = z;
				t += step;
			}
		}
		result.x = s_points[index].x;
		result.y = s_points[index].y;
		result.z = s_points[index].z;
	}
	return result;
}

}
