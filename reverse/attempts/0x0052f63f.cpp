// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.99964 date=2026-10-20
// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.8227 date=2026-10-20
// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.8035 date=2026-10-20
// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.7051406402 date=2026-10-19
// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.601 date=2026-10-17
// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.8014 date=2026-10-14
// ?rva0052F63F@Pathfinder@@QAEXPAVObject@@_N@Z
// partial score=0.6198830409 date=2026-10-13
// W7-SOL6 WB-first owner port:3017/3027B, frame10C/native114, callback52E6E6 missing.
// Corrected search/merge inside loop, scalar raster bounds, cached current layer per WB12DB220.
// Barrier in wallDelta restores native MOV/spill/FILD; indexed layer receiver restores second-loop recompute.
// Strict instruction similarity (only branch/global addresses normalized) .619883; stack displacement cascade dominates.
// Existing owner851B classification row verified; this complete bank includes its class view context.
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_BFME_RETAIL_TREE_INSERT_LAYOUT /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /I.
// stlport
#include <new>
#include <set>
#include <vector>
#include "ascii_string.h"
extern "C" void __cdecl free(void*);
// ?Rva0052F2EC@Pathfinder@@QAEXXZ retail 0x0052F2EC..0x0052F63F (851 bytes).
// BFME 2's Pathfinder::classifyMap twin (Zero Hour AIPathfind.cpp; Open-BFME-1
// PathfinderClassifyMap.cpp is BFME 1's shape): over the logical extent at
// +0x14..+0x20 of the column table at +0x10 (16-byte cells) it classifies
// every cell through the rowed static Pathfinder::classifyMapCell 0x0052E11A
// then pinches clear cells next to cliffs (bit 16) and turns pinched clear
// cells into cliffs through the rowed PathfindCell::SetType_Dirty 0x0052DA1C.
// It then calls the rowed 0x0052F294 on itself and grows a deep-water edge
// mask: type-7 cells with a non type-7 neighbour set bit 23 (rowed setter
// 0x0052E0CE) and six passes spread it through type 7/1 neighbours via bit
// 22 (rowed setter 0x0052E02F). Callgraph twin WB 0x012D86D0.

typedef int Int;

class Rva0052E02F
{
public:
	bool rva0052E02F(bool value);
};

class Rva0052E0CE
{
public:
	bool rva0052E0CE(bool value);
};

class Rva002E713FOwner
{
public:
	void rva0052F294();
	void rva0052ED74(void *,int);
};

class PathfindCell
{
public:
	enum CellType
	{
		CELL_CLEAR = 0,
		CELL_WATER = 1,
		CELL_CLIFF = 2,
		CELL_DEEP_WATER = 7
	};

	// Keep the native four-bit access inline without a competing getter copy.
	__declspec(dllimport) __forceinline CellType getType() const { return (CellType)type; }
	bool getPinched() const { return pinched; }
	Int getLayer() const { return layer; }
	void setPinched(bool pinch) { pinched = pinch; }
	bool getBit22() const { return m_bit22; }
	bool getBit23() const { return m_bit23; }
	bool SetType_Dirty(int type);
	void setBit22(bool on) { reinterpret_cast<Rva0052E02F *>(this)->rva0052E02F(on); }
	void setBit23(bool on) { reinterpret_cast<Rva0052E0CE *>(this)->rva0052E0CE(on); }

public:
	char m_head[0x0C];
	unsigned int type : 4;
	unsigned int layer : 6;
	unsigned int m_low : 6;
	unsigned int pinched : 1;
	unsigned int m_mid : 5;
	unsigned int m_bit22 : 1;
	unsigned int m_bit23 : 1;
	unsigned int m_high : 8;
};

#include "Code/Libraries/Include/Lib/ICoord2D.h"

struct IRegion2D
{
	ICoord2D lo;
	ICoord2D hi;
};

struct BfmeE8{int a,b;};
class Dict;
class Rva0027C36A{public:Rva0027C36A();char bytes[0xa8];};
class PolygonTrigger{public:virtual void *destroy(unsigned);void getBounds(IRegion2D*);};
class Bridge{public:Bridge(Rva0027C36A&,Dict*,const AsciiString&,PolygonTrigger*);virtual void *destroy(unsigned);Bridge*next;char bytes[0xcc-8];};
class Drawable{public:int rva002725E7(int);int rva002725B1(int);bool rva0027267D(int,int,int,int);bool rva002726C3(int,int,int,int);};
struct WallTemplate{char pad[0x64];AsciiString name;const AsciiString&getName()const{return name;}};
class Object{public:Drawable*getDrawable()const;const WallTemplate*getTemplate()const{return templ;}char pad0[4];WallTemplate*templ;char pad8[0x74-8];int id;int getID()const{return id;}char pad78[0x94-0x78];unsigned status;};
class Rva0036666B{public:bool rva0036666B();};
class Rva0036658B{public:bool rva0036658B(void*,void*);};
class PathfindLayer{public:bool DoBoundsOverlap(const IRegion2D*);void rva003667D4();void AddArea(void*);void allocateCells(const IRegion2D*);char pad[0x38];PolygonTrigger*areas;int height;int getHeight()const{return height;}};
class Rva00366500{public:bool rva00366500(int);bool rva0036652D(int);};
class Rva0052E001{public:bool rva0052E001(bool);};
class PathfindZoneManager{public:void MarkDirty(int,int);};

#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic*TheGameLogic;
class Debug{public:
 virtual void s00();virtual void s04();virtual void s08();virtual void s0C();virtual void s10();virtual void s14();virtual void s18();virtual void s1C();
 virtual Debug&operator<<(const char*);virtual Debug&operator<<(int);virtual Debug&operator<<(unsigned);virtual Debug&operator<<(long);virtual Debug&operator<<(unsigned long);virtual Debug&operator<<(bool);virtual Debug&operator<<(float);virtual void s3C();virtual void s40();virtual void s44();virtual void s48();virtual bool CrashDone(int);virtual void s50();virtual void s54();virtual void s58();virtual void s5C();virtual void SkipNext();virtual void s64();virtual void s68();virtual Debug&CrashBegin(const char*,int,int);
};
extern Debug*theDebug;
bool bfmeRva000387C0();void _bfme_debugRecordCallsite(int);
#include <math.h>
static __forceinline int float2long(float f){int i;__asm{
 fld f
 fistp i
}return i;}
#define FLOOR(x) float2long(floorf(x))
#define CEIL(x) float2long(ceilf(x))


class Pathfinder
{
public:
	static void classifyMapCell(Int cellX, Int cellY, PathfindCell *cell);
	void Rva0052F2EC();
	void rva0052F63F(Object *,bool);
	bool rva0052E6E6(int,int,PathfindCell *,PolygonTrigger *,int,bool);
	float &heightForLayer(int layer){return *((float*)((char*)this+0x1be78)+layer);}
	const AsciiString &nameForLayer(int layer){return names[layer-17];}

private:
	char m_head[0xC];
	int allocated;
	PathfindCell **m_map;
	IRegion2D m_extent;
	char pad24[0x5C-0x24];Bridge *bridges;PathfindLayer layers[16];PathfindZoneManager zones;
	char pad461[0x1be91-0x461];bool changedLayer;char pad1BE92[0x1beb4-0x1be92];bool changedWall;char pad1BEB5[3];int heightCount;float heights[64];AsciiString names[64];char pad1C0BC[0x1c1c0-0x1c0bc];_STL::set<int>wallIDs;
};

void Pathfinder::Rva0052F2EC()
{
	Int i, j;
	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			classifyMapCell(i, j, &m_map[i][j]);
		}
	}

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			if (m_map[i][j].getType() == PathfindCell::CELL_CLIFF)
			{
				for (Int k = i - 1; k < i + 2; k++)
				{
					if (k < m_extent.lo.x || k > m_extent.hi.x)
						continue;
					for (Int l = j - 1; l < j + 2; l++)
					{
						if (l < m_extent.lo.y || l > m_extent.hi.y)
							continue;
						if (m_map[k][l].getType() == PathfindCell::CELL_CLEAR)
						{
							m_map[k][l].setPinched(true);
						}
					}
				}
			}
		}
	}

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			if (m_map[i][j].getPinched() && m_map[i][j].getType() == PathfindCell::CELL_CLEAR)
			{
				m_map[i][j].SetType_Dirty(PathfindCell::CELL_CLIFF);
			}
		}
	}

	reinterpret_cast<Rva002E713FOwner *>(this)->rva0052F294();

	for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
	{
		for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
		{
			PathfindCell *cell = &m_map[i][j];
			if (cell->getType() == PathfindCell::CELL_DEEP_WATER)
			{
				if ((i > m_extent.lo.x && m_map[i - 1][j].getType() != PathfindCell::CELL_DEEP_WATER)
					|| (i < m_extent.hi.x && m_map[i + 1][j].getType() != PathfindCell::CELL_DEEP_WATER)
					|| (j > m_extent.lo.y && m_map[i][j - 1].getType() != PathfindCell::CELL_DEEP_WATER)
					|| (j < m_extent.hi.y && m_map[i][j + 1].getType() != PathfindCell::CELL_DEEP_WATER))
				{
					cell->setBit23(true);
				}
			}
		}
	}

	for (Int pass = 0; pass < 6; pass++)
	{
		for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
		{
			for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
			{
				if (m_map[i][j].getBit23())
				{
					if (i > m_extent.lo.x && (m_map[i - 1][j].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i - 1][j].getType() == PathfindCell::CELL_WATER))
						m_map[i - 1][j].setBit22(true);
					if (i < m_extent.hi.x && (m_map[i + 1][j].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i + 1][j].getType() == PathfindCell::CELL_WATER))
						m_map[i + 1][j].setBit22(true);
					if (j > m_extent.lo.y && (m_map[i][j - 1].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i][j - 1].getType() == PathfindCell::CELL_WATER))
						m_map[i][j - 1].setBit22(true);
					if (j < m_extent.hi.y && (m_map[i][j + 1].getType() == PathfindCell::CELL_DEEP_WATER || m_map[i][j + 1].getType() == PathfindCell::CELL_WATER))
						m_map[i][j + 1].setBit22(true);
				}
			}
		}

		for (j = m_extent.lo.y; j <= m_extent.hi.y; j++)
		{
			for (i = m_extent.lo.x; i <= m_extent.hi.x; i++)
			{
				Int type = m_map[i][j].getType();
				if (m_map[i][j].getBit22()
					&& (type == PathfindCell::CELL_DEEP_WATER || type == PathfindCell::CELL_WATER))
				{
					m_map[i][j].setBit22(false);
					m_map[i][j].setBit23(true);
				}
			}
		}
	}
}

extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
static __forceinline float wallDelta(PathfindLayer *entry,const float &height) { int value=entry->height; _ReadWriteBarrier(); return (float)value-height; }
static __forceinline void deletePoly(PolygonTrigger *p){operator delete(p?p->destroy(0):0);}
// Normalize pinch queries through the Boolean accessor used by the map classifier.
// Bounds arguments and wall diagnostic text follow the native call sites.
void Pathfinder::rva0052F63F(Object*obj,bool insert)
{
 const float tolerance=3.5f;
 Int i, j;
 Drawable*drawable=obj->getDrawable();if(!drawable)return;
 Rva0027C36A data;PolygonTrigger*poly;
 if(insert){
  float h;poly=(PolygonTrigger*)drawable->rva002725E7((int)&h);
  if(poly){
   bool merged = false;
   int layer=2;IRegion2D bounds;poly->getBounds(&bounds);
   for(;layer <= 15;layer++){
    PathfindLayer *entry = &layers[layer];
    if(((Rva0036666B*)entry)->rva0036666B() && entry->areas && entry->DoBoundsOverlap(&bounds) && fabs(entry->getHeight()-h)<tolerance){
     if(allocated)layers[layer].rva003667D4();
     layers[layer].AddArea(poly);
     if(allocated)layers[layer].allocateCells(&m_extent);
     poly=0;merged=true;break;
    }
   }
   if(!merged){
    for(layer=2;layer <= 15;++layer){
     const PathfindLayer *entry = &layers[layer];
     if(!((Rva0036666B*)entry)->rva0036666B()){
      if(((Rva0036658B*)&layers[layer])->rva0036658B(poly,(void*)layer)){
       if(allocated){layers[layer].allocateCells(&m_extent);changedLayer=true;}
       break;
      }
      break;
     }
    }
   }
  }
  if(drawable->rva0027267D((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);b->next=bridges;bridges=b;changedWall=true;
  }
  if(drawable->rva002726C3((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);b->next=bridges;bridges=b;changedWall=true;
  }
 }else{
  if(drawable->rva0027267D((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);((Rva002E713FOwner*)this)->rva0052ED74(b,0);operator delete(b?b->destroy(0):0);
  }
  if(drawable->rva002726C3((int)&data,(int)&poly,0,1)){
   Bridge*b=new Bridge(data,0,AsciiString::TheEmptyString,poly);((Rva002E713FOwner*)this)->rva0052ED74(b,0);operator delete(b?b->destroy(0):0);
  }
 }
 float height;PolygonTrigger*area=(PolygonTrigger*)drawable->rva002725B1((int)&height);if(!area)return;
 float closest=1000000.0f;int layer=1;
 for(int i=0;i<heightCount;++i){float distance=fabs(height-heights[i]);if(distance<closest){closest=distance;layer=i+17;}}
 if(closest > tolerance){
  static int count=0;
  if(closest < 9.9f&&count<10){
   ++count;
   if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);theDebug->SkipNext();
    (theDebug->CrashBegin(0,0,0)<<obj->getTemplate()->getName().str()<<" has a wall height of "<<height<<" but there's already a wall with a height\nof "<<heightForLayer(layer)<<" defined by "<<nameForLayer(layer).str()<<" - maximum delta for considering two walls to\nbe equal is "<<tolerance<<"; needs to be fixed /"<<layer).CrashDone(2);
   }
  }
  if(heightCount < 64){heights[heightCount]=height;names[heightCount]=obj->getTemplate()->getName();layer=heightCount+17;++heightCount;}
  else{
   static bool warned=false;
   if((!warned)){warned=true;if(bfmeRva000387C0()){
    _bfme_debugRecordCallsite(1);theDebug->SkipNext();(theDebug->CrashBegin(0,0,0)<<"Ran out of wall entries; too many walls with different heights on map").CrashDone(2);
   }}
  }
 }
 if(height>heightForLayer(layer)){heightForLayer(layer)=height;names[layer-17]=obj->getTemplate()->getName();}
 IRegion2D world;area->getBounds(&world);
 IRegion2D cellBounds;
 cellBounds.lo.x=FLOOR(world.lo.x/10)-2;
 cellBounds.lo.y=FLOOR(world.lo.y/10)-2;
 cellBounds.hi.x=CEIL(world.hi.x/10)+2;
 cellBounds.hi.y=CEIL(world.hi.y/10)+2;
 
 if(cellBounds.lo.x<m_extent.lo.x)cellBounds.lo.x=m_extent.lo.x;
 if(cellBounds.lo.y<m_extent.lo.y)cellBounds.lo.y=m_extent.lo.y;
 if(cellBounds.hi.x>m_extent.hi.x)cellBounds.hi.x=m_extent.hi.x;
 if(cellBounds.hi.y>m_extent.hi.y)cellBounds.hi.y=m_extent.hi.y;
 if(insert){
  wallIDs.insert(obj->getID());_STL::vector<BfmeE8>changed;
  for(j=cellBounds.lo.y;j <= cellBounds.hi.y;++j)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   if(rva0052E6E6(i,j,&m_map[i][j],area,layer,insert)){BfmeE8 p={i,j};changed.push_back(p);}
  }
  for(j=cellBounds.lo.y;j<=cellBounds.hi.y;++j)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   const int current=m_map[i][j].layer;
   if(current==layer)m_map[i][j].setPinched(false);
   if(m_map[i][j].getType()==0){
    int count=0;for(int k=i-1;k<i+2;k++){if(k<m_extent.lo.x||k>m_extent.hi.x)continue;
     for(int l=j-1;l<j+2;++l){if(l<m_extent.lo.y||l>m_extent.hi.y)continue;if(k==i&&j==l)continue;
      if(m_map[k][l].layer!=current)++count;
     }
    }
    if(count > 1)m_map[i][j].setPinched(true);
   }
  }
  for(_STL::vector<BfmeE8>::iterator p=changed.begin();p!=changed.end();p++){
   const int i=p->a,j=p->b;if(m_map[i][j].getPinched()&&m_map[i][j].getType()==0){m_map[i][j].SetType_Dirty(8);zones.MarkDirty(i,j);}m_map[i][j].setPinched(false);
  }
 }else{
  _STL::set<int>::iterator found=wallIDs.find(obj->getID());if(found!=wallIDs.end())wallIDs.erase(found);
  for(j=cellBounds.lo.y;j<=cellBounds.hi.y;j++)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   if(m_map[i][j].getPinched()){int current=m_map[i][j].layer;int count=0;
    for(int k=i-1;k<i+2;k++){if(k<m_extent.lo.x||k>m_extent.hi.x)continue;
     for(int l=j-1;l<j+2;l++){if(l<m_extent.lo.y||l>m_extent.hi.y)continue;if(k==i&&j==l)continue;if(m_map[k][l].layer!=current)++count;}
    }
    if(count > 1)m_map[i][j].setPinched(false);
   }
  }
  for(j=cellBounds.lo.y;j<=cellBounds.hi.y;j++)for(i=cellBounds.lo.x;i<=cellBounds.hi.x;++i){
   PathfindCell*c=&m_map[i][j];
   if(c->layer==layer){
    bool dirty=c->SetType_Dirty(0);dirty|=((Rva0052E001*)c)->rva0052E001(false);dirty|=((Rva00366500*)c)->rva00366500(true);dirty|=((Rva00366500*)c)->rva0036652D(false);
    _ReadWriteBarrier();
    if(dirty)zones.MarkDirty(i,j);c->setPinched(false);
   }
  }
  for(_STL::set<int>::iterator p=wallIDs.begin();p!=wallIDs.end();++p){
   Object*other=TheGameLogic->findObjectByID((ObjectID)*p);if((!other)||(other->status&1))continue;
   Drawable*d=other->getDrawable();if((!d))continue;float z;PolygonTrigger*q=(PolygonTrigger*)d->rva002725B1((int)&z);if(!q)continue;
   IRegion2D qb;q->getBounds(&qb);
   IRegion2D qc;
   qc.lo.x=FLOOR(qb.lo.x/10)-2;
   qc.lo.y=FLOOR(qb.lo.y/10)-2;
   qc.hi.x=CEIL(qb.hi.x/10)+2;
   qc.hi.y=CEIL(qb.hi.y/10)+2;
   if((qc.lo.x<=cellBounds.hi.x&&qc.hi.x>=cellBounds.lo.x&&qc.lo.y<=cellBounds.hi.y&&qc.hi.y>=cellBounds.lo.y)){rva0052F63F(other,true);deletePoly(q);}
  }
 }
 deletePoly(area);
}
