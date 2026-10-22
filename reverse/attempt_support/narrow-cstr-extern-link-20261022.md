# Narrow cstr ownership: extern-template consumer trials

Inputs: BFME2 35861e85dc (sources unchanged from b1433f0f92), BFME1 37c3022de1ab944c7ffe536440d637dc8199091c, published legacy census 08160bc2c9 / 2026-10-22 17:08. Native cstr owner at RVA 0x9100 already links. No donor layout or identity inference was introduced.

Five consumer units still fail legacy linking solely on their nonretail narrow cstr constructor copy: BfmeNarrowRecord00079C23Ctor.cpp (87B), VersionBlockParserText.cpp (97B), PeerThreadNickError.cpp (394B), MainMenuUtils_hasWriteAccess.cpp (233B), stlport_money_put_long_double.cpp (184B). Byte lengths here are link_check measured, excluding some EH data.

Prior declaration-only attempts lose allocator escape information. New hypothesis: keep the STL template definition visible but suppress its emission through an extern template instantiation declaration. Trial 1 inserted after includes, before existing declaration-only specializations; trial 2 appended after all caller definitions. Both used exactly:

```cpp
namespace _STL { extern template basic_string<char, char_traits<char>, allocator<char> >::basic_string(const char*, const allocator<char>&); }
```

Both positions produce the same byte failures. Record constructor: second allocator home EBP-0D becomes EBP-0E. Version overloads: allocator EBP+0B becomes +0F / +13. Nick callback: allocator +0B becomes +0F and two-character buffer +0E becomes +12. hasWriteAccess: four allocator temporaries stop sharing EBP-0D and use -0D/-0E/-0F/-10. money_put: frame 4C becomes 50, shifting locale/string temporary homes and unwind code. Bodies largely retain lengths; pointer escape/temporary lifetime summaries, rather than helper byte identity alone, are the concrete prerequisite. Do not repeat extern-template positioning or declaration-only suppression without new evidence about preserving those summaries.

The exact originals remain the best candidates and were restored byte-for-byte. ./build.sh on all five restored units passes 19/19 functions, literals/imports/floats; no attempted source or generated-label change retained. Local logs build/link-seat-cstr-trial1.txt, trial2.txt and restored.txt contain complete diagnostics. No banked nonmatching candidate: this is a link-only attempt against already byte-exact bodies. t=12min, model=gpt-6.1-sol.
