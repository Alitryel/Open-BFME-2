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
