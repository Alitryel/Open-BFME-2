// cl: /EHsc /MD
// Native RVA 0x62903D is the private type_info copy constructor.
// MSVC 7.1 ti_inst.obj independently supplies this exact symbol and complete
// 11-byte body; the sole vtable relocation is type_info, whose vector deleting
// destructor is rowed at 0x629048. Reconstructed as real C++ using the
// shipped ABI declaration; intentionally does not copy RTTI metadata.
// ABI header/toolchain from pinned BFME1 a7c38d3b2597121f178ab5190b3062478823257d.
#include <typeinfo.h>
type_info::type_info(const type_info&) {}
