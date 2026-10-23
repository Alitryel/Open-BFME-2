Subtitle registry / record cleanup link repair, 2026-10-20

Declare the record base destructor, record allocator deallocate and ModuleData
pointer-vector push_back so their existing providers own out-of-line calls.
Use the existing __copy_trivial extern switch before the first STL include.
No helper body, class layout, global, pin or ledger change.

Frozen index e7a7769fe5, 2026-10-20 18:36: paired legacy preview 0 -> 764
nonpadding matched bytes. Both phases replace the object's actual census
basename in a fresh copy of the same index. Four blockers disappear, all
five blocking fields are empty, retained COMDAT byte/relocation digests
are identical and no new COMDAT is emitted. proof.py and proof.json record
the local build/seat-subtitle snapshots, hashes and comparison.

Self-strict byte checks pass all six rows before and after, including the
renumbered unwind label, one string, one float and zero imports. EH 2/2 EXACT.
This is legacy preview gain with strict-current own rows; closed-strict
closure and executable gain are unmeasured. Authored C++ bytes +0.

Cause sweep: Rva00506A52 has unchanged prior evidence that declaration-only
push_back changes the parent frame, so it was not retried. RankInfoCtor also
needs Overridable vtable/destructor reconciliation and vector assignment;
removing __copy_trivial alone would not link it. Other record-vector units
are blocked by different insert/fill providers. No speculative sweep edit.
BFME1 donor review reused unchanged 4483e88da1c2 ownership leads a411b334c,
3313189ad and c54305633; this repair uses the existing BFME2 native types,
providers and retail byte checks, without transplanting donor addresses.
t=10min model=gpt-6.1-sol.
