# FXShaderGeometry::Init accessor experiment

Target 0x0018C84E..0x0018D16B, 2,333 bytes; base commit 1e2a28889e.
The current r10 bank and its existing native/WorldBuilder identity evidence
were retained. No production code, pin, matched row or bank changed.

29 isolated compiles comprise one baseline, eight whole-Vector3 copy variants,
five copy variants at each of three remaining normal/position sites, and five
equivalent signed bone-index sums. The indexed-reference spellings come from
the Zero Hour WWMath/vector3.h operator[] declarations. This is a source-shape
lead, not proof of the original BFME2 spelling or layout.

None improved the baseline. Its 2,333-byte size reproduces, with 29 positional
byte differences including the unresolved short _Vector_base constructor
relocation. That constructor still needs ordinary fold admission; this run
did not substitute a scratch pin. The established load-order and SIB operand
differences remain. EH exactness is inherited bank evidence, not rechecked here.

The raw metric differs from the old resolved-bank metric. Scores are the
existing variant_search fitness, not a percentage of verified bytes. Positional
byte differences become misleading when instruction positions shift. normal4
was rejected because a relocation extends beyond the retail extent; the extent
was not enlarged. Other longer bodies are recorded as nonmatching sizes even
when the scoring helper could compare their first 2,333 bytes.

results.json records all trials. Scripts, sources, objects, disassembly and
diffs remain under build/fxinit-20261015. Compiles use explicit private object
paths; no exploratory object was placed in the shared match cache. The original
bank remains the strongest starting point. The claim was released.
