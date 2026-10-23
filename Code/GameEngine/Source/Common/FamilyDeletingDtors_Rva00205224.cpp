// cl: /MD
// ??_GSequentialScript@@UAEPAXI@Z @0x00205208 28B: scalar deleting dtor calling the
// rowed ??1Rva00205224 0x00205224 then operator delete. Family block
// per §4.3 (public for UAE).

class Xfer;
struct EmitVtableTag;

class SequentialScript
{
public:
    SequentialScript(EmitVtableTag *);
    virtual ~SequentialScript();
protected:
    virtual void loadPostProcess();
public:
    virtual const char *GetSnapshotName();
protected:
    virtual void xfer(Xfer *xfer);
};
// ?<SequentialScript::SequentialScript> absent-from-retail
SequentialScript::SequentialScript(EmitVtableTag *) {}
