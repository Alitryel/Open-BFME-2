// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.988 date=2026-10-14
// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z
// partial score=0.988 date=2026-10-14 r6 W7-D1
// ?getPortTransform@BuildAssistant@@QAE_NPBUCoord3D@@PBVThingTemplate@@MPAMPAU2@@Z @0x00392802 (725B)
// FRAGMENT for Code/GameEngine/Source/Common/System/BuildAssistant.cpp (production TU, /O1 /EHs /MD /arch:SSE).
//
// r6 recipe (from the WB 0xF9B980 debug body): the original normalization is the
// inlined MathCoord3D.h Coord3D::operator/=(Real) (WB sub_41FA20:
// inv=1.0f/d; x*=inv; y*=inv; z*=inv) applied to the averaged sample sums, and
// the two Coord3D accessors used later (length 0x3571 =69B, normalize 0x35B6 =86B)
// must be visible out of line in the TU, or cl spills dir.z across the
// isUnderwater call and the body is 730B/+0xA3:
//     inline __declspec(noinline) float Coord3D::length() const {...}
//     inline __declspec(noinline) void  Coord3D::normalize()     {...}
//     static Real s_portAngleOffset = PI / 2;   // retail 0x00DC0854 = 0x3FC90FDB
//     double __cdecl Rva000422A0Atan2( float y, float x );
// The volatile casts on the sum components reproduce retail's memory homes.
//
// Current state: 725B size-exact, nd9. Residue is the WATER normalization's
// list schedule only (0x3928D0..0x3928FE): retail loads [ebp-0x30] and
// [ebp-0x2C] before `movaps xmm1,xmm0 / divss xmm1,xmm3` and [ebp-0x34] after;
// ours divides first and then loads all three. Everything else (guards, land
// normalization, dir sub/mul cluster, length/normalize calls, ground-height
// block and atan2 tail) already matches.
// Exhausted without moving it: volatile pattern 8x8 over both blocks (best
// land=xyz water=yz = current), statement order 6x6 both blocks, named locals
// (nd34), _ReadWriteBarrier at every boundary (>=147), IR-load-count dead
// re-reads (nd9), natural operator/=-style helpers with no volatile (711B/nd149),
// block swap (nd154), pointer/volatile-pointer reads and *= forms (worse).
// Next ideas: flag-level /Ob1 or scheduler knobs, or an IR-order change that
// makes the divide depend on the first two loads (e.g. a spelling cl cannot
// sink), not more local/barrier permutations.
//
// WB identity: BuildAssistant::getPortTransform (BuildAssistant.cpp:2124);
// retail assert line 2124. No ZH analogue (BFME2-new naval port placement).
// The statics are file-static (COFF storage STATIC), so data_rows cannot own
// 0x00DC0854 directly; the ledger anchors _s_maxWaterLandSampleRatio 0x9C0858
// and derives _s_portAngleOffset 0x9C0854 from the same section run.

// -- TU additions (after addCoord3D):
inline void subCoord3D( Coord3D *diff, const Coord3D *a )
{
	diff->x -= a->x;
	diff->y -= a->y;
	diff->z -= a->z;
}

inline void scaleCoord3D( Coord3D *c, Real scale )
{
	c->x *= scale;
	c->y *= scale;
	c->z *= scale;
}

inline __declspec(noinline) float Coord3D::length() const
{
	return (float)sqrt(x * x + y * y + z * z);
}

inline __declspec(noinline) void Coord3D::normalize()
{
	float len = length();
	if (len != 0.0f) {
		float scale = 1.0f / len;
		x *= scale;
		y *= scale;
		z *= scale;
	}
}

// -- statics (after s_maxWaterLandSampleRatio):
// static Real s_portAngleOffset = PI / 2;
// double __cdecl Rva000422A0Atan2( float y, float x );

// -- body (append after reset):
Bool BuildAssistant::getPortTransform( const Coord3D *worldPos, const ThingTemplate *build,
					 Real angle, Real *outAngle, Coord3D *outPos )
{
	Region3D terrainExtent;
	TheTerrainLogic->getExtent( &terrainExtent );

	SampleBuildData sampleData;
	TheTerrainLogic->getExtent( &sampleData.mapRegion );
	sampleData.build = build;
	sampleData.requireWaterOrLand = FALSE;
	sampleData.waterSamples = 0.0f;
	sampleData.landSamples = 0.0f;
	sampleData.landSum.x = 0.0f;
	sampleData.landSum.y = 0.0f;
	sampleData.landSum.z = 0.0f;
	sampleData.waterSum.x = 0.0f;
	sampleData.waterSum.y = 0.0f;
	sampleData.waterSum.z = 0.0f;
	sampleData.hiZ = terrainExtent.lo.z;
	sampleData.loZ = terrainExtent.hi.z;
	sampleData.terrainRestricted = FALSE;
	sampleData.playerIndex = -1;
	iterateFootprint( build, angle, worldPos, MAP_XY_FACTOR, checkSampleBuildLocation, &sampleData );

	if( sampleData.terrainRestricted || !(sampleData.landSamples > 0.0f) || !(sampleData.waterSamples > 0.0f) )
		return FALSE;

	{Real inv=1.0f/sampleData.landSamples;
	sampleData.landSum.x=*(const volatile Real*)&sampleData.landSum.x*inv;
	sampleData.landSum.y=*(const volatile Real*)&sampleData.landSum.y*inv;
	sampleData.landSum.z=*(const volatile Real*)&sampleData.landSum.z*inv;
	}
	{Real inv=1.0f/sampleData.waterSamples;
	sampleData.waterSum.x=sampleData.waterSum.x*inv;
	sampleData.waterSum.y=*(const volatile Real*)&sampleData.waterSum.y*inv;
	sampleData.waterSum.z=*(const volatile Real*)&sampleData.waterSum.z*inv;
	}
	Coord3D dir;
	dir.x = sampleData.waterSum.x - sampleData.landSum.x;
	dir.y = sampleData.waterSum.y - sampleData.landSum.y;
	dir.z = sampleData.waterSum.z - sampleData.landSum.z;
	Real dist = dir.length();
	dir.normalize();
	scaleCoord3D( &dir, 5.0f );

	*outPos = sampleData.landSum;
	for( Real t = 0.0f; t < dist; t += 5.0f )
	{
		if( TheTerrainLogic->isUnderwater( outPos->x, outPos->y ) )
		{
			dir.normalize();
			scaleCoord3D( &dir, 10.0f );
			subCoord3D( outPos, &dir );
			outPos->z = TheTerrainLogic->getGroundHeight( outPos->x, outPos->y );
			break;
		}
		addCoord3D( outPos, &dir );
	}

	*outAngle = Rva000422A0Atan2( dir.y, dir.x );
	*outAngle += s_portAngleOffset;
	return TRUE;

}  // end getPortTransform
