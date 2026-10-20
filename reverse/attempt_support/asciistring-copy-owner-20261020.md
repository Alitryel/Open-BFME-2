# StringBase-flavor AsciiString placement-copy owner

Retail 0002C485 is a complete 45-byte null-guarded placement-copy helper.
Its StringBase<char> copy edge is the established 000365F0 body, witnessed
by existing string-vector and set callers. The template spelling was already
owned at 00142CC0 by a different Buffer-model implementation; the synthetic
dup row borrowed that name through object-symbol metadata.

Define the existing typed AsciiStringCopyConstructAtRva0002C485 interface as
real C++ placement-copy code and make it the row owner. This preserves the
known flavor difference and does not claim an original application spelling.
The existing AsciiString interface/representation is inherited evidence.
No new type, layout, compiler flag, header or pin is introduced. Its redundant
same-address pin and former linker alias are removed.

An isolated trial with the owner's effective compiler settings reproduces
the complete45B code and the entire native EH graph EXACT. That graph places
the genuine compiler cleanup at 0075C98C; its14B body and parent name are
updated to the real emitted owner. Native frame data identifies handler
0075C99A and FuncInfo008FE414. The handler already has a valid owner in the
AsciiString-pair unit and remains unchanged; no second name or coverage claim.

The normal owner/typed-caller byte gate and strict current-object preparation
verify the production sources. Required commit and push hooks remain enabled.
One object alias, one linker alias and one pin are removed, with exactly three
register deletions. This is credited repair with zero new unique retail bytes.
