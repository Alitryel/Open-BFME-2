// cl: /MD
// Target evidence: Ghidra starts 0x0046AA69 at 28 bytes. Retail saves this,
// calls the matched destructor at 0x00469DCE (~Rva0046AA69Record), tests delete flag bit 0,
// conditionally calls operator delete at 0x0002FD60, returns this, and ret 4.
// The target object's class identity is unresolved, so keep the type address-derived.
struct Rva0046AA69Record { ~Rva0046AA69Record(); };	// 0x00469DCE, rowed in AudioEventRTSDtor.cpp

class Rva0046AA69 {
public:
	~Rva0046AA69() { ((Rva0046AA69Record *)this)->~Rva0046AA69Record(); }
};

void Rva0046AA69_Delete(Rva0046AA69 *p) { delete p; }
