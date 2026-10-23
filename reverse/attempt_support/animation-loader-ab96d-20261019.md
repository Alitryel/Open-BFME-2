# Animation loader AB96D: the caller's nonthrowing contract

Recovered the full native 194-byte range AB96D..ABA2F, ending in RET0.
WB8A63F0 supplies the w3dLoadAnimation lead. The native allocation size 30h,
owned AB910 constructor/AB956 loader pipeline, `%s.const` formatting, complete
file read and final dispatch establish the target operation and boundaries.
The retained function and neutral owner type names do not claim original names.

## Compiler finding

The no-EH bank emitted 191 bytes, missing `mov [ebp-0Ch],esp` before constructing
the outgoing by-value handle. EH-enabled compilation emits that save but also
installs an EH frame absent from native. Declaring the loader itself `throw()`
retains the save and elides the frame: the complete 194 bytes match. Earlier
controls marking all individual callees nonthrowing do not produce that result.
This establishes the source/compiler behavior, not the original author's exact
annotation or the compiler's internal reason. Absence of an EH frame alone is
not enough evidence to apply this recipe elsewhere.

The old animation-focus diagnostic saved only a target-sized 194-byte prefix
for longer candidates. Its `all_nothrow` length was not the actual function
extent: re-reading the complete object symbol measures 219 bytes. New controls
record complete symbol sizes. Never treat a patched comparison window's length
as the compiled function size.

The farm bank's equal-arm data ternary is removed. A plain named `char *data`
local gives native's ECX preload; passing the member directly folds the load
into the push and emits 193 bytes. The exact source has no dummy condition,
volatile home or assembly. It uses the unchanged canonical AsciiString header
with its existing BFME_ASCII_DTOR_DECL switch and the established private EAX
openFile helper. Its local helper copy also independently matches all 61 bytes;
the already owned helper is not claimed a second time.

## Ownership and integration

Removed the bank's reinterpret-cast function-pointer dispatch. Rva00893030 now
takes the existing four-byte BfmeRefVGO ownership view directly. Its manager
still takes the existing Rva006D07E0Key view; a force-inlined explicit converting
constructor copies the +0 pointer and performs the same acquire. Both existing
views use the same decrement/drop operations. The incoming parameter's release
and outgoing acquisition remain in the native order. The provider's complete
132-byte body and EH metadata independently remain exact, as does its 10-byte
handler; their ledger names are reconciled, not duplicated or repinned.

Two reset words at VA DE6164/DE6168 are proven by native stores. Their eight
initial retail bytes are zero; the new definitions preserve those initializers.
Their g_aptConstResetState0/1 names describe observed writes, not recovered
original symbols. No shared header, pin, hatch baseline or regional compiler
override changed. The new loader uses EHsc/Ob0 and its native region defaults.

All same-function verdicts and the saved prior animation-focus controls were
read before retrying. Inputs: BFME2 8a0ac377090fb72e2fed9405891ece5a5f7e2bca,
BFME1 a2c8039e61ad4dfb20c095d8eafe048248d31f25, MSVC 13.10.3077. Local
replay sources and assembly are in build/anim194-20261019; compact controls are
committed in animation-loader-ab96d-20261019.json. The 339-byte callback-table
initializer at ABA2F explicitly waited on this loader and can now be revisited;
its remaining alias requirements are separate work.
