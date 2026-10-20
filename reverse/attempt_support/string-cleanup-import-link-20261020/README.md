STLport cleanup DLL imports, 2026-10-20
=====================================

Baseline1ff910beec after rebasing on upstream8ec482f1ca. BFME1 inputs remain
92f6bbe8e1dcdb46b5d27da0674313efc822b790. Six caller units were held solely by
unresolved imported string destructors; the same six EH graphs were baseline
debt because their cleanup funclets used DLL-import jumps instead of retail's
direct jumps. The real destructors are already matched: narrow basic_string
at00142D70(14B), wide _String_base folded with narrow at0000B3C0(63B).

Remove dllimport from the five narrow cleanup views while retaining their
forceinline bodies. Each emits exactly the rowed14B destructor and leaves all
previous external COMDAT bodies and symbolic relocations identical. Declare
the wide base destructor out of line: it is only called for exceptional
cleanup, so its caller's matched constructor stays unchanged and the funclet
now binds the existing63B provider. No new pins, aliases, globals or type
identity claims were added. Standard STLport identity is inherited from the
existing rows; target bytes and relocations are verified independently.

Checks: strict-current8/8 touched rows plus13/13 existing provider rows.
Paired proof using one unchanged census index and the same provider objects:
LEGACY prediction0/6 ->6/6 units,0 ->801 nonpadding bytes. Every retained
external COMDAT byte/relocation digest is unchanged; the five added destructor
copies receive RetailTruth's retail verdict. Six EH graphs improve from
bytes_differ/dllimport to EXACT. Remove exactly these six repaired EH-baseline
entries(43->37), verified shrink-only. Closed-strict closure/gain unmeasured.
Class, declared-definition, ledger and data/converged checks pass. The normal
link_check display starts from old census coverage801B; the paired before
objects prove that current pre-repair coverage was0B, rather than counting
that published coverage as a new local gain.

Commands: link_check.py --prepare-current on six callers and two providers;
link_check.py on six callers; eh_verify.py on six callers and baseline objects;
eh_verify.py --write-baseline on six callers; eh_verify.py --assert-shrink-only
HEAD; class_gate.py; find_declared_unmatched.py; check_csv.py; data_check.py.
Paired proof.json records object hashes, unchanged index identity, added COMDAT
hashes/native verdicts, full before/after findings and both EH verdict sets.
