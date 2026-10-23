# Chat recipient prefix recovery, 2026-10-20

Retail body: 0x001EFD9C..0x001EFFC6, 554 bytes, thiscall with three four-byte
argument slots. Best candidate remains 554 bytes with exactly 14 resolved byte
differences: names occupies ebp+0x10 instead of native ebp-0x10; the temporary
ASCII objects occupy the opposite home. All other resolved bytes agree, all
REL32 calls resolve, and the native cleanup order and request offsets agree.
No exact verification or coverage is claimed. Bank: reverse/attempts/0x001efd9c.cpp.

Read all prior verdicts and reverse/attempt_support/efd9c-worker-20261019.md.
This pass removes the old equal-arm isAction selector expression without any
byte regression. The minimal witnessed pointer prefix now supplies begin/end
and size methods; ordinary size()==0 reproduces the native end-minus-begin test.
The complete std::vector<int> type, mutable/const variants and iterator distance
also produce the same 14 differences, but the bank does not assert that complete
type without independent layout evidence. empty() instead produces 549 bytes;
the plain old byte-mask expression without the artifact produces 559 bytes.

Independent hypotheses tested after that improvement:

- Named local return objects, const locals and const references: 555/556 bytes,
  worsen matching; the two return-object lifetimes do not explain the swap.
- /Zi, /Z7, /Zc:forScope, /Ob1 and /Op: unchanged 554/14. /Og-: 1060 bytes.
  Native wchar setting does not emit the requested symbol and is not a result.
- Direct returns and early-empty/combined returns: unchanged 554/14. Early-room
  alone: 570 bytes; assigning success before names cleanup: 553 bytes.
- Factoring real seed formatting and/or recipient appending into force-inlined
  semantic helpers: unchanged 554/14. Plain inline helpers were outlined and
  leave unresolved calls, so are not viable target candidates.

Current identity facts remain those established in the preceding handoff:
native vtable VA0x00C19500 slot64 and WB Chat.cpp callgraph support sendChat;
slots12/22/23/29 and request tag/action/text accesses are target evidence.
The previous BFME1 donor supplies semantic flow, not target layout proof.
The bank's two-pointer prefix and leading PlayerInfo string expose only retail
accesses; full types remain unproven. No pin, Code source, header or gate edited.

Compiler: Windows MSVC13.10.3077, /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB
/D_CRTIMP= /DNDEBUG and local bfme2_ascii headers. BFME1 donor checkout
b3cc6b1588f2fdd4d31ab65199945a837f1f6e9b. BFME2 base supplied in revision.txt.
Per-group measurements and the whole resolved comparison are retained here;
scratch diagnostics and generators remain in build/chat-*-oct20/.
Further work needs a supported explanation of stack-home allocation; replaying
the listed syntax/settings/visibility trials offers no new evidence.
