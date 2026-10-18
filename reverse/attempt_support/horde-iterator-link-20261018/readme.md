# Horde iterator helper ownership

At BFME2 ba773588f9 and census c2c5ac8c27, HordeGarrisonContain::exitObjectViaDoor is blocked solely by its non-retail _List_iterator_base::operator!= copy. A TU-scoped imported forward declaration keeps the standard header definitions available for inlining and defers external copies to the existing providers. All retained COMDAT bytes and relocations remain identical (object-proof.json). No type identity, layout, target pin, shared header, or ledger range changes.

Before link_check: blocked, 0/261 bytes. After: LINKS, 261/261 bytes. This is a legacy census-preview gain with a self-strict touched object, not a closed-strict result. build.sh passes the 261-byte row, and link_check.py --prepare-current produces a reusable strict receipt. A paired gate with the restored formation unit passes all three rows and string/float/import checks.

Cause sweep: HordeContainChangeToFormation also has a competing find helper. Deferring it changes the caller stack/register homes; the whole formation source is restored, its blocked evidence is logged, and its claims are released. The remaining ranked Rva000A7E9E consumer also has independent rb-tree blockers. Neither is claimed as repaired.

The standard header comes from the verified BFME1 pointer 64d369b90170b7e9ec917d646f020b11f13eb0d5. The imported-class ownership adaptation is locally verified against BFME2 retail; the separate BFME1 freshness update remains pending full verification.
