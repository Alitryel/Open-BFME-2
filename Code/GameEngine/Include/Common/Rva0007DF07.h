// Partial layout from reverse/class_contracts/Rva0007DF07.json.
// Retail 7DF07 zeros +4 before installing BC6F20; 4E84A4 restores that
// vptr, whose only slot is deleting destructor 7E5EE. Original names and
// the complete original class hierarchy remain unknown.
#ifndef CANONICAL_RVA0007DF07_H
#define CANONICAL_RVA0007DF07_H

// This storage helper preserves the observed initialization order. It does
// not assert a separately identified retail base class or the word's type.
struct Rva0007DF07Storage {
    unsigned int m_04;
    Rva0007DF07Storage() : m_04(0) {}
};

class Rva0007DF07 : public Rva0007DF07Storage {
public:
    Rva0007DF07() {}
    virtual ~Rva0007DF07() {}
};

#endif // CANONICAL_RVA0007DF07_H
