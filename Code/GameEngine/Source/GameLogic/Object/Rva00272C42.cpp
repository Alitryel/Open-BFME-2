// cl: /O1 /DNDEBUG /MD
// Retail 0x00272C42..0x00272C5B, a 25-byte RET4 forwarder on the Drawable
// returned by Thing::getDrawable. Native +14C is the pointer to its null-ended
// module array. Forwarding to slot +D4 of its first module is target evidence;
// the original method name and parameter meaning remain unresolved. Caller
// DynamicPortalBehaviour 0x0046129A supplies module-data +138 string bytes.
template <int N> class Rva00272C42Slots : public Rva00272C42Slots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};
template <> class Rva00272C42Slots<0> {};
class Rva00272C42Module : public Rva00272C42Slots<53>
{
public:
    virtual void forward(const char *text) = 0;
};
class Rva00272C42
{
public:
    void rva00272C42(const char *text);
private:
    char pad[0x14C];
    Rva00272C42Module **modules;
};
void Rva00272C42::rva00272C42(const char *text)
{
    // Retail loads the first module through EAX before the virtual tail call.
    Rva00272C42Module *const volatile &entry = *modules;
    Rva00272C42Module *module = entry;
    if (module)
        module->forward(text);
}

// Retail 0x00272C5B..0x00272C74, the RET8 sibling directly after it: the same
// first-module load, forwarding two dword arguments to slot +D8 instead.
// Argument meaning and the method name remain unresolved.
class Rva00272C5BModule : public Rva00272C42Slots<54>
{
public:
    virtual void forward(int a, int b) = 0;
};
class Rva00272C5B
{
public:
    void rva00272C5B(int a, int b);
private:
    char pad[0x14C];
    Rva00272C5BModule **modules;
};
void Rva00272C5B::rva00272C5B(int a, int b)
{
    Rva00272C5BModule *const volatile &entry = *modules;
    Rva00272C5BModule *module = entry;
    if (module)
        module->forward(a, b);
}
