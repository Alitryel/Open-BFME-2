# Clone lifetime partition

At BFME2 15aff98d08, the six verified clone bodies in RvaCloneValueReturns.cpp
were held out by unresolved destructors for Rva005677B9, Rva00574ABB,
Rva005CE259 and Rva005E9742 and competing unproven lifetime COMDATs.
Move those four complete class views and clones to RvaCloneDeferredValueReturns.cpp.
The two remaining owners have existing lifetime providers; no algorithm, flags,
identity, layout, pin, alias, or virtual contract changed. Existing ledger notes
preserve each owner constructor/vtable and hidden-result evidence.

Paired `link_check.py Code/GameEngine/Source/Common/RvaCloneValueReturns.cpp`
against census 268f876e3b (retail-truth-4) changed from 0 to 138 linked bytes.
This is a legacy provider preview, not a measured closed-strict census gain.
The new deferred unit has no position in that census and is not claimed linked.
Both source byte gates pass (2/2 retained and 4/4 deferred), and all definitions
are ledgered. Scoped strict input receipts were prepared for both units.

The BFME1 linking repair review used verified donor 32774ab03393709a7f14331ba8d98d281a55ffd9;
no applicable donor lifetime contract resolved these four address-derived owners.
The existing local-player constructor bank remains relevant for Rva005E9742:
reverse/attempt_support/local-player-ctor-link-20261020/readme.md.
Resume the deferred contracts from retail vtables; do not invent empty dtors.
