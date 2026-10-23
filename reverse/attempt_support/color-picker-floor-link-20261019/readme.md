# Color-picker math emitter and cleanup ownership repair

Inputs: BFME2 f296c2b20e6b6924b3b589e16815c99bf4ceb0a6; verified BFME1
pointer6b9d92bf92debd03e4357462bab41f701651e67c. Complete current color-picker
owner, prior Floor refusal, and tracked font/shroud math repairs were read.
The published census index measures4ae54b0a4f at2026-10-19 10:38; its SHA256
and source/object hashes are in object-proof.json. No census or link cycle ran.

The O1 owner emits a surplus18B WWMath::Floor COMDAT; the ledger's20B retail
copy belongs to lightenvironment.cpp. A declaration-only shim was previously
refuted because it changed the caller. Preserve the actual visible operation,
return floorf(value), in a file-static inline helper instead. This removes the
public copy while retaining the same inlined calls. No shared header, compiler
flag, pragma, pin, alias, global or arithmetic behavior changed.

Before/after object proof removes exactly ?Floor@WWMath@@SAMM@Z. All30 retained
external COMDAT raw-body/relocation digests and all undefined externals agree.
All five existing owner rows remain byte-exact, including the1100B Render,
307B Init and235B ExternFunc; two complete EH graphs remain EXACT. Ten strings,
four empty-string refs, four float literals and eight imports pass without
skips/baselines. Declared-definition check passes.

Same-index lightweight link_check before the edit reports two Floor findings
and current LINKED0; after reports LINKS for all1653 authored non-padding bytes.
Its printed historical census546 is a third figure, not the before-edit
preview. This is a1653B preview improvement, zero new unique exact C++ bytes,
and no claim of measured link placement or closed-strict coverage.

## Real cleanup ownership

The exact parent EH relocation graphs locate six8B cleanup bodies:

- Render00741152:007AB56B,007AB573,007AB583,007AB58B.
- Init0074159E:007AB5A5,007AB5AD.

Each former anonymous uw_gen harness row is replaced through add_match's
generated-unwind-scaffold admission with its actual compiler-local label and
same-source parent. Every whole8B body and callee relocation verifies. No
generated source is edited. This binds48B to the real C++ lifetimes but does
not increase unique C++ coverage; progress.py explicitly remains+0 for this
repair. Funclet locations come from the exact graph, never adjacency or byte
ties. Local label numbers are hints; the gate rederives their parent locations.

Two other8B Render cleanups,007AB57B/007AB593, retain their generated harnesses.
The actual local ColorSurfaceLock destructor has no admitted binding; the
native cleanup jumps to0004D754, already owned as Rva0004D754::clear. This
needs a supported provider/consumer identity reconciliation, not another pin
or a second name on that address. No incomplete ownership transfer is retained.

The known W3DTankTruckDraw Floor consumer was read in full and previewed, but
also has many independent audio/particle/class blockers; no edit was attempted
there and its file claim was released. Existing BFME2 identity/layout evidence
and donor uncertainties in both sources are unchanged. t=8min model=gpt-6.1-sol.

Raw scripts, snapshots, explain/build/ref/EH logs and both preview outputs are
under build/color-picker-floor-link-oct19; the original before-preview log is
build/recent-handlers-oct19/color-link-before.txt. Tracked object proof and
cleanup receipts preserve the facts needed to review this repair.
