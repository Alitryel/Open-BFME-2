// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
//
// ?rva002B39CF@Rva002BA8F1Logic@@QAEXXZ retail 0x002B39CF 121B: with more
// than one player in the +0x8C list, hand the local role (rowed setLocal,
// 0x002B38F7, Rva002B38F7.cpp) to the player after the current +0x98 one,
// wrapping round; nothing happens when the current player is not listed.
// Kept out of setLocal's unit so the call sees only its declaration. The
// list is a pointer vector (begin/end/capacity at +0x8C/+0x90/+0x94); names
// are address-derived.

class Rva002E2903Player;

struct Rva002B39CFPlayerList
{
	unsigned int size() const { return m_end - m_begin; }
	Rva002E2903Player *operator[](unsigned int i) const { return m_begin[i]; }
	Rva002E2903Player **m_begin;
	Rva002E2903Player **m_end;
	Rva002E2903Player **m_capacity;
};

class Rva002BA8F1Logic
{
public:
	void setLocal(Rva002E2903Player *player);
	void rva002B39CF();
private:
	char m_pad00[0x8C];
	Rva002B39CFPlayerList m_players; // +0x8C
	Rva002E2903Player *m_98;
};

void Rva002BA8F1Logic::rva002B39CF()
{
	if (m_players.size() > 1) {
		int index = -1;
		for (unsigned int i = 0; i < m_players.size(); ++i) {
			if (m_players[i] == m_98) {
				index = i;
				break;
			}
		}
		if (index >= 0)
			setLocal(m_players[(index + 1) % m_players.size()]);
	}
}
