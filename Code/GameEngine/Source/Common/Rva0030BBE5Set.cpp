// ?rva0030BBE5@Rva0030BBE5@@QAEXH@Z, retail 0x0030BBE5, 20 bytes.
// Guarded setter: store int at +0x64 and virtual slot 11 on change.
// Evidence: callers 0x0030C7A3 0x003293F3 plus jmp 0x0030BCBA; prev setter 0x0030BBB4 same shape slot12 next Disp8Dword both no-flags.
class Rva0030BBE5
{
public:
	void rva0030BBE5(int v);
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
	virtual void notify();

private:
	char m_pad[0x60];
	int m_val;
};

void Rva0030BBE5::rva0030BBE5(int v)
{
	if (v == m_val)
		return;
	m_val = v;
	notify();
}
