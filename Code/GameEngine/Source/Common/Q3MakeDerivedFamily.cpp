// Trimmed port of reference/open-bfme-1/Code/GameEngine/Source/Common/
// Q3MakeDerivedFamily.cpp: the Rva007E9B40, Rva007F2E60, Rva007F3410,
// Rva007F40F0 and Rva007FBB20 helpers are carried; the three sibling helpers
// stay with the donor until rows land. See the donor for the full
// multiple-inheritance analysis.

void *Gen007F0130( unsigned int size );

class Q3MakeBaseA
{
public:
	// Pure: every factory's object overrides it, and retail never stores this
	// base's own vftable, so the only reference left is the base vftable the
	// compiler emits, which now names _purecall instead of an undefined slot.
	virtual void primary() = 0;
	static void *operator new( unsigned int size ) { return Gen007F0130( size ); }
};

class Q3MakeBaseB
{
public:
	virtual void secondary();
	void *m_payload;
	Q3MakeBaseB( void *payload ) { m_payload = payload; }
};

class Rva007E9B40Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007E9B40Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva007E9B40Object *Rva007E9B40( void *payload )
{
	return new Rva007E9B40Object( payload );
}

class Rva007F2E60Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007F2E60Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva007F2E60Object *Rva007F2E60( void *payload )
{
	return new Rva007F2E60Object( payload );
}

class Rva007F3410Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007F3410Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva007F3410Object *Rva007F3410( void *payload )
{
	return new Rva007F3410Object( payload );
}

class Rva007F40F0Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007F40F0Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva007F40F0Object *Rva007F40F0( void *payload )
{
	return new Rva007F40F0Object( payload );
}

class Rva007FBB20Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007FBB20Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva007FBB20Object *Rva007FBB20( void *payload )
{
	return new Rva007FBB20Object( payload );
}

// Two more family members (retail 0x0065EC70 and 0x0065E7A0, primary vftables
// 0x00CE23AC / 0x00CE20E4), same shape as the five above.
class Rva0065EC70Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva0065EC70Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva0065EC70Object *Rva0065EC70( void *payload )
{
	return new Rva0065EC70Object( payload );
}

class Rva0065E7A0Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva0065E7A0Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva0065E7A0Object *Rva0065E7A0( void *payload )
{
	return new Rva0065E7A0Object( payload );
}

// Retail 0x00669480 (primary vftable 0x00CE3788), the same shape again.
class Rva007FCF80Object : public Q3MakeBaseA, public Q3MakeBaseB
{
public:
	Rva007FCF80Object( void *payload ) : Q3MakeBaseB( payload ) {}
	virtual void primary();
	virtual void secondary();
};

Rva007FCF80Object *Rva007FCF80( void *payload )
{
	return new Rva007FCF80Object( payload );
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Gen007E9B40@@YAPAURva007E9D70Cached@@PAURva007E9D70Owner@@@Z=?Rva007E9B40@@YAPAVRva007E9B40Object@@PAX@Z")
#pragma comment(linker, "/alternatename:?Gen007F2E60@@YAPAURva007E9DF0Cached@@PAURva007E9DF0Owner@@@Z=?Rva007F2E60@@YAPAVRva007F2E60Object@@PAX@Z")
#pragma comment(linker, "/alternatename:?Gen007F3410@@YAPAURva007E9E30Cached@@PAURva007E9E30Owner@@@Z=?Rva007F3410@@YAPAVRva007F3410Object@@PAX@Z")
#pragma comment(linker, "/alternatename:?Gen007F40F0@@YAPAURva007E9E70Cached@@PAURva007E9E70Owner@@@Z=?Rva007F40F0@@YAPAVRva007F40F0Object@@PAX@Z")

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?secondary@Q3MakeBaseB@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?secondary@Rva007F2E60Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007F2E60Object@@UAEXXZ=??_GGen007F2E30@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007F3410Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007F3410Object@@UAEXXZ=??_GGen007F33E0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007F40F0Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007F40F0Object@@UAEXXZ=??_GGen007F40C0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007FBB20Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007FBB20Object@@UAEXXZ=??_GGen007FBAF0@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007E9B40Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007E9B40Object@@UAEXXZ=??_GGen007E9B10@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?Gen007F2150@@YAPAURva007E9DB0Cached@@PAURva007E9DB0Owner@@@Z=?Rva0065EC70@@YAPAVRva0065EC70Object@@PAX@Z")
#pragma comment(linker, "/alternatename:?Gen007F1C20@@YAPAURva007E9CE0Cached@@PAURva007E9CE0Owner@@@Z=?Rva0065E7A0@@YAPAVRva0065E7A0Object@@PAX@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva0065EC70Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva0065EC70Object@@UAEXXZ=??_GGen007F2120@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva0065E7A0Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva0065E7A0Object@@UAEXXZ=??_GGen007FCF50@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?secondary@Rva007FCF80Object@@UAEXXZ=?Get_First_Collected_Object_Internal@CullSystemClass@@IAEPAVCullableClass@@XZ")
#pragma comment(linker, "/alternatename:?primary@Rva007FCF80Object@@UAEXXZ=??_GGen007F1BF0@@UAEPAXI@Z")
