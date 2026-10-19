// cl: /Od /Ob1 /DNDEBUG /MD
// Native 0x000239A0..0x000239C3: ECX receiver, pointer at +4, RET 4.
// STLport _M_terminate_string_aux(false_type) / _M_construct_null source shape,
// from BFME1 6b9d92bf92debd03e4357462bab41f701651e67c inputs/vendor/stlport/stl/_string.h.
// This retains the prior donor-neutral class spelling, not a recovered original name.
// The unused argument's original tag type is unknown; the prior pointer slot is retained.
// Two real inline helper levels generate the twelve-byte frame without padding or asm.
// Evidence: reverse/attempt_support/string-terminator-20261019.md.
struct StringIntegralTag {};
class BfmeStrV57 {
public:
 char *b; char *e; char *c;
 void bfmeTermV57(char *tag);
 void constructNullAux(char *p,const StringIntegralTag &) { *p=0; }
 void constructNull(char *p) { constructNullAux(p,StringIntegralTag()); }
};
void BfmeStrV57::bfmeTermV57(char *tag) { constructNull(e); }
