# Narrow C-string constructor visibility, 2026-10-22

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
