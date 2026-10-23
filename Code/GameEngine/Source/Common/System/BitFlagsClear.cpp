// cl: /O2 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
#include <bitset>
// Rehomes the existing clear row at 0x00666E80, not a newly identified function.
// EA's Common/BitFlags.h stores one bitset and delegates clear to reset.
// This limited class view retains that field and implementation. Its prior
// owner had only this verified row plus unrelated naked assembly; the full
// prior source is preserved under reverse/attempt_support/bitflags-clear-owner-20261023/.
// Original reference is GPL-3.0-or-later; this repository retains its license.
template <unsigned int N> class BitFlags {
    _STL::bitset<N> m_bits;
public:
    void clear();
};
template<unsigned int N> void BitFlags<N>::clear() { m_bits.reset(); }
template void BitFlags<116>::clear();
