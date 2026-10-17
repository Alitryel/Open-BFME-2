// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport

#include <fstream>
// bfme link decl-only begin
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_allocate_buffers(unsigned short *, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_init(bool); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_seek_return(long, int); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_input_mode(); }
namespace _STL { template <> bool basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_switch_to_output_mode(); }
namespace _STL { template <> unsigned short basic_filebuf<unsigned short, char_traits<unsigned short> >::_M_underflow_aux(); }
namespace _STL { template <> basic_filebuf<unsigned short, char_traits<unsigned short> > * basic_filebuf<unsigned short, char_traits<unsigned short> >::open(char const *, int); }
namespace _STL { template <> fpos<int> basic_filebuf<unsigned short, char_traits<unsigned short> >::seekpos(fpos<int>, int); }
// bfme link decl-only end

template class _STL::basic_filebuf<wchar_t, _STL::char_traits<wchar_t> >;
