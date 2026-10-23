# Narrow ifstream link repair handoff

At BFME2 d9fc9093d42cfbdc6a79f6d544de72cfbda40562, the current paired
legacy preview holds 1,640 consumer bytes out of linking. Its two exact helper
providers remain clean (81 + 297 bytes). The census is c2c5ac8c27; no
closed-strict measurement or newly linked bytes are claimed.

Consumer: `Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_ifstream.cpp`.
Providers: sibling `stlport_narrow_filebuf_seek_return.cpp` and
`stlport_narrow_filebuf_overflow.cpp`.

1. Declaration-only specializations of `basic_filebuf<char>::overflow(int_type)`
   and `_M_seek_return(streamoff, mbstate_t)` before the explicit ifstream
   instantiation remove the competing copies, but fail two of fourteen rows:
   seekoff changes register allocation and inlined newline-count scheduling;
   `_M_switch_to_output_mode` stops emitting its rowed body.
2. Keeping the seek-return definition visible using an extern-template
   declaration, and explicitly instantiating `_M_switch_to_output_mode`, still
   fails those same two rows. The mode worker calls its allocation helper where
   retail inlines the page-size rounding and allocation.

Both trials were reverted. `./build.sh` on the original consumer passes 14/14;
no C++ or ledger changes survive. File and all fourteen RVA claims are released.
The seekoff native extent is 0x00014010..0x0001439f (911 bytes); the first log
entry mistakenly said 887 and the next entry corrects it. Do not repeat these
suppression trials without new compiler/inlining evidence.

The attached outputs retain the exact failed bytes and restored gate result.
Model: gpt-6.1-sol. Trial time: 8 minutes.
