// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0@@@Z
// partial score=0.233 date=2026-10-17
// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0@@@Z
// partial score=0.551 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0@@@Z
// partial score=0.54189 date=2026-10-13
// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0@@@Z
// partial score=0.54189 date=2026-10-10
// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0@@@Z
// partial score=0.54189 date=2026-10-09
// cl: /DNDEBUG /MD /EHsc /G6
class Gen_008F7CD0;
class Rva0073BAA0 {
public:
 virtual char testFunc(int,int);
 char rva0073BAA0(int,int,int);
private:
 Gen_008F7CD0 *grid;
 unsigned mask;
};
class RasterEdge {
public:
 int value,step,remaining;
 __forceinline RasterEdge(int from,int to,int n) {set(from,to,n);}
 __forceinline void set(int from,int to,int n) {
  remaining=n;
  if(n>0) {
   step=((to-from)<<8)/n;
   value=(from<<8)+step/2;
  }
 }
 __forceinline bool next() {
  value+=step;
  return --remaining!=0;
 }
 __forceinline int rounded() const {return (value+128)/256;}
};
__forceinline int prev(int i,int n) {return i?i-1:n-1;}
__forceinline int next(int i,int n) {return ++i==n?0:i;}
char __cdecl Rva0073BFE0Raster(int *ys,int *xs,int n,Rva0073BAA0 updater)
{
 int count=1;
 int *py=ys;
 int *px=xs;
 for(int i=1;i<n;++i) {
  if((1 ? (px[i]!=px[count-1] || py[i]!=py[count-1]) : (px[i]!=px[count-1] || py[i]!=py[count-1]))) {
   px[count]=px[i]; py[count]=py[i]; ++count;
  }
 }
 n=count;
 while(n>2 && xs[0]==xs[n-1] && ys[0]==ys[n-1]) --n;
 if(n<3) return 1;
 int first=0;
 for(int i=1;i<n;++i) {
  int yi=ys[i];
  if(yi<ys[first] || (yi==ys[first] && xs[i]<xs[first])) first=i;
 }
 int y=ys[first];
 int firstx=xs[first];
 { volatile int tmpS=0; (void)tmpS; }
 int left=prev(first,n);
 {
  RasterEdge leftEdge(firstx,xs[left],ys[left]-ys[first]);
  int right=next(first,n);
  while(ys[first]==ys[right]) first=right=next(first,n);
  (void)0;
  RasterEdge rightEdge(firstx,xs[right],ys[right]-ys[first]);
  Rva0073BAA0 upd=updater;
  if(!upd.rva0073BAA0(leftEdge.rounded(),rightEdge.rounded(),y)) return 0;
  for(;;) {
   ++y;
   if(!leftEdge.next()) {
    do {
     int other=prev(left,n);
     leftEdge.set(xs[left],xs[other],ys[other]-ys[left]);
     left=other;
     if(leftEdge.remaining<0) return 1;
    } while(leftEdge.remaining==0);
   }
   if(!rightEdge.next()) {
    do {
     int other=next(right,n);
     rightEdge.set(xs[right],xs[other],ys[other]-ys[right]);
     right=other;
     if(rightEdge.remaining<0) return 1;
    } while(rightEdge.remaining==0);
   }
   if(!updater.rva0073BAA0(leftEdge.rounded(),rightEdge.rounded(),y)) return 0;
  }
 }
 _ReadWriteBarrier();
}
