// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00537E7C@WaterArea@@QAEX_N@Z @0x00537E7C 20B bool setter: if m_b2C != v then m_b2C = v plus virtual [eax+0x10].
// Evidence: packet disassembly; caller 0x00537FCC readByte+setne passes bool; sibling WaterArea setters 0x00537F74/0x00537FA0/0x00537E90 on the same this own +0x20/+0x24/+0x28.
class WaterArea
{
public:
	virtual ~WaterArea();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	void rva00537E7C(bool v);

private:
	unsigned char m_pad[0x28];
	bool m_b2C;
};

void WaterArea::rva00537E7C(bool v)
{
	if (v != m_b2C) {
		m_b2C = v;
		v4();
	}
}
