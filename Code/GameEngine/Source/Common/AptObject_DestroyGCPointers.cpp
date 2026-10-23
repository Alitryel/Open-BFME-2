// cl: /MD
// AptObject slot 11 forwards directly to AptValueWithHash slot 11.
// Retail vtables 0x008EA264 and 0x008EA228 establish the two owners.

class AptValueWithHash
{
public:
    virtual void DestroyGCPointers();
};

class AptObject : public AptValueWithHash
{
public:
    virtual void DestroyGCPointers();
};

void AptObject::DestroyGCPointers()
{
    AptValueWithHash::DestroyGCPointers();
}
