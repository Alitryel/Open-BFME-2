#pragma once

// Accessed views shared by the rowed Squad visitor and compact bodies.
// Gen_0018BC70 remains an address-derived owner; this does not identify its
// pointer element or recover the complete Squad class.
namespace _STL
{
template <class T> class allocator
{
};

template <class T, class A = allocator<T> > class vector
{
public:
	void push_back(const T &value);
	T *erase(T *position);
	T *erase(T *first, T *last);

	T *m_start;
	T *m_finish;
	T *m_end;
};
}

class BfmeItemBF;
class BfmeVisitorBF;

class BfmeVecAK
{
public:
	BfmeItemBF **m_start;
	BfmeItemBF **m_finish;
	BfmeItemBF **m_end;
};

class Gen_0018BC70
{
public:
	BfmeVecAK *bfmeCompact(bool restart);
	void bfmeVisitAll(BfmeVisitorBF *visitor);

private:
	int m_head[4];
	BfmeVecAK m_vector;
};
