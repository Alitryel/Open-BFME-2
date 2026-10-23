// cl: /O1 /arch:SSE /G7
// BF1 f989 Common/BfmeConv880.cpp is the source expression guide only.
// Native2FE371/17 calls actual2FE193 using receiverword8 and stackword4,
// restores the two cdecl call arguments, and RET4. Its original receiver
// identity and declared result remain unresolved. Object/AI declarations
// reuse the existing actual callee candidate, whose478B provider is not
// rowed; they are not new identity evidence from this wrapper.
class Object;
class AI {
public: static bool rva002FE193(Object *, Object *);
};
// Slot 1 (allow) of partition filter vftable 0x00C071C0.
class Rva002FE371Filter {
public: virtual ~Rva002FE371Filter(); virtual bool allow(Object *argument);
private: unsigned char unknown4[4]; Object *word8;
};
bool Rva002FE371Filter::allow(Object *object)
{
    return AI::rva002FE193(word8, object);
}
