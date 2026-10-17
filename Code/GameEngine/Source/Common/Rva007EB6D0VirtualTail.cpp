// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Virtual tail-call chain at retail 0x00658660, preceding 0x00658670 (Rva007EB6E0VirtualTail.cpp).

class Rva007EB6D0Object
{
public:
    virtual Rva007EB6D0Object *unused0(void);
    virtual Rva007EB6D0Object *advance(void);
    virtual void unused2(void);
    virtual void tail(void);

    void invoke(void);

private:
    char m_pad0[0x20];
    Rva007EB6D0Object *m_next;
};

void Rva007EB6D0Object::invoke(void)
{
    Rva007EB6D0Object *result = advance();
    result->m_next->tail();
}
