# Browser BSTR lifetime repair

The served two-string wrapper at177130 is an existing135-byte C++ body.
Its native EH actions767EF0 and767EF8 both reach176FF0. The existing local
BfmeBstrVGP destructor emitted12 bytes: it released the payload but omitted
the pointer reset present in the complete22-byte retail cleanup. A direct
whole-callee audit caught that mismatch even though the parent/EH table
shapes already matched. This was a real missing cleanup behavior, not a
false verifier rejection.

Add the native pointer reset after release. The real out-of-line destructor
now emits the entire22-byte retail body, including the call to the existing
release176E90. The compiler removes the dead parameter reset from the
inlined normal return paths, so all nine previously owned bodies remain
exact. All five wrapper EH graphs also verify exactly, and their actual
cleanup callees are now complete byte/relocation twins of retail.

The inherited BSTR/Data_t view and descriptive Bfme names come from the
existing BFME1 donor port. This repair establishes only the native owning
pointer at offset0, its release call, its subsequent zero store, and the
by-value argument cleanup relationship. It does not infer original class
names or additional payload layout from equal bytes.

Admit the naturally emitted22-byte destructor as a gen-alias ICF twin of
the existing Rva00958C40::go owner at176FF0 through normal add_match
--icf-owner. No pin, object-symbol alias, duplicate unique-byte credit or
new source surrogate is introduced. The two-argument wrappers at177010
and177130 share native FuncInfo90CA48 and handler767F00. Own that complete
ten-byte handler through the served real parent. The three single-argument
wrappers share the already owned handler767ED8/FuncInfo90CA6C; they add no
new unique bytes.

Rehome both existing generated eight-byte argument actions to their actual
parent-scoped compiler labels. Consecutive local COFF labels and the named
following handler establish boundaries0/8/16 in their26-byte section; all
three whole bodies and the complete parent graph verify. The generated
source is untouched. Two object-symbol annotations disappear. The existing
single-argument action's older annotation remains unchanged and normal
parent-based label-renumbering verification still passes.

Normal source verification passes13/13. proof.json checks each whole body,
all relocations, all five full parent EH graphs and actual cleanup bindings,
strict dependency currency, source/object hashes and native cleanup bytes.
The source previews as LINKS against census8eecc93d07; this is a preview,
not a new census. place_bodies finds zero additional bodies or pins and the
frozen-file check passes. Strict unique C++ recovery is ten bytes.
No compiler flags, shared headers, gates or baselines changed; no maintained
runner or runtime test was needed for byte-identical native behavior.
Pinned BFME1 input cf0a80c228; about six minutes; gpt-6.1-sol.
