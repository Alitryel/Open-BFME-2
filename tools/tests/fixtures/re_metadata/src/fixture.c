/* Synthetic, repository-owned fixture for tools/re_metadata.py round trips.
 *
 * Nothing here is game code. It exists so a fresh Ghidra project can be built
 * from a tiny PE32 whose functions, types, calling conventions and one
 * deliberately fragmented body are known in advance. Build recipe:
 * tools/tests/fixtures/re_metadata/README.md (clang i686-pc-windows-msvc,
 * lld-link, no CRT). The fragmented bodies are hand-written assembly below:
 * clang does not split functions on its own.
 */
typedef unsigned int fx_u32;

typedef enum fx_kind { FX_KIND_NEG = -2, FX_KIND_ZERO = 0, FX_KIND_MAX = 0x7fffffff } fx_kind;

struct fx_point {
	int x;
	int y;
	short z;
	unsigned char tag;
	char pad;
};

struct fx_box {
	struct fx_point lo;
	struct fx_point hi;
	struct fx_box *next;
	fx_kind kind;
	int counts[4];
	fx_u32 id;
};

int _fltused = 0;

volatile int fx_sink;
struct fx_box fx_boxes[2];

__declspec(noinline) int __cdecl fx_add(int a, int b)
{
	return a * 3 + b;
}

__declspec(noinline) short __stdcall fx_scale(struct fx_point *p, int k)
{
	p->x *= k;
	p->y *= k;
	return (short)(p->x + p->y);
}

__declspec(noinline) unsigned int __thiscall fx_box_count(struct fx_box *self, int index)
{
	return (unsigned int)self->counts[index & 3] + self->id;
}

__declspec(noinline) void __cdecl fx_reset(struct fx_box *b)
{
	b->next = 0;
	b->kind = FX_KIND_ZERO;
	b->id = 0;
}

__declspec(noinline) float __cdecl fx_ratio(int a, int b)
{
	return (float)a / (float)(b | 1);
}

__declspec(noinline) int __cdecl fx_sum(int n, ...)
{
	int *p = &n + 1;
	int total = 0;
	while (n-- > 0)
		total += *p++;
	return total;
}

__declspec(noinline) int __cdecl fx_byval(struct fx_point p)
{
	return p.x + p.y;
}

__declspec(noinline) long long __cdecl fx_wide(long long v)
{
	return v * 7;
}

/* fx_frag: a hot part in .text$m and a cold part in .text$z, with fx_mid in
 * .text$n between them. The cold part is reached by a conditional jump.
 * fx_hidden: its tail is reached only through push/ret, which auto-analysis
 * does not follow, so the analysed body is one range and the curated body two.
 * fx_orphan: never referenced, so auto-analysis creates no function for it. */
__asm__(
	".section .text$m,\"xr\"\n"
	".globl _fx_frag\n"
	"_fx_frag:\n"
	"  movl 4(%esp), %eax\n"
	"  testl %eax, %eax\n"
	"  js fx_frag_cold\n"
	"  addl $1, %eax\n"
	"  ret\n"
	".globl _fx_hidden\n"
	"_fx_hidden:\n"
	"  movl 4(%esp), %eax\n"
	"  pushl $fx_hidden_tail\n"
	"  ret\n"
	".section .text$n,\"xr\"\n"
	".globl _fx_mid\n"
	"_fx_mid:\n"
	"  movl 4(%esp), %eax\n"
	"  shll $2, %eax\n"
	"  ret\n"
	".section .text$z,\"xr\"\n"
	"fx_frag_cold:\n"
	"  negl %eax\n"
	"  subl $1, %eax\n"
	"  ret\n"
	"fx_hidden_tail:\n"
	"  xorl $0x55, %eax\n"
	"  ret\n"
	".globl _fx_orphan\n"
	"_fx_orphan:\n"
	"  movl 4(%esp), %eax\n"
	"  imull $13, %eax, %eax\n"
	"  ret\n");

int __cdecl fx_frag(int v);
int __cdecl fx_hidden(int v);
int __cdecl fx_mid(int v);

int __cdecl fx_start(void)
{
	struct fx_point pt = { 1, 2, 3, 4, 0 };
	int r = fx_add(fx_sink, 2);
	r += fx_scale(&fx_boxes[0].lo, r);
	r += (int)fx_box_count(&fx_boxes[1], r);
	fx_reset(&fx_boxes[r & 1]);
	r += (int)fx_ratio(r, 3);
	r += fx_sum(3, r, 2, 1);
	r += fx_byval(pt);
	r += (int)fx_wide(r);
	r += fx_frag(r) + fx_hidden(r) + fx_mid(r);
	fx_boxes[0].next = &fx_boxes[1];
	fx_sink = r;
	return r;
}
