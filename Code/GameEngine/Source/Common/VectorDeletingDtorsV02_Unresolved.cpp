// cl: /O1 /DNDEBUG /MD /EHsc
//
// Vector deleting destructors (??_E), batch V02: 75-byte bodies that, for
// an array delete (flag bit 1), run the eh vector destructor iterator
// (0x00629110) over the count stored before the array with the destructor's
// address and the element size, then free the block from its count word with
// operator delete[] (0x0002FD80); otherwise they call the destructor and free
// through operator delete (0x0002FD60). The element size is the class size.
// Each class's destructor is declared, not defined (pinned); the anchor below
// (no retail counterpart) news an array of each class so this TU emits the
// vector deleting destructor. Owners are opaque unless the destructor already
// carried a ledger name.
//
//   ??_E        dtor        size  vtable#slot
//   0x003A6F85  0x003A6201  0x38  0x00C1BBE0#0
//   0x003A7614  0x003A6201  0x24  0x00C1BC70#0
//   0x003A8681  0x003A9397  0x38  0x00C1BEA0#0
//   0x003A8FAC  0x003A9397  0x24  0x00C1C058#0
//   0x003A9286  0x003A9397  0x28  0x00C1C0C4#0
//   0x003A93D4  0x003A9397  0x50  0x00C1BFB8#0
//   0x00001EAE  0x00001F18  0x08  0x00BBB58C#0
//   0x001F4540  0x003A6201  0x50  0x00BE16C8#0

// Declared so the array path frees through operator delete[] (0x0002FD80)
// as retail does; left undeclared, cl falls back to scalar operator delete.
void operator delete[](void *p);

namespace FXParticleSystem
{
template <int CATEGORY> class CategoryModuleTemplate;
}


class __declspec(novtable) Rva003A6F85VecBase0
{
public:
	virtual ~Rva003A6F85VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A6F85VecBase8
{
public:
	virtual ~Rva003A6F85VecBase8();
private:
	char m_unmodelled_04[0x30 - 0x04];
};

class Rva003A6F85Vec : public Rva003A6F85VecBase0, public Rva003A6F85VecBase8
{
public:
	virtual ~Rva003A6F85Vec();
};

class __declspec(novtable) Rva003A7614VecBase0
{
public:
	virtual ~Rva003A7614VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A7614VecBase8
{
public:
	virtual ~Rva003A7614VecBase8();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003A7614Vec : public Rva003A7614VecBase0, public Rva003A7614VecBase8
{
public:
	virtual ~Rva003A7614Vec();
};

class __declspec(novtable) Rva003A8681VecBase0
{
public:
	virtual ~Rva003A8681VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A8681VecBase8
{
public:
	virtual ~Rva003A8681VecBase8();
private:
	char m_unmodelled_04[0x30 - 0x04];
};

class Rva003A8681Vec : public Rva003A8681VecBase0, public Rva003A8681VecBase8
{
public:
	virtual ~Rva003A8681Vec();
};

class __declspec(novtable) Rva003A8FACVecBase0
{
public:
	virtual ~Rva003A8FACVecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A8FACVecBase8
{
public:
	virtual ~Rva003A8FACVecBase8();
private:
	char m_unmodelled_04[0x1C - 0x04];
};

class Rva003A8FACVec : public Rva003A8FACVecBase0, public Rva003A8FACVecBase8
{
public:
	virtual ~Rva003A8FACVec();
};

class __declspec(novtable) Rva003A9286VecBase0
{
public:
	virtual ~Rva003A9286VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A9286VecBase8
{
public:
	virtual ~Rva003A9286VecBase8();
private:
	char m_unmodelled_04[0x20 - 0x04];
};

class Rva003A9286Vec : public Rva003A9286VecBase0, public Rva003A9286VecBase8
{
public:
	virtual ~Rva003A9286Vec();
};

class __declspec(novtable) Rva003A93D4VecBase0
{
public:
	virtual ~Rva003A93D4VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva003A93D4VecBase8
{
public:
	virtual ~Rva003A93D4VecBase8();
private:
	char m_unmodelled_04[0x48 - 0x04];
};

class Rva003A93D4Vec : public Rva003A93D4VecBase0, public Rva003A93D4VecBase8
{
public:
	virtual ~Rva003A93D4Vec();
};

class Rva00001F18
{
public:
	virtual ~Rva00001F18();
private:
	char m_unmodelled_04[0x8 - 0x04];
};




class __declspec(novtable) Rva001F4540VecBase0
{
public:
	virtual ~Rva001F4540VecBase0();
private:
	char m_unmodelled_04[0x8 - 0x04];
};

// Secondary base at +0x8, proven by the this-adjusting thunk (sub ecx,
// 0x8) to this class's vector deleting destructor in its vtable.
class __declspec(novtable) Rva001F4540VecBase8
{
public:
	virtual ~Rva001F4540VecBase8();
private:
	char m_unmodelled_04[0x48 - 0x04];
};

class Rva001F4540Vec : public Rva001F4540VecBase0, public Rva001F4540VecBase8
{
public:
	virtual ~Rva001F4540Vec();
};

class Rva002B2508
{
public:
	Rva002B2508();
	virtual ~Rva002B2508();
private:
	char m_unmodelled_04[0x2C - 0x04];
};


// ?<bfmeVectorDeleteAnchorV02Unresolved> absent-from-retail
void bfmeVectorDeleteAnchorV02Unresolved()
{
	new Rva003A6F85Vec[2];
	new Rva003A7614Vec[2];
	new Rva003A8681Vec[2];
	new Rva003A8FACVec[2];
	new Rva003A9286Vec[2];
	new Rva003A93D4Vec[2];
	new Rva00001F18[2];
	new Rva001F4540Vec[2];
	new Rva002B2508[2];
}
