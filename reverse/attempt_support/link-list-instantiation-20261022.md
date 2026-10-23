# List instantiation link repair

At BFME 2 `114bba088f`, with published census `08160bc2c9`, narrowed
`stlport_list_opaqueref_erase.cpp` from whole-class instantiation to its
recovered erase, pop_front, pop_back and destructor operations. The destructor
still emits the rowed base destructor and clear worker. Whole-class emission
also instantiated unowned sort/remove operations with undefined element
comparison operators; no comparison implementation or alias was invented.

The same explicit source passed `link_check.py` before and after: 0/168 B
before (unresolved element `operator==` and `operator<`), 168/168 B after.
`./build.sh` verifies all six rows, strings, floats and imports;
`link_check.py --prepare-current` verifies the same six rows and writes strict
reusable receipts. This is a legacy link prediction with self-strict byte
evidence, not a closed-strict gain. Unreferenced allocator diagnostics remain
unchanged. No ledger, pins, dependencies or compiler flags changed.

The cause sweep found `stlport_list_002b4dc1_insert.cpp` already narrowed and
linking on HEAD (133 B, inherited, excluded from the gain). The three
CrateCreationEntryList units remain blocked by non-retail merge/base-constructor
copies as well as undefined comparisons. In particular, the clear unit is the
recorded fold-proof source for list(allocator) and alloc_proxy copy constructors;
do not prune those proof bodies without reconciling their providers and the
sorting-family identity. `StlSweepW4Rva00501B33.cpp` additionally lacks the
element copy constructor/destructor and has a non-retail tree-base constructor.
No changes made to these blocked units.
