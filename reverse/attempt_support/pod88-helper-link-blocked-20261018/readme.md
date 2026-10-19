# Remaining Pod88 constructor link blocker

The verified clear-owner prerequisite is committed in `1bf34efd8e`. This
follow-up tried to free the remaining 96-byte constructor and 55-byte push
without retaining the unit's competing helper definitions.

Narrowing the class instantiation to those two members preserved their exact
bytes, but the paired legacy link preview still reported divergent placement,
range-copy, fill and overflow helpers (`link.txt`): no additional linked bytes.

Declaring the existing copy helpers and forwarding the overflow to its rowed
owner changed the compiler's handling of the unused `__false_type` argument.
The constructor changed its frame and the push grew to 58 bytes, past its valid
55-byte extent (`gate.txt`). `trial.diff` preserves that failed experiment.
This is a code-generation blocker, not evidence for increasing the row extent.

The source was restored to `1bf34efd8e` and its byte gate passed again (2/2).
No follow-up source change or additional link gain is claimed. The file and
both body claims were released. A future attempt needs a new, evidence-backed
compiler-shape hypothesis that preserves the native tag lifetime and call ABI.
