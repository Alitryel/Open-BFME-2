# Wide assignment append binding

The 102-byte wide _M_assign_dispatch at RVA 0x130A0 copies the existing
prefix and appends the remaining source range without modifying it. Its
private append declaration formerly instantiated the mutable-pointer name;
all five copies of that name in the published index are proven wrong. The
rowed const-pointer append at 0x13160 implements exactly this read-only
range operation. Passing const pointers to the existing wrapper selects it.

The complete 102 raw bytes are unchanged. Of three REL32 relocations, only
the append call at +91 changes its name, PAG -> PBG; both target the same
retail 0x13160. The two erase calls and the provider are unchanged. This
reuses the provider's real row name without a pin, alias or thunk.
proof.json records all relocations and COMDAT digests before/after.

Paired strict-current two-unit preview, same census c2c5ac8c27, index SHA256
90bd1bed6c06692963e0e6e96411614d502ca33f48b3e26d5338daaae99cf761:
assignment 0 -> 102 legacy linked bytes; append remains 241 -> 241. Both
units now pass the local preview. This is not a self-strict or closed-strict
link measurement. Strict preparation and ./build.sh verify 2/2 complete
rows; new-variants, class/frozen, data enforce/converged all pass; no EH rows
apply. Scratch inputs and logs: build/wide-assign-link-20261018/.

This follows the same target-supported STL helper binding repair as the
preceding wide insertion repair; the source range's read-only contract is
established by the provider body, not inferred solely from equal bytes.
No census, index or status artifact is changed.
