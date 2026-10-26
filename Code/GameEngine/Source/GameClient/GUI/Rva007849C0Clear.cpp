// cl: /DNDEBUG /MD /EHsc
//
// Ported from Open-BFME-1 GameEngine/Source/GameClient/GUI/Rva007849C0Clear.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   0x000A9DA8 (28B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// ~Rva00787C20 (0x000AAE59) passes it to for_each over its second
// hash_map<int, 12-byte value> (+0x1C), so it takes the map's pair by reference.
struct Rva007849C0Object
{
    void *m_slot0;
};
struct Gen_t_00786e70_p12cd
{
    Rva007849C0Object *m_object;
    int m_unknown[2];
};
namespace _STL
{
template <class T1, class T2> struct pair { T1 first; T2 second; };
}
void Rva007849C0Clear(_STL::pair<const int, Gen_t_00786e70_p12cd> &entry)
{
    Rva007849C0Object *object = entry.second.m_object;
    if (object)
    {
        object->m_slot0 = 0;
        ::operator delete(object);
    }
    entry.second.m_object = 0;
}
