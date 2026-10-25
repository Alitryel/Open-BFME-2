# Sol family B shard 1/2 prerequisites, 2026-10-25

Seat codexb5; allocation from `/opt/runner/consolidation_queue.py --limit 20`.
Started from clean d7fa8a31bf with no inherited session metadata or local commits.
Read current AGENTS.md, consolidation workflow/audit, claims and naming rules.
Initial pull and `python3 tools/check_csv.py` passed (98,252 function rows).

## Bridge allocator prerequisite verified

Target TU: Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBridgeBuffer.cpp.
The seed omitted the existing allocateBridgeBuffers method declaration; its
allocator donor used m_0C where the seed calls the verified counter at +0x0C
m_c. Add the nonvirtual declaration and use the seed's existing placeholder
in the donor. No layout, signature, body, flags or provider identity changes.

Before: normal merge dry run accepted nothing. After: accepts the seed and
W3DBridgeAllocateBridgeBuffers.cpp, preserving all 14 matched rows (10 seed,
4 allocator, including its two unwind funclets and handler). Local receipts:
build/sol-b5-bridge-before.txt and build/sol-b5-bridge-final.txt.
This demonstrates an allocator-subset unblock; no merge was applied and no
later Luna landing is claimed. The mechanical seat may merge that pair with
ordinary destination verification.

Checks: `./build.sh` on seed verifies 10/10; on allocator and the unchanged
loader verifies 5/5. Frozen-file checks pass for all three. Allocator
`eh_verify.py` reports EXACT 1, no missing objects or baseline exceptions.
Staged code-identity check: 14 rows, zero new findings in shadow mode.
Staged data checks: zero findings; converged data check: no second names or
unjudged rows. Neither changed source has header-queue, SDK-queue, data-debt
or code-identity-debt keys. No register key was retired.

Remaining Bridge blockers: loader declaration trial reaches C2146/C2501 at
m_start because composition relocates Vector3 after W3DBridge's by-value
fields. The unused loader declarations were removed; loader source unchanged,
verdict recorded with re_log.py and its file/RVA claims released. Destructor,
vertex, load, ctor and refill donors retain their private-view/declaration
failures; getModelVerticesFixed remains protected-register keyed. Mixed donors
stay intact. Do not treat the ready allocator pair as closure for the TU.

## Other investigated allocation

W3DPropDraw normal dry run accepts the seed and module-data destructor but
rejects reactToTransformChange with Coord3D redefinition at Coord3DCtorView.h.
The react donor deliberately needs the destructor-bearing shared view for
retail EH. No source or claim was changed for that read-only trial; the
existing Prop handoff remains applicable. Receipt: build/sol-b5-prop-before.txt.

## Reference freshness and outgoing audit

Official BFME 1 fetch found local 0bf534ea7ccde110c456edb9cd2dd5dae823c953
behind upstream f633d0e97a953289405438821be0c09b28527bbb. Retained the verified
pinned inputs, as in the prior consolidation-device-20261025.md freshness
handoff. No success receipt or reference-pointer update was invented. A
separate full verification/update remains necessary outside this lane.

The complete pending origin/master..HEAD range plus the staged prerequisite
has no moved/deleted sources. Active tools, hooks, workflows, includes, build
inputs and registries need no path repoints; historical EA paths are preserved.
Functions, data and identity owners remain unchanged. Provider/consumer code
and selected COMDATs have no new identity findings. File reduction: zero;
identity debt retired: zero; recovered C++/retail bytes: zero.

Keep seed, allocator and this handoff file claims plus 0x000DD8B8 until
publication is confirmed. Release file scopes and settle landed RVAs afterward.
