// cl: /GX-
// ?Rva000752BDGet@@YAHXZ @ 0x000752BD (6B): global dword getter reading
// 0x00E08D30 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape).
// First of a four-deep adjacent run (0x752BD/C3/C9/CF); dedicated TU so no
// caller inlines the load (Rva007EB810Get precedent).

// cpudetect.cpp's private CPUDetectClass statics, read through a TU-scoped
// friend view: real decorations, no alias, no second datum.
class CPUDetectClass
{
	friend int Rva000752BDGet(void);
	friend int Rva000752C3Get(void);
	friend int Rva000752C9Get(void);
	friend int Rva000752CFGet(void);
	enum ProcessorManufacturerType {};
	enum IntelProcessorType {};
	enum AMDProcessorType {};
	static ProcessorManufacturerType ProcessorManufacturer;
	static IntelProcessorType IntelProcessor;
	static AMDProcessorType AMDProcessor;
	static int ProcessorSpeed;
};

int Rva000752BDGet(void)
{
	return CPUDetectClass::ProcessorManufacturer;
}

// ?Rva000752C3Get@@YAHXZ @ 0x000752C3 (6B): same shape over 0x00E08CA8.

int Rva000752C3Get(void)
{
	return CPUDetectClass::IntelProcessor;
}

// ?Rva000752C9Get@@YAHXZ @ 0x000752C9 (6B): same shape over 0x00E08CF4.

int Rva000752C9Get(void)
{
	return CPUDetectClass::AMDProcessor;
}

// ?Rva000752CFGet@@YAHXZ @ 0x000752CF (6B): same shape over 0x00E08D20.

int Rva000752CFGet(void)
{
	return CPUDetectClass::ProcessorSpeed;
}
