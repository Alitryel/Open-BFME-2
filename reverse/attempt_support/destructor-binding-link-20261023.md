# Constructor/destructor provider binding

Inputs: BFME 2 `5be8758e8b`, verified BFME 1 donor pointer
`96c88c73a5cd1a58fc2f8db691beea50acd996db`, published census
`0393df10e2` (2026-10-23 19:47). Findings below use BFME 2 retail and
existing BFME 2 providers; no donor identity is promoted.

## Rva006253F0 constructor: verified repair

Retail constructor 6253F0 stores primary table C7C6B0 at +0 and secondary
table C7C6A0 at +0C. Destructor 6254B0 restores the same tables at the
same offsets. Primary slot 0 is deleting destructor 6255B0, which calls
6254B0. The latter already has the ledger owner
`Open2Store880FC0::~Open2Store880FC0`. Bind the constructor view's undefined
destructor to that provider with a TU-local alternatename directive.
Both names remain existing address-derived views; no original class name
or new function identity is asserted. No function bytes or tables change.

Paired legacy preview of Rva006253F0Ctor.cpp and Open2Twins006.cpp:
before 801 B / 1 of 2 units; after 947 B / 2 of 2 units, **+146 B**.
This is a current-object legacy result, not self-strict or closed-strict
closure. Scoped build passes all five constructor-unit rows, including
the three funclets and EH handler. `--prepare-current` also admits its
strict reusable byte receipt. Logs in ignored build/seat-partition-*.txt.

## ExperienceTracker: blocked, trial restored

ExperienceTrackerXfer_ExperienceTracker.cpp is blocked by the undefined
ExperienceTracker destructor and a competing Rva0039ADF3 table. Native
C1AD20 slot 0 reaches 39AD56 via deleting destructor 39AF5A. This supports
binding to the existing neutral base destructor provider, but is insufficient
to reconcile the whole class.

A trial added that binding, a fifth pure base slot, a base xfer binding
and the derived xfer declaration in Rva0039AD56Dtor.cpp. Both units passed
11 byte checks and the legacy preview rose from 156 to 364 B. **The trial
was restored**, because comparing retail tables revealed further omissions:

| Table | Native entries (RVAs) |
| --- | --- |
| C1AD20 base | 39AF5A, 39AC9C, 03B810, 39AFC8, 03B810 |
| C1AD34 object | 39B0F1, 39AC9C, 39ADFE, 39B10D, 39B57F |
| C766A4 auto resolve | 5DB1E8, 39AC9C, 5DAFFE, 5DB074, 5DB145 |

Constructor views currently inherit pure post-load/name slots and the
object view's fifth slot remains pure. The destructor view starts with
only Snapshot's four slots. Replacing these with matching but incomplete
private copies can satisfy the legacy comparator without supplying native
data. Reconcile the full five-slot contract and existing rowed forwarder,
name getter and level-update providers before crediting this repair.
The base forwarder 39AC9C is rowed in VslotSizedForwarders.cpp; the object
name getter 39ADFE in ModuleNameGetters3.cpp; 39B57F has its own tracker TU.
The AutoResolve constructor 5DB08F was foreign-claimed and was not edited.
No failed reconstruction remains in Code/.

The diagnostics are reproducible from current sources and the entries
above; no candidate source is needed to resume. Trial compiler flags were
the existing source `// cl:` flags. Byte receipt logs:
build/seat-tracker-{ctor,dtor}-byte.txt; paired previews:
build/seat-tracker-{before,after}.txt. The +208 B trial is not credited.
