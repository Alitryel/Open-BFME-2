// ?getClosestPointOnLand@Pathfinder@@QAE_NPBUCoord3D@@PAVObject@@PAU2@@Z
// partial score=0.9795 date=2026-10-13
// ?getClosestPointOnLand@Pathfinder@@QAE_NPBUCoord3D@@PAVObject@@PAU2@@Z
// FRAGMENT for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
// at 102d4da (and the same home declarations at 63b30f092a).
// Add a forward declaration class Rva002E7E26; before Pathfinder, then public:
// Bool getClosestPointOnLand(const Coord3D*,Object*,Coord3D*);
// Int rva002EB4DF(const ICoord2DBase*,const ICoord2DBase*,float,Int,Rva002E7E26*);
// Int rva002E8773(Int*,Int*,Int,Int,Rva002E7E26*);
// Append this fragment using the home /O1 /G7 /arch:SSE /MD /EHsc settings.
// WB D644A0 and native 002EE7EE..002EE96B RET12; full381/frame5C.
// Natural visitor replaces placement-new storage and the barrier. Real visible
// ctor + callback + polygon + rectangle definitions prove stack escape facts;
// marking the ctor inline (while keeping it out of line) recovers the exact
// arithmetic schedule. Const-reference landCells operands/factors are required.
// Every helper emitted here also matches its existing owner in this context:
// 2E7DF5/49, 2E7E26/176, 2E6CFE/49, 2E6D2F/19, 2E8773/724, 2EB4DF/406.
// Do not add duplicate ledger claims or pins for these existing providers.
// Padding uses existing g_00DBD33C[10..11], no overlapping data definitions.
// Remaining: ours clears EH state before all3 MOVSD output stores. Native
// clears it after2 MOVSD, then LEA ECX for cleanup, then final MOVSD. Every
// other instruction matches, including all arithmetic and the late found load.
// Not exact: normal complete-home byte, relocation, EH and identity gates
// remain mandatory before any landing. No nonmatching Code edits retained.
struct _Rva002E7DF5Cell { int x, y, z; };
class Rva002E7DF5
{
public:
	Rva002E7DF5(int, const _Rva002E7DF5Cell &) throw();
	int owner;
	int sourceWords[3];
	Coord3D closest;
	float cost;
	bool found;
};

class Rva002E7E26 {public:int rva002E7E26(Object*,int,int);int owner;Coord3D source,closest;float cost;bool found;};
enum LandCellKind { LandClear=0, LandWater=1, LandSolid=7 };
struct LandWordView {
    int a,b,c;
    unsigned packed;
    __forceinline LandCellKind getKind() const {
        return (LandCellKind)(packed&15);
    }
};
struct LandLocalPoint : Coord3D {
    __forceinline void set(const float *p) { x=p[0]; y=p[1]; z=p[2]; }
    __forceinline void set(float a,float b,float c) { x=a; y=b; z=c; }
    __forceinline void sub(const float *p) { x-=p[0]; y-=p[1]; z-=p[2]; }
    __forceinline float squared() const { return x*x+y*y+z*z; }
};
inline int Rva002E7E26::rva002E7E26(Object *object,int x,int y)
{
    if (((LandWordView *)object)->getKind()==LandSolid) return 0;
    if (((LandWordView *)object)->getKind()==LandWater) return 0;
    if (((LandWordView *)object)->getKind()!=LandClear) return 0;
    LandLocalPoint point;
    point.set((float)(x*10),(float)(y*10),source.z);
    LandLocalPoint delta;
    delta.set(&source.x);
    delta.sub(&point.x);
    float distance=delta.squared();
    if (cost>distance) {
        closest=point;
        cost=distance;
        found=true;
    }
    return 0;
}
class Rva002E6CFE
{
public:
	int m_00;	// x in 24.8 fixed point
	int m_04;	// x step per row
	int m_08;	// rows left on this edge
	int m_0C;	// vertex index (used by the convex polygon walk)
	void rva002E6CFE(int a, int b, int c);
	bool rva002E6D2F();
};

// ?rva002E6CFE@Rva002E6CFE@@QAEXHHH@Z @0x002E6CFE 49B
void Rva002E6CFE::rva002E6CFE(int a, int b, int c)
{
	m_08 = c;
	if (c > 0) {
		m_04 = ((b - a) << 8) / c;
		m_00 = (m_04 / 2) + (a << 8);
	}
}

// ?rva002E6D2F@Rva002E6CFE@@QAE_NXZ @0x002E6D2F 19B
bool Rva002E6CFE::rva002E6D2F()
{
	m_00 += m_04;
	return --m_08 > 0;
}

#define nextIndex(i,n) ((i)+1==(n)?0:(i)+1)
#define prevIndex(i,n) ((i)!=0?(i)-1:(n)-1)
inline Int Pathfinder::rva002E8773( Int *xPts, Int *yPts, Int numEdges, Int layer, Rva002E7E26 *visitor )
{
	Int i;
	Int j = 1;
	for (i = 1; i < numEdges; i++) {
		if (xPts[i] != xPts[j - 1] || yPts[i] != yPts[j - 1]) {
			xPts[j] = xPts[i];
			yPts[j] = yPts[i];
			j++;
		}
	}
	numEdges = j;
	while (numEdges > 2 && xPts[0] == xPts[numEdges - 1] && yPts[0] == yPts[numEdges - 1]) {
		numEdges--;
	}
	if (numEdges < 3) {
		return -1;
	}

	Int topIdx = 0;
	Int maxY = 0;
	for (i = 1; i < numEdges; i++) {
		if (yPts[i] < yPts[topIdx] || (yPts[i] == yPts[topIdx] && xPts[i] < xPts[topIdx]))
			topIdx = i;
		if (yPts[i] > maxY)
			maxY = yPts[i];
	}

	Int y = yPts[topIdx];
	Rva002E6CFE left;
	left.m_0C = topIdx;
	left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)],
		yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C] );
	left.m_0C = prevIndex(left.m_0C, numEdges);

	while (yPts[topIdx] == yPts[nextIndex(topIdx, numEdges)])
		topIdx = nextIndex(topIdx, numEdges);
	Rva002E6CFE right;
	right.m_0C = topIdx;
	right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)],
		yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C] );
	right.m_0C = nextIndex(right.m_0C, numEdges);

	while (y <= maxY) {
		Int x = (left.m_00 + 0x80) / 256;
		Int xEnd = (right.m_00 + 0x80) / 256;
		while (x <= xEnd) {
			PathfindCell *cell = getCell( (PathfindLayerEnum)layer, x, y );
			x++;
			if (!cell)
				continue;
			Int ret = visitor->rva002E7E26( (Object *)cell, x - 1, y );
			if (ret)
				return ret;
		}
		y++;
		if (!left.rva002E6D2F()) {
			while (left.m_08 == 0) {
				Int dy = yPts[prevIndex(left.m_0C, numEdges)] - yPts[left.m_0C];
				if (dy < 0)
					break;
				left.rva002E6CFE( xPts[left.m_0C], xPts[prevIndex(left.m_0C, numEdges)], dy );
				left.m_0C = prevIndex(left.m_0C, numEdges);
			}
		}
		if (!right.rva002E6D2F()) {
			while (right.m_08 == 0) {
				Int dy = yPts[nextIndex(right.m_0C, numEdges)] - yPts[right.m_0C];
				if (dy < 0)
					break;
				right.rva002E6CFE( xPts[right.m_0C], xPts[nextIndex(right.m_0C, numEdges)], dy );
				right.m_0C = nextIndex(right.m_0C, numEdges);
				if (right.m_08 < 0)
					return 0;
			}
		}
	}
	return 0;
}
#undef nextIndex
#undef prevIndex
inline int Pathfinder::rva002EB4DF(const ICoord2DBase *center,const ICoord2DBase *diameter,float angle,int layer,Rva002E7E26 *visitor)
{
 if (diameter->x==1 && diameter->y==1) {
   PathfindCell *cell=getCell((PathfindLayerEnum)layer,center->x,center->y);
   return cell ? visitor->rva002E7E26((Object *)cell,center->x,center->y) : 0;
 }
 int x[4],y[4];
 if (angle!=0.0f) {
   float sine,cosine;
   __asm { fld angle
           fsincos
           fstp cosine
           fstp sine }
   float hx=diameter->x*0.5f,hy=diameter->y*0.5f;
   float cx=(float)center->x,cy=(float)center->y;
   x[0]=(int)(cx-hx*cosine+hy*sine);
   y[0]=(int)(cy-hy*cosine-hx*sine);
   x[1]=(int)(cx+hx*cosine+hy*sine);
   y[1]=(int)(cy-hy*cosine+hx*sine);
   x[2]=(int)(cx+hx*cosine-hy*sine);
   y[2]=(int)(cy+hy*cosine+hx*sine);
   x[3]=(int)(cx-hx*cosine-hy*sine);
   y[3]=(int)(cy+hy*cosine-hx*sine);
 } else {
   int hx=diameter->x/2,hy=diameter->y/2;
   x[0]=x[3]=center->x-hx;
   y[0]=y[1]=center->y-hy;
   x[1]=x[2]=center->x+diameter->x-hx-1;
   y[2]=y[3]=center->y+diameter->y-hy-1;
 }
 return rva002E8773(x,y,4,layer,visitor);
}

extern float g_Va00BBB8E0;
__declspec(noinline) inline Rva002E7DF5::Rva002E7DF5(int a,const _Rva002E7DF5Cell &cell) throw(){
float f=g_Va00BBB8E0;owner=a;sourceWords[0]=cell.x;sourceWords[1]=cell.y;sourceWords[2]=cell.z;cost=f;found=false;
}
static __forceinline int landCells(const float & radius,const float & padding){const float & scale=2.0f;const float & inv=0.1f;return (int)(((radius+padding)*scale)*inv);}
Bool Pathfinder::getClosestPointOnLand(const Coord3D *position, Object *object, Coord3D *out)
{
	if (((TerrainLogicWaterQuery *)TheTerrainLogic)->slot4C(position->x, position->y, 0, 0, 0)) {
		{
			GeometryShape shape;
			reinterpret_cast<const GeometryInfo *>((const char *)object + 0xa8)->rva006BD9C0(shape);
int minorCells=landCells(shape.minor,(*reinterpret_cast<const float *>(&g_00DBD33C[11])));
int majorCells=landCells(shape.major,(*reinterpret_cast<const float *>(&g_00DBD33C[10])));
			ICoord2DBase diameter = { majorCells, minorCells };
			Rva002E7DF5 visitor((int)this, *reinterpret_cast<const _Rva002E7DF5Cell *>(position));
			int y = realToIntFloor(position->y * 0.1f + 0.5f);
			int x = realToIntFloor(position->x * 0.1f + 0.5f);
			ICoord2DBase center = { x, y };
			rva002EB4DF(&center, &diameter, object->m_orientation, 1, reinterpret_cast<Rva002E7E26 *>(&visitor));
			*out = visitor.closest;
			return visitor.found;
		}
	}
	else {
		*out = *position;
		return true;
	}
}
