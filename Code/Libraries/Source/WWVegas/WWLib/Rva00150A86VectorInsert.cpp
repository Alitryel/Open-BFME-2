// cl: /O1 /G7 /DNDEBUG /MD /EHsc
// Native full5B entry unconditionally forwards unchanged this and three stack arguments to rowed76-byte-element fill-insert150959. STLport4.5.3 _vector.h supplies count-insert semantics; enclosing owner name remains address-derived because the callee itself retains that uncertainty. No added pins or layout assumptions.
// Reference revision: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d.
struct Rva001504A1Record;
class Rva0014F699;
class Rva00150959 {public:void rva00150959(Rva001504A1Record*,unsigned,const Rva0014F699&);};
class Rva00150A86 {public:void insert(Rva001504A1Record*,unsigned,const Rva0014F699&);};
void Rva00150A86::insert(Rva001504A1Record *p,unsigned n,const Rva0014F699 &v){reinterpret_cast<Rva00150959*>(this)->rva00150959(p,n,v);}
