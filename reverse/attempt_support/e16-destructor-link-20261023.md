# BfmeE16 vector cleanup link blocker

Input: BFME2 6ae1fde8d5; published census 0fa62a2841, 2026-10-22 23:07; verified BFME1 f890413e75. BFME1 linking history reviewed (including 908413c254); no applicable vector-destructor repair found. No donor layout or identity imported.

The rowed vector<BfmeE16> destructor at 0x0052D1CD is 63 bytes in Rva0056616BCopy.cpp, whose nontrivial storage cleanup differs from these consumers' POD-buffer inline cleanup and emitted outline. Thirteen consumers totaling 130 matched rows passed strict reusable self preparation before editing. Their sole legacy blocker is the competing destructor. This does not establish a closed-strict result.

Two pilots: AIUnitBuilderRva00598D7A.cpp and Rva00082EF5Ctor.cpp. Added an explicit destructor specialization with the vendor body `_Destroy(this->_M_start, this->_M_finish)` and `__declspec(dllimport) __forceinline`, following the existing LightPointSystem.cpp pattern. The AI unit keeps its matched bytes but now references unresolved `__imp_??1?$vector@UBfmeE16...`; the behavior unit additionally changes native destructor 0x00081C7F (96 B) from inline null-check/free to an out-of-line destructor call and loses its EH parent match. Link preview confirms the unresolved import and wrong-selected parent. This does not fix the earlier declaration-only/inlining wall.

Both source trials were restored. No repair or linked-byte gain claimed. Do not repeat imported/declaration-only suppression without a way to preserve inline cleanup and mandatory EH cleanup references. The source snapshots and logs are scratch under build/link-seat-20261023 (e16-pilot-build.txt, e16-pilot-link.txt); the tested insertion above is the complete experiment. No banked nonmatching source is needed.
