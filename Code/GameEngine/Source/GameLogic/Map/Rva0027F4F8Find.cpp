// cl: /DNDEBUG /MD /EHsc
// ?getWaterHandleByID@Rva0027F4F8@@QAEPAXH@Z @0x0027F4F8 33B. Linear search of
// 8-byte entries from [this+0x14] to [this+0x18]: return second dword
// where first equals int arg else NULL. Caller 0x00283845.
struct WaterHandleEntry {
	int key;
	void *value;
};
class Rva0027F4F8 {
public: void *getWaterHandleByID(int key);
private: char m_pad00[20];
         WaterHandleEntry *m_begin;
         WaterHandleEntry *m_end;
};
void *Rva0027F4F8::getWaterHandleByID(int key)
{
	for (WaterHandleEntry *entry = m_begin; entry != m_end; ++entry)
		if (entry->key == key)
			return entry->value;
	return 0;
}
