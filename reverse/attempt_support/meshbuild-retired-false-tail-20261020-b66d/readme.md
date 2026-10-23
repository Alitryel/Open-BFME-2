# Preserve meshbuild after its sole false placement was retired

Upstream `d61f5c72ef565b39bf1d88d778a18615b628afe8` removed the only ledger row for `Code/Libraries/Source/WWVegas/WW3D2/meshbuild.cpp`: the six-byte `FaceHasherClass::Get_Hash_Value` placement at `0x006C0BC9` was inside the complete 15-byte `BfmeCellFC::rva006C0BC0` body. That commit rows the complete body in `BfmeGridRasterCircle.cpp`; this cleanup does not restore the false identity or claim any replacement bytes.

The retained meshbuild TU then failed full-gate source claims with zero matched rows. No current function or data row refers to it, and no source includes the cpp. Preserve the complete 1,884-line source here as `meshbuild.cpp.txt`, outside the compiled Code tree, for future evidence-based recovery. No whitelist, verifier or baseline is changed.

The file move preserves every byte of the working-tree source at `bb649475aaa6eb54405a990dd66624654eabe06d`. Git blob: `ed0c767b21f74153c91d17aca810ab4a7568fa3c`. SHA-256: `050b6ffe3c93dc0f4cd71d27c3dedeccb61c260f93453952d25d771c67b8f466`. All donor comments, compiler flags, local wrapper adaptations and unmatched markers are retained verbatim. Their presence is historical evidence, not verification of those unclaimed bodies.

The full gate before this cleanup passed 97,366 functions, 1,116 data rows, registry and reference checks; its only failure was this zero-row source. The final publication repeats the normal full gate after the move. This cleanup adds zero exact C++ bytes.
