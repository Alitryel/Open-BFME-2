// ?getRenderRegion@AptShapeContainer@@QAEXAAVCoord2D@@0@Z
// partial score=0.985 date=2026-10-15
// ?getRenderRegion@AptShapeContainer@@QAEXAAVCoord2D@@0@Z
// partial score=0.9899567303446856 date=2026-10-14
// ?getRenderRegion@AptShapeContainer@@QAEXAAVCoord2D@@0@Z
// partial score=0.99 date=2026-10-13
// ?getRenderRegion@AptShapeContainer@@QAEXAAVCoord2D@@0@Z
// partial score=0.97 date=2026-10-10
// cl: /I. /O1 /G7 /arch:SSE /EHsc /MD
#include "Code/Libraries/Include/Lib/Coord2D.h"
struct AptTriangle 
{
 Coord2D point[3];
 
}
;
struct AptLine 
{
 Coord2D point[2];
 
}
;
class AptSolidShape 
{
 public: char unknown[8];
 AptTriangle *first, *last;
 
}
;
class AptLineShape 
{
 public: char unknown[12];
 AptLine *first, *last;
 
}
;
class AptShape 
{
 public:
 virtual void slot00();
 virtual int slot04();
 virtual void slot08();
 virtual AptSolidShape *slot0C();
 virtual AptLineShape *slot10();
 
}
;
struct AptRenderTransform 
{
 float a,b,c,d,tx,ty;
 
}
;
static void rva000A94F9(Coord2D &low,Coord2D &high,const Coord2D &point)

{
 if (point.x < low.x) low.x = point.x;
 else if (point.x > high.x) high.x = point.x;
 if (point.y < low.y) low.y = point.y;
 else if (point.y > high.y) high.y = point.y;
 
}
static inline void aptMatrixMul(Coord2D&out,const Coord2D&point,const AptRenderTransform&matrix){out.x=(point.y*matrix.c)+(point.x*matrix.a)+matrix.tx;out.y=(point.y*matrix.d)+(point.x*matrix.b)+matrix.ty;}
class AptShapeContainer 
{
 public:
 int unknown00;
 AptShape **first,**last;
 int unknown0C;
 AptRenderTransform matrix;
 void getRenderRegion(Coord2D &,Coord2D &);
 
}
;
void AptShapeContainer::getRenderRegion(Coord2D &low,Coord2D &high)

{
 low.x=99999.0f;
 low.y=99999.0f;
 high.x=-99999.0f;
 high.y=-99999.0f;
 Coord2D point;
 for(AptShape **it=first;it!=last;++it) 
 {
  AptShape *shape=*it;
  switch(shape->slot04()) 
  {
   case 0: case 1: 
   {
    AptSolidShape *solid=shape->slot0C();
    if(!solid) break;
    for(AptTriangle *triangle=solid->first;triangle!=solid->last;++triangle) 
    {
     const Coord2D *p=triangle->point;
     aptMatrixMul(point,p[0],matrix);
     rva000A94F9(low,high,point);
     aptMatrixMul(point,p[2],matrix);
     rva000A94F9(low,high,point);
     aptMatrixMul(point,p[1],matrix);
     rva000A94F9(low,high,point);
     
    }
    break;
    
   }
   case 2: 
   {
    AptLineShape *lineShape=shape->slot10();
    if(!lineShape) break;
    for(AptLine *line=lineShape->first;line!=lineShape->last;++line) 
    {
     const Coord2D *p=line->point;
     aptMatrixMul(point,p[1],matrix);
     rva000A94F9(low,high,point);
     aptMatrixMul(point,p[0],matrix);
     rva000A94F9(low,high,point);
     
    }
    break;
    
   }
   
  }
  
 }
 high.x-=low.x;
 high.y-=low.y;
 
}
