# SidesInfo script accessor emission repair, 2026-10-15

`SidesList_sidesInfo.cpp` emitted an unused four-byte non-const
`SidesInfo::getScriptList` COMDAT. It differs from the first existing copy
in link order. Imported forceinline preserves its established inlined
`&m_scripts` access while suppressing this competing standalone definition.
There is no new import reference, alias, global, pin, header, layout or extent.

Before checkout: a0fe13e5ed3ae1456958bc36400562f0c052cff5.
Runner index: a2839ea429, 2026-10-15 13:35, original census 5986a99448,
2026-10-15 04:52. Index SHA256:
`c76811bd8f1cc3b5821d37038c76dbe5815dbb478d53ed5e33f02c150daa7d37`.
The committed status file measures another revision; it was not changed.

Both consumer objects have strict reusable current receipts. Both existing
getter providers, `Common/RTS/Player.cpp` and `ScriptEngine/Scripts.cpp`, were
claimed and prepared with `link_check.py --prepare-current`; their current
objects were refreshed together with each consumer object into the same
index in memory. No census or full link cycle was run.

The paired consumer preview drops exactly one COMDAT finding (five findings
to four), with every other finding unchanged. Provider findings are identical
before and after; counts and complete-finding hashes are in `proof.json`.
Both remaining getter copies retain their keep/loss decisions and kept body
facts, evaluated in link order. The 34 retained COMDATs, every retained
nondebug section byte/flag/relocation, external/weak binding and data fact
are unchanged; none references the removed definition. Proof records the
source, object, receipt and index hashes. This is a self-strict current
consumer/provider comparison against legacy index facts. Legacy LINKED
bytes remain 0 -> 0; authored-byte gain is zero. No self-strict executable
or closed-strict gain is claimed.

Acceptance:
- Strict preparation: consumer 25/25 rows before and after; providers 22/22.
- Normal `./build.sh` consumer: 25/25 exact, literal/float/import checks pass.
- EH: consumer five EXACT before and after, provider one EXACT; no baseline
  or missing-object verdicts.
- Frozen-definition, class, CSV, new-variant and whitespace checks pass.
- Shadow data: zero findings; enforced converged data: eight addresses,
  zero second names and zero unjudged rows.
- `place_bodies.py`: zero bodies and zero pins.

The established BFME 2 matched callers prove the retained member access.
No new standalone getter identity or class-layout fact is asserted. BFME 1
repairs c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 and
66b19a8e95a4add525ef808fcea088e306798e2b were reviewed for the applicable
inline-import emission mechanism; no donor body, identity or layout is
imported. The verified BFME 1 gitlink/checkout remains
 a7c38d3b2597121f178ab5190b3062478823257d. Official master was fetched as
95eeb3bef370a7cd730b0ad5f228c317c8756e72. Another live seat owns
`file:reference/open-bfme-1`; the comparative full verification and donor
refresh for that pointer update remain with it. No success stamp was written.

Remaining consumer blockers: `ScriptList::~ScriptList`, callbacks
`Rva005CB265` and `Rva005CC208`, and the selected faction-list copy provider.
The two refreshed provider units also retain independent blockers; this
repair neither changes nor claims to resolve them. Broader link closure
remains unmeasured.
