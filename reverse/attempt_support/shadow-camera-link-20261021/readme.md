# Shadow camera linking prerequisite

At 894111481c, current-object check against 2b4d1fb42a holds 4176 real bytes:
assert import, Vector3::Cross_Product losing copy, BfmePod8 range erase losing
copy. Existing landed parent 0x7C8AE and handler 0x75F39D are retained.

Trial 1 adds DNDEBUG. Assert and cross-product blockers disappear but the
parent changes. Trial 2 restores flags, binds range erase by declaration to
its existing rowed provider 0x3FA4DB, and replaces source cross calls with a
TU-local forceinline copy of donor cross-product arithmetic. All original
helper blockers disappear; parent still differs. Thus simply removing an
unused helper copy or rebinding calls is insufficient: visible helper
summaries influence this parent's sensitive SSE allocation/scheduling.
Both whole-unit builds fail parent byte comparison; no third trial made.
Source restored exactly. No source, pin, layout or verification relaxation.

Scratch logs retained locally in build/seat-shadow-link/{ndebug,local}-{byte,link}.log.
Prior conversion banks describe the same SSE operand-order sensitivity;
this linking attempt does not replace their stronger evidence or banks.
Resume with a scoped helper binding that preserves all parent bytes and EH.
