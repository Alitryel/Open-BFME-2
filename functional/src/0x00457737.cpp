// ?createScaffolding@BridgeBehavior@@UAEXXZ
// partial score=0.8130978755323712 date=2026-10-16
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /ICode/Libraries/Include /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// W9-A1 round2: canonical Coord3D/Coord2D and local ScaffoldCoord copy lifetime;
// existing WWMath conversion; real338B setScaffoldData visible; no private coordinate
// classes, new assembly, volatile experiment or artificial ID temp retained.
// W7-G1 r6 (2026-10-14): rebuilt from the ZH body, sizes/targets re-derived against retail.
// Levers found: (1) Coord3D needs an INLINE COPY CONSTRUCTOR (member-wise copy) while assignment stays
// a block copy: ZH `ScaffoldCoord supportRiseToPos = *riseToPos;` then yields retail's scalar copies in the
// left half and movsd block copies in the right half (assignments). (2) cl evaluates `Above()+Below()`
// by member-declaration order, not source order: declare GeometryInfo::getMaxHeightBelowPosition BEFORE
// getMaxHeightAbovePosition and the ZH expression calls Above first like retail. (3) Score with the
// T1-lab scorer (raw compile is 1872 B; the U1-lab scorer under-reports the size).
// State: instruction stream matches retail modulo stack displacements; nd 213 (T1 gen_args/barrier/
// vref/swap mutations), frame 0x1A8 vs retail 0x1A0: wall = stack-slot ranking (retail ranks the three
// AsciiString locals above leftAngle/rightAngle/scaffoldHeight and shares the ObjectID temp across all
// four appends and rightAngle's slot with the second height-partial temp; ours opposite). Declaration
// order of locals/masks is inert.
// BridgeBehavior::createScaffolding (retail 0x00457737, 1851B), the Zero Hour
// GameEngine/Source/GameLogic/Object/Behavior/BridgeBehavior.cpp body built
// /O1 G7 SSE like the rest of the BridgeBehavior TU
// (BridgeBehaviorAreaEffects.cpp). `this` is the BridgeBehaviorInterface
// subobject at +0x20; setScaffoldData (0x004568EC) runs on the behavior.
// BFME target facts: scaffold present flag +0xFD and scaffold ObjectID list
// +0x100 of the behavior; scaffold/support template names come from the road
// template (0x002D9BC1 / 0x0056394A) and are looked up through
// TheThingFactory 0x002D06CA; geometry major radius at template +0xB0 and
// the GeometryInfo height getters 0x000BD7C0 / 0x000BD8A0 on template +0xA0;
// objects come from the four-argument newObject with a zeroed CreateMask
// and the owner's team (+0x304); bridge layer +0xC4 goes to
// Pathfinder::SetBridgeStateRepaired(layer, false) on TheAI +0x10.
// The bridge template name getter is the ICF-folded 0x000AF1DD body, reached
// through the admitted TerrainType::getTexture pin as in
// BridgeBehaviorAreaEffects.cpp.
#include "ascii_string.h"
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"
struct ScaffoldCoord:Coord3D {
 ScaffoldCoord(){}
 ScaffoldCoord(const Coord3D&o){x=o.x;y=o.y;z=o.z;}

};
#include <math.h>
#include <string.h>
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
#define TWO_PI 6.28318530718f
#include "wwmath.h"
#define REAL_TO_INT_CEIL(x) WWMath::Float_To_Long((Real)ceil(x))
#define INT_TO_REAL(x) ((Real)(x))
class Team;
class GeometryInfo

{
 public:
 Real getMajorRadius() const 
 {
  return m_majorRadius;
  
 }
 Real getMaxHeightBelowPosition() const;
 Real getMaxHeightAbovePosition() const;
 private:
 unsigned char m_unmodelled00[0x10];
 Real m_majorRadius;
// +0x10
 
}
;
class ThingTemplate

{
 public:
 const GeometryInfo &getTemplateGeometryInfo() const 
 {
  return m_geometryInfo;
  
 }
 private:
 unsigned char m_unmodelled000[0xA0];
 GeometryInfo m_geometryInfo;
// +0xA0
 
}
;
typedef UnsignedInt ObjectID;
class Thing {public:void setPosition(const Coord3D*);void setOrientation(Real);};
class Object:public Thing

{
 public:
 ObjectID getID() const 
 {
  return m_id;
  
 }
 const Coord3D *getPosition() const 
 {
  return &m_pos;
  
 }
 Team *getTeam() const 
 {
  return m_team;
  
 }
 private:
 unsigned char m_unmodelled000[0x38];
 Coord3D m_pos;
// +0x38
 unsigned char m_unmodelled044[0x74 - 0x44];
 ObjectID m_id;
// +0x74
 unsigned char m_unmodelled078[0x304 - 0x78];
 Team *m_team;
// +0x304
 
}
;
// newObject's third argument: a 16-byte bit mask, zeroed when constructed.
struct CreateMask

{
 unsigned int m_bits[4];
 
}
;
class ThingFactory

{
 public:
 Object *newObject(const ThingTemplate *tmplate, Team *team, const CreateMask *mask, bool b);
 const ThingTemplate *findTemplate(const AsciiString &name);
 
}
;
extern ThingFactory *TheThingFactory;
class Rva002D9BC1AsciiField

{
 public:
 AsciiString get() const;
 
}
;
class Rva0056394A

{
 public:
 AsciiString rva0056394A();
 
}
;
// The road template's scaffold / scaffold-support object name getters are
// rowed under address-derived owners (0x002D9BC1 / 0x0056394A).
class TerrainRoadType;
class Rva0027C36A

{
 public:
 Rva0027C36A();
 Rva0027C36A &operator=(const Rva0027C36A &other);
 Coord3D from;
// +0x00
 Coord3D to;
// +0x0C
 Real bridgeWidth;
// +0x18
 Coord3D fromLeft;
// +0x1C
 Coord3D fromRight;
// +0x28
 Coord3D toLeft;
// +0x34
 Coord3D toRight;
// +0x40
 private:
 char m_pad4C[0xA8 - 0x4C];
 
}
;
typedef Rva0027C36A BridgeInfo;
class TerrainType

{
 public:
 AsciiString getTexture() const;
 
}
;
class Bridge

{
 public:
 void getBridgeInfo(BridgeInfo *info) 
 {
  *info = m_bridgeInfo;
  
 }
 Int getLayer() const 
 {
  return m_layer;
  
 }
 private:
 void *m_vtable;
 Bridge *m_next;
// +0x04
 AsciiString m_templateName;
// +0x08
 BridgeInfo m_bridgeInfo;
// +0x0C
 char m_padB4[0xC4 - 0xB4];
 Int m_layer;
// +0xC4
 
}
;
class TerrainRoadCollection

{
 public:
 TerrainRoadType *findBridge(AsciiString name);
 
}
;
extern TerrainRoadCollection *TheTerrainRoads;
class TerrainLogic

{
 public:
 virtual void slot00();
 virtual void slot04();
 virtual void slot08();
 virtual void slot0C();
 virtual void slot10();
 virtual void slot14();
 virtual void slot18();
 virtual void slot1C();
 virtual void slot20();
 virtual void slot24();
 virtual void slot28();
 virtual void slot2C();
 virtual void slot30();
 virtual void slot34();
 virtual void slot38();
 virtual void slot3C();
 virtual void slot40();
 virtual void slot44();
 virtual void slot48();
 virtual void slot4C();
 virtual void slot50();
 virtual void slot54();
 virtual void slot58();
 virtual void slot5C();
 virtual void slot60();
 virtual void slot64();
 virtual void slot68();
 virtual void slot6C();
 virtual void slot70();
 virtual void slot74();
 virtual void slot78();
 virtual void slot7C();
 virtual void slot80();
 virtual void slot84();
 virtual void slot88();
 virtual void slot8C();
 virtual void slot90();
 virtual void slot94();
 virtual void slot98();
 virtual void slot9C();
 virtual void slotA0();
 virtual Bridge *findBridgeAt(const Coord3D *loc) const;
 
}
;
extern TerrainLogic *TheTerrainLogic;
class Pathfinder

{
 public:
 void SetBridgeStateRepaired(Int layer, bool repaired);
 
}
;
class AI

{
 public:
 Pathfinder *pathfinder() 
 {
  return m_pathfinder;
  
 }
 private:
 unsigned char m_unmodelled00[0x10];
 Pathfinder *m_pathfinder;
// +0x10
 
}
;
extern AI *TheAI;
class Rva002A1B6FNativeList

{
 public:
 void append(void *const &value);
 
}
;
struct BridgeBehaviorModuleData {char pad[8];Real m_lateralScaffoldSpeed,m_verticalScaffoldSpeed;};
class BridgeBehaviorBase

{
 public:
 virtual ~BridgeBehaviorBase();
 Object *getObject() const 
 {
  return m_object;
  
 }
 protected:
 BridgeBehaviorModuleData *m_moduleData;
// +0x04
 Object *m_object;
// +0x08
 unsigned char m_unmodelled0C[0x20 - 0x0C];
 
}
;
class BridgeBehaviorInterface

{
 public:
 virtual void createScaffolding() = 0;
 
}
;
class BridgeBehavior : public BridgeBehaviorBase, public BridgeBehaviorInterface

{
 public:
 virtual void createScaffolding();
 protected:
 void setScaffoldData(Object *obj, Real *angle, Real *height, const Coord3D *riseToPos,
 const Coord3D *buildPos, const Coord3D *bridgeCenter);
 private:
 unsigned char m_unmodelled24[0xFD - 0x24];
 Bool m_scaffoldPresent;
// +0xFD
 unsigned char m_unmodelledFE[0x100 - 0xFE];
 Rva002A1B6FNativeList m_scaffoldObjectIDList;
// +0x100
 
}
;
// ------------------------------------------------------------------------------------------------
/** Start the bridge repair scaffolding.  If we already have scaffolding this call
	* is ignored */
// ------------------------------------------------------------------------------------------------
class BridgeScaffoldBehaviorInterface
{
public:
	virtual void setPositions(const Coord3D *sunkenPosition,
		const Coord3D *risePosition, const Coord3D *buildPosition);
	virtual void setMotion(int motion);
	virtual int getCurrentMotion() const;
	virtual void reverseMotion();
	virtual void setLateralSpeed(Real speed);
	virtual void setVerticalSpeed(Real speed);
};

class BridgeScaffoldBehavior
{
public:
	static BridgeScaffoldBehaviorInterface *getBridgeScaffoldBehaviorInterfaceFromObject(Object *object);
};


extern const Real g_00BC2A10;
void BridgeBehavior::setScaffoldData(Object *object, Real *angle,
	Real *sunkenHeight, const Coord3D *risePosition,
	const Coord3D *buildPosition, const Coord3D *bridgeCenter)
{
	if (!object)
		return;
	if (!angle)
		return;
	if (!risePosition)
		return;
	if (!buildPosition)
		return;

	BridgeBehaviorModuleData *moduleData = m_moduleData;
	BridgeScaffoldBehaviorInterface *scaffold =
		BridgeScaffoldBehavior::getBridgeScaffoldBehaviorInterfaceFromObject(object);
	Coord3D sunkenPosition;
	sunkenPosition.x = risePosition->x;
	sunkenPosition.y = risePosition->y;
	sunkenPosition.z = risePosition->z - *sunkenHeight - g_00BC2A10;
	object->setPosition(&sunkenPosition);
	scaffold->setPositions(&sunkenPosition, risePosition, buildPosition);
	scaffold->setMotion(1);
	((Thing *)object)->setOrientation(*angle);

	Real lateralSpeed = moduleData->m_lateralScaffoldSpeed;
	Coord3D buildToCenter;
	buildToCenter.x = buildPosition->x - risePosition->x;
	buildToCenter.y = buildPosition->y - risePosition->y;
	buildToCenter.z = buildPosition->z - risePosition->z;
	Coord3D riseToCenter;
	riseToCenter.x = bridgeCenter->x - risePosition->x;
	riseToCenter.y = bridgeCenter->y - risePosition->y;
	riseToCenter.z = bridgeCenter->z - risePosition->z;
	Real buildDistance = buildToCenter.length();
	Real riseDistance = riseToCenter.length();
	scaffold->setLateralSpeed(lateralSpeed * (buildDistance / riseDistance));
	Real verticalSpeed = moduleData->m_verticalScaffoldSpeed;
	scaffold->setVerticalSpeed(verticalSpeed);
}

void BridgeBehavior::createScaffolding( void )

{
// if we already have scaffolding, do nothing
 if( m_scaffoldPresent == true )
 return;
// get our bridge
 Object *us = getObject();
 const Coord3D *center = us->getPosition();
 Bridge *bridge = TheTerrainLogic->findBridgeAt( us->getPosition() );
// get the bridge template
 AsciiString bridgeTemplateName = ((const TerrainType *)bridge)->getTexture();
 TerrainRoadType *bridgeTemplate = TheTerrainRoads->findBridge( bridgeTemplateName );
// get the scaffold template
 AsciiString scaffoldObjectName = ((const Rva002D9BC1AsciiField *)bridgeTemplate)->get();
 const ThingTemplate *scaffoldTemplate = TheThingFactory->findTemplate( scaffoldObjectName );
 if( scaffoldTemplate == 0 )
 return;
// get the scaffold support template
 AsciiString scaffoldSupportObjectName = ((Rva0056394A *)bridgeTemplate)->rva0056394A();
 const ThingTemplate *scaffoldSupportTemplate = TheThingFactory->findTemplate( scaffoldSupportObjectName );
 if( scaffoldSupportTemplate == 0 )
 return;
// how far apart are the scaffold objects, and how tall are they
 Real spacing = scaffoldTemplate->getTemplateGeometryInfo().getMajorRadius() * 2.0f;
 Real scaffoldHeight = scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition() +
 scaffoldTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition();
 Real scaffoldSupportHeight = scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightAbovePosition() +
 scaffoldSupportTemplate->getTemplateGeometryInfo().getMaxHeightBelowPosition();
// get the bridge info
 BridgeInfo bridgeInfo;
 bridge->getBridgeInfo( &bridgeInfo );
// the scaffolding starts at the middle of each end of the bridge
 Coord3D leftStart;
 leftStart.x = ((bridgeInfo.fromLeft.x - bridgeInfo.fromRight.x) / 2.0f) + bridgeInfo.fromRight.x;
 leftStart.y = ((bridgeInfo.fromLeft.y - bridgeInfo.fromRight.y) / 2.0f) + bridgeInfo.fromRight.y;
 leftStart.z = ((bridgeInfo.fromLeft.z - bridgeInfo.fromRight.z) / 2.0f) + bridgeInfo.fromRight.z;
 Coord3D rightStart;
 rightStart.x = ((bridgeInfo.toLeft.x - bridgeInfo.toRight.x) / 2.0f) + bridgeInfo.toRight.x;
 rightStart.y = ((bridgeInfo.toLeft.y - bridgeInfo.toRight.y) / 2.0f) + bridgeInfo.toRight.y;
 rightStart.z = ((bridgeInfo.toLeft.z - bridgeInfo.toRight.z) / 2.0f) + bridgeInfo.toRight.z;
// angles of the scaffolding at each end
 Coord2D angleV;
 angleV.x = rightStart.x - leftStart.x;
 angleV.y = rightStart.y - leftStart.y;
 Real leftAngle = angleV.toAngle();
 Real rightAngle = leftAngle + TWO_PI;
// vectors from each end to the other
 Coord3D leftVector;
 leftVector.x = rightStart.x - leftStart.x;
 leftVector.y = rightStart.y - leftStart.y;
 leftVector.z = rightStart.z - leftStart.z;
 Coord3D rightVector;
 rightVector.x = leftStart.x - rightStart.x;
 rightVector.y = leftStart.y - rightStart.y;
 rightVector.z = leftStart.z - rightStart.z;
// how many objects we need
 Real tileDistance = leftVector.length();
 Int numObjects = REAL_TO_INT_CEIL( tileDistance / spacing ) + 1;
 Int numIterations = REAL_TO_INT_CEIL( INT_TO_REAL( numObjects ) / 2.0f );
 leftVector.normalize();
 rightVector.normalize();
// create the objects from each end towards the middle
 Int scaffoldObjectsCreated = 0;
 Coord3D destinationPos, *riseToPos;
 Real *angle;
 Object *obj;
 for( Int i = 0; i < numIterations; ++i )
 
 {
// the left side
  CreateMask leftMask;
  memset( &leftMask, 0, sizeof( leftMask ) );
  obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam(), &leftMask, false );
  riseToPos = &leftStart;
  angle = &leftAngle;
  destinationPos.x = leftVector.x * (spacing * i) + riseToPos->x + 0.1f;
  destinationPos.y = leftVector.y * (spacing * i) + riseToPos->y;
  destinationPos.z = leftVector.z * (spacing * i) + riseToPos->z;
  setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );
  scaffoldObjectsCreated++;
  m_scaffoldObjectIDList.append( (void *)obj->getID() );
// supports under the left piece
  Real offset = riseToPos->z;
  ScaffoldCoord supportDestinationPos = destinationPos;
  ScaffoldCoord supportRiseToPos = *riseToPos;
  ScaffoldCoord supportBridgeCenter = *center;
  while( offset >= 0.0f )
  
  {
   supportRiseToPos.z -= scaffoldSupportHeight;
   supportDestinationPos.z -= scaffoldSupportHeight;
   supportBridgeCenter.z -= scaffoldSupportHeight;
   CreateMask supportMask;
   memset( &supportMask, 0, sizeof( supportMask ) );
   obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam(), &supportMask, false );
   setScaffoldData( obj, angle, &scaffoldSupportHeight,
   &supportRiseToPos, &supportDestinationPos, &supportBridgeCenter );
   m_scaffoldObjectIDList.append( (void *)obj->getID() );
   offset -= scaffoldSupportHeight;
   
  }
// end while
// the right side
  if( scaffoldObjectsCreated < numObjects )
  
  {
   CreateMask rightMask;
   memset( &rightMask, 0, sizeof( rightMask ) );
   obj = TheThingFactory->newObject( scaffoldTemplate, us->getTeam(), &rightMask, false );
   riseToPos = &rightStart;
   angle = &rightAngle;
   destinationPos.x = rightVector.x * (spacing * i) + riseToPos->x + 0.1f;
   destinationPos.y = rightVector.y * (spacing * i) + riseToPos->y;
   destinationPos.z = rightVector.z * (spacing * i) + riseToPos->z;
   setScaffoldData( obj, angle, &scaffoldHeight, riseToPos, &destinationPos, center );
   scaffoldObjectsCreated++;
   m_scaffoldObjectIDList.append((void*)obj->getID());
   offset = riseToPos->z;
   (Coord3D&)supportRiseToPos = *riseToPos;
   (Coord3D&)supportDestinationPos = destinationPos;
   (Coord3D&)supportBridgeCenter = *center;
   while( offset >= 0.0f )
   
   {
    supportRiseToPos.z -= scaffoldSupportHeight;
    supportDestinationPos.z -= scaffoldSupportHeight;
    supportBridgeCenter.z -= scaffoldSupportHeight;
    CreateMask supportMask;
    memset( &supportMask, 0, sizeof( supportMask ) );
    obj = TheThingFactory->newObject( scaffoldSupportTemplate, us->getTeam(), &supportMask, false );
    setScaffoldData( obj, angle, &scaffoldSupportHeight,
    &supportRiseToPos, &supportDestinationPos, &supportBridgeCenter );
    m_scaffoldObjectIDList.append( (void *)obj->getID() );
    offset -= scaffoldSupportHeight;
    
   }
// end while
   
  }
// end if
  
 }
// end for i
// we now have scaffolding
 m_scaffoldPresent = true;
// the bridge is not passable while being repaired
 TheAI->pathfinder()->SetBridgeStateRepaired( bridge->getLayer(), false );
 
}
// end createScaffolding
