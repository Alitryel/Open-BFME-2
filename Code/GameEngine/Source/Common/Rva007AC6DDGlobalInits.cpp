// cl: /MD
// File-scope object initializers from the 0x007AC6xx..0x007B67xx initializer
// strip. Each is the compiler's dynamic-initializer shape: ecx = &storage,
// call the rowed default constructor (or init member), then atexit() the
// rowed 10-byte cleanup thunk that destroys the same storage (in
// Rva007B6880Thunks.cpp / Rva007B6A00AtexitThunks.cpp). Same shape as the
// matched 0x007B6760/0x007B6780 and 0x007B6830. The owning TUs are
// unrecovered, so each keeps an honest address name and the storage keeps the
// global its cleanup thunk already names. Retail bytes give every operand.

inline void *operator new(unsigned int, void *where)
{
	return where;
}

extern "C" int __cdecl atexit(void (__cdecl *callback)());

namespace _STL
{
	class ios_base
	{
	public:
		class _Loc_init
		{
		public:
			_Loc_init();
		};
	};
}

struct BfmeUiResourceEntryState;
class Rva005F0152;

class TerrainFXShaderParameterSourceNamespace
{
public:
	TerrainFXShaderParameterSourceNamespace();
};

class Rva000E6350
{
public:
	Rva000E6350();
};

class Rva000FA83B
{
public:
	Rva000FA83B *init();
};

class Rva001F4B01
{
public:
	Rva001F4B01();
};

class Rva004E5610
{
public:
	Rva004E5610();
};

class Rva004ABDC3
{
public:
	Rva004ABDC3();
};

class Rva00502EC6
{
public:
	Rva00502EC6();
};

class Rva005E2237
{
public:
	Rva005E2237();
};

class Rva005E3DE8
{
public:
	Rva005E3DE8();
};

class Rva005F00FB
{
public:
	Rva005F00FB();
};

class Rva003B6831
{
public:
	Rva003B6831();
};

class AptActionInterpreter
{
public:
	AptActionInterpreter();
};

class Rva000FB87B
{
public:
	Rva000FB87B();
};

class Rva000FB8B6
{
public:
	Rva000FB8B6();
};

class Rva00579731
{
public:
	Rva00579731();
};

class Rva0057A4E7
{
public:
	Rva0057A4E7();
};

extern unsigned g_Va00DEBC64;
void __cdecl rva007B6DFA();

// ?rva007AC6DD@@YAXXZ @0x007AC6DD 22B: ctor 0x000E188F on &g_Va00DEBC64, atexit(0x007B6DFA).
void rva007AC6DD()
{
	new (&g_Va00DEBC64) TerrainFXShaderParameterSourceNamespace;
	atexit(rva007B6DFA);
}

extern unsigned g_Va00DEBC98;
void __cdecl rva007B6E18();

// ?rva007AC747@@YAXXZ @0x007AC747 22B: ctor 0x000E6350 on &g_Va00DEBC98, atexit(0x007B6E18).
void rva007AC747()
{
	new (&g_Va00DEBC98) Rva000E6350;
	atexit(rva007B6E18);
}

extern unsigned g_Va00DEC0E0;
void __cdecl rva007B6ED6();

// ?rva007AC910@@YAXXZ @0x007AC910 22B: init 0x000FA83B on &g_Va00DEC0E0, atexit(0x007B6ED6).
void rva007AC910()
{
	((Rva000FA83B *)&g_Va00DEC0E0)->init();
	atexit(rva007B6ED6);
}

extern unsigned g_Va00DFDD0C;
void __cdecl rva007B7588();

// ?rva007AD50B@@YAXXZ @0x007AD50B 22B: ctor 0x001F4A40 on &g_Va00DFDD0C, atexit(0x007B7588).
void rva007AD50B()
{
	new (&g_Va00DFDD0C) Rva001F4B01;
	atexit(rva007B7588);
}

extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
void __cdecl rva007B789C();

// ?rva007AE097@@YAXXZ @0x007AE097 22B: ctor 0x004E5610 on &BfmeUiResourceEntryCollectorState, atexit(0x007B789C).
void rva007AE097()
{
	new (&BfmeUiResourceEntryCollectorState) Rva004E5610;
	atexit(rva007B789C);
}

extern unsigned g_00E01E41;
void __cdecl rva007B7C72();

// ?rva007AEC8E@@YAXXZ @0x007AEC8E 22B: ctor 0x0000F740 on &g_00E01E41, atexit(0x007B7C72).
void rva007AEC8E()
{
	new (&g_00E01E41) _STL::ios_base::_Loc_init;
	atexit(rva007B7C72);
}

extern unsigned g_Va00E03CE0;
void __cdecl rva007B89C1();

// ?rva007B1CDC@@YAXXZ @0x007B1CDC 22B: ctor 0x004ABDC3 on &g_Va00E03CE0, atexit(0x007B89C1).
void rva007B1CDC()
{
	new (&g_Va00E03CE0) Rva004ABDC3;
	atexit(rva007B89C1);
}

extern unsigned g_Va00E04508;
void __cdecl rva007B9049();

// ?rva007B342C@@YAXXZ @0x007B342C 22B: ctor 0x00502EC6 on &g_Va00E04508, atexit(0x007B9049).
void rva007B342C()
{
	new (&g_Va00E04508) Rva00502EC6;
	atexit(rva007B9049);
}

extern unsigned g_Va00E0669C;
void __cdecl rva007B993D();

// ?rva007B4FDA@@YAXXZ @0x007B4FDA 22B: ctor 0x005E2237 on &g_Va00E0669C, atexit(0x007B993D).
void rva007B4FDA()
{
	new (&g_Va00E0669C) Rva005E2237;
	atexit(rva007B993D);
}

extern unsigned g_Va00E06710;
void __cdecl rva007B9947();

// ?rva007B5000@@YAXXZ @0x007B5000 22B: ctor 0x005E3D95 on &g_Va00E06710, atexit(0x007B9947).
void rva007B5000()
{
	new (&g_Va00E06710) Rva005E3DE8;
	atexit(rva007B9947);
}

extern Rva005F0152 Rva00A06858;
void __cdecl rva007B99B5();

// ?rva007B51EB@@YAXXZ @0x007B51EB 22B: ctor 0x005F005B on &Rva00A06858, atexit(0x007B99B5).
void rva007B51EB()
{
	new (&Rva00A06858) Rva005F00FB;
	atexit(rva007B99B5);
}

extern unsigned g_Va00E06E60;
void __cdecl rva007B9A37();

// ?rva007B53D4@@YAXXZ @0x007B53D4 22B: ctor 0x003B6831 on &g_Va00E06E60, atexit(0x007B9A37).
void rva007B53D4()
{
	new (&g_Va00E06E60) Rva003B6831;
	atexit(rva007B9A37);
}

extern unsigned g_Va00E182E0;
void __cdecl rva007B9C50();

// ?rva007B67A0@@YAXXZ @0x007B67A0 22B: ctor 0x006FE980 on &g_Va00E182E0, atexit(0x007B9C50).
void rva007B67A0()
{
	new (&g_Va00E182E0) AptActionInterpreter;
	atexit(rva007B9C50);
}

extern unsigned g_Va00DDEF54;
void __cdecl rva007B6A50();

// ?rva007ABB80@@YAXXZ @0x007ABB80 22B: ctor 0x0000F740 on &g_Va00DDEF54, atexit(0x007B6A50).
void rva007ABB80()
{
	new (&g_Va00DDEF54) _STL::ios_base::_Loc_init;
	atexit(rva007B6A50);
}

extern unsigned g_Va00DEC140;
void __cdecl rva007B6EEA();

// ?rva007AC940@@YAXXZ @0x007AC940 22B: ctor 0x000FB87B on &g_Va00DEC140, atexit(0x007B6EEA).
void rva007AC940()
{
	new (&g_Va00DEC140) Rva000FB87B;
	atexit(rva007B6EEA);
}

extern unsigned g_Va00DEC174;
void __cdecl rva007B6EF4();

// ?rva007AC956@@YAXXZ @0x007AC956 22B: ctor 0x000FB8B6 on &g_Va00DEC174, atexit(0x007B6EF4).
void rva007AC956()
{
	new (&g_Va00DEC174) Rva000FB8B6;
	atexit(rva007B6EF4);
}

extern unsigned g_Va00E0631C;
void __cdecl rva007B94C8();

// ?rva007B4100@@YAXXZ @0x007B4100 22B: ctor 0x00579C52 on &g_Va00E0631C, atexit(0x007B94C8).
void rva007B4100()
{
	new (&g_Va00E0631C) Rva00579731;
	atexit(rva007B94C8);
}

extern unsigned g_Va00E06360;
void __cdecl rva007B94D2();

// ?rva007B4116@@YAXXZ @0x007B4116 22B: ctor 0x0057AA45 on &g_Va00E06360, atexit(0x007B94D2).
void rva007B4116()
{
	new (&g_Va00E06360) Rva0057A4E7;
	atexit(rva007B94D2);
}

// Atexit-only initializers: a file-scope object whose constructor is trivial
// but whose destructor is not compiles to just atexit(cleanup thunk).

void __cdecl Rva007B6890();

// ?rva007AB8C0@@YAXXZ @0x007AB8C0 12B: atexit(0x007B6890).
void rva007AB8C0()
{
	atexit(Rva007B6890);
}

void __cdecl rva007B6B73();

// ?rva007ABE93@@YAXXZ @0x007ABE93 12B: atexit(0x007B6B73).
void rva007ABE93()
{
	atexit(rva007B6B73);
}

void __cdecl rva007B700A();

// ?rva007ACC9A@@YAXXZ @0x007ACC9A 12B: atexit(0x007B700A).
void rva007ACC9A()
{
	atexit(rva007B700A);
}

void __cdecl rva007B7230();

// ?rva007ACE70@@YAXXZ @0x007ACE70 12B: atexit(0x007B7230).
void rva007ACE70()
{
	atexit(rva007B7230);
}

void __cdecl rva007B781A();

// ?rva007ADFB2@@YAXXZ @0x007ADFB2 12B: atexit(0x007B781A).
void rva007ADFB2()
{
	atexit(rva007B781A);
}

void __cdecl rva007B7824();

// ?rva007ADFBE@@YAXXZ @0x007ADFBE 12B: atexit(0x007B7824).
void rva007ADFBE()
{
	atexit(rva007B7824);
}

void __cdecl rva007B7CD7();

// ?rva007AEDCB@@YAXXZ @0x007AEDCB 12B: atexit(0x007B7CD7).
void rva007AEDCB()
{
	atexit(rva007B7CD7);
}

void __cdecl rva007B92A2();

// ?rva007B3A22@@YAXXZ @0x007B3A22 12B: atexit(0x007B92A2).
void rva007B3A22()
{
	atexit(rva007B92A2);
}

void __cdecl rva007B981A();

// ?rva007B4C64@@YAXXZ @0x007B4C64 12B: atexit(0x007B981A).
void rva007B4C64()
{
	atexit(rva007B981A);
}

void __cdecl rva007B9BA0();

// ?rva007B6190@@YAXXZ @0x007B6190 12B: atexit(0x007B9BA0).
void rva007B6190()
{
	atexit(rva007B9BA0);
}

void __cdecl rva007B9BB0();

// ?rva007B6600@@YAXXZ @0x007B6600 12B: atexit(0x007B9BB0).
void rva007B6600()
{
	atexit(rva007B9BB0);
}

void __cdecl rva007B9BD0();

// ?rva007B6630@@YAXXZ @0x007B6630 12B: atexit(0x007B9BD0).
void rva007B6630()
{
	atexit(rva007B9BD0);
}

void __cdecl rva007B9BE0();

// ?rva007B6670@@YAXXZ @0x007B6670 12B: atexit(0x007B9BE0).
void rva007B6670()
{
	atexit(rva007B9BE0);
}

void __cdecl rva007B9C00();

// ?rva007B6680@@YAXXZ @0x007B6680 12B: atexit(0x007B9C00).
void rva007B6680()
{
	atexit(rva007B9C00);
}

// PointGroupClass::transformed_loc (VA 0x00DF709C, read and resized by
// 0x0017E920) is a VectorClass<Vector3> built empty by the rowed
// (int, const Vector3 *) constructor 0x000F0D2F and destroyed by the rowed
// cleanup 0x007B73C0. Only the declarations the call sites need are given.
class Vector3;
template <class T> class VectorClass
{
public:
	VectorClass(int size = 0, T const *array = 0);
	virtual ~VectorClass();
};
void rva007ACF00();
class PointGroupClass
{
	friend void rva007ACF00();
	static VectorClass<Vector3> transformed_loc;
};
void __cdecl Rva007B73C0();

// ?rva007ACF00@@YAXXZ @0x007ACF00 26B: VectorClass<Vector3>(0, 0) on
// PointGroupClass::transformed_loc, atexit(0x007B73C0).
void rva007ACF00()
{
	new (&PointGroupClass::transformed_loc) VectorClass<Vector3>(0, 0);
	atexit(Rva007B73C0);
}
