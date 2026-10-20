# Shroud: real notification-helper visibility

Target remains `?onComingOutOfShroud@Drawable@@AAEXXZ`,
0x0027893E..0x00278C29, 747 bytes. The clean 740-byte bank is unchanged.
Inputs: master `1c014bb0f2`, BFME 1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`.

The existing bank and both October 20 handoffs were read before this test.
Unlike the earlier nearest-object visibility control, these four isolated
sources combine the bank with its actual lazy-helper home and the actual
status/notification providers. No prototype-only replacement, fabricated
callee or new pin is used.

| Visible native code | Parent | Complete providers |
| --- | ---: | --- |
| Existing lazy-helper home | 740 B | 119 B helper and its existing EH rows exact |
| Also status query 270260 | 740 B | 22 B status query also exact |
| Also notification 2706A8 | 740 B | 72 B notification and 31 B callback also exact |
| Both providers | 740 B | All of the above exact |

All four raw parent byte arrays are identical. Thus real provider visibility
and actual storage for the status bytes do not explain the holder/template
allocation mismatch. The notification callback retains its independently
verified Object-to-Drawable lookup and +445 flag store. No declaration layout
or source-body fact was inferred merely from matching width.

No production source, row, pin or bank changed. The scratch integration driver
and normal mismatch outputs are in
`build/shroud-real-notification-context-oct20{.py,/}`. About five minutes of
review, integration and verification; model gpt-6.
