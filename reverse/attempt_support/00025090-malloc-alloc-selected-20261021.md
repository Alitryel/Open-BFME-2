# __malloc_alloc<0>::allocate (0x00025090): wrong copy selected by link order

Census 2026-10-21 (17918792f6): stlport_vector_pair.cpp (570 B) and
STLMallocAlloc0Allocate.cpp (48 B) fail only on `selected
?allocate@?$__malloc_alloc@$0A@@_STL@@SAPAXI@Z` (the kept copy is not retail's).

Copies (census index): stlport_wide_money_get_string.obj 93e207f06ed2 (wrong, /Ob1,
calls _malloc), STLMallocAlloc0Allocate.obj 2ffb6ea3f52c (retail, /Od, __imp__malloc),
Rva002829BDSphereMerge.obj 235189b8d9d0 (wrong). Link order is by lowest row RVA, so
money_get (0x00012190) precedes 0x00025090 and link.exe keeps its copy.

Cause (target evidence + scratch compiles): nothing in money_get references the copy;
MSVC 7.1 emits every odr-used inline function. A 5-line TU calling wstring::append with
money_get's flags emits the same COMDAT. In money_get the odr-use comes through
allocator<char/wchar_t>::allocate (via append in the _M_assign_dispatch specialization).
Retail's money_get .text precedes 0x25090 yet retail selected the /Od body, so retail's
money_get object did not emit an /Ob1 copy first.

Tried and ruled out (scratch only, build/mm):
- moving the _M_assign_dispatch definition to the end of the TU: still emitted
- making that specialization inline, __declspec(noinline), or both: still emitted
- a __forceinline explicit specialization of __malloc_alloc<0>::allocate: still emitted
- `extern template class __malloc_alloc<0>`: still emitted
- member `extern template`: suppressed, but stops inlining (do_get 2824 -> 2904 B)

Verified recipe (scratch compile; not landed because the file was claimed by another seat):
explicit specializations of allocator<char>::allocate and allocator<wchar_t>::allocate
that call malloc and _S_oom_malloc directly. _S_oom_malloc is reached through the
explicit-instantiation access idiom, since access is not checked in
explicit-instantiation arguments.

Result of the recipe:
- __malloc_alloc<0>::allocate is no longer emitted;
- do_get (2824 B) and its funclets are byte-identical;
- the only other COMDATs that change (append<PAG> fwd, _M_insert_aux, reserve, the
  allocator/proxy allocate copies) were already losing or non-first copies;
- one new unreferenced COMDAT, _MoneyOom (6 B), has no retail address.

Still to check when landing: ./build.sh on the file, and link_check on money_get,
stlport_vector_pair and STLMallocAlloc0Allocate together.

Patch:

```diff
--- a/Code/Libraries/Source/WWVegas/WWLib/stlport_wide_money_get_string.cpp
+++ b/Code/Libraries/Source/WWVegas/WWLib/stlport_wide_money_get_string.cpp
@@ -83,6 +83,26 @@
 // opaque preserves the retail sbumpc call inside inline iterator increment.
 #define _STLP_INTERNAL_STREAMBUF
 #include <memory>
+namespace _STL {
+// Retail's money_get never names __malloc_alloc<0>::allocate: its allocator
+// bodies call malloc and the out-of-memory hook directly.
+typedef void *(_STLP_CALL *_MoneyOomFn)(size_t);
+struct _MoneyOomTag { friend _MoneyOomFn _MoneyOom(_MoneyOomTag); };
+template <_MoneyOomFn _Fn> struct _MoneyOomRef { friend _MoneyOomFn _MoneyOom(_MoneyOomTag) { return _Fn; } };
+template struct _MoneyOomRef<&__malloc_alloc<0>::_S_oom_malloc>;
+template <> inline char *allocator<char>::allocate(size_type __n, const void *) const {
+  if (__n == 0) return 0;
+  void *__result = malloc(__n);
+  if (0 == __result) __result = _MoneyOom(_MoneyOomTag())(__n);
+  return (char *)__result;
+}
+template <> inline wchar_t *allocator<wchar_t>::allocate(size_type __n, const void *) const {
+  if (__n == 0) return 0;
+  void *__result = malloc(__n * sizeof(wchar_t));
+  if (0 == __result) __result = _MoneyOom(_MoneyOomTag())(__n * sizeof(wchar_t));
+  return (wchar_t *)__result;
+}
+}
 enum { _MONEY_LEAKS_CHECK = 0 };
 #include <string>
 namespace _STL {
```
