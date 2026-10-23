# Correct the default list append identity

The published b73720bed9 census (2026-10-20 05:34 UTC) is the comparison
index; it was not rebuilt or edited. Paired legacy-index previews of
stlport_list_int_o1.cpp, stlport_list_int.cpp and
stlport_list_create_node_vecuint.cpp changed from 0/3 clean, 0 linked bytes,
to 1/3 clean, 667 linked bytes. This is a legacy preview gain, not a claim
of closed-strict link closure.

The old integer-list default insert pin at 0x79CB6 contradicts the verified
94-byte list<vector<unsigned>>::insert(iterator) owner there. Its vector
base constructor and typed insert family establish the existing structural
element type; the application meaning of the unsigned elements remains unknown.
The 20-byte default push_back at 0x79E8D directly calls that owner, so its
integer-list identity was also wrong. Instantiating the vector-list append
in the existing provider reproduces all 20 bytes and that relocation.

Move the append row to that provider, suppress the unrowed integer append
and remove the contradicted pin. No new pin, alias or unmatched marker is
needed. The integer provider retains 18 rows and now previews cleanly.
The ordinary integer-list TU retains its other existing COMDAT conflicts;
the vector-list provider retains its recorded vector default-constructor
conflict. Neither is counted as a gain.

The dependent-source hook found one remaining caller of the old integer
append name: W3DHordeModelDrawManager::ProcessGroup. Its private declaration
used list<int> but already treated the appended element as a vector of
drawable slots. Correcting that list's element declaration to the proven
structural provider preserves all 616 bytes and the direct append relocation.
Its paired legacy preview stays 616 -> 616 bytes; no additional gain is claimed.

Validation: scoped ./build.sh passed 23/23 rows across the two edited units;
link_check.py --prepare-current passed both units with strict reusable
compiler receipts and the ordinary byte/reference gates. The final paired
legacy link preview reproduced the 667-byte gain. check_csv.py and
find_declared_unmatched.py passed. Local diagnostic logs are
build/list-int-before.txt, build/list-vec-before.txt,
build/list-repair-after.txt, build/list-repair-strict.txt and
build/list-repair-final-link.txt.
