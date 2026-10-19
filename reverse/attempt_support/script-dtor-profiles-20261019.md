# Script destructor compiler comparison

Target: `0x003B35B1..0x003B3662`, 177 bytes, `Script::~Script`.
BFME2 input: `95f0f83963`; proposed BFME1 input: `f52d3a5cb419`.

Read the complete existing bank, `ScriptDtor.cpp`, previous attempt-log
entries, and the BFME1/ZH destructor definitions. The donor definitions
establish the owned condition/action lifetime role, but have different
layouts and destruction lowering; their identities do not prove BFME2 bytes.

New hypothesis: the authenticated MSVC 7.1 SP1 or DDK 4035 optimizer might
schedule the pointer increment differently from RTM. Compiled the unchanged
bank with `/O1 /MD /EHsc` using the supported `// compiler:` profiles and
`tools/explain_mismatch.py`. All three emit the same resolved 177-byte body:
no masked bytes and no unresolved relocations. Each differs at offsets
68 through 88 and 90. The first difference is `+0x44`: the candidate hoists
`add edi,4` before the null test; retail advances the cursor after deletion.
All other bytes agree. Changing compiler release does not fix this window.

Best candidate remains `reverse/attempts/0x003b35b1.cpp`, unchanged. Its
historical score comments are not a current byte-match claim. Earlier
loop/control-flow and helper trials remain applicable; no replay of those
trials and no production source, ledger, or pin change was made here.
The next useful hypothesis must affect instruction scheduling while retaining
the native null branch, receiver/counter registers, and exact EH graph.

Reproduce for each profile by copying the bank to an ignored `build/` file,
adding `// compiler: vc71-sp1` or `// compiler: vc71-ddk-4035` (omit for RTM),
and running `python tools/explain_mismatch.py '??1Rva003B35B1@@UAE@XZ'
--rva 0x003B35B1 --size 177 --source <scratch-file>`.
