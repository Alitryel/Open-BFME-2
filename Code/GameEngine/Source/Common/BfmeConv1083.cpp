class BfmeS1083
{
public:
	virtual void bfmeSlot1083S_0(void);
	virtual void bfmeSlot1083S_1(void);
};

extern BfmeS1083 *g_bfmeS1083_0;
// g_bfmeS1083_0: matched references place it at VA 0xe1823c (zero-filled .bss).
BfmeS1083 * g_bfmeS1083_0;
extern BfmeS1083 *g_bfmeS1083_1;
// g_bfmeS1083_1: matched references place it at VA 0xe18244 (zero-filled .bss).
BfmeS1083 * g_bfmeS1083_1;
extern BfmeS1083 *g_bfmeS1083_2;
// g_bfmeS1083_2: matched references place it at VA 0xe18240 (zero-filled .bss).
BfmeS1083 * g_bfmeS1083_2;

// ?bfmeGo1083A@@YAXXZ
void bfmeGo1083A(void)
{
	if (g_bfmeS1083_0) {
		g_bfmeS1083_0->bfmeSlot1083S_1();
		g_bfmeS1083_0 = 0;
	}
	if (g_bfmeS1083_1) {
		g_bfmeS1083_1->bfmeSlot1083S_1();
		g_bfmeS1083_1 = 0;
	}
	if (g_bfmeS1083_2) {
		g_bfmeS1083_2->bfmeSlot1083S_1();
		g_bfmeS1083_2 = 0;
	}
}
