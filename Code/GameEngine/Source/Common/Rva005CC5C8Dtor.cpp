// cl: /MD
// ??1Rva005CC5C8@@UAE@XZ @0x005CC5C8 11B
// Derived dtor stores vtable 0x00874EAC then tail-jmps to rowed base ??1RegionDetailsMovieClip@StrategicHUD@@UAE@XZ at 0x005E3258.
// Evidence: mov [ecx] vtable then jmp base shape; chain lane calls 0x005E3258 landed; caller 0x005CC67F.
namespace StrategicHUD {
class RegionDetailsMovieClip
{
public:
	virtual ~RegionDetailsMovieClip();
};
}

class Rva005CC5C8 : public StrategicHUD::RegionDetailsMovieClip
{
public:
	virtual ~Rva005CC5C8();
};

Rva005CC5C8::~Rva005CC5C8()
{
}
