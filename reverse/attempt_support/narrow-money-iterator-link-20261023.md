# Narrow money parser iterator providers

At BFME 2 `5707edaf6c`, the current legacy preview leaves the 2,584-byte
`stlport_narrow_money_get_string.cpp` unit unlinked: its emitted
`istreambuf_iterator<char>::operator*() const` and `operator++()` copies lose
to the rowed providers. The 2,528-byte parser begins at RVA `0x00011230`.
All 17 rows pass the baseline and restored byte gate, including its EH rows.
Compiler flags remain those in the source's `// cl:` line.

Two unsuccessful trials, with no retained source edits:

1. Include `<iterator>` and declare the two iterator specializations before
   `<locale>`, instead of relying on the late increment declaration. The
   parser changes; the other 16 rows still match. This does not preserve its
   established inlining boundary.
2. After the source's opaque `basic_streambuf<char>` specialization, insert
   imported forceinline versions of the vendor iterator bodies:
   `this->_M_getc(); return this->_M_c;` and
   `this->_M_bumpc(); return *this;`. Compilation refuses this with C2908
   (`_M_getc` already instantiated) and C2995 (duplicate increment definition).
   The source already contains later explicit cache-getc and increment bodies;
   this trial did not reconcile those specializations. It does not establish
   that an appropriately placed inline specialization is impossible.

Resume by understanding those existing cache helpers and their instantiation
order, then compare the emitted iterator bodies with the rowed providers in
`stlport_narrow_istreambuf_iterator.cpp` and `stlport_money_get.cpp`. Merely
moving declarations earlier changes the matched parser. Do not repeat either
trial unchanged. The original source was restored and passes 17/17 again;
all claims for this attempt were released. No linked-byte improvement claimed.
