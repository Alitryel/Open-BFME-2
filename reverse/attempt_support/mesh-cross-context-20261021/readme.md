# Mesh deformation: named cross product improves the bank

Target: get_deformed_vertices(Vector3 *, const HTreeClass *), native
0016B680..0016BF3D, 2237 bytes ending RET8. The complete meshgeometry.cpp
owner, existing bank, pertinent w2b/w7/w8/w9/w10/w11 evidence and the paired
normal-producing overload's bank/r53/r57/r60/r61 log were reviewed.
No production source, shared header, pin or matched row changes here.

The best candidate retains the signed vertex count returned by the existing
accessor and names the actual cross-product component
`cx = Rotation.Y*v->Z - v->Y*Rotation.Z` before forming the quaternion
product's x component. Both operations already existed; there is no dummy
effect, volatile access or added mathematical term. Signed count alone
regresses the blend. Together they remove the matrix product operand swap
without that regression: the old M2/B8/S8 becomes M0/B8/S8, still 2237 bytes.
The matrix prefix is exact; blend and single-bone multiplication/evaluation
order remain different. A y or z cross component, or the true quaternion dot
product, gives the same best output with the signed count.

The measured byte score is explicitly defined in verification.json: identical
mnemonic-aligned instruction bytes after resolving relocations and masking
jump displacements, divided by 2237. It improves 2141/2237 to 2150/2237.
This is not comparable to the historical bank's differently defined 0.98674.
The previous source is retained verbatim. Neither score is a byte gate.

Investigations included real preceding-function context, nine blend product/
row models, every subset of the four problematic blend products, five row
helper forms, 96 real helper parameter/count combinations, named scalar
cross/dot/component models, cross/dot subsets, and single/pair parenthesis
changes around the improved body. Complete trial identifiers, input hashes,
actual COFF extents, unresolved-reference counts and region results are in
trials.tsv. No exact result was obtained. Earlier inert-local/count and flag
searches were reassessed, not repeated.

The ArmyDefinition predecessor-state finding was tested using the real owner
and its existing Scale and Compute_Bounds definitions, including a diagnostic
framed bounds method. With the bank's original WWMath providers retained,
these target outputs are byte-identical to the old bank. The existing 652-byte
Scale body and ordinary 239-byte bounds body remain exact in those controls;
the framed bounds diagnostic is 242 bytes and is not an admitted recovery.
With the owner's link-view math headers selected first, the candidate instead
emits 2305 bytes; moving the preceding source definitions still changes
nothing. COFF section ordering does not prove c2 pass/emission order or the
value of its global availability array. These controls therefore reject the
tested arrangements, not every conceivable inherited-state explanation.
Existing Scale volatile operations were copied unchanged into ignored
diagnostics only; none is added to production or the improved bank.

Replay at BFME2 80be2829c04 with verified BFME1 cea1e9734dc0:
context-replay, products-replay (default blend forms, then --tpa-only and
--subsets-only), row-order-replay, parens-replay (default, then --pairs), and
audit-replay. The .py.txt drivers are evidence; copy them to the named ignored
build paths before running. The owner is read from that fixed git revision
and the prior bank from this handoff. The dependency receipt retains all
21 header fingerprints and compiler-command fingerprint for the improved
ordinary compile. Source flags remain SSE/G7/DNDEBUG/MD with the existing
WWMath, WWLib and WWDebug includes. /Oy- is diagnostic only.

At the starting revision the paired normal-producing bank at 0016BF40 had
exact single-bone loops and a different matrix-X/normal-row residue. During
publication, the rebase to 27bbe7c66bf brought its exact 2960-byte recovery
f3ebce7f5ed and its r62 handoff. That entire new owner was read. The prior
follow-up in 35ab82a2d25 tested the old 80-differing-byte bank. A further 111
controls tested the improved 74-differing-byte cross-component base: all 105
nonempty row/column subsets of tm1.Row -> tm1[] and five real bone-pointer/
reference arrangements inspired by the newly landed source. Indexing retains
or worsens the result; the pointer/reference arrangements emit 2251 bytes
and regress. There is no further improvement or exact result.

Those follow-up inputs and full extents are in sibling-trials.tsv; the frozen
input is cross-base.cpp.txt. Copy sibling-replay to the named ignored path,
then run it and audit-replay as above. verification.json distinguishes the
439 initial diagnostics from the 111 follow-up controls (550 total). The
existing improved bank is retained, not replaced by a worse transfer. No
donor identity or layout is newly asserted from byte similarity. gpt-6.1-sol.
