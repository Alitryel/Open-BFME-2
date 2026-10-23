// cl: /Ireference/shims/bfme2_ascii /Ob0
// ??4GameSpyGroupRoom@@QAEAAV0@ABV0@@Z @0x00381E56 69B (formerly rowed as
// ??4Rva00381E56@@..., same bytes). GameSpyGroupRoom copy-assign: AsciiString
// at +0x00 via canonical StringBase<char>::set(copy) 0x000366F0, UnicodeString at +0x04 via
// pinned set 0x00037150, ints at +0x08..+0x1C copied, returns this.
// Evidence: 2 pinned calls plus 6 int moves; callers 0x00386DD3/0x00386E9C;
// next Rva00630D60Assign same /O1 /Ob0 assign recipe.
// Identity: GameSpyInfo::addGroupRoom 0x00386B7B (PeerDefs.cpp) reaches it
// as the GroupRoomMap value assignment (callers 0x00386DD3/0x00386E9C).
#include "ascii_string.h"


class GameSpyGroupRoom
{
public:
	GameSpyGroupRoom &operator=(const GameSpyGroupRoom &other);
private:
	AsciiString m00;
	StringBase<unsigned short> m04;
	int m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	int m1C;
};

GameSpyGroupRoom &GameSpyGroupRoom::operator=(const GameSpyGroupRoom &other)
{
	((StringBase<char> *)&m00)->set(*(const StringBase<char> *)&other.m00);
	m04.set(other.m04);
	m08 = other.m08;
	m0C = other.m0C;
	m10 = other.m10;
	m14 = other.m14;
	m18 = other.m18;
	m1C = other.m1C;
	return *this;
}
