// ?rva0052AC0F@Rva0052AF1C@@QAEXXZ
// partial score=0.7357142857142858 date=2026-10-14
// ?rva0052AC0F@Rva0052AF1C@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// Native 0052AC0F..0052AC16: MOV ECX,[ECX]; JMP 0052A85D.
// The 45-byte inventory includes the following two 19-byte wrappers.
// Existing Rva0052AF1C constructor 0052AF1C owns the implementation at +0.
// The callee is the unlanded 941-byte WB AptInGameSpellBookInterface::Impl::Update.
class AptInGameSpellBookInterface {
public:
    class Impl { public: void Update(); };
};
class Rva0052AF1C {
public:
    void rva0052AC0F();
private:
    AptInGameSpellBookInterface::Impl *m_impl;
};
void Rva0052AF1C::rva0052AC0F()
{
    m_impl->Update();
}
