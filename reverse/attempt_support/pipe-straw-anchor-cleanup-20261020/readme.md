# Pipe and straw synthetic anchor cleanup

BFME2 base54a521e4, retained BFME1 donor92f6bbe8. The actual reference files are `game/Libraries/Source/WWVegas/WWLib/{pipe,xpipe,straw,xstraw}.cpp`. None contains the render-object include or synthetic array helper; their implementation bodies use no arrays. Independently decoded native calls for every owned row contain no call to the array-constructor iterator at RVA0x1423.

Removing only the synthetic anchor preserved all18 owned rows but exposed a wrong array-constructor iterator copy in every unit. That unsuccessful intermediate link result is preserved in `anchor-only-link.json`. The source files still included unrelated `rendobj.h`, which pulled the array machinery into these pipe/stream units. Remove that unused source include together with the synthetic preamble. No headers or compiler flags change.

Normal before/after whole-unit checks pass18/18 rows,918 claimed bytes, and both EH graphs remain EXACT. `paired.json` proves identical relocated bytes at every owned row, including the two EH-proven renamed unwind labels. All four current objects remain link-clean against the same census index before and after. The only external definition removed from each object is the redundant array-constructor iterator; no external definition is added. `dropped-providers.json` records its remaining providers. No canonical provider or owned retail method is removed.

This removes four synthetic anchors and eight pragma-optimize directives. Focused placement finds0 bodies/0 pins, and undeclared-definition checks pass. Zero new unique bytes and zero new linked bytes are claimed. No gate, baseline, header, alias or pin changes. Objects, original source copies and reproduction script remain under ignored `build/pipe-anchor/` in the writer checkout.

Agent: Codex (runtime model not exposed).
