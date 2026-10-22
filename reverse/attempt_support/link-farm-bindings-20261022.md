# Farm-library data bindings, 2026-10-22

BFME2 input 21387ea4c9; published census ae3b3e68e2 (11:05 UTC).
Rva004EA420Init.cpp originally references undefined g_00E04490 and g_00E04494.
The target accesses the string word at VA E04490 and the vector words at
E04494/E04498/E0449C. Existing data owners are g_Va00E04490 (4-byte storage,
constructed as AsciiString in Rva007AB85CAtexitInits.cpp) and
AIEconomyBuilder::m_farmList (AIEconomyBuilderFarmLibrary.h, storage defined
in Rva007B6880Thunks.cpp). The initializer now uses those same owners and
casts the existing storage to its established local views. The shared header
records independent target and WorldBuilder evidence for the farm list.
No additional data, pin, private class or alternate name is introduced.

Same-index current-object legacy preview: 0 -> 206 authored nonpadding bytes,
1/1 unit links. Normal byte gate: 3/3 rows exact, zero skipped string/import
references. Strict reusable byte receipt passes; closure was not checked.
EH graph EXACT; class gate, undeclared-definition check, data checks and
converged-data check pass (10 converged addresses, no second names). These
are self-strict byte checks plus a legacy link preview, not closed-strict or
actual placement gains. Scratch logs: build/link-seat-farm-{before,after,
byte,strict}.txt. Cause sweep found the other farm consumers already use the
canonical owners; only this initializer retained the two undefined aliases.

## Reverted trials

Rva0026E7C8Xfer.cpp (388 authored B): the temporary derived record's destructor
COMDAT differs from the flat +8 member view in Rva003328EDRva003328ED.cpp.
A dllimport/forceinline empty destructor preserves 4/4 rows but emits an
unresolved imported destructor in cleanup; plain forceinline preserves bytes
but retains the conflict. Reconcile the class contract before another trial.

stlport_wide_ios_imbue.cpp (238 B): declaring the rowed char-string assignment
specialization removes the inline self-check/range call (-15 B); importing
a forceinline equivalent materializes a dispatch-tag store (+5 B) and swaps
locale homes. Requires template/compiler-summary reconciliation, not merely
binding a declaration. Both candidates reverted; both blocked verdicts are in
the attempt log and their claims were released.

## Reference freshness and inherited work

Verified BFME1 pointer remains 37c3022de1ab944c7ffe536440d637dc8199091c;
official master fetched at 42bba2ddbd5cb895d99293583891d3b7315fa49e. The
old-pointer full byte baseline waited on the host compiler lock without
compiling for about twelve minutes; only this seat's waiting build was
terminated. No pointer update or success receipt was written. Freshness is
still due. Changed donor sources were inspected; no moved headers/inputs were
silently substituted. The prior layout migration remains applicable.

Current-object probing found 89,022 B already link from other contributors'
repairs; these are not session gains. ControlBar destructor also links when
its already-repaired opaque provider is refreshed. The published census is
older than those sources. rehome_rows cannot run without its census.log input;
no census or maintainer-only runner was started to recreate it.

## Narrow-string initializer consumers

stlport_narrow_string_range_ctors.cpp copied from three undefined StaticEmpty
aliases. Retail calls at 0x17A40/0x17AA0/0x19D30 read storage at VA DDEF08,
DDEEFC and DDEF38. Rva007AB8D0StringInits.cpp already owns these addresses as
g_Va00DDEF08/g_Va00DDEEFC/g_Va00DDEF38 and constructs "true", "false" and "";
Rva007B6880Thunks.cpp already destroys them through the same string view.
The repair binds the consumers to those existing owners, without new data.
The owner's unsigned storage declaration is pre-existing modeling debt.

Same-index legacy preview: 0 -> 367 authored nonpadding bytes, 1/1 unit links,
against ae3b3e68e2. All 8/8 rows byte-exact, five EH graphs EXACT, strict
reusable byte receipt passes. Closure was not checked; this is no claim of
closed-strict or actual placement gain. Frozen-source, class and whitespace
checks pass; converged-data check reports no second names. Scratch logs:
build/link-seat-range-{before,after,byte,strict}.txt.

The shadow data check reports three wrong-name references: committed
reverse/data_ledger.csv still calls the removed, undefined aliases the owner
(defs=0). A scratch-only regeneration, build/link-seat-data-ledger.csv,
selects the three existing initializer owners (defs=1), agreeing with the
existing data_rows. No generated ledger or baseline was edited. That scratch
regeneration also reports missing unrelated objects, so it is not a replacement
full data measurement. Canonical data placement remains unverified here.
The farm commit's shadow hatch counter likewise warned about two references
to its already-owned address-named global; it added no separate datum.

## Screen-effect copy helpers

Moved bfmeReset (0x309E30, 27 B), bfmeCopyTable (0x309E51, 20 B), and
bfmeCopySecond (0x309E6B, 20 B) into the corresponding glow, ring and fire
parser units. The parsers already own each saved/active object. Their target
relocations establish VA DBD7B8/DBD7DC (36 B), DBD800/DBD860 (96 B), and
DBD8C0/DBD918 (88 B); the copy bodies address those same objects. BFME1 donor
6d9434269164392c5ba62aaa7c15a86b5b020d76 supplies the copy semantics; target
bytes and parser relocations independently support these storage bindings.
Names and layouts are preserved, with no new data or pins. Removed the three
rowless standalone helper units and their six undefined data aliases.

Same-index current-object legacy preview: 630 -> 697 authored nonpadding
bytes, +67 B. To measure retirement with the existing index, the three old
units were temporarily compiled as empty translation units alongside the
three updated owners; the final tree deletes those obsolete units. All 12/12
rows in the owners pass the byte gate and strict reusable receipt preparation;
closure was not checked. This is a legacy retirement preview, not evidence of
closed-strict or actual placement gain. Class, frozen-source, CSV, converged
data and whitespace checks pass. Scratch logs are
build/link-seat-effects-{before,after,strict}.txt and
build/link-seat-effects-{reset,ring,fire}-add.txt.

The shadow data check reports two new wrong-name findings for the glow saved
and active objects. The committed data ledger still selects the deleted
undefined aliases as unowned names, while listing the existing parser-local
objects as definitions at those same addresses. Ring/fire storage references
are already baselined. No data ledger or baseline was changed.
