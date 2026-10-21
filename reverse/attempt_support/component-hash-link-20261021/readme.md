Component callback hash binding
===============================

BFME2 c3a3f7aaf0; BFME1 00c2ffbb23e9154fbe9970954afacb04e4943dd7;
published census c7845fd6e7, 2026-10-21 15:41.

Rva00462710ModeCheckForEach.cpp's sole legacy link blocker was its
rts::hash<AsciiString>::operator()(AsciiString) const COMDAT. The census
contains two copies: ThingFactory's first copy (9fde177159d3) and this
StringInline-based copy (fca37058872a). This name has no established retail
address. The replacement is a declaration of the same operator signature,
allowing the kept definition to serve it; there is no new identity, pin,
alias or target data-layout claim. The existing donor-based callbacks and
for_each identities and their native callees are retained.

Before: link_check.py on this source, 0 -> 0 B, sole differing hash copy.
After: same command and frozen index, 0 -> 307 B, LINKS.
A two-emitter census search finds no additional losing units for this name.

./build.sh: 5/5 owned rows exact, string/float/import checks pass.
eh_verify.py: 1 graph EXACT, no baseline or missing object.
find_declared_unmatched.py: all definitions matched.
link_check.py --prepare-current: strict receipts and normal byte gate pass.
The 307B gain is a legacy frozen-index preview, not closed-strict or a full
link cycle. No protected verification runner was started.
