// cl: /MD
// Native TexBufferClass destructor 15D0E0 and deleting wrapper 15D7E0.
// Constructors 15D080/15D0C0 install the same vtable BD3CF4; slot 1
// selects the wrapper, which calls this destructor. The base cleanup at
// 15CC90 already has the neutral canonical name BfmeOwnVVE. Its original
// template identity remains unknown; preserve it rather than add an alias.
class RefCountClass
{
public:
    virtual void Delete_This();
};
class BfmeOwnVVE : public RefCountClass
{
public:
    ~BfmeOwnVVE();
};
class TexBufferClass : public BfmeOwnVVE
{
public:
    virtual ~TexBufferClass();
};
TexBufferClass::~TexBufferClass()
{
}
