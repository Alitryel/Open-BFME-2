// cl: /MD
//
// ?rva000A77B3@AudioFileCache@@QAEXXZ, retail 0x000A77B3, 38 bytes.
// Closes the thread handle at +0x48 after waiting on it, sets byte at +0x4C.
// Imports WaitForSingleObject and CloseHandle from KERNEL32 (IAT). No EH.
// Callers at 0x0006101B (~MilesAudioManager, on m_audioFileCache) and
// 0x000A7D0F (~AudioFileCache, on its own this); +0x48/+0x4C are the cache's
// loader thread handle and quit flag.

extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long timeout);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *handle);

class AudioFileCache
{
public:
	void rva000A77B3();

private:
	char m_pad00[0x48];
	void *m_handle;
	bool m_done;
};

void AudioFileCache::rva000A77B3()
{
	void *handle = m_handle;
	m_done = true;
	if (handle != 0)
	{
		WaitForSingleObject(handle, 0xFFFFFFFF);
		CloseHandle(m_handle);
		m_handle = 0;
	}
}
