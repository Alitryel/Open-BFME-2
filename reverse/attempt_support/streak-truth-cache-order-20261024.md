# Streak recursive proof cache order, 2026-10-24

BFME2 e46a0ba24c; BFME1 32774ab03393709a7f14331ba8d98d281a55ffd9.
Published index 268f876e3b, retail-truth-4. No source or verifier edit.

Reproduction with current objects:

    python tools/link_check.py Code/Libraries/Source/WWVegas/WW3D2/StreakLineDestructor.cpp Code/Libraries/Source/WWVegas/WWLib/simplevec_float_cleanup.cpp

rejects Streak's 327-byte unit on the float dynamic-vector destructor. Reverse
the two arguments: both units link, 502 bytes total. The original Streak
source passes build.sh (1/1 function, references pass). This is inherited
source, not newly recovered or newly linked coverage.

Independently reading the cleanup provider with a fresh RetailTruth proves
its normal destructors (33 and 35 bytes), deleting destructors (28 each),
Add and Grow retail. The normal dynamic destructor's digest is 23974f600193.
The Streak unit emits a wrong 70-byte outline, but the kept cleanup provider
precedes it and supplies the proven retail body. Existing retail-truth-3
admits discarded wrong copies when a proven provider exists.

Likely cause: RetailTruth._defined_at caches (symbol, digest, target), without
the different transitive definitions attached to equal vtable bytes and
relocation names in different objects. Judging Streak first can cache a failed
vtable proof, then prevent proving the cleanup provider. This causal diagnosis
is an inference; argument-order dependence is directly reproduced.

Do not change tools in this linking pass. A tooling repair needs a separate
regression covering both orders and transitive definitions, plus the required
Verifier-Change trailer and exploit-suite checks.

Additional discarded source trials: importing the forceinline dynamic
destructor preserves the parent but introduces __imp_ calls and a wrong EH
cleanup. Size optimization and a late base-destructor definition preserve the
327-byte parent but emit 57-byte dynamic cleanup, still inlining the base
instead of retail's tail call. All production trials were reverted. The
existing cleanup provider already solves the actual link selection.
