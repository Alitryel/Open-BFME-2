# WorkOrder destructor follow-up, 2026-10-19

Retail WorkOrder vtable VA 00C62E40 contains RVAs 004F1D1C,
000B3FD0, 004F1116 and 004F0716 (four little-endian pointers read
from game.dat). The last two are the rowed WorkOrder literal getter
and WorkOrder::xfer. Constructor 004F10E6 installs this table;
TeamInQueue::xfer allocates 0x30 bytes and calls that constructor.

Rva004F1B56Dtor.cpp instead inherits the three pure Snapshot slots.
Its instruction bytes alone do not establish the complete vtable.
Do not admit handler 00792CB5 from this incomplete model.

class_views found five WorkOrder definitions: WorkOrderCtor,
WorkOrderXfer, TeamInQueueXfer, TeamInQueueBuildPredicates and
AIPlayerTeamBuild. class_contract found 48 bytes but chose no base
and placeholder v00/v01/v02 by majority. These choices do not resolve
the actual Snapshot base witnessed by the destructor's BBB554 store.
The header adoption lane tried data, data+ctor and data+methods;
each passed 0/5 units (C2143, C2273, C2600, C2039). All source trials
were automatically restored. The generated contract and trial logs
are retained under build/resume-oct19-workorder-* as local evidence.

Next repair requires an evidence-backed shared WorkOrder declaration,
its Snapshot slot signature, actual getter and deleting-destructor
owners, and all five consumers checked together. TeamInQueue's
004F05F0 destructor also carries handler 00792CB5 but has the same
incomplete Snapshot-slot issue. No handler was banked here.
