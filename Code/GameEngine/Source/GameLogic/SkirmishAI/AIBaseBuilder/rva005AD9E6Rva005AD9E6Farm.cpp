// ?rva005AD9E6@Rva005AD9E6@@QAEHXZ
// ?rva005AD9E6@Rva005AD9E6@@QAEHXZ
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva005AD9E6@Rva005AD9E6@@QAEHXZ
// ?rva005AD9E6@Rva005AD9E6@@QAEHXZ
// ?rva005AD9E6@Rva005AD9E6@@QAEHXZ
// cl: /O1 /arch:SSE /G7 /MD
// ?rva005AD9E6@Rva005AD9E6@@QAEHXZ @ 0x005AD9E6 25B
// Circular list count: head at [this+0], empty when [head]==head.
// Evidence: caller at 0x005ADB25 in 0x005ADAB2, no callees, honest Rva name.
// Near miss: same 24/25B, only register allocation (head in edx vs ecx,
// cur in ecx vs eax, count in eax vs edx) and branch shape (je+lea vs
// ret+xor+jmp+final mov) differs. Tried /O1 for/while/do (16B), /O2
// do/while/for and definition-order (24B): identical. t=25 model=muse-spark

struct Rva005AD9E6Node
{
	Rva005AD9E6Node *m_next;
};

class Rva005AD9E6
{
public:
	int rva005AD9E6();
private:
	Rva005AD9E6Node *m_head;
};

int Rva005AD9E6::rva005AD9E6()
{
	Rva005AD9E6Node *head = m_head;
	Rva005AD9E6Node *cur = head->m_next;
	int result;
	if (1 ? cur == head : cur == head) {
		_ReadWriteBarrier();
		result = 0;
	} else {
		int n = 0;
		while (cur != head) {
			cur = cur->m_next;
			++n;
		}
		_ReadWriteBarrier();
		result = n;
	}
	return result;
}
