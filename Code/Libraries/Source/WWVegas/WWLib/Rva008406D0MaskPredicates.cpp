// Address-derived mask-table predicates over unsigned character codes.
struct Rva008406D0MaskTable
{
    unsigned int m_mask;
    const unsigned int *m_table;
    bool doesNotMatch(unsigned char code) const;
};

bool Rva008406D0MaskTable::doesNotMatch(unsigned char code) const
{
    return (m_table[code] & m_mask) == 0;
}
