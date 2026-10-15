# Floor texture-copy blocker handoff

At source revision 9802502188, current-object checks against census 28269d8e8d
(2026-10-15 09:31) confirm the sole Rva000E473F.cpp blocker is
??0?$RefCountPtr@VTextureClass@@@@QAE@ABV0@@Z. This specialization forwards
to the verified AssetReference copy at 000424BB, whereas other same-name
copies implement incompatible texture reference counting. Native drawFloors
uses the AssetReference copy; treating every RefCountPtr specialization as
the ordinary texture pointer would be unsupported.

Two bounded trials, __forceinline and removing the explicit wrapper in favor
of implicit memberwise copying, both pass 15/15 byte rows but still emit the
same 19-byte COMDAT 56ff7424088bf1e8000000008bc65ec20400, with the
AssetReference copy relocation at +8. Neither removes the conflict. Restored
the complete original source, recorded blocked via re_log.py and released
the file claim. No failed reconstruction remains in Code/.

DebugStatisticsRecordTextureEnd.cpp, the other sole-blocker unit in the old
ranking, already emits no copy constructor and LINKS with its current object
(997 authored bytes). Its strict-current preparation passed 2/2 byte rows.
No change was needed and its file claim was released. This existing result
is not credited to this session. Further floor work needs evidence-backed
handle ABI reconciliation; fake imports or another alias are not a repair.
Original sources/objects and trial logs remain in ignored
build/texture-copy-link-20261015. The blocker is also in re_attempts.log.
