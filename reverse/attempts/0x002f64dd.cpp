// ?FindCollisionFreeQuickPath@Pathfinder@@UAEPAVPath@@PAVObject@@PBUCoord3D@@PAVPathNode@@@Z
// partial score=0.6684385564 date=2026-10-16
// Owner patch for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp; apply diff before compiling.
// Existing83 owner rows verified, including vptr/field layout preservation.
#if 0
--- a/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
+++ b/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
@@ -620,6 +620,17 @@
 class Pathfinder
 {
 public:
+virtual void QuickPathReserved0()=0;
+virtual void QuickPathReserved1()=0;
+virtual void QuickPathReserved2()=0;
+virtual void QuickPathReserved3()=0;
+virtual void QuickPathReserved4()=0;
+virtual void QuickPathReserved5()=0;
+virtual void QuickPathReserved6()=0;
+virtual void QuickPathReserved7()=0;
+virtual void QuickPathReserved8()=0;
+virtual void QuickPathReserved9()=0;
+virtual Path *FindCollisionFreeQuickPath(Object *,const Coord3D *,PathNode *);
  Bool AdjustToNearestValidCell(Coord3D *);
  Bool AdjustToNearestGroundCell(Coord3D *);
 bool rva002ED313(Object*);
@@ -718,7 +729,7 @@
 		Coord3D *adjustedTo);
 private:
 	Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002E7261Info *);
-	char m_pad000[8];Bool m_isMapReady;char m_pad009[7];
+	char m_pad004[4];Bool m_isMapReady;char m_pad009[7];
 	int m_unknown10;
 	ICoord2D m_clampLo, m_clampHi;	// +0x14 cell extent the 0x002E7917 clamp uses
     Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
@@ -4837,3 +4848,133 @@
 	*dest = adjustCellCenter(center, (Rva002E8C23Pair *)&info.targetCell, (PathfindLayerEnum)target->rva0028B511());
 	return false;
 }
+
+Path *Pathfinder::FindCollisionFreeQuickPath(Object *obj, const Coord3D *to, PathNode *nodes)
+{
+	m_ignoreObstacleID = (ObjectID)0;
+	Int radius;
+	Bool center;
+	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
+	const Coord3D *pos = obj->getPosition();
+	Coord3D from;
+	from.x = pos->x;
+	from.y = pos->y;
+	from.z = pos->z;
+	ICoord2D startCell;
+	Rva002E7875WorldToCell(&startCell, center, &from);
+	ICoord2D goalCell;
+	Rva002E7875WorldToCell(&goalCell, center, to);
+	if (startCell == *(const ICoord2DBase *)&goalCell)
+		return 0;
+	Int priority = obj->m_template->priority;
+	Bool flag = obj->m_template->flag;
+	Rva002E8BCF info((const Rva002E8BCFSrc *)(obj->m_258+0x1cc), !flag, priority - 1, obj->rva0028AFBB());
+	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
+	PathfindCell *goals[20];
+	goals[0] = getCell(goalLayer, goalCell.x, goalCell.y);
+	Int numGoals = 1;
+	if (!goals[0] || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, goals[0]))
+		return 0;
+	PathfindCell *parent = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &from);
+	if (!parent)
+		return 0;
+	goals[0]->allocateInfo((In002E6BA1 *)&goalCell);
+	parent->allocateInfo((In002E6BA1 *)&startCell);
+	parent->StartPathfind((Int)goals[0]);
+	parent->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parent, goals[0]);
+	AddToOpenList(parent);
+	Int cellCount = 0;
+	while (nodes && numGoals < 20)
+	{
+		nodes = nodes->next;
+		if (nodes)
+		{
+			goals[numGoals] = (PathfindCell *)rva001E3647Pos(nodes->layer, &nodes->position);
+			if (goals[numGoals])
+				++numGoals;
+		}
+	}
+	Path *path;
+	while ((parent = rva002F36E5()) != 0)
+	{
+		for (Int g = 0; g < numGoals; ++g)
+		{
+			if (parent == goals[g])
+			{
+				path = new Path;
+				PrependCells(path, pos, parent, center);
+				path->wordC = 1;
+				goto done;
+			}
+		}
+		parent->PutOnClosedList(&m_closedList);
+		if (cellCount > 3000)
+			break;
+		CheckChangeLayers(parent, obj);
+		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
+		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
+		const Int adjacent[5] = {0, 1, 2, 3, 0};
+		Bool neighborFlags[8];
+		for (Int i = 0; i < 8; ++i)
+		{
+			neighborFlags[i] = false;
+			ICoord2D coords={parent->getXIndex()+deltaX[i],parent->getYIndex()+deltaY[i]};ICoord2D next=coords;
+			PathfindCell *neighbor = getCell((PathfindLayerEnum)parent->getLayer(), next.x, next.y);
+			if (!neighbor)
+				continue;
+			if ((unsigned char)((Rva002E6B06 *)neighbor)->rva002E6B06())
+				continue;
+			if ((unsigned char)((Rva002E6AF3 *)neighbor)->get())
+				continue;
+			Int neighborLayer = (neighbor->m_info >> 4) & 0x3f;
+			Int parentLayer = (parent->m_info >> 4) & 0x3f;
+			if (neighborLayer != parentLayer)
+			{
+				Int parentConnect = (parent->m_info >> 10) & 0x3f;
+				if (neighborLayer != parentConnect)
+				{
+					Int neighborConnect = (neighbor->m_info >> 10) & 0x3f;
+					if (neighborConnect != parentLayer && (parentConnect != 0x10 || neighborConnect != 0x10))
+						continue;
+				}
+			}
+			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
+				continue;
+			Int extra = CalcCollisionFreeExtraCosts(obj, parent, (Rva002EBC7FPair *)&next, (PathfindLayerEnum)neighborLayer, radius, radius + (center ? 1 : 0), true);
+			if (extra < 0 || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, neighbor))
+			{
+				neighbor->allocateInfo((In002E6BA1 *)&next);
+				neighbor->PutOnClosedList(&m_closedList);
+				continue;
+			}
+			neighborFlags[i] = true;
+			if (!neighbor->m_pathInfo)
+			{
+				++cellCount;
+				if (!TheMixFileInfoPool)
+					Rva0052DBCDInit();
+				neighbor->m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)neighbor, (In002E6BA1 *)&next);
+			}
+			else
+				neighbor->m_pathInfo->parentWaypoint = 0;
+			Int cost = neighbor->CalcCostSoFar((const Rva002E6C79 *)parent);
+			Int dx = abs(next.x - goals[0]->m_pathInfo->position.x);
+			Int dy = abs(next.y - goals[0]->m_pathInfo->position.y);
+			if ((neighbor->m_info & 0x10000) && dx + dy > 3)
+				cost += 10;
+			neighbor->m_pathInfo->flags &= ~1U;
+			Int remaining = rva002F0A72(neighbor, goals[0]);
+			if ((neighbor->m_info & 0xf) == 4)
+				cost += 1000;
+			neighbor->m_pathInfo->costSoFar = (unsigned short)(extra + cost);
+			neighbor->SetParentCell((Int *)parent);
+			neighbor->m_pathInfo->totalCost = (unsigned short)(neighbor->m_pathInfo->costSoFar + remaining);
+			AddToOpenList(neighbor);
+		}
+	}
+	path = 0;
+done:
+	rva002F40E7();
+	goals[0]->ReleaseInfo();
+	return path;
+}
#endif
Path *Pathfinder::FindCollisionFreeQuickPath(Object *obj, const Coord3D *to, PathNode *nodes)
{
	m_ignoreObstacleID = (ObjectID)0;
	Int radius;
	Bool center;
	Rva002EBCA7Split(obj, &radius, (unsigned char *)&center);
	const Coord3D *pos = obj->getPosition();
	Coord3D from;
	from.x = pos->x;
	from.y = pos->y;
	from.z = pos->z;
	ICoord2D startCell;
	Rva002E7875WorldToCell(&startCell, center, &from);
	ICoord2D goalCell;
	Rva002E7875WorldToCell(&goalCell, center, to);
	if (startCell == *(const ICoord2DBase *)&goalCell)
		return 0;
	Int priority = obj->m_template->priority;
	Bool flag = obj->m_template->flag;
	Rva002E8BCF info((const Rva002E8BCFSrc *)(obj->m_258+0x1cc), !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
	PathfindCell *goals[20];
	goals[0] = getCell(goalLayer, goalCell.x, goalCell.y);
	Int numGoals = 1;
	if (!goals[0] || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, goals[0]))
		return 0;
	PathfindCell *parent = rva002E8BF8((PathfindLayerEnum)obj->rva0028B511(), &from);
	if (!parent)
		return 0;
	goals[0]->allocateInfo((In002E6BA1 *)&goalCell);
	parent->allocateInfo((In002E6BA1 *)&startCell);
	parent->StartPathfind((Int)goals[0]);
	parent->m_pathInfo->totalCost = (unsigned short)rva002F0A72(parent, goals[0]);
	AddToOpenList(parent);
	Int cellCount = 0;
	while (nodes && numGoals < 20)
	{
		nodes = nodes->next;
		if (nodes)
		{
			goals[numGoals] = (PathfindCell *)rva001E3647Pos(nodes->layer, &nodes->position);
			if (goals[numGoals])
				++numGoals;
		}
	}
	Path *path;
	while ((parent = rva002F36E5()) != 0)
	{
		for (Int g = 0; g < numGoals; ++g)
		{
			if (parent == goals[g])
			{
				path = new Path;
				PrependCells(path, pos, parent, center);
				path->wordC = 1;
				goto done;
			}
		}
		parent->PutOnClosedList(&m_closedList);
		if (cellCount > 3000)
			break;
		CheckChangeLayers(parent, obj);
		static Int deltaX[] = {1, 0, -1, 0, 1, -1, -1, 1};
		static Int deltaY[] = {0, 1, 0, -1, 1, 1, -1, -1};
		const Int adjacent[5] = {0, 1, 2, 3, 0};
		Bool neighborFlags[8];
		for (Int i = 0; i < 8; ++i)
		{
			neighborFlags[i] = false;
			ICoord2D coords={parent->getXIndex()+deltaX[i],parent->getYIndex()+deltaY[i]};ICoord2D next=coords;
			PathfindCell *neighbor = getCell((PathfindLayerEnum)parent->getLayer(), next.x, next.y);
			if (!neighbor)
				continue;
			if ((unsigned char)((Rva002E6B06 *)neighbor)->rva002E6B06())
				continue;
			if ((unsigned char)((Rva002E6AF3 *)neighbor)->get())
				continue;
			Int neighborLayer = (neighbor->m_info >> 4) & 0x3f;
			Int parentLayer = (parent->m_info >> 4) & 0x3f;
			if (neighborLayer != parentLayer)
			{
				Int parentConnect = (parent->m_info >> 10) & 0x3f;
				if (neighborLayer != parentConnect)
				{
					Int neighborConnect = (neighbor->m_info >> 10) & 0x3f;
					if (neighborConnect != parentLayer && (parentConnect != 0x10 || neighborConnect != 0x10))
						continue;
				}
			}
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			Int extra = CalcCollisionFreeExtraCosts(obj, parent, (Rva002EBC7FPair *)&next, (PathfindLayerEnum)neighborLayer, radius, radius + (center ? 1 : 0), true);
			if (extra < 0 || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, neighbor))
			{
				neighbor->allocateInfo((In002E6BA1 *)&next);
				neighbor->PutOnClosedList(&m_closedList);
				continue;
			}
			neighborFlags[i] = true;
			if (!neighbor->m_pathInfo)
			{
				++cellCount;
				if (!TheMixFileInfoPool)
					Rva0052DBCDInit();
				neighbor->m_pathInfo = (PathfinderGroundInfo *)Rva002E8B7AInit((MixFileInfoBuffer **)&TheMixFileInfoPool, (Int)neighbor, (In002E6BA1 *)&next);
			}
			else
				neighbor->m_pathInfo->parentWaypoint = 0;
			Int cost = neighbor->CalcCostSoFar((const Rva002E6C79 *)parent);
			Int dx = abs(next.x - goals[0]->m_pathInfo->position.x);
			Int dy = abs(next.y - goals[0]->m_pathInfo->position.y);
			if ((neighbor->m_info & 0x10000) && dx + dy > 3)
				cost += 10;
			neighbor->m_pathInfo->flags &= ~1U;
			Int remaining = rva002F0A72(neighbor, goals[0]);
			if ((neighbor->m_info & 0xf) == 4)
				cost += 1000;
			neighbor->m_pathInfo->costSoFar = (unsigned short)(extra + cost);
			neighbor->SetParentCell((Int *)parent);
			neighbor->m_pathInfo->totalCost = (unsigned short)(neighbor->m_pathInfo->costSoFar + remaining);
			AddToOpenList(neighbor);
		}
	}
	path = 0;
done:
	rva002F40E7();
	goals[0]->ReleaseInfo();
	return path;
}
