# Scope the STL trait instantiation

The sole claimed body in StlSweepW6Rva00584D3F.cpp is the 17-byte
`_OKToMemCpy<Rva00584D3FElement, Rva00584D3FElement>::_Ret` at RVA 0x00584D3F.
The file instantiated nine complete sorting/heap operations to emit that trait.
Their extra definitions referenced the provisional element's undefined
comparison, preventing the unit from linking.

Instantiate the trait class directly. Keep the element view, compiler settings,
headers and matched identity unchanged. The original element identity and
unconstrained fields remain structural inference. No comparator is invented.

Verified on BFME2 parent 2fc6691864 and BFME1 input
96c88c73a5cd1a58fc2f8db691beea50acd996db with MSVC 13.10.3077:

- Normal byte gate: 1/1 exact. Strict preparation: one reusable receipt.
- Original and new COFF retain identical complete 17-byte code and zero
  relocations. The original immutable-cache object has the same source,
  command and current header inputs; its receipt and object hashes agree.
- Emitted external definitions decrease from 90 to one; none is added.
  Other Code sources and symbol pins do not name the private element type.
- Three removed shared helpers retain their existing first providers:
  integer gcd (27 copies), integer log (52), placement new (1,323).
  None has a measured selection exception naming this unit.
- Paired per-file preview against the same updated index: 0 -> 17 nonpadding
  bytes linkable. This is a legacy preview, not a new census or closed-strict
  closure result. No C++ coverage growth is claimed.
- Declared definitions pass; placement resweep finds zero bodies or pins.

The object and provider summaries preserve the comparison. No source outside
this unit, ledger row, pin, header, compiler flag or verifier is changed.
