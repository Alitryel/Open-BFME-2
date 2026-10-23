# Allocator trailer: header fields and construction lifetime

Target `?rva006C4730@GeneralAllocatorDebug@@QAEPAXPAXIH@Z`, complete native
`0x006C4730..0x006C4A4E`, 798 bytes including RET12. The queue's 785-byte
inventory prefix and lock-guard identity are not the actual extent or identity.
Inputs: official BFME2 master through `9220c707a6`, BFME1
`b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b`, stock VC7.1 13.10.3077,
unchanged bank `/MD` flags. Read all prior RVA log entries, both existing
20261019 handoffs, the whole current 453-line home and whole home-TU bank.

The unchanged bank still emits 798 bytes with every call resolved, first
difference +0x9B and 18 differing fixed bytes confined to the same six
instruction lines. Nothing below improves that bank.

Twelve new controls use normal `explain_mismatch.py` in isolated build paths:

| Hypothesis | Controls | Result |
| --- | ---: | --- |
| Decode the established header bits as a local union/bit-field view: mapped bit 1, size bits 3..30, other flags preserved | 5 | Numeric/if/ushort-index variants 784 bytes, 605 differing positions; pointer PHI 816 bytes, 624 positions |
| Establish the trailer object's lifetime with standard placement construction of an unsigned short or a one-word footer, using either numeric or pointer capacity | 4 | All 830 bytes; frame changes to 0x540, and the constructor's null check is absent from retail |
| Return a word/footer reference from an inline accessor; assign its word or copy a zero-initialized footer | 3 | All 784 bytes, 605 differing positions |

The construction controls reveal a useful compiler-phase distinction: numeric
placement construction emits retail's exact `and/add4/join/lea -10` sequence
through 0x6C47DD, but inserts `cmp ecx,ebx; je` before the word store. Its
subsequent register/frame changes prevent recovery. This does not justify
removing that check with an invented allocator, annotation or barrier.
The bit-field view and footer type are diagnostic structural inferences from
the target's independently established mask and word store, not recovered
original type names. Native arithmetic, call ABI and trailer width remain
the target facts. No Code, ledger, pin, header or compiler flag changes were
retained. The existing stronger bank remains unchanged.

Replay: copy `allocator-header-lifetime-20261020.py.txt` into `build/` and run
without arguments, then with `construct`, then `reference`. It reads the bank
and writes scratch sources/results under `build/allocator-bitfields-oct20/`.
The compact construction diagnostic is preserved alongside this handoff;
complete logs and result tables remain in the scratch directory. All calls
resolve in every compiled control. About 10 minutes, model gpt-6.1-sol.
