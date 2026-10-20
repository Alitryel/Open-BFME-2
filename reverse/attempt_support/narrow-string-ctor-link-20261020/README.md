Narrow-string constructor link sweep, 2026-10-20
================================================

BFME2 baseline 11f965017e; BFME1 inputs remain at verified gitlink
92f6bbe8e1dcdb46b5d27da0674313efc822b790. No donor update or new pin.
BFME1 linking repairs reviewed at that revision favor direct row-owner calls.

Three constructors (allocator270D0/124B, reserve27150/129B, fill271E0/177B)
call allocation7460. Their private _String_base-scope spelling resolved to a
nonretail selected copy. Call the existing basic_string-scope owner directly
through the same three-pointer layout, following the already matched manual
constructor views. The reserve constructor follows the vendor _string.h
reserve-tag body exactly, with the same base constructor and NUL termination;
its first argument is an empty tag, as existing native callsite evidence proves.
Its vendor linker directives are preserved explicitly.

All three also emitted an11-byte empty allocator-proxy destructor under /Od;
retail's native unwind graph calls the shared one-byte body at69E440.
A plain external destructor declaration removes the wrong copy without changing
the unwind call, data or cleanup. No imported call, alias or optimized body.

Paired proof.json uses the same5366c4f808 census index and unchanged strict-current
rowed allocation provider in both phases. Legacy prediction0/3units0B becomes
3/3units450B (187fill+134allocator+129reserve; funclet padding excluded).
Self-strict objects: all7 touched rows pass the full byte gate; provider row
also strict-current. Closed-strict closure/gain is unmeasured.
All retained nondebug sections, symbolic relocations, EH and directives agree
exactly after the one allocation-call owner substitution. Removed COMDATs are
listed in proof.json. EH verifier:3graphsEXACT, zero baseline exemptions.
Class, declared-definition, data/converged checks pass. No full link cycle.

Cause sweep: default/copy/C-string narrow constructors already predict clean;
substring/range constructors and other allocation-name consumers retain
independent blockers. No zero-gain edits made to those units. Existing pins
are unchanged; no authored retail-byte growth is claimed.
