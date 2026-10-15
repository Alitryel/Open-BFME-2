// ?rva0024004D@GameLogic@@QAEX_N@Z
// partial score=0.996 date=2026-10-15
// ?rva0024004D@GameLogic@@QAEX_N@Z
// Banked 0x0024004D attempt: unified diff against GameLogicInit.cpp at 49fb0dd9fe; git apply after stripping these comment lines.
// Residue: ONE byte - lea eax,[ebp-1] vs retail [ebp-4] for the empty functor (98.0 store schedule fixed: file-static float).
diff --git a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
index 5e285ce856..d4c5caba70 100644
--- a/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
+++ b/Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
@@ -1428,6 +1428,7 @@ public:
 	virtual void slot28();
 	void rva001DC5EC(void);
 	void reverse(AsciiString groupName);
+	void setGroup(AsciiString groupName, bool immidiate = false);
 };
 
 class Rva0023C7D2
@@ -5418,3 +5419,120 @@ void GameLogic::rva0024622F(bool dontCreate)
 		it->obj->rva00293E64(it->mapObj->getProperties());
 	}
 }
+
+// ?rva0024004D@GameLogic@@QAEX_N@Z @0x0024004D 247B (ebp frame without EH,
+// ret 4; next body 0x00240144). Called from the new-game pass 0x00248558.
+// Target evidence: unless +0x72 or +0x78 is set or the Apt window manager's
+// +0x31C is non-zero, TheTransitionHandler takes the "FadeWholeScreen"
+// group (rowed setGroup 0x001DC252) and waits (0x001DC5EC); GlobalData
+// +0xAF5 is cleared and 0x00376D49 runs; when TheDisplay's virtual +0x114
+// holds, the load screen at +0x120 is polled through its virtual +0x14 with
+// Sleep(5). In modes 2, 1 and 5 (+0x110) a timed operation is queued through
+// the rowed registry 0x003FE7E6 with a callback built by the holder
+// constructor 0x0023E8AC from an empty local functor and the id slot
+// 0x00E02EC4; the load screen's +0x0C flag is cleared, 98.0 goes to the
+// float at 0x00DFE788 and TheAudio's virtual +0xF0 gets (0.0, true).
+// Donor (semantic guide only): BFME 1 GameLogic.cpp startNewGame's closing
+// steps (fade-in transition, load-screen wait); names stay offset names.
+class Bfme5RefHolderA
+{
+public:
+	Bfme5RefHolderA(int unused);
+	void *m_bfmeNode;
+};
+
+struct Rva0024004DFunctor
+{
+};
+
+class Rva00211E75Callback : public Bfme5RefHolderA
+{
+public:
+	Rva00211E75Callback(const Rva0024004DFunctor &functor) : Bfme5RefHolderA((int)&functor) {}
+	Rva00211E75Callback(const Rva00211E75Callback &other);
+};
+
+bool Rva003FE7E6(Rva00211E75Callback callback, int *id);
+
+class Rva0024004DDisplayView
+{
+public:
+	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
+	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
+	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
+	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
+	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
+	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
+	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
+	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
+	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
+	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
+	virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
+	virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
+	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
+	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
+	virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
+	virtual void v3c(); virtual void v3d(); virtual void v3e(); virtual void v3f();
+	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
+	virtual void v44();
+	virtual bool v45(void);                                              // +0x114
+};
+
+class Rva0024004DLoadScreenView
+{
+public:
+	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
+	virtual void v04();
+	virtual bool v05(void);                                              // +0x14
+	char m_pad04[0xc - 0x4];
+	bool m_c;
+};
+
+class Rva0024004DAudioView
+{
+public:
+	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
+	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
+	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
+	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
+	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
+	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
+	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
+	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
+	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
+	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
+	virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
+	virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
+	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
+	virtual void v34(); virtual void v35(); virtual void v36(); virtual void v37();
+	virtual void v38(); virtual void v39(); virtual void v3a(); virtual void v3b();
+	virtual void v3c(float value, bool flag);                            // +0xF0
+};
+
+extern int g_00E02EC4;
+static float g_00DFE788;
+
+
+void GameLogic::rva0024004D(bool loadingSaveGame)
+{
+	if (!m_72 && !m_78 && !g_bfmeAptWindowManager->m_31c) {
+		TheTransitionHandler->setGroup(AsciiString("FadeWholeScreen"));
+		TheTransitionHandler->rva001DC5EC();
+	}
+	TheWritableGlobalData->m_af5 = false;
+	rva00376D49();
+
+	if (((Rva0024004DDisplayView *)TheDisplay)->v45() && m_120) {
+		while (!((Rva0024004DLoadScreenView *)m_120)->v05())
+			Sleep(5);
+	}
+
+	if (m_110 == 2 || m_110 == 1 || m_110 == 5) {
+		Rva0024004DFunctor functor;
+		Rva003FE7E6(Rva00211E75Callback(functor), &g_00E02EC4);
+		if (m_120)
+			((Rva0024004DLoadScreenView *)m_120)->m_c = false;
+		g_00DFE788 = 98.0f;
+		((Rva0024004DAudioView *)TheAudio)->v3c(0.0f, true);
+	}
+}
