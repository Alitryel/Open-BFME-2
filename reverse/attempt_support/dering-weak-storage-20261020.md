# Weak deringing: storage and processor controls

Native _DeringBlockWeak_C is1C22C0..1C28B6,1526 bytes. Only reviewed specs
001c22c0/001c1ad0, retail, the complete bank and its linked evidence were used.
No external decoder source was consulted. Inputs45c587deb0/BFME1b3cc6b1588f2.

The existing mixed-counter bank freshly reproduces1526 bytes, firstdiff+63,
243 fixed-offset differing bytes. Native and candidate have the same actual
16-bit array addresses; the remaining cursor bias and scheduling are already
documented. No physical array enlargement or padding was justified or added.

Six independent ordinary diagnostics tested two previously unrecorded controls:

- Unsigned16-bit storage for vertical weights, horizontal weights, or both,
  with an explicit signed-short interpretation at every output read. This
  preserves negative sharpen weights and the same72 physical entries. All
  three compile to exactly the baseline's code bytes AND relocation records.
- Valid G5/G7/GB processor profiles instead of the bank's G6. G5 and GB are
  also byte-and-relocation identical. G7 emits1486 rather than1526 and worsens
  fixed differences243->1145. No profile supplies the native cursor layout.

The unchanged baseline scores1440 aligned bytes when SequenceMatcher receives
candidate first and target second; the old1441 metric uses a different ordering.
No one-byte regression or improvement is asserted from that asymmetric metric.
The243 fixed differences and actual baseline code are unchanged. No new oracle
run is claimed: no replacement bank was selected, and the prior2560-case
native/C++/independent-spec check remains evidence for that same bank.

The better bank is preserved unchanged. No production source, row, pin, global,
header or verifier was edited. Complete normal explain logs, the code hashes,
relocation-equality results and isolated source variants remain
build/dering-weak-storage-oct20/. Future work needs a distinct explanation of
the cursor bias and output schedule rather than these storage/processor forms.
