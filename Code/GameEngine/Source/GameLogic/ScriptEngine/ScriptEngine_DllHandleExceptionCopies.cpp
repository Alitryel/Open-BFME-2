// cl: /O1 /DNDEBUG /MD /EHsc
// DllHandle exception hierarchy named by catchable-type RTTI at 0x00D11F4C.
// Its two adjacent copy constructors at 0x0020426C and 0x00204285 copy the
// exception base in order, each installing the folded vtable at 0x00BD3B54.

extern "C" const void *const vtbl_00BD3B54[];  // ??_7FunctorNotSet@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BD3B54=??_7FunctorNotSet@@6B@")

class __declspec(dllimport) exception
{
public:
    exception(const exception &other);
    virtual ~exception();
private:
    const char *m_what;
    int m_doFree;
};

class DllHandle
{
public:
    class Exception : public exception
    {
    public:
        Exception(const Exception &other);
        virtual ~Exception();
    };
    class LoadFailure : public Exception
    {
    public:
        LoadFailure(const LoadFailure &other);
    };
};

DllHandle::Exception::Exception(const Exception &other)
    : exception(other)
{
    *(unsigned int *)this = ((unsigned int)vtbl_00BD3B54);
}

DllHandle::LoadFailure::LoadFailure(const LoadFailure &other)
    : Exception(other)
{
    *(unsigned int *)this = ((unsigned int)vtbl_00BD3B54);
}
