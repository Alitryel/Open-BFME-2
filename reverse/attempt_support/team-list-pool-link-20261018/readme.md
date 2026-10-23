Player team-list sentinel reconciliation, 2026-10-18

Paired current-provider legacy preview: 40 -> 499 linked matched bytes, +459 B.
PlayerUpdate gains 361 B and StlSweepR3Rva002AE577 gains 98 B. The unchanged
Rva002AC026MemberInit.cpp provider contributes 40 B before and after and is
excluded from the gain. Published census c2c5ac8c27; self-strict receipts only,
no closure expansion or closed-strict gain claimed. No authored-byte increase.

Native Player update2AE770 copies its +32C team list through 2AE577. That copy
calls the 40B sentinel constructor2AC026, independently rowed under the opaque
Rva002AC026Member::init name. Its proxy setup14F3C4, sentinel poolDBBD2C and
FreelistPool::pop2393E2 identify the pooled allocation path. Both template
units previously emitted general-purpose allocator523D6C calls instead. The
explicit base-constructor specializations now emit the full native40B, with
all three relocations unchanged from the native owner (constructor.txt).
The pointer-target spelling remains inherited evidence, not a recovered type.

The copy unit now declares the pooled base clear/destructor, binding to the
complete existing PlayerUpdate specializations and the already rowed canonical
pool owners. This removes its general-purpose deallocation copies. No pins,
aliases, ledger extents, shared headers or baselines changed.

Acceptance: 7/7 byte-exact rows, 2/2 complete EH graphs EXACT, data_check
--enforce zero findings; converged9 addresses and zero second names/unjudged
rows; all definitions declared; check_csv passes. Normal build verifies the
renumbered Player unwind funclet through its unchanged parent EH graph.
An initial strict preparation raced parallel cache-reading gates and detected
a stale receipt; the isolated repeat is recorded in strict.txt.
