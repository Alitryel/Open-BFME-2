// cl: /MD /EHsc
// Clean C++ donor: Open-BFME/Open-BFME-1 2791daf5536e4e2147dc3a4aa25c17816828dd69,
// game/Libraries/Source/STLport/Rva00841180VirtualDispatch.cpp, b1 0x00841180.
// Three donor records fold to the SAME BFME2 address: only one body is claimed.
// Native 0x00013580 has a padded 19B extent. It reads the argument's vbtable,
// adjusts by vbtable+4, pushes the no-free flag 0 and calls vtable slot zero.
// Native virtual-inheritance destructor syntax reproduces those operations.
// The ABI/accesses are target facts. Destructor spelling is the donor/ABI
// interpretation; original stream specialization and class identity are not
// recovered. The type and function names use the target address, so none of
// the folded donor names is claimed as an original BFME2 name.

class Rva00013580Base
{
public:
    virtual ~Rva00013580Base();
};

class Rva00013580Owner : public virtual Rva00013580Base
{
};

void rva00013580Dispatch(Rva00013580Owner *object)
{
    object->~Rva00013580Owner();
}

