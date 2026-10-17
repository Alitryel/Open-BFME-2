# Authored COM dispatch and exception-info recovery

Eight routines move from the prebuilt MSVC 7.1 COM support archive to real C++: 624 C++-exact bytes. Total byte coverage is unchanged; these bytes were previously library-backed. Four independently verified data rows cover another 52 bytes (three GUIDs and one callback pointer).

| Routine | Retail RVA | Complete bytes |
| --- | --- | ---: |
| `_set_com_error_handler` | `00654B10` | 12 |
| `_com_issue_error` | `00654B20` | 16 |
| `_com_issue_errorex` | `00654B30` | 110 |
| `_com_dispatch_method` | `00654BA0` | 73 |
| `_com_dispatch_propget` | `00654BF0` | 35 |
| `_com_dispatch_propput` | `00654C20` | 104 |
| `_com_error::WCodeToHRESULT` | `006554E0` | 26 |
| `_com_handle_excepinfo` | `00655500` | 248 |

The existing `Release\comsupp.obj` and `Release\invkerr.obj` mangled symbols establish function and ABI identities independently of the byte match. The implementation was authored from retail and those native-object identities. No Microsoft implementation source was read or copied. The toolchain SDK supplies canonical COM interface, GUID, and EXCEPINFO declarations. The SDK include directory and actual headers were checked, not merely presumed from successful compilation. Normal O2/G7 region defaults suffice; no override, pin, alias, assembly, emitted byte, or naked function was introduced.

The native setter/callback references establish `__errorPfn` at VA `00DD7F28`; its four-byte initializer points to existing `_com_raise_error` at RVA `00654CD0`. QueryInterface/SetGUID uses and the native GUID symbols independently establish IID_ISupportErrorInfo at `00CE0B34`, IID_IErrorInfo at `00CE0B5C`, and IID_IDispatch at `00CE0B6C`. All three sixteen-byte values and the callback relocation pass the normal typed data-row verifier.

The non-instantiated `_com_error` declaration is used only for its static status mapper. The native constructor at `00654C90` writes vptr/long/pointer/pointer at offsets 0/4/8/12, and `_com_raise_error` uses a sixteen-byte stack object. The destructor at `00654D50` releases the interface at +8 and passes the allocation at +12 to LocalFree. The message element type is not established; the view keeps it as an opaque pointer. Constructors, virtual destructor, vftable and RTTI remain supplied by the retained native comraise member; this source emits none of them.

After all eight rows move, the matched-object inventory no longer selects old comsupp or invkerr. A non-executed focused DLL link forces all thirteen recovered COM routines (including the prior ComUtil batch), uses the typed CRT-free provider, and retains only native comraise/invkprxy with normal CRT/Win32/OLE import libraries. It passes with old comsupp/comutil/invkerr omitted. This is a bounded symbol-closure/duplicate-definition check, not a full-game census or runtime test. New-variant previews report no conflicts, final identity checks report no new findings, and affected-source placement scans find no additional body or pin.
