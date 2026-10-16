// ?FindClosestPath@Pathfinder@@QAEPAVPath@@PAVObject@@ABVLocomotorSet@@PBUCoord3D@@PAU5@_NM4@Z
// partial score=0.8559270516717326 date=2026-10-16
// Owner patch for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp; apply the unified diff below.
// WB D48830 confirms float conversion of sqrt before adding25; real Coord3D helper bodies
// are visible and their bytes match existing rows. Existing owner83/83 rows still exact.
// Target remains2315B vs2338 and frameC8 vsC0.
#if 0
diff --git a/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp b/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
index 78cf23697d..ded6191f16 100644
--- a/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
+++ b/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
@@ -220,6 +220,7 @@ public:
 	Bool rvaBit16() const { return (Bool)((m_info >> 16) & 1); }
  PathfindCell *getParentCell(){return (PathfindCell *)((Rva002E6C79 *)this)->rva002E6C79();}
  Waypoint *getParentWaypoint()const {return m_pathInfo?m_pathInfo->parentWaypoint:0;}
+ ObjectID getObstacleID() const { return m_pathInfo ? m_pathInfo->obstacleID : (ObjectID)0; }
 
 private:
 	PathfinderGroundInfo *m_pathInfo;
@@ -503,6 +504,7 @@ private:
 class PathfindZoneManager
 {
 public:
+	void rva005312BE();
 	void rva00531300();
 	void rva00531481();
 	void rva005314C6(Int x, Int y, unsigned char flag);
@@ -661,6 +663,7 @@ Bool rva002EEA8A(const ICoord2D*,Int,ICoord2D*,void*,Int);
 	Path *InternalFindPath(Object *,const LocomotorSet &,const Coord3D *,const Coord3D *,HierarchicalPath *,Bool *);
 	Int rva002F83F5(PathfindCell *,PathfindCell *,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
 	Path *GetMoveAwayFromPath(Object *,Object *,Path *,Object *,Path *);
+	Path *FindClosestPath(Object *,const LocomotorSet &,const Coord3D *,Coord3D *,Bool,float,Bool);
 	Int ExamineNeighboringCellsForSidewaysAttack(PathfindCell *,const ICoord2D *,Int,const LocomotorSet &,Bool,Bool,Int,ICoord2D *,Object *,Int);
 	Bool checkForMovement(Object *,TCheckMovementInfo &);
 	Bool rva002EDFF9(Object *,Coord3D *);
@@ -3512,6 +3515,231 @@ Path *Pathfinder::GetMoveAwayFromPath(Object *obj,Object *otherObj,Path *pathToA
  m_isTunneling=false;rva002F40E7();return 0;
 }
 
+extern float g_00DBD338;
+class Rva0053476A;
+class Rva002EAD62 { public: void rva002EAD62(); };
+class Rva002EAD39 { public: void rva002EAD39(Rva0053476A *); };
+// Owner of the hierarchical path the closest search consults.
+struct PathfinderAttackHandle
+{
+	Path *path;
+	__forceinline PathfinderAttackHandle(Path *p) : path(p) {}
+	__forceinline ~PathfinderAttackHandle() { ((Rva002EAD62 *)this)->rva002EAD62(); }
+};
+// WB D48830 supplies FindClosestPath identity and target-specific stages;
+// ZH findClosestPath supplies closest-cell and hierarchical search semantics.
+inline __declspec(noinline) float Coord3D::length()const{return(float)sqrt(x*x+y*y+z*z);}
+inline __declspec(noinline) float Coord3D::GetLength()const{float a=x,b=y,c=z;return(float)sqrt(a*a+b*b+c*c);}
+inline __declspec(noinline) float Coord3D::Normalize(){float len=GetLength();float scale=1.0f/len;x*=scale;y*=scale;z*=scale;return len;}
+Path *Pathfinder::FindClosestPath(Object *obj,const LocomotorSet &locos,const Coord3D *from,
+Coord3D *rawTo,Bool blocked,float multiplier,Bool moveAllies)
+{
+ m_srcMineshaft=0;
+ m_destMineshaft=0;
+ Bool human=true;
+ if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1)human=false;
+ if(!locos.getValidSurfaces() || !m_isMapReady)return 0;
+ m_isTunneling=false;
+ Bool throughUnits=false;
+ if(obj->getAI())throughUnits=*((const Bool *)obj->getAI()+0x3ba);
+ Int radius;
+ Bool center;
+ Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
+ Coord3D adjusted;
+ copyCoord3D(&adjusted,rawTo);
+ if(!QuickDoesPathExist(obj,from,&adjusted,false))
+ {
+  Coord3D delta;
+  delta.x=adjusted.x-from->x;
+  delta.y=adjusted.y-from->y;
+  delta.z=0;
+  Int steps=-1-(Int)(delta.length()*(-1.0f/30.0f));
+  if(steps>5)steps=5;
+  delta.Normalize();
+  delta.x*=30.0f;
+  delta.y*=30.0f;
+  delta.z*=30.0f;
+  for(Int i=0;i<steps;++i)
+  {
+   adjusted.x-=delta.x;
+   adjusted.y-=delta.y;
+   adjusted.z-=delta.z;
+   if(QuickDoesPathExist(obj,from,&adjusted,false))break;
+  }
+ }
+ Coord3D destination;
+ copyCoord3D(&destination,&adjusted);
+ if(!center)
+ {
+  destination.x+=5.0f;
+  destination.y+=5.0f;
+ }
+ Coord3D clippedFrom;
+ copyCoord3D(&clippedFrom,from);
+ rva002E75A3(&clippedFrom,&destination);
+ ICoord2D startIndex;
+ Rva002E7875WorldToCell(&startIndex,true,from);
+ PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),&clippedFrom);
+ if(!parent)return 0;
+ Int priority=obj->m_template->priority;
+ Bool flag=obj->m_template->flag;
+ Rva002E8BCF movement((const Rva002E8BCFSrc *)&locos,!flag,priority-1,obj->rva0028AFBB());
+ if(!((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent))m_isTunneling=true;
+ {
+  TCheckMovementInfo info;
+  ((Rva002E6FDF *)&info)->rva002E6FDF();
+  info.cell=startIndex;
+  info.layer=(PathfindLayerEnum)obj->rva0028B511();
+  info.centerInCell=center;
+  info.radius=radius;
+  info.m_11=blocked;
+  info.m_14=obj->m_template->testKindWord(90)?1:16;
+  readMoverInfo(info,obj);
+  if(!checkForMovement(obj,info))m_isTunneling=true;
+ }
+ Bool gotHierarchical=false;
+ ((_STL::vector<Gen_p12pod> *)&m_1C1CC)->clear();
+ PathfinderAttackHandle hierarchical(0);
+ if(m_isTunneling)m_zoneManager.rva00531300();
+ else
+ {
+  m_zoneManager.rva005312BE();
+  Path *path=FindClosestHierarchicalPath(human,locos,obj,from,&adjusted,false,&destination);
+  ((Rva002EAD39 *)&hierarchical)->rva002EAD39((Rva0053476A *)path);
+  if(hierarchical.path)gotHierarchical=true;
+  else m_zoneManager.rva00531300();
+ }
+ PathfindCell *goal=rva002E8BF8(TheTerrainLogic->getLayerForDestination(0,&destination),&destination);
+ if(!goal)return 0;
+ Bool goalOnObstacle=false;
+ if(m_ignoreObstacleID)
+ {
+  Object *goalObj=TheGameLogic->findObjectByID(m_ignoreObstacleID);
+  if(goalObj)
+  {
+   PathfindCell *ignoreCell=rva002E8BF8((PathfindLayerEnum)goalObj->rva0028B511(),(const Coord3D *)goalObj->position);
+   if(goal->getObstacleID()==ignoreCell->getObstacleID() && goal->getObstacleID())
+   {
+    Object *newObstacle=TheGameLogic->findObjectByID(goal->getObstacleID());
+    if(newObstacle && newObstacle->m_template->hasKind(35))
+    {
+     m_ignoreObstacleID=goal->getObstacleID();
+     goalOnObstacle=true;
+    }
+    else
+    {
+     if(m_ignoreObstacleID==goal->getObstacleID())goalOnObstacle=true;
+    }
+   }
+  }
+ }
+ ICoord2D index;
+ goal->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&index,true,&destination));
+ if(parent!=goal)
+ {
+  parent->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&index,true,&clippedFrom));
+ }
+ parent->StartPathfind((Int)goal);
+ parent->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parent,goal);
+ PathfindCell *closest=0;
+ float closestMetric=8.5070587e37f;
+ Int closestOrder=0;
+ float bestDistance=8.5070587e37f,bestScreenDistance=8.5070587e37f;
+ PathfinderSearchCellsVisited=0;
+ AddToOpenList(parent);
+ Int count=0;
+ Bool foundGoal=false;
+ while((parent=rva002F36E5())!=0)
+ {
+  if(parent==goal)
+  {
+   if(goalOnObstacle || !closest || throughUnits || bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center)))
+   {
+    m_isTunneling=false;
+    Path *path=BuildActualPath(obj,locos.getValidSurfaces(),from,goal,center,blocked,true);
+    rva002F40E7();
+    parent->ReleaseInfo();
+    return path;
+   }
+   foundGoal=true;
+   parent->PutOnClosedList(&m_closedList);
+   continue;
+  }
+  parent->PutOnClosedList(&m_closedList);
+  if(!m_isTunneling && bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center)) &&
+  (!throughUnits || ((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent)))
+  {
+   float dx=(float)abs(goal->getXIndex()-parent->getXIndex());
+   float dy=(float)abs(goal->getYIndex()-parent->getYIndex());
+   float distance=dy*dy+dx*dx;
+   if(distance<bestDistance)
+   {
+    if(dx+dy>25.0f)
+    {
+     float metric=(float)sqrt((double)distance); metric+=25.0f;
+     bestScreenDistance=(float)(metric*metric);
+    }
+    else bestScreenDistance=distance*4.0f;
+    bestDistance=distance;
+   }
+   unsigned short cost=parent->m_pathInfo->costSoFar;
+   distance=(cost*(cost*g_00DBD338))*multiplier+distance+(unsigned int)(((_STL::vector<Gen_p12pod> *)&m_1C1CC)->size()*10000U);
+   float metric=distance;
+   if(hierarchical.path)
+   {
+    Int order=((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
+    if(order>closestOrder || (order==closestOrder && metric<closestMetric))
+    {
+     if(rva002EDFF9(obj,cellPointArg(Rva002E8C23Call(center,parent))))
+     {
+      closest=parent;
+      closestOrder=order;
+      closestMetric=metric;
+     }
+    }
+   }
+   else if(metric<closestMetric)
+   {
+    if(rva002EDFF9(obj,cellPointArg(Rva002E8C23Call(center,parent))))
+    {
+     closest=parent;
+     closestMetric=metric;
+    }
+   }
+  }
+  float dx=(float)abs(goal->getXIndex()-parent->getXIndex());
+  float dy=(float)abs(goal->getYIndex()-parent->getYIndex());
+  float distance=dy*dy+dx*dx;
+  Bool stop=false;
+  if(distance>bestScreenDistance){
+   if(!gotHierarchical)stop=true;
+   if(count>2000)stop=true;
+  }
+  if(distance<100.0f)stop=false;
+  if(!stop && !foundGoal)
+  {
+   CheckChangeLayers(parent,obj);
+   count+=rva002F83F5(parent,goal,locos,human,center,radius,&startIndex,obj,0);
+  }
+ }
+ Path *path;
+ if(closest)
+ {
+  m_isTunneling=false;
+  adjusted.x=closest->getXIndex()*10+5.0f;
+  adjusted.y=closest->getYIndex()*10+5.0f;
+  path=BuildActualPath(obj,locos.getValidSurfaces(),from,closest,center,blocked,true);
+ }
+ else
+ {
+  m_isTunneling=false;
+  path=0;
+ }
+ rva002F40E7();
+ goal->ReleaseInfo();
+ return path;
+}
+
 Path *Pathfinder::InternalFindPath(Object *obj, const LocomotorSet &locomotorSet, const Coord3D *from,
 	const Coord3D *rawTo, HierarchicalPath *hierarchicalPath, Bool *destinationAdjusted)
 {

// Recovered function and visible helpers (owner declarations are required):
inline __declspec(noinline) float Coord3D::length()const{return(float)sqrt(x*x+y*y+z*z);}
inline __declspec(noinline) float Coord3D::GetLength()const{float a=x,b=y,c=z;return(float)sqrt(a*a+b*b+c*c);}
inline __declspec(noinline) float Coord3D::Normalize(){float len=GetLength();float scale=1.0f/len;x*=scale;y*=scale;z*=scale;return len;}
Path *Pathfinder::FindClosestPath(Object *obj,const LocomotorSet &locos,const Coord3D *from,
Coord3D *rawTo,Bool blocked,float multiplier,Bool moveAllies)
{
 m_srcMineshaft=0;
 m_destMineshaft=0;
 Bool human=true;
 if(obj->getControllingPlayer() && obj->getControllingPlayer()->m_playerType==1)human=false;
 if(!locos.getValidSurfaces() || !m_isMapReady)return 0;
 m_isTunneling=false;
 Bool throughUnits=false;
 if(obj->getAI())throughUnits=*((const Bool *)obj->getAI()+0x3ba);
 Int radius;
 Bool center;
 Rva002EBCA7Split(obj,&radius,(unsigned char *)&center);
 Coord3D adjusted;
 copyCoord3D(&adjusted,rawTo);
 if(!QuickDoesPathExist(obj,from,&adjusted,false))
 {
  Coord3D delta;
  delta.x=adjusted.x-from->x;
  delta.y=adjusted.y-from->y;
  delta.z=0;
  Int steps=-1-(Int)(delta.length()*(-1.0f/30.0f));
  if(steps>5)steps=5;
  delta.Normalize();
  delta.x*=30.0f;
  delta.y*=30.0f;
  delta.z*=30.0f;
  for(Int i=0;i<steps;++i)
  {
   adjusted.x-=delta.x;
   adjusted.y-=delta.y;
   adjusted.z-=delta.z;
   if(QuickDoesPathExist(obj,from,&adjusted,false))break;
  }
 }
 Coord3D destination;
 copyCoord3D(&destination,&adjusted);
 if(!center)
 {
  destination.x+=5.0f;
  destination.y+=5.0f;
 }
 Coord3D clippedFrom;
 copyCoord3D(&clippedFrom,from);
 rva002E75A3(&clippedFrom,&destination);
 ICoord2D startIndex;
 Rva002E7875WorldToCell(&startIndex,true,from);
 PathfindCell *parent=rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(),&clippedFrom);
 if(!parent)return 0;
 Int priority=obj->m_template->priority;
 Bool flag=obj->m_template->flag;
 Rva002E8BCF movement((const Rva002E8BCFSrc *)&locos,!flag,priority-1,obj->rva0028AFBB());
 if(!((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent))m_isTunneling=true;
 {
  TCheckMovementInfo info;
  ((Rva002E6FDF *)&info)->rva002E6FDF();
  info.cell=startIndex;
  info.layer=(PathfindLayerEnum)obj->rva0028B511();
  info.centerInCell=center;
  info.radius=radius;
  info.m_11=blocked;
  info.m_14=obj->m_template->testKindWord(90)?1:16;
  readMoverInfo(info,obj);
  if(!checkForMovement(obj,info))m_isTunneling=true;
 }
 Bool gotHierarchical=false;
 ((_STL::vector<Gen_p12pod> *)&m_1C1CC)->clear();
 PathfinderAttackHandle hierarchical(0);
 if(m_isTunneling)m_zoneManager.rva00531300();
 else
 {
  m_zoneManager.rva005312BE();
  Path *path=FindClosestHierarchicalPath(human,locos,obj,from,&adjusted,false,&destination);
  ((Rva002EAD39 *)&hierarchical)->rva002EAD39((Rva0053476A *)path);
  if(hierarchical.path)gotHierarchical=true;
  else m_zoneManager.rva00531300();
 }
 PathfindCell *goal=rva002E8BF8(TheTerrainLogic->getLayerForDestination(0,&destination),&destination);
 if(!goal)return 0;
 Bool goalOnObstacle=false;
 if(m_ignoreObstacleID)
 {
  Object *goalObj=TheGameLogic->findObjectByID(m_ignoreObstacleID);
  if(goalObj)
  {
   PathfindCell *ignoreCell=rva002E8BF8((PathfindLayerEnum)goalObj->rva0028B511(),(const Coord3D *)goalObj->position);
   if(goal->getObstacleID()==ignoreCell->getObstacleID() && goal->getObstacleID())
   {
    Object *newObstacle=TheGameLogic->findObjectByID(goal->getObstacleID());
    if(newObstacle && newObstacle->m_template->hasKind(35))
    {
     m_ignoreObstacleID=goal->getObstacleID();
     goalOnObstacle=true;
    }
    else
    {
     if(m_ignoreObstacleID==goal->getObstacleID())goalOnObstacle=true;
    }
   }
  }
 }
 ICoord2D index;
 goal->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&index,true,&destination));
 if(parent!=goal)
 {
  parent->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&index,true,&clippedFrom));
 }
 parent->StartPathfind((Int)goal);
 parent->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parent,goal);
 PathfindCell *closest=0;
 float closestMetric=8.5070587e37f;
 Int closestOrder=0;
 float bestDistance=8.5070587e37f,bestScreenDistance=8.5070587e37f;
 PathfinderSearchCellsVisited=0;
 AddToOpenList(parent);
 Int count=0;
 Bool foundGoal=false;
 while((parent=rva002F36E5())!=0)
 {
  if(parent==goal)
  {
   if(goalOnObstacle || !closest || throughUnits || bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center)))
   {
    m_isTunneling=false;
    Path *path=BuildActualPath(obj,locos.getValidSurfaces(),from,goal,center,blocked,true);
    rva002F40E7();
    parent->ReleaseInfo();
    return path;
   }
   foundGoal=true;
   parent->PutOnClosedList(&m_closedList);
   continue;
  }
  parent->PutOnClosedList(&m_closedList);
  if(!m_isTunneling && bfmeWrapE6E90(obj,(void *)parent->getXIndex(),(void *)parent->getYIndex(),(void *)parent->getLayer(),(void *)radius,boolArg(center)) &&
  (!throughUnits || ((Rva002E6DC4 *)this)->rva002E6DC4(&movement,parent)))
  {
   float dx=(float)abs(goal->getXIndex()-parent->getXIndex());
   float dy=(float)abs(goal->getYIndex()-parent->getYIndex());
   float distance=dy*dy+dx*dx;
   if(distance<bestDistance)
   {
    if(dx+dy>25.0f)
    {
     float metric=(float)sqrt((double)distance); metric+=25.0f;
     bestScreenDistance=(float)(metric*metric);
    }
    else bestScreenDistance=distance*4.0f;
    bestDistance=distance;
   }
   unsigned short cost=parent->m_pathInfo->costSoFar;
   distance=(cost*(cost*g_00DBD338))*multiplier+distance+(unsigned int)(((_STL::vector<Gen_p12pod> *)&m_1C1CC)->size()*10000U);
   float metric=distance;
   if(hierarchical.path)
   {
    Int order=((HierarchicalPath *)hierarchical.path)->lookUpPositionOnPath((const Coord3D *)parent->m_pathInfo);
    if(order>closestOrder || (order==closestOrder && metric<closestMetric))
    {
     if(rva002EDFF9(obj,cellPointArg(Rva002E8C23Call(center,parent))))
     {
      closest=parent;
      closestOrder=order;
      closestMetric=metric;
     }
    }
   }
   else if(metric<closestMetric)
   {
    if(rva002EDFF9(obj,cellPointArg(Rva002E8C23Call(center,parent))))
    {
     closest=parent;
     closestMetric=metric;
    }
   }
  }
  float dx=(float)abs(goal->getXIndex()-parent->getXIndex());
  float dy=(float)abs(goal->getYIndex()-parent->getYIndex());
  float distance=dy*dy+dx*dx;
  Bool stop=false;
  if(distance>bestScreenDistance){
   if(!gotHierarchical)stop=true;
   if(count>2000)stop=true;
  }
  if(distance<100.0f)stop=false;
  if(!stop && !foundGoal)
  {
   CheckChangeLayers(parent,obj);
   count+=rva002F83F5(parent,goal,locos,human,center,radius,&startIndex,obj,0);
  }
 }
 Path *path;
 if(closest)
 {
  m_isTunneling=false;
  adjusted.x=closest->getXIndex()*10+5.0f;
  adjusted.y=closest->getYIndex()*10+5.0f;
  path=BuildActualPath(obj,locos.getValidSurfaces(),from,closest,center,blocked,true);
 }
 else
 {
  m_isTunneling=false;
  path=0;
 }
 rva002F40E7();
 goal->ReleaseInfo();
 return path;
}


#endif
