// cl: /O1 /MD /EHsc /DNDEBUG
// ??0Rva001040D5@@QAE@XZ retail 0x001040D5 18B.
// Evidence: calls rowed base SimpleSceneClass 0x00142960 then installs vtable 0x00BCF6F0; neighbours Sub and VslotSmallBodiesAJ.
class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();
};

class Rva001040D5 : public SimpleSceneClass
{
public:
	Rva001040D5();
	virtual ~Rva001040D5();
};

Rva001040D5::Rva001040D5()
{
}

// vftable 0x00BCF6F0 slot 1 is the deleting dtor 0x001042CF, whose dtor call goes to the 5-byte tail jump at 0x00740555.
#pragma comment(linker, "/alternatename:??1Rva001040D5@@UAE@XZ=??1Rva00740555@@UAE@XZ")
