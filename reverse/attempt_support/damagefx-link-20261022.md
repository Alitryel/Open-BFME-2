# DamageFX destructor linkage, 2026-10-22

At BFME 2 14b723b147 and donor 37c3022de1ab944c7ffe536440d637dc8199091c,
replace whole DamageFX hash_map explicit instantiation in Rva0016DEE0Cluster.cpp
with explicit instantiation of its owned hashtable destructor. This removes
unowned non-retail helper copies rather than changing their implementation.

Acceptance: build.sh and link_check --prepare-current pass all four rows
(77+82+82+5 bytes), string/float/import gates pass. Published census index
08160bc2c9 (2026-10-22 17:08), with explicit current objects for the cluster and
DamageFX_hashtableNewNode.cpp: before 0/2 units, 0 B; after cluster LINKS 246 B,
consumer remains 0 B. This is a legacy census-preview gain only; no measured
self-strict or closed-strict link-cycle gain is claimed. Strict reusable compile
receipts were prepared; that alone is not closure evidence.

The consumer previously selected this cluster's wrong const-iterator range
 erase. Removing that copy exposes its unresolved definition; the consumer also
has a conflicting unproven destructor. Its RVAs are claimed by another worker,
so this change does not touch it. A real retail range-erase implementation and
consumer destructor reconciliation remain necessary. The cluster itself has no
remaining link blockers in this preview.
