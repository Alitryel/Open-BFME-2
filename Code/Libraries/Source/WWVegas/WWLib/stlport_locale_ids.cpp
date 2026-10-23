// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// STLport 4.5.3 src/locale_impl.cpp, _Stl_loc_assign_ids.
// Modified: export under the existing BFME2 caller identity, _Stl_loc_init_facets.
// Retail RVA 0x6F80: the 24 facet-ID stores and their order match upstream.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */
#include <locale>

namespace _STL
{
// Built-in facet IDs and the allocation limit are separate from the
// iterator-facet IDs assigned below. The vendor locale::id is one size_t;
// matched BFME2 DIR32 references independently locate these initialized
// four-byte .data objects. Values are read from retail, not inferred from
// the neighboring facet slots.
size_t locale::id::_S_max = 39;                         // VA 0x00DA61D8
locale::id ctype<char>::id = {2};                       // VA 0x00DA61E0
locale::id codecvt<char, char, mbstate_t>::id = {3};     // VA 0x00DA61E4
locale::id moneypunct<char, true>::id = {4};             // VA 0x00DA61EC
locale::id moneypunct<char, false>::id = {5};            // VA 0x00DA61F0
locale::id numpunct<char>::id = {6};                    // VA 0x00DA61F4
locale::id ctype<wchar_t>::id = {21};                   // VA 0x00DA6200
locale::id codecvt<wchar_t, char, mbstate_t>::id = {22}; // VA 0x00DA61E8
// Verified use_facet bodies at RVAs 0x19990 and 0x19980 pass these
// exact addresses to locale::_M_use_facet; retail initializes them to 23/24.
locale::id moneypunct<wchar_t, true>::id = {23};        // VA 0x00DA6204
locale::id moneypunct<wchar_t, false>::id = {24};       // VA 0x00DA6208
locale::id numpunct<wchar_t>::id = {25};                // VA 0x00DA620C

void _Stl_loc_init_facets() {
  // This assigns ids to every facet that is a member of a category,
  // and also to money_get/put, num_get/put, and time_get/put
  // instantiated using ordinary pointers as the input/output
  // iterators.  (The default is [io]streambuf_iterator.)

  money_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                     = 8;
  money_get<char, const char*>::id._M_index        = 9;
  money_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                     = 10;
  money_put<char, char*>::id._M_index              = 11;

  num_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                       = 12;
  num_get<char, const char*>::id._M_index          = 13;
  num_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                       = 14;
  num_put<char, char*>::id._M_index                = 15;
  time_get<char, istreambuf_iterator<char, char_traits<char> > >::id._M_index                      = 16;
  time_get<char, const char*>::id._M_index         = 17;
  time_put<char, ostreambuf_iterator<char, char_traits<char> > >::id._M_index                      = 18;
  time_put<char, char*>::id._M_index               = 19;

# ifndef _STLP_NO_WCHAR_T

  money_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                  = 27;
  money_get<wchar_t, const wchar_t*>::id._M_index  = 28;
  money_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                  = 29;
  money_put<wchar_t, wchar_t*>::id._M_index        = 30;

  num_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                       = 31;
  num_get<wchar_t, const wchar_t*>::id._M_index    = 32;
  num_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > > ::id._M_index                      = 33;
  num_put<wchar_t, wchar_t*>::id._M_index          = 34;
  time_get<wchar_t, istreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                   = 35;
  time_get<wchar_t, const wchar_t*>::id._M_index   = 36;
  time_put<wchar_t, ostreambuf_iterator<wchar_t, char_traits<wchar_t> > >::id._M_index                   = 37;
  time_put<wchar_t, wchar_t*>::id._M_index         = 38;
  //  messages<wchar_t>::id._M_index                   = 38;
# endif

}

}
