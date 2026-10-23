# Name the two existing window providers

The exact script `createWindow` at 0x00316BD2 calls the 12-byte setter at
0x0031404A with `WinInstanceData::m_id`, and the Apt component creator at
0x004115A9 calls the same setter with the key derived from the component name.
The same-name donor `GameWindow::winSetWindowId` supplies the purpose; target
stores establish `GameWindow + 0x30 + 4` and the integer-zero return. Rename the
sole address-derived owner to this method and keep it in `GameWindowFields.cpp`.
The old unrelated +0x44 setter remains in its original unit and keeps its name.

The 7-byte getter at 0x0031450A returns the word at GameWindow+0x214. The script
factory then uses that word as a pointer to the four callback-name AsciiStrings,
matching the donor `winGetEditData` purpose. Name its pointer return and field
accordingly. The existing raw-word setter of that field keeps its ABI through
an explicit cast. No second name or alias is added at either address.

All live Code consumers of the two former names are updated: the Apt creator
and the already matched script factory. Normal builds verify all 23 matched
bodies across the four affected sources, with literals and imports checked.
This is a prerequisite identity/linking repair for the joint parseWindow
recovery, not additional C++ byte coverage. It avoids adding pins for names that
would duplicate the existing owners.
