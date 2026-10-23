// ??0Rva007F0910Record@@QAE@XZ
struct Rva007F0910Record {
	int m_0; int m_4; int m_8; int m_c; int m_10; int m_14; int m_18; int m_1c; int m_20; int m_24; int m_28; int m_2c;
	Rva007F0910Record();
};
Rva007F0910Record::Rva007F0910Record()
	: m_0(0), m_8(-1), m_c(-1), m_10(0), m_14(0), m_18(0), m_1c(0), m_20(0), m_24(0), m_28(0), m_2c(0)
{
}

// ??0Rva0065D760Record@@QAE@XZ (retail 0x0065D760, 47B, two bodies after the
// one above): the same zero/-1 initialisation with two flag bytes at +0x1C.
struct Rva0065D760Record {
	int m_0; int m_4; int m_8; int m_c; int m_10; int m_14; int m_18;
	bool m_1c; bool m_1d; char m_pad1e[2];
	int m_20; int m_24; int m_28; int m_2c;
	Rva0065D760Record();
};
Rva0065D760Record::Rva0065D760Record()
	: m_0(0), m_4(-1), m_8(0), m_c(0), m_10(0), m_14(0), m_18(0), m_1c(true), m_1d(false),
	  m_20(-1), m_24(-1), m_28(0), m_2c(0)
{
}
