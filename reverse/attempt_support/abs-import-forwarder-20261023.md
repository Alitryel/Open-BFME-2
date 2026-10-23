# Five-byte abs import forwarder

Target: RVA 0x00001158..0x0000115D, bytes E9 3D 7F 62 00.
The jump resolves to RVA 0x0062909A. Its existing generated import row
identifies MSVCR71.dll abs, IAT VA 0x00BBA6D8. The bundled MSVC 7.1
stdlib.h declares cdecl int abs(int), independently establishing the ABI.
absForwarder is a descriptive inferred wrapper name, not an original name.

The old blocked verdict came from a generated b_<target>/j_<address> alias
pin rejected as a second real name. This recovery creates no pin and uses
the already admitted _abs binding at 0x0062909A. Its alternate existing
binding at 0x00629952 is not this retail target.

Ordinary return abs(value), with intrinsic expansion disabled, reproduces
the complete tail jump. Scratch /O1, /O1 /Oy, /O1 /Ob2 and /O2 controls all
match. Final Code source uses region defaults with /Oi-; no override,
assembly, new alias or verifier change. Normal add_match verifies 1/1 rows;
string, float and import checks pass. The import checker has zero direct
IAT operands here because this body reaches the already rowed import thunk
through REL32. The branch target itself was resolved and verified.
