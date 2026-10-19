# EBD tree cleanup, 2026-10-19

Whole BfmeConv802.cpp was reviewed, along with BfmeNodeValueEBDDestructor.cpp.
The six existing rows (214 bytes) and both value-provider rows pass official
byte verification. Same-census link preview reports 1/1 source linking.
The 56-byte tree destructor384DEB calls clear383EEA on its receiver and
destroys its one-pointer header on both normal and exceptional exits.
Its native prologue installs handler77FA5F and FuncInfo929E30.
The full associative EH graph places eight-byte cleanup77FA57.

The emitted BfmeHeaderEBD destructor is the entire14-byte conditional free
at7FAB3, including the allocator relocation. This was independently compared
through compile_function before admission; add_match verifies the folded
row through the normal byte and relocation gates. No five-byte wrapper is
substituted for a longer native callee. Original application and payload
identities remain opaque; the header layout follows the native clear/erase.

The earlier attempted handler from StlportRbTreeDtorFamily was withdrawn
for divergent PlayerInfo payload destruction. This independent tree owner
uses its verified node-value provider382879 and mapped-value provider38240F;
both whole bodies were rebuilt. It does not reuse that rejected unit.
The automatic landed log for the header fold initially described the
parent as57B; its exact ledger extent is56B and the row notes correct this.
