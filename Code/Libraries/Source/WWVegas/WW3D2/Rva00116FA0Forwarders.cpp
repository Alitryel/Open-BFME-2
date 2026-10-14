// cl: /DNDEBUG /MD
// Four 5-byte forwarders, each its own int3-padded function in the WW3D2
// run, that tail-jump to an already rowed body with the caller's arguments:
//   0x00116FA0 -> ?Rva00120130Get@@YAHXZ (0x00120130)
//   0x001174C0 -> ?Rva0011CDB0Get@@YAHXZ (0x0011CDB0)
//   0x001174E0 -> ?Rva00174F30Get@@YAHXZ (0x00174F30)
//   0x0012E830 -> ?Sort@@YAXPAUTempIndexStruct@@0@Z (0x0012DCF0)
// No direct caller reaches them in retail; names stay address-derived.
int Rva00120130Get(void);
int Rva0011CDB0Get(void);
int Rva00174F30Get(void);

struct TempIndexStruct;
void Sort(TempIndexStruct *begin, TempIndexStruct *end);

int Rva00116FA0Get(void)
{
	return Rva00120130Get();
}

int Rva001174C0Get(void)
{
	return Rva0011CDB0Get();
}

int Rva001174E0Get(void)
{
	return Rva00174F30Get();
}

void Rva0012E830Sort(TempIndexStruct *begin, TempIndexStruct *end)
{
	Sort(begin, end);
}
