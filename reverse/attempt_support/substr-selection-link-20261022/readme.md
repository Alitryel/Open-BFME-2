# Narrow substr selection repair

At parent b9918a4dea, using the published 2026-10-22 11:05 census at
ae3b3e68e2, refresh the three explicit current objects together:

```
python3 tools/link_check.py \
  Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string.cpp \
  Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_substr.cpp \
  Code/GameEngine/Source/Common/System/Rva00309358Tokenize.cpp
```

Before: 0/3 units link, 0 bytes. The early whole-class instantiation emits
a wrong `basic_string<char>::substr` copy ahead of the independently rowed
251-byte retail provider at 0x0002AD50. The tokenizer's sole blocker is
selection of that wrong copy. After: 1/3 units link, 158 bytes; the tokenizer
has no blockers. This is a paired legacy preview gain, not a closed-strict
gain. The string units retain their other allocation, range-template and
comparison blockers.

Declare the provider specialization in the early unit. Its removed substr
copy was also the only use instantiating the rowed mutable-range constructor
family; explicitly instantiate that constructor to preserve all four affected
rows, including its EH handler. No identities, pins or compiler flags change.

Acceptance: `./build.sh` verifies 19/19 rows, strings/floats/imports pass;
`link_check.py --prepare-current` verifies the same 19 rows and produces one
self-strict reusable provider receipt. Frozen-source and CSV checks pass.
The published census, index and link status are unchanged.
