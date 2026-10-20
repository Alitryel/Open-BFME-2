# String-record instantiation blocker

The banked narrow-instantiation candidate passes all six existing rows, including
the copy constructor's EH handler (273B total). It removes the undefined default
constructor, but leaves the assignment COMDAT/selected blocker and links 0B.

The existing record assignment pin at 26F4F4 names a 163B vector assignment,
currently rowed as vector<Rva0026F4F4Element>::operator=. Existing fill3F1ECE
calls that address; the separately rowed Rva003F1ECEFill implementation correctly
uses a vector assignment over 12B entries. The StringRecord fill template row
shares that address but implies an incompatible scalar/string record assignment.
This requires identity/row reconciliation, not another emission suppression.
The production source is restored, claims released, and the byte-exact trial
retained only as evidence. No link improvement is claimed.

An independent mapper helper repair from this session was dropped during rebase:
upstream 0826e8a906 landed the identical source change first. Do not count its
5,784B as this seat's newly linked bytes.

BFME1 freshness remains pending: verified pointer92f6bbe8e1dcdb46b5d27da0674313efc822b790,
fetched official master01b84526fc8a43c9dea1cfe6abd0a6859b34eee5. Only three
authored sources changed, no headers. Baseline full verification waited for the
shared compiler lock and was interrupted (130); no pointer or success stamp was
updated. Retry verification when the lock is available.
