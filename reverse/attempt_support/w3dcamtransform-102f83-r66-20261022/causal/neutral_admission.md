# Existing pinned identity preserves both ordinary bodies

`neutral.cpp` is the best `translation_lifetime/value_reference.cpp` under the
existing neutral entry and descriptor identities. It defines exactly:

`?rva00102F83@Rva00102F83Owner@@QAEXPAVRva0010274F@@@Z`

Rva0010274F is a class with public fields. W3DCamTransform keeps its established
transition method and state view; it friends Rva00102F83Owner. The neutral entry
accesses those existing fields and transition through explicit zero-adjustment
`reinterpret_cast<W3DCamTransform *>(this)` expressions. No alias local,
inheritance, wrapper, extra call, new pin or canonical-name assertion was added.
All other source expressions remain the input's expressions.

Full ordinary COFF comparison in `results.json`:

| Body | Before/after extent | Relocations | Complete byte/relocation equality |
|---|---:|---:|---|
| Camera entry | 4286 / 4286 | 57 / 57 | yes / yes |
| transitionLiveMode | 1024 / 1024 | 49 / 49 | yes / yes |

Camera fitness remains 0.9311709691110692; it is still not an exact retail match.
The admission spelling is therefore available without disturbing the current
compiler result. No production source, pin, header or ledger was edited.

Reproduce the isolated ordinary comparison with
`python build/camera-causal-20261021/neutral_admission.py`.
This uses the existing source flags and permute.Scorer, and reads the complete
object symbols independently of Scorer's target-sized scoring window.
