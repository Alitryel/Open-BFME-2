# Truck particle-handle constructor emission repair

Target base 14cac4e8aa. Frozen runner index measurement ac77c85054,
2026-10-15 14:25; object-proof.json records the exact index hash and snapshots.
The source file was claimed and passed the declared-definition check first.

W3DTruckDrawCtor.cpp emitted a competing RvaSmartPtr12(void *) constructor.
Its private implementation stored a pointer and zeroed both list links even
for nonnull input. The rowed native owner in SmartPtrCopyCtor.cpp instead
attaches nonnull pointers and zeroes links only for null input (0x0004CBF7,
34 bytes). The truck constructor initializes all three handles with null.

Use those established native semantics in the visible inline constructor,
marked imported forceinline to suppress the unused external copy. The compiler
still folds the three null initializers to the exact existing stores. There is
no new import or attach reference. No layout, ABI, flag, header, pin, alias,
ledger row or baseline changes. Target identity/layout claims remain those of
the existing rows; this repair does not infer an original handle type name.

The emission technique follows BFME 1 repair
66b19a8e95a4add525ef808fcea088e306798e2b (reviewed at the verified donor checkout
a7c38d3b2597121f178ab5190b3062478823257d). Its suppression pattern is applicable;
no donor body, address or layout is imported. The overdue BFME 1 update remains
under another worker's live submodule claim; inputs and success stamp were
preserved.

## Acceptance and limits

- Ordinary build.sh: all nine truck rows exact, including parent/unwind rows.
- Bounded strict preparation before/after: 12/12 rows across consumer and owner;
  both have strict reusable receipts, zero skipped literal/import references.
- proof.py: every retained COMDAT and nondebug section preserves bytes, flags,
  definitions and symbolic relocations. Only the competing constructor copy
  disappears; no retained section references it. Undefined bindings and data
  facts are unchanged. The native owner object is unchanged.
- Paired copies of the same index refreshed with just these two objects:
  truck findings 4 -> 2 (duplicate and wrong COMDAT removed), owner 1 -> 0.
  Legacy predicted linked nonpadding bytes 0 -> 114. Ordinary local link_check
  agrees: owner links, truck still has unresolved DrawInterfaceC::slotC and
  DrawInterface8C::slot8C. Its nonzero aggregate exit reflects those blockers.
- EH graph: 1 EXACT, none missing/nonexact. Data enforce and converged checks:
  zero findings, eight converged addresses with no second names/unjudged rows.
  Class gate, frozen-file check, new-variant admission, CSV and whitespace pass.
  Placement rescan: zero bodies, zero pins.

The index inventories only these two constructor emitters: the native owner
and this rejected truck copy. Other declarations are not additional definitions.
This verifies self-strict byte receipts and a legacy local preview improvement;
closed-strict placement and census gains remain unmeasured. Authored C++ byte
coverage grows by zero. No full census, link cycle, nightly or boot ran.

proof.py requires ignored build/truck-handle-link-20261015 snapshots. The saved
JSON records this session's evidence, not a portable standalone regression test.
No census/index/status/history artifact was changed.

## Separate blocked probe

The Pod16 map lookup (0x00257252, 92 bytes) has a generic 33-byte node factory
conflicting with native 0x00413374/34 bytes. Its original strict gate passes;
node/insert provider preparation passes 23/23. Both a declaration-only node
specialization (matching the insertion sibling) and a visible native
allocator<char>/_Construct implementation change the lookup's copy/argument
scheduling and produce 91 bytes. After two failed byte gates the source was
restored, passed 1/1, logged blocked and its file claim released. Snapshots and
failed outputs remain under build/pod16-node-link-20261015. A repair needs to
preserve the caller's transitive compiler summary, not repeat these trials.

The iterator _M_getc, Apt counted-key, critical-section/result destructors and
wide comparator leads already have unchanged recorded blockers. Several other
ranked entries were stale repairs already in current source; the competing
wrapper-constructor lead was held by another worker and was not edited.

## Shadow identity handoff

The normal commit hook passes but reports two shadow interior-binding findings.
A paired scan using allowed_symbols.load/scan, with row_object redirected to the
saved baseline object only for the truck source, records one before and two
after (shadow-identity-comparison.json). The additional uw_00762505 finding
looks up its stale object-symbol=$L488 directly. Strict preparation instead
resolves the verified parent EH graph to $L490 at 0x00762505; $L492 likewise
resolves to $L491 at 0x00762513. See prepare-after.txt. The whole retained
nondebug object graph, including symbolic relocations, remains identical in
the independent paired object proof. No identity baseline or ledger labels
were changed. A tooling follow-up should make the shadow identity scan use
the same proven EH-label resolution; these findings are not closed-strict
acceptance evidence.
