# Asset refresh pending-tree prerequisite

The 3244-byte refresh at 0x006227E0 has a pending multimap whose insertion
descent compares the element's +0x10 word against node+0x10 with CMP/JAE
(0x00622A32/37). It stores that key at stack+0x40 and the element pointer at
stack+0x44 (0x00622A28/2C), passes the pair to insertion 0x00759BC0, retrieves
the pointer while evicting entries, and calls destructor 0x00620A00 on the same
pending object. These target facts establish unsigned ordering, a four-byte
payload pointer and the lifetime relationship independently of a byte match.
The original C++ key spelling and record name remain unknown.

The existing 122-byte destructor owner instead instantiated an int key and an
opaque one-byte record; its notes already classified these as donor inference.
Correct that view to unsigned int and an element-pointer record, retaining the
neutral Rva00620A00Record name. Rename its existing owner and naturally emitted
ten-byte handler in place. The already recovered five-byte release wrapper
uses the same corrected type. This introduces no second destructor identity
or address and adds zero unique C++ bytes.

Retire the old int-key _M_erase pin. The corrected source emits the actual
unsigned instantiation as a complete 51-byte function. tools/pin_admission.py
--add admits its fold onto the existing Rva00620390 cleanup owner only after
proving the whole body, both recursive/free relocations and every owner
relocation. The pin records fold-proof=the corrected source. Pin count does
not grow. No baseline change is included: the tool also removed two unrelated
allow annotations, and those existing annotations were preserved.

A smaller direct-call specialization was tested first, calling the existing
cleanup worker through an ordinary typed adapter. Both an empty and a proven
twelve-byte receiver view emit 120 bytes: the compiler changes argument
register selection and removes the native ECX reload. That nonmatching adapter
is not used. Retain the real STL template and the verifier-proven fold instead.
The destructor's original /EHs is necessary; the caller's /EHsc is independent.

Normal build.sh verifies the three owner rows and the separate canonical
cleanup worker together. Full EH verification is EXACT. The final independent
proof uses the real admitted symbol map, strict include-inventory receipts,
whole 122/10/5-byte owner bodies, the emitted 51-byte fold and its canonical
51-byte owner. Pin consistency and frozen-file checks pass. The new-variants
check passes and place_bodies finds zero further bodies and zero pins. No
maintained verification runner or runtime test was started.

Inputs: BFME2 e4855174ef; BFME1 pointer
6b9d92bf92debd03e4357462bab41f701651e67c; existing STLport 4.5.3 reference and
unchanged compiler flags. Source/object hashes and relocation lists are in
provider-proof.json; previous owner records are in previous-identities.json.
The 3244-byte refresh is still a separate unfinished reconstruction. This
prerequisite does not claim that routine, its insertion instantiation, its
original class name, or new link/census coverage. Model gpt-6.1-sol; about
thirteen minutes including caller investigation.
