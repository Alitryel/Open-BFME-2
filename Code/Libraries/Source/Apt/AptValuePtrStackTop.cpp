// cl: /MD
// AptValuePtrStack<AptValue>::top @0x006DE160 53B and ::at @0x006DCC10 66B.
// top returns the top element m_aElements[m_nElements-1] of the Apt value ptr
// stack from _AptValuePtrStack.h, asserting m_nElements - nPos > 0 at line
// 0x89 via the shared Apt assert triple (the nPos text is at()'s, which top()
// inlines with nPos 0). Layout mirrors AptBasePtrStack
// (m_nElements at +0, m_nCapacity at +4, m_aElements at +8). Callers at
// 0x6DF9F4 and 0x70846C consume the top. No donor; retail-shaped.
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *, const char *, int);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
void __debugbreak();
#pragma intrinsic(__debugbreak)

class AptValue;

template <class T>
class AptValuePtrStack
{
public:
	int m_nElements;
	int m_nCapacity;
	T **m_aElements;
	T *top();
	T *at(int nPos);
};

template <class T>
T *AptValuePtrStack<T>::top()
{
	if (!(m_nElements > 0)) {
		g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x89);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return m_aElements[m_nElements - 1];
}

template <class T>
T *AptValuePtrStack<T>::at(int nPos)
{
	if (!(m_nElements - nPos > 0)) {
		g_bfmeAptAssertAtE17734("m_nElements - nPos > 0", "c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\_AptValuePtrStack.h", 0x89);
		if (g_bfmeAptBreakOnAssertAtDDC01C)
			__debugbreak();
	}
	return m_aElements[m_nElements - nPos - 1];
}

template AptValue *AptValuePtrStack<AptValue>::top();
template AptValue *AptValuePtrStack<AptValue>::at(int);
