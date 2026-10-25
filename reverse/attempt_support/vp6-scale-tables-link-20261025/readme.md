# VP6 scaler coefficient ownership, 2026-10-25

model=gpt-6 lane=R budget=30m. Production base d0c913e6dde06ee8ff4e7cdfa655c4aa0a2889f5.
The six committed clean-room specifications and retail bytes are the only decoder
sources of evidence; no external decoder source or BFME1 decoder donor is read.

The completed authoritative a7637e3b221cc7af51ce45eb036048a8d46c3f57 snapshot
leaves all six MMX scalers self-failing on data-back mappings. Each horizontal
scaler has a private rounding array; both last-band files and both routines in
VerticalBandInterpMmx.cpp have private five-array copies. Retail's 64 named DIR32
references independently identify one address for each of the five coefficients:
RVA 7D9910/20/30/40/50, holding four unsigned 16-bit lanes of 51/102/154/205/128.
The full logical allocation is eight bytes each. The following eight zero bytes
are native alignment padding, excluded from the ownership rows and arrays.

The existing VerticalBandInterpMmx.cpp now owns five external C-linkage arrays,
using names already present in the ledger. Four other units declare and use
those owners; the second routine in the owner no longer has another private
copy. No instruction, calling convention, arithmetic, loop, function identity,
source path, header, pin, alias, hatch or verifier changes. The repair reconciles
native data identity rather than asserting the original C++ source spelling.

Before and after normal controls pass 6/6 bodies, 1,739 bytes in five sources.
The after control also verifies five eight-byte data rows. Native proof confirms
all 64 references keep the same instruction offsets, addends and retail targets;
private definition counts 4/4/4/4/6 become exactly one external definition each.
Control and repair process exits are both zero. This adds zero matched function
coverage. The source result is recorded once per body with add_match.

A controlled authoritative link measurement is pending. No prospective gain or
current census headline change is claimed. The comparison will hold the completed
a7637e3b22 snapshot constant except for these five sources and five data rows;
all five original source blobs have already been proved equal to that snapshot.
