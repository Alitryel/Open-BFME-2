// ??1MilesAudioManager@@UAE@XZ
// partial score=0.6 date=2026-10-15
// Bank for ??1MilesAudioManager@@UAE@XZ 0x00060FE2 (967B). Apply on top of
// Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManager.cpp (after the 0x0005CF5F ctor landing).
// The class-view edits are the unified diff below; the destructor body is appended at the end of the TU.
#if 0
--- MilesAudioManager.cpp
+++ MilesAudioManager.cpp (draft)
@@ -1040,7 +1040,12 @@
 // Native base constructor 0x0005107D: SubsystemInterface 0x001B4E63, then
 // the Snapshot and the abstract base's own vftables (BC5148/BC5138) -- Zero
 // Hour's AudioManager, which MilesAudioManager derives from.
-class AudioManager : public SubsystemInterface, public Snapshot {
+// Its destructor is the rowed 0x0005109D (address-named class there).
+class Rva005109D : public SubsystemInterface, public Snapshot {
+public:
+    virtual ~Rva005109D();
+};
+class AudioManager : public Rva005109D {
 public:
     AudioManager();
 };
@@ -1053,7 +1058,9 @@
 // ctor 0x0005A2E6 / dtor 0x0005925E; methods use the GlobalVolumeData view.
 class Rva006ABC60 { public: Rva006ABC60(); ~Rva006ABC60(); int m_myViewFocus; private: char m_body[0x1C0]; };
 // The manager's mutex at +0x9D4, built by the rowed Mutex(1, 0, 0) 0x00040F1E.
-class Mutex { public: Mutex(int, const char *, void *); ~Mutex(); private: void *m_handle; int m_04; };
+// Its virtual destructor is the rowed 0x00040EDB (address-named class there).
+class Rva0040EDB { public: virtual ~Rva0040EDB(); private: void *m_handle; };
+class Mutex : public Rva0040EDB { public: Mutex(int, const char *, void *); };
 // Objects the constructor allocates: 0x204-byte settings (ctor 0x00041589)
 // and the 0xF4-byte record at +0x14 (ctor 0x001ED70C).
 // The +0xB90 stream owner: zero-initialized in place and destroyed on unwind
@@ -1066,15 +1073,19 @@
 private:
     void *m_owner;
 };
-class Rva000416E7 { public: Rva000416E7(); private: char m_body[0x204]; };
-class Rva001ED70C { public: Rva001ED70C(); private: char m_body[0xF4]; };
+class Rva000416E7 { public: Rva000416E7(); virtual ~Rva000416E7(); private: char m_body[0x200]; };
+class Rva001ED70C { public: Rva001ED70C(); ~Rva001ED70C(); private: char m_body[0xF4]; };
 class Image;
 typedef _STL::map<unsigned int, Image *> Rva0005B256HandleMap;
+// +0xB78: built by the folded hash constructor like the handle maps but
+// destroyed by its own 0x00057AEE, so a distinct table type.
+typedef _STL::hash_map<unsigned int, Image *> Rva00056DA2Map;
 extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64 *);
 
 class MilesAudioManager : public AudioManager {
 public:
     MilesAudioManager();
+    virtual ~MilesAudioManager();
     // Virtual slots 0..74 are not named here; slot 75 (+0x12C) looks an
     // event info up by name.
     virtual void init(); virtual void slot02(); virtual void slot03(); virtual void slot04();
@@ -1342,7 +1353,7 @@
     unsigned int m_nextHandle;           // +0xD0, next playing handle (0x0005B256)
     // Zero Hour's inline AudioManager::allocateNewHandle.
     unsigned int allocateNewHandle(void) { return m_nextHandle++; }
-    _STL::vector<int> m_atD4;          // +0xD4
+    _STL::vector<OpaqueRefElement4> m_atD4;  // +0xD4 (destroyed by 0x00057994)
     QueuedAudioEvents m_queuedEvents[3];  // +0xE0, per view type (0x60123)
     // Native handle-map operations establish these two 20-byte tables.
     MilesKeyAliases m_handleAliases;       // +0x104
@@ -1398,7 +1409,7 @@
     _STL::vector<AudioTriggerArea> m_triggerAreas;  // +0xB54, scanned by 0x55C5D
     _STL::vector<AudioTriggerAreaSave> m_savedTriggerAreas;  // +0xB60, resolved by loadPostProcess
     Rva0005B256HandleMap atB6C;           // +0xB6C, cleared through the rowed 0x00054B9A
-    MilesHandleMap atB78;           // +0xB78, cleared through the rowed 0x00056DA2
+    Rva00056DA2Map atB78;           // +0xB78, cleared through the rowed 0x00056DA2
     AudioFileCache *m_audioFileCache;    // +0xB8C (WorldBuilder requestFile receiver)
     MilesStreamOwnerRef m_atB90;         // +0xB90, handed to the stream opener 0x000A8D0B
     PlayingAudioList m_completedAudio;   // +0xB94, filled by the EOS handlers
@@ -6596,3 +6607,49 @@
         m_physicalHandles.insert(MilesPhysicalHandles::value_type(physical, logical));
     }
 }
+
+// ??1MilesAudioManager@@UAE@XZ @0x00060FE2 967B (native 0x00060FE2..
+// 0x000613A9; WB 0x00780FC0 names it). Zero Hour's ~MilesAudioManager is the
+// semantic guide: stop the loop-buffer thread, close the device, clear
+// TheAudio, drain the completed list and both request containers, then free
+// the loop buffers, the file cache, the misc record and the settings.
+extern "C" __declspec(dllimport) unsigned long __stdcall WaitForSingleObject(void *handle, unsigned long ms);
+class Rva000A77B3 { public: void rva000A77B3(void); };
+class Rva00A897D { public: void rva000A89C1(void); };
+MilesAudioManager::~MilesAudioManager()
+{
+    m_atBE0 = true;
+    if (m_audioFileCache)
+        reinterpret_cast<Rva000A77B3 *>(m_audioFileCache)->rva000A77B3();
+    if (m_atB90)
+        reinterpret_cast<Rva00A897D *>((void *)m_atB90)->rva000A89C1();
+    if (m_loopBufferThread) {
+        WaitForSingleObject(m_loopBufferThread, (unsigned long)-1);
+        m_loopBufferThread = 0;
+    }
+    rva0006047C();
+    if (TheAudio == this)
+        TheAudio = 0;
+    m_completedAudio.clear();
+    while (!m_audioRequests.empty()) {
+        Rva00051107AudioRequest *request = m_audioRequests.back();
+        m_audioRequests.pop_back();
+        deleteAudioRequest(request);
+    }
+    Rva00051107AudioRequestSet::iterator it = m_requestSet.begin();
+    while (it != m_requestSet.end()) {
+        Rva00051107AudioRequest *request = *it;
+        m_requestSet.erase(it);
+        it = m_requestSet.begin();
+        deleteAudioRequest(request);
+    }
+    m_numLoopBuffers = 0;
+    delete[] m_loopBuffers;
+    delete m_audioFileCache;
+    delete m_at14;
+    m_at14 = 0;
+    ::delete reinterpret_cast<Rva000416E7 *>(m_audioSettings);
+    m_audioSettings = 0;
+    delete m_subTitleWindow;
+    m_subTitleWindow = 0;
+}
#endif
