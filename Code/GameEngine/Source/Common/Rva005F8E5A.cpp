// cl: /DNDEBUG /MD
// Native constructor 0x005F8E5A stores the BattlePrompt owner at +0x38.
// Its tab-window base is constructed with the level and AsciiString name.
extern "C" const void *const vtbl_00C79D0C[];	// ??_7Rva005F8F7B@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C79D0C=??_7Rva005F8F7B@@6B@")

class AsciiString;
namespace StrategicHUD { class BattlePromptMovieClip { public: class Impl; }; }
class Rva005F8E5A
{
public:
	Rva005F8E5A(StrategicHUD::BattlePromptMovieClip::Impl *, int, const AsciiString &);
	char m_pad[0x38];
	StrategicHUD::BattlePromptMovieClip::Impl *m_38;
};

class Rva005FE750 { public: Rva005FE750(int, const AsciiString &); };

Rva005F8E5A::Rva005F8E5A(StrategicHUD::BattlePromptMovieClip::Impl *owner, int level, const AsciiString &name)
{
	((Rva005FE750 *)this)->Rva005FE750::Rva005FE750(level, name);
	m_38 = owner;
	((void **)this)[0] = (void *)vtbl_00C79D0C;
}
