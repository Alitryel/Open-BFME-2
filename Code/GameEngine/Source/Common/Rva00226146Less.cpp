// cl: /MD
// Lead: current BFME1 9cbfb551 RespawnUpdateNewRule.cpp record comparison.
// Native 17097E..17098D follows bounded 170960/30B and returns a full EAX 0/1
// from unsigned receiver-word < argument-word, with ret 4 cleanup.
// Only the raw-word operation and ABI are claimed; record identity is unknown.
class Rva0017097EWord
{
public:
    unsigned int lessThan(const unsigned int *other) const;
    unsigned int m_word;
};
unsigned int Rva0017097EWord::lessThan(const unsigned int *other) const
{
    return m_word < *other;
}
