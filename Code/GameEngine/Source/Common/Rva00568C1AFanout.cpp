// cl: /MD
//
// ?rva00568C1A@Rva00568C1A@@QAEXXZ @0x00568C1A 28B.
// Fan-out: run every element of the +0x58/+0x5C pointer range through
// the (banked) 0x00568939 keyed notify with this as the key. Same
// LargeGroupAudioSoundKeyPair element view as the banked notify TU.
class LargeGroupAudioSoundKeyPair
{
public:
	void rva00568939(int key);
};

class Rva00568C1A
{
public:
	void rva00568C1A();
private:
	char m_pad[0x58];
	LargeGroupAudioSoundKeyPair **m_begin58;
	LargeGroupAudioSoundKeyPair **m_end5C;
};

void Rva00568C1A::rva00568C1A()
{
	for (LargeGroupAudioSoundKeyPair **largeGroupAudioSoundKeyPair = m_begin58; largeGroupAudioSoundKeyPair != m_end5C; ++largeGroupAudioSoundKeyPair)
		(*largeGroupAudioSoundKeyPair)->rva00568939((int)this);
}
