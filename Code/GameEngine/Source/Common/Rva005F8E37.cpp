// cl: /DNDEBUG /MD
// Native constructor 0x005F8E37 stores the BattlePrompt owner at +0x3C.
// Its tab-window base is constructed with the level and AsciiString name.
extern "C" const void *const vtbl_00C79CF8[];	// ??_7Rva005F8F5A@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C79CF8=??_7Rva005F8F5A@@6B@")

class AsciiString;
namespace StrategicHUD { class BattlePromptMovieClip { public: class Impl; }; }
class Rva005F8E37
{
public:
	Rva005F8E37(StrategicHUD::BattlePromptMovieClip::Impl *, int, const AsciiString &);
	char m_pad[0x3C];
	StrategicHUD::BattlePromptMovieClip::Impl *m_3C;
};

class Rva005FE7FA { public: Rva005FE7FA(int, const AsciiString &); };

Rva005F8E37::Rva005F8E37(StrategicHUD::BattlePromptMovieClip::Impl *owner, int level, const AsciiString &name)
{
	((Rva005FE7FA *)this)->Rva005FE7FA::Rva005FE7FA(level, name);
	m_3C = owner;
	((void **)this)[0] = (void *)vtbl_00C79CF8;
}
