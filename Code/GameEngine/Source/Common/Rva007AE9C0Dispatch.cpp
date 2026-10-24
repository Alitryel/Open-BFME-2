// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Retail manager table 0x00BCF9C4 places these forwards at slots 4 and 5;
// both dispatch through its seventh slot.

typedef unsigned int UnsignedInt;

class W3DProjectedShadow;
class RenderObjClass;
struct Rva0010C065Info;
class Shadow { public: struct ShadowTypeInfo; };
class W3DProjectedShadowManager
{
public:
 virtual ~W3DProjectedShadowManager();
 virtual void rva0010BE72();
 virtual W3DProjectedShadow *rva0010C065(Rva0010C065Info *);
 virtual W3DProjectedShadow *rva0010C145(RenderObjClass *,Shadow::ShadowTypeInfo *,bool,bool);
 virtual void forward(unsigned,unsigned,unsigned);
 virtual unsigned forwardIf(unsigned,void *,unsigned,unsigned);
 virtual W3DProjectedShadow *rva0010C2D5(int,RenderObjClass *,Shadow::ShadowTypeInfo *,Shadow::ShadowTypeInfo *);
};

void W3DProjectedShadowManager::forward( UnsignedInt first, UnsignedInt second,
	UnsignedInt third )
{
	rva0010C2D5(first, 0, (Shadow::ShadowTypeInfo *)second, (Shadow::ShadowTypeInfo *)third);
}

UnsignedInt W3DProjectedShadowManager::forwardIf( UnsignedInt first,
	void *second, UnsignedInt third, UnsignedInt fourth )
{
	if ( second == 0 ) {
		return 0;
	}
	return (UnsignedInt)rva0010C2D5(first, (RenderObjClass *)second, (Shadow::ShadowTypeInfo *)third, (Shadow::ShadowTypeInfo *)fourth);
}
