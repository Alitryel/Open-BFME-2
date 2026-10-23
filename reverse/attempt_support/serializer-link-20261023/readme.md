# Serializer link prerequisite, 2026-10-23

At BFME 2 2bb4ace602, published retail-truth-4 index 456ce161c5,
Rva00427FB2Serialize.cpp remains 0/341 B linked. Current paired previews also
included stlport_narrow_string_substring_ctor.cpp, stlport_narrow_money_put_string.cpp
and stlport_money_put.cpp: all four remain blocked.

The attached patch binds both stream str() calls to the already rowed
Rva006026E0::get at 0x6027F0. Reversing the operands of pointer addition,
count + pointer, preserves the original call order and all 324 parent bytes
under the source flags (MSVC 7.1, O1/G7/SSE/EHsc/MD). Explicit count/end locals
instead produced 328 bytes and changed allocator-temporary setup. No new pin
or identity is proposed. The patch is diagnostic evidence, not landed code.

Remaining prerequisite: the link selects a non-retail const-char range
constructor at 0x2A590 from the earlier narrow money formatter, then the
money_put explicit class instantiation. The exact 125-byte owner is
stlport_narrow_string_substring_ctor.cpp. Import-forceinline on the formatter's
range constructor changes its 2802-byte body and makes one existing unwind
mapping ambiguous. Declaring money_put's string do_put specialization only
also removes four rowed helper definitions: fill_n, pos_format and both
use_facet<moneypunct<char>> instantiations. Those experiments were restored.
Further work needs to preserve formatter inlining/EH and helper emission;
changing the serializer alone has no measured linked-byte gain.

Local diagnostics: build/link-repair-20261023/serializer-{trial,trial2}.log,
serializer-paired-before.log, money-gate.log. Input donor checkout
21ef97bd08952c60197cc69c79fcc8dc383e9332; its headers are unchanged from the
previous verified 138757e9 pointer. No live Code candidate remains.
