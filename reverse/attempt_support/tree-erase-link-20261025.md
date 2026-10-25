# Selective tree erase instantiation

At BFME2 a9653aa8cf, stlport_rb_tree_rva0027EA49_erase.cpp defines six
recovered erase/clear/destruction bodies but instantiates the whole tree class.
Its unrowed insertion/copy members reference an undefined _M_create_node.
The independently rowed node creator at5C6728 belongs to an int-keyed map,
so inventing a set creator identity or equating their record types is unwarranted.
Instantiate the six recovered APIs directly and remove the obsolete declaration
that incorrectly claimed this set factory had a kept provider. All existing
names, semantics, extents, flags, helper calls and rows are preserved.

Paired current-object link_check.py against ce1b975697 (October25 03:51,
retail-truth-4) changes the whole unit0 ->302 nonpadding bytes. This is a
legacy preview, not a self-strict/closed-strict census or executable result.
The only old definitions with graph edges from outside this unit are common
swap<unsigned>, __black_count, and iterator equality helpers; the census has
40,9,378 providers respectively. No private record operation loses a provider.
The narrowed unit's link preview is clean with no missing callee or competing
copy. No new symbol pin, alias, hatch, data definition or identity is added.

Acceptance: ./build.sh and link_check.py --prepare-current pass6/6 rows with
a strict reusable byte receipt; link_check.py predicts302 B linked;
find_declared_unmatched.py, check_csv.py and commit-hook checks pass.
Original source, external-reference audit and before/after logs are in ignored
build/link-seat-tree/. Relevant Rva0027EA49 identity/copy and5C6D9C evidence
was reviewed; no deferred body was retried. Reference basis is the already
vendored STLport4.5.3 implementation, with no new donor attribution.
