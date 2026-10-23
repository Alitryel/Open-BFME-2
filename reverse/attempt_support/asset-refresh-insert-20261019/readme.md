# Pending-tree insertion prerequisite

Refresh 0x006227E0 constructs an unsigned key and an element pointer at
0x00622A28/2C, uses CMP/JAE during descent at 0x00622A32/37, and calls
0x00759BC0 at 0x00622A57. These target accesses and the established lifetime
relationship identify its pending-tree insertion independently of a placement.
The original class, record and element names remain unknown. The neutral
Rva00620A00Record view agrees with the corrected destructor provider; it is
not a recovered original type spelling.

Instantiate only the STLport 4.5.3 _M_insert member, preserving the parent's
/O2 /G6 /arch:SSE /EHsc and bfmealloc settings. It emits a complete 180-byte
body and its naturally required 23-byte _Construct pair copy. add_match.py
admits the copy first and then insertion with --icf-owner, through normal
verification. No symbol pins, alias directives, compiler barriers or gate edits are
added. Both bodies already have canonical owners, so this is zero unique
C++ bytes; its purpose is to resolve the actual caller's template identity.

proof.json independently checks all four complete bodies (both new template
instances and their canonical owners), every relocation, resolved retail
hashes, source/object hashes and strict dependency receipts. Normal build.sh
also passes 10/10 rows across the helper, canonical insertion/copy providers
and corrected lifetime provider. The frozen-file check passes. place_bodies
finds zero additional bodies and zero pins. The commit hook performs the
normal identity, data and new-variant checks. No maintained verification
runner or link census was started, and no linked-byte gain is claimed.

With the real admitted helper bindings, the parent still emits 3244/3244
bytes with eight differing displacement operands in its final queue sums;
it is not claimed as matched. The previous diagnostic binding is no longer
needed. The remaining parent investigation is a separate handoff.

Inputs: BFME2 parent a4ef3976c3, pinned BFME1
cf0a80c228583af789772b794ab27abcab2debbf, unchanged STLport 4.5.3 and native
MSVC profile. The incoming reference update changes no compiler/header input
used by this unit. Model gpt-6.1-sol; about ten minutes including the parent
trials and independent fold proof.
