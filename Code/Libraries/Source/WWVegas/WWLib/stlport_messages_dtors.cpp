// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Reconstructed STLport 4.5.3 facet destruction from the vendor layouts and
// retail code. Destructor identities independently follow PE vtable RTTI
// (.?AV?$messages@D@_STL@@ at 0x007BC8C0, .?AV?$messages@G@_STL@@ at
// 0x007BC8EC). Twin of stlport_messages_ctors.cpp: the constructor TU proves
// the _Messages-impl layout (impl pointer at +0x0C, _M_delete flag at its
// +0x04); this TU proves the guarded-release teardown.
// Modified reconstruction; no new address aliases are introduced.
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
namespace _STL {
class _Messages {
public:
 _Messages();
 virtual int do_open(const string&,const locale&) const;
 virtual string do_get(int,int,int,const string&) const;
 virtual wstring do_get(int,int,int,const wstring&) const;
 virtual void do_close(int) const;
 virtual ~_Messages();
 bool _M_delete;
};
messages<char>::~messages() { if (_M_impl && _M_impl->_M_delete) delete _M_impl; }
messages<wchar_t>::~messages() { if (_M_impl && _M_impl->_M_delete) delete _M_impl; }
int _Messages::do_open(const string&, const locale&) const { return -1; }
// ??1_Messages@_STL@@UAE@XZ present-unmatched
_Messages::~_Messages() {}
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?do_get@_Messages@_STL@@UBE?AV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@HHHABV32@@Z=?bfmeGoDQE@BfmeThingDQE@@QAEPAVBfmeOtherDQE@@PAV2@PAX111@Z")
#pragma comment(linker, "/alternatename:?do_get@_Messages@_STL@@UBE?AV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@2@HHHABV32@@Z=?bfmeGoDQD@BfmeThingDQD@@QAEPAVBfmeOtherDQD@@PAV2@PAX111@Z")
#pragma comment(linker, "/alternatename:?do_close@_Messages@_STL@@UBEXH@Z=?imbue@?$basic_streambuf@GV?$char_traits@G@_STL@@@_STL@@MAEXABVlocale@2@@Z")
