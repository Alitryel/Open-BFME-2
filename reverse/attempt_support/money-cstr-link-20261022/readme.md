# Narrow money_put cstr visibility, 2026-10-22

The current legacy preview rejects 184 bytes on an unowned const-char string
constructor copy. Declare that constructor only. Both 174-byte parent and one
funclet change: stack frame 0x4c -> 0x50 and local operands shift. Same shared
empty-allocator visibility issue as the peer-stat and water-loader trials; no
further identical trials justified. Patch retained, original source restored.
BFME2 66c176bd18, verified BFME1 37c3022de1ab944c7ffe536440d637dc8199091c,
census 08160bc2c9; unchanged existing compiler settings.
