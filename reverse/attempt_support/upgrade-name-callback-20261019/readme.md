# Independent UpgradeName callback and lifetime ownership

Retail 004C7E09..004C7E48 is a separate 63-byte callback. The only data
pointer to it is the field-parse entry at RVA0085E23C: UpgradeName, callback
VA008C7E09, null user data, destination offset7C. Native reads the INI and
destination stack arguments, obtains an AsciiString by value, calls the
already owned vector push_back and destroys the local string. These facts
establish the callback ABI and behavior independently of its old byte alias.
The original C++ scope is unknown; the new free-function name is neutral.

The prior row used object-symbol=the callback at004C3859. Its notes already
acknowledged that the two copies cannot fold because their handler operands
differ. That alias did not emit a second C++ lifetime graph. Emit the second
real callback in the same home unit and replace the scaffold through normal
add_match --replace-rva. Both complete63-byte bodies and both complete EH
graphs now match independently. No caller, field offset, helper pin, compiler
setting or shared header is changed.

The new callback naturally emits its own10-byte handler at0079037B, naming
FuncInfo00941AEC; this adds ten unique strict C++ bytes. The original callback
already owns its handler0078FF33/FuncInfo00941400. Rehome their8-byte cleanup
actions0078FF2B and00790373 from gen_uw's anonymous harness to the actual
parent-scoped compiler labels. Each action shares an18-byte .text$x section
with its following10-byte handler. The native handler address and named COFF
handler offset independently establish the8-byte boundary; both entire
sections are covered by the action/handler proofs and exact parent graphs.
No Code/gen_small source is edited. The parent alias and two generated
object-symbol annotations disappear: three actual escape hatches removed.
The hatch register's old allowances are left for a later batched tightening.

proof.json checks all six whole bodies, every relocation, both full parent
graphs, strict dependency currency and source/object hashes. Normal admission
passes6/6; frozen-file validation passes; scoped link preview reports LINKS
against the published8eecc93d07 census. That is a preview, not a new census or
a global link-coverage claim. place_bodies finds no additional bodies/pins.
No runtime test is needed for the byte-identical callback; no maintained
verification runner, new pin, alias directive, assembly or source surrogate
was introduced.

The nearby vector handler leads use similar old dup_* parent aliases but do
not emit independent parent/handler identities. Their canonical owner graphs
are exact; treating the alias name as a real COFF parent was the initial
read-only audit failure. They need their actual element/parent relationships
before recovery. Their source is unchanged and their claims are released.

Inputs: BFME2 base dd27f1e6e2; pinned BFME1cf0a80c228; existing bfme2_ascii
shim and source /DNDEBUG /MD /EHsc flags. This is target-led lifetime repair;
no donor implementation was imported. About eight minutes, gpt-6.1-sol.
