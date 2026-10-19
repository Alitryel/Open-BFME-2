// ?FindCollisionFreeQuickPath@Pathfinder@@UAEPAVPath@@PAVObject@@PBUCoord3D@@PAVPathNode@@@Z
// partial score=0.7902476780185759 date=2026-10-19
// ?FindCollisionFreeQuickPath@Pathfinder@@UAEPAVPath@@PAVObject@@PBUCoord3D@@PAVPathNode@@@Z
// partial score=0.6684385564 date=2026-10-16
// Owner patch for Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp; apply diff before compiling.
// Existing83 owner rows verified, including vptr/field layout preservation.
// Current candidate: 2026-10-19; model=gpt-6.1-sol. The preceding score and owner-row count are preserved historical evidence.
// Current owner patch follows. Evidence: reverse/attempt_support/0x002f64dd-20261019-w5.md.
// align_diff: 48 structural / 70 memory / 65 register -> 3 / 7 / 0; all seven remaining memory differences are DIR32 relocations.
// Emitted 1298 versus retail 1286 bytes; frame 0xB0 exact; remaining mismatch is shared return-block placement.
#if 0
--- a/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
+++ b/Code/GameEngine/Source/GameLogic/Pathfinder/pathfinder.cpp
@@ -631,6 +631,17 @@
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
  Bool rva002F07F5(Object *,const Coord3D *);
  Bool IsValidHordeMemberRegularMovement(Object *,const Coord3D *,const Coord3D *,const Coord3D *);
  Bool AdjustToNearestValidCell(Coord3D *);
@@ -736,7 +747,7 @@
 		Coord3D *adjustedTo);
 private:
 	Int iterateCellsAlongLine(const ICoord2D *,const ICoord2D *,PathfindLayerEnum,Rva002E7261Info *);
-	char m_pad000[8];Bool m_isMapReady;char m_pad009[7];
+	char m_pad004[4];Bool m_isMapReady;char m_pad009[7];
 	int m_unknown10;
 	ICoord2D m_clampLo, m_clampHi;	// +0x14 cell extent the 0x002E7917 clamp uses
     Int m_extentLowX,m_extentLowY,m_extentHighX,m_extentHighY;
@@ -5304,3 +5315,129 @@
 }
 return cellCount;
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
+	char *ai = obj->m_258;
+	Rva002E8BCF info((const Rva002E8BCFSrc *)(ai+0x1cc), !flag, priority - 1, obj->rva0028AFBB());
+	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
+	PathfindCell *goals[20];
+	goals[0] = getCell(goalLayer, goalCell.x, goalCell.y);
+	Int numGoals = 1;
+	if (!goals[0] || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, goals[0]))
+		return 0;
+	PathfindLayerEnum fromLayer = (PathfindLayerEnum)obj->rva0028B511();
+	PathfindCell *parent = rva002E8BF8(fromLayer, &from);
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
+			PathfindLayerEnum nodeLayer = nodes->layer;
+			goals[numGoals] = (PathfindCell *)rva001E3647Pos(nodeLayer, &nodes->position);
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
+			if (neighbor->getLayer() != parent->getLayer()
+				&& neighbor->getLayer() != parent->getConnectLayer()
+				&& neighbor->getConnectLayer() != parent->getLayer()
+				&& !(parent->getConnectLayer() == 16 && neighbor->getConnectLayer() == parent->getConnectLayer()))
+				continue;
+			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
+				continue;
+			Int extra = CalcCollisionFreeExtraCosts(obj, parent, (Rva002EBC7FPair *)&next, (PathfindLayerEnum)neighbor->getLayer(), radius, radius + (center ? 1 : 0), true);
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
+			Int dx = abs(coords.x - goals[0]->getXIndex());
+			Int dy = abs(coords.y - goals[0]->getYIndex());
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
	char *ai = obj->m_258;
	Rva002E8BCF info((const Rva002E8BCFSrc *)(ai+0x1cc), !flag, priority - 1, obj->rva0028AFBB());
	PathfindLayerEnum goalLayer = TheTerrainLogic->getLayerForDestination(obj, to);
	PathfindCell *goals[20];
	goals[0] = getCell(goalLayer, goalCell.x, goalCell.y);
	Int numGoals = 1;
	if (!goals[0] || !((Rva002E6DC4 *)this)->rva002E6DC4(&info, goals[0]))
		return 0;
	PathfindLayerEnum fromLayer = (PathfindLayerEnum)obj->rva0028B511();
	PathfindCell *parent = rva002E8BF8(fromLayer, &from);
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
			PathfindLayerEnum nodeLayer = nodes->layer;
			goals[numGoals] = (PathfindCell *)rva001E3647Pos(nodeLayer, &nodes->position);
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
			if (neighbor->getLayer() != parent->getLayer()
				&& neighbor->getLayer() != parent->getConnectLayer()
				&& neighbor->getConnectLayer() != parent->getLayer()
				&& !(parent->getConnectLayer() == 16 && neighbor->getConnectLayer() == parent->getConnectLayer()))
				continue;
			if (i >= 4 && !neighborFlags[adjacent[i - 4]] && !neighborFlags[adjacent[i - 3]])
				continue;
			Int extra = CalcCollisionFreeExtraCosts(obj, parent, (Rva002EBC7FPair *)&next, (PathfindLayerEnum)neighbor->getLayer(), radius, radius + (center ? 1 : 0), true);
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
			Int dx = abs(coords.x - goals[0]->getXIndex());
			Int dy = abs(coords.y - goals[0]->getYIndex());
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
