// ?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z
// partial score=0.88601 date=2026-10-16
// ?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z
// partial score=0.8847884124981439 date=2026-10-15
// ?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z
// partial score=0.8119096975121662 date=2026-10-15
// ?internal_findHierarchicalPath@Pathfinder@@IAEPAVPath@@_NHPAVObject@@PBUCoord3D@@200PAU4@@Z
// W7-D1 r11 native2F71A6..2F83A3 RET32; WB D4FAE0 semantic spine.
// Full4605B and frame110 EXACT; normalized243/raw441 remain (fitness.8847884).
// WB fixes: named int result between zone calls, cached parent layer,
// direct initial layer field accesses, k>>1, scan origins stored before offsets,
// shared scan counter, original in-loop success returns, lower-bound direction.
// Local SearchStorage and CandidateStorage are implementation storage adapters,
// NOT claims of original target classes. Candidate switches from waypoint to
// closest-cell only after its waypoint phase dies; every read follows a write.
// Query/point/block goal retain independently established member types/layouts.
// parentZone is unsigned short: retail stores/compares it as a word
// (2F781C/2F7841/2F7D73); zone helper returns ushort. Plain rawTo zero check.
// Separate min-distance and initial-cell defs. Residue (opus r12): entry keeps
// this in ecx (retail rawTo esi, from edi); waypoint loop not inverted and not
// cached in edi (retail edi + home slot 2C); no xor-edi zero reg after loop;
// stack slot permutation. Disproved r12: ICoord2D block, scalar way/closestCell,
// dropping entry barrier, named location pointer in waypoint loop.
// Existing sole datum owner g_Va00E01EDC replaces an unadmitted second name;
// data_ledger owner GameStateInit.cpp, role from GameEngineInit registration.
// Root audit:139 REL32 sites/42 names, all already admitted; no new pins.
// Source/datum identity checks and owner integration remain required to land.
// Context retains unrelated pre-existing assembly unchanged; none was added.
// Discard the 4540B/nd243 ctor-view experiment: it outlined non-retail ctor calls.
// cl: /I. /O1 /DNDEBUG /MD /arch:SSE /G7 /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "reverse/attempt_evidence/pathfinder_hierarchy/owner_context.inc"
Path *Pathfinder::internal_findHierarchicalPath(Bool isHuman,
 LocomotorSurfaceTypeMask surfaces,Object *obj,const Coord3D *from,
 const Coord3D *rawTo,Bool crusher,Bool closestOK,Coord3D *adjustedTo)
{
 union CandidateStorage {Waypoint *waypoint;PathfindCell *cell;};CandidateStorage candidate;
 if(rawTo->x==0.0f && rawTo->y==0.0f)return 0;
 if(!m_isMapReady)return 0;
 struct SearchStorage {HierarchyPoint point;HierarchySearchOptions query;ICoord2D blockGoal;__forceinline SearchStorage(const Coord3D&p):point(p){} };SearchStorage storage(*rawTo);HierarchyPoint &adjustTo=storage.point;
 _ReadWriteBarrier();
 Coord3D *to=&adjustTo;
 HierarchyPoint clipFrom(*from);
 rva002E75A3(&clipFrom,&adjustTo);
 m_isTunneling=false;
 Bool useMineshaft=false;
 HierarchyPoint originalTo(adjustTo);
 if(((MineshaftPortalNetworkManager *)g_Va00E01EDC)->hasUsableNetwork(obj->getControllingPlayer())) {
  float startDistance=0.0f,endDistance=0.0f;
  for(candidate.waypoint=((HierarchyTerrain *)TheTerrainLogic)->getFirstWaypoint();candidate.waypoint;candidate.waypoint=candidate.waypoint->next) {
   if(candidate.waypoint->type==8 && (unsigned char)((Rva002E6ECA *)candidate.waypoint)->get() && candidate.waypoint->isValidUnitType(obj)) {
    if(rva001E3647Pos(TheTerrainLogic->getLayerForDestination(0,&candidate.waypoint->location),&candidate.waypoint->location)) {
     HierarchyPoint delta;delta.x=candidate.waypoint->location.x;delta.y=candidate.waypoint->location.y;delta.z=candidate.waypoint->location.z;
     delta.x-=obj->position[0];delta.y-=obj->position[1];delta.z-=obj->position[2];
     float dist=delta.x*delta.x+delta.y*delta.y;
     if(!m_srcMineshaft || dist<startDistance) {m_srcMineshaft=(PathfinderMineshaft *)candidate.waypoint;startDistance=dist;}
     delta=candidate.waypoint->location;
     delta.x-=rawTo->x;delta.y-=rawTo->y;delta.z-=rawTo->z;
     dist=delta.x*delta.x+delta.y*delta.y;
     if(!m_destMineshaft || dist<endDistance) {m_destMineshaft=(PathfinderMineshaft *)candidate.waypoint;endDistance=dist;}
    }
   }
  }
  if(m_srcMineshaft && m_destMineshaft && m_srcMineshaft!=m_destMineshaft &&
     QuickDoesPathExist(obj,from,&m_srcMineshaft->m_position,0) &&
     QuickDoesPathExist(obj,&m_destMineshaft->m_position,rawTo,0)) {
   useMineshaft=true;adjustTo=m_srcMineshaft->m_position;rva002E75A3(&clipFrom,&adjustTo);
  } else {m_srcMineshaft=0;m_destMineshaft=0;}
 }
 PathfindLayerEnum destinationLayer=TheTerrainLogic->getLayerForDestination(0,to);
 ICoord2D cell;Rva002E7875WorldToCell(&cell,true,to);
 PathfindCell *goalCell=getCell(destinationLayer,cell.x,cell.y);
 if(!goalCell)return 0;
 goalCell->allocateInfo((In002E6BA1 *)&cell);
 PathfindLayerEnum layer=TheTerrainLogic->getLayerForDestination(0,from);
 PathfindCell *parentCell=rva002E8BF8(layer,&clipFrom);
 if(!parentCell)return 0;
 if(parentCell==goalCell) {goalCell->ReleaseInfo();return 0;}
 { ICoord2D startCellNdx;
 parentCell->allocateInfo((In002E6BA1 *)Rva002E7875WorldToCell(&startCellNdx,true,&clipFrom)); }
 if((parentCell->m_info & 15)==4 &&
    (parentCell->m_pathInfo?parentCell->m_pathInfo->obstacleID:(ObjectID)0)!=m_ignoreObstacleID) {
  goalCell->ReleaseInfo();parentCell->ReleaseInfo();return 0;
 }
 Int priority=obj->m_template->priority;
 Bool flag=obj->m_template->flag;
 Bool layerFlag=obj->rva0028AC62();
 Bool objectFlag=obj->rva0028AFBB();
 HierarchySearchOptions &options=storage.query;options.surfaces=surfaces;options.passFlag=!flag;options.objectFlag=objectFlag;options.priority=priority-1;options.layerFlag=layerFlag;
 Rva002E99F9Sub460 *zones=(Rva002E99F9Sub460 *)&m_zoneManager;
 Int zone1=zones->rva0053241F(&options,parentCell->quickZone());
 Int zone2=zones->rva0053241F(&options,goalCell->quickZone());
 if((goalCell->m_info & 15)==4){zone2=zones->rva00531FD4(&options,(unsigned short)zone2);zone2=zones->rva0053241F(&options,(unsigned short)zone2);}
 if(!closestOK && !rva002F4115(obj,zone1,zone2,0)) {goalCell->ReleaseInfo();parentCell->ReleaseInfo();return 0;}
 parentCell->StartPathfind((Int)goalCell);
 parentCell->m_pathInfo->totalCost=(unsigned short)rva002F0A72(parentCell,goalCell);
 Int cellCount=0;
 unsigned short goalBlockZone;
 ICoord2D &goalBlockNdx=storage.blockGoal;
 if((unsigned char)Rva002E6E6CGet(goalCell->getLayer())) {
  goalBlockZone=zones->rva00532041((Int)&options,goalCell->getXIndex(),goalCell->getYIndex(),(Rva00532041Record **)m_unknown10);
  goalBlockNdx.x=goalCell->getXIndex()/16;goalBlockNdx.y=goalCell->getYIndex()/16;
 } else {goalBlockZone=goalCell->quickZone();goalBlockNdx.x=-1;goalBlockNdx.y=-1;}
 AddToOpenList(parentCell);
 Int parentLayer=parentCell->getLayer();
 if(!(unsigned char)Rva002E6E6CGet(parentLayer)) {
  ICoord2D ndx=((HierarchyLayerView *)&m_layers[parentLayer])->start,toNdx=((HierarchyLayerView *)&m_layers[parentLayer])->end;
  PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
  PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
  if(end && start) {
   rva002F36E5();parentCell->PutOnClosedList(&m_closedList);
   start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);++cellCount;
   Int curCost=start->CalcCostToHierGoal(parentCell),remCost=start->CalcCostToHierGoal(goalCell);
   start->m_pathInfo->costSoFar=(unsigned short)curCost;start->m_pathInfo->totalCost=(unsigned short)remCost;
   hierarchySetParent(start,parentCell);AddToOpenList(start);
   ++cellCount;end->allocateInfo((In002E6BA1 *)&toNdx);
   curCost=end->CalcCostToHierGoal(parentCell);remCost=end->CalcCostToHierGoal(goalCell);
   end->m_pathInfo->costSoFar=(unsigned short)curCost;end->m_pathInfo->totalCost=(unsigned short)remCost;
   hierarchySetParent(end,parentCell);AddToOpenList(end);
  }
 }
 candidate.cell=0;
 float closestDistSqr=1.0e12f;
 PathfindCell *initialCell=parentCell;
 while((parentCell=rva002F36E5())!=0) {
  parentCell->PutOnClosedList(&m_closedList);
  unsigned short parentZone;
  if((unsigned char)Rva002E6E6CGet(parentCell->getLayer()))
   parentZone=zones->rva00532041((Int)&options,parentCell->getXIndex(),parentCell->getYIndex(),(Rva00532041Record **)m_unknown10);
  else parentZone=parentCell->quickZone();
  Bool reachedGoal=false;
  Int blockX=parentCell->getXIndex()/16,blockY=parentCell->getYIndex()/16;
  if(parentZone==goalBlockZone && (goalBlockNdx.x==-1 || (blockX==goalBlockNdx.x && blockY==goalBlockNdx.y)))reachedGoal=true;
  Disp32IntPair extent;((Rva005315B0IntPairField *)&m_zoneManager)->get(extent);
  if(!reachedGoal && m_zoneManager.rva00532069(parentCell->getXIndex(),parentCell->getYIndex())) {
   for(Int i=0;i<=15;++i) {
    HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[i];
    if(!((Rva0036666B *)bridge)->rva0036666B() || bridge->destroyed)continue;
    ICoord2D ndx=bridge->start,toNdx=bridge->end;
    if(ndx.x/16!=blockX || ndx.y/16!=blockY) {toNdx=bridge->start;ndx=bridge->end;}
    if(ndx.x<0 || ndx.y<0)continue;
    _ReadWriteBarrier();
    if(toNdx.x<0 || toNdx.y<0)continue;
    if(ndx.x/16==blockX && ndx.y/16==blockY) {
     Int bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
     if(bridgeZone!=parentZone) {
      if(ndx.x/16==toNdx.x/16 && ndx.y/16==toNdx.y/16) {
       ICoord2D temp=ndx;ndx=toNdx;toNdx=temp;
       bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
      }
      if(bridgeZone!=parentZone)continue;
     }
     if(bridge->zone==goalBlockZone) {reachedGoal=true;break;}
     PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
     if(!end || hierarchyClosed(end) || hierarchyOpen(end))continue;
     PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
     if(!start || start==end)continue;
     if(start!=parentCell) {
      start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);
      if(!hierarchyClosed(start) && !hierarchyOpen(start))start->PutOnClosedList(&m_closedList);
     }
     end->allocateInfo((In002E6BA1 *)&toNdx);hierarchySetParent(end,start);++cellCount;
     Int curCost=end->CalcCostToHierGoal(start),remCost=end->CalcCostToHierGoal(goalCell);
     end->m_pathInfo->costSoFar=(unsigned short)(start->m_pathInfo->costSoFar+curCost);
     end->m_pathInfo->totalCost=(unsigned short)(end->m_pathInfo->costSoFar+remCost);
     hierarchySetParent(end,start);AddToOpenList(end);
    }
   }
  }
  Bool wasMineshaft=useMineshaft;
  if(reachedGoal) {
   if(useMineshaft) {
    useMineshaft=false;reachedGoal=false;adjustTo=originalTo;
    PathfindLayerEnum dest=TheTerrainLogic->getLayerForDestination(0,to);
    ICoord2D ndx;Rva002E7875WorldToCell(&ndx,true,to);
    goalCell=getCell(dest,ndx.x,ndx.y);goalCell->allocateInfo((In002E6BA1 *)&ndx);
    zone2=zones->rva0053241F(&options,goalCell->quickZone());
    if((unsigned char)Rva002E6E6CGet(goalCell->getLayer())) {
     goalBlockZone=zones->rva00532041((Int)&options,goalCell->getXIndex(),goalCell->getYIndex(),(Rva00532041Record **)m_unknown10);
     goalBlockNdx.x=goalCell->getXIndex()/16;goalBlockNdx.y=goalCell->getYIndex()/16;
    } else {goalBlockZone=goalCell->quickZone();goalBlockNdx.x=-1;goalBlockNdx.y=-1;}
   }
   if(reachedGoal){
   if(parentCell!=goalCell)hierarchySetParent(goalCell,parentCell);
   m_isTunneling=false;
   Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)goalCell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
   rva002F40E7();goalCell->ReleaseInfo();goalCell->ReleaseInfo();*adjustedTo=adjustTo;return path;
  }
  }
  if(m_zoneManager.rva005315C8(parentCell->getXIndex(),parentCell->getYIndex())) {
   Int i=0;
   for(Waypoint *wp=(Waypoint *)m_zoneManager.GetPortal(parentCell->getXIndex(),parentCell->getYIndex(),i);
       wp;wp=(Waypoint *)m_zoneManager.GetPortal(parentCell->getXIndex(),parentCell->getYIndex(),++i)) {
    if(wp->type==8 && !wasMineshaft)continue;
    if(!wp->isValidUnitType(obj))continue;
    ICoord2D ndx;Rva002E7875WorldToCell(&ndx,true,&wp->location);
    for(Int j=0;j<wp->linkCount;++j) {
     Waypoint *link=wp->getLink(j);if(!link)continue;
     ICoord2D toNdx;Rva002E7875WorldToCell(&toNdx,true,&link->location);
     HierarchyLayerView *bridge=(HierarchyLayerView *)&m_layers[i];
     if(ndx.x/16!=blockX || ndx.y/16!=blockY) {toNdx=bridge->start;ndx=bridge->end;}
     if(ndx.x<0 || ndx.y<0)continue;
     if(toNdx.x<0 || toNdx.y<0)continue;
     _ReadWriteBarrier();
     if(ndx.x/16==blockX && ndx.y/16==blockY) {
      unsigned short bridgeZone=zones->rva00532041((Int)&options,ndx.x,ndx.y,(Rva00532041Record **)m_unknown10);
      if(bridgeZone!=parentZone)continue;
      if(bridge->zone==goalBlockZone) {reachedGoal=true;break;}
      PathfindCell *end=getCell(PATHFIND_LAYER_GROUND,toNdx.x,toNdx.y);
      if(!end || hierarchyClosed(end) || hierarchyOpen(end))continue;
      PathfindCell *start=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
      if(!start)continue;
      if(start!=parentCell) {
       start->allocateInfo((In002E6BA1 *)&ndx);hierarchySetParent(start,parentCell);
       if(!hierarchyClosed(start) && !hierarchyOpen(start))start->PutOnClosedList(&m_closedList);
      }
      end->allocateInfo((In002E6BA1 *)&toNdx);hierarchySetParent(end,start,wp);++cellCount;
      Int curCost=0;if(wp->type==8)curCost=500;else curCost=end->CalcCostToHierGoal(start);
      Int remCost=end->CalcCostToHierGoal(goalCell);
      end->m_pathInfo->costSoFar=(unsigned short)(start->m_pathInfo->costSoFar+curCost);
      end->m_pathInfo->totalCost=(unsigned short)(end->m_pathInfo->costSoFar+remCost);
      hierarchySetParent(end,start,wp);AddToOpenList(end);
     }
    }
   }
  }
  if(reachedGoal){
   if(parentCell!=goalCell)hierarchySetParent(goalCell,parentCell);
   m_isTunneling=false;
   Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)goalCell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
   rva002F40E7();goalCell->ReleaseInfo();goalCell->ReleaseInfo();*adjustedTo=adjustTo;return path;
  }
  float dx=(float)((Int (__cdecl *)(Int))ji_00629952)(goalCell->getXIndex()-parentCell->getXIndex());
  float dy=(float)((Int (__cdecl *)(Int))ji_00629952)(goalCell->getYIndex()-parentCell->getYIndex());
  float distance=dx*dx+dy*dy;
  if(distance<closestDistSqr) {candidate.cell=parentCell;closestDistSqr=distance;}
  Int k; unsigned short examinedZones[16];Int examinedCount=0;
  if(blockX>0) {
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.x=blockX*16;ndx.y=blockY*16;ndx.y+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.y+=offset;ICoord2D delta={ -1,0 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockX<extent.x-1) {
   examinedCount=0;
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.x=blockX*16+15;ndx.y=blockY*16;ndx.y+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.y+=offset;ICoord2D delta={ 1,0 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockY>0) {
   examinedCount=0;
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.y=blockY*16;ndx.x=blockX*16;ndx.x+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.x+=offset;ICoord2D delta={ 0,-1 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
  if(blockY<extent.y-1) {
   examinedCount=0;
   for(k=1;k<=16;++k) {
    ICoord2D ndx; ndx.y=blockY*16+15;ndx.x=blockX*16;ndx.x+=8;Int offset=k>>1;if(k&1)offset=-offset;ndx.x+=offset;ICoord2D delta={ 0,1 };
    PathfindCell *test=getCell(PATHFIND_LAYER_GROUND,ndx.x,ndx.y);
    if(test && !hierarchyClosed(test) && !hierarchyOpen(test) &&
       (!isHuman || (ndx.x>=m_extentLowX && ndx.x<=m_extentHighX && ndx.y>=m_extentLowY && ndx.y<=m_extentHighY)))
     rva002F5022(ndx,delta,parentCell,goalCell,parentZone,examinedZones,examinedCount,(Int)&options,cellCount);
   }
  }
 }
 if(closestOK && candidate.cell && candidate.cell!=initialCell) {
  m_isTunneling=false;
  _ReadWriteBarrier();
  Coord3D closest;
  *adjustedTo=*(Coord3D *)Rva002E8C4DCall((Int)&closest,1,(Rva002E8C23Pair *)candidate.cell->m_pathInfo,1);
  Path *path=(Path *)MakeHierarchicalPathPassable((void *)from,(Rva002E6C79 *)candidate.cell,((((const unsigned int *)obj->m_template->kinds)[5]>>31)&1)!=0);
  rva002F40E7();goalCell->ReleaseInfo();return path;
 }
 _STL::vector<Gen_p12pod> *hops=(_STL::vector<Gen_p12pod> *)&m_1C1CC;hops->erase(hops->begin(),hops->end());
 m_isTunneling=false;rva002F40E7();goalCell->ReleaseInfo();return 0;
}
