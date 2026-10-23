# Historical BFME1 input comparison

`verification.json` records the completed comparison of verified inputs
`64d369b90170b7e9ec917d646f020b11f13eb0d5` and
`d348fca17814122303884ebe194cbc877a2c0bb0` at the BFME2 source revision
named in that record. Both full byte/data runs passed, their whole-ledger EH
verdicts agreed, and neither introduced converged-data identity debt.

This is comparison evidence, not a claim that the current gitlink was advanced.
The code-publication stage retains master's `64d369b901` inputs; its eight
edited sources independently passed all 224 rows and 28 named import bindings
with that actual checkout. The intermediate pointer-update commit
`f46c12719dac08c85ba5ab90039b127ed6f4ea9f` remains preserved separately.

A separate freshness pass is evaluating the newer official revision
`8619c4c56d73cfeb7beb7d7dd87e4fbde47b01da`. It must finish verification before
advancing the gitlink. No successful check of that newer revision is claimed
here, and this evidence earns no C++ recovery bytes.
