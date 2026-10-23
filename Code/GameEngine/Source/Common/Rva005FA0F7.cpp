// cl: /O1 /G6 /DNDEBUG /MD
// Native constructor 0x005FA0F7 builds PlayerPageFrame for the Enemy side.
// The owner supplies level/name at +4/+8; index and record follow on the stack.
extern "C" const void *__identifier("??_7Rva005FA141@@6B@")[];
class AsciiString;
struct Rva005F91F3Src;
namespace StrategicHUD { class BattlePromptMovieClip { public: class Impl; }; }
class StrategicHUD::BattlePromptMovieClip::Impl { public: int word0, level, nameWord; };

class Rva005FA0F7
{
public:
	Rva005FA0F7(StrategicHUD::BattlePromptMovieClip::Impl *, int, const Rva005F91F3Src &);
	char m_pad[4];
};

namespace StrategicHUD {
class PlayerPageFrame
{
public:
	PlayerPageFrame(int level, const AsciiString &name, const char *side,
		int index, const Rva005F91F3Src &record);
};
}


Rva005FA0F7::Rva005FA0F7(StrategicHUD::BattlePromptMovieClip::Impl *owner, int index, const Rva005F91F3Src &record)
{
	((StrategicHUD::PlayerPageFrame *)this)->StrategicHUD::PlayerPageFrame::PlayerPageFrame(owner->level, *(const AsciiString *)&owner->nameWord,
		"Enemy", index, record);
	((int *)this)[0] = (int)__identifier("??_7Rva005FA141@@6B@");
}
