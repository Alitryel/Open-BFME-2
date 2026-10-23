# Rva0010F7EE vtable reconciliation

Base: `8ead345076cdde734c0983fb2b3f1f08a6ecf898`.
Frozen local index: SHA256
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`,
measurement commit `a2839ea429` (2026-10-15 13:35), census commit
`5986a99448` (2026-10-15 04:52). The committed status CSV is older;
no census, status rewrite, full link cycle or index publication was performed.

## Target evidence and change

Retail VA `0x00BCFAB0` contains `0x0050F7D2, 0x009D124D`;
the next table starts at `0x00BCFAB8` with `0x0050F822`.
These slots name the matched deleting destructor at RVA `0x0010F7D2`
and the matched forwarding member at RVA `0x005D124D`.
`Rva0010F760Factory.cpp` already declares this complete two-slot class and
emits that table. `OpaqueScalarDeletingDtorsB01.cpp` declared only the virtual
destructor, emitting a competing one-slot table under the same name.
Declare the existing forwarding member in that view. No body, pin, alias,
import, baseline or data claim is added. The address-derived class identity
and existing gen-alias forwarder remain as established by the ledger.

The paired COFF proof finds only the table growing from 4 to 8 bytes and its
new DIR32 reference to the already matched member. Every code COMDAT, every
other nondebug section, symbolic relocation, weak external and existing
external binding is unchanged. The factory object is unchanged under these
comparisons. Both tables now have identical bytes and relocation signatures.

## Checks and measured result

Before and after, `link_check.py --prepare-current` byte-verifies both explicit
sources, 22/22 rows, and produces current strict reusable object receipts.
`./build.sh` also passes 22/22 with string, float and import checks.
`proof.py` refreshes both before objects together and both after objects
together against independent copies of the same index. The factory goes
from one conflicting COMDAT to zero findings: local legacy LINKED 0 -> 161
nonpadding owned bytes. The emitter remains 0 -> 0 with the same nine
unresolved dependencies (listed in `proof.json`). Its remaining code is
unchanged. The destructor provider `Rva0010F7EEDtor.cpp` remains LINKED 62 -> 62.
The three-source ordinary local preview therefore reports 62 -> 223 and exits
1 because the emitter still cannot link. This expected failure is retained.

Self-strict byte verification/current receipts are established; self-strict
executable placement and closed-strict closure are unmeasured. This is a local
legacy improvement, not a new census or closed-strict gain. Authored C++ gain
is zero.

Additional checks: `find_declared_unmatched.py` on both sources passes;
`link_check.py --new-variants` passes; `eh_verify.py` reports one exact EH row,
zero nonexact/missing; `data_check.py --enforce` has zero findings;
`data_check.py --converged` checks eight addresses with no second names or
unjudged addresses; `class_gate.py` passes; `place_bodies.py` finds no additional
bodies or pins; `check_csv.py` and `git diff --check` pass.

## Donor linking review and provenance

Official BFME 1 master was fetched at `464e5b60`; the verified checkout/gitlink
remains `a7c38d3b2597121f178ab5190b3062478823257d` while another seat owns
its pointer update. No freshness-success stamp was written.
Reviewed BFME 1 repair `9af805d8ed9f679b0b93f04ba1b7d7ff67119b62`:
it reconciles a constructor's wrongly named vtable with the deleting-destructor
owner proved by retail. Its ownership principle applies, but its class rename,
source, addresses and ledger changes do not: BFME 2 already has one name and
needs the missing second slot. The change here follows BFME 2 retail and
existing matched providers only. Also reviewed unused-emission repairs
`c1315665a1b22beb7e6d9279548fe5b1c26ed1f9`,
`53d32d6b4b377317a3397971629ca3ad20b870e9` and
`66b19a8e95a4add525ef808fcea088e306798e2b`; no suppression or donor type was
used for this repair.

## Reproduction and limitations

`proof.json` retains hashes, paired findings and exact variant names.
`proof.py` uses ignored before snapshots in
`build/callback-vtable-link-20261015/before/`, its `context.json`, the frozen
index and current compiled objects. These snapshots are local evidence;
the script is not standalone without them. The tracked base revision and
hashes identify the before inputs for an independent reconstruction.
The emitter's eight destructor dependencies and `g_bfmeVftBVJS` still need
separate supported repairs. Broader link validation remains outstanding.
