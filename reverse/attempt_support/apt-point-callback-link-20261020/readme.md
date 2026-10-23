# Apt point-hit callback slot linkage

At census 5366c4f808 (retail-truth-2), Rva000ABA2F.cpp has one unresolved
name, _pointHitTestCallback. Its own nonpadding matched body is 338 bytes.
The data ledger owns the four-byte slot at RVA 0x00A177B4 in
AptCharacterByteCounts.cpp, whose definition incorrectly had internal linkage.
Native initializer 0x000ABA2F stores callback 0x000910FB into this slot;
worker 0x006ECA70 tests and calls that same slot. This establishes the shared
slot independently of any donor identity. The callback's original source name
and full argument types remain inferred from the worker; the folded zero
callback ignores all arguments.

Give the existing zero-initialized typed slot external C linkage, using the
same typed declaration in its consumer. No new datum, pin or alias is added.
The paired local legacy preview improves 3,050 -> 3,388 linked bytes (+338 B),
with both units clean. Strict-current preparation verifies 17/17 code rows and
24 literals. This is self-strict evidence, not a closed-strict or full-link
measurement. Data shadow check reports zero findings; enforced converged data
check reports zero second names. Frozen definitions and class gate pass.

The same session abandoned the Path angle helper repair after an ordinary
external declaration changed its caller's register/frame shape. The consumer
already emits an exact helper, but cannot own the row profitably while scale
and 0x00364AA2 are still unresolved. Source restored; re_attempts.log records
the blocker. A Vector3 virtual-destructor declaration trial also passed byte
rows but exposed the known deleting-destructor mismatch; restored, with prior
evidence at log entries dated October 18 remaining authoritative.
