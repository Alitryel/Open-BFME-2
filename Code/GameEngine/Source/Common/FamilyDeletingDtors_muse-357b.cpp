// cl: /MD
// ??_GCDownload@@QAEPAXI@Z @0x005E046F 28B: deleting dtor calls the rowed
// ??1CDownload@@QAE@XZ at 0x006C9730 then rowed operator delete 0x0002FD60
// on flag; chain-unlocked by the CDownload dtor landing.
// ??_GDownloadManager@@UAEPAXI@Z @0x005E0AF3 28B: slot 5 of vtable 0x00877944;
// calls the rowed ??1DownloadManager@@UAE@XZ at 0x005E0994 then rowed operator
// delete 0x0002FD60 on flag.
struct EmitVtableTag;

class CDownload
{
public:
	~CDownload();
};

void CDownload_Delete(CDownload *p) { delete p; }

// The table as DownloadManager.cpp (first in link order) has it: the five
// download-callback slots, the deleting dtor (slot 5), then downloadFile.
class AsciiString;
class DownloadManager
{
public:
	DownloadManager(EmitVtableTag *);
	virtual long OnError(int error);
	virtual long OnEnd();
	virtual long OnQueryResume();
	virtual long OnProgressUpdate(int bytesread, int totalsize, int timetaken, int timeleft);
	virtual long OnStatusUpdate(int status);
	virtual ~DownloadManager();
	virtual long downloadFile(AsciiString server, AsciiString username, AsciiString password, AsciiString file, AsciiString localfile, AsciiString regkey, bool tryResume);
};
// ?<DownloadManager::DownloadManager> absent-from-retail
DownloadManager::DownloadManager(EmitVtableTag *) {}

