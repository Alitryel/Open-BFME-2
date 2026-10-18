# Narrow string count constructor ownership, 2026-10-18

Base e359159f5b; published census c2c5ac8c27 (2026-10-18 11:36).

The constructor at 0x00028B10 calls the const-char forward-range helper at
0x000078C0. Its local declaration used private access, producing an AAE
reference. That spelling has a pin but no ledger owner; the selected copy
is wrong. The byte-verified owner in stlport_narrow_string_range_init.cpp
uses public access (QAE). Match that declaration's access in the constructor
unit. This reconciles object names without changing the helper address,
argument types, object layout or constructor bytes. It does not establish
the access modifier of the original source as a target fact.

Paired identical two-provider LEGACY previews: 84 -> 207 bytes, +123 bytes.
Both units now link. The existing 84-byte helper is not new coverage.
Strict reusable byte receipts pass 3/3 rows across the two providers;
the constructor's EH graph is EXACT, and new-variants passes. Normal byte
gate also passes both constructor-unit rows. No self-strict LINK,
closed-strict or full-link gain is claimed. No full runner used.

The BFME1 donor survey and freshness blocker remain as documented in
../peek-shader-link-20261018/readme.md. No reference inputs changed.
