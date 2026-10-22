# Narrow C-string constructor visibility, 2026-10-22

The isolated-provider link verdict below is superseded by the paired-current
check at the end. The failed source trials remain valid evidence.

Trial tree: 8124f88828, with verified BFME 1 inputs 42bba2ddbd5c.
MSVC 7.1 and each source's unchanged `// cl:` settings were used.

The following current consumers each have one legacy link blocker: their
non-retail copy of the narrow `basic_string` C-string constructor, whose
retail owner is stlport_narrow_string_cstr_ctor.cpp at RVA 9100 (108 bytes).

- GameNetwork/GameSpy/Thread/PeerThreadStats_PackStatKey.cpp: 295 rowed bytes.
- GameNetwork/GameSpy/Thread/PingThread_Pinger_getPing.cpp: 172 rowed bytes.
- GameLogic/Map/StandingWaterAreaLoadPCA.cpp: 2362 rowed bytes.

Paths above are relative to Code/GameEngine/Source/. Ordinary link_check on
all three reported 0/3 clean, zero linked bytes, using the published census
at 08160bc2c9 (2026-10-22 17:08). No strict closure claim is made.

Two equivalent attempts inserted this declaration after the includes:

```cpp
namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(
    char const*, allocator<char> const&);
}
```

The second replaced `template <>` with `extern template`. Both failed the
full source byte gate. In packStatKey, the allocator temporary's LEA changed
from ebp+0B to ebp+0F. In getPing, the stack frame grew from 14 to 18 bytes;
LoadPCAFile also diverged. Parent failures additionally prevent verification
of compiler-emitted EH actions. Calls were already out of line: suppressing
emission also removes constructor visibility needed for retail's temporary
elision. These two forms are ruled out, rather than evidence for changing
the constructor's identity or weakening COMDAT checks.

All three source edits were reverted. There is no better byte-exact candidate
to bank; the original sources remain the starting point. The shared blocked
entry is recorded against packStatKey at 38A5D6. Consumer claims were released.
The restored sources passed 37/37 rows, four string literals, 15 floating
literals and 19 imports; a fresh ordinary link_check remains 0/3 clean.
Future work needs another evidence-backed way to retain optimizer visibility
while binding the constructor copy correctly; do not repeat these declarations.

Current-object triage of 32 other near-ranked units found 13 already linking
after upstream repairs. Those are not gains from this session. Refresh both
providers and consumers before using stale census blockers to choose a repair.
The EH assignment's separate handoff is eh-stubs-base-fold-20261022.md: three
new 8-byte cleanups verified, five unchanged blockers remain.

## Paired-current follow-up

At 7975c91816, with the same published index 08160bc2c9, checking the three
unchanged consumers together with stlport_narrow_string_cstr_ctor.cpp and
registry.cpp gives 5/5 clean: 172 + 295 + 2362 + 108 + 4418 = 7355 linked
bytes. The census comparison is 4526 -> 7355; all of this is already upstream
behavior, not a new repair. This removes the justification for further
constructor-suppression trials. These are legacy previews, not closed-strict
closure evidence.

Other current paired checks likewise find inherited repairs: the float4
assignment (183 B), Rva0054000B insert (152 B), opaque B12 destructors (701 B),
gap forwarders (739 B), notice display (197 B), C828C vector overflow (221 B),
HAnimCombo finish (94 B), ocean water (1581 B), and selection translator
(4145 B) already link. The current FXParticleSystemFactories and
HAnimComboBFME1 providers retain their own unrelated blockers.

The remaining assigned EH stubs are unchanged: 768841/76884B/768868 depend
on the unrowed 18C84E parent held by another worker; 75C850 needs coordinated
lock destructor ownership; 7A70A0 retains the scalar/array-delete cleanup
codegen difference. Preserve the two EH handoffs rather than retrying them.

Fallback checks: name_globals.py --dry-run kept zero edits; rehome_rows.py
cannot run because the fetched census bundle lacks build/link_census/census.log.
No full census was started. BFME1 upstream fetched successfully, but updating
the clean verified 42bba2ddbd5c pointer to 4592ab9117f4 is deferred to the
worker holding file:reference/open-bfme-1; no freshness stamp was advanced.
