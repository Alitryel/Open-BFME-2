// cl: /O1 /DNDEBUG /MD /EHsc
// cl: /O1 /DNDEBUG /MD /EHsc
//
// ?rva00232A42@Keyboard@@QAEXXZ @0x00232A42 (166B): Keyboard key-list
// resync over the m_keys vector walked as stride-8 KeyboardIO records.
// Each record refreshes its kind-indexed m_keyStatus slot (flag/key/frame),
// kind 0x0F sets the record flag when either status byte carries bit 2, and
// seven kinds route through translateKey 0x00232763; then rowed
// checkKeyRepeat 0x002329D3 runs and nonzero modifiers OR into every
// record. Per-statement kind re-reads (aliasing blocks CSE) plus the direct
// slot indexing reproduce retail. Layout reuses Keyboard.cpp's proven
// Keyboard model; KeyboardIO field roles are structural.
#include "KeyboardView.h"

struct KeySlot
{
	unsigned char m_pad0;
	unsigned char m_flag;
	unsigned short m_key;
	unsigned int m_frame;
};

void Keyboard::rva00232A42()
{
	KeyboardIO *rec = (KeyboardIO *)m_keys._M_start;
	KeyboardIO *end = (KeyboardIO *)m_keys._M_finish;
	while (rec != end) {
		((KeySlot *)&m_keyStatus)[rec->key].m_key = rec->state;
		((KeySlot *)&m_keyStatus)[rec->key].m_flag = rec->status;
		((KeySlot *)&m_keyStatus)[rec->key].m_frame = m_inputFrame;
		unsigned char kind = rec->key;
		if (kind == 0x0F) {
			if (((((unsigned char *)m_keyStatus)[0x1C2] & 2) != 0) || ((((unsigned char *)m_keyStatus)[0x5C2] & 2) != 0))
				rec->status = 1;
		}
		else if (kind == 0x3A || kind == 0x1D || kind == 0x9D || kind == 0x2A || kind == 0x36 || kind == 0x38 || kind == 0xB8) {
			translateKey((unsigned short)kind);
		}
		++rec;
	}
	checkKeyRepeat();
	if (m_modifiers != 0) {
		KeyboardIO *last = (KeyboardIO *)m_keys._M_finish;
		KeyboardIO *keyboardIO = (KeyboardIO *)m_keys._M_start;
		while (keyboardIO != last) {
			keyboardIO->state |= m_modifiers;
			++keyboardIO;
		}
	}
}
