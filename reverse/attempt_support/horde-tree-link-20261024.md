# HordeContain empty-tree constructor providers, 2026-10-24

Inputs: BFME2 4d4a0a207e, BFME1 32774ab03393709a7f14331ba8d98d281a55ffd9,
stock MSVC7.1 through build.sh, unchanged original flags and headers.
Published index: 268f876e3b, retail-truth-4.

The current HordeContain constructor unit has only two unresolved names:
Rva0046A915's constructor and Rva0046AB7D's constructor. Existing destructor
and clear providers establish their owning tree lifetimes. Native HordeContain
initializes those owners at +258 and +1A0, using distinct 25-byte constructor
bodies. Its own 624-byte body and complete EH graph already match.

| Owner | Constructor | Tree constructor | Base constructor | Header allocation |
| --- | --- | --- | --- | --- |
| Rva0046A915 | 33C432, 25B | 1F068F, 42B | 1F0534, 36B | 24 bytes |
| Rva0046AB7D | 242F01, 25B | 46AB53, 42B | 33B758, 36B | 36 bytes |

Final identity-check follow-up also supplies the ObjectID-set owner
Rva002EE9B7 at +170: constructor D3A71 (25B), tree 2F0BF4 (42B), 20-byte
node allocation. The only pre-existing definition was ChatWindowsLan.cpp's
49-byte EH wrapper around set<int> construction. That wrapper runs correctly
when inlined into its own caller, but is wrong as HordeContain's D3A71 outline.
The code identity hook exposed this after the initial legacy preview passed.
HordeContain precedes ChatWindowsLan in native link order (15147 versus 20684
in the published index). The new genuine 25-byte definition supplies the kept
body; the later wrapper is discarded under the existing retail-truth rules.
ChatWindowsLan source is unchanged. The set's construction view preserves
the existing ObjectID role and external owner destructor.

Both base constructors call the existing allocator proxy at 14F3C4 and
game allocation at 307F0. Each tree constructor then clears count, root and
color and points both extrema at the allocated header. Their complete native
call chains, pointer stores, distinct allocation sizes and parent field offsets
are target facts.

BFME1 HordeContainConstructor.cpp at the verified pointer supplies the semantic
reference: map<int, Gen_t_00223550_p4pod> and map<int,
Gen_t_0023abb0_p16cd>. BFME2's construction views retain the int-key hypothesis
and four/sixteen-byte mapped extents while explicitly leaving original payload
identities unresolved. The target allocations independently support the total
node sizes; they alone do not prove key semantics. Only initialization uses
these views. The established Rva owner destructors remain external and keep
their existing real cleanup implementations; no opaque value is copied or
destroyed by newly invented element behavior.

The two owner constructors use ordinary STLport comparator/allocator construction
over twelve-byte tree members. noinline retains native parent calls; inline
keeps their emitted definitions foldable. Both 25-byte bodies pass add_match
with explicit existing ICF owners: map<int,void*> and map<long,LadderPref>.
The three new template constructor pins were admitted by pin_admission
with fold-proof=HordeContainCtor.cpp. It proved the entire emitted bodies and
recursive allocator/base/proxy relocations, not just a masked placement.
Consistency prechecks found neither new template name previously pinned;
the post-admission global consistency check passes.

The pin-admission tool also updated hatch_baseline.tsv: three admitted pin counts
and its automatic stale-count shrink/expired admission normalization. These are
generated admission records; no verifier code or gate rule changes. The commit
includes the required Verifier-Change trailer for this protected data file.

Paired baseline and candidate used identical constructor/destructor providers:

* Before: only the destructor unit links, 348 bytes; constructor has the two
  unresolved names above. Original byte gate passes 10/10.
* After: both units link, 985 bytes: **net +637 unique linked bytes**.
* Candidate byte gate passes 13/13, all references pass, full parent EH EXACT,
  no missing objects or baseline EH findings. find_declared_unmatched and
  global pin consistency pass.
* Final code identity check: 13 rows, zero new findings. Including unchanged
  ChatWindowsLan gives 1,225 -> 1,862 bytes; all three units link and the net
  gain remains 637. The constructor outline correction adds no extra bytes.

The three new constructor rows are zero-byte ICF aliases. They add no authored
coverage and do not inflate the gain by their seventy-five shared bytes. Each of those
rows has a distinct address and is a whole-body relocation twin of its owner.
This is a scoped legacy linking prediction, not a new full-link census or a
closed-strict measurement. Reproduction logs live in ignored
build/link-horde-20261024/{before,after}-{byte,link}.txt and after-eh.txt.
