# Image map helper ownership repair

Against the 2967eab33e census (2026-10-18 08:17; retail-truth-2),
current objects at 80676908e7 expose a strong 69 B ImageSubscriptMap subscript
in stlport_map_uint_image_insert.cpp and an identical SELECT_ANY copy needed
by HostValidateColorsRva004422DDFarm.cpp. The strong/ANY pair conflicts.
Both complete bodies have digest 2474c8f7c269 including all relocations.

Rehome the existing row to the already emitted inline consumer copy and remove
the strong definition. Keep the independently rowed 20 B tree lower_bound
explicitly instantiated; it previously emitted through the subscript body.
This preserves the existing name, address and identity evidence. It adds no
alias, pin, function, layout claim, or unique authored byte.

Paired current-object LEGACY previews: both units blocked before; afterwards
the STL unit links its remaining 613 B. The consumer's 579 nonpadding bytes
remain blocked by five allocator/tree COMDAT conflicts and a selected allocator
conflict. No self-strict or closed-strict link-closure gain is asserted.

Both units pass strict-current preparation before and after, 7/7 rows total.
The consumer's new 69 B row also passed add_match's normal byte gate. Strings,
floats and imports have no unchecked references. Source claims and declared
body checks pass. The ordinary STL unit gate verifies its other five rows.

The STL source was unchanged from the census to the pre-repair HEAD. All 25
retained COMDAT byte-and-relocation digests are unchanged; no new or changed
COMDAT appears. Eight definitions disappear, including the strong wrapper and
its now-unused inline helpers. The consumer source and object are unchanged.
The first removal trial dropped lower_bound; explicit instantiation restored
its whole native body before acceptance.

The same commit records an independent blocked vector<unsigned> constructor
trial, fully reverted with restored 9/9 strict-current rows. Declaration-only
suppression redirects partial-inline calls from base ctor 211E58 to the real
vector ctor 25100, while forceinline changes callers. The name already owns
25100, so it cannot be fold-pinned to the base constructor.
