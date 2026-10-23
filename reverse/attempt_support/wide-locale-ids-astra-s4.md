# Wide monetary facet-ID definitions

The byte-verified use_facet<moneypunct<wchar_t,false>> body at RVA
0x00019980 pushes VA 0x00DA6208; its true counterpart at 0x00019990 pushes
VA 0x00DA6204. Both call locale::_M_use_facet at 0x00007190. Retail's
four-byte data at those addresses is respectively 24 and 23. These target
facts establish both symbol identities and initializer values independently
of neighboring facet IDs.

Add the two definitions to the existing STLport locale-ID provider beside
its narrow monetary IDs. COFF inspection confirms external definitions
with initialized bytes 17000000 and 18000000 at .data+0x20/+0x24.
The existing 241-byte _Stl_loc_init_facets row still passes the full byte gate.
The paired local link preview resolves both previously undefined IDs in
money_put_wide and wide_money_get_string; their other blockers remain,
so this prerequisite repair claims zero additional linked code bytes.
Index: 491a8b3d87 (2026-10-23 03:12 UTC); no new census or runtime test.
No pins, aliases, ledger rows, or shared headers changed.

model=gpt-6-astra seat=s4
