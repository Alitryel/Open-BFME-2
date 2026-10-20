# Hero-selection message destructor link blocker

Base44f33aef2a, donor01b84526fc8a43c9dea1cfe6abd0a6859b34eee5,
index5366c4f808. Strict baseline two rows exact,195 unique nonpadding bytes.
Sole blocker: Rva004E7392 deleting destructor. Shared copy in
Rva004E7392Copy.cpp calls an external destructor (28B); this caller's local
empty inline destructor leads to an inline vptr store in its29B deleting copy.

Imported forceinline empty destructor preserves both native rows and every
common COMDAT digest, but removes only ordinary destructor and adds a live
__imp_ destructor reference. Deleting destructor still differs; preview0->0.
Plain external declaration agrees with the shared deleting-copy strategy but
adds explicit normal cleanup to the185B caller, changing branches and bytes;
the real ordinary destructor has no current provider. Neither is a repair.
No pins, import aliases or fabricated vtable slots were added. Full six-slot
retail message/base contract is not represented by these private one-slot
views. A supported class/provider reconciliation must preserve the native
normal-path empty cleanup and direct EH action. Original restored and
reverified; diagnostic gate/preview logs retained; no gain claimed.
