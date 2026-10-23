# Captured-bone allocation-owner trial, 2026-10-22

Inputs: BFME2 3135430de3, verified BFME1 37c3022de1a, published index
08160bc2c9 (17:08). The earlier POD36 erase repair removes a wrong sized-base
constructor, leaving the 175-byte captured-bone copy's base callee unresolved.
An exact 86-byte allocation constructor at native 162800 is already rowed in
StlVectorRva00162800.cpp under Rva00162800Record. Both strides are independently
36; this establishes allocation width, not a shared recovered element identity.

Baseline explicit-current preview of captured copy, erase unit, and actual
base owner: 2/3 units link, 208 bytes (122 erase + 86 base); copy unresolved.
The preserved patch derives the copy view from the actual rowed base, casts
its storage pointers to the independently recovered captured-bone type, and
passes the empty allocator by a view cast. The base call now targets its real
owner, but cl eliminates the original allocator-getter call at native 166125.
The loop remains instruction-identical except the removed alignment nop;
prologue/count evaluation changes because the hidden return temporary is no
longer consumed as an allocator of its original type. A second careful trial
marks the existing getter noinline: identical failure. Two failed byte gates;
no further trial or linked-gain claim. Original source restored and build.sh
passes 1/1 plus literal/import checks.

Next work needs an inline-preserving empty-allocator conversion or an explicit
call to the existing native getter (rowed wide-string get_allocator at 1627F0),
while retaining the hidden return pointer and call order. Do not simply repeat
the base-type substitution or noinline trial. Original full 175-byte source
remains in Code; patch is diagnostic evidence only. No pins/aliases/flags or
ledger rows were changed. Legacy preview only, no strict closure claim.
