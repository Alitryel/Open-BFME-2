// _$E1
// partial score=1.0 date=2026-10-14
// cl: /O1 /MD
// Native dynamic initializer 0x007ACFB0..0x007ACFBB calls the independently
// recovered bool table generator at 0x001B20E5 and stores AL to VA 0x00DFD8E8.
// That generator is guided by ZH motchan.cpp; BFME1 reference is pinned at
// a7c38d3b2597121f178ab5190b3062478823257d. The result variable's original
// name is unknown. It is distinct from motchan's table_valid at VA 0x00DFCEC0.
// The result slot has one native reference, this byte write. An eventual
// landed provider must own its one-byte zero-initialized slot in data_rows.csv.
bool Rva001B20E5Init();
bool BfmeMotionFilterTableInitializationResult = Rva001B20E5Init();
