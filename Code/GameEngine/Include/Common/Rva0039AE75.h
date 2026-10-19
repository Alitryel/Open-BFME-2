// Canonical 0x14-byte experience scalar-table view.
// ABI evidence and unresolved original identity: reverse/class_contracts/Rva0039AE75.json.
// Completes the generated header's missing forward declarations and retail virtual slots.
#ifndef CANONICAL_RVA0039AE75_H
#define CANONICAL_RVA0039AE75_H

class Xfer;
class ExperienceScalarTable;
struct Rva0039AE75Owner;
struct EmitVtableTag;

class Rva0039AE75 {
public:
    Rva0039AE75(Rva0039AE75Owner *owner);
    // Existing non-retail table-emission overload in InlineDtorDeletingDtorsC01.cpp.
    Rva0039AE75(EmitVtableTag *);
    virtual ~Rva0039AE75() {}
    float bfmeAt(int value) const;
protected:
    // Native slot 1 is C3 at 000B3FD0: no argument and no recovered original name.
    virtual void rva000B3FD0() {}
    virtual void xfer(Xfer *xfer);
private:
    int indexFor(int value) const;
    Rva0039AE75Owner *m_owner;
    float m_bfmeReal08;
    int m_bfmeValue0C;
    ExperienceScalarTable *m_bfmeTable10;
};

#endif
