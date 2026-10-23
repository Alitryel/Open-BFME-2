// ?GetBuildPlotByIndex@Rva005F05E6@@QAEPAXH@Z @0x005F05E6 16B.
// Indexed load through this+4 then +0x34: returns base[index].
// Unblocks 0x005E2138. TU-local honest-address views.
// cl: /MD
struct Rva005F05E6Mid { char pad[0x34]; void **base; };
struct Rva005F05E6 { char pad[4]; Rva005F05E6Mid *mid; void *GetBuildPlotByIndex(int i); };
void *Rva005F05E6::GetBuildPlotByIndex(int i)
{
    return mid->base[i];
}
