# Audio-cache iterator false reject

At the revision and index recorded in `evidence.json`, a local typed tree/list
iterator comparison repair in `Rva000A7E9E.cpp` removed two conflicting external
comparison copies. All retained COMDAT bodies, extents and relocations remained
identical. Normalized nondebug sections changed only for those two unreferenced
comparison copies, replaced by private typed comparisons.

`./build.sh Code/Libraries/Source/WWVegas/WWLib/Rva000A7E9E.cpp` accepted nine of
ten rows, but refused `uw_00760bc6`: its existing `object-symbol=$L7970` label no
longer existed. MSVC renumbered that same section 191, offset zero, to `$L7996`.
The whole normalized section and its relocations are unchanged. The local-label
binding is recorded in the JSON alongside object hashes and the exact helper
section deltas. This is a false-reject lead for the verifier tooling lane.

The attempted change added the established static typed `operator!=` overloads
for `_Rb_tree_iterator<Value, LeftTraits/RightTraits>` and
`_List_iterator<Value, LeftTraits/RightTraits>` immediately after `<list>`;
both return `a._M_node != b._M_node`. No ledger label, check or baseline was
changed. Source and cached object plus dependency receipt were restored, and the
file claim released. Scratch before/after objects remain under
`build/audio-cache-iterator-link-20261015/` in this checkout. No link or byte gain
is claimed. The independent tree `insert_unique` conflict remains unresolved.
