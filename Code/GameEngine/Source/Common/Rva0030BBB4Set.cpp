// ?rva0030BBB4@Rva0030BBB4@@QAEXH@Z, retail 0x0030BBB4, 20 bytes.
// Guarded setter: store int at +0x60 and virtual slot 12 on change.
// Evidence: callers 0x0030C7E6 0x0030C800; prev getter 0x0030BBA9 next Disp8Dword both no-flags.
class Rva0030BBB4
{
public:
	void rva0030BBB4(int v);
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual void v11();
	virtual void notify();

private:
	char m_pad[0x5C];
	int m_val;
};

void Rva0030BBB4::rva0030BBB4(int v)
{
	if (m_val == v)
		return;
	m_val = v;
	notify();
}
