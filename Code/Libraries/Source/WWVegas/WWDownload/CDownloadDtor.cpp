// cl: /DNDEBUG /MD /EHs-c- /O2 /Ob2
//
// ??1CDownload@@QAE@XZ, retail 0x006C9730, 40 bytes. Non-virtual CDownload
// destructor: restores vtable 0x00CE89A0 then deletes m_Ftp at +0x5C0 via the
// unfolded vf0(0)+free idiom (push 0 / call [vf0] / push eax / call operator
// delete, with xor-eax null path that still frees 0).
//
// Zero Hour donor (reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/
// GeneralsMD/Code/Libraries/Source/WWVegas/WWDownload/Download.h):
// ~CDownload() { delete m_Ftp; }. A folded delete passes flag 1 with no
// separate free (probe-proven under both /O1 and /O2); retail passes flag 0
// and frees the result, so the TU spells it explicitly as
// ::operator delete(p != 0 ? p->scalarDeletingDestructor(0) : 0) per the
// DX8MeshRendererClass_Invalidate_Thunk precedent. Cftp slot 0 is the rowed
// deleting dtor ??_GCftp at 0x006CB5B0 (vtable 0x00CE8A38, single entry);
// the scalar ??1Cftp at 0x006CA600 is pinned. Layout m_Ftp +0x5C0 from the
// sibling CDownloadDownloadFile.cpp (DownloadFile 0x006C9760 slot 2 of the
// same vtable). Callers: DownloadManager dtor 0x005E09BC and unclaimed
// 0x005E0472. Neighbours: ctor 0x006C9640, DownloadFile 0x006C9760.

void __cdecl operator delete(void *ptr);

class Cftp;

class CDownload
{
public:
	virtual long PumpMessages();
	virtual long Abort();
	virtual long DownloadFile(const char *server, const char *username, const char *password, const char *file, const char *localfile, const char *regkey, bool tryresume);
	virtual long GetLastLocalFile(char *local_file, int maxlen);
	~CDownload();

private:
	char m_pad04[0x5C0 - 0x04];
	Cftp *m_Ftp;
};

inline CDownload::~CDownload()
{
	// This is an ABI view of Cftp's existing deleting-destructor slot, not
	// another virtual method on Cftp. Its single slot is 0x006CB5B0, which
	// returns this in eax and frees only when flags & 1 is set.
	struct DeletingDestructorSlot
	{
		virtual void *scalarDeletingDestructor(unsigned int flags);
	};
	::operator delete(m_Ftp != 0 ?
		reinterpret_cast<DeletingDestructorSlot *>(m_Ftp)->scalarDeletingDestructor(0) : 0);
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCDownloadInlineAnchor@@YAXPAVCDownload@@@Z absent-from-retail
void _bfmeCDownloadInlineAnchor(CDownload *download)
{
    download->CDownload::~CDownload();
}
#pragma inline_depth()
