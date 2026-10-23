// DXGetErrorString9A, retail 0x0062B16A, whole 72,878-byte stdcall body.
// Identity, ABI and boundary: original August 2005 DirectX SDK dxerr9.lib,
// member obj\i386\dxerr9.obj; same exported name and complete retail body.
// Microsoft DXUT 2c3ad3ceaf99a7aaff5278dabc2cc952c727d8c1 Core/dxerr.cpp
// (Copyright Microsoft Corporation; MIT License, see license.dxut.txt) supplies
// the semantic switch/return structure only. Every HRESULT and exact literal
// below is independently recovered from the complete bounded retail CFG.
// Original COFF line records prove ordering and case grouping: every recovered
// return offset has an exact original line entry. Macro spellings are unknown.
// 5467 non-default HRESULT cases, 3688 original source groups;
// default is 'Unknown'. Full instruction, jump-table and literal gates
// are required together; matching relocation-masked bytes alone is insufficient.
// Compiler 13.10.4035 is recorded in the original archive CodeView. The
// authenticated Microsoft DDK profile reproduces the complete native body.
// compiler: vc71-ddk-4035
// cl: /O1 /G6 /MT /DNDEBUG /hotpatch /Oy- /GS
// Case groups follow the original object COFF line records.
extern "C" const char * __stdcall DXGetErrorString9A(long hr)
{
    switch (hr)
    {
    // Original object relative source line 6.
    case 0x00000000: return "S_OK";
    // Original object relative source line 7.
    case 0x00000001: return "S_FALSE";
    // Original object relative source line 9.
    case 0x8000FFFF: return "E_UNEXPECTED";
    // Original object relative source line 10.
    case 0x80004001: return "E_NOTIMPL";
    // Original object relative source line 11.
    case 0x8007000E: return "E_OUTOFMEMORY";
    // Original object relative source line 12.
    case 0x80070057: return "E_INVALIDARG";
    // Original object relative source line 13.
    case 0x80004002: return "E_NOINTERFACE";
    // Original object relative source line 14.
    case 0x80004003: return "E_POINTER";
    // Original object relative source line 15.
    case 0x80070006: return "E_HANDLE";
    // Original object relative source line 16.
    case 0x80004004: return "E_ABORT";
    // Original object relative source line 17.
    case 0x80004005: return "E_FAIL";
    // Original object relative source line 18.
    case 0x80070005: return "E_ACCESSDENIED";
    // Original object relative source line 19.
    case 0x8000000A: return "E_PENDING";
    // Original object relative source line 20.
    case 0x80004006: return "CO_E_INIT_TLS";
    // Original object relative source line 21.
    case 0x80004007: return "CO_E_INIT_SHARED_ALLOCATOR";
    // Original object relative source line 22.
    case 0x80004008: return "CO_E_INIT_MEMORY_ALLOCATOR";
    // Original object relative source line 23.
    case 0x80004009: return "CO_E_INIT_CLASS_CACHE";
    // Original object relative source line 24.
    case 0x8000400A: return "CO_E_INIT_RPC_CHANNEL";
    // Original object relative source line 25.
    case 0x8000400B: return "CO_E_INIT_TLS_SET_CHANNEL_CONTROL";
    // Original object relative source line 26.
    case 0x8000400C: return "CO_E_INIT_TLS_CHANNEL_CONTROL";
    // Original object relative source line 27.
    case 0x8000400D: return "CO_E_INIT_UNACCEPTED_USER_ALLOCATOR";
    // Original object relative source line 28.
    case 0x8000400E: return "CO_E_INIT_SCM_MUTEX_EXISTS";
    // Original object relative source line 29.
    case 0x8000400F: return "CO_E_INIT_SCM_FILE_MAPPING_EXISTS";
    // Original object relative source line 30.
    case 0x80004010: return "CO_E_INIT_SCM_MAP_VIEW_OF_FILE";
    // Original object relative source line 31.
    case 0x80004011: return "CO_E_INIT_SCM_EXEC_FAILURE";
    // Original object relative source line 32.
    case 0x80004012: return "CO_E_INIT_ONLY_SINGLE_THREADED";
    // Original object relative source line 33.
    case 0x80004013: return "CO_E_CANT_REMOTE";
    // Original object relative source line 34.
    case 0x80004014: return "CO_E_BAD_SERVER_NAME";
    // Original object relative source line 35.
    case 0x80004015: return "CO_E_WRONG_SERVER_IDENTITY";
    // Original object relative source line 36.
    case 0x80004016: return "CO_E_OLE1DDE_DISABLED";
    // Original object relative source line 37.
    case 0x80004017: return "CO_E_RUNAS_SYNTAX";
    // Original object relative source line 38.
    case 0x80004018: return "CO_E_CREATEPROCESS_FAILURE";
    // Original object relative source line 39.
    case 0x80004019: return "CO_E_RUNAS_CREATEPROCESS_FAILURE";
    // Original object relative source line 40.
    case 0x8000401A: return "CO_E_RUNAS_LOGON_FAILURE";
    // Original object relative source line 41.
    case 0x8000401B: return "CO_E_LAUNCH_PERMSSION_DENIED";
    // Original object relative source line 42.
    case 0x8000401C: return "CO_E_START_SERVICE_FAILURE";
    // Original object relative source line 43.
    case 0x8000401D: return "CO_E_REMOTE_COMMUNICATION_FAILURE";
    // Original object relative source line 44.
    case 0x8000401E: return "CO_E_SERVER_START_TIMEOUT";
    // Original object relative source line 45.
    case 0x8000401F: return "CO_E_CLSREG_INCONSISTENT";
    // Original object relative source line 46.
    case 0x80004020: return "CO_E_IIDREG_INCONSISTENT";
    // Original object relative source line 47.
    case 0x80004021: return "CO_E_NOT_SUPPORTED";
    // Original object relative source line 48.
    case 0x80004022: return "CO_E_RELOAD_DLL";
    // Original object relative source line 49.
    case 0x80004023: return "CO_E_MSI_ERROR";
    // Original object relative source line 50.
    case 0x80040000: return "OLE_E_FIRST";
    // Original object relative source line 51.
    case 0x800400FF: return "OLE_E_LAST";
    // Original object relative source line 52.
    case 0x00040000: return "OLE_S_FIRST";
    // Original object relative source line 53.
    case 0x000400FF: return "OLE_S_LAST";
    // Original object relative source line 55.
    case 0x80040001: return "OLE_E_ADVF";
    // Original object relative source line 56.
    case 0x80040002: return "OLE_E_ENUM_NOMORE";
    // Original object relative source line 57.
    case 0x80040003: return "OLE_E_ADVISENOTSUPPORTED";
    // Original object relative source line 58.
    case 0x80040004: return "OLE_E_NOCONNECTION";
    // Original object relative source line 59.
    case 0x80040005: return "OLE_E_NOTRUNNING";
    // Original object relative source line 60.
    case 0x80040006: return "OLE_E_NOCACHE";
    // Original object relative source line 61.
    case 0x80040007: return "OLE_E_BLANK";
    // Original object relative source line 62.
    case 0x80040008: return "OLE_E_CLASSDIFF";
    // Original object relative source line 63.
    case 0x80040009: return "OLE_E_CANT_GETMONIKER";
    // Original object relative source line 64.
    case 0x8004000A: return "OLE_E_CANT_BINDTOSOURCE";
    // Original object relative source line 65.
    case 0x8004000B: return "OLE_E_STATIC";
    // Original object relative source line 66.
    case 0x8004000C: return "OLE_E_PROMPTSAVECANCELLED";
    // Original object relative source line 67.
    case 0x8004000D: return "OLE_E_INVALIDRECT";
    // Original object relative source line 68.
    case 0x8004000E: return "OLE_E_WRONGCOMPOBJ";
    // Original object relative source line 69.
    case 0x8004000F: return "OLE_E_INVALIDHWND";
    // Original object relative source line 70.
    case 0x80040010: return "OLE_E_NOT_INPLACEACTIVE";
    // Original object relative source line 71.
    case 0x80040011: return "OLE_E_CANTCONVERT";
    // Original object relative source line 72.
    case 0x80040012: return "OLE_E_NOSTORAGE";
    // Original object relative source line 73.
    case 0x80040064: return "DV_E_FORMATETC";
    // Original object relative source line 74.
    case 0x80040065: return "DV_E_DVTARGETDEVICE";
    // Original object relative source line 75.
    case 0x80040066: return "DV_E_STGMEDIUM";
    // Original object relative source line 76.
    case 0x80040067: return "DV_E_STATDATA";
    // Original object relative source line 77.
    case 0x80040068: return "DV_E_LINDEX";
    // Original object relative source line 78.
    case 0x80040069: return "DV_E_TYMED";
    // Original object relative source line 79.
    case 0x8004006A: return "DV_E_CLIPFORMAT";
    // Original object relative source line 80.
    case 0x8004006B: return "DV_E_DVASPECT";
    // Original object relative source line 81.
    case 0x8004006C: return "DV_E_DVTARGETDEVICE_SIZE";
    // Original object relative source line 82.
    case 0x8004006D: return "DV_E_NOIVIEWOBJECT";
    // Original object relative source line 83.
    case 0x80040100: return "DRAGDROP_E_FIRST";
    // Original object relative source line 84.
    case 0x8004010F: return "DRAGDROP_E_LAST";
    // Original object relative source line 85.
    case 0x00040100: return "DRAGDROP_S_FIRST";
    // Original object relative source line 86.
    case 0x0004010F: return "DRAGDROP_S_LAST";
    // Original object relative source line 88.
    case 0x80040101: return "DRAGDROP_E_ALREADYREGISTERED";
    // Original object relative source line 89.
    case 0x80040102: return "DRAGDROP_E_INVALIDHWND";
    // Original object relative source line 90.
    case 0x80040110: return "CLASSFACTORY_E_FIRST";
    // Original object relative source line 91.
    case 0x8004011F: return "CLASSFACTORY_E_LAST";
    // Original object relative source line 92.
    case 0x00040110: return "CLASSFACTORY_S_FIRST";
    // Original object relative source line 93.
    case 0x0004011F: return "CLASSFACTORY_S_LAST";
    // Original object relative source line 95.
    case 0x80040111: return "CLASS_E_CLASSNOTAVAILABLE";
    // Original object relative source line 96.
    case 0x80040112: return "CLASS_E_NOTLICENSED";
    // Original object relative source line 97.
    case 0x80040120: return "MARSHAL_E_FIRST";
    // Original object relative source line 98.
    case 0x8004012F: return "MARSHAL_E_LAST";
    // Original object relative source line 99.
    case 0x00040120: return "MARSHAL_S_FIRST";
    // Original object relative source line 100.
    case 0x0004012F: return "MARSHAL_S_LAST";
    // Original object relative source line 101.
    case 0x80040130: return "DATA_E_FIRST";
    // Original object relative source line 102.
    case 0x8004013F: return "DATA_E_LAST";
    // Original object relative source line 103.
    case 0x00040130: return "DATA_S_FIRST";
    // Original object relative source line 104.
    case 0x0004013F: return "DATA_S_LAST";
    // Original object relative source line 105.
    case 0x80040140: return "VIEW_E_FIRST";
    // Original object relative source line 106.
    case 0x8004014F: return "VIEW_E_LAST";
    // Original object relative source line 107.
    case 0x00040140: return "VIEW_S_FIRST";
    // Original object relative source line 108.
    case 0x0004014F: return "VIEW_S_LAST";
    // Original object relative source line 110.
    case 0x80040150: return "REGDB_E_FIRST";
    // Original object relative source line 111.
    case 0x8004015F: return "REGDB_E_LAST";
    // Original object relative source line 112.
    case 0x00040150: return "REGDB_S_FIRST";
    // Original object relative source line 113.
    case 0x0004015F: return "REGDB_S_LAST";
    // Original object relative source line 115.
    case 0x80040151: return "REGDB_E_WRITEREGDB";
    // Original object relative source line 116.
    case 0x80040152: return "REGDB_E_KEYMISSING";
    // Original object relative source line 117.
    case 0x80040153: return "REGDB_E_INVALIDVALUE";
    // Original object relative source line 118.
    case 0x80040154: return "REGDB_E_CLASSNOTREG";
    // Original object relative source line 119.
    case 0x80040155: return "REGDB_E_IIDNOTREG";
    // Original object relative source line 120.
    case 0x80040160: return "CAT_E_FIRST";
    // Original object relative source line 121.
    case 0x80040161: return "CAT_E_LAST";
    // Original object relative source line 124.
    case 0x80040164: return "CS_E_FIRST";
    // Original object relative source line 125.
    case 0x8004016F: return "CS_E_LAST";
    // Original object relative source line 127.
    case 0x80040165: return "CS_E_NOT_DELETABLE";
    // Original object relative source line 128.
    case 0x80040166: return "CS_E_CLASS_NOTFOUND";
    // Original object relative source line 129.
    case 0x80040167: return "CS_E_INVALID_VERSION";
    // Original object relative source line 130.
    case 0x80040168: return "CS_E_NO_CLASSSTORE";
    // Original object relative source line 131.
    case 0x80040169: return "CS_E_OBJECT_NOTFOUND";
    // Original object relative source line 132.
    case 0x8004016A: return "CS_E_OBJECT_ALREADY_EXISTS";
    // Original object relative source line 133.
    case 0x8004016B: return "CS_E_INVALID_PATH";
    // Original object relative source line 134.
    case 0x8004016C: return "CS_E_NETWORK_ERROR";
    // Original object relative source line 135.
    case 0x8004016D: return "CS_E_ADMIN_LIMIT_EXCEEDED";
    // Original object relative source line 136.
    case 0x8004016E: return "CS_E_SCHEMA_MISMATCH";
    // Original object relative source line 138.
    case 0x80040170: return "CACHE_E_FIRST";
    // Original object relative source line 139.
    case 0x8004017F: return "CACHE_E_LAST";
    // Original object relative source line 140.
    case 0x00040170: return "CACHE_S_FIRST";
    // Original object relative source line 141.
    case 0x0004017F: return "CACHE_S_LAST";
    // Original object relative source line 143.
    case 0x80040180: return "OLEOBJ_E_FIRST";
    // Original object relative source line 144.
    case 0x8004018F: return "OLEOBJ_E_LAST";
    // Original object relative source line 145.
    case 0x00040180: return "OLEOBJ_S_FIRST";
    // Original object relative source line 146.
    case 0x0004018F: return "OLEOBJ_S_LAST";
    // Original object relative source line 148.
    case 0x80040181: return "OLEOBJ_E_INVALIDVERB";
    // Original object relative source line 149.
    case 0x80040190: return "CLIENTSITE_E_FIRST";
    // Original object relative source line 150.
    case 0x8004019F: return "CLIENTSITE_E_LAST";
    // Original object relative source line 151.
    case 0x00040190: return "CLIENTSITE_S_FIRST";
    // Original object relative source line 152.
    case 0x0004019F: return "CLIENTSITE_S_LAST";
    // Original object relative source line 153.
    case 0x800401A0: return "INPLACE_E_NOTUNDOABLE";
    // Original object relative source line 154.
    case 0x800401A1: return "INPLACE_E_NOTOOLSPACE";
    // Original object relative source line 156.
    case 0x800401AF: return "INPLACE_E_LAST";
    // Original object relative source line 157.
    case 0x000401A0: return "INPLACE_S_FIRST";
    // Original object relative source line 158.
    case 0x000401AF: return "INPLACE_S_LAST";
    // Original object relative source line 159.
    case 0x800401B0: return "ENUM_E_FIRST";
    // Original object relative source line 160.
    case 0x800401BF: return "ENUM_E_LAST";
    // Original object relative source line 161.
    case 0x000401B0: return "ENUM_S_FIRST";
    // Original object relative source line 162.
    case 0x000401BF: return "ENUM_S_LAST";
    // Original object relative source line 163.
    case 0x800401C0: return "CONVERT10_E_FIRST";
    // Original object relative source line 164.
    case 0x800401CF: return "CONVERT10_E_LAST";
    // Original object relative source line 165.
    case 0x000401C0: return "CONVERT10_S_FIRST";
    // Original object relative source line 166.
    case 0x000401CF: return "CONVERT10_S_LAST";
    // Original object relative source line 168.
    case 0x800401C1: return "CONVERT10_E_OLESTREAM_PUT";
    // Original object relative source line 169.
    case 0x800401C2: return "CONVERT10_E_OLESTREAM_FMT";
    // Original object relative source line 170.
    case 0x800401C3: return "CONVERT10_E_OLESTREAM_BITMAP_TO_DIB";
    // Original object relative source line 171.
    case 0x800401C4: return "CONVERT10_E_STG_FMT";
    // Original object relative source line 172.
    case 0x800401C5: return "CONVERT10_E_STG_NO_STD_STREAM";
    // Original object relative source line 173.
    case 0x800401C6: return "CONVERT10_E_STG_DIB_TO_BITMAP";
    // Original object relative source line 174.
    case 0x800401D0: return "CLIPBRD_E_FIRST";
    // Original object relative source line 175.
    case 0x800401DF: return "CLIPBRD_E_LAST";
    // Original object relative source line 176.
    case 0x000401D0: return "CLIPBRD_S_FIRST";
    // Original object relative source line 177.
    case 0x000401DF: return "CLIPBRD_S_LAST";
    // Original object relative source line 179.
    case 0x800401D1: return "CLIPBRD_E_CANT_EMPTY";
    // Original object relative source line 180.
    case 0x800401D2: return "CLIPBRD_E_CANT_SET";
    // Original object relative source line 181.
    case 0x800401D3: return "CLIPBRD_E_BAD_DATA";
    // Original object relative source line 182.
    case 0x800401D4: return "CLIPBRD_E_CANT_CLOSE";
    // Original object relative source line 183.
    case 0x800401E0: return "MK_E_FIRST";
    // Original object relative source line 184.
    case 0x800401EF: return "MK_E_LAST";
    // Original object relative source line 185.
    case 0x000401E0: return "MK_S_FIRST";
    // Original object relative source line 186.
    case 0x000401EF: return "MK_S_LAST";
    // Original object relative source line 188.
    case 0x800401E1: return "MK_E_EXCEEDEDDEADLINE";
    // Original object relative source line 189.
    case 0x800401E2: return "MK_E_NEEDGENERIC";
    // Original object relative source line 190.
    case 0x800401E3: return "MK_E_UNAVAILABLE";
    // Original object relative source line 191.
    case 0x800401E4: return "MK_E_SYNTAX";
    // Original object relative source line 192.
    case 0x800401E5: return "MK_E_NOOBJECT";
    // Original object relative source line 193.
    case 0x800401E6: return "MK_E_INVALIDEXTENSION";
    // Original object relative source line 194.
    case 0x800401E7: return "MK_E_INTERMEDIATEINTERFACENOTSUPPORTED";
    // Original object relative source line 195.
    case 0x800401E8: return "MK_E_NOTBINDABLE";
    // Original object relative source line 196.
    case 0x800401E9: return "MK_E_NOTBOUND";
    // Original object relative source line 197.
    case 0x800401EA: return "MK_E_CANTOPENFILE";
    // Original object relative source line 198.
    case 0x800401EB: return "MK_E_MUSTBOTHERUSER";
    // Original object relative source line 199.
    case 0x800401EC: return "MK_E_NOINVERSE";
    // Original object relative source line 200.
    case 0x800401ED: return "MK_E_NOSTORAGE";
    // Original object relative source line 201.
    case 0x800401EE: return "MK_E_NOPREFIX";
    // Original object relative source line 203.
    case 0x800401F0: return "CO_E_NOTINITIALIZED";
    // Original object relative source line 204.
    case 0x800401F1: return "CO_E_ALREADYINITIALIZED";
    // Original object relative source line 205.
    case 0x800401F2: return "CO_E_CANTDETERMINECLASS";
    // Original object relative source line 206.
    case 0x800401F3: return "CO_E_CLASSSTRING";
    // Original object relative source line 207.
    case 0x800401F4: return "CO_E_IIDSTRING";
    // Original object relative source line 208.
    case 0x800401F5: return "CO_E_APPNOTFOUND";
    // Original object relative source line 209.
    case 0x800401F6: return "CO_E_APPSINGLEUSE";
    // Original object relative source line 210.
    case 0x800401F7: return "CO_E_ERRORINAPP";
    // Original object relative source line 211.
    case 0x800401F8: return "CO_E_DLLNOTFOUND";
    // Original object relative source line 212.
    case 0x800401F9: return "CO_E_ERRORINDLL";
    // Original object relative source line 213.
    case 0x800401FA: return "CO_E_WRONGOSFORAPP";
    // Original object relative source line 214.
    case 0x800401FB: return "CO_E_OBJNOTREG";
    // Original object relative source line 215.
    case 0x800401FC: return "CO_E_OBJISREG";
    // Original object relative source line 216.
    case 0x800401FD: return "CO_E_OBJNOTCONNECTED";
    // Original object relative source line 217.
    case 0x800401FE: return "CO_E_APPDIDNTREG";
    // Original object relative source line 218.
    case 0x800401FF: return "CO_E_RELEASED";
    // Original object relative source line 220.
    case 0x00040001: return "OLE_S_STATIC & MS_S_PENDING & WBEM_S_ALREADY_EXISTS";
    // Original object relative source line 221.
    case 0x00040002: return "OLE_S_MAC_CLIPFORMAT & MS_S_NOUPDATE & WBEM_S_RESET_TO_DEFAULT";
    // Original object relative source line 223.
    case 0x00040101: return "DRAGDROP_S_CANCEL";
    // Original object relative source line 224.
    case 0x00040102: return "DRAGDROP_S_USEDEFAULTCURSORS";
    // Original object relative source line 228.
    case 0x00040171: return "CACHE_S_SAMECACHE";
    // Original object relative source line 229.
    case 0x00040172: return "CACHE_S_SOMECACHES_NOTUPDATED";
    // Original object relative source line 231.
    case 0x00040181: return "OLEOBJ_S_CANNOT_DOVERB_NOW";
    // Original object relative source line 232.
    case 0x00040182: return "OLEOBJ_S_INVALIDHWND";
    // Original object relative source line 235.
    case 0x000401E2: return "MK_S_REDUCED_TO_SELF";
    // Original object relative source line 236.
    case 0x000401E4: return "MK_S_ME";
    // Original object relative source line 237.
    case 0x000401E5: return "MK_S_HIM";
    // Original object relative source line 238.
    case 0x000401E6: return "MK_S_US";
    // Original object relative source line 239.
    case 0x000401E7: return "MK_S_MONIKERALREADYREGISTERED";
    // Original object relative source line 240.
    case 0x80080001: return "CO_E_CLASS_CREATE_FAILED";
    // Original object relative source line 241.
    case 0x80080002: return "CO_E_SCM_ERROR";
    // Original object relative source line 242.
    case 0x80080003: return "CO_E_SCM_RPC_FAILURE";
    // Original object relative source line 243.
    case 0x80080004: return "CO_E_BAD_PATH";
    // Original object relative source line 244.
    case 0x80080005: return "CO_E_SERVER_EXEC_FAILURE";
    // Original object relative source line 245.
    case 0x80080006: return "CO_E_OBJSRV_RPC_FAILURE";
    // Original object relative source line 246.
    case 0x80080007: return "MK_E_NO_NORMALIZED";
    // Original object relative source line 247.
    case 0x80080008: return "CO_E_SERVER_STOPPING";
    // Original object relative source line 248.
    case 0x80080009: return "MEM_E_INVALID_ROOT";
    // Original object relative source line 249.
    case 0x80080010: return "MEM_E_INVALID_LINK";
    // Original object relative source line 250.
    case 0x80080011: return "MEM_E_INVALID_SIZE";
    // Original object relative source line 251.
    case 0x00080012: return "CO_S_NOTALLINTERFACES";
    // Original object relative source line 252.
    case 0x80020001: return "DISP_E_UNKNOWNINTERFACE";
    // Original object relative source line 253.
    case 0x80020003: return "DISP_E_MEMBERNOTFOUND";
    // Original object relative source line 254.
    case 0x80020004: return "DISP_E_PARAMNOTFOUND";
    // Original object relative source line 255.
    case 0x80020005: return "DISP_E_TYPEMISMATCH";
    // Original object relative source line 256.
    case 0x80020006: return "DISP_E_UNKNOWNNAME";
    // Original object relative source line 257.
    case 0x80020007: return "DISP_E_NONAMEDARGS";
    // Original object relative source line 258.
    case 0x80020008: return "DISP_E_BADVARTYPE";
    // Original object relative source line 259.
    case 0x80020009: return "DISP_E_EXCEPTION";
    // Original object relative source line 260.
    case 0x8002000A: return "DISP_E_OVERFLOW";
    // Original object relative source line 261.
    case 0x8002000B: return "DISP_E_BADINDEX";
    // Original object relative source line 262.
    case 0x8002000C: return "DISP_E_UNKNOWNLCID";
    // Original object relative source line 263.
    case 0x8002000D: return "DISP_E_ARRAYISLOCKED";
    // Original object relative source line 264.
    case 0x8002000E: return "DISP_E_BADPARAMCOUNT";
    // Original object relative source line 265.
    case 0x8002000F: return "DISP_E_PARAMNOTOPTIONAL";
    // Original object relative source line 266.
    case 0x80020010: return "DISP_E_BADCALLEE";
    // Original object relative source line 267.
    case 0x80020011: return "DISP_E_NOTACOLLECTION";
    // Original object relative source line 268.
    case 0x80020012: return "DISP_E_DIVBYZERO";
    // Original object relative source line 269.
    case 0x80020013: return "DISP_E_BUFFERTOOSMALL";
    // Original object relative source line 270.
    case 0x80028016: return "TYPE_E_BUFFERTOOSMALL";
    // Original object relative source line 271.
    case 0x80028017: return "TYPE_E_FIELDNOTFOUND";
    // Original object relative source line 272.
    case 0x80028018: return "TYPE_E_INVDATAREAD";
    // Original object relative source line 273.
    case 0x80028019: return "TYPE_E_UNSUPFORMAT";
    // Original object relative source line 274.
    case 0x8002801C: return "TYPE_E_REGISTRYACCESS";
    // Original object relative source line 275.
    case 0x8002801D: return "TYPE_E_LIBNOTREGISTERED";
    // Original object relative source line 276.
    case 0x80028027: return "TYPE_E_UNDEFINEDTYPE";
    // Original object relative source line 277.
    case 0x80028028: return "TYPE_E_QUALIFIEDNAMEDISALLOWED";
    // Original object relative source line 278.
    case 0x80028029: return "TYPE_E_INVALIDSTATE";
    // Original object relative source line 279.
    case 0x8002802A: return "TYPE_E_WRONGTYPEKIND";
    // Original object relative source line 280.
    case 0x8002802B: return "TYPE_E_ELEMENTNOTFOUND";
    // Original object relative source line 281.
    case 0x8002802C: return "TYPE_E_AMBIGUOUSNAME";
    // Original object relative source line 282.
    case 0x8002802D: return "TYPE_E_NAMECONFLICT";
    // Original object relative source line 283.
    case 0x8002802E: return "TYPE_E_UNKNOWNLCID";
    // Original object relative source line 284.
    case 0x8002802F: return "TYPE_E_DLLFUNCTIONNOTFOUND";
    // Original object relative source line 285.
    case 0x800288BD: return "TYPE_E_BADMODULEKIND";
    // Original object relative source line 286.
    case 0x800288C5: return "TYPE_E_SIZETOOBIG";
    // Original object relative source line 287.
    case 0x800288C6: return "TYPE_E_DUPLICATEID";
    // Original object relative source line 288.
    case 0x800288CF: return "TYPE_E_INVALIDID";
    // Original object relative source line 289.
    case 0x80028CA0: return "TYPE_E_TYPEMISMATCH";
    // Original object relative source line 290.
    case 0x80028CA1: return "TYPE_E_OUTOFBOUNDS";
    // Original object relative source line 291.
    case 0x80028CA2: return "TYPE_E_IOERROR";
    // Original object relative source line 292.
    case 0x80028CA3: return "TYPE_E_CANTCREATETMPFILE";
    // Original object relative source line 293.
    case 0x80029C4A: return "TYPE_E_CANTLOADLIBRARY";
    // Original object relative source line 294.
    case 0x80029C83: return "TYPE_E_INCONSISTENTPROPFUNCS";
    // Original object relative source line 295.
    case 0x80029C84: return "TYPE_E_CIRCULARTYPE";
    // Original object relative source line 296.
    case 0x80030001: return "STG_E_INVALIDFUNCTION";
    // Original object relative source line 297.
    case 0x80030002: return "STG_E_FILENOTFOUND";
    // Original object relative source line 298.
    case 0x80030003: return "STG_E_PATHNOTFOUND";
    // Original object relative source line 299.
    case 0x80030004: return "STG_E_TOOMANYOPENFILES";
    // Original object relative source line 300.
    case 0x80030005: return "STG_E_ACCESSDENIED";
    // Original object relative source line 301.
    case 0x80030006: return "STG_E_INVALIDHANDLE";
    // Original object relative source line 302.
    case 0x80030008: return "STG_E_INSUFFICIENTMEMORY";
    // Original object relative source line 303.
    case 0x80030009: return "STG_E_INVALIDPOINTER";
    // Original object relative source line 304.
    case 0x80030012: return "STG_E_NOMOREFILES";
    // Original object relative source line 305.
    case 0x80030013: return "STG_E_DISKISWRITEPROTECTED";
    // Original object relative source line 306.
    case 0x80030019: return "STG_E_SEEKERROR";
    // Original object relative source line 307.
    case 0x8003001D: return "STG_E_WRITEFAULT";
    // Original object relative source line 308.
    case 0x8003001E: return "STG_E_READFAULT";
    // Original object relative source line 309.
    case 0x80030020: return "STG_E_SHAREVIOLATION";
    // Original object relative source line 310.
    case 0x80030021: return "STG_E_LOCKVIOLATION";
    // Original object relative source line 311.
    case 0x80030050: return "STG_E_FILEALREADYEXISTS";
    // Original object relative source line 312.
    case 0x80030057: return "STG_E_INVALIDPARAMETER";
    // Original object relative source line 313.
    case 0x80030070: return "STG_E_MEDIUMFULL";
    // Original object relative source line 314.
    case 0x800300F0: return "STG_E_PROPSETMISMATCHED";
    // Original object relative source line 315.
    case 0x800300FA: return "STG_E_ABNORMALAPIEXIT";
    // Original object relative source line 316.
    case 0x800300FB: return "STG_E_INVALIDHEADER";
    // Original object relative source line 317.
    case 0x800300FC: return "STG_E_INVALIDNAME";
    // Original object relative source line 318.
    case 0x800300FD: return "STG_E_UNKNOWN";
    // Original object relative source line 319.
    case 0x800300FE: return "STG_E_UNIMPLEMENTEDFUNCTION";
    // Original object relative source line 320.
    case 0x800300FF: return "STG_E_INVALIDFLAG";
    // Original object relative source line 321.
    case 0x80030100: return "STG_E_INUSE";
    // Original object relative source line 322.
    case 0x80030101: return "STG_E_NOTCURRENT";
    // Original object relative source line 323.
    case 0x80030102: return "STG_E_REVERTED";
    // Original object relative source line 324.
    case 0x80030103: return "STG_E_CANTSAVE";
    // Original object relative source line 325.
    case 0x80030104: return "STG_E_OLDFORMAT";
    // Original object relative source line 326.
    case 0x80030105: return "STG_E_OLDDLL";
    // Original object relative source line 327.
    case 0x80030106: return "STG_E_SHAREREQUIRED";
    // Original object relative source line 328.
    case 0x80030107: return "STG_E_NOTFILEBASEDSTORAGE";
    // Original object relative source line 329.
    case 0x80030108: return "STG_E_EXTANTMARSHALLINGS";
    // Original object relative source line 330.
    case 0x80030109: return "STG_E_DOCFILECORRUPT";
    // Original object relative source line 331.
    case 0x80030110: return "STG_E_BADBASEADDRESS";
    // Original object relative source line 332.
    case 0x80030111: return "STG_E_DOCFILETOOLARGE";
    // Original object relative source line 333.
    case 0x80030112: return "STG_E_NOTSIMPLEFORMAT";
    // Original object relative source line 334.
    case 0x80030201: return "STG_E_INCOMPLETE";
    // Original object relative source line 335.
    case 0x80030202: return "STG_E_TERMINATED";
    // Original object relative source line 336.
    case 0x00030200: return "STG_S_CONVERTED";
    // Original object relative source line 337.
    case 0x00030201: return "STG_S_BLOCK";
    // Original object relative source line 338.
    case 0x00030202: return "STG_S_RETRYNOW";
    // Original object relative source line 339.
    case 0x00030203: return "STG_S_MONITORING";
    // Original object relative source line 340.
    case 0x00030204: return "STG_S_MULTIPLEOPENS";
    // Original object relative source line 341.
    case 0x00030205: return "STG_S_CONSOLIDATIONFAILED";
    // Original object relative source line 342.
    case 0x00030206: return "STG_S_CANNOTCONSOLIDATE";
    // Original object relative source line 343.
    case 0x80010001: return "RPC_E_CALL_REJECTED";
    // Original object relative source line 344.
    case 0x80010002: return "RPC_E_CALL_CANCELED";
    // Original object relative source line 345.
    case 0x80010003: return "RPC_E_CANTPOST_INSENDCALL";
    // Original object relative source line 346.
    case 0x80010004: return "RPC_E_CANTCALLOUT_INASYNCCALL";
    // Original object relative source line 347.
    case 0x80010005: return "RPC_E_CANTCALLOUT_INEXTERNALCALL";
    // Original object relative source line 348.
    case 0x80010006: return "RPC_E_CONNECTION_TERMINATED";
    // Original object relative source line 349.
    case 0x80010007: return "RPC_E_SERVER_DIED";
    // Original object relative source line 350.
    case 0x80010008: return "RPC_E_CLIENT_DIED";
    // Original object relative source line 351.
    case 0x80010009: return "RPC_E_INVALID_DATAPACKET";
    // Original object relative source line 352.
    case 0x8001000A: return "RPC_E_CANTTRANSMIT_CALL";
    // Original object relative source line 353.
    case 0x8001000B: return "RPC_E_CLIENT_CANTMARSHAL_DATA";
    // Original object relative source line 354.
    case 0x8001000C: return "RPC_E_CLIENT_CANTUNMARSHAL_DATA";
    // Original object relative source line 355.
    case 0x8001000D: return "RPC_E_SERVER_CANTMARSHAL_DATA";
    // Original object relative source line 356.
    case 0x8001000E: return "RPC_E_SERVER_CANTUNMARSHAL_DATA";
    // Original object relative source line 357.
    case 0x8001000F: return "RPC_E_INVALID_DATA";
    // Original object relative source line 358.
    case 0x80010010: return "RPC_E_INVALID_PARAMETER";
    // Original object relative source line 359.
    case 0x80010011: return "RPC_E_CANTCALLOUT_AGAIN";
    // Original object relative source line 360.
    case 0x80010012: return "RPC_E_SERVER_DIED_DNE";
    // Original object relative source line 361.
    case 0x80010100: return "RPC_E_SYS_CALL_FAILED";
    // Original object relative source line 362.
    case 0x80010101: return "RPC_E_OUT_OF_RESOURCES";
    // Original object relative source line 363.
    case 0x80010102: return "RPC_E_ATTEMPTED_MULTITHREAD";
    // Original object relative source line 364.
    case 0x80010103: return "RPC_E_NOT_REGISTERED";
    // Original object relative source line 365.
    case 0x80010104: return "RPC_E_FAULT";
    // Original object relative source line 366.
    case 0x80010105: return "RPC_E_SERVERFAULT";
    // Original object relative source line 367.
    case 0x80010106: return "RPC_E_CHANGED_MODE";
    // Original object relative source line 368.
    case 0x80010107: return "RPC_E_INVALIDMETHOD";
    // Original object relative source line 369.
    case 0x80010108: return "RPC_E_DISCONNECTED";
    // Original object relative source line 370.
    case 0x80010109: return "RPC_E_RETRY";
    // Original object relative source line 371.
    case 0x8001010A: return "RPC_E_SERVERCALL_RETRYLATER";
    // Original object relative source line 372.
    case 0x8001010B: return "RPC_E_SERVERCALL_REJECTED";
    // Original object relative source line 373.
    case 0x8001010C: return "RPC_E_INVALID_CALLDATA";
    // Original object relative source line 374.
    case 0x8001010D: return "RPC_E_CANTCALLOUT_ININPUTSYNCCALL";
    // Original object relative source line 375.
    case 0x8001010E: return "RPC_E_WRONG_THREAD";
    // Original object relative source line 376.
    case 0x8001010F: return "RPC_E_THREAD_NOT_INIT";
    // Original object relative source line 377.
    case 0x80010110: return "RPC_E_VERSION_MISMATCH";
    // Original object relative source line 378.
    case 0x80010111: return "RPC_E_INVALID_HEADER";
    // Original object relative source line 379.
    case 0x80010112: return "RPC_E_INVALID_EXTENSION";
    // Original object relative source line 380.
    case 0x80010113: return "RPC_E_INVALID_IPID";
    // Original object relative source line 381.
    case 0x80010114: return "RPC_E_INVALID_OBJECT";
    // Original object relative source line 382.
    case 0x80010115: return "RPC_S_CALLPENDING";
    // Original object relative source line 383.
    case 0x80010116: return "RPC_S_WAITONTIMER";
    // Original object relative source line 384.
    case 0x80010117: return "RPC_E_CALL_COMPLETE";
    // Original object relative source line 385.
    case 0x80010118: return "RPC_E_UNSECURE_CALL";
    // Original object relative source line 386.
    case 0x80010119: return "RPC_E_TOO_LATE";
    // Original object relative source line 387.
    case 0x8001011A: return "RPC_E_NO_GOOD_SECURITY_PACKAGES";
    // Original object relative source line 388.
    case 0x8001011B: return "RPC_E_ACCESS_DENIED";
    // Original object relative source line 389.
    case 0x8001011C: return "RPC_E_REMOTE_DISABLED";
    // Original object relative source line 390.
    case 0x8001011D: return "RPC_E_INVALID_OBJREF";
    // Original object relative source line 391.
    case 0x8001011E: return "RPC_E_NO_CONTEXT";
    // Original object relative source line 392.
    case 0x8001011F: return "RPC_E_TIMEOUT";
    // Original object relative source line 393.
    case 0x80010120: return "RPC_E_NO_SYNC";
    // Original object relative source line 394.
    case 0x80010121: return "RPC_E_FULLSIC_REQUIRED";
    // Original object relative source line 395.
    case 0x80010122: return "RPC_E_INVALID_STD_NAME";
    // Original object relative source line 396.
    case 0x80010123: return "CO_E_FAILEDTOIMPERSONATE";
    // Original object relative source line 397.
    case 0x80010124: return "CO_E_FAILEDTOGETSECCTX";
    // Original object relative source line 398.
    case 0x80010125: return "CO_E_FAILEDTOOPENTHREADTOKEN";
    // Original object relative source line 399.
    case 0x80010126: return "CO_E_FAILEDTOGETTOKENINFO";
    // Original object relative source line 400.
    case 0x80010127: return "CO_E_TRUSTEEDOESNTMATCHCLIENT";
    // Original object relative source line 401.
    case 0x80010128: return "CO_E_FAILEDTOQUERYCLIENTBLANKET";
    // Original object relative source line 402.
    case 0x80010129: return "CO_E_FAILEDTOSETDACL";
    // Original object relative source line 403.
    case 0x8001012A: return "CO_E_ACCESSCHECKFAILED";
    // Original object relative source line 404.
    case 0x8001012B: return "CO_E_NETACCESSAPIFAILED";
    // Original object relative source line 405.
    case 0x8001012C: return "CO_E_WRONGTRUSTEENAMESYNTAX";
    // Original object relative source line 406.
    case 0x8001012D: return "CO_E_INVALIDSID";
    // Original object relative source line 407.
    case 0x8001012E: return "CO_E_CONVERSIONFAILED";
    // Original object relative source line 408.
    case 0x8001012F: return "CO_E_NOMATCHINGSIDFOUND";
    // Original object relative source line 409.
    case 0x80010130: return "CO_E_LOOKUPACCSIDFAILED";
    // Original object relative source line 410.
    case 0x80010131: return "CO_E_NOMATCHINGNAMEFOUND";
    // Original object relative source line 411.
    case 0x80010132: return "CO_E_LOOKUPACCNAMEFAILED";
    // Original object relative source line 412.
    case 0x80010133: return "CO_E_SETSERLHNDLFAILED";
    // Original object relative source line 413.
    case 0x80010134: return "CO_E_FAILEDTOGETWINDIR";
    // Original object relative source line 414.
    case 0x80010135: return "CO_E_PATHTOOLONG";
    // Original object relative source line 415.
    case 0x80010136: return "CO_E_FAILEDTOGENUUID";
    // Original object relative source line 416.
    case 0x80010137: return "CO_E_FAILEDTOCREATEFILE";
    // Original object relative source line 417.
    case 0x80010138: return "CO_E_FAILEDTOCLOSEHANDLE";
    // Original object relative source line 418.
    case 0x80010139: return "CO_E_EXCEEDSYSACLLIMIT";
    // Original object relative source line 419.
    case 0x8001013A: return "CO_E_ACESINWRONGORDER";
    // Original object relative source line 420.
    case 0x8001013B: return "CO_E_INCOMPATIBLESTREAMVERSION";
    // Original object relative source line 421.
    case 0x8001013C: return "CO_E_FAILEDTOOPENPROCESSTOKEN";
    // Original object relative source line 422.
    case 0x8001013D: return "CO_E_DECODEFAILED";
    // Original object relative source line 423.
    case 0x8001013F: return "CO_E_ACNOTINITIALIZED";
    // Original object relative source line 424.
    case 0x8001FFFF: return "RPC_E_UNEXPECTED";
    // Original object relative source line 425.
    case 0x80090001: return "NTE_BAD_UID";
    // Original object relative source line 426.
    case 0x80090002: return "NTE_BAD_HASH";
    // Original object relative source line 427.
    case 0x80090003: return "NTE_BAD_KEY";
    // Original object relative source line 428.
    case 0x80090004: return "NTE_BAD_LEN";
    // Original object relative source line 429.
    case 0x80090005: return "NTE_BAD_DATA";
    // Original object relative source line 430.
    case 0x80090006: return "NTE_BAD_SIGNATURE";
    // Original object relative source line 431.
    case 0x80090007: return "NTE_BAD_VER";
    // Original object relative source line 432.
    case 0x80090008: return "NTE_BAD_ALGID";
    // Original object relative source line 433.
    case 0x80090009: return "NTE_BAD_FLAGS";
    // Original object relative source line 434.
    case 0x8009000A: return "NTE_BAD_TYPE";
    // Original object relative source line 435.
    case 0x8009000B: return "NTE_BAD_KEY_STATE";
    // Original object relative source line 436.
    case 0x8009000C: return "NTE_BAD_HASH_STATE";
    // Original object relative source line 437.
    case 0x8009000D: return "NTE_NO_KEY";
    // Original object relative source line 438.
    case 0x8009000E: return "NTE_NO_MEMORY";
    // Original object relative source line 439.
    case 0x8009000F: return "NTE_EXISTS";
    // Original object relative source line 440.
    case 0x80090010: return "NTE_PERM";
    // Original object relative source line 441.
    case 0x80090011: return "NTE_NOT_FOUND";
    // Original object relative source line 442.
    case 0x80090012: return "NTE_DOUBLE_ENCRYPT";
    // Original object relative source line 443.
    case 0x80090013: return "NTE_BAD_PROVIDER";
    // Original object relative source line 444.
    case 0x80090014: return "NTE_BAD_PROV_TYPE";
    // Original object relative source line 445.
    case 0x80090015: return "NTE_BAD_PUBLIC_KEY";
    // Original object relative source line 446.
    case 0x80090016: return "NTE_BAD_KEYSET";
    // Original object relative source line 447.
    case 0x80090017: return "NTE_PROV_TYPE_NOT_DEF";
    // Original object relative source line 448.
    case 0x80090018: return "NTE_PROV_TYPE_ENTRY_BAD";
    // Original object relative source line 449.
    case 0x80090019: return "NTE_KEYSET_NOT_DEF";
    // Original object relative source line 450.
    case 0x8009001A: return "NTE_KEYSET_ENTRY_BAD";
    // Original object relative source line 451.
    case 0x8009001B: return "NTE_PROV_TYPE_NO_MATCH";
    // Original object relative source line 452.
    case 0x8009001C: return "NTE_SIGNATURE_FILE_BAD";
    // Original object relative source line 453.
    case 0x8009001D: return "NTE_PROVIDER_DLL_FAIL";
    // Original object relative source line 454.
    case 0x8009001E: return "NTE_PROV_DLL_NOT_FOUND";
    // Original object relative source line 455.
    case 0x8009001F: return "NTE_BAD_KEYSET_PARAM";
    // Original object relative source line 456.
    case 0x80090020: return "NTE_FAIL";
    // Original object relative source line 457.
    case 0x80090021: return "NTE_SYS_ERR";
    // Original object relative source line 458.
    case 0x80090022: return "NTE_SILENT_CONTEXT";
    // Original object relative source line 459.
    case 0x80090023: return "NTE_TOKEN_KEYSET_STORAGE_FULL";
    // Original object relative source line 460.
    case 0x80091001: return "CRYPT_E_MSG_ERROR";
    // Original object relative source line 461.
    case 0x80091002: return "CRYPT_E_UNKNOWN_ALGO";
    // Original object relative source line 462.
    case 0x80091003: return "CRYPT_E_OID_FORMAT";
    // Original object relative source line 463.
    case 0x80091004: return "CRYPT_E_INVALID_MSG_TYPE";
    // Original object relative source line 464.
    case 0x80091005: return "CRYPT_E_UNEXPECTED_ENCODING";
    // Original object relative source line 465.
    case 0x80091006: return "CRYPT_E_AUTH_ATTR_MISSING";
    // Original object relative source line 466.
    case 0x80091007: return "CRYPT_E_HASH_VALUE";
    // Original object relative source line 467.
    case 0x80091008: return "CRYPT_E_INVALID_INDEX";
    // Original object relative source line 468.
    case 0x80091009: return "CRYPT_E_ALREADY_DECRYPTED";
    // Original object relative source line 469.
    case 0x8009100A: return "CRYPT_E_NOT_DECRYPTED";
    // Original object relative source line 470.
    case 0x8009100B: return "CRYPT_E_RECIPIENT_NOT_FOUND";
    // Original object relative source line 471.
    case 0x8009100C: return "CRYPT_E_CONTROL_TYPE";
    // Original object relative source line 472.
    case 0x8009100D: return "CRYPT_E_ISSUER_SERIALNUMBER";
    // Original object relative source line 473.
    case 0x8009100E: return "CRYPT_E_SIGNER_NOT_FOUND";
    // Original object relative source line 474.
    case 0x8009100F: return "CRYPT_E_ATTRIBUTES_MISSING";
    // Original object relative source line 475.
    case 0x80091010: return "CRYPT_E_STREAM_MSG_NOT_READY";
    // Original object relative source line 476.
    case 0x80091011: return "CRYPT_E_STREAM_INSUFFICIENT_DATA";
    // Original object relative source line 477.
    case 0x80092001: return "CRYPT_E_BAD_LEN";
    // Original object relative source line 478.
    case 0x80092002: return "CRYPT_E_BAD_ENCODE";
    // Original object relative source line 479.
    case 0x80092003: return "CRYPT_E_FILE_ERROR";
    // Original object relative source line 480.
    case 0x80092004: return "CRYPT_E_NOT_FOUND";
    // Original object relative source line 481.
    case 0x80092005: return "CRYPT_E_EXISTS";
    // Original object relative source line 482.
    case 0x80092006: return "CRYPT_E_NO_PROVIDER";
    // Original object relative source line 483.
    case 0x80092007: return "CRYPT_E_SELF_SIGNED";
    // Original object relative source line 484.
    case 0x80092008: return "CRYPT_E_DELETED_PREV";
    // Original object relative source line 485.
    case 0x80092009: return "CRYPT_E_NO_MATCH";
    // Original object relative source line 486.
    case 0x8009200A: return "CRYPT_E_UNEXPECTED_MSG_TYPE";
    // Original object relative source line 487.
    case 0x8009200B: return "CRYPT_E_NO_KEY_PROPERTY";
    // Original object relative source line 488.
    case 0x8009200C: return "CRYPT_E_NO_DECRYPT_CERT";
    // Original object relative source line 489.
    case 0x8009200D: return "CRYPT_E_BAD_MSG";
    // Original object relative source line 490.
    case 0x8009200E: return "CRYPT_E_NO_SIGNER";
    // Original object relative source line 491.
    case 0x8009200F: return "CRYPT_E_PENDING_CLOSE";
    // Original object relative source line 492.
    case 0x80092010: return "CRYPT_E_REVOKED";
    // Original object relative source line 493.
    case 0x80092011: return "CRYPT_E_NO_REVOCATION_DLL";
    // Original object relative source line 494.
    case 0x80092012: return "CRYPT_E_NO_REVOCATION_CHECK";
    // Original object relative source line 495.
    case 0x80092013: return "CRYPT_E_REVOCATION_OFFLINE";
    // Original object relative source line 496.
    case 0x80092014: return "CRYPT_E_NOT_IN_REVOCATION_DATABASE";
    // Original object relative source line 497.
    case 0x80092020: return "CRYPT_E_INVALID_NUMERIC_STRING";
    // Original object relative source line 498.
    case 0x80092021: return "CRYPT_E_INVALID_PRINTABLE_STRING";
    // Original object relative source line 499.
    case 0x80092022: return "CRYPT_E_INVALID_IA5_STRING";
    // Original object relative source line 500.
    case 0x80092023: return "CRYPT_E_INVALID_X500_STRING";
    // Original object relative source line 501.
    case 0x80092024: return "CRYPT_E_NOT_CHAR_STRING";
    // Original object relative source line 502.
    case 0x80092025: return "CRYPT_E_FILERESIZED";
    // Original object relative source line 503.
    case 0x80092026: return "CRYPT_E_SECURITY_SETTINGS";
    // Original object relative source line 504.
    case 0x80092027: return "CRYPT_E_NO_VERIFY_USAGE_DLL";
    // Original object relative source line 505.
    case 0x80092028: return "CRYPT_E_NO_VERIFY_USAGE_CHECK";
    // Original object relative source line 506.
    case 0x80092029: return "CRYPT_E_VERIFY_USAGE_OFFLINE";
    // Original object relative source line 507.
    case 0x8009202A: return "CRYPT_E_NOT_IN_CTL";
    // Original object relative source line 508.
    case 0x8009202B: return "CRYPT_E_NO_TRUSTED_SIGNER";
    // Original object relative source line 509.
    case 0x80093000: return "CRYPT_E_OSS_ERROR";
    // Original object relative source line 510.
    case 0x80093001: return "OSS_MORE_BUF";
    // Original object relative source line 511.
    case 0x80093002: return "OSS_NEGATIVE_UINTEGER";
    // Original object relative source line 512.
    case 0x80093003: return "OSS_PDU_RANGE";
    // Original object relative source line 513.
    case 0x80093004: return "OSS_MORE_INPUT";
    // Original object relative source line 514.
    case 0x80093005: return "OSS_DATA_ERROR";
    // Original object relative source line 515.
    case 0x80093006: return "OSS_BAD_ARG";
    // Original object relative source line 516.
    case 0x80093007: return "OSS_BAD_VERSION";
    // Original object relative source line 517.
    case 0x80093008: return "OSS_OUT_MEMORY";
    // Original object relative source line 518.
    case 0x80093009: return "OSS_PDU_MISMATCH";
    // Original object relative source line 519.
    case 0x8009300A: return "OSS_LIMITED";
    // Original object relative source line 520.
    case 0x8009300B: return "OSS_BAD_PTR";
    // Original object relative source line 521.
    case 0x8009300C: return "OSS_BAD_TIME";
    // Original object relative source line 522.
    case 0x8009300D: return "OSS_INDEFINITE_NOT_SUPPORTED";
    // Original object relative source line 523.
    case 0x8009300E: return "OSS_MEM_ERROR";
    // Original object relative source line 524.
    case 0x8009300F: return "OSS_BAD_TABLE";
    // Original object relative source line 525.
    case 0x80093010: return "OSS_TOO_LONG";
    // Original object relative source line 526.
    case 0x80093011: return "OSS_CONSTRAINT_VIOLATED";
    // Original object relative source line 527.
    case 0x80093012: return "OSS_FATAL_ERROR";
    // Original object relative source line 528.
    case 0x80093013: return "OSS_ACCESS_SERIALIZATION_ERROR";
    // Original object relative source line 529.
    case 0x80093014: return "OSS_NULL_TBL";
    // Original object relative source line 530.
    case 0x80093015: return "OSS_NULL_FCN";
    // Original object relative source line 531.
    case 0x80093016: return "OSS_BAD_ENCRULES";
    // Original object relative source line 532.
    case 0x80093017: return "OSS_UNAVAIL_ENCRULES";
    // Original object relative source line 533.
    case 0x80093018: return "OSS_CANT_OPEN_TRACE_WINDOW";
    // Original object relative source line 534.
    case 0x80093019: return "OSS_UNIMPLEMENTED";
    // Original object relative source line 535.
    case 0x8009301A: return "OSS_OID_DLL_NOT_LINKED";
    // Original object relative source line 536.
    case 0x8009301B: return "OSS_CANT_OPEN_TRACE_FILE";
    // Original object relative source line 537.
    case 0x8009301C: return "OSS_TRACE_FILE_ALREADY_OPEN";
    // Original object relative source line 538.
    case 0x8009301D: return "OSS_TABLE_MISMATCH";
    // Original object relative source line 539.
    case 0x8009301E: return "OSS_TYPE_NOT_SUPPORTED";
    // Original object relative source line 540.
    case 0x8009301F: return "OSS_REAL_DLL_NOT_LINKED";
    // Original object relative source line 541.
    case 0x80093020: return "OSS_REAL_CODE_NOT_LINKED";
    // Original object relative source line 542.
    case 0x80093021: return "OSS_OUT_OF_RANGE";
    // Original object relative source line 543.
    case 0x80093022: return "OSS_COPIER_DLL_NOT_LINKED";
    // Original object relative source line 544.
    case 0x80093023: return "OSS_CONSTRAINT_DLL_NOT_LINKED";
    // Original object relative source line 545.
    case 0x80093024: return "OSS_COMPARATOR_DLL_NOT_LINKED";
    // Original object relative source line 546.
    case 0x80093025: return "OSS_COMPARATOR_CODE_NOT_LINKED";
    // Original object relative source line 547.
    case 0x80093026: return "OSS_MEM_MGR_DLL_NOT_LINKED";
    // Original object relative source line 548.
    case 0x80093027: return "OSS_PDV_DLL_NOT_LINKED";
    // Original object relative source line 549.
    case 0x80093028: return "OSS_PDV_CODE_NOT_LINKED";
    // Original object relative source line 550.
    case 0x80093029: return "OSS_API_DLL_NOT_LINKED";
    // Original object relative source line 551.
    case 0x8009302A: return "OSS_BERDER_DLL_NOT_LINKED";
    // Original object relative source line 552.
    case 0x8009302B: return "OSS_PER_DLL_NOT_LINKED";
    // Original object relative source line 553.
    case 0x8009302C: return "OSS_OPEN_TYPE_ERROR";
    // Original object relative source line 554.
    case 0x8009302D: return "OSS_MUTEX_NOT_CREATED";
    // Original object relative source line 555.
    case 0x8009302E: return "OSS_CANT_CLOSE_TRACE_FILE";
    // Original object relative source line 556.
    case 0x80094001: return "CERTSRV_E_BAD_REQUESTSUBJECT";
    // Original object relative source line 557.
    case 0x80094002: return "CERTSRV_E_NO_REQUEST";
    // Original object relative source line 558.
    case 0x80094003: return "CERTSRV_E_BAD_REQUESTSTATUS";
    // Original object relative source line 559.
    case 0x80094004: return "CERTSRV_E_PROPERTY_EMPTY";
    // Original object relative source line 560.
    case 0x80094005: return "CERTSRV_E_INVALID_CA_CERTIFICATE";
    // Original object relative source line 561.
    case 0x80094800: return "CERTSRV_E_UNSUPPORTED_CERT_TYPE";
    // Original object relative source line 562.
    case 0x80094801: return "CERTSRV_E_NO_CERT_TYPE";
    // Original object relative source line 563.
    case 0x80096001: return "TRUST_E_SYSTEM_ERROR";
    // Original object relative source line 564.
    case 0x80096002: return "TRUST_E_NO_SIGNER_CERT";
    // Original object relative source line 565.
    case 0x80096003: return "TRUST_E_COUNTER_SIGNER";
    // Original object relative source line 566.
    case 0x80096004: return "TRUST_E_CERT_SIGNATURE";
    // Original object relative source line 567.
    case 0x80096005: return "TRUST_E_TIME_STAMP";
    // Original object relative source line 568.
    case 0x80096010: return "TRUST_E_BAD_DIGEST";
    // Original object relative source line 569.
    case 0x80096019: return "TRUST_E_BASIC_CONSTRAINTS";
    // Original object relative source line 570.
    case 0x8009601E: return "TRUST_E_FINANCIAL_CRITERIA";
    // Original object relative source line 572.
    case 0x800B0001: return "TRUST_E_PROVIDER_UNKNOWN";
    // Original object relative source line 573.
    case 0x800B0002: return "TRUST_E_ACTION_UNKNOWN";
    // Original object relative source line 574.
    case 0x800B0003: return "TRUST_E_SUBJECT_FORM_UNKNOWN";
    // Original object relative source line 575.
    case 0x800B0004: return "TRUST_E_SUBJECT_NOT_TRUSTED";
    // Original object relative source line 576.
    case 0x800B0005: return "DIGSIG_E_ENCODE";
    // Original object relative source line 577.
    case 0x800B0006: return "DIGSIG_E_DECODE";
    // Original object relative source line 578.
    case 0x800B0007: return "DIGSIG_E_EXTENSIBILITY";
    // Original object relative source line 579.
    case 0x800B0008: return "DIGSIG_E_CRYPTO";
    // Original object relative source line 580.
    case 0x800B0009: return "PERSIST_E_SIZEDEFINITE";
    // Original object relative source line 581.
    case 0x800B000A: return "PERSIST_E_SIZEINDEFINITE";
    // Original object relative source line 582.
    case 0x800B000B: return "PERSIST_E_NOTSELFSIZING";
    // Original object relative source line 583.
    case 0x800B0100: return "TRUST_E_NOSIGNATURE";
    // Original object relative source line 584.
    case 0x800B0101: return "CERT_E_EXPIRED";
    // Original object relative source line 585.
    case 0x800B0102: return "CERT_E_VALIDITYPERIODNESTING";
    // Original object relative source line 586.
    case 0x800B0103: return "CERT_E_ROLE";
    // Original object relative source line 587.
    case 0x800B0104: return "CERT_E_PATHLENCONST";
    // Original object relative source line 588.
    case 0x800B0105: return "CERT_E_CRITICAL";
    // Original object relative source line 589.
    case 0x800B0106: return "CERT_E_PURPOSE";
    // Original object relative source line 590.
    case 0x800B0107: return "CERT_E_ISSUERCHAINING";
    // Original object relative source line 591.
    case 0x800B0108: return "CERT_E_MALFORMED";
    // Original object relative source line 592.
    case 0x800B0109: return "CERT_E_UNTRUSTEDROOT";
    // Original object relative source line 593.
    case 0x800B010A: return "CERT_E_CHAINING";
    // Original object relative source line 594.
    case 0x800B010B: return "TRUST_E_FAIL";
    // Original object relative source line 595.
    case 0x800B010C: return "CERT_E_REVOKED";
    // Original object relative source line 596.
    case 0x800B010D: return "CERT_E_UNTRUSTEDTESTROOT";
    // Original object relative source line 597.
    case 0x800B010E: return "CERT_E_REVOCATION_FAILURE";
    // Original object relative source line 598.
    case 0x800B010F: return "CERT_E_CN_NO_MATCH";
    // Original object relative source line 599.
    case 0x800B0110: return "CERT_E_WRONG_USAGE";
    // Original object relative source line 600.
    case 0x800F0000: return "SPAPI_E_EXPECTED_SECTION_NAME";
    // Original object relative source line 601.
    case 0x800F0001: return "SPAPI_E_BAD_SECTION_NAME_LINE";
    // Original object relative source line 602.
    case 0x800F0002: return "SPAPI_E_SECTION_NAME_TOO_LONG";
    // Original object relative source line 603.
    case 0x800F0003: return "SPAPI_E_GENERAL_SYNTAX";
    // Original object relative source line 604.
    case 0x800F0100: return "SPAPI_E_WRONG_INF_STYLE";
    // Original object relative source line 605.
    case 0x800F0101: return "SPAPI_E_SECTION_NOT_FOUND";
    // Original object relative source line 606.
    case 0x800F0102: return "SPAPI_E_LINE_NOT_FOUND";
    // Original object relative source line 607.
    case 0x800F0103: return "SPAPI_E_NO_BACKUP";
    // Original object relative source line 608.
    case 0x800F0200: return "SPAPI_E_NO_ASSOCIATED_CLASS";
    // Original object relative source line 609.
    case 0x800F0201: return "SPAPI_E_CLASS_MISMATCH";
    // Original object relative source line 610.
    case 0x800F0202: return "SPAPI_E_DUPLICATE_FOUND";
    // Original object relative source line 611.
    case 0x800F0203: return "SPAPI_E_NO_DRIVER_SELECTED";
    // Original object relative source line 612.
    case 0x800F0204: return "SPAPI_E_KEY_DOES_NOT_EXIST";
    // Original object relative source line 613.
    case 0x800F0205: return "SPAPI_E_INVALID_DEVINST_NAME";
    // Original object relative source line 614.
    case 0x800F0206: return "SPAPI_E_INVALID_CLASS";
    // Original object relative source line 615.
    case 0x800F0207: return "SPAPI_E_DEVINST_ALREADY_EXISTS";
    // Original object relative source line 616.
    case 0x800F0208: return "SPAPI_E_DEVINFO_NOT_REGISTERED";
    // Original object relative source line 617.
    case 0x800F0209: return "SPAPI_E_INVALID_REG_PROPERTY";
    // Original object relative source line 618.
    case 0x800F020A: return "SPAPI_E_NO_INF";
    // Original object relative source line 619.
    case 0x800F020B: return "SPAPI_E_NO_SUCH_DEVINST";
    // Original object relative source line 620.
    case 0x800F020C: return "SPAPI_E_CANT_LOAD_CLASS_ICON";
    // Original object relative source line 621.
    case 0x800F020D: return "SPAPI_E_INVALID_CLASS_INSTALLER";
    // Original object relative source line 622.
    case 0x800F020E: return "SPAPI_E_DI_DO_DEFAULT";
    // Original object relative source line 623.
    case 0x800F020F: return "SPAPI_E_DI_NOFILECOPY";
    // Original object relative source line 624.
    case 0x800F0210: return "SPAPI_E_INVALID_HWPROFILE";
    // Original object relative source line 625.
    case 0x800F0211: return "SPAPI_E_NO_DEVICE_SELECTED";
    // Original object relative source line 626.
    case 0x800F0212: return "SPAPI_E_DEVINFO_LIST_LOCKED";
    // Original object relative source line 627.
    case 0x800F0213: return "SPAPI_E_DEVINFO_DATA_LOCKED";
    // Original object relative source line 628.
    case 0x800F0214: return "SPAPI_E_DI_BAD_PATH";
    // Original object relative source line 629.
    case 0x800F0215: return "SPAPI_E_NO_CLASSINSTALL_PARAMS";
    // Original object relative source line 630.
    case 0x800F0216: return "SPAPI_E_FILEQUEUE_LOCKED";
    // Original object relative source line 631.
    case 0x800F0217: return "SPAPI_E_BAD_SERVICE_INSTALLSECT";
    // Original object relative source line 632.
    case 0x800F0218: return "SPAPI_E_NO_CLASS_DRIVER_LIST";
    // Original object relative source line 633.
    case 0x800F0219: return "SPAPI_E_NO_ASSOCIATED_SERVICE";
    // Original object relative source line 634.
    case 0x800F021A: return "SPAPI_E_NO_DEFAULT_DEVICE_INTERFACE";
    // Original object relative source line 635.
    case 0x800F021B: return "SPAPI_E_DEVICE_INTERFACE_ACTIVE";
    // Original object relative source line 636.
    case 0x800F021C: return "SPAPI_E_DEVICE_INTERFACE_REMOVED";
    // Original object relative source line 637.
    case 0x800F021D: return "SPAPI_E_BAD_INTERFACE_INSTALLSECT";
    // Original object relative source line 638.
    case 0x800F021E: return "SPAPI_E_NO_SUCH_INTERFACE_CLASS";
    // Original object relative source line 639.
    case 0x800F021F: return "SPAPI_E_INVALID_REFERENCE_STRING";
    // Original object relative source line 640.
    case 0x800F0220: return "SPAPI_E_INVALID_MACHINENAME";
    // Original object relative source line 641.
    case 0x800F0221: return "SPAPI_E_REMOTE_COMM_FAILURE";
    // Original object relative source line 642.
    case 0x800F0222: return "SPAPI_E_MACHINE_UNAVAILABLE";
    // Original object relative source line 643.
    case 0x800F0223: return "SPAPI_E_NO_CONFIGMGR_SERVICES";
    // Original object relative source line 644.
    case 0x800F0224: return "SPAPI_E_INVALID_PROPPAGE_PROVIDER";
    // Original object relative source line 645.
    case 0x800F0225: return "SPAPI_E_NO_SUCH_DEVICE_INTERFACE";
    // Original object relative source line 646.
    case 0x800F0226: return "SPAPI_E_DI_POSTPROCESSING_REQUIRED";
    // Original object relative source line 647.
    case 0x800F0227: return "SPAPI_E_INVALID_COINSTALLER";
    // Original object relative source line 648.
    case 0x800F0228: return "SPAPI_E_NO_COMPAT_DRIVERS";
    // Original object relative source line 649.
    case 0x800F0229: return "SPAPI_E_NO_DEVICE_ICON";
    // Original object relative source line 650.
    case 0x800F022A: return "SPAPI_E_INVALID_INF_LOGCONFIG";
    // Original object relative source line 651.
    case 0x800F022B: return "SPAPI_E_DI_DONT_INSTALL";
    // Original object relative source line 652.
    case 0x800F022C: return "SPAPI_E_INVALID_FILTER_DRIVER";
    // Original object relative source line 653.
    case 0x800F022D: return "SPAPI_E_NON_WINDOWS_NT_DRIVER";
    // Original object relative source line 654.
    case 0x800F022E: return "SPAPI_E_NON_WINDOWS_DRIVER";
    // Original object relative source line 655.
    case 0x800F022F: return "SPAPI_E_NO_CATALOG_FOR_OEM_INF";
    // Original object relative source line 656.
    case 0x800F0230: return "SPAPI_E_DEVINSTALL_QUEUE_NONNATIVE";
    // Original object relative source line 657.
    case 0x800F1000: return "SPAPI_E_ERROR_NOT_INSTALLED";
    // Original object relative source line 659.
    case 0x80100001: return "SCARD_F_INTERNAL_ERROR";
    // Original object relative source line 660.
    case 0x80100002: return "SCARD_E_CANCELLED";
    // Original object relative source line 661.
    case 0x80100003: return "SCARD_E_INVALID_HANDLE";
    // Original object relative source line 662.
    case 0x80100004: return "SCARD_E_INVALID_PARAMETER";
    // Original object relative source line 663.
    case 0x80100005: return "SCARD_E_INVALID_TARGET";
    // Original object relative source line 664.
    case 0x80100006: return "SCARD_E_NO_MEMORY";
    // Original object relative source line 665.
    case 0x80100007: return "SCARD_F_WAITED_TOO_LONG";
    // Original object relative source line 666.
    case 0x80100008: return "SCARD_E_INSUFFICIENT_BUFFER";
    // Original object relative source line 667.
    case 0x80100009: return "SCARD_E_UNKNOWN_READER";
    // Original object relative source line 668.
    case 0x8010000A: return "SCARD_E_TIMEOUT";
    // Original object relative source line 669.
    case 0x8010000B: return "SCARD_E_SHARING_VIOLATION";
    // Original object relative source line 670.
    case 0x8010000C: return "SCARD_E_NO_SMARTCARD";
    // Original object relative source line 671.
    case 0x8010000D: return "SCARD_E_UNKNOWN_CARD";
    // Original object relative source line 672.
    case 0x8010000E: return "SCARD_E_CANT_DISPOSE";
    // Original object relative source line 673.
    case 0x8010000F: return "SCARD_E_PROTO_MISMATCH";
    // Original object relative source line 674.
    case 0x80100010: return "SCARD_E_NOT_READY";
    // Original object relative source line 675.
    case 0x80100011: return "SCARD_E_INVALID_VALUE";
    // Original object relative source line 676.
    case 0x80100012: return "SCARD_E_SYSTEM_CANCELLED";
    // Original object relative source line 677.
    case 0x80100013: return "SCARD_F_COMM_ERROR";
    // Original object relative source line 678.
    case 0x80100014: return "SCARD_F_UNKNOWN_ERROR";
    // Original object relative source line 679.
    case 0x80100015: return "SCARD_E_INVALID_ATR";
    // Original object relative source line 680.
    case 0x80100016: return "SCARD_E_NOT_TRANSACTED";
    // Original object relative source line 681.
    case 0x80100017: return "SCARD_E_READER_UNAVAILABLE";
    // Original object relative source line 682.
    case 0x80100018: return "SCARD_P_SHUTDOWN";
    // Original object relative source line 683.
    case 0x80100019: return "SCARD_E_PCI_TOO_SMALL";
    // Original object relative source line 684.
    case 0x8010001A: return "SCARD_E_READER_UNSUPPORTED";
    // Original object relative source line 685.
    case 0x8010001B: return "SCARD_E_DUPLICATE_READER";
    // Original object relative source line 686.
    case 0x8010001C: return "SCARD_E_CARD_UNSUPPORTED";
    // Original object relative source line 687.
    case 0x8010001D: return "SCARD_E_NO_SERVICE";
    // Original object relative source line 688.
    case 0x8010001E: return "SCARD_E_SERVICE_STOPPED";
    // Original object relative source line 689.
    case 0x8010001F: return "SCARD_E_UNEXPECTED";
    // Original object relative source line 690.
    case 0x80100020: return "SCARD_E_ICC_INSTALLATION";
    // Original object relative source line 691.
    case 0x80100021: return "SCARD_E_ICC_CREATEORDER";
    // Original object relative source line 692.
    case 0x80100022: return "SCARD_E_UNSUPPORTED_FEATURE";
    // Original object relative source line 693.
    case 0x80100023: return "SCARD_E_DIR_NOT_FOUND";
    // Original object relative source line 694.
    case 0x80100024: return "SCARD_E_FILE_NOT_FOUND";
    // Original object relative source line 695.
    case 0x80100025: return "SCARD_E_NO_DIR";
    // Original object relative source line 696.
    case 0x80100026: return "SCARD_E_NO_FILE";
    // Original object relative source line 697.
    case 0x80100027: return "SCARD_E_NO_ACCESS";
    // Original object relative source line 698.
    case 0x80100028: return "SCARD_E_WRITE_TOO_MANY";
    // Original object relative source line 699.
    case 0x80100029: return "SCARD_E_BAD_SEEK";
    // Original object relative source line 700.
    case 0x8010002A: return "SCARD_E_INVALID_CHV";
    // Original object relative source line 701.
    case 0x8010002B: return "SCARD_E_UNKNOWN_RES_MNG";
    // Original object relative source line 702.
    case 0x8010002C: return "SCARD_E_NO_SUCH_CERTIFICATE";
    // Original object relative source line 703.
    case 0x8010002D: return "SCARD_E_CERTIFICATE_UNAVAILABLE";
    // Original object relative source line 704.
    case 0x8010002E: return "SCARD_E_NO_READERS_AVAILABLE";
    // Original object relative source line 705.
    case 0x8010002F: return "SCARD_E_COMM_DATA_LOST";
    // Original object relative source line 706.
    case 0x80100065: return "SCARD_W_UNSUPPORTED_CARD";
    // Original object relative source line 707.
    case 0x80100066: return "SCARD_W_UNRESPONSIVE_CARD";
    // Original object relative source line 708.
    case 0x80100067: return "SCARD_W_UNPOWERED_CARD";
    // Original object relative source line 709.
    case 0x80100068: return "SCARD_W_RESET_CARD";
    // Original object relative source line 710.
    case 0x80100069: return "SCARD_W_REMOVED_CARD";
    // Original object relative source line 711.
    case 0x8010006A: return "SCARD_W_SECURITY_VIOLATION";
    // Original object relative source line 712.
    case 0x8010006B: return "SCARD_W_WRONG_CHV";
    // Original object relative source line 713.
    case 0x8010006C: return "SCARD_W_CHV_BLOCKED";
    // Original object relative source line 714.
    case 0x8010006D: return "SCARD_W_EOF";
    // Original object relative source line 715.
    case 0x8010006E: return "SCARD_W_CANCELLED_BY_USER";
    // Original object relative source line 716.
    case 0x80070001: return "ERROR_INVALID_FUNCTION";
    // Original object relative source line 717.
    case 0x00000002:
    case 0x80070002: return "ERROR_FILE_NOT_FOUND";
    // Original object relative source line 718.
    case 0x00000003:
    case 0x80070003: return "ERROR_PATH_NOT_FOUND";
    // Original object relative source line 719.
    case 0x00000004:
    case 0x80070004: return "ERROR_TOO_MANY_OPEN_FILES";
    // Original object relative source line 720.
    case 0x00000005: return "ERROR_ACCESS_DENIED";
    // Original object relative source line 721.
    case 0x00000006: return "ERROR_INVALID_HANDLE";
    // Original object relative source line 722.
    case 0x00000007:
    case 0x80070007: return "ERROR_ARENA_TRASHED";
    // Original object relative source line 723.
    case 0x00000008:
    case 0x80070008: return "ERROR_NOT_ENOUGH_MEMORY";
    // Original object relative source line 724.
    case 0x00000009:
    case 0x80070009: return "ERROR_INVALID_BLOCK";
    // Original object relative source line 725.
    case 0x0000000A:
    case 0x8007000A: return "ERROR_BAD_ENVIRONMENT";
    // Original object relative source line 726.
    case 0x0000000B:
    case 0x8007000B: return "ERROR_BAD_FORMAT";
    // Original object relative source line 727.
    case 0x0000000C:
    case 0x8007000C: return "ERROR_INVALID_ACCESS & DIERR_NOTACQUIRED";
    // Original object relative source line 728.
    case 0x0000000D:
    case 0x8007000D: return "ERROR_INVALID_DATA";
    // Original object relative source line 729.
    case 0x0000000E: return "ERROR_OUTOFMEMORY";
    // Original object relative source line 730.
    case 0x0000000F:
    case 0x8007000F: return "ERROR_INVALID_DRIVE";
    // Original object relative source line 731.
    case 0x00000010:
    case 0x80070010: return "ERROR_CURRENT_DIRECTORY";
    // Original object relative source line 732.
    case 0x00000011:
    case 0x80070011: return "ERROR_NOT_SAME_DEVICE";
    // Original object relative source line 733.
    case 0x00000012:
    case 0x80070012: return "ERROR_NO_MORE_FILES";
    // Original object relative source line 734.
    case 0x00000013:
    case 0x80070013: return "ERROR_WRITE_PROTECT";
    // Original object relative source line 735.
    case 0x00000014:
    case 0x80070014: return "ERROR_BAD_UNIT";
    // Original object relative source line 736.
    case 0x00000015:
    case 0x80070015: return "ERROR_NOT_READY & DIERR_NOTINITIALIZED";
    // Original object relative source line 737.
    case 0x00000016:
    case 0x80070016: return "ERROR_BAD_COMMAND";
    // Original object relative source line 738.
    case 0x00000017:
    case 0x80070017: return "ERROR_CRC";
    // Original object relative source line 739.
    case 0x00000018:
    case 0x80070018: return "ERROR_BAD_LENGTH";
    // Original object relative source line 740.
    case 0x00000019:
    case 0x80070019: return "ERROR_SEEK";
    // Original object relative source line 741.
    case 0x0000001A:
    case 0x8007001A: return "ERROR_NOT_DOS_DISK";
    // Original object relative source line 742.
    case 0x0000001B:
    case 0x8007001B: return "ERROR_SECTOR_NOT_FOUND";
    // Original object relative source line 743.
    case 0x0000001C:
    case 0x8007001C: return "ERROR_OUT_OF_PAPER";
    // Original object relative source line 744.
    case 0x0000001D:
    case 0x8007001D: return "ERROR_WRITE_FAULT";
    // Original object relative source line 745.
    case 0x0000001E:
    case 0x8007001E: return "ERROR_READ_FAULT & DIERR_INPUTLOST";
    // Original object relative source line 746.
    case 0x0000001F:
    case 0x8007001F: return "ERROR_GEN_FAILURE";
    // Original object relative source line 747.
    case 0x00000020:
    case 0x80070020: return "ERROR_SHARING_VIOLATION";
    // Original object relative source line 748.
    case 0x00000021:
    case 0x80070021: return "ERROR_LOCK_VIOLATION";
    // Original object relative source line 749.
    case 0x00000022:
    case 0x80070022: return "ERROR_WRONG_DISK";
    // Original object relative source line 750.
    case 0x00000024:
    case 0x80070024: return "ERROR_SHARING_BUFFER_EXCEEDED";
    // Original object relative source line 751.
    case 0x00000026:
    case 0x80070026: return "ERROR_HANDLE_EOF";
    // Original object relative source line 752.
    case 0x00000027:
    case 0x80070027: return "ERROR_HANDLE_DISK_FULL";
    // Original object relative source line 753.
    case 0x00000032:
    case 0x80070032: return "ERROR_NOT_SUPPORTED";
    // Original object relative source line 754.
    case 0x00000033:
    case 0x80070033: return "ERROR_REM_NOT_LIST";
    // Original object relative source line 755.
    case 0x00000034:
    case 0x80070034: return "ERROR_DUP_NAME";
    // Original object relative source line 756.
    case 0x00000035:
    case 0x80070035: return "ERROR_BAD_NETPATH";
    // Original object relative source line 757.
    case 0x00000036:
    case 0x80070036: return "ERROR_NETWORK_BUSY";
    // Original object relative source line 758.
    case 0x00000037:
    case 0x80070037: return "ERROR_DEV_NOT_EXIST";
    // Original object relative source line 759.
    case 0x00000038:
    case 0x80070038: return "ERROR_TOO_MANY_CMDS";
    // Original object relative source line 760.
    case 0x00000039:
    case 0x80070039: return "ERROR_ADAP_HDW_ERR";
    // Original object relative source line 761.
    case 0x0000003A:
    case 0x8007003A: return "ERROR_BAD_NET_RESP";
    // Original object relative source line 762.
    case 0x0000003B:
    case 0x8007003B: return "ERROR_UNEXP_NET_ERR";
    // Original object relative source line 763.
    case 0x0000003C:
    case 0x8007003C: return "ERROR_BAD_REM_ADAP";
    // Original object relative source line 764.
    case 0x0000003D:
    case 0x8007003D: return "ERROR_PRINTQ_FULL";
    // Original object relative source line 765.
    case 0x0000003E:
    case 0x8007003E: return "ERROR_NO_SPOOL_SPACE";
    // Original object relative source line 766.
    case 0x0000003F:
    case 0x8007003F: return "ERROR_PRINT_CANCELLED";
    // Original object relative source line 767.
    case 0x00000040:
    case 0x80070040: return "ERROR_NETNAME_DELETED";
    // Original object relative source line 768.
    case 0x00000041:
    case 0x80070041: return "ERROR_NETWORK_ACCESS_DENIED";
    // Original object relative source line 769.
    case 0x00000042:
    case 0x80070042: return "ERROR_BAD_DEV_TYPE";
    // Original object relative source line 770.
    case 0x00000043:
    case 0x80070043: return "ERROR_BAD_NET_NAME";
    // Original object relative source line 771.
    case 0x00000044:
    case 0x80070044: return "ERROR_TOO_MANY_NAMES";
    // Original object relative source line 772.
    case 0x00000045:
    case 0x80070045: return "ERROR_TOO_MANY_SESS";
    // Original object relative source line 773.
    case 0x00000046:
    case 0x80070046: return "ERROR_SHARING_PAUSED";
    // Original object relative source line 774.
    case 0x00000047:
    case 0x80070047: return "ERROR_REQ_NOT_ACCEP";
    // Original object relative source line 775.
    case 0x00000048:
    case 0x80070048: return "ERROR_REDIR_PAUSED";
    // Original object relative source line 776.
    case 0x00000050:
    case 0x80070050: return "ERROR_FILE_EXISTS";
    // Original object relative source line 777.
    case 0x00000052:
    case 0x80070052: return "ERROR_CANNOT_MAKE";
    // Original object relative source line 778.
    case 0x00000053:
    case 0x80070053: return "ERROR_FAIL_I24";
    // Original object relative source line 779.
    case 0x00000054:
    case 0x80070054: return "ERROR_OUT_OF_STRUCTURES";
    // Original object relative source line 780.
    case 0x00000055:
    case 0x80070055: return "ERROR_ALREADY_ASSIGNED";
    // Original object relative source line 781.
    case 0x00000056:
    case 0x80070056: return "ERROR_INVALID_PASSWORD";
    // Original object relative source line 782.
    case 0x00000057: return "ERROR_INVALID_PARAMETER";
    // Original object relative source line 783.
    case 0x00000058:
    case 0x80070058: return "ERROR_NET_WRITE_FAULT";
    // Original object relative source line 784.
    case 0x00000059:
    case 0x80070059: return "ERROR_NO_PROC_SLOTS";
    // Original object relative source line 785.
    case 0x00000064:
    case 0x80070064: return "ERROR_TOO_MANY_SEMAPHORES";
    // Original object relative source line 786.
    case 0x00000065:
    case 0x80070065: return "ERROR_EXCL_SEM_ALREADY_OWNED";
    // Original object relative source line 787.
    case 0x00000066:
    case 0x80070066: return "ERROR_SEM_IS_SET";
    // Original object relative source line 788.
    case 0x00000067:
    case 0x80070067: return "ERROR_TOO_MANY_SEM_REQUESTS";
    // Original object relative source line 789.
    case 0x00000068:
    case 0x80070068: return "ERROR_INVALID_AT_INTERRUPT_TIME";
    // Original object relative source line 790.
    case 0x00000069:
    case 0x80070069: return "ERROR_SEM_OWNER_DIED";
    // Original object relative source line 791.
    case 0x0000006A:
    case 0x8007006A: return "ERROR_SEM_USER_LIMIT";
    // Original object relative source line 792.
    case 0x0000006B:
    case 0x8007006B: return "ERROR_DISK_CHANGE";
    // Original object relative source line 793.
    case 0x0000006C:
    case 0x8007006C: return "ERROR_DRIVE_LOCKED";
    // Original object relative source line 794.
    case 0x0000006D:
    case 0x8007006D: return "ERROR_BROKEN_PIPE";
    // Original object relative source line 795.
    case 0x0000006E:
    case 0x8007006E: return "ERROR_OPEN_FAILED";
    // Original object relative source line 796.
    case 0x0000006F:
    case 0x8007006F: return "ERROR_BUFFER_OVERFLOW";
    // Original object relative source line 797.
    case 0x00000070:
    case 0x80070070: return "ERROR_DISK_FULL";
    // Original object relative source line 798.
    case 0x00000071:
    case 0x80070071: return "ERROR_NO_MORE_SEARCH_HANDLES";
    // Original object relative source line 799.
    case 0x00000072:
    case 0x80070072: return "ERROR_INVALID_TARGET_HANDLE";
    // Original object relative source line 800.
    case 0x00000075:
    case 0x80070075: return "ERROR_INVALID_CATEGORY";
    // Original object relative source line 801.
    case 0x00000076:
    case 0x80070076: return "ERROR_INVALID_VERIFY_SWITCH";
    // Original object relative source line 802.
    case 0x00000077:
    case 0x80070077: return "ERROR_BAD_DRIVER_LEVEL & DIERR_BADDRIVERVER";
    // Original object relative source line 803.
    case 0x00000078:
    case 0x80070078: return "ERROR_CALL_NOT_IMPLEMENTED";
    // Original object relative source line 804.
    case 0x00000079:
    case 0x80070079: return "ERROR_SEM_TIMEOUT";
    // Original object relative source line 805.
    case 0x0000007A:
    case 0x8007007A: return "ERROR_INSUFFICIENT_BUFFER";
    // Original object relative source line 806.
    case 0x0000007B:
    case 0x8007007B: return "ERROR_INVALID_NAME";
    // Original object relative source line 807.
    case 0x0000007C:
    case 0x8007007C: return "ERROR_INVALID_LEVEL";
    // Original object relative source line 808.
    case 0x0000007D:
    case 0x8007007D: return "ERROR_NO_VOLUME_LABEL";
    // Original object relative source line 809.
    case 0x0000007E:
    case 0x8007007E: return "ERROR_MOD_NOT_FOUND";
    // Original object relative source line 810.
    case 0x0000007F:
    case 0x8007007F: return "ERROR_PROC_NOT_FOUND";
    // Original object relative source line 811.
    case 0x00000080:
    case 0x80070080: return "ERROR_WAIT_NO_CHILDREN";
    // Original object relative source line 812.
    case 0x00000081:
    case 0x80070081: return "ERROR_CHILD_NOT_COMPLETE";
    // Original object relative source line 813.
    case 0x00000082:
    case 0x80070082: return "ERROR_DIRECT_ACCESS_HANDLE";
    // Original object relative source line 814.
    case 0x00000083:
    case 0x80070083: return "ERROR_NEGATIVE_SEEK";
    // Original object relative source line 815.
    case 0x00000084:
    case 0x80070084: return "ERROR_SEEK_ON_DEVICE";
    // Original object relative source line 816.
    case 0x00000085:
    case 0x80070085: return "ERROR_IS_JOIN_TARGET";
    // Original object relative source line 817.
    case 0x00000086:
    case 0x80070086: return "ERROR_IS_JOINED";
    // Original object relative source line 818.
    case 0x00000087:
    case 0x80070087: return "ERROR_IS_SUBSTED";
    // Original object relative source line 819.
    case 0x00000088:
    case 0x80070088: return "ERROR_NOT_JOINED";
    // Original object relative source line 820.
    case 0x00000089:
    case 0x80070089: return "ERROR_NOT_SUBSTED";
    // Original object relative source line 821.
    case 0x0000008A:
    case 0x8007008A: return "ERROR_JOIN_TO_JOIN";
    // Original object relative source line 822.
    case 0x0000008B:
    case 0x8007008B: return "ERROR_SUBST_TO_SUBST";
    // Original object relative source line 823.
    case 0x0000008C:
    case 0x8007008C: return "ERROR_JOIN_TO_SUBST";
    // Original object relative source line 824.
    case 0x0000008D:
    case 0x8007008D: return "ERROR_SUBST_TO_JOIN";
    // Original object relative source line 825.
    case 0x0000008E:
    case 0x8007008E: return "ERROR_BUSY_DRIVE";
    // Original object relative source line 826.
    case 0x0000008F:
    case 0x8007008F: return "ERROR_SAME_DRIVE";
    // Original object relative source line 827.
    case 0x00000090:
    case 0x80070090: return "ERROR_DIR_NOT_ROOT";
    // Original object relative source line 828.
    case 0x00000091:
    case 0x80070091: return "ERROR_DIR_NOT_EMPTY";
    // Original object relative source line 829.
    case 0x00000092:
    case 0x80070092: return "ERROR_IS_SUBST_PATH";
    // Original object relative source line 830.
    case 0x00000093:
    case 0x80070093: return "ERROR_IS_JOIN_PATH";
    // Original object relative source line 831.
    case 0x00000094:
    case 0x80070094: return "ERROR_PATH_BUSY";
    // Original object relative source line 832.
    case 0x00000095:
    case 0x80070095: return "ERROR_IS_SUBST_TARGET";
    // Original object relative source line 833.
    case 0x00000096:
    case 0x80070096: return "ERROR_SYSTEM_TRACE";
    // Original object relative source line 834.
    case 0x00000097:
    case 0x80070097: return "ERROR_INVALID_EVENT_COUNT";
    // Original object relative source line 835.
    case 0x00000098:
    case 0x80070098: return "ERROR_TOO_MANY_MUXWAITERS";
    // Original object relative source line 836.
    case 0x00000099:
    case 0x80070099: return "ERROR_INVALID_LIST_FORMAT";
    // Original object relative source line 837.
    case 0x0000009A:
    case 0x8007009A: return "ERROR_LABEL_TOO_LONG";
    // Original object relative source line 838.
    case 0x0000009B:
    case 0x8007009B: return "ERROR_TOO_MANY_TCBS";
    // Original object relative source line 839.
    case 0x0000009C:
    case 0x8007009C: return "ERROR_SIGNAL_REFUSED";
    // Original object relative source line 840.
    case 0x0000009D:
    case 0x8007009D: return "ERROR_DISCARDED";
    // Original object relative source line 841.
    case 0x0000009E:
    case 0x8007009E: return "ERROR_NOT_LOCKED";
    // Original object relative source line 842.
    case 0x0000009F:
    case 0x8007009F: return "ERROR_BAD_THREADID_ADDR";
    // Original object relative source line 843.
    case 0x000000A0:
    case 0x800700A0: return "ERROR_BAD_ARGUMENTS";
    // Original object relative source line 844.
    case 0x000000A1:
    case 0x800700A1: return "ERROR_BAD_PATHNAME";
    // Original object relative source line 845.
    case 0x000000A2:
    case 0x800700A2: return "ERROR_SIGNAL_PENDING";
    // Original object relative source line 846.
    case 0x000000A4:
    case 0x800700A4: return "ERROR_MAX_THRDS_REACHED";
    // Original object relative source line 847.
    case 0x000000A7:
    case 0x800700A7: return "ERROR_LOCK_FAILED";
    // Original object relative source line 848.
    case 0x000000AA:
    case 0x800700AA: return "ERROR_BUSY & DIERR_ACQUIRED";
    // Original object relative source line 849.
    case 0x000000AD:
    case 0x800700AD: return "ERROR_CANCEL_VIOLATION";
    // Original object relative source line 850.
    case 0x000000AE:
    case 0x800700AE: return "ERROR_ATOMIC_LOCKS_NOT_SUPPORTED";
    // Original object relative source line 851.
    case 0x000000B4:
    case 0x800700B4: return "ERROR_INVALID_SEGMENT_NUMBER";
    // Original object relative source line 852.
    case 0x000000B6:
    case 0x800700B6: return "ERROR_INVALID_ORDINAL";
    // Original object relative source line 853.
    case 0x000000B7:
    case 0x800700B7: return "ERROR_ALREADY_EXISTS";
    // Original object relative source line 854.
    case 0x000000BA:
    case 0x800700BA: return "ERROR_INVALID_FLAG_NUMBER";
    // Original object relative source line 855.
    case 0x000000BB:
    case 0x800700BB: return "ERROR_SEM_NOT_FOUND";
    // Original object relative source line 856.
    case 0x000000BC:
    case 0x800700BC: return "ERROR_INVALID_STARTING_CODESEG";
    // Original object relative source line 857.
    case 0x000000BD:
    case 0x800700BD: return "ERROR_INVALID_STACKSEG";
    // Original object relative source line 858.
    case 0x000000BE:
    case 0x800700BE: return "ERROR_INVALID_MODULETYPE";
    // Original object relative source line 859.
    case 0x000000BF:
    case 0x800700BF: return "ERROR_INVALID_EXE_SIGNATURE";
    // Original object relative source line 860.
    case 0x000000C0:
    case 0x800700C0: return "ERROR_EXE_MARKED_INVALID";
    // Original object relative source line 861.
    case 0x000000C1:
    case 0x800700C1: return "ERROR_BAD_EXE_FORMAT";
    // Original object relative source line 862.
    case 0x000000C2:
    case 0x800700C2: return "ERROR_ITERATED_DATA_EXCEEDS_64k";
    // Original object relative source line 863.
    case 0x000000C3:
    case 0x800700C3: return "ERROR_INVALID_MINALLOCSIZE";
    // Original object relative source line 864.
    case 0x000000C4:
    case 0x800700C4: return "ERROR_DYNLINK_FROM_INVALID_RING";
    // Original object relative source line 865.
    case 0x000000C5:
    case 0x800700C5: return "ERROR_IOPL_NOT_ENABLED";
    // Original object relative source line 866.
    case 0x000000C6:
    case 0x800700C6: return "ERROR_INVALID_SEGDPL";
    // Original object relative source line 867.
    case 0x000000C7:
    case 0x800700C7: return "ERROR_AUTODATASEG_EXCEEDS_64k";
    // Original object relative source line 868.
    case 0x000000C8: return "ERROR_RING2SEG_MUST_BE_MOVABLE";
    // Original object relative source line 869.
    case 0x000000C9: return "ERROR_RELOC_CHAIN_XEEDS_SEGLIM";
    // Original object relative source line 870.
    case 0x000000CA:
    case 0x800700CA: return "ERROR_INFLOOP_IN_RELOC_CHAIN";
    // Original object relative source line 871.
    case 0x000000CB:
    case 0x800700CB: return "ERROR_ENVVAR_NOT_FOUND";
    // Original object relative source line 872.
    case 0x000000CD:
    case 0x800700CD: return "ERROR_NO_SIGNAL_SENT";
    // Original object relative source line 873.
    case 0x000000CE:
    case 0x800700CE: return "ERROR_FILENAME_EXCED_RANGE";
    // Original object relative source line 874.
    case 0x000000CF:
    case 0x800700CF: return "ERROR_RING2_STACK_IN_USE";
    // Original object relative source line 875.
    case 0x000000D0:
    case 0x800700D0: return "ERROR_META_EXPANSION_TOO_LONG";
    // Original object relative source line 876.
    case 0x000000D1:
    case 0x800700D1: return "ERROR_INVALID_SIGNAL_NUMBER";
    // Original object relative source line 877.
    case 0x000000D2:
    case 0x800700D2: return "ERROR_THREAD_1_INACTIVE";
    // Original object relative source line 878.
    case 0x000000D4:
    case 0x800700D4: return "ERROR_LOCKED";
    // Original object relative source line 879.
    case 0x000000D6:
    case 0x800700D6: return "ERROR_TOO_MANY_MODULES";
    // Original object relative source line 880.
    case 0x000000D7:
    case 0x800700D7: return "ERROR_NESTING_NOT_ALLOWED";
    // Original object relative source line 881.
    case 0x000000D8:
    case 0x800700D8: return "ERROR_EXE_MACHINE_TYPE_MISMATCH";
    // Original object relative source line 882.
    case 0x000000E6:
    case 0x800700E6: return "ERROR_BAD_PIPE";
    // Original object relative source line 883.
    case 0x000000E7:
    case 0x800700E7: return "ERROR_PIPE_BUSY";
    // Original object relative source line 884.
    case 0x000000E8:
    case 0x800700E8: return "ERROR_NO_DATA";
    // Original object relative source line 885.
    case 0x000000E9:
    case 0x800700E9: return "ERROR_PIPE_NOT_CONNECTED";
    // Original object relative source line 886.
    case 0x000000EA:
    case 0x800700EA: return "ERROR_MORE_DATA";
    // Original object relative source line 887.
    case 0x000000F0:
    case 0x800700F0: return "ERROR_VC_DISCONNECTED";
    // Original object relative source line 888.
    case 0x000000FE:
    case 0x800700FE: return "ERROR_INVALID_EA_NAME";
    // Original object relative source line 889.
    case 0x000000FF:
    case 0x800700FF: return "ERROR_EA_LIST_INCONSISTENT";
    // Original object relative source line 890.
    case 0x00000102:
    case 0x80070102: return "WAIT_TIMEOUT";
    // Original object relative source line 891.
    case 0x00000103:
    case 0x80070103: return "ERROR_NO_MORE_ITEMS & DIERR_NOMOREITEMS";
    // Original object relative source line 892.
    case 0x0000010A:
    case 0x8007010A: return "ERROR_CANNOT_COPY";
    // Original object relative source line 893.
    case 0x0000010B:
    case 0x8007010B: return "ERROR_DIRECTORY";
    // Original object relative source line 894.
    case 0x00000113:
    case 0x80070113: return "ERROR_EAS_DIDNT_FIT";
    // Original object relative source line 895.
    case 0x00000114:
    case 0x80070114: return "ERROR_EA_FILE_CORRUPT";
    // Original object relative source line 896.
    case 0x00000115:
    case 0x80070115: return "ERROR_EA_TABLE_FULL";
    // Original object relative source line 897.
    case 0x00000116:
    case 0x80070116: return "ERROR_INVALID_EA_HANDLE";
    // Original object relative source line 898.
    case 0x0000011A:
    case 0x8007011A: return "ERROR_EAS_NOT_SUPPORTED";
    // Original object relative source line 899.
    case 0x00000120:
    case 0x80070120: return "ERROR_NOT_OWNER";
    // Original object relative source line 900.
    case 0x0000012A:
    case 0x8007012A: return "ERROR_TOO_MANY_POSTS";
    // Original object relative source line 901.
    case 0x0000012B:
    case 0x8007012B: return "ERROR_PARTIAL_COPY";
    // Original object relative source line 902.
    case 0x0000012C:
    case 0x8007012C: return "ERROR_OPLOCK_NOT_GRANTED";
    // Original object relative source line 903.
    case 0x0000012D:
    case 0x8007012D: return "ERROR_INVALID_OPLOCK_PROTOCOL";
    // Original object relative source line 904.
    case 0x0000013D:
    case 0x8007013D: return "ERROR_MR_MID_NOT_FOUND";
    // Original object relative source line 905.
    case 0x000001E7:
    case 0x800701E7: return "ERROR_INVALID_ADDRESS";
    // Original object relative source line 906.
    case 0x00000216:
    case 0x80070216: return "ERROR_ARITHMETIC_OVERFLOW";
    // Original object relative source line 907.
    case 0x00000217:
    case 0x80070217: return "ERROR_PIPE_CONNECTED";
    // Original object relative source line 908.
    case 0x00000218:
    case 0x80070218: return "ERROR_PIPE_LISTENING";
    // Original object relative source line 909.
    case 0x000003E2:
    case 0x800703E2: return "ERROR_EA_ACCESS_DENIED";
    // Original object relative source line 910.
    case 0x000003E3:
    case 0x800703E3: return "ERROR_OPERATION_ABORTED";
    // Original object relative source line 911.
    case 0x000003E4:
    case 0x800703E4: return "ERROR_IO_INCOMPLETE";
    // Original object relative source line 912.
    case 0x000003E5:
    case 0x800703E5: return "ERROR_IO_PENDING";
    // Original object relative source line 913.
    case 0x000003E6:
    case 0x800703E6: return "ERROR_NOACCESS";
    // Original object relative source line 914.
    case 0x000003E7:
    case 0x800703E7: return "ERROR_SWAPERROR";
    // Original object relative source line 915.
    case 0x000003E9:
    case 0x800703E9: return "ERROR_STACK_OVERFLOW";
    // Original object relative source line 916.
    case 0x000003EA:
    case 0x800703EA: return "ERROR_INVALID_MESSAGE";
    // Original object relative source line 917.
    case 0x000003EB:
    case 0x800703EB: return "ERROR_CAN_NOT_COMPLETE";
    // Original object relative source line 918.
    case 0x000003EC:
    case 0x800703EC: return "ERROR_INVALID_FLAGS";
    // Original object relative source line 919.
    case 0x000003ED:
    case 0x800703ED: return "ERROR_UNRECOGNIZED_VOLUME";
    // Original object relative source line 920.
    case 0x000003EE:
    case 0x800703EE: return "ERROR_FILE_INVALID";
    // Original object relative source line 921.
    case 0x000003EF:
    case 0x800703EF: return "ERROR_FULLSCREEN_MODE";
    // Original object relative source line 922.
    case 0x000003F0:
    case 0x800703F0: return "ERROR_NO_TOKEN";
    // Original object relative source line 923.
    case 0x000003F1:
    case 0x800703F1: return "ERROR_BADDB";
    // Original object relative source line 924.
    case 0x000003F2:
    case 0x800703F2: return "ERROR_BADKEY";
    // Original object relative source line 925.
    case 0x000003F3:
    case 0x800703F3: return "ERROR_CANTOPEN";
    // Original object relative source line 926.
    case 0x000003F4:
    case 0x800703F4: return "ERROR_CANTREAD";
    // Original object relative source line 927.
    case 0x000003F5:
    case 0x800703F5: return "ERROR_CANTWRITE";
    // Original object relative source line 928.
    case 0x000003F6:
    case 0x800703F6: return "ERROR_REGISTRY_RECOVERED";
    // Original object relative source line 929.
    case 0x000003F7:
    case 0x800703F7: return "ERROR_REGISTRY_CORRUPT";
    // Original object relative source line 930.
    case 0x000003F8:
    case 0x800703F8: return "ERROR_REGISTRY_IO_FAILED";
    // Original object relative source line 931.
    case 0x000003F9:
    case 0x800703F9: return "ERROR_NOT_REGISTRY_FILE";
    // Original object relative source line 932.
    case 0x000003FA:
    case 0x800703FA: return "ERROR_KEY_DELETED";
    // Original object relative source line 933.
    case 0x000003FB:
    case 0x800703FB: return "ERROR_NO_LOG_SPACE";
    // Original object relative source line 934.
    case 0x000003FC:
    case 0x800703FC: return "ERROR_KEY_HAS_CHILDREN";
    // Original object relative source line 935.
    case 0x000003FD:
    case 0x800703FD: return "ERROR_CHILD_MUST_BE_VOLATILE";
    // Original object relative source line 936.
    case 0x000003FE:
    case 0x800703FE: return "ERROR_NOTIFY_ENUM_DIR";
    // Original object relative source line 937.
    case 0x0000041B:
    case 0x8007041B: return "ERROR_DEPENDENT_SERVICES_RUNNING";
    // Original object relative source line 938.
    case 0x0000041C:
    case 0x8007041C: return "ERROR_INVALID_SERVICE_CONTROL";
    // Original object relative source line 939.
    case 0x0000041D:
    case 0x8007041D: return "ERROR_SERVICE_REQUEST_TIMEOUT";
    // Original object relative source line 940.
    case 0x0000041E:
    case 0x8007041E: return "ERROR_SERVICE_NO_THREAD";
    // Original object relative source line 941.
    case 0x0000041F:
    case 0x8007041F: return "ERROR_SERVICE_DATABASE_LOCKED";
    // Original object relative source line 942.
    case 0x00000420:
    case 0x80070420: return "ERROR_SERVICE_ALREADY_RUNNING";
    // Original object relative source line 943.
    case 0x00000421:
    case 0x80070421: return "ERROR_INVALID_SERVICE_ACCOUNT";
    // Original object relative source line 944.
    case 0x00000422:
    case 0x80070422: return "ERROR_SERVICE_DISABLED";
    // Original object relative source line 945.
    case 0x00000423:
    case 0x80070423: return "ERROR_CIRCULAR_DEPENDENCY";
    // Original object relative source line 946.
    case 0x00000424:
    case 0x80070424: return "ERROR_SERVICE_DOES_NOT_EXIST";
    // Original object relative source line 947.
    case 0x00000425:
    case 0x80070425: return "ERROR_SERVICE_CANNOT_ACCEPT_CTRL";
    // Original object relative source line 948.
    case 0x00000426:
    case 0x80070426: return "ERROR_SERVICE_NOT_ACTIVE";
    // Original object relative source line 949.
    case 0x00000427:
    case 0x80070427: return "ERROR_FAILED_SERVICE_CONTROLLER_CONNECT";
    // Original object relative source line 950.
    case 0x00000428:
    case 0x80070428: return "ERROR_EXCEPTION_IN_SERVICE";
    // Original object relative source line 951.
    case 0x00000429:
    case 0x80070429: return "ERROR_DATABASE_DOES_NOT_EXIST";
    // Original object relative source line 952.
    case 0x0000042A:
    case 0x8007042A: return "ERROR_SERVICE_SPECIFIC_ERROR";
    // Original object relative source line 953.
    case 0x0000042B:
    case 0x8007042B: return "ERROR_PROCESS_ABORTED";
    // Original object relative source line 954.
    case 0x0000042C:
    case 0x8007042C: return "ERROR_SERVICE_DEPENDENCY_FAIL";
    // Original object relative source line 955.
    case 0x0000042D:
    case 0x8007042D: return "ERROR_SERVICE_LOGON_FAILED";
    // Original object relative source line 956.
    case 0x0000042E:
    case 0x8007042E: return "ERROR_SERVICE_START_HANG";
    // Original object relative source line 957.
    case 0x0000042F:
    case 0x8007042F: return "ERROR_INVALID_SERVICE_LOCK";
    // Original object relative source line 958.
    case 0x00000430:
    case 0x80070430: return "ERROR_SERVICE_MARKED_FOR_DELETE";
    // Original object relative source line 959.
    case 0x00000431:
    case 0x80070431: return "ERROR_SERVICE_EXISTS";
    // Original object relative source line 960.
    case 0x00000432:
    case 0x80070432: return "ERROR_ALREADY_RUNNING_LKG";
    // Original object relative source line 961.
    case 0x00000433:
    case 0x80070433: return "ERROR_SERVICE_DEPENDENCY_DELETED";
    // Original object relative source line 962.
    case 0x00000434:
    case 0x80070434: return "ERROR_BOOT_ALREADY_ACCEPTED";
    // Original object relative source line 963.
    case 0x00000435:
    case 0x80070435: return "ERROR_SERVICE_NEVER_STARTED";
    // Original object relative source line 964.
    case 0x00000436:
    case 0x80070436: return "ERROR_DUPLICATE_SERVICE_NAME";
    // Original object relative source line 965.
    case 0x00000437:
    case 0x80070437: return "ERROR_DIFFERENT_SERVICE_ACCOUNT";
    // Original object relative source line 966.
    case 0x00000438:
    case 0x80070438: return "ERROR_CANNOT_DETECT_DRIVER_FAILURE";
    // Original object relative source line 967.
    case 0x00000439:
    case 0x80070439: return "ERROR_CANNOT_DETECT_PROCESS_ABORT";
    // Original object relative source line 968.
    case 0x0000043A:
    case 0x8007043A: return "ERROR_NO_RECOVERY_PROGRAM";
    // Original object relative source line 969.
    case 0x0000043B:
    case 0x8007043B: return "ERROR_SERVICE_NOT_IN_EXE";
    // Original object relative source line 970.
    case 0x0000044C:
    case 0x8007044C: return "ERROR_END_OF_MEDIA";
    // Original object relative source line 971.
    case 0x0000044D:
    case 0x8007044D: return "ERROR_FILEMARK_DETECTED";
    // Original object relative source line 972.
    case 0x0000044E:
    case 0x8007044E: return "ERROR_BEGINNING_OF_MEDIA";
    // Original object relative source line 973.
    case 0x0000044F:
    case 0x8007044F: return "ERROR_SETMARK_DETECTED";
    // Original object relative source line 974.
    case 0x00000450:
    case 0x80070450: return "ERROR_NO_DATA_DETECTED";
    // Original object relative source line 975.
    case 0x00000451:
    case 0x80070451: return "ERROR_PARTITION_FAILURE";
    // Original object relative source line 976.
    case 0x00000452:
    case 0x80070452: return "ERROR_INVALID_BLOCK_LENGTH";
    // Original object relative source line 977.
    case 0x00000453:
    case 0x80070453: return "ERROR_DEVICE_NOT_PARTITIONED";
    // Original object relative source line 978.
    case 0x00000454:
    case 0x80070454: return "ERROR_UNABLE_TO_LOCK_MEDIA";
    // Original object relative source line 979.
    case 0x00000455:
    case 0x80070455: return "ERROR_UNABLE_TO_UNLOAD_MEDIA";
    // Original object relative source line 980.
    case 0x00000456:
    case 0x80070456: return "ERROR_MEDIA_CHANGED";
    // Original object relative source line 981.
    case 0x00000457:
    case 0x80070457: return "ERROR_BUS_RESET";
    // Original object relative source line 982.
    case 0x00000458:
    case 0x80070458: return "ERROR_NO_MEDIA_IN_DRIVE";
    // Original object relative source line 983.
    case 0x00000459:
    case 0x80070459: return "ERROR_NO_UNICODE_TRANSLATION";
    // Original object relative source line 984.
    case 0x0000045A:
    case 0x8007045A: return "ERROR_DLL_INIT_FAILED";
    // Original object relative source line 985.
    case 0x0000045B:
    case 0x8007045B: return "ERROR_SHUTDOWN_IN_PROGRESS";
    // Original object relative source line 986.
    case 0x0000045C:
    case 0x8007045C: return "ERROR_NO_SHUTDOWN_IN_PROGRESS";
    // Original object relative source line 987.
    case 0x0000045D:
    case 0x8007045D: return "ERROR_IO_DEVICE";
    // Original object relative source line 988.
    case 0x0000045E:
    case 0x8007045E: return "ERROR_SERIAL_NO_DEVICE";
    // Original object relative source line 989.
    case 0x0000045F:
    case 0x8007045F: return "ERROR_IRQ_BUSY";
    // Original object relative source line 990.
    case 0x00000460:
    case 0x80070460: return "ERROR_MORE_WRITES";
    // Original object relative source line 991.
    case 0x00000461:
    case 0x80070461: return "ERROR_COUNTER_TIMEOUT";
    // Original object relative source line 992.
    case 0x00000462:
    case 0x80070462: return "ERROR_FLOPPY_ID_MARK_NOT_FOUND";
    // Original object relative source line 993.
    case 0x00000463:
    case 0x80070463: return "ERROR_FLOPPY_WRONG_CYLINDER";
    // Original object relative source line 994.
    case 0x00000464:
    case 0x80070464: return "ERROR_FLOPPY_UNKNOWN_ERROR";
    // Original object relative source line 995.
    case 0x00000465:
    case 0x80070465: return "ERROR_FLOPPY_BAD_REGISTERS";
    // Original object relative source line 996.
    case 0x00000466:
    case 0x80070466: return "ERROR_DISK_RECALIBRATE_FAILED";
    // Original object relative source line 997.
    case 0x00000467:
    case 0x80070467: return "ERROR_DISK_OPERATION_FAILED";
    // Original object relative source line 998.
    case 0x00000468:
    case 0x80070468: return "ERROR_DISK_RESET_FAILED";
    // Original object relative source line 999.
    case 0x00000469:
    case 0x80070469: return "ERROR_EOM_OVERFLOW";
    // Original object relative source line 1000.
    case 0x0000046A:
    case 0x8007046A: return "ERROR_NOT_ENOUGH_SERVER_MEMORY";
    // Original object relative source line 1001.
    case 0x0000046B:
    case 0x8007046B: return "ERROR_POSSIBLE_DEADLOCK";
    // Original object relative source line 1002.
    case 0x0000046C:
    case 0x8007046C: return "ERROR_MAPPED_ALIGNMENT";
    // Original object relative source line 1003.
    case 0x00000474:
    case 0x80070474: return "ERROR_SET_POWER_STATE_VETOED";
    // Original object relative source line 1004.
    case 0x00000475:
    case 0x80070475: return "ERROR_SET_POWER_STATE_FAILED";
    // Original object relative source line 1005.
    case 0x00000476:
    case 0x80070476: return "ERROR_TOO_MANY_LINKS";
    // Original object relative source line 1006.
    case 0x0000047E:
    case 0x8007047E: return "ERROR_OLD_WIN_VERSION & DIERR_OLDDIRECTINPUTVERSION";
    // Original object relative source line 1007.
    case 0x0000047F:
    case 0x8007047F: return "ERROR_APP_WRONG_OS";
    // Original object relative source line 1008.
    case 0x00000480:
    case 0x80070480: return "ERROR_SINGLE_INSTANCE_APP";
    // Original object relative source line 1009.
    case 0x00000481:
    case 0x80070481: return "ERROR_RMODE_APP & DIERR_BETADIRECTINPUTVERSION";
    // Original object relative source line 1010.
    case 0x00000482:
    case 0x80070482: return "ERROR_INVALID_DLL";
    // Original object relative source line 1011.
    case 0x00000483:
    case 0x80070483: return "ERROR_NO_ASSOCIATION";
    // Original object relative source line 1012.
    case 0x00000484:
    case 0x80070484: return "ERROR_DDE_FAIL";
    // Original object relative source line 1013.
    case 0x00000485:
    case 0x80070485: return "ERROR_DLL_NOT_FOUND";
    // Original object relative source line 1014.
    case 0x00000486:
    case 0x80070486: return "ERROR_NO_MORE_USER_HANDLES";
    // Original object relative source line 1015.
    case 0x00000487:
    case 0x80070487: return "ERROR_MESSAGE_SYNC_ONLY";
    // Original object relative source line 1016.
    case 0x00000488:
    case 0x80070488: return "ERROR_SOURCE_ELEMENT_EMPTY";
    // Original object relative source line 1017.
    case 0x00000489:
    case 0x80070489: return "ERROR_DESTINATION_ELEMENT_FULL";
    // Original object relative source line 1018.
    case 0x0000048A:
    case 0x8007048A: return "ERROR_ILLEGAL_ELEMENT_ADDRESS";
    // Original object relative source line 1019.
    case 0x0000048B:
    case 0x8007048B: return "ERROR_MAGAZINE_NOT_PRESENT";
    // Original object relative source line 1020.
    case 0x0000048C:
    case 0x8007048C: return "ERROR_DEVICE_REINITIALIZATION_NEEDED";
    // Original object relative source line 1021.
    case 0x0000048D:
    case 0x8007048D: return "ERROR_DEVICE_REQUIRES_CLEANING";
    // Original object relative source line 1022.
    case 0x0000048E:
    case 0x8007048E: return "ERROR_DEVICE_DOOR_OPEN";
    // Original object relative source line 1023.
    case 0x0000048F:
    case 0x8007048F: return "ERROR_DEVICE_NOT_CONNECTED";
    // Original object relative source line 1024.
    case 0x00000490:
    case 0x80070490: return "ERROR_NOT_FOUND & E_PROP_ID_UNSUPPORTED";
    // Original object relative source line 1025.
    case 0x00000491:
    case 0x80070491: return "ERROR_NO_MATCH";
    // Original object relative source line 1026.
    case 0x00000492:
    case 0x80070492: return "ERROR_SET_NOT_FOUND & E_PROP_SET_UNSUPPORTED";
    // Original object relative source line 1027.
    case 0x00000493:
    case 0x80070493: return "ERROR_POINT_NOT_FOUND";
    // Original object relative source line 1028.
    case 0x00000494:
    case 0x80070494: return "ERROR_NO_TRACKING_SERVICE";
    // Original object relative source line 1029.
    case 0x00000495:
    case 0x80070495: return "ERROR_NO_VOLUME_ID";
    // Original object relative source line 1030.
    case 0x00000497:
    case 0x80070497: return "ERROR_UNABLE_TO_REMOVE_REPLACED";
    // Original object relative source line 1031.
    case 0x00000498:
    case 0x80070498: return "ERROR_UNABLE_TO_MOVE_REPLACEMENT";
    // Original object relative source line 1032.
    case 0x00000499:
    case 0x80070499: return "ERROR_UNABLE_TO_MOVE_REPLACEMENT_2";
    // Original object relative source line 1033.
    case 0x0000049A:
    case 0x8007049A: return "ERROR_JOURNAL_DELETE_IN_PROGRESS";
    // Original object relative source line 1034.
    case 0x0000049B:
    case 0x8007049B: return "ERROR_JOURNAL_NOT_ACTIVE";
    // Original object relative source line 1035.
    case 0x0000049C:
    case 0x8007049C: return "ERROR_POTENTIAL_FILE_FOUND";
    // Original object relative source line 1036.
    case 0x000004B0:
    case 0x800704B0: return "ERROR_BAD_DEVICE";
    // Original object relative source line 1037.
    case 0x000004B1:
    case 0x800704B1: return "ERROR_CONNECTION_UNAVAIL";
    // Original object relative source line 1038.
    case 0x000004B2:
    case 0x800704B2: return "ERROR_DEVICE_ALREADY_REMEMBERED";
    // Original object relative source line 1039.
    case 0x000004B3:
    case 0x800704B3: return "ERROR_NO_NET_OR_BAD_PATH";
    // Original object relative source line 1040.
    case 0x000004B4:
    case 0x800704B4: return "ERROR_BAD_PROVIDER";
    // Original object relative source line 1041.
    case 0x000004B5:
    case 0x800704B5: return "ERROR_CANNOT_OPEN_PROFILE";
    // Original object relative source line 1042.
    case 0x000004B6:
    case 0x800704B6: return "ERROR_BAD_PROFILE";
    // Original object relative source line 1043.
    case 0x000004B7:
    case 0x800704B7: return "ERROR_NOT_CONTAINER";
    // Original object relative source line 1044.
    case 0x000004B8:
    case 0x800704B8: return "ERROR_EXTENDED_ERROR";
    // Original object relative source line 1045.
    case 0x000004B9:
    case 0x800704B9: return "ERROR_INVALID_GROUPNAME";
    // Original object relative source line 1046.
    case 0x000004BA:
    case 0x800704BA: return "ERROR_INVALID_COMPUTERNAME";
    // Original object relative source line 1047.
    case 0x000004BB:
    case 0x800704BB: return "ERROR_INVALID_EVENTNAME";
    // Original object relative source line 1048.
    case 0x000004BC:
    case 0x800704BC: return "ERROR_INVALID_DOMAINNAME";
    // Original object relative source line 1049.
    case 0x000004BD:
    case 0x800704BD: return "ERROR_INVALID_SERVICENAME";
    // Original object relative source line 1050.
    case 0x000004BE:
    case 0x800704BE: return "ERROR_INVALID_NETNAME";
    // Original object relative source line 1051.
    case 0x000004BF:
    case 0x800704BF: return "ERROR_INVALID_SHARENAME";
    // Original object relative source line 1052.
    case 0x000004C0:
    case 0x800704C0: return "ERROR_INVALID_PASSWORDNAME";
    // Original object relative source line 1053.
    case 0x000004C1:
    case 0x800704C1: return "ERROR_INVALID_MESSAGENAME";
    // Original object relative source line 1054.
    case 0x000004C2:
    case 0x800704C2: return "ERROR_INVALID_MESSAGEDEST";
    // Original object relative source line 1055.
    case 0x000004C3:
    case 0x800704C3: return "ERROR_SESSION_CREDENTIAL_CONFLICT";
    // Original object relative source line 1056.
    case 0x000004C4:
    case 0x800704C4: return "ERROR_REMOTE_SESSION_LIMIT_EXCEEDED";
    // Original object relative source line 1057.
    case 0x000004C5:
    case 0x800704C5: return "ERROR_DUP_DOMAINNAME";
    // Original object relative source line 1058.
    case 0x000004C6:
    case 0x800704C6: return "ERROR_NO_NETWORK";
    // Original object relative source line 1059.
    case 0x000004C7:
    case 0x800704C7: return "ERROR_CANCELLED";
    // Original object relative source line 1060.
    case 0x000004C8:
    case 0x800704C8: return "ERROR_USER_MAPPED_FILE";
    // Original object relative source line 1061.
    case 0x000004C9:
    case 0x800704C9: return "ERROR_CONNECTION_REFUSED";
    // Original object relative source line 1062.
    case 0x000004CA:
    case 0x800704CA: return "ERROR_GRACEFUL_DISCONNECT";
    // Original object relative source line 1063.
    case 0x000004CB:
    case 0x800704CB: return "ERROR_ADDRESS_ALREADY_ASSOCIATED";
    // Original object relative source line 1064.
    case 0x000004CC:
    case 0x800704CC: return "ERROR_ADDRESS_NOT_ASSOCIATED";
    // Original object relative source line 1065.
    case 0x000004CD:
    case 0x800704CD: return "ERROR_CONNECTION_INVALID";
    // Original object relative source line 1066.
    case 0x000004CE:
    case 0x800704CE: return "ERROR_CONNECTION_ACTIVE";
    // Original object relative source line 1067.
    case 0x000004CF:
    case 0x800704CF: return "ERROR_NETWORK_UNREACHABLE";
    // Original object relative source line 1068.
    case 0x000004D0:
    case 0x800704D0: return "ERROR_HOST_UNREACHABLE";
    // Original object relative source line 1069.
    case 0x000004D1:
    case 0x800704D1: return "ERROR_PROTOCOL_UNREACHABLE";
    // Original object relative source line 1070.
    case 0x000004D2:
    case 0x800704D2: return "ERROR_PORT_UNREACHABLE";
    // Original object relative source line 1071.
    case 0x000004D3:
    case 0x800704D3: return "ERROR_REQUEST_ABORTED";
    // Original object relative source line 1072.
    case 0x000004D4:
    case 0x800704D4: return "ERROR_CONNECTION_ABORTED";
    // Original object relative source line 1073.
    case 0x000004D5:
    case 0x800704D5: return "ERROR_RETRY";
    // Original object relative source line 1074.
    case 0x000004D6:
    case 0x800704D6: return "ERROR_CONNECTION_COUNT_LIMIT";
    // Original object relative source line 1075.
    case 0x000004D7:
    case 0x800704D7: return "ERROR_LOGIN_TIME_RESTRICTION";
    // Original object relative source line 1076.
    case 0x000004D8:
    case 0x800704D8: return "ERROR_LOGIN_WKSTA_RESTRICTION";
    // Original object relative source line 1077.
    case 0x000004D9:
    case 0x800704D9: return "ERROR_INCORRECT_ADDRESS";
    // Original object relative source line 1078.
    case 0x000004DA:
    case 0x800704DA: return "ERROR_ALREADY_REGISTERED";
    // Original object relative source line 1079.
    case 0x000004DB:
    case 0x800704DB: return "ERROR_SERVICE_NOT_FOUND";
    // Original object relative source line 1080.
    case 0x000004DC:
    case 0x800704DC: return "ERROR_NOT_AUTHENTICATED";
    // Original object relative source line 1081.
    case 0x000004DD:
    case 0x800704DD: return "ERROR_NOT_LOGGED_ON";
    // Original object relative source line 1082.
    case 0x000004DE:
    case 0x800704DE: return "ERROR_CONTINUE";
    // Original object relative source line 1083.
    case 0x000004DF:
    case 0x800704DF: return "ERROR_ALREADY_INITIALIZED & DIERR_ALREADYINITIALIZED";
    // Original object relative source line 1084.
    case 0x000004E0:
    case 0x800704E0: return "ERROR_NO_MORE_DEVICES";
    // Original object relative source line 1085.
    case 0x000004E1:
    case 0x800704E1: return "ERROR_NO_SUCH_SITE";
    // Original object relative source line 1086.
    case 0x000004E2:
    case 0x800704E2: return "ERROR_DOMAIN_CONTROLLER_EXISTS";
    // Original object relative source line 1087.
    case 0x00000514:
    case 0x80070514: return "ERROR_NOT_ALL_ASSIGNED";
    // Original object relative source line 1088.
    case 0x00000515:
    case 0x80070515: return "ERROR_SOME_NOT_MAPPED";
    // Original object relative source line 1089.
    case 0x00000516:
    case 0x80070516: return "ERROR_NO_QUOTAS_FOR_ACCOUNT";
    // Original object relative source line 1090.
    case 0x00000517:
    case 0x80070517: return "ERROR_LOCAL_USER_SESSION_KEY";
    // Original object relative source line 1091.
    case 0x00000518:
    case 0x80070518: return "ERROR_NULL_LM_PASSWORD";
    // Original object relative source line 1092.
    case 0x00000519:
    case 0x80070519: return "ERROR_UNKNOWN_REVISION";
    // Original object relative source line 1093.
    case 0x0000051A:
    case 0x8007051A: return "ERROR_REVISION_MISMATCH";
    // Original object relative source line 1094.
    case 0x0000051B:
    case 0x8007051B: return "ERROR_INVALID_OWNER";
    // Original object relative source line 1095.
    case 0x0000051C:
    case 0x8007051C: return "ERROR_INVALID_PRIMARY_GROUP";
    // Original object relative source line 1096.
    case 0x0000051D:
    case 0x8007051D: return "ERROR_NO_IMPERSONATION_TOKEN";
    // Original object relative source line 1097.
    case 0x0000051E:
    case 0x8007051E: return "ERROR_CANT_DISABLE_MANDATORY";
    // Original object relative source line 1098.
    case 0x0000051F:
    case 0x8007051F: return "ERROR_NO_LOGON_SERVERS";
    // Original object relative source line 1099.
    case 0x00000520:
    case 0x80070520: return "ERROR_NO_SUCH_LOGON_SESSION";
    // Original object relative source line 1100.
    case 0x00000521:
    case 0x80070521: return "ERROR_NO_SUCH_PRIVILEGE";
    // Original object relative source line 1101.
    case 0x00000522:
    case 0x80070522: return "ERROR_PRIVILEGE_NOT_HELD";
    // Original object relative source line 1102.
    case 0x00000523:
    case 0x80070523: return "ERROR_INVALID_ACCOUNT_NAME";
    // Original object relative source line 1103.
    case 0x00000524:
    case 0x80070524: return "ERROR_USER_EXISTS";
    // Original object relative source line 1104.
    case 0x00000525:
    case 0x80070525: return "ERROR_NO_SUCH_USER";
    // Original object relative source line 1105.
    case 0x00000526:
    case 0x80070526: return "ERROR_GROUP_EXISTS";
    // Original object relative source line 1106.
    case 0x00000527:
    case 0x80070527: return "ERROR_NO_SUCH_GROUP";
    // Original object relative source line 1107.
    case 0x00000528:
    case 0x80070528: return "ERROR_MEMBER_IN_GROUP";
    // Original object relative source line 1108.
    case 0x00000529:
    case 0x80070529: return "ERROR_MEMBER_NOT_IN_GROUP";
    // Original object relative source line 1109.
    case 0x0000052A:
    case 0x8007052A: return "ERROR_LAST_ADMIN";
    // Original object relative source line 1110.
    case 0x0000052B:
    case 0x8007052B: return "ERROR_WRONG_PASSWORD";
    // Original object relative source line 1111.
    case 0x0000052C:
    case 0x8007052C: return "ERROR_ILL_FORMED_PASSWORD";
    // Original object relative source line 1112.
    case 0x0000052D:
    case 0x8007052D: return "ERROR_PASSWORD_RESTRICTION";
    // Original object relative source line 1113.
    case 0x0000052E:
    case 0x8007052E: return "ERROR_LOGON_FAILURE";
    // Original object relative source line 1114.
    case 0x0000052F:
    case 0x8007052F: return "ERROR_ACCOUNT_RESTRICTION";
    // Original object relative source line 1115.
    case 0x00000530:
    case 0x80070530: return "ERROR_INVALID_LOGON_HOURS";
    // Original object relative source line 1116.
    case 0x00000531:
    case 0x80070531: return "ERROR_INVALID_WORKSTATION";
    // Original object relative source line 1117.
    case 0x00000532:
    case 0x80070532: return "ERROR_PASSWORD_EXPIRED";
    // Original object relative source line 1118.
    case 0x00000533:
    case 0x80070533: return "ERROR_ACCOUNT_DISABLED";
    // Original object relative source line 1119.
    case 0x00000534:
    case 0x80070534: return "ERROR_NONE_MAPPED";
    // Original object relative source line 1120.
    case 0x00000535:
    case 0x80070535: return "ERROR_TOO_MANY_LUIDS_REQUESTED";
    // Original object relative source line 1121.
    case 0x00000536:
    case 0x80070536: return "ERROR_LUIDS_EXHAUSTED";
    // Original object relative source line 1122.
    case 0x00000537:
    case 0x80070537: return "ERROR_INVALID_SUB_AUTHORITY";
    // Original object relative source line 1123.
    case 0x00000538:
    case 0x80070538: return "ERROR_INVALID_ACL";
    // Original object relative source line 1124.
    case 0x00000539:
    case 0x80070539: return "ERROR_INVALID_SID";
    // Original object relative source line 1125.
    case 0x0000053A:
    case 0x8007053A: return "ERROR_INVALID_SECURITY_DESCR";
    // Original object relative source line 1126.
    case 0x0000053C:
    case 0x8007053C: return "ERROR_BAD_INHERITANCE_ACL";
    // Original object relative source line 1127.
    case 0x0000053D:
    case 0x8007053D: return "ERROR_SERVER_DISABLED";
    // Original object relative source line 1128.
    case 0x0000053E:
    case 0x8007053E: return "ERROR_SERVER_NOT_DISABLED";
    // Original object relative source line 1129.
    case 0x0000053F:
    case 0x8007053F: return "ERROR_INVALID_ID_AUTHORITY";
    // Original object relative source line 1130.
    case 0x00000540:
    case 0x80070540: return "ERROR_ALLOTTED_SPACE_EXCEEDED";
    // Original object relative source line 1131.
    case 0x00000541:
    case 0x80070541: return "ERROR_INVALID_GROUP_ATTRIBUTES";
    // Original object relative source line 1132.
    case 0x00000542:
    case 0x80070542: return "ERROR_BAD_IMPERSONATION_LEVEL";
    // Original object relative source line 1133.
    case 0x00000543:
    case 0x80070543: return "ERROR_CANT_OPEN_ANONYMOUS";
    // Original object relative source line 1134.
    case 0x00000544:
    case 0x80070544: return "ERROR_BAD_VALIDATION_CLASS";
    // Original object relative source line 1135.
    case 0x00000545:
    case 0x80070545: return "ERROR_BAD_TOKEN_TYPE";
    // Original object relative source line 1136.
    case 0x00000546:
    case 0x80070546: return "ERROR_NO_SECURITY_ON_OBJECT";
    // Original object relative source line 1137.
    case 0x00000547:
    case 0x80070547: return "ERROR_CANT_ACCESS_DOMAIN_INFO";
    // Original object relative source line 1138.
    case 0x00000548:
    case 0x80070548: return "ERROR_INVALID_SERVER_STATE";
    // Original object relative source line 1139.
    case 0x00000549:
    case 0x80070549: return "ERROR_INVALID_DOMAIN_STATE";
    // Original object relative source line 1140.
    case 0x0000054A:
    case 0x8007054A: return "ERROR_INVALID_DOMAIN_ROLE";
    // Original object relative source line 1141.
    case 0x0000054B:
    case 0x8007054B: return "ERROR_NO_SUCH_DOMAIN";
    // Original object relative source line 1142.
    case 0x0000054C:
    case 0x8007054C: return "ERROR_DOMAIN_EXISTS";
    // Original object relative source line 1143.
    case 0x0000054D:
    case 0x8007054D: return "ERROR_DOMAIN_LIMIT_EXCEEDED";
    // Original object relative source line 1144.
    case 0x0000054E:
    case 0x8007054E: return "ERROR_INTERNAL_DB_CORRUPTION";
    // Original object relative source line 1145.
    case 0x0000054F:
    case 0x8007054F: return "ERROR_INTERNAL_ERROR";
    // Original object relative source line 1146.
    case 0x00000550:
    case 0x80070550: return "ERROR_GENERIC_NOT_MAPPED";
    // Original object relative source line 1147.
    case 0x00000551:
    case 0x80070551: return "ERROR_BAD_DESCRIPTOR_FORMAT";
    // Original object relative source line 1148.
    case 0x00000552:
    case 0x80070552: return "ERROR_NOT_LOGON_PROCESS";
    // Original object relative source line 1149.
    case 0x00000553:
    case 0x80070553: return "ERROR_LOGON_SESSION_EXISTS";
    // Original object relative source line 1150.
    case 0x00000554:
    case 0x80070554: return "ERROR_NO_SUCH_PACKAGE";
    // Original object relative source line 1151.
    case 0x00000555:
    case 0x80070555: return "ERROR_BAD_LOGON_SESSION_STATE";
    // Original object relative source line 1152.
    case 0x00000556:
    case 0x80070556: return "ERROR_LOGON_SESSION_COLLISION";
    // Original object relative source line 1153.
    case 0x00000557:
    case 0x80070557: return "ERROR_INVALID_LOGON_TYPE";
    // Original object relative source line 1154.
    case 0x00000558:
    case 0x80070558: return "ERROR_CANNOT_IMPERSONATE";
    // Original object relative source line 1155.
    case 0x00000559:
    case 0x80070559: return "ERROR_RXACT_INVALID_STATE";
    // Original object relative source line 1156.
    case 0x0000055A:
    case 0x8007055A: return "ERROR_RXACT_COMMIT_FAILURE";
    // Original object relative source line 1157.
    case 0x0000055B:
    case 0x8007055B: return "ERROR_SPECIAL_ACCOUNT";
    // Original object relative source line 1158.
    case 0x0000055C:
    case 0x8007055C: return "ERROR_SPECIAL_GROUP";
    // Original object relative source line 1159.
    case 0x0000055D:
    case 0x8007055D: return "ERROR_SPECIAL_USER";
    // Original object relative source line 1160.
    case 0x0000055E:
    case 0x8007055E: return "ERROR_MEMBERS_PRIMARY_GROUP";
    // Original object relative source line 1161.
    case 0x0000055F:
    case 0x8007055F: return "ERROR_TOKEN_ALREADY_IN_USE";
    // Original object relative source line 1162.
    case 0x00000560:
    case 0x80070560: return "ERROR_NO_SUCH_ALIAS";
    // Original object relative source line 1163.
    case 0x00000561:
    case 0x80070561: return "ERROR_MEMBER_NOT_IN_ALIAS";
    // Original object relative source line 1164.
    case 0x00000562:
    case 0x80070562: return "ERROR_MEMBER_IN_ALIAS";
    // Original object relative source line 1165.
    case 0x00000563:
    case 0x80070563: return "ERROR_ALIAS_EXISTS";
    // Original object relative source line 1166.
    case 0x00000564:
    case 0x80070564: return "ERROR_LOGON_NOT_GRANTED";
    // Original object relative source line 1167.
    case 0x00000565:
    case 0x80070565: return "ERROR_TOO_MANY_SECRETS";
    // Original object relative source line 1168.
    case 0x00000566:
    case 0x80070566: return "ERROR_SECRET_TOO_LONG";
    // Original object relative source line 1169.
    case 0x00000567:
    case 0x80070567: return "ERROR_INTERNAL_DB_ERROR";
    // Original object relative source line 1170.
    case 0x00000568:
    case 0x80070568: return "ERROR_TOO_MANY_CONTEXT_IDS";
    // Original object relative source line 1171.
    case 0x00000569:
    case 0x80070569: return "ERROR_LOGON_TYPE_NOT_GRANTED";
    // Original object relative source line 1172.
    case 0x0000056A:
    case 0x8007056A: return "ERROR_NT_CROSS_ENCRYPTION_REQUIRED";
    // Original object relative source line 1173.
    case 0x0000056B:
    case 0x8007056B: return "ERROR_NO_SUCH_MEMBER";
    // Original object relative source line 1174.
    case 0x0000056C:
    case 0x8007056C: return "ERROR_INVALID_MEMBER";
    // Original object relative source line 1175.
    case 0x0000056D:
    case 0x8007056D: return "ERROR_TOO_MANY_SIDS";
    // Original object relative source line 1176.
    case 0x0000056E:
    case 0x8007056E: return "ERROR_LM_CROSS_ENCRYPTION_REQUIRED";
    // Original object relative source line 1177.
    case 0x0000056F:
    case 0x8007056F: return "ERROR_NO_INHERITANCE";
    // Original object relative source line 1178.
    case 0x00000570:
    case 0x80070570: return "ERROR_FILE_CORRUPT";
    // Original object relative source line 1179.
    case 0x00000571:
    case 0x80070571: return "ERROR_DISK_CORRUPT";
    // Original object relative source line 1180.
    case 0x00000572:
    case 0x80070572: return "ERROR_NO_USER_SESSION_KEY";
    // Original object relative source line 1181.
    case 0x00000573:
    case 0x80070573: return "ERROR_LICENSE_QUOTA_EXCEEDED";
    // Original object relative source line 1182.
    case 0x00000574:
    case 0x80070574: return "ERROR_WRONG_TARGET_NAME";
    // Original object relative source line 1183.
    case 0x00000575:
    case 0x80070575: return "ERROR_MUTUAL_AUTH_FAILED";
    // Original object relative source line 1184.
    case 0x00000576:
    case 0x80070576: return "ERROR_TIME_SKEW";
    // Original object relative source line 1185.
    case 0x00000578:
    case 0x80070578: return "ERROR_INVALID_WINDOW_HANDLE";
    // Original object relative source line 1186.
    case 0x00000579:
    case 0x80070579: return "ERROR_INVALID_MENU_HANDLE";
    // Original object relative source line 1187.
    case 0x0000057A:
    case 0x8007057A: return "ERROR_INVALID_CURSOR_HANDLE";
    // Original object relative source line 1188.
    case 0x0000057B:
    case 0x8007057B: return "ERROR_INVALID_ACCEL_HANDLE";
    // Original object relative source line 1189.
    case 0x0000057C:
    case 0x8007057C: return "ERROR_INVALID_HOOK_HANDLE";
    // Original object relative source line 1190.
    case 0x0000057D:
    case 0x8007057D: return "ERROR_INVALID_DWP_HANDLE";
    // Original object relative source line 1191.
    case 0x0000057E:
    case 0x8007057E: return "ERROR_TLW_WITH_WSCHILD";
    // Original object relative source line 1192.
    case 0x0000057F:
    case 0x8007057F: return "ERROR_CANNOT_FIND_WND_CLASS";
    // Original object relative source line 1193.
    case 0x00000580:
    case 0x80070580: return "ERROR_WINDOW_OF_OTHER_THREAD";
    // Original object relative source line 1194.
    case 0x00000581:
    case 0x80070581: return "ERROR_HOTKEY_ALREADY_REGISTERED";
    // Original object relative source line 1195.
    case 0x00000582:
    case 0x80070582: return "ERROR_CLASS_ALREADY_EXISTS";
    // Original object relative source line 1196.
    case 0x00000583:
    case 0x80070583: return "ERROR_CLASS_DOES_NOT_EXIST";
    // Original object relative source line 1197.
    case 0x00000584:
    case 0x80070584: return "ERROR_CLASS_HAS_WINDOWS";
    // Original object relative source line 1198.
    case 0x00000585:
    case 0x80070585: return "ERROR_INVALID_INDEX";
    // Original object relative source line 1199.
    case 0x00000586:
    case 0x80070586: return "ERROR_INVALID_ICON_HANDLE";
    // Original object relative source line 1200.
    case 0x00000587:
    case 0x80070587: return "ERROR_PRIVATE_DIALOG_INDEX";
    // Original object relative source line 1201.
    case 0x00000588:
    case 0x80070588: return "ERROR_LISTBOX_ID_NOT_FOUND";
    // Original object relative source line 1202.
    case 0x00000589:
    case 0x80070589: return "ERROR_NO_WILDCARD_CHARACTERS";
    // Original object relative source line 1203.
    case 0x0000058A:
    case 0x8007058A: return "ERROR_CLIPBOARD_NOT_OPEN";
    // Original object relative source line 1204.
    case 0x0000058B:
    case 0x8007058B: return "ERROR_HOTKEY_NOT_REGISTERED";
    // Original object relative source line 1205.
    case 0x0000058C:
    case 0x8007058C: return "ERROR_WINDOW_NOT_DIALOG";
    // Original object relative source line 1206.
    case 0x0000058D:
    case 0x8007058D: return "ERROR_CONTROL_ID_NOT_FOUND";
    // Original object relative source line 1207.
    case 0x0000058E:
    case 0x8007058E: return "ERROR_INVALID_COMBOBOX_MESSAGE";
    // Original object relative source line 1208.
    case 0x0000058F:
    case 0x8007058F: return "ERROR_WINDOW_NOT_COMBOBOX";
    // Original object relative source line 1209.
    case 0x00000590:
    case 0x80070590: return "ERROR_INVALID_EDIT_HEIGHT";
    // Original object relative source line 1210.
    case 0x00000591:
    case 0x80070591: return "ERROR_DC_NOT_FOUND";
    // Original object relative source line 1211.
    case 0x00000592:
    case 0x80070592: return "ERROR_INVALID_HOOK_FILTER";
    // Original object relative source line 1212.
    case 0x00000593:
    case 0x80070593: return "ERROR_INVALID_FILTER_PROC";
    // Original object relative source line 1213.
    case 0x00000594:
    case 0x80070594: return "ERROR_HOOK_NEEDS_HMOD";
    // Original object relative source line 1214.
    case 0x00000595:
    case 0x80070595: return "ERROR_GLOBAL_ONLY_HOOK";
    // Original object relative source line 1215.
    case 0x00000596:
    case 0x80070596: return "ERROR_JOURNAL_HOOK_SET";
    // Original object relative source line 1216.
    case 0x00000597:
    case 0x80070597: return "ERROR_HOOK_NOT_INSTALLED";
    // Original object relative source line 1217.
    case 0x00000598:
    case 0x80070598: return "ERROR_INVALID_LB_MESSAGE";
    // Original object relative source line 1218.
    case 0x00000599:
    case 0x80070599: return "ERROR_SETCOUNT_ON_BAD_LB";
    // Original object relative source line 1219.
    case 0x0000059A:
    case 0x8007059A: return "ERROR_LB_WITHOUT_TABSTOPS";
    // Original object relative source line 1220.
    case 0x0000059B:
    case 0x8007059B: return "ERROR_DESTROY_OBJECT_OF_OTHER_THREAD";
    // Original object relative source line 1221.
    case 0x0000059C:
    case 0x8007059C: return "ERROR_CHILD_WINDOW_MENU";
    // Original object relative source line 1222.
    case 0x0000059D:
    case 0x8007059D: return "ERROR_NO_SYSTEM_MENU";
    // Original object relative source line 1223.
    case 0x0000059E:
    case 0x8007059E: return "ERROR_INVALID_MSGBOX_STYLE";
    // Original object relative source line 1224.
    case 0x0000059F:
    case 0x8007059F: return "ERROR_INVALID_SPI_VALUE";
    // Original object relative source line 1225.
    case 0x000005A0:
    case 0x800705A0: return "ERROR_SCREEN_ALREADY_LOCKED";
    // Original object relative source line 1226.
    case 0x000005A1:
    case 0x800705A1: return "ERROR_HWNDS_HAVE_DIFF_PARENT";
    // Original object relative source line 1227.
    case 0x000005A2:
    case 0x800705A2: return "ERROR_NOT_CHILD_WINDOW";
    // Original object relative source line 1228.
    case 0x000005A3:
    case 0x800705A3: return "ERROR_INVALID_GW_COMMAND";
    // Original object relative source line 1229.
    case 0x000005A4:
    case 0x800705A4: return "ERROR_INVALID_THREAD_ID";
    // Original object relative source line 1230.
    case 0x000005A5:
    case 0x800705A5: return "ERROR_NON_MDICHILD_WINDOW";
    // Original object relative source line 1231.
    case 0x000005A6:
    case 0x800705A6: return "ERROR_POPUP_ALREADY_ACTIVE";
    // Original object relative source line 1232.
    case 0x000005A7:
    case 0x800705A7: return "ERROR_NO_SCROLLBARS";
    // Original object relative source line 1233.
    case 0x000005A8:
    case 0x800705A8: return "ERROR_INVALID_SCROLLBAR_RANGE";
    // Original object relative source line 1234.
    case 0x000005A9:
    case 0x800705A9: return "ERROR_INVALID_SHOWWIN_COMMAND";
    // Original object relative source line 1235.
    case 0x000005AA:
    case 0x800705AA: return "ERROR_NO_SYSTEM_RESOURCES";
    // Original object relative source line 1236.
    case 0x000005AB:
    case 0x800705AB: return "ERROR_NONPAGED_SYSTEM_RESOURCES";
    // Original object relative source line 1237.
    case 0x000005AC:
    case 0x800705AC: return "ERROR_PAGED_SYSTEM_RESOURCES";
    // Original object relative source line 1238.
    case 0x000005AD:
    case 0x800705AD: return "ERROR_WORKING_SET_QUOTA";
    // Original object relative source line 1239.
    case 0x000005AE:
    case 0x800705AE: return "ERROR_PAGEFILE_QUOTA";
    // Original object relative source line 1240.
    case 0x000005AF:
    case 0x800705AF: return "ERROR_COMMITMENT_LIMIT";
    // Original object relative source line 1241.
    case 0x000005B0:
    case 0x800705B0: return "ERROR_MENU_ITEM_NOT_FOUND";
    // Original object relative source line 1242.
    case 0x000005B1:
    case 0x800705B1: return "ERROR_INVALID_KEYBOARD_HANDLE";
    // Original object relative source line 1243.
    case 0x000005B2:
    case 0x800705B2: return "ERROR_HOOK_TYPE_NOT_ALLOWED";
    // Original object relative source line 1244.
    case 0x000005B3:
    case 0x800705B3: return "ERROR_REQUIRES_INTERACTIVE_WINDOWSTATION";
    // Original object relative source line 1245.
    case 0x000005B4:
    case 0x800705B4: return "ERROR_TIMEOUT";
    // Original object relative source line 1246.
    case 0x000005B5:
    case 0x800705B5: return "ERROR_INVALID_MONITOR_HANDLE";
    // Original object relative source line 1247.
    case 0x000005DC:
    case 0x800705DC: return "ERROR_EVENTLOG_FILE_CORRUPT";
    // Original object relative source line 1248.
    case 0x000005DD:
    case 0x800705DD: return "ERROR_EVENTLOG_CANT_START";
    // Original object relative source line 1249.
    case 0x000005DE:
    case 0x800705DE: return "ERROR_LOG_FILE_FULL";
    // Original object relative source line 1250.
    case 0x000005DF:
    case 0x800705DF: return "ERROR_EVENTLOG_FILE_CHANGED";
    // Original object relative source line 1251.
    case 0x00000642:
    case 0x80070642: return "ERROR_INSTALL_USEREXIT";
    // Original object relative source line 1252.
    case 0x00000643:
    case 0x80070643: return "ERROR_INSTALL_FAILURE";
    // Original object relative source line 1253.
    case 0x00000644:
    case 0x80070644: return "ERROR_INSTALL_SUSPEND";
    // Original object relative source line 1254.
    case 0x00000645:
    case 0x80070645: return "ERROR_UNKNOWN_PRODUCT";
    // Original object relative source line 1255.
    case 0x00000646:
    case 0x80070646: return "ERROR_UNKNOWN_FEATURE";
    // Original object relative source line 1256.
    case 0x00000647:
    case 0x80070647: return "ERROR_UNKNOWN_COMPONENT";
    // Original object relative source line 1257.
    case 0x00000648:
    case 0x80070648: return "ERROR_UNKNOWN_PROPERTY";
    // Original object relative source line 1258.
    case 0x00000649:
    case 0x80070649: return "ERROR_INVALID_HANDLE_STATE";
    // Original object relative source line 1259.
    case 0x0000064A:
    case 0x8007064A: return "ERROR_BAD_CONFIGURATION";
    // Original object relative source line 1260.
    case 0x0000064B:
    case 0x8007064B: return "ERROR_INDEX_ABSENT";
    // Original object relative source line 1261.
    case 0x0000064C:
    case 0x8007064C: return "ERROR_INSTALL_SOURCE_ABSENT";
    // Original object relative source line 1262.
    case 0x0000064E:
    case 0x8007064E: return "ERROR_PRODUCT_UNINSTALLED";
    // Original object relative source line 1263.
    case 0x0000064F:
    case 0x8007064F: return "ERROR_BAD_QUERY_SYNTAX";
    // Original object relative source line 1264.
    case 0x00000650:
    case 0x80070650: return "ERROR_INVALID_FIELD";
    // Original object relative source line 1265.
    case 0x00000651:
    case 0x80070651: return "ERROR_DEVICE_REMOVED";
    // Original object relative source line 1266.
    case 0x000006A4:
    case 0x800706A4: return "RPC_S_INVALID_STRING_BINDING";
    // Original object relative source line 1267.
    case 0x000006A5:
    case 0x800706A5: return "RPC_S_WRONG_KIND_OF_BINDING";
    // Original object relative source line 1268.
    case 0x000006A6:
    case 0x800706A6: return "RPC_S_INVALID_BINDING";
    // Original object relative source line 1269.
    case 0x000006A7:
    case 0x800706A7: return "RPC_S_PROTSEQ_NOT_SUPPORTED";
    // Original object relative source line 1270.
    case 0x000006A8:
    case 0x800706A8: return "RPC_S_INVALID_RPC_PROTSEQ";
    // Original object relative source line 1271.
    case 0x000006A9:
    case 0x800706A9: return "RPC_S_INVALID_STRING_UUID";
    // Original object relative source line 1272.
    case 0x000006AA:
    case 0x800706AA: return "RPC_S_INVALID_ENDPOINT_FORMAT";
    // Original object relative source line 1273.
    case 0x000006AB:
    case 0x800706AB: return "RPC_S_INVALID_NET_ADDR";
    // Original object relative source line 1274.
    case 0x000006AC:
    case 0x800706AC: return "RPC_S_NO_ENDPOINT_FOUND";
    // Original object relative source line 1275.
    case 0x000006AD:
    case 0x800706AD: return "RPC_S_INVALID_TIMEOUT";
    // Original object relative source line 1276.
    case 0x000006AE:
    case 0x800706AE: return "RPC_S_OBJECT_NOT_FOUND";
    // Original object relative source line 1277.
    case 0x000006AF:
    case 0x800706AF: return "RPC_S_ALREADY_REGISTERED";
    // Original object relative source line 1278.
    case 0x000006B0:
    case 0x800706B0: return "RPC_S_TYPE_ALREADY_REGISTERED";
    // Original object relative source line 1279.
    case 0x000006B1:
    case 0x800706B1: return "RPC_S_ALREADY_LISTENING";
    // Original object relative source line 1280.
    case 0x000006B2:
    case 0x800706B2: return "RPC_S_NO_PROTSEQS_REGISTERED";
    // Original object relative source line 1281.
    case 0x000006B3:
    case 0x800706B3: return "RPC_S_NOT_LISTENING";
    // Original object relative source line 1282.
    case 0x000006B4:
    case 0x800706B4: return "RPC_S_UNKNOWN_MGR_TYPE";
    // Original object relative source line 1283.
    case 0x000006B5:
    case 0x800706B5: return "RPC_S_UNKNOWN_IF";
    // Original object relative source line 1284.
    case 0x000006B6:
    case 0x800706B6: return "RPC_S_NO_BINDINGS";
    // Original object relative source line 1285.
    case 0x000006B7:
    case 0x800706B7: return "RPC_S_NO_PROTSEQS";
    // Original object relative source line 1286.
    case 0x000006B8:
    case 0x800706B8: return "RPC_S_CANT_CREATE_ENDPOINT";
    // Original object relative source line 1287.
    case 0x000006B9:
    case 0x800706B9: return "RPC_S_OUT_OF_RESOURCES";
    // Original object relative source line 1288.
    case 0x000006BA:
    case 0x800706BA: return "RPC_S_SERVER_UNAVAILABLE";
    // Original object relative source line 1289.
    case 0x000006BB:
    case 0x800706BB: return "RPC_S_SERVER_TOO_BUSY";
    // Original object relative source line 1290.
    case 0x000006BC:
    case 0x800706BC: return "RPC_S_INVALID_NETWORK_OPTIONS";
    // Original object relative source line 1291.
    case 0x000006BD:
    case 0x800706BD: return "RPC_S_NO_CALL_ACTIVE";
    // Original object relative source line 1292.
    case 0x000006BE:
    case 0x800706BE: return "RPC_S_CALL_FAILED";
    // Original object relative source line 1293.
    case 0x000006BF:
    case 0x800706BF: return "RPC_S_CALL_FAILED_DNE";
    // Original object relative source line 1294.
    case 0x000006C0:
    case 0x800706C0: return "RPC_S_PROTOCOL_ERROR";
    // Original object relative source line 1295.
    case 0x000006C2:
    case 0x800706C2: return "RPC_S_UNSUPPORTED_TRANS_SYN";
    // Original object relative source line 1296.
    case 0x000006C4:
    case 0x800706C4: return "RPC_S_UNSUPPORTED_TYPE";
    // Original object relative source line 1297.
    case 0x000006C5:
    case 0x800706C5: return "RPC_S_INVALID_TAG";
    // Original object relative source line 1298.
    case 0x000006C6:
    case 0x800706C6: return "RPC_S_INVALID_BOUND";
    // Original object relative source line 1299.
    case 0x000006C7:
    case 0x800706C7: return "RPC_S_NO_ENTRY_NAME";
    // Original object relative source line 1300.
    case 0x000006C8:
    case 0x800706C8: return "RPC_S_INVALID_NAME_SYNTAX";
    // Original object relative source line 1301.
    case 0x000006C9:
    case 0x800706C9: return "RPC_S_UNSUPPORTED_NAME_SYNTAX";
    // Original object relative source line 1302.
    case 0x000006CB:
    case 0x800706CB: return "RPC_S_UUID_NO_ADDRESS";
    // Original object relative source line 1303.
    case 0x000006CC:
    case 0x800706CC: return "RPC_S_DUPLICATE_ENDPOINT";
    // Original object relative source line 1304.
    case 0x000006CD:
    case 0x800706CD: return "RPC_S_UNKNOWN_AUTHN_TYPE";
    // Original object relative source line 1305.
    case 0x000006CE:
    case 0x800706CE: return "RPC_S_MAX_CALLS_TOO_SMALL";
    // Original object relative source line 1306.
    case 0x000006CF:
    case 0x800706CF: return "RPC_S_STRING_TOO_LONG";
    // Original object relative source line 1307.
    case 0x000006D0:
    case 0x800706D0: return "RPC_S_PROTSEQ_NOT_FOUND";
    // Original object relative source line 1308.
    case 0x000006D1:
    case 0x800706D1: return "RPC_S_PROCNUM_OUT_OF_RANGE";
    // Original object relative source line 1309.
    case 0x000006D2:
    case 0x800706D2: return "RPC_S_BINDING_HAS_NO_AUTH";
    // Original object relative source line 1310.
    case 0x000006D3:
    case 0x800706D3: return "RPC_S_UNKNOWN_AUTHN_SERVICE";
    // Original object relative source line 1311.
    case 0x000006D4:
    case 0x800706D4: return "RPC_S_UNKNOWN_AUTHN_LEVEL";
    // Original object relative source line 1312.
    case 0x000006D5:
    case 0x800706D5: return "RPC_S_INVALID_AUTH_IDENTITY";
    // Original object relative source line 1313.
    case 0x000006D6:
    case 0x800706D6: return "RPC_S_UNKNOWN_AUTHZ_SERVICE";
    // Original object relative source line 1314.
    case 0x000006D7:
    case 0x800706D7: return "EPT_S_INVALID_ENTRY";
    // Original object relative source line 1315.
    case 0x000006D8:
    case 0x800706D8: return "EPT_S_CANT_PERFORM_OP";
    // Original object relative source line 1316.
    case 0x000006D9:
    case 0x800706D9: return "EPT_S_NOT_REGISTERED";
    // Original object relative source line 1317.
    case 0x000006DA:
    case 0x800706DA: return "RPC_S_NOTHING_TO_EXPORT";
    // Original object relative source line 1318.
    case 0x000006DB:
    case 0x800706DB: return "RPC_S_INCOMPLETE_NAME";
    // Original object relative source line 1319.
    case 0x000006DC:
    case 0x800706DC: return "RPC_S_INVALID_VERS_OPTION";
    // Original object relative source line 1320.
    case 0x000006DD:
    case 0x800706DD: return "RPC_S_NO_MORE_MEMBERS";
    // Original object relative source line 1321.
    case 0x000006DE:
    case 0x800706DE: return "RPC_S_NOT_ALL_OBJS_UNEXPORTED";
    // Original object relative source line 1322.
    case 0x000006DF:
    case 0x800706DF: return "RPC_S_INTERFACE_NOT_FOUND";
    // Original object relative source line 1323.
    case 0x000006E0:
    case 0x800706E0: return "RPC_S_ENTRY_ALREADY_EXISTS";
    // Original object relative source line 1324.
    case 0x000006E1:
    case 0x800706E1: return "RPC_S_ENTRY_NOT_FOUND";
    // Original object relative source line 1325.
    case 0x000006E2:
    case 0x800706E2: return "RPC_S_NAME_SERVICE_UNAVAILABLE";
    // Original object relative source line 1326.
    case 0x000006E3:
    case 0x800706E3: return "RPC_S_INVALID_NAF_ID";
    // Original object relative source line 1327.
    case 0x000006E4:
    case 0x800706E4: return "RPC_S_CANNOT_SUPPORT";
    // Original object relative source line 1328.
    case 0x000006E5:
    case 0x800706E5: return "RPC_S_NO_CONTEXT_AVAILABLE";
    // Original object relative source line 1329.
    case 0x000006E6:
    case 0x800706E6: return "RPC_S_INTERNAL_ERROR";
    // Original object relative source line 1330.
    case 0x000006E7:
    case 0x800706E7: return "RPC_S_ZERO_DIVIDE";
    // Original object relative source line 1331.
    case 0x000006E8:
    case 0x800706E8: return "RPC_S_ADDRESS_ERROR";
    // Original object relative source line 1332.
    case 0x000006E9:
    case 0x800706E9: return "RPC_S_FP_DIV_ZERO";
    // Original object relative source line 1333.
    case 0x000006EA:
    case 0x800706EA: return "RPC_S_FP_UNDERFLOW";
    // Original object relative source line 1334.
    case 0x000006EB:
    case 0x800706EB: return "RPC_S_FP_OVERFLOW";
    // Original object relative source line 1335.
    case 0x000006EC:
    case 0x800706EC: return "RPC_X_NO_MORE_ENTRIES";
    // Original object relative source line 1336.
    case 0x000006ED:
    case 0x800706ED: return "RPC_X_SS_CHAR_TRANS_OPEN_FAIL";
    // Original object relative source line 1337.
    case 0x000006EE:
    case 0x800706EE: return "RPC_X_SS_CHAR_TRANS_SHORT_FILE";
    // Original object relative source line 1338.
    case 0x000006EF:
    case 0x800706EF: return "RPC_X_SS_IN_NULL_CONTEXT";
    // Original object relative source line 1339.
    case 0x000006F1:
    case 0x800706F1: return "RPC_X_SS_CONTEXT_DAMAGED";
    // Original object relative source line 1340.
    case 0x000006F2:
    case 0x800706F2: return "RPC_X_SS_HANDLES_MISMATCH";
    // Original object relative source line 1341.
    case 0x000006F3:
    case 0x800706F3: return "RPC_X_SS_CANNOT_GET_CALL_HANDLE";
    // Original object relative source line 1342.
    case 0x000006F4:
    case 0x800706F4: return "RPC_X_NULL_REF_POINTER";
    // Original object relative source line 1343.
    case 0x000006F5:
    case 0x800706F5: return "RPC_X_ENUM_VALUE_OUT_OF_RANGE";
    // Original object relative source line 1344.
    case 0x000006F6:
    case 0x800706F6: return "RPC_X_BYTE_COUNT_TOO_SMALL";
    // Original object relative source line 1345.
    case 0x000006F7:
    case 0x800706F7: return "RPC_X_BAD_STUB_DATA";
    // Original object relative source line 1346.
    case 0x000006F8:
    case 0x800706F8: return "ERROR_INVALID_USER_BUFFER";
    // Original object relative source line 1347.
    case 0x000006F9:
    case 0x800706F9: return "ERROR_UNRECOGNIZED_MEDIA";
    // Original object relative source line 1348.
    case 0x000006FA:
    case 0x800706FA: return "ERROR_NO_TRUST_LSA_SECRET";
    // Original object relative source line 1349.
    case 0x000006FB:
    case 0x800706FB: return "ERROR_NO_TRUST_SAM_ACCOUNT";
    // Original object relative source line 1350.
    case 0x000006FC:
    case 0x800706FC: return "ERROR_TRUSTED_DOMAIN_FAILURE";
    // Original object relative source line 1351.
    case 0x000006FD:
    case 0x800706FD: return "ERROR_TRUSTED_RELATIONSHIP_FAILURE";
    // Original object relative source line 1352.
    case 0x000006FE:
    case 0x800706FE: return "ERROR_TRUST_FAILURE";
    // Original object relative source line 1353.
    case 0x000006FF:
    case 0x800706FF: return "RPC_S_CALL_IN_PROGRESS";
    // Original object relative source line 1354.
    case 0x00000700:
    case 0x80070700: return "ERROR_NETLOGON_NOT_STARTED";
    // Original object relative source line 1355.
    case 0x00000701:
    case 0x80070701: return "ERROR_ACCOUNT_EXPIRED";
    // Original object relative source line 1356.
    case 0x00000702:
    case 0x80070702: return "ERROR_REDIRECTOR_HAS_OPEN_HANDLES";
    // Original object relative source line 1357.
    case 0x00000703:
    case 0x80070703: return "ERROR_PRINTER_DRIVER_ALREADY_INSTALLED";
    // Original object relative source line 1358.
    case 0x00000704:
    case 0x80070704: return "ERROR_UNKNOWN_PORT";
    // Original object relative source line 1359.
    case 0x00000705:
    case 0x80070705: return "ERROR_UNKNOWN_PRINTER_DRIVER";
    // Original object relative source line 1360.
    case 0x00000706:
    case 0x80070706: return "ERROR_UNKNOWN_PRINTPROCESSOR";
    // Original object relative source line 1361.
    case 0x00000707:
    case 0x80070707: return "ERROR_INVALID_SEPARATOR_FILE";
    // Original object relative source line 1362.
    case 0x00000708:
    case 0x80070708: return "ERROR_INVALID_PRIORITY";
    // Original object relative source line 1363.
    case 0x00000709:
    case 0x80070709: return "ERROR_INVALID_PRINTER_NAME";
    // Original object relative source line 1364.
    case 0x0000070A:
    case 0x8007070A: return "ERROR_PRINTER_ALREADY_EXISTS";
    // Original object relative source line 1365.
    case 0x0000070B:
    case 0x8007070B: return "ERROR_INVALID_PRINTER_COMMAND";
    // Original object relative source line 1366.
    case 0x0000070C:
    case 0x8007070C: return "ERROR_INVALID_DATATYPE";
    // Original object relative source line 1367.
    case 0x0000070D:
    case 0x8007070D: return "ERROR_INVALID_ENVIRONMENT";
    // Original object relative source line 1368.
    case 0x0000070E:
    case 0x8007070E: return "RPC_S_NO_MORE_BINDINGS";
    // Original object relative source line 1369.
    case 0x0000070F:
    case 0x8007070F: return "ERROR_NOLOGON_INTERDOMAIN_TRUST_ACCOUNT";
    // Original object relative source line 1370.
    case 0x00000710:
    case 0x80070710: return "ERROR_NOLOGON_WORKSTATION_TRUST_ACCOUNT";
    // Original object relative source line 1371.
    case 0x00000711:
    case 0x80070711: return "ERROR_NOLOGON_SERVER_TRUST_ACCOUNT";
    // Original object relative source line 1372.
    case 0x00000712:
    case 0x80070712: return "ERROR_DOMAIN_TRUST_INCONSISTENT";
    // Original object relative source line 1373.
    case 0x00000713:
    case 0x80070713: return "ERROR_SERVER_HAS_OPEN_HANDLES";
    // Original object relative source line 1374.
    case 0x00000714:
    case 0x80070714: return "ERROR_RESOURCE_DATA_NOT_FOUND";
    // Original object relative source line 1375.
    case 0x00000715:
    case 0x80070715: return "ERROR_RESOURCE_TYPE_NOT_FOUND";
    // Original object relative source line 1376.
    case 0x00000716:
    case 0x80070716: return "ERROR_RESOURCE_NAME_NOT_FOUND";
    // Original object relative source line 1377.
    case 0x00000717:
    case 0x80070717: return "ERROR_RESOURCE_LANG_NOT_FOUND";
    // Original object relative source line 1378.
    case 0x00000718:
    case 0x80070718: return "ERROR_NOT_ENOUGH_QUOTA";
    // Original object relative source line 1379.
    case 0x00000719:
    case 0x80070719: return "RPC_S_NO_INTERFACES";
    // Original object relative source line 1380.
    case 0x0000071A:
    case 0x8007071A: return "RPC_S_CALL_CANCELLED";
    // Original object relative source line 1381.
    case 0x0000071B:
    case 0x8007071B: return "RPC_S_BINDING_INCOMPLETE";
    // Original object relative source line 1382.
    case 0x0000071C:
    case 0x8007071C: return "RPC_S_COMM_FAILURE";
    // Original object relative source line 1383.
    case 0x0000071D:
    case 0x8007071D: return "RPC_S_UNSUPPORTED_AUTHN_LEVEL";
    // Original object relative source line 1384.
    case 0x0000071E:
    case 0x8007071E: return "RPC_S_NO_PRINC_NAME";
    // Original object relative source line 1385.
    case 0x0000071F:
    case 0x8007071F: return "RPC_S_NOT_RPC_ERROR";
    // Original object relative source line 1386.
    case 0x00000720:
    case 0x80070720: return "RPC_S_UUID_LOCAL_ONLY";
    // Original object relative source line 1387.
    case 0x00000721:
    case 0x80070721: return "RPC_S_SEC_PKG_ERROR";
    // Original object relative source line 1388.
    case 0x00000722:
    case 0x80070722: return "RPC_S_NOT_CANCELLED";
    // Original object relative source line 1389.
    case 0x00000723:
    case 0x80070723: return "RPC_X_INVALID_ES_ACTION";
    // Original object relative source line 1390.
    case 0x00000724:
    case 0x80070724: return "RPC_X_WRONG_ES_VERSION";
    // Original object relative source line 1391.
    case 0x00000725:
    case 0x80070725: return "RPC_X_WRONG_STUB_VERSION";
    // Original object relative source line 1392.
    case 0x00000726:
    case 0x80070726: return "RPC_X_INVALID_PIPE_OBJECT";
    // Original object relative source line 1393.
    case 0x00000727:
    case 0x80070727: return "RPC_X_WRONG_PIPE_ORDER";
    // Original object relative source line 1394.
    case 0x00000728:
    case 0x80070728: return "RPC_X_WRONG_PIPE_VERSION";
    // Original object relative source line 1395.
    case 0x0000076A:
    case 0x8007076A: return "RPC_S_GROUP_MEMBER_NOT_FOUND";
    // Original object relative source line 1396.
    case 0x0000076B:
    case 0x8007076B: return "EPT_S_CANT_CREATE";
    // Original object relative source line 1397.
    case 0x0000076C:
    case 0x8007076C: return "RPC_S_INVALID_OBJECT";
    // Original object relative source line 1398.
    case 0x0000076D:
    case 0x8007076D: return "ERROR_INVALID_TIME";
    // Original object relative source line 1399.
    case 0x0000076E:
    case 0x8007076E: return "ERROR_INVALID_FORM_NAME";
    // Original object relative source line 1400.
    case 0x0000076F:
    case 0x8007076F: return "ERROR_INVALID_FORM_SIZE";
    // Original object relative source line 1401.
    case 0x00000770:
    case 0x80070770: return "ERROR_ALREADY_WAITING";
    // Original object relative source line 1402.
    case 0x00000771:
    case 0x80070771: return "ERROR_PRINTER_DELETED";
    // Original object relative source line 1403.
    case 0x00000772:
    case 0x80070772: return "ERROR_INVALID_PRINTER_STATE";
    // Original object relative source line 1404.
    case 0x00000773:
    case 0x80070773: return "ERROR_PASSWORD_MUST_CHANGE";
    // Original object relative source line 1405.
    case 0x00000774:
    case 0x80070774: return "ERROR_DOMAIN_CONTROLLER_NOT_FOUND";
    // Original object relative source line 1406.
    case 0x00000775:
    case 0x80070775: return "ERROR_ACCOUNT_LOCKED_OUT";
    // Original object relative source line 1407.
    case 0x00000776:
    case 0x80070776: return "OR_INVALID_OXID";
    // Original object relative source line 1408.
    case 0x00000777:
    case 0x80070777: return "OR_INVALID_OID";
    // Original object relative source line 1409.
    case 0x00000778:
    case 0x80070778: return "OR_INVALID_SET";
    // Original object relative source line 1410.
    case 0x00000779:
    case 0x80070779: return "RPC_S_SEND_INCOMPLETE";
    // Original object relative source line 1411.
    case 0x0000077A:
    case 0x8007077A: return "RPC_S_INVALID_ASYNC_HANDLE";
    // Original object relative source line 1412.
    case 0x0000077B:
    case 0x8007077B: return "RPC_S_INVALID_ASYNC_CALL";
    // Original object relative source line 1413.
    case 0x0000077C:
    case 0x8007077C: return "RPC_X_PIPE_CLOSED";
    // Original object relative source line 1414.
    case 0x0000077D:
    case 0x8007077D: return "RPC_X_PIPE_DISCIPLINE_ERROR";
    // Original object relative source line 1415.
    case 0x0000077E:
    case 0x8007077E: return "RPC_X_PIPE_EMPTY";
    // Original object relative source line 1416.
    case 0x0000077F:
    case 0x8007077F: return "ERROR_NO_SITENAME";
    // Original object relative source line 1417.
    case 0x00000780:
    case 0x80070780: return "ERROR_CANT_ACCESS_FILE";
    // Original object relative source line 1418.
    case 0x00000781:
    case 0x80070781: return "ERROR_CANT_RESOLVE_FILENAME";
    // Original object relative source line 1419.
    case 0x000007D0:
    case 0x800707D0: return "ERROR_INVALID_PIXEL_FORMAT";
    // Original object relative source line 1420.
    case 0x000007D1:
    case 0x800707D1: return "ERROR_BAD_DRIVER";
    // Original object relative source line 1421.
    case 0x000007D2:
    case 0x800707D2: return "ERROR_INVALID_WINDOW_STYLE";
    // Original object relative source line 1422.
    case 0x000007D3:
    case 0x800707D3: return "ERROR_METAFILE_NOT_SUPPORTED";
    // Original object relative source line 1423.
    case 0x000007D4:
    case 0x800707D4: return "ERROR_TRANSFORM_NOT_SUPPORTED";
    // Original object relative source line 1424.
    case 0x000007D5:
    case 0x800707D5: return "ERROR_CLIPPING_NOT_SUPPORTED";
    // Original object relative source line 1425.
    case 0x000007DA:
    case 0x800707DA: return "ERROR_INVALID_CMM";
    // Original object relative source line 1426.
    case 0x000007DB:
    case 0x800707DB: return "ERROR_INVALID_PROFILE";
    // Original object relative source line 1427.
    case 0x000007DC:
    case 0x800707DC: return "ERROR_TAG_NOT_FOUND";
    // Original object relative source line 1428.
    case 0x000007DD:
    case 0x800707DD: return "ERROR_TAG_NOT_PRESENT";
    // Original object relative source line 1429.
    case 0x000007DE:
    case 0x800707DE: return "ERROR_DUPLICATE_TAG";
    // Original object relative source line 1430.
    case 0x000007DF:
    case 0x800707DF: return "ERROR_PROFILE_NOT_ASSOCIATED_WITH_DEVICE";
    // Original object relative source line 1431.
    case 0x000007E0:
    case 0x800707E0: return "ERROR_PROFILE_NOT_FOUND";
    // Original object relative source line 1432.
    case 0x000007E1:
    case 0x800707E1: return "ERROR_INVALID_COLORSPACE";
    // Original object relative source line 1433.
    case 0x000007E2:
    case 0x800707E2: return "ERROR_ICM_NOT_ENABLED";
    // Original object relative source line 1434.
    case 0x000007E3:
    case 0x800707E3: return "ERROR_DELETING_ICM_XFORM";
    // Original object relative source line 1435.
    case 0x000007E4:
    case 0x800707E4: return "ERROR_INVALID_TRANSFORM";
    // Original object relative source line 1436.
    case 0x000007E5:
    case 0x800707E5: return "ERROR_COLORSPACE_MISMATCH";
    // Original object relative source line 1437.
    case 0x000007E6:
    case 0x800707E6: return "ERROR_INVALID_COLORINDEX";
    // Original object relative source line 1438.
    case 0x0000083C:
    case 0x8007083C: return "ERROR_CONNECTED_OTHER_PASSWORD";
    // Original object relative source line 1439.
    case 0x0000089A:
    case 0x8007089A: return "ERROR_BAD_USERNAME";
    // Original object relative source line 1440.
    case 0x000008CA:
    case 0x800708CA: return "ERROR_NOT_CONNECTED";
    // Original object relative source line 1441.
    case 0x00000961:
    case 0x80070961: return "ERROR_OPEN_FILES";
    // Original object relative source line 1442.
    case 0x00000962:
    case 0x80070962: return "ERROR_ACTIVE_CONNECTIONS";
    // Original object relative source line 1443.
    case 0x00000964:
    case 0x80070964: return "ERROR_DEVICE_IN_USE";
    // Original object relative source line 1444.
    case 0x00000BB8:
    case 0x80070BB8: return "ERROR_UNKNOWN_PRINT_MONITOR";
    // Original object relative source line 1445.
    case 0x00000BB9:
    case 0x80070BB9: return "ERROR_PRINTER_DRIVER_IN_USE";
    // Original object relative source line 1446.
    case 0x00000BBA:
    case 0x80070BBA: return "ERROR_SPOOL_FILE_NOT_FOUND";
    // Original object relative source line 1447.
    case 0x00000BBB:
    case 0x80070BBB: return "ERROR_SPL_NO_STARTDOC";
    // Original object relative source line 1448.
    case 0x00000BBC:
    case 0x80070BBC: return "ERROR_SPL_NO_ADDJOB";
    // Original object relative source line 1449.
    case 0x00000BBD:
    case 0x80070BBD: return "ERROR_PRINT_PROCESSOR_ALREADY_INSTALLED";
    // Original object relative source line 1450.
    case 0x00000BBE:
    case 0x80070BBE: return "ERROR_PRINT_MONITOR_ALREADY_INSTALLED";
    // Original object relative source line 1451.
    case 0x00000BBF:
    case 0x80070BBF: return "ERROR_INVALID_PRINT_MONITOR";
    // Original object relative source line 1452.
    case 0x00000BC0:
    case 0x80070BC0: return "ERROR_PRINT_MONITOR_IN_USE";
    // Original object relative source line 1453.
    case 0x00000BC1:
    case 0x80070BC1: return "ERROR_PRINTER_HAS_JOBS_QUEUED";
    // Original object relative source line 1454.
    case 0x00000BC2:
    case 0x80070BC2: return "ERROR_SUCCESS_REBOOT_REQUIRED";
    // Original object relative source line 1455.
    case 0x00000BC3:
    case 0x80070BC3: return "ERROR_SUCCESS_RESTART_REQUIRED";
    // Original object relative source line 1456.
    case 0x00000BC4:
    case 0x80070BC4: return "ERROR_PRINTER_NOT_FOUND";
    // Original object relative source line 1457.
    case 0x00000FA0:
    case 0x80070FA0: return "ERROR_WINS_INTERNAL";
    // Original object relative source line 1458.
    case 0x00000FA1:
    case 0x80070FA1: return "ERROR_CAN_NOT_DEL_LOCAL_WINS";
    // Original object relative source line 1459.
    case 0x00000FA2:
    case 0x80070FA2: return "ERROR_STATIC_INIT";
    // Original object relative source line 1460.
    case 0x00000FA3:
    case 0x80070FA3: return "ERROR_INC_BACKUP";
    // Original object relative source line 1461.
    case 0x00000FA4:
    case 0x80070FA4: return "ERROR_FULL_BACKUP";
    // Original object relative source line 1462.
    case 0x00000FA5:
    case 0x80070FA5: return "ERROR_REC_NON_EXISTENT";
    // Original object relative source line 1463.
    case 0x00000FA6:
    case 0x80070FA6: return "ERROR_RPL_NOT_ALLOWED";
    // Original object relative source line 1464.
    case 0x00001004:
    case 0x80071004: return "ERROR_DHCP_ADDRESS_CONFLICT";
    // Original object relative source line 1465.
    case 0x00001068:
    case 0x80071068: return "ERROR_WMI_GUID_NOT_FOUND";
    // Original object relative source line 1466.
    case 0x00001069:
    case 0x80071069: return "ERROR_WMI_INSTANCE_NOT_FOUND";
    // Original object relative source line 1467.
    case 0x0000106A:
    case 0x8007106A: return "ERROR_WMI_ITEMID_NOT_FOUND";
    // Original object relative source line 1468.
    case 0x0000106B:
    case 0x8007106B: return "ERROR_WMI_TRY_AGAIN";
    // Original object relative source line 1469.
    case 0x0000106C:
    case 0x8007106C: return "ERROR_WMI_DP_NOT_FOUND";
    // Original object relative source line 1470.
    case 0x0000106D:
    case 0x8007106D: return "ERROR_WMI_UNRESOLVED_INSTANCE_REF";
    // Original object relative source line 1471.
    case 0x0000106E:
    case 0x8007106E: return "ERROR_WMI_ALREADY_ENABLED";
    // Original object relative source line 1472.
    case 0x0000106F:
    case 0x8007106F: return "ERROR_WMI_GUID_DISCONNECTED";
    // Original object relative source line 1473.
    case 0x00001070:
    case 0x80071070: return "ERROR_WMI_SERVER_UNAVAILABLE";
    // Original object relative source line 1474.
    case 0x00001071:
    case 0x80071071: return "ERROR_WMI_DP_FAILED";
    // Original object relative source line 1475.
    case 0x00001072:
    case 0x80071072: return "ERROR_WMI_INVALID_MOF";
    // Original object relative source line 1476.
    case 0x00001073:
    case 0x80071073: return "ERROR_WMI_INVALID_REGINFO";
    // Original object relative source line 1477.
    case 0x00001074:
    case 0x80071074: return "ERROR_WMI_ALREADY_DISABLED";
    // Original object relative source line 1478.
    case 0x00001075:
    case 0x80071075: return "ERROR_WMI_READ_ONLY";
    // Original object relative source line 1479.
    case 0x00001076:
    case 0x80071076: return "ERROR_WMI_SET_FAILURE";
    // Original object relative source line 1480.
    case 0x000010CC:
    case 0x800710CC: return "ERROR_INVALID_MEDIA";
    // Original object relative source line 1481.
    case 0x000010CD:
    case 0x800710CD: return "ERROR_INVALID_LIBRARY";
    // Original object relative source line 1482.
    case 0x000010CE:
    case 0x800710CE: return "ERROR_INVALID_MEDIA_POOL";
    // Original object relative source line 1483.
    case 0x000010CF:
    case 0x800710CF: return "ERROR_DRIVE_MEDIA_MISMATCH";
    // Original object relative source line 1484.
    case 0x000010D0:
    case 0x800710D0: return "ERROR_MEDIA_OFFLINE";
    // Original object relative source line 1485.
    case 0x000010D1:
    case 0x800710D1: return "ERROR_LIBRARY_OFFLINE";
    // Original object relative source line 1486.
    case 0x000010D2:
    case 0x800710D2: return "ERROR_EMPTY";
    // Original object relative source line 1487.
    case 0x000010D3:
    case 0x800710D3: return "ERROR_NOT_EMPTY";
    // Original object relative source line 1488.
    case 0x000010D4:
    case 0x800710D4: return "ERROR_MEDIA_UNAVAILABLE";
    // Original object relative source line 1489.
    case 0x000010D5:
    case 0x800710D5: return "ERROR_RESOURCE_DISABLED";
    // Original object relative source line 1490.
    case 0x000010D6:
    case 0x800710D6: return "ERROR_INVALID_CLEANER";
    // Original object relative source line 1491.
    case 0x000010D7:
    case 0x800710D7: return "ERROR_UNABLE_TO_CLEAN";
    // Original object relative source line 1492.
    case 0x000010D8:
    case 0x800710D8: return "ERROR_OBJECT_NOT_FOUND";
    // Original object relative source line 1493.
    case 0x000010D9:
    case 0x800710D9: return "ERROR_DATABASE_FAILURE";
    // Original object relative source line 1494.
    case 0x000010DA:
    case 0x800710DA: return "ERROR_DATABASE_FULL";
    // Original object relative source line 1495.
    case 0x000010DB:
    case 0x800710DB: return "ERROR_MEDIA_INCOMPATIBLE";
    // Original object relative source line 1496.
    case 0x000010DC:
    case 0x800710DC: return "ERROR_RESOURCE_NOT_PRESENT";
    // Original object relative source line 1497.
    case 0x000010DD:
    case 0x800710DD: return "ERROR_INVALID_OPERATION";
    // Original object relative source line 1498.
    case 0x000010DE:
    case 0x800710DE: return "ERROR_MEDIA_NOT_AVAILABLE";
    // Original object relative source line 1499.
    case 0x000010DF:
    case 0x800710DF: return "ERROR_DEVICE_NOT_AVAILABLE";
    // Original object relative source line 1500.
    case 0x000010E0:
    case 0x800710E0: return "ERROR_REQUEST_REFUSED";
    // Original object relative source line 1501.
    case 0x000010E1:
    case 0x800710E1: return "ERROR_INVALID_DRIVE_OBJECT";
    // Original object relative source line 1502.
    case 0x000010E2:
    case 0x800710E2: return "ERROR_LIBRARY_FULL";
    // Original object relative source line 1503.
    case 0x000010E3:
    case 0x800710E3: return "ERROR_MEDIUM_NOT_ACCESSIBLE";
    // Original object relative source line 1504.
    case 0x000010E4:
    case 0x800710E4: return "ERROR_UNABLE_TO_LOAD_MEDIUM";
    // Original object relative source line 1505.
    case 0x000010E5:
    case 0x800710E5: return "ERROR_UNABLE_TO_INVENTORY_DRIVE";
    // Original object relative source line 1506.
    case 0x000010E6:
    case 0x800710E6: return "ERROR_UNABLE_TO_INVENTORY_SLOT";
    // Original object relative source line 1507.
    case 0x000010E7:
    case 0x800710E7: return "ERROR_UNABLE_TO_INVENTORY_TRANSPORT";
    // Original object relative source line 1508.
    case 0x000010E8:
    case 0x800710E8: return "ERROR_TRANSPORT_FULL";
    // Original object relative source line 1509.
    case 0x000010E9:
    case 0x800710E9: return "ERROR_CONTROLLING_IEPORT";
    // Original object relative source line 1510.
    case 0x000010EA:
    case 0x800710EA: return "ERROR_UNABLE_TO_EJECT_MOUNTED_MEDIA";
    // Original object relative source line 1511.
    case 0x000010EB:
    case 0x800710EB: return "ERROR_CLEANER_SLOT_SET";
    // Original object relative source line 1512.
    case 0x000010EC:
    case 0x800710EC: return "ERROR_CLEANER_SLOT_NOT_SET";
    // Original object relative source line 1513.
    case 0x000010ED:
    case 0x800710ED: return "ERROR_CLEANER_CARTRIDGE_SPENT";
    // Original object relative source line 1514.
    case 0x000010EE:
    case 0x800710EE: return "ERROR_UNEXPECTED_OMID";
    // Original object relative source line 1515.
    case 0x000010EF:
    case 0x800710EF: return "ERROR_CANT_DELETE_LAST_ITEM";
    // Original object relative source line 1516.
    case 0x000010F0:
    case 0x800710F0: return "ERROR_MESSAGE_EXCEEDS_MAX_SIZE";
    // Original object relative source line 1517.
    case 0x000010FE:
    case 0x800710FE: return "ERROR_FILE_OFFLINE";
    // Original object relative source line 1518.
    case 0x000010FF:
    case 0x800710FF: return "ERROR_REMOTE_STORAGE_NOT_ACTIVE";
    // Original object relative source line 1519.
    case 0x00001100:
    case 0x80071100: return "ERROR_REMOTE_STORAGE_MEDIA_ERROR";
    // Original object relative source line 1520.
    case 0x00001126:
    case 0x80071126: return "ERROR_NOT_A_REPARSE_POINT";
    // Original object relative source line 1521.
    case 0x00001127:
    case 0x80071127: return "ERROR_REPARSE_ATTRIBUTE_CONFLICT";
    // Original object relative source line 1522.
    case 0x00001128:
    case 0x80071128: return "ERROR_INVALID_REPARSE_DATA";
    // Original object relative source line 1523.
    case 0x00001389:
    case 0x80071389: return "ERROR_DEPENDENT_RESOURCE_EXISTS";
    // Original object relative source line 1524.
    case 0x0000138A:
    case 0x8007138A: return "ERROR_DEPENDENCY_NOT_FOUND";
    // Original object relative source line 1525.
    case 0x0000138B:
    case 0x8007138B: return "ERROR_DEPENDENCY_ALREADY_EXISTS";
    // Original object relative source line 1526.
    case 0x0000138C:
    case 0x8007138C: return "ERROR_RESOURCE_NOT_ONLINE";
    // Original object relative source line 1527.
    case 0x0000138D:
    case 0x8007138D: return "ERROR_HOST_NODE_NOT_AVAILABLE";
    // Original object relative source line 1528.
    case 0x0000138E:
    case 0x8007138E: return "ERROR_RESOURCE_NOT_AVAILABLE";
    // Original object relative source line 1529.
    case 0x0000138F:
    case 0x8007138F: return "ERROR_RESOURCE_NOT_FOUND";
    // Original object relative source line 1530.
    case 0x00001390:
    case 0x80071390: return "ERROR_SHUTDOWN_CLUSTER";
    // Original object relative source line 1531.
    case 0x00001391:
    case 0x80071391: return "ERROR_CANT_EVICT_ACTIVE_NODE";
    // Original object relative source line 1532.
    case 0x00001392:
    case 0x80071392: return "ERROR_OBJECT_ALREADY_EXISTS";
    // Original object relative source line 1533.
    case 0x00001393:
    case 0x80071393: return "ERROR_OBJECT_IN_LIST";
    // Original object relative source line 1534.
    case 0x00001394:
    case 0x80071394: return "ERROR_GROUP_NOT_AVAILABLE";
    // Original object relative source line 1535.
    case 0x00001395:
    case 0x80071395: return "ERROR_GROUP_NOT_FOUND";
    // Original object relative source line 1536.
    case 0x00001396:
    case 0x80071396: return "ERROR_GROUP_NOT_ONLINE";
    // Original object relative source line 1537.
    case 0x00001397:
    case 0x80071397: return "ERROR_HOST_NODE_NOT_RESOURCE_OWNER";
    // Original object relative source line 1538.
    case 0x00001398:
    case 0x80071398: return "ERROR_HOST_NODE_NOT_GROUP_OWNER";
    // Original object relative source line 1539.
    case 0x00001399:
    case 0x80071399: return "ERROR_RESMON_CREATE_FAILED";
    // Original object relative source line 1540.
    case 0x0000139A:
    case 0x8007139A: return "ERROR_RESMON_ONLINE_FAILED";
    // Original object relative source line 1541.
    case 0x0000139B:
    case 0x8007139B: return "ERROR_RESOURCE_ONLINE";
    // Original object relative source line 1542.
    case 0x0000139C:
    case 0x8007139C: return "ERROR_QUORUM_RESOURCE";
    // Original object relative source line 1543.
    case 0x0000139D:
    case 0x8007139D: return "ERROR_NOT_QUORUM_CAPABLE";
    // Original object relative source line 1544.
    case 0x0000139E:
    case 0x8007139E: return "ERROR_CLUSTER_SHUTTING_DOWN";
    // Original object relative source line 1545.
    case 0x0000139F:
    case 0x8007139F: return "ERROR_INVALID_STATE";
    // Original object relative source line 1546.
    case 0x000013A0:
    case 0x800713A0: return "ERROR_RESOURCE_PROPERTIES_STORED";
    // Original object relative source line 1547.
    case 0x000013A1:
    case 0x800713A1: return "ERROR_NOT_QUORUM_CLASS";
    // Original object relative source line 1548.
    case 0x000013A2:
    case 0x800713A2: return "ERROR_CORE_RESOURCE";
    // Original object relative source line 1549.
    case 0x000013A3:
    case 0x800713A3: return "ERROR_QUORUM_RESOURCE_ONLINE_FAILED";
    // Original object relative source line 1550.
    case 0x000013A4:
    case 0x800713A4: return "ERROR_QUORUMLOG_OPEN_FAILED";
    // Original object relative source line 1551.
    case 0x000013A5:
    case 0x800713A5: return "ERROR_CLUSTERLOG_CORRUPT";
    // Original object relative source line 1552.
    case 0x000013A6:
    case 0x800713A6: return "ERROR_CLUSTERLOG_RECORD_EXCEEDS_MAXSIZE";
    // Original object relative source line 1553.
    case 0x000013A7:
    case 0x800713A7: return "ERROR_CLUSTERLOG_EXCEEDS_MAXSIZE";
    // Original object relative source line 1554.
    case 0x000013A8:
    case 0x800713A8: return "ERROR_CLUSTERLOG_CHKPOINT_NOT_FOUND";
    // Original object relative source line 1555.
    case 0x000013A9:
    case 0x800713A9: return "ERROR_CLUSTERLOG_NOT_ENOUGH_SPACE";
    // Original object relative source line 1556.
    case 0x00001770:
    case 0x80071770: return "ERROR_ENCRYPTION_FAILED";
    // Original object relative source line 1557.
    case 0x00001771:
    case 0x80071771: return "ERROR_DECRYPTION_FAILED";
    // Original object relative source line 1558.
    case 0x00001772:
    case 0x80071772: return "ERROR_FILE_ENCRYPTED";
    // Original object relative source line 1559.
    case 0x00001773:
    case 0x80071773: return "ERROR_NO_RECOVERY_POLICY";
    // Original object relative source line 1560.
    case 0x00001774:
    case 0x80071774: return "ERROR_NO_EFS";
    // Original object relative source line 1561.
    case 0x00001775:
    case 0x80071775: return "ERROR_WRONG_EFS";
    // Original object relative source line 1562.
    case 0x00001776:
    case 0x80071776: return "ERROR_NO_USER_KEYS";
    // Original object relative source line 1563.
    case 0x00001777:
    case 0x80071777: return "ERROR_FILE_NOT_ENCRYPTED";
    // Original object relative source line 1564.
    case 0x00001778:
    case 0x80071778: return "ERROR_NOT_EXPORT_FORMAT";
    // Original object relative source line 1565.
    case 0x000017E6:
    case 0x800717E6: return "ERROR_NO_BROWSER_SERVERS_FOUND";
    // Original object relative source line 1566.
    case 0x00001B59:
    case 0x80071B59: return "ERROR_CTX_WINSTATION_NAME_INVALID";
    // Original object relative source line 1567.
    case 0x00001B5A:
    case 0x80071B5A: return "ERROR_CTX_INVALID_PD";
    // Original object relative source line 1568.
    case 0x00001B5B:
    case 0x80071B5B: return "ERROR_CTX_PD_NOT_FOUND";
    // Original object relative source line 1569.
    case 0x00001B5C:
    case 0x80071B5C: return "ERROR_CTX_WD_NOT_FOUND";
    // Original object relative source line 1570.
    case 0x00001B5D:
    case 0x80071B5D: return "ERROR_CTX_CANNOT_MAKE_EVENTLOG_ENTRY";
    // Original object relative source line 1571.
    case 0x00001B5E:
    case 0x80071B5E: return "ERROR_CTX_SERVICE_NAME_COLLISION";
    // Original object relative source line 1572.
    case 0x00001B5F:
    case 0x80071B5F: return "ERROR_CTX_CLOSE_PENDING";
    // Original object relative source line 1573.
    case 0x00001B60:
    case 0x80071B60: return "ERROR_CTX_NO_OUTBUF";
    // Original object relative source line 1574.
    case 0x00001B61:
    case 0x80071B61: return "ERROR_CTX_MODEM_INF_NOT_FOUND";
    // Original object relative source line 1575.
    case 0x00001B62:
    case 0x80071B62: return "ERROR_CTX_INVALID_MODEMNAME";
    // Original object relative source line 1576.
    case 0x00001B63:
    case 0x80071B63: return "ERROR_CTX_MODEM_RESPONSE_ERROR";
    // Original object relative source line 1577.
    case 0x00001B64:
    case 0x80071B64: return "ERROR_CTX_MODEM_RESPONSE_TIMEOUT";
    // Original object relative source line 1578.
    case 0x00001B65:
    case 0x80071B65: return "ERROR_CTX_MODEM_RESPONSE_NO_CARRIER";
    // Original object relative source line 1579.
    case 0x00001B66:
    case 0x80071B66: return "ERROR_CTX_MODEM_RESPONSE_NO_DIALTONE";
    // Original object relative source line 1580.
    case 0x00001B67:
    case 0x80071B67: return "ERROR_CTX_MODEM_RESPONSE_BUSY";
    // Original object relative source line 1581.
    case 0x00001B68:
    case 0x80071B68: return "ERROR_CTX_MODEM_RESPONSE_VOICE";
    // Original object relative source line 1582.
    case 0x00001B69:
    case 0x80071B69: return "ERROR_CTX_TD_ERROR";
    // Original object relative source line 1583.
    case 0x00001B6E:
    case 0x80071B6E: return "ERROR_CTX_WINSTATION_NOT_FOUND";
    // Original object relative source line 1584.
    case 0x00001B6F:
    case 0x80071B6F: return "ERROR_CTX_WINSTATION_ALREADY_EXISTS";
    // Original object relative source line 1585.
    case 0x00001B70:
    case 0x80071B70: return "ERROR_CTX_WINSTATION_BUSY";
    // Original object relative source line 1586.
    case 0x00001B71:
    case 0x80071B71: return "ERROR_CTX_BAD_VIDEO_MODE";
    // Original object relative source line 1587.
    case 0x00001B7B:
    case 0x80071B7B: return "ERROR_CTX_GRAPHICS_INVALID";
    // Original object relative source line 1588.
    case 0x00001B7D:
    case 0x80071B7D: return "ERROR_CTX_LOGON_DISABLED";
    // Original object relative source line 1589.
    case 0x00001B7E:
    case 0x80071B7E: return "ERROR_CTX_NOT_CONSOLE";
    // Original object relative source line 1590.
    case 0x00001B80:
    case 0x80071B80: return "ERROR_CTX_CLIENT_QUERY_TIMEOUT";
    // Original object relative source line 1591.
    case 0x00001B81:
    case 0x80071B81: return "ERROR_CTX_CONSOLE_DISCONNECT";
    // Original object relative source line 1592.
    case 0x00001B82:
    case 0x80071B82: return "ERROR_CTX_CONSOLE_CONNECT";
    // Original object relative source line 1593.
    case 0x00001B84:
    case 0x80071B84: return "ERROR_CTX_SHADOW_DENIED";
    // Original object relative source line 1594.
    case 0x00001B85:
    case 0x80071B85: return "ERROR_CTX_WINSTATION_ACCESS_DENIED";
    // Original object relative source line 1595.
    case 0x00001B89:
    case 0x80071B89: return "ERROR_CTX_INVALID_WD";
    // Original object relative source line 1596.
    case 0x00001B8A:
    case 0x80071B8A: return "ERROR_CTX_SHADOW_INVALID";
    // Original object relative source line 1597.
    case 0x00001B8B:
    case 0x80071B8B: return "ERROR_CTX_SHADOW_DISABLED";
    // Original object relative source line 1598.
    case 0x00001F41:
    case 0x80071F41: return "FRS_ERR_INVALID_API_SEQUENCE";
    // Original object relative source line 1599.
    case 0x00001F42:
    case 0x80071F42: return "FRS_ERR_STARTING_SERVICE";
    // Original object relative source line 1600.
    case 0x00001F43:
    case 0x80071F43: return "FRS_ERR_STOPPING_SERVICE";
    // Original object relative source line 1601.
    case 0x00001F44:
    case 0x80071F44: return "FRS_ERR_INTERNAL_API";
    // Original object relative source line 1602.
    case 0x00001F45:
    case 0x80071F45: return "FRS_ERR_INTERNAL";
    // Original object relative source line 1603.
    case 0x00001F46:
    case 0x80071F46: return "FRS_ERR_SERVICE_COMM";
    // Original object relative source line 1604.
    case 0x00001F47:
    case 0x80071F47: return "FRS_ERR_INSUFFICIENT_PRIV";
    // Original object relative source line 1605.
    case 0x00001F48:
    case 0x80071F48: return "FRS_ERR_AUTHENTICATION";
    // Original object relative source line 1606.
    case 0x00001F49:
    case 0x80071F49: return "FRS_ERR_PARENT_INSUFFICIENT_PRIV";
    // Original object relative source line 1607.
    case 0x00001F4A:
    case 0x80071F4A: return "FRS_ERR_PARENT_AUTHENTICATION";
    // Original object relative source line 1608.
    case 0x00001F4B:
    case 0x80071F4B: return "FRS_ERR_CHILD_TO_PARENT_COMM";
    // Original object relative source line 1609.
    case 0x00001F4C:
    case 0x80071F4C: return "FRS_ERR_PARENT_TO_CHILD_COMM";
    // Original object relative source line 1610.
    case 0x00001F4D:
    case 0x80071F4D: return "FRS_ERR_SYSVOL_POPULATE";
    // Original object relative source line 1611.
    case 0x00001F4E:
    case 0x80071F4E: return "FRS_ERR_SYSVOL_POPULATE_TIMEOUT";
    // Original object relative source line 1612.
    case 0x00001F4F:
    case 0x80071F4F: return "FRS_ERR_SYSVOL_IS_BUSY";
    // Original object relative source line 1613.
    case 0x00001F50:
    case 0x80071F50: return "FRS_ERR_SYSVOL_DEMOTE";
    // Original object relative source line 1614.
    case 0x00001F51:
    case 0x80071F51: return "FRS_ERR_INVALID_SERVICE_PARAMETER";
    // Original object relative source line 1616.
    case 0x00002008:
    case 0x80072008: return "ERROR_DS_NOT_INSTALLED";
    // Original object relative source line 1617.
    case 0x00002009:
    case 0x80072009: return "ERROR_DS_MEMBERSHIP_EVALUATED_LOCALLY";
    // Original object relative source line 1618.
    case 0x0000200A:
    case 0x8007200A: return "ERROR_DS_NO_ATTRIBUTE_OR_VALUE";
    // Original object relative source line 1619.
    case 0x0000200B:
    case 0x8007200B: return "ERROR_DS_INVALID_ATTRIBUTE_SYNTAX";
    // Original object relative source line 1620.
    case 0x0000200C:
    case 0x8007200C: return "ERROR_DS_ATTRIBUTE_TYPE_UNDEFINED";
    // Original object relative source line 1621.
    case 0x0000200D:
    case 0x8007200D: return "ERROR_DS_ATTRIBUTE_OR_VALUE_EXISTS";
    // Original object relative source line 1622.
    case 0x0000200E:
    case 0x8007200E: return "ERROR_DS_BUSY";
    // Original object relative source line 1623.
    case 0x0000200F:
    case 0x8007200F: return "ERROR_DS_UNAVAILABLE";
    // Original object relative source line 1624.
    case 0x00002010:
    case 0x80072010: return "ERROR_DS_NO_RIDS_ALLOCATED";
    // Original object relative source line 1625.
    case 0x00002011:
    case 0x80072011: return "ERROR_DS_NO_MORE_RIDS";
    // Original object relative source line 1626.
    case 0x00002012:
    case 0x80072012: return "ERROR_DS_INCORRECT_ROLE_OWNER";
    // Original object relative source line 1627.
    case 0x00002013:
    case 0x80072013: return "ERROR_DS_RIDMGR_INIT_ERROR";
    // Original object relative source line 1628.
    case 0x00002014:
    case 0x80072014: return "ERROR_DS_OBJ_CLASS_VIOLATION";
    // Original object relative source line 1629.
    case 0x00002015:
    case 0x80072015: return "ERROR_DS_CANT_ON_NON_LEAF";
    // Original object relative source line 1630.
    case 0x00002016:
    case 0x80072016: return "ERROR_DS_CANT_ON_RDN";
    // Original object relative source line 1631.
    case 0x00002017:
    case 0x80072017: return "ERROR_DS_CANT_MOD_OBJ_CLASS";
    // Original object relative source line 1632.
    case 0x00002018:
    case 0x80072018: return "ERROR_DS_CROSS_DOM_MOVE_ERROR";
    // Original object relative source line 1633.
    case 0x00002019:
    case 0x80072019: return "ERROR_DS_GC_NOT_AVAILABLE";
    // Original object relative source line 1634.
    case 0x0000201A:
    case 0x8007201A: return "ERROR_SHARED_POLICY";
    // Original object relative source line 1635.
    case 0x0000201B:
    case 0x8007201B: return "ERROR_POLICY_OBJECT_NOT_FOUND";
    // Original object relative source line 1636.
    case 0x0000201C:
    case 0x8007201C: return "ERROR_POLICY_ONLY_IN_DS";
    // Original object relative source line 1637.
    case 0x0000201D:
    case 0x8007201D: return "ERROR_PROMOTION_ACTIVE";
    // Original object relative source line 1638.
    case 0x0000201E:
    case 0x8007201E: return "ERROR_NO_PROMOTION_ACTIVE";
    // Original object relative source line 1639.
    case 0x00002020:
    case 0x80072020: return "ERROR_DS_OPERATIONS_ERROR";
    // Original object relative source line 1640.
    case 0x00002021:
    case 0x80072021: return "ERROR_DS_PROTOCOL_ERROR";
    // Original object relative source line 1641.
    case 0x00002022:
    case 0x80072022: return "ERROR_DS_TIMELIMIT_EXCEEDED";
    // Original object relative source line 1642.
    case 0x00002023:
    case 0x80072023: return "ERROR_DS_SIZELIMIT_EXCEEDED";
    // Original object relative source line 1643.
    case 0x00002024:
    case 0x80072024: return "ERROR_DS_ADMIN_LIMIT_EXCEEDED";
    // Original object relative source line 1644.
    case 0x00002025:
    case 0x80072025: return "ERROR_DS_COMPARE_FALSE";
    // Original object relative source line 1645.
    case 0x00002026:
    case 0x80072026: return "ERROR_DS_COMPARE_TRUE";
    // Original object relative source line 1646.
    case 0x00002027:
    case 0x80072027: return "ERROR_DS_AUTH_METHOD_NOT_SUPPORTED";
    // Original object relative source line 1647.
    case 0x00002028:
    case 0x80072028: return "ERROR_DS_STRONG_AUTH_REQUIRED";
    // Original object relative source line 1648.
    case 0x00002029:
    case 0x80072029: return "ERROR_DS_INAPPROPRIATE_AUTH";
    // Original object relative source line 1649.
    case 0x0000202A:
    case 0x8007202A: return "ERROR_DS_AUTH_UNKNOWN";
    // Original object relative source line 1650.
    case 0x0000202B:
    case 0x8007202B: return "ERROR_DS_REFERRAL";
    // Original object relative source line 1651.
    case 0x0000202C:
    case 0x8007202C: return "ERROR_DS_UNAVAILABLE_CRIT_EXTENSION";
    // Original object relative source line 1652.
    case 0x0000202D:
    case 0x8007202D: return "ERROR_DS_CONFIDENTIALITY_REQUIRED";
    // Original object relative source line 1653.
    case 0x0000202E:
    case 0x8007202E: return "ERROR_DS_INAPPROPRIATE_MATCHING";
    // Original object relative source line 1654.
    case 0x0000202F:
    case 0x8007202F: return "ERROR_DS_CONSTRAINT_VIOLATION";
    // Original object relative source line 1655.
    case 0x00002030:
    case 0x80072030: return "ERROR_DS_NO_SUCH_OBJECT";
    // Original object relative source line 1656.
    case 0x00002031:
    case 0x80072031: return "ERROR_DS_ALIAS_PROBLEM";
    // Original object relative source line 1657.
    case 0x00002032:
    case 0x80072032: return "ERROR_DS_INVALID_DN_SYNTAX";
    // Original object relative source line 1658.
    case 0x00002033:
    case 0x80072033: return "ERROR_DS_IS_LEAF";
    // Original object relative source line 1659.
    case 0x00002034:
    case 0x80072034: return "ERROR_DS_ALIAS_DEREF_PROBLEM";
    // Original object relative source line 1660.
    case 0x00002035:
    case 0x80072035: return "ERROR_DS_UNWILLING_TO_PERFORM";
    // Original object relative source line 1661.
    case 0x00002036:
    case 0x80072036: return "ERROR_DS_LOOP_DETECT";
    // Original object relative source line 1662.
    case 0x00002037:
    case 0x80072037: return "ERROR_DS_NAMING_VIOLATION";
    // Original object relative source line 1663.
    case 0x00002038:
    case 0x80072038: return "ERROR_DS_OBJECT_RESULTS_TOO_LARGE";
    // Original object relative source line 1664.
    case 0x00002039:
    case 0x80072039: return "ERROR_DS_AFFECTS_MULTIPLE_DSAS";
    // Original object relative source line 1665.
    case 0x0000203A:
    case 0x8007203A: return "ERROR_DS_SERVER_DOWN";
    // Original object relative source line 1666.
    case 0x0000203B:
    case 0x8007203B: return "ERROR_DS_LOCAL_ERROR";
    // Original object relative source line 1667.
    case 0x0000203C:
    case 0x8007203C: return "ERROR_DS_ENCODING_ERROR";
    // Original object relative source line 1668.
    case 0x0000203D:
    case 0x8007203D: return "ERROR_DS_DECODING_ERROR";
    // Original object relative source line 1669.
    case 0x0000203E:
    case 0x8007203E: return "ERROR_DS_FILTER_UNKNOWN";
    // Original object relative source line 1670.
    case 0x0000203F:
    case 0x8007203F: return "ERROR_DS_PARAM_ERROR";
    // Original object relative source line 1671.
    case 0x00002040:
    case 0x80072040: return "ERROR_DS_NOT_SUPPORTED";
    // Original object relative source line 1672.
    case 0x00002041:
    case 0x80072041: return "ERROR_DS_NO_RESULTS_RETURNED";
    // Original object relative source line 1673.
    case 0x00002042:
    case 0x80072042: return "ERROR_DS_CONTROL_NOT_FOUND";
    // Original object relative source line 1674.
    case 0x00002043:
    case 0x80072043: return "ERROR_DS_CLIENT_LOOP";
    // Original object relative source line 1675.
    case 0x00002044:
    case 0x80072044: return "ERROR_DS_REFERRAL_LIMIT_EXCEEDED";
    // Original object relative source line 1676.
    case 0x0000206D:
    case 0x8007206D: return "ERROR_DS_ROOT_MUST_BE_NC";
    // Original object relative source line 1677.
    case 0x0000206E:
    case 0x8007206E: return "ERROR_DS_ADD_REPLICA_INHIBITED";
    // Original object relative source line 1678.
    case 0x0000206F:
    case 0x8007206F: return "ERROR_DS_ATT_NOT_DEF_IN_SCHEMA";
    // Original object relative source line 1679.
    case 0x00002070:
    case 0x80072070: return "ERROR_DS_MAX_OBJ_SIZE_EXCEEDED";
    // Original object relative source line 1680.
    case 0x00002071:
    case 0x80072071: return "ERROR_DS_OBJ_STRING_NAME_EXISTS";
    // Original object relative source line 1681.
    case 0x00002072:
    case 0x80072072: return "ERROR_DS_NO_RDN_DEFINED_IN_SCHEMA";
    // Original object relative source line 1682.
    case 0x00002073:
    case 0x80072073: return "ERROR_DS_RDN_DOESNT_MATCH_SCHEMA";
    // Original object relative source line 1683.
    case 0x00002074:
    case 0x80072074: return "ERROR_DS_NO_REQUESTED_ATTS_FOUND";
    // Original object relative source line 1684.
    case 0x00002075:
    case 0x80072075: return "ERROR_DS_USER_BUFFER_TO_SMALL";
    // Original object relative source line 1685.
    case 0x00002076:
    case 0x80072076: return "ERROR_DS_ATT_IS_NOT_ON_OBJ";
    // Original object relative source line 1686.
    case 0x00002077:
    case 0x80072077: return "ERROR_DS_ILLEGAL_MOD_OPERATION";
    // Original object relative source line 1687.
    case 0x00002078:
    case 0x80072078: return "ERROR_DS_OBJ_TOO_LARGE";
    // Original object relative source line 1688.
    case 0x00002079:
    case 0x80072079: return "ERROR_DS_BAD_INSTANCE_TYPE";
    // Original object relative source line 1689.
    case 0x0000207A:
    case 0x8007207A: return "ERROR_DS_MASTERDSA_REQUIRED";
    // Original object relative source line 1690.
    case 0x0000207B:
    case 0x8007207B: return "ERROR_DS_OBJECT_CLASS_REQUIRED";
    // Original object relative source line 1691.
    case 0x0000207C:
    case 0x8007207C: return "ERROR_DS_MISSING_REQUIRED_ATT";
    // Original object relative source line 1692.
    case 0x0000207D:
    case 0x8007207D: return "ERROR_DS_ATT_NOT_DEF_FOR_CLASS";
    // Original object relative source line 1693.
    case 0x0000207E:
    case 0x8007207E: return "ERROR_DS_ATT_ALREADY_EXISTS";
    // Original object relative source line 1694.
    case 0x00002080:
    case 0x80072080: return "ERROR_DS_CANT_ADD_ATT_VALUES";
    // Original object relative source line 1695.
    case 0x00002081:
    case 0x80072081: return "ERROR_DS_SINGLE_VALUE_CONSTRAINT";
    // Original object relative source line 1696.
    case 0x00002082:
    case 0x80072082: return "ERROR_DS_RANGE_CONSTRAINT";
    // Original object relative source line 1697.
    case 0x00002083:
    case 0x80072083: return "ERROR_DS_ATT_VAL_ALREADY_EXISTS";
    // Original object relative source line 1698.
    case 0x00002084:
    case 0x80072084: return "ERROR_DS_CANT_REM_MISSING_ATT";
    // Original object relative source line 1699.
    case 0x00002085:
    case 0x80072085: return "ERROR_DS_CANT_REM_MISSING_ATT_VAL";
    // Original object relative source line 1700.
    case 0x00002086:
    case 0x80072086: return "ERROR_DS_ROOT_CANT_BE_SUBREF";
    // Original object relative source line 1701.
    case 0x00002087:
    case 0x80072087: return "ERROR_DS_NO_CHAINING";
    // Original object relative source line 1702.
    case 0x00002088:
    case 0x80072088: return "ERROR_DS_NO_CHAINED_EVAL";
    // Original object relative source line 1703.
    case 0x00002089:
    case 0x80072089: return "ERROR_DS_NO_PARENT_OBJECT";
    // Original object relative source line 1704.
    case 0x0000208A:
    case 0x8007208A: return "ERROR_DS_PARENT_IS_AN_ALIAS";
    // Original object relative source line 1705.
    case 0x0000208B:
    case 0x8007208B: return "ERROR_DS_CANT_MIX_MASTER_AND_REPS";
    // Original object relative source line 1706.
    case 0x0000208C:
    case 0x8007208C: return "ERROR_DS_CHILDREN_EXIST";
    // Original object relative source line 1707.
    case 0x0000208D:
    case 0x8007208D: return "ERROR_DS_OBJ_NOT_FOUND";
    // Original object relative source line 1708.
    case 0x0000208E:
    case 0x8007208E: return "ERROR_DS_ALIASED_OBJ_MISSING";
    // Original object relative source line 1709.
    case 0x0000208F:
    case 0x8007208F: return "ERROR_DS_BAD_NAME_SYNTAX";
    // Original object relative source line 1710.
    case 0x00002090:
    case 0x80072090: return "ERROR_DS_ALIAS_POINTS_TO_ALIAS";
    // Original object relative source line 1711.
    case 0x00002091:
    case 0x80072091: return "ERROR_DS_CANT_DEREF_ALIAS";
    // Original object relative source line 1712.
    case 0x00002092:
    case 0x80072092: return "ERROR_DS_OUT_OF_SCOPE";
    // Original object relative source line 1713.
    case 0x00002094:
    case 0x80072094: return "ERROR_DS_CANT_DELETE_DSA_OBJ";
    // Original object relative source line 1714.
    case 0x00002095:
    case 0x80072095: return "ERROR_DS_GENERIC_ERROR";
    // Original object relative source line 1715.
    case 0x00002096:
    case 0x80072096: return "ERROR_DS_DSA_MUST_BE_INT_MASTER";
    // Original object relative source line 1716.
    case 0x00002097:
    case 0x80072097: return "ERROR_DS_CLASS_NOT_DSA";
    // Original object relative source line 1717.
    case 0x00002098:
    case 0x80072098: return "ERROR_DS_INSUFF_ACCESS_RIGHTS";
    // Original object relative source line 1718.
    case 0x00002099:
    case 0x80072099: return "ERROR_DS_ILLEGAL_SUPERIOR";
    // Original object relative source line 1719.
    case 0x0000209A:
    case 0x8007209A: return "ERROR_DS_ATTRIBUTE_OWNED_BY_SAM";
    // Original object relative source line 1720.
    case 0x0000209B:
    case 0x8007209B: return "ERROR_DS_NAME_TOO_MANY_PARTS";
    // Original object relative source line 1721.
    case 0x0000209C:
    case 0x8007209C: return "ERROR_DS_NAME_TOO_LONG";
    // Original object relative source line 1722.
    case 0x0000209D:
    case 0x8007209D: return "ERROR_DS_NAME_VALUE_TOO_LONG";
    // Original object relative source line 1723.
    case 0x0000209E:
    case 0x8007209E: return "ERROR_DS_NAME_UNPARSEABLE";
    // Original object relative source line 1724.
    case 0x0000209F:
    case 0x8007209F: return "ERROR_DS_NAME_TYPE_UNKNOWN";
    // Original object relative source line 1725.
    case 0x000020A0:
    case 0x800720A0: return "ERROR_DS_NOT_AN_OBJECT";
    // Original object relative source line 1726.
    case 0x000020A1:
    case 0x800720A1: return "ERROR_DS_SEC_DESC_TOO_SHORT";
    // Original object relative source line 1727.
    case 0x000020A2:
    case 0x800720A2: return "ERROR_DS_SEC_DESC_INVALID";
    // Original object relative source line 1728.
    case 0x000020A3:
    case 0x800720A3: return "ERROR_DS_NO_DELETED_NAME";
    // Original object relative source line 1729.
    case 0x000020A4:
    case 0x800720A4: return "ERROR_DS_SUBREF_MUST_HAVE_PARENT";
    // Original object relative source line 1730.
    case 0x000020A5:
    case 0x800720A5: return "ERROR_DS_NCNAME_MUST_BE_NC";
    // Original object relative source line 1731.
    case 0x000020A6:
    case 0x800720A6: return "ERROR_DS_CANT_ADD_SYSTEM_ONLY";
    // Original object relative source line 1732.
    case 0x000020A7:
    case 0x800720A7: return "ERROR_DS_CLASS_MUST_BE_CONCRETE";
    // Original object relative source line 1733.
    case 0x000020A8:
    case 0x800720A8: return "ERROR_DS_INVALID_DMD";
    // Original object relative source line 1734.
    case 0x000020A9:
    case 0x800720A9: return "ERROR_DS_OBJ_GUID_EXISTS";
    // Original object relative source line 1735.
    case 0x000020AA:
    case 0x800720AA: return "ERROR_DS_NOT_ON_BACKLINK";
    // Original object relative source line 1736.
    case 0x000020AB:
    case 0x800720AB: return "ERROR_DS_NO_CROSSREF_FOR_NC";
    // Original object relative source line 1737.
    case 0x000020AC:
    case 0x800720AC: return "ERROR_DS_SHUTTING_DOWN";
    // Original object relative source line 1738.
    case 0x000020AD:
    case 0x800720AD: return "ERROR_DS_UNKNOWN_OPERATION";
    // Original object relative source line 1739.
    case 0x000020AE:
    case 0x800720AE: return "ERROR_DS_INVALID_ROLE_OWNER";
    // Original object relative source line 1740.
    case 0x000020AF:
    case 0x800720AF: return "ERROR_DS_COULDNT_CONTACT_FSMO";
    // Original object relative source line 1741.
    case 0x000020B0:
    case 0x800720B0: return "ERROR_DS_CROSS_NC_DN_RENAME";
    // Original object relative source line 1742.
    case 0x000020B1:
    case 0x800720B1: return "ERROR_DS_CANT_MOD_SYSTEM_ONLY";
    // Original object relative source line 1743.
    case 0x000020B2:
    case 0x800720B2: return "ERROR_DS_REPLICATOR_ONLY";
    // Original object relative source line 1744.
    case 0x000020B3:
    case 0x800720B3: return "ERROR_DS_OBJ_CLASS_NOT_DEFINED";
    // Original object relative source line 1745.
    case 0x000020B4:
    case 0x800720B4: return "ERROR_DS_OBJ_CLASS_NOT_SUBCLASS";
    // Original object relative source line 1746.
    case 0x000020B5:
    case 0x800720B5: return "ERROR_DS_NAME_REFERENCE_INVALID";
    // Original object relative source line 1747.
    case 0x000020B6:
    case 0x800720B6: return "ERROR_DS_CROSS_REF_EXISTS";
    // Original object relative source line 1748.
    case 0x000020B7:
    case 0x800720B7: return "ERROR_DS_CANT_DEL_MASTER_CROSSREF";
    // Original object relative source line 1749.
    case 0x000020B8:
    case 0x800720B8: return "ERROR_DS_SUBTREE_NOTIFY_NOT_NC_HEAD";
    // Original object relative source line 1750.
    case 0x000020B9:
    case 0x800720B9: return "ERROR_DS_NOTIFY_FILTER_TOO_COMPLEX";
    // Original object relative source line 1751.
    case 0x000020BA:
    case 0x800720BA: return "ERROR_DS_DUP_RDN";
    // Original object relative source line 1752.
    case 0x000020BB:
    case 0x800720BB: return "ERROR_DS_DUP_OID";
    // Original object relative source line 1753.
    case 0x000020BC:
    case 0x800720BC: return "ERROR_DS_DUP_MAPI_ID";
    // Original object relative source line 1754.
    case 0x000020BD:
    case 0x800720BD: return "ERROR_DS_DUP_SCHEMA_ID_GUID";
    // Original object relative source line 1755.
    case 0x000020BE:
    case 0x800720BE: return "ERROR_DS_DUP_LDAP_DISPLAY_NAME";
    // Original object relative source line 1756.
    case 0x000020BF:
    case 0x800720BF: return "ERROR_DS_SEMANTIC_ATT_TEST";
    // Original object relative source line 1757.
    case 0x000020C0:
    case 0x800720C0: return "ERROR_DS_SYNTAX_MISMATCH";
    // Original object relative source line 1758.
    case 0x000020C1:
    case 0x800720C1: return "ERROR_DS_EXISTS_IN_MUST_HAVE";
    // Original object relative source line 1759.
    case 0x000020C2:
    case 0x800720C2: return "ERROR_DS_EXISTS_IN_MAY_HAVE";
    // Original object relative source line 1760.
    case 0x000020C3:
    case 0x800720C3: return "ERROR_DS_NONEXISTENT_MAY_HAVE";
    // Original object relative source line 1761.
    case 0x000020C4:
    case 0x800720C4: return "ERROR_DS_NONEXISTENT_MUST_HAVE";
    // Original object relative source line 1762.
    case 0x000020C5:
    case 0x800720C5: return "ERROR_DS_AUX_CLS_TEST_FAIL";
    // Original object relative source line 1763.
    case 0x000020C6:
    case 0x800720C6: return "ERROR_DS_NONEXISTENT_POSS_SUP";
    // Original object relative source line 1764.
    case 0x000020C7:
    case 0x800720C7: return "ERROR_DS_SUB_CLS_TEST_FAIL";
    // Original object relative source line 1765.
    case 0x000020C8:
    case 0x800720C8: return "ERROR_DS_BAD_RDN_ATT_ID_SYNTAX";
    // Original object relative source line 1766.
    case 0x000020C9:
    case 0x800720C9: return "ERROR_DS_EXISTS_IN_AUX_CLS";
    // Original object relative source line 1767.
    case 0x000020CA:
    case 0x800720CA: return "ERROR_DS_EXISTS_IN_SUB_CLS";
    // Original object relative source line 1768.
    case 0x000020CB:
    case 0x800720CB: return "ERROR_DS_EXISTS_IN_POSS_SUP";
    // Original object relative source line 1769.
    case 0x000020CC:
    case 0x800720CC: return "ERROR_DS_RECALCSCHEMA_FAILED";
    // Original object relative source line 1770.
    case 0x000020CD:
    case 0x800720CD: return "ERROR_DS_TREE_DELETE_NOT_FINISHED";
    // Original object relative source line 1771.
    case 0x000020CE:
    case 0x800720CE: return "ERROR_DS_CANT_DELETE";
    // Original object relative source line 1772.
    case 0x000020CF:
    case 0x800720CF: return "ERROR_DS_ATT_SCHEMA_REQ_ID";
    // Original object relative source line 1773.
    case 0x000020D0:
    case 0x800720D0: return "ERROR_DS_BAD_ATT_SCHEMA_SYNTAX";
    // Original object relative source line 1774.
    case 0x000020D1:
    case 0x800720D1: return "ERROR_DS_CANT_CACHE_ATT";
    // Original object relative source line 1775.
    case 0x000020D2:
    case 0x800720D2: return "ERROR_DS_CANT_CACHE_CLASS";
    // Original object relative source line 1776.
    case 0x000020D3:
    case 0x800720D3: return "ERROR_DS_CANT_REMOVE_ATT_CACHE";
    // Original object relative source line 1777.
    case 0x000020D4:
    case 0x800720D4: return "ERROR_DS_CANT_REMOVE_CLASS_CACHE";
    // Original object relative source line 1778.
    case 0x000020D5:
    case 0x800720D5: return "ERROR_DS_CANT_RETRIEVE_DN";
    // Original object relative source line 1779.
    case 0x000020D6:
    case 0x800720D6: return "ERROR_DS_MISSING_SUPREF";
    // Original object relative source line 1780.
    case 0x000020D7:
    case 0x800720D7: return "ERROR_DS_CANT_RETRIEVE_INSTANCE";
    // Original object relative source line 1781.
    case 0x000020D8:
    case 0x800720D8: return "ERROR_DS_CODE_INCONSISTENCY";
    // Original object relative source line 1782.
    case 0x000020D9:
    case 0x800720D9: return "ERROR_DS_DATABASE_ERROR";
    // Original object relative source line 1783.
    case 0x000020DA:
    case 0x800720DA: return "ERROR_DS_GOVERNSID_MISSING";
    // Original object relative source line 1784.
    case 0x000020DB:
    case 0x800720DB: return "ERROR_DS_MISSING_EXPECTED_ATT";
    // Original object relative source line 1785.
    case 0x000020DC:
    case 0x800720DC: return "ERROR_DS_NCNAME_MISSING_CR_REF";
    // Original object relative source line 1786.
    case 0x000020DD:
    case 0x800720DD: return "ERROR_DS_SECURITY_CHECKING_ERROR";
    // Original object relative source line 1787.
    case 0x000020DE:
    case 0x800720DE: return "ERROR_DS_SCHEMA_NOT_LOADED";
    // Original object relative source line 1788.
    case 0x000020DF:
    case 0x800720DF: return "ERROR_DS_SCHEMA_ALLOC_FAILED";
    // Original object relative source line 1789.
    case 0x000020E0:
    case 0x800720E0: return "ERROR_DS_ATT_SCHEMA_REQ_SYNTAX";
    // Original object relative source line 1790.
    case 0x000020E1:
    case 0x800720E1: return "ERROR_DS_GCVERIFY_ERROR";
    // Original object relative source line 1791.
    case 0x000020E2:
    case 0x800720E2: return "ERROR_DS_DRA_SCHEMA_MISMATCH";
    // Original object relative source line 1792.
    case 0x000020E3:
    case 0x800720E3: return "ERROR_DS_CANT_FIND_DSA_OBJ";
    // Original object relative source line 1793.
    case 0x000020E4:
    case 0x800720E4: return "ERROR_DS_CANT_FIND_EXPECTED_NC";
    // Original object relative source line 1794.
    case 0x000020E5:
    case 0x800720E5: return "ERROR_DS_CANT_FIND_NC_IN_CACHE";
    // Original object relative source line 1795.
    case 0x000020E6:
    case 0x800720E6: return "ERROR_DS_CANT_RETRIEVE_CHILD";
    // Original object relative source line 1796.
    case 0x000020E7:
    case 0x800720E7: return "ERROR_DS_SECURITY_ILLEGAL_MODIFY";
    // Original object relative source line 1797.
    case 0x000020E8:
    case 0x800720E8: return "ERROR_DS_CANT_REPLACE_HIDDEN_REC";
    // Original object relative source line 1798.
    case 0x000020E9:
    case 0x800720E9: return "ERROR_DS_BAD_HIERARCHY_FILE";
    // Original object relative source line 1799.
    case 0x000020EA:
    case 0x800720EA: return "ERROR_DS_BUILD_HIERARCHY_TABLE_FAILED";
    // Original object relative source line 1800.
    case 0x000020EB:
    case 0x800720EB: return "ERROR_DS_CONFIG_PARAM_MISSING";
    // Original object relative source line 1801.
    case 0x000020EC:
    case 0x800720EC: return "ERROR_DS_COUNTING_AB_INDICES_FAILED";
    // Original object relative source line 1802.
    case 0x000020ED:
    case 0x800720ED: return "ERROR_DS_HIERARCHY_TABLE_MALLOC_FAILED";
    // Original object relative source line 1803.
    case 0x000020EE:
    case 0x800720EE: return "ERROR_DS_INTERNAL_FAILURE";
    // Original object relative source line 1804.
    case 0x000020EF:
    case 0x800720EF: return "ERROR_DS_UNKNOWN_ERROR";
    // Original object relative source line 1805.
    case 0x000020F0:
    case 0x800720F0: return "ERROR_DS_ROOT_REQUIRES_CLASS_TOP";
    // Original object relative source line 1806.
    case 0x000020F1:
    case 0x800720F1: return "ERROR_DS_REFUSING_FSMO_ROLES";
    // Original object relative source line 1807.
    case 0x000020F2:
    case 0x800720F2: return "ERROR_DS_MISSING_FSMO_SETTINGS";
    // Original object relative source line 1808.
    case 0x000020F3:
    case 0x800720F3: return "ERROR_DS_UNABLE_TO_SURRENDER_ROLES";
    // Original object relative source line 1809.
    case 0x000020F4:
    case 0x800720F4: return "ERROR_DS_DRA_GENERIC";
    // Original object relative source line 1810.
    case 0x000020F5:
    case 0x800720F5: return "ERROR_DS_DRA_INVALID_PARAMETER";
    // Original object relative source line 1811.
    case 0x000020F6:
    case 0x800720F6: return "ERROR_DS_DRA_BUSY";
    // Original object relative source line 1812.
    case 0x000020F7:
    case 0x800720F7: return "ERROR_DS_DRA_BAD_DN";
    // Original object relative source line 1813.
    case 0x000020F8:
    case 0x800720F8: return "ERROR_DS_DRA_BAD_NC";
    // Original object relative source line 1814.
    case 0x000020F9:
    case 0x800720F9: return "ERROR_DS_DRA_DN_EXISTS";
    // Original object relative source line 1815.
    case 0x000020FA:
    case 0x800720FA: return "ERROR_DS_DRA_INTERNAL_ERROR";
    // Original object relative source line 1816.
    case 0x000020FB:
    case 0x800720FB: return "ERROR_DS_DRA_INCONSISTENT_DIT";
    // Original object relative source line 1817.
    case 0x000020FC:
    case 0x800720FC: return "ERROR_DS_DRA_CONNECTION_FAILED";
    // Original object relative source line 1818.
    case 0x000020FD:
    case 0x800720FD: return "ERROR_DS_DRA_BAD_INSTANCE_TYPE";
    // Original object relative source line 1819.
    case 0x000020FE:
    case 0x800720FE: return "ERROR_DS_DRA_OUT_OF_MEM";
    // Original object relative source line 1820.
    case 0x000020FF:
    case 0x800720FF: return "ERROR_DS_DRA_MAIL_PROBLEM";
    // Original object relative source line 1821.
    case 0x00002100:
    case 0x80072100: return "ERROR_DS_DRA_REF_ALREADY_EXISTS";
    // Original object relative source line 1822.
    case 0x00002101:
    case 0x80072101: return "ERROR_DS_DRA_REF_NOT_FOUND";
    // Original object relative source line 1823.
    case 0x00002102:
    case 0x80072102: return "ERROR_DS_DRA_OBJ_IS_REP_SOURCE";
    // Original object relative source line 1824.
    case 0x00002103:
    case 0x80072103: return "ERROR_DS_DRA_DB_ERROR";
    // Original object relative source line 1825.
    case 0x00002104:
    case 0x80072104: return "ERROR_DS_DRA_NO_REPLICA";
    // Original object relative source line 1826.
    case 0x00002105:
    case 0x80072105: return "ERROR_DS_DRA_ACCESS_DENIED";
    // Original object relative source line 1827.
    case 0x00002106:
    case 0x80072106: return "ERROR_DS_DRA_NOT_SUPPORTED";
    // Original object relative source line 1828.
    case 0x00002107:
    case 0x80072107: return "ERROR_DS_DRA_RPC_CANCELLED";
    // Original object relative source line 1829.
    case 0x00002108:
    case 0x80072108: return "ERROR_DS_DRA_SOURCE_DISABLED";
    // Original object relative source line 1830.
    case 0x00002109:
    case 0x80072109: return "ERROR_DS_DRA_SINK_DISABLED";
    // Original object relative source line 1831.
    case 0x0000210A:
    case 0x8007210A: return "ERROR_DS_DRA_NAME_COLLISION";
    // Original object relative source line 1832.
    case 0x0000210B:
    case 0x8007210B: return "ERROR_DS_DRA_SOURCE_REINSTALLED";
    // Original object relative source line 1833.
    case 0x0000210C:
    case 0x8007210C: return "ERROR_DS_DRA_MISSING_PARENT";
    // Original object relative source line 1834.
    case 0x0000210D:
    case 0x8007210D: return "ERROR_DS_DRA_PREEMPTED";
    // Original object relative source line 1835.
    case 0x0000210E:
    case 0x8007210E: return "ERROR_DS_DRA_ABANDON_SYNC";
    // Original object relative source line 1836.
    case 0x0000210F:
    case 0x8007210F: return "ERROR_DS_DRA_SHUTDOWN";
    // Original object relative source line 1837.
    case 0x00002110:
    case 0x80072110: return "ERROR_DS_DRA_INCOMPATIBLE_PARTIAL_SET";
    // Original object relative source line 1838.
    case 0x00002111:
    case 0x80072111: return "ERROR_DS_DRA_SOURCE_IS_PARTIAL_REPLICA";
    // Original object relative source line 1839.
    case 0x00002112:
    case 0x80072112: return "ERROR_DS_DRA_EXTN_CONNECTION_FAILED";
    // Original object relative source line 1840.
    case 0x00002113:
    case 0x80072113: return "ERROR_DS_INSTALL_SCHEMA_MISMATCH";
    // Original object relative source line 1841.
    case 0x00002114:
    case 0x80072114: return "ERROR_DS_DUP_LINK_ID";
    // Original object relative source line 1842.
    case 0x00002115:
    case 0x80072115: return "ERROR_DS_NAME_ERROR_RESOLVING";
    // Original object relative source line 1843.
    case 0x00002116:
    case 0x80072116: return "ERROR_DS_NAME_ERROR_NOT_FOUND";
    // Original object relative source line 1844.
    case 0x00002117:
    case 0x80072117: return "ERROR_DS_NAME_ERROR_NOT_UNIQUE";
    // Original object relative source line 1845.
    case 0x00002118:
    case 0x80072118: return "ERROR_DS_NAME_ERROR_NO_MAPPING";
    // Original object relative source line 1846.
    case 0x00002119:
    case 0x80072119: return "ERROR_DS_NAME_ERROR_DOMAIN_ONLY";
    // Original object relative source line 1847.
    case 0x0000211A:
    case 0x8007211A: return "ERROR_DS_NAME_ERROR_NO_SYNTACTICAL_MAPPING";
    // Original object relative source line 1848.
    case 0x0000211B:
    case 0x8007211B: return "ERROR_DS_CONSTRUCTED_ATT_MOD";
    // Original object relative source line 1849.
    case 0x0000211C:
    case 0x8007211C: return "ERROR_DS_WRONG_OM_OBJ_CLASS";
    // Original object relative source line 1850.
    case 0x0000211D:
    case 0x8007211D: return "ERROR_DS_DRA_REPL_PENDING";
    // Original object relative source line 1851.
    case 0x00002328:
    case 0x80072328: return "DNS_ERROR_RESPONSE_CODES_BASE";
    // Original object relative source line 1853.
    case 0x00002329:
    case 0x80072329: return "DNS_ERROR_RCODE_FORMAT_ERROR";
    // Original object relative source line 1854.
    case 0x0000232A:
    case 0x8007232A: return "DNS_ERROR_RCODE_SERVER_FAILURE";
    // Original object relative source line 1855.
    case 0x0000232B:
    case 0x8007232B: return "DNS_ERROR_RCODE_NAME_ERROR";
    // Original object relative source line 1856.
    case 0x0000232C:
    case 0x8007232C: return "DNS_ERROR_RCODE_NOT_IMPLEMENTED";
    // Original object relative source line 1857.
    case 0x0000232D:
    case 0x8007232D: return "DNS_ERROR_RCODE_REFUSED";
    // Original object relative source line 1858.
    case 0x0000232E:
    case 0x8007232E: return "DNS_ERROR_RCODE_YXDOMAIN";
    // Original object relative source line 1859.
    case 0x0000232F:
    case 0x8007232F: return "DNS_ERROR_RCODE_YXRRSET";
    // Original object relative source line 1860.
    case 0x00002330:
    case 0x80072330: return "DNS_ERROR_RCODE_NXRRSET";
    // Original object relative source line 1861.
    case 0x00002331:
    case 0x80072331: return "DNS_ERROR_RCODE_NOTAUTH";
    // Original object relative source line 1862.
    case 0x00002332:
    case 0x80072332: return "DNS_ERROR_RCODE_NOTZONE";
    // Original object relative source line 1863.
    case 0x00002338:
    case 0x80072338: return "DNS_ERROR_RCODE_BADSIG";
    // Original object relative source line 1864.
    case 0x00002339:
    case 0x80072339: return "DNS_ERROR_RCODE_BADKEY";
    // Original object relative source line 1865.
    case 0x0000233A:
    case 0x8007233A: return "DNS_ERROR_RCODE_BADTIME";
    // Original object relative source line 1866.
    case 0x0000251C:
    case 0x8007251C: return "DNS_ERROR_PACKET_FMT_BASE";
    // Original object relative source line 1867.
    case 0x0000251D:
    case 0x8007251D: return "DNS_INFO_NO_RECORDS";
    // Original object relative source line 1868.
    case 0x0000251E:
    case 0x8007251E: return "DNS_ERROR_BAD_PACKET";
    // Original object relative source line 1869.
    case 0x0000251F:
    case 0x8007251F: return "DNS_ERROR_NO_PACKET";
    // Original object relative source line 1870.
    case 0x00002520:
    case 0x80072520: return "DNS_ERROR_RCODE";
    // Original object relative source line 1871.
    case 0x00002521:
    case 0x80072521: return "DNS_ERROR_UNSECURE_PACKET";
    // Original object relative source line 1872.
    case 0x0000254E:
    case 0x8007254E: return "DNS_ERROR_GENERAL_API_BASE";
    // Original object relative source line 1873.
    case 0x0000254F:
    case 0x8007254F: return "DNS_ERROR_INVALID_TYPE";
    // Original object relative source line 1874.
    case 0x00002550:
    case 0x80072550: return "DNS_ERROR_INVALID_IP_ADDRESS";
    // Original object relative source line 1875.
    case 0x00002551:
    case 0x80072551: return "DNS_ERROR_INVALID_PROPERTY";
    // Original object relative source line 1876.
    case 0x00002552:
    case 0x80072552: return "DNS_ERROR_TRY_AGAIN_LATER";
    // Original object relative source line 1877.
    case 0x00002553:
    case 0x80072553: return "DNS_ERROR_NOT_UNIQUE";
    // Original object relative source line 1878.
    case 0x00002554:
    case 0x80072554: return "DNS_ERROR_NON_RFC_NAME";
    // Original object relative source line 1879.
    case 0x00002555:
    case 0x80072555: return "DNS_STATUS_FQDN";
    // Original object relative source line 1880.
    case 0x00002556:
    case 0x80072556: return "DNS_STATUS_DOTTED_NAME";
    // Original object relative source line 1881.
    case 0x00002557:
    case 0x80072557: return "DNS_STATUS_SINGLE_PART_NAME";
    // Original object relative source line 1882.
    case 0x00002580:
    case 0x80072580: return "DNS_ERROR_ZONE_BASE";
    // Original object relative source line 1883.
    case 0x00002581:
    case 0x80072581: return "DNS_ERROR_ZONE_DOES_NOT_EXIST";
    // Original object relative source line 1884.
    case 0x00002582:
    case 0x80072582: return "DNS_ERROR_NO_ZONE_INFO";
    // Original object relative source line 1885.
    case 0x00002583:
    case 0x80072583: return "DNS_ERROR_INVALID_ZONE_OPERATION";
    // Original object relative source line 1886.
    case 0x00002584:
    case 0x80072584: return "DNS_ERROR_ZONE_CONFIGURATION_ERROR";
    // Original object relative source line 1887.
    case 0x00002585:
    case 0x80072585: return "DNS_ERROR_ZONE_HAS_NO_SOA_RECORD";
    // Original object relative source line 1888.
    case 0x00002586:
    case 0x80072586: return "DNS_ERROR_ZONE_HAS_NO_NS_RECORDS";
    // Original object relative source line 1889.
    case 0x00002587:
    case 0x80072587: return "DNS_ERROR_ZONE_LOCKED";
    // Original object relative source line 1890.
    case 0x00002588:
    case 0x80072588: return "DNS_ERROR_ZONE_CREATION_FAILED";
    // Original object relative source line 1891.
    case 0x00002589:
    case 0x80072589: return "DNS_ERROR_ZONE_ALREADY_EXISTS";
    // Original object relative source line 1892.
    case 0x0000258A:
    case 0x8007258A: return "DNS_ERROR_AUTOZONE_ALREADY_EXISTS";
    // Original object relative source line 1893.
    case 0x0000258B:
    case 0x8007258B: return "DNS_ERROR_INVALID_ZONE_TYPE";
    // Original object relative source line 1894.
    case 0x0000258C:
    case 0x8007258C: return "DNS_ERROR_SECONDARY_REQUIRES_MASTER_IP";
    // Original object relative source line 1895.
    case 0x0000258D:
    case 0x8007258D: return "DNS_ERROR_ZONE_NOT_SECONDARY";
    // Original object relative source line 1896.
    case 0x0000258E:
    case 0x8007258E: return "DNS_ERROR_NEED_SECONDARY_ADDRESSES";
    // Original object relative source line 1897.
    case 0x0000258F:
    case 0x8007258F: return "DNS_ERROR_WINS_INIT_FAILED";
    // Original object relative source line 1898.
    case 0x00002590:
    case 0x80072590: return "DNS_ERROR_NEED_WINS_SERVERS";
    // Original object relative source line 1899.
    case 0x00002591:
    case 0x80072591: return "DNS_ERROR_NBSTAT_INIT_FAILED";
    // Original object relative source line 1900.
    case 0x00002592:
    case 0x80072592: return "DNS_ERROR_SOA_DELETE_INVALID";
    // Original object relative source line 1901.
    case 0x000025B2:
    case 0x800725B2: return "DNS_ERROR_DATAFILE_BASE";
    // Original object relative source line 1902.
    case 0x000025B3:
    case 0x800725B3: return "DNS_ERROR_PRIMARY_REQUIRES_DATAFILE";
    // Original object relative source line 1903.
    case 0x000025B4:
    case 0x800725B4: return "DNS_ERROR_INVALID_DATAFILE_NAME";
    // Original object relative source line 1904.
    case 0x000025B5:
    case 0x800725B5: return "DNS_ERROR_DATAFILE_OPEN_FAILURE";
    // Original object relative source line 1905.
    case 0x000025B6:
    case 0x800725B6: return "DNS_ERROR_FILE_WRITEBACK_FAILED";
    // Original object relative source line 1906.
    case 0x000025B7:
    case 0x800725B7: return "DNS_ERROR_DATAFILE_PARSING";
    // Original object relative source line 1907.
    case 0x000025E4:
    case 0x800725E4: return "DNS_ERROR_DATABASE_BASE";
    // Original object relative source line 1908.
    case 0x000025E5:
    case 0x800725E5: return "DNS_ERROR_RECORD_DOES_NOT_EXIST";
    // Original object relative source line 1909.
    case 0x000025E6:
    case 0x800725E6: return "DNS_ERROR_RECORD_FORMAT";
    // Original object relative source line 1910.
    case 0x000025E7:
    case 0x800725E7: return "DNS_ERROR_NODE_CREATION_FAILED";
    // Original object relative source line 1911.
    case 0x000025E8:
    case 0x800725E8: return "DNS_ERROR_UNKNOWN_RECORD_TYPE";
    // Original object relative source line 1912.
    case 0x000025E9:
    case 0x800725E9: return "DNS_ERROR_RECORD_TIMED_OUT";
    // Original object relative source line 1913.
    case 0x000025EA:
    case 0x800725EA: return "DNS_ERROR_NAME_NOT_IN_ZONE";
    // Original object relative source line 1914.
    case 0x000025EB:
    case 0x800725EB: return "DNS_ERROR_CNAME_LOOP";
    // Original object relative source line 1915.
    case 0x000025EC:
    case 0x800725EC: return "DNS_ERROR_NODE_IS_CNAME";
    // Original object relative source line 1916.
    case 0x000025ED:
    case 0x800725ED: return "DNS_ERROR_CNAME_COLLISION";
    // Original object relative source line 1917.
    case 0x000025EE:
    case 0x800725EE: return "DNS_ERROR_RECORD_ONLY_AT_ZONE_ROOT";
    // Original object relative source line 1918.
    case 0x000025EF:
    case 0x800725EF: return "DNS_ERROR_RECORD_ALREADY_EXISTS";
    // Original object relative source line 1919.
    case 0x000025F0:
    case 0x800725F0: return "DNS_ERROR_SECONDARY_DATA";
    // Original object relative source line 1920.
    case 0x000025F1:
    case 0x800725F1: return "DNS_ERROR_NO_CREATE_CACHE_DATA";
    // Original object relative source line 1921.
    case 0x000025F2:
    case 0x800725F2: return "DNS_ERROR_NAME_DOES_NOT_EXIST";
    // Original object relative source line 1922.
    case 0x000025F3:
    case 0x800725F3: return "DNS_WARNING_PTR_CREATE_FAILED";
    // Original object relative source line 1923.
    case 0x000025F4:
    case 0x800725F4: return "DNS_WARNING_DOMAIN_UNDELETED";
    // Original object relative source line 1924.
    case 0x000025F5:
    case 0x800725F5: return "DNS_ERROR_DS_UNAVAILABLE";
    // Original object relative source line 1925.
    case 0x000025F6:
    case 0x800725F6: return "DNS_ERROR_DS_ZONE_ALREADY_EXISTS";
    // Original object relative source line 1926.
    case 0x000025F7:
    case 0x800725F7: return "DNS_ERROR_NO_BOOTFILE_IF_DS_ZONE";
    // Original object relative source line 1927.
    case 0x00002616:
    case 0x80072616: return "DNS_ERROR_OPERATION_BASE";
    // Original object relative source line 1928.
    case 0x00002617:
    case 0x80072617: return "DNS_INFO_AXFR_COMPLETE";
    // Original object relative source line 1929.
    case 0x00002618:
    case 0x80072618: return "DNS_ERROR_AXFR";
    // Original object relative source line 1930.
    case 0x00002619:
    case 0x80072619: return "DNS_INFO_ADDED_LOCAL_WINS";
    // Original object relative source line 1931.
    case 0x00002648:
    case 0x80072648: return "DNS_ERROR_SECURE_BASE";
    // Original object relative source line 1932.
    case 0x00002649:
    case 0x80072649: return "DNS_STATUS_CONTINUE_NEEDED";
    // Original object relative source line 1933.
    case 0x0000267A:
    case 0x8007267A: return "DNS_ERROR_SETUP_BASE";
    // Original object relative source line 1934.
    case 0x0000267B:
    case 0x8007267B: return "DNS_ERROR_NO_TCPIP";
    // Original object relative source line 1935.
    case 0x0000267C:
    case 0x8007267C: return "DNS_ERROR_NO_DNS_SERVERS";
    // Original object relative source line 1936.
    case 0x00002710:
    case 0x80072710: return "WSABASEERR";
    // Original object relative source line 1937.
    case 0x00002714:
    case 0x80072714: return "WSAEINTR";
    // Original object relative source line 1938.
    case 0x00002719:
    case 0x80072719: return "WSAEBADF";
    // Original object relative source line 1939.
    case 0x0000271D:
    case 0x8007271D: return "WSAEACCES";
    // Original object relative source line 1940.
    case 0x0000271E:
    case 0x8007271E: return "WSAEFAULT";
    // Original object relative source line 1941.
    case 0x00002726:
    case 0x80072726: return "WSAEINVAL";
    // Original object relative source line 1942.
    case 0x00002728:
    case 0x80072728: return "WSAEMFILE";
    // Original object relative source line 1943.
    case 0x00002733:
    case 0x80072733: return "WSAEWOULDBLOCK";
    // Original object relative source line 1944.
    case 0x00002734:
    case 0x80072734: return "WSAEINPROGRESS";
    // Original object relative source line 1945.
    case 0x00002735:
    case 0x80072735: return "WSAEALREADY";
    // Original object relative source line 1946.
    case 0x00002736:
    case 0x80072736: return "WSAENOTSOCK";
    // Original object relative source line 1947.
    case 0x00002737:
    case 0x80072737: return "WSAEDESTADDRREQ";
    // Original object relative source line 1948.
    case 0x00002738:
    case 0x80072738: return "WSAEMSGSIZE";
    // Original object relative source line 1949.
    case 0x00002739:
    case 0x80072739: return "WSAEPROTOTYPE";
    // Original object relative source line 1950.
    case 0x0000273A:
    case 0x8007273A: return "WSAENOPROTOOPT";
    // Original object relative source line 1951.
    case 0x0000273B:
    case 0x8007273B: return "WSAEPROTONOSUPPORT";
    // Original object relative source line 1952.
    case 0x0000273C:
    case 0x8007273C: return "WSAESOCKTNOSUPPORT";
    // Original object relative source line 1953.
    case 0x0000273D:
    case 0x8007273D: return "WSAEOPNOTSUPP";
    // Original object relative source line 1954.
    case 0x0000273E:
    case 0x8007273E: return "WSAEPFNOSUPPORT";
    // Original object relative source line 1955.
    case 0x0000273F:
    case 0x8007273F: return "WSAEAFNOSUPPORT";
    // Original object relative source line 1956.
    case 0x00002740:
    case 0x80072740: return "WSAEADDRINUSE";
    // Original object relative source line 1957.
    case 0x00002741:
    case 0x80072741: return "WSAEADDRNOTAVAIL";
    // Original object relative source line 1958.
    case 0x00002742:
    case 0x80072742: return "WSAENETDOWN";
    // Original object relative source line 1959.
    case 0x00002743:
    case 0x80072743: return "WSAENETUNREACH";
    // Original object relative source line 1960.
    case 0x00002744:
    case 0x80072744: return "WSAENETRESET";
    // Original object relative source line 1961.
    case 0x00002745:
    case 0x80072745: return "WSAECONNABORTED";
    // Original object relative source line 1962.
    case 0x00002746:
    case 0x80072746: return "WSAECONNRESET";
    // Original object relative source line 1963.
    case 0x00002747:
    case 0x80072747: return "WSAENOBUFS";
    // Original object relative source line 1964.
    case 0x00002748:
    case 0x80072748: return "WSAEISCONN";
    // Original object relative source line 1965.
    case 0x00002749:
    case 0x80072749: return "WSAENOTCONN";
    // Original object relative source line 1966.
    case 0x0000274A:
    case 0x8007274A: return "WSAESHUTDOWN";
    // Original object relative source line 1967.
    case 0x0000274B:
    case 0x8007274B: return "WSAETOOMANYREFS";
    // Original object relative source line 1968.
    case 0x0000274C:
    case 0x8007274C: return "WSAETIMEDOUT";
    // Original object relative source line 1969.
    case 0x0000274D:
    case 0x8007274D: return "WSAECONNREFUSED";
    // Original object relative source line 1970.
    case 0x0000274E:
    case 0x8007274E: return "WSAELOOP";
    // Original object relative source line 1971.
    case 0x0000274F:
    case 0x8007274F: return "WSAENAMETOOLONG";
    // Original object relative source line 1972.
    case 0x00002750:
    case 0x80072750: return "WSAEHOSTDOWN";
    // Original object relative source line 1973.
    case 0x00002751:
    case 0x80072751: return "WSAEHOSTUNREACH";
    // Original object relative source line 1974.
    case 0x00002752:
    case 0x80072752: return "WSAENOTEMPTY";
    // Original object relative source line 1975.
    case 0x00002753:
    case 0x80072753: return "WSAEPROCLIM";
    // Original object relative source line 1976.
    case 0x00002754:
    case 0x80072754: return "WSAEUSERS";
    // Original object relative source line 1977.
    case 0x00002755:
    case 0x80072755: return "WSAEDQUOT";
    // Original object relative source line 1978.
    case 0x00002756:
    case 0x80072756: return "WSAESTALE";
    // Original object relative source line 1979.
    case 0x00002757:
    case 0x80072757: return "WSAEREMOTE";
    // Original object relative source line 1980.
    case 0x0000276B:
    case 0x8007276B: return "WSASYSNOTREADY";
    // Original object relative source line 1981.
    case 0x0000276C:
    case 0x8007276C: return "WSAVERNOTSUPPORTED";
    // Original object relative source line 1982.
    case 0x0000276D:
    case 0x8007276D: return "WSANOTINITIALISED";
    // Original object relative source line 1983.
    case 0x00002775:
    case 0x80072775: return "WSAEDISCON";
    // Original object relative source line 1984.
    case 0x00002776:
    case 0x80072776: return "WSAENOMORE";
    // Original object relative source line 1985.
    case 0x00002777:
    case 0x80072777: return "WSAECANCELLED";
    // Original object relative source line 1986.
    case 0x00002778:
    case 0x80072778: return "WSAEINVALIDPROCTABLE";
    // Original object relative source line 1987.
    case 0x00002779:
    case 0x80072779: return "WSAEINVALIDPROVIDER";
    // Original object relative source line 1988.
    case 0x0000277A:
    case 0x8007277A: return "WSAEPROVIDERFAILEDINIT";
    // Original object relative source line 1989.
    case 0x0000277B:
    case 0x8007277B: return "WSASYSCALLFAILURE";
    // Original object relative source line 1990.
    case 0x0000277C:
    case 0x8007277C: return "WSASERVICE_NOT_FOUND";
    // Original object relative source line 1991.
    case 0x0000277D:
    case 0x8007277D: return "WSATYPE_NOT_FOUND";
    // Original object relative source line 1992.
    case 0x0000277E:
    case 0x8007277E: return "WSA_E_NO_MORE";
    // Original object relative source line 1993.
    case 0x0000277F:
    case 0x8007277F: return "WSA_E_CANCELLED";
    // Original object relative source line 1994.
    case 0x00002780:
    case 0x80072780: return "WSAEREFUSED";
    // Original object relative source line 1995.
    case 0x00002AF9:
    case 0x80072AF9: return "WSAHOST_NOT_FOUND";
    // Original object relative source line 1996.
    case 0x00002AFA:
    case 0x80072AFA: return "WSATRY_AGAIN";
    // Original object relative source line 1997.
    case 0x00002AFB:
    case 0x80072AFB: return "WSANO_RECOVERY";
    // Original object relative source line 1998.
    case 0x00002AFC:
    case 0x80072AFC: return "WSANO_DATA";
    // Original object relative source line 1999.
    case 0x00002AFD:
    case 0x80072AFD: return "WSA_QOS_RECEIVERS";
    // Original object relative source line 2000.
    case 0x00002AFE:
    case 0x80072AFE: return "WSA_QOS_SENDERS";
    // Original object relative source line 2001.
    case 0x00002AFF:
    case 0x80072AFF: return "WSA_QOS_NO_SENDERS";
    // Original object relative source line 2002.
    case 0x00002B00:
    case 0x80072B00: return "WSA_QOS_NO_RECEIVERS";
    // Original object relative source line 2003.
    case 0x00002B01:
    case 0x80072B01: return "WSA_QOS_REQUEST_CONFIRMED";
    // Original object relative source line 2004.
    case 0x00002B02:
    case 0x80072B02: return "WSA_QOS_ADMISSION_FAILURE";
    // Original object relative source line 2005.
    case 0x00002B03:
    case 0x80072B03: return "WSA_QOS_POLICY_FAILURE";
    // Original object relative source line 2006.
    case 0x00002B04:
    case 0x80072B04: return "WSA_QOS_BAD_STYLE";
    // Original object relative source line 2007.
    case 0x00002B05:
    case 0x80072B05: return "WSA_QOS_BAD_OBJECT";
    // Original object relative source line 2008.
    case 0x00002B06:
    case 0x80072B06: return "WSA_QOS_TRAFFIC_CTRL_ERROR";
    // Original object relative source line 2009.
    case 0x00002B07:
    case 0x80072B07: return "WSA_QOS_GENERIC_ERROR";
    // Original object relative source line 2015.
    case 0x80004024: return "CO_E_ATTEMPT_TO_CREATE_OUTSIDE_CLIENT_CONTEXT";
    // Original object relative source line 2016.
    case 0x80004025: return "CO_E_SERVER_PAUSED";
    // Original object relative source line 2017.
    case 0x80004026: return "CO_E_SERVER_NOT_PAUSED";
    // Original object relative source line 2018.
    case 0x80004027: return "CO_E_CLASS_DISABLED";
    // Original object relative source line 2019.
    case 0x80004028: return "CO_E_CLRNOTAVAILABLE";
    // Original object relative source line 2020.
    case 0x80004029: return "CO_E_ASYNC_WORK_REJECTED";
    // Original object relative source line 2021.
    case 0x8000402A: return "CO_E_SERVER_INIT_TIMEOUT";
    // Original object relative source line 2022.
    case 0x8000402B: return "CO_E_NO_SECCTX_IN_ACTIVATE";
    // Original object relative source line 2023.
    case 0x80004030: return "CO_E_TRACKER_CONFIG";
    // Original object relative source line 2024.
    case 0x80004031: return "CO_E_THREADPOOL_CONFIG";
    // Original object relative source line 2025.
    case 0x80004032: return "CO_E_SXS_CONFIG";
    // Original object relative source line 2026.
    case 0x80004033: return "CO_E_MALFORMED_SPN";
    // Original object relative source line 2027.
    case 0x80040156: return "REGDB_E_BADTHREADINGMODEL";
    // Original object relative source line 2034.
    case 0x00040202: return "EVENT_S_NOSUBSCRIBERS";
    // Original object relative source line 2049.
    case 0x8004D000: return "XACT_E_FIRST";
    // Original object relative source line 2050.
    case 0x8004D029: return "XACT_E_LAST";
    // Original object relative source line 2051.
    case 0x0004D000: return "XACT_S_FIRST";
    // Original object relative source line 2052.
    case 0x0004D010: return "XACT_S_LAST";
    // Original object relative source line 2054.
    case 0x8004D001: return "XACT_E_CANTRETAIN";
    // Original object relative source line 2055.
    case 0x8004D002: return "XACT_E_COMMITFAILED";
    // Original object relative source line 2056.
    case 0x8004D003: return "XACT_E_COMMITPREVENTED";
    // Original object relative source line 2057.
    case 0x8004D004: return "XACT_E_HEURISTICABORT";
    // Original object relative source line 2058.
    case 0x8004D005: return "XACT_E_HEURISTICCOMMIT";
    // Original object relative source line 2059.
    case 0x8004D006: return "XACT_E_HEURISTICDAMAGE";
    // Original object relative source line 2060.
    case 0x8004D007: return "XACT_E_HEURISTICDANGER";
    // Original object relative source line 2061.
    case 0x8004D008: return "XACT_E_ISOLATIONLEVEL";
    // Original object relative source line 2062.
    case 0x8004D009: return "XACT_E_NOASYNC";
    // Original object relative source line 2063.
    case 0x8004D00A: return "XACT_E_NOENLIST";
    // Original object relative source line 2064.
    case 0x8004D00B: return "XACT_E_NOISORETAIN";
    // Original object relative source line 2065.
    case 0x8004D00C: return "XACT_E_NORESOURCE";
    // Original object relative source line 2066.
    case 0x8004D00D: return "XACT_E_NOTCURRENT";
    // Original object relative source line 2067.
    case 0x8004D00E: return "XACT_E_NOTRANSACTION";
    // Original object relative source line 2068.
    case 0x8004D00F: return "XACT_E_NOTSUPPORTED";
    // Original object relative source line 2069.
    case 0x8004D010: return "XACT_E_UNKNOWNRMGRID";
    // Original object relative source line 2070.
    case 0x8004D011: return "XACT_E_WRONGSTATE";
    // Original object relative source line 2071.
    case 0x8004D012: return "XACT_E_WRONGUOW";
    // Original object relative source line 2072.
    case 0x8004D013: return "XACT_E_XTIONEXISTS";
    // Original object relative source line 2073.
    case 0x8004D014: return "XACT_E_NOIMPORTOBJECT";
    // Original object relative source line 2074.
    case 0x8004D015: return "XACT_E_INVALIDCOOKIE";
    // Original object relative source line 2075.
    case 0x8004D016: return "XACT_E_INDOUBT";
    // Original object relative source line 2076.
    case 0x8004D017: return "XACT_E_NOTIMEOUT";
    // Original object relative source line 2077.
    case 0x8004D018: return "XACT_E_ALREADYINPROGRESS";
    // Original object relative source line 2078.
    case 0x8004D019: return "XACT_E_ABORTED";
    // Original object relative source line 2079.
    case 0x8004D01A: return "XACT_E_LOGFULL";
    // Original object relative source line 2080.
    case 0x8004D01B: return "XACT_E_TMNOTAVAILABLE";
    // Original object relative source line 2081.
    case 0x8004D01C: return "XACT_E_CONNECTION_DOWN";
    // Original object relative source line 2082.
    case 0x8004D01D: return "XACT_E_CONNECTION_DENIED";
    // Original object relative source line 2083.
    case 0x8004D01E: return "XACT_E_REENLISTTIMEOUT";
    // Original object relative source line 2084.
    case 0x8004D01F: return "XACT_E_TIP_CONNECT_FAILED";
    // Original object relative source line 2085.
    case 0x8004D020: return "XACT_E_TIP_PROTOCOL_ERROR";
    // Original object relative source line 2086.
    case 0x8004D021: return "XACT_E_TIP_PULL_FAILED";
    // Original object relative source line 2087.
    case 0x8004D022: return "XACT_E_DEST_TMNOTAVAILABLE";
    // Original object relative source line 2088.
    case 0x8004D023: return "XACT_E_TIP_DISABLED";
    // Original object relative source line 2089.
    case 0x8004D024: return "XACT_E_NETWORK_TX_DISABLED";
    // Original object relative source line 2090.
    case 0x8004D025: return "XACT_E_PARTNER_NETWORK_TX_DISABLED";
    // Original object relative source line 2091.
    case 0x8004D026: return "XACT_E_XA_TX_DISABLED";
    // Original object relative source line 2092.
    case 0x8004D027: return "XACT_E_UNABLE_TO_READ_DTC_CONFIG";
    // Original object relative source line 2093.
    case 0x8004D028: return "XACT_E_UNABLE_TO_LOAD_DTC_PROXY";
    // Original object relative source line 2095.
    case 0x8004D080: return "XACT_E_CLERKNOTFOUND";
    // Original object relative source line 2096.
    case 0x8004D081: return "XACT_E_CLERKEXISTS";
    // Original object relative source line 2097.
    case 0x8004D082: return "XACT_E_RECOVERYINPROGRESS";
    // Original object relative source line 2098.
    case 0x8004D083: return "XACT_E_TRANSACTIONCLOSED";
    // Original object relative source line 2099.
    case 0x8004D084: return "XACT_E_INVALIDLSN";
    // Original object relative source line 2100.
    case 0x8004D085: return "XACT_E_REPLAYREQUEST";
    // Original object relative source line 2102.
    case 0x0004D001: return "XACT_S_DEFECT";
    // Original object relative source line 2103.
    case 0x0004D002: return "XACT_S_READONLY";
    // Original object relative source line 2104.
    case 0x0004D003: return "XACT_S_SOMENORETAIN";
    // Original object relative source line 2105.
    case 0x0004D004: return "XACT_S_OKINFORM";
    // Original object relative source line 2106.
    case 0x0004D005: return "XACT_S_MADECHANGESCONTENT";
    // Original object relative source line 2107.
    case 0x0004D006: return "XACT_S_MADECHANGESINFORM";
    // Original object relative source line 2108.
    case 0x0004D007: return "XACT_S_ALLNORETAIN";
    // Original object relative source line 2109.
    case 0x0004D008: return "XACT_S_ABORTING";
    // Original object relative source line 2110.
    case 0x0004D009: return "XACT_S_SINGLEPHASE";
    // Original object relative source line 2111.
    case 0x0004D00A: return "XACT_S_LOCALLY_OK";
    // Original object relative source line 2113.
    case 0x8004E000: return "CONTEXT_E_FIRST";
    // Original object relative source line 2114.
    case 0x8004E02F: return "CONTEXT_E_LAST";
    // Original object relative source line 2115.
    case 0x0004E000: return "CONTEXT_S_FIRST";
    // Original object relative source line 2116.
    case 0x0004E02F: return "CONTEXT_S_LAST";
    // Original object relative source line 2117.
    case 0x8004E002: return "CONTEXT_E_ABORTED";
    // Original object relative source line 2118.
    case 0x8004E003: return "CONTEXT_E_ABORTING";
    // Original object relative source line 2119.
    case 0x8004E004: return "CONTEXT_E_NOCONTEXT";
    // Original object relative source line 2121.
    case 0x8004E006: return "CONTEXT_E_SYNCH_TIMEOUT";
    // Original object relative source line 2122.
    case 0x8004E007: return "CONTEXT_E_OLDREF";
    // Original object relative source line 2123.
    case 0x8004E00C: return "CONTEXT_E_ROLENOTFOUND";
    // Original object relative source line 2124.
    case 0x8004E00F: return "CONTEXT_E_TMNOTAVAILABLE";
    // Original object relative source line 2125.
    case 0x8004E021: return "CO_E_ACTIVATIONFAILED";
    // Original object relative source line 2126.
    case 0x8004E022: return "CO_E_ACTIVATIONFAILED_EVENTLOGGED";
    // Original object relative source line 2127.
    case 0x8004E023: return "CO_E_ACTIVATIONFAILED_CATALOGERROR";
    // Original object relative source line 2128.
    case 0x8004E024: return "CO_E_ACTIVATIONFAILED_TIMEOUT";
    // Original object relative source line 2129.
    case 0x8004E025: return "CO_E_INITIALIZATIONFAILED";
    // Original object relative source line 2130.
    case 0x8004E026: return "CONTEXT_E_NOJIT";
    // Original object relative source line 2131.
    case 0x8004E027: return "CONTEXT_E_NOTRANSACTION";
    // Original object relative source line 2132.
    case 0x8004E028: return "CO_E_THREADINGMODEL_CHANGED";
    // Original object relative source line 2133.
    case 0x8004E029: return "CO_E_NOIISINTRINSICS";
    // Original object relative source line 2134.
    case 0x8004E02A: return "CO_E_NOCOOKIES";
    // Original object relative source line 2135.
    case 0x8004E02B: return "CO_E_DBERROR";
    // Original object relative source line 2136.
    case 0x8004E02C: return "CO_E_NOTPOOLED";
    // Original object relative source line 2137.
    case 0x8004E02D: return "CO_E_NOTCONSTRUCTED";
    // Original object relative source line 2138.
    case 0x8004E02E: return "CO_E_NOSYNCHRONIZATION";
    // Original object relative source line 2140.
    case 0x00041300: return "SCHED_S_TASK_READY";
    // Original object relative source line 2141.
    case 0x00041301: return "SCHED_S_TASK_RUNNING";
    // Original object relative source line 2142.
    case 0x00041302: return "SCHED_S_TASK_DISABLED";
    // Original object relative source line 2143.
    case 0x00041303: return "SCHED_S_TASK_HAS_NOT_RUN";
    // Original object relative source line 2144.
    case 0x00041304: return "SCHED_S_TASK_NO_MORE_RUNS";
    // Original object relative source line 2145.
    case 0x00041305: return "SCHED_S_TASK_NOT_SCHEDULED";
    // Original object relative source line 2146.
    case 0x00041306: return "SCHED_S_TASK_TERMINATED";
    // Original object relative source line 2147.
    case 0x00041307: return "SCHED_S_TASK_NO_VALID_TRIGGERS";
    // Original object relative source line 2148.
    case 0x00041308: return "SCHED_S_EVENT_TRIGGER";
    // Original object relative source line 2149.
    case 0x80041309: return "SCHED_E_TRIGGER_NOT_FOUND";
    // Original object relative source line 2150.
    case 0x8004130A: return "SCHED_E_TASK_NOT_READY";
    // Original object relative source line 2151.
    case 0x8004130B: return "SCHED_E_TASK_NOT_RUNNING";
    // Original object relative source line 2152.
    case 0x8004130C: return "SCHED_E_SERVICE_NOT_INSTALLED";
    // Original object relative source line 2153.
    case 0x8004130D: return "SCHED_E_CANNOT_OPEN_TASK";
    // Original object relative source line 2154.
    case 0x8004130E: return "SCHED_E_INVALID_TASK";
    // Original object relative source line 2155.
    case 0x8004130F: return "SCHED_E_ACCOUNT_INFORMATION_NOT_SET";
    // Original object relative source line 2156.
    case 0x80041310: return "SCHED_E_ACCOUNT_NAME_NOT_FOUND";
    // Original object relative source line 2157.
    case 0x80041311: return "SCHED_E_ACCOUNT_DBASE_CORRUPT";
    // Original object relative source line 2158.
    case 0x80041312: return "SCHED_E_NO_SECURITY_SERVICES";
    // Original object relative source line 2159.
    case 0x80041313: return "SCHED_E_UNKNOWN_OBJECT_VERSION";
    // Original object relative source line 2160.
    case 0x80041314: return "SCHED_E_UNSUPPORTED_ACCOUNT_OPTION";
    // Original object relative source line 2161.
    case 0x80041315: return "SCHED_E_SERVICE_NOT_RUNNING";
    // Original object relative source line 2162.
    case 0x00080013: return "CO_S_MACHINENAMENOTFOUND";
    // Original object relative source line 2163.
    case 0x80030305: return "STG_E_STATUS_COPY_PROTECTION_FAILURE";
    // Original object relative source line 2164.
    case 0x80030306: return "STG_E_CSS_AUTHENTICATION_FAILURE";
    // Original object relative source line 2165.
    case 0x80030307: return "STG_E_CSS_KEY_NOT_PRESENT";
    // Original object relative source line 2166.
    case 0x80030308: return "STG_E_CSS_KEY_NOT_ESTABLISHED";
    // Original object relative source line 2167.
    case 0x80030309: return "STG_E_CSS_SCRAMBLED_SECTOR";
    // Original object relative source line 2168.
    case 0x8003030A: return "STG_E_CSS_REGION_MISMATCH";
    // Original object relative source line 2169.
    case 0x8003030B: return "STG_E_RESETS_EXHAUSTED";
    // Original object relative source line 2170.
    case 0x80010140: return "CO_E_CANCEL_DISABLED";
    // Original object relative source line 2171.
    case 0xC0090001: return "ERROR_AUDITING_DISABLED";
    // Original object relative source line 2172.
    case 0xC0090002: return "ERROR_ALL_SIDS_FILTERED";
    // Original object relative source line 2173.
    case 0x80090024: return "NTE_TEMPORARY_PROFILE";
    // Original object relative source line 2174.
    case 0x80090025: return "NTE_FIXEDPARAMETER";
    // Original object relative source line 2175.
    case 0x80090300: return "SEC_E_INSUFFICIENT_MEMORY";
    // Original object relative source line 2176.
    case 0x80090301: return "SEC_E_INVALID_HANDLE";
    // Original object relative source line 2177.
    case 0x80090302: return "SEC_E_UNSUPPORTED_FUNCTION";
    // Original object relative source line 2178.
    case 0x80090303: return "SEC_E_TARGET_UNKNOWN";
    // Original object relative source line 2179.
    case 0x80090304: return "SEC_E_INTERNAL_ERROR";
    // Original object relative source line 2180.
    case 0x80090305: return "SEC_E_SECPKG_NOT_FOUND";
    // Original object relative source line 2181.
    case 0x80090306: return "SEC_E_NOT_OWNER";
    // Original object relative source line 2182.
    case 0x80090307: return "SEC_E_CANNOT_INSTALL";
    // Original object relative source line 2183.
    case 0x80090308: return "SEC_E_INVALID_TOKEN";
    // Original object relative source line 2184.
    case 0x80090309: return "SEC_E_CANNOT_PACK";
    // Original object relative source line 2185.
    case 0x8009030A: return "SEC_E_QOP_NOT_SUPPORTED";
    // Original object relative source line 2186.
    case 0x8009030B: return "SEC_E_NO_IMPERSONATION";
    // Original object relative source line 2187.
    case 0x8009030C: return "SEC_E_LOGON_DENIED";
    // Original object relative source line 2188.
    case 0x8009030D: return "SEC_E_UNKNOWN_CREDENTIALS";
    // Original object relative source line 2189.
    case 0x8009030E: return "SEC_E_NO_CREDENTIALS";
    // Original object relative source line 2190.
    case 0x8009030F: return "SEC_E_MESSAGE_ALTERED";
    // Original object relative source line 2191.
    case 0x80090310: return "SEC_E_OUT_OF_SEQUENCE";
    // Original object relative source line 2192.
    case 0x80090311: return "SEC_E_NO_AUTHENTICATING_AUTHORITY";
    // Original object relative source line 2193.
    case 0x00090312: return "SEC_I_CONTINUE_NEEDED";
    // Original object relative source line 2194.
    case 0x00090313: return "SEC_I_COMPLETE_NEEDED";
    // Original object relative source line 2195.
    case 0x00090314: return "SEC_I_COMPLETE_AND_CONTINUE";
    // Original object relative source line 2196.
    case 0x00090315: return "SEC_I_LOCAL_LOGON";
    // Original object relative source line 2197.
    case 0x80090316: return "SEC_E_BAD_PKGID";
    // Original object relative source line 2198.
    case 0x80090317: return "SEC_E_CONTEXT_EXPIRED";
    // Original object relative source line 2199.
    case 0x00090317: return "SEC_I_CONTEXT_EXPIRED";
    // Original object relative source line 2200.
    case 0x80090318: return "SEC_E_INCOMPLETE_MESSAGE";
    // Original object relative source line 2201.
    case 0x80090320: return "SEC_E_INCOMPLETE_CREDENTIALS";
    // Original object relative source line 2202.
    case 0x80090321: return "SEC_E_BUFFER_TOO_SMALL";
    // Original object relative source line 2203.
    case 0x00090320: return "SEC_I_INCOMPLETE_CREDENTIALS";
    // Original object relative source line 2204.
    case 0x00090321: return "SEC_I_RENEGOTIATE";
    // Original object relative source line 2205.
    case 0x80090322: return "SEC_E_WRONG_PRINCIPAL";
    // Original object relative source line 2206.
    case 0x00090323: return "SEC_I_NO_LSA_CONTEXT";
    // Original object relative source line 2207.
    case 0x80090324: return "SEC_E_TIME_SKEW";
    // Original object relative source line 2208.
    case 0x80090325: return "SEC_E_UNTRUSTED_ROOT";
    // Original object relative source line 2209.
    case 0x80090326: return "SEC_E_ILLEGAL_MESSAGE";
    // Original object relative source line 2210.
    case 0x80090327: return "SEC_E_CERT_UNKNOWN";
    // Original object relative source line 2211.
    case 0x80090328: return "SEC_E_CERT_EXPIRED";
    // Original object relative source line 2212.
    case 0x80090329: return "SEC_E_ENCRYPT_FAILURE";
    // Original object relative source line 2213.
    case 0x80090330: return "SEC_E_DECRYPT_FAILURE";
    // Original object relative source line 2214.
    case 0x80090331: return "SEC_E_ALGORITHM_MISMATCH";
    // Original object relative source line 2215.
    case 0x80090332: return "SEC_E_SECURITY_QOS_FAILED";
    // Original object relative source line 2216.
    case 0x80090333: return "SEC_E_UNFINISHED_CONTEXT_DELETED";
    // Original object relative source line 2217.
    case 0x80090334: return "SEC_E_NO_TGT_REPLY";
    // Original object relative source line 2218.
    case 0x80090335: return "SEC_E_NO_IP_ADDRESSES";
    // Original object relative source line 2219.
    case 0x80090336: return "SEC_E_WRONG_CREDENTIAL_HANDLE";
    // Original object relative source line 2220.
    case 0x80090337: return "SEC_E_CRYPTO_SYSTEM_INVALID";
    // Original object relative source line 2221.
    case 0x80090338: return "SEC_E_MAX_REFERRALS_EXCEEDED";
    // Original object relative source line 2222.
    case 0x80090339: return "SEC_E_MUST_BE_KDC";
    // Original object relative source line 2223.
    case 0x8009033A: return "SEC_E_STRONG_CRYPTO_NOT_SUPPORTED";
    // Original object relative source line 2224.
    case 0x8009033B: return "SEC_E_TOO_MANY_PRINCIPALS";
    // Original object relative source line 2225.
    case 0x8009033C: return "SEC_E_NO_PA_DATA";
    // Original object relative source line 2226.
    case 0x8009033D: return "SEC_E_PKINIT_NAME_MISMATCH";
    // Original object relative source line 2227.
    case 0x8009033E: return "SEC_E_SMARTCARD_LOGON_REQUIRED";
    // Original object relative source line 2228.
    case 0x8009033F: return "SEC_E_SHUTDOWN_IN_PROGRESS";
    // Original object relative source line 2229.
    case 0x80090340: return "SEC_E_KDC_INVALID_REQUEST";
    // Original object relative source line 2230.
    case 0x80090341: return "SEC_E_KDC_UNABLE_TO_REFER";
    // Original object relative source line 2231.
    case 0x80090342: return "SEC_E_KDC_UNKNOWN_ETYPE";
    // Original object relative source line 2232.
    case 0x80090343: return "SEC_E_UNSUPPORTED_PREAUTH";
    // Original object relative source line 2233.
    case 0x80090345: return "SEC_E_DELEGATION_REQUIRED";
    // Original object relative source line 2234.
    case 0x80090346: return "SEC_E_BAD_BINDINGS";
    // Original object relative source line 2235.
    case 0x80090347: return "SEC_E_MULTIPLE_ACCOUNTS";
    // Original object relative source line 2236.
    case 0x80090348: return "SEC_E_NO_KERB_KEY";
    // Original object relative source line 2239.
    case 0x80090351: return "SEC_E_SMARTCARD_CERT_REVOKED";
    // Original object relative source line 2240.
    case 0x80090352: return "SEC_E_ISSUING_CA_UNTRUSTED";
    // Original object relative source line 2241.
    case 0x80090353: return "SEC_E_REVOCATION_OFFLINE_C";
    // Original object relative source line 2242.
    case 0x80090354: return "SEC_E_PKINIT_CLIENT_FAILURE";
    // Original object relative source line 2243.
    case 0x80090355: return "SEC_E_SMARTCARD_CERT_EXPIRED";
    // Original object relative source line 2246.
    case 0x00091012: return "CRYPT_I_NEW_PROTECTION_REQUIRED";
    // Original object relative source line 2247.
    case 0x8009202C: return "CRYPT_E_MISSING_PUBKEY_PARA";
    // Original object relative source line 2248.
    case 0x80093100: return "CRYPT_E_ASN1_ERROR";
    // Original object relative source line 2249.
    case 0x80093101: return "CRYPT_E_ASN1_INTERNAL";
    // Original object relative source line 2250.
    case 0x80093102: return "CRYPT_E_ASN1_EOD";
    // Original object relative source line 2251.
    case 0x80093103: return "CRYPT_E_ASN1_CORRUPT";
    // Original object relative source line 2252.
    case 0x80093104: return "CRYPT_E_ASN1_LARGE";
    // Original object relative source line 2253.
    case 0x80093105: return "CRYPT_E_ASN1_CONSTRAINT";
    // Original object relative source line 2254.
    case 0x80093106: return "CRYPT_E_ASN1_MEMORY";
    // Original object relative source line 2255.
    case 0x80093107: return "CRYPT_E_ASN1_OVERFLOW";
    // Original object relative source line 2256.
    case 0x80093108: return "CRYPT_E_ASN1_BADPDU";
    // Original object relative source line 2257.
    case 0x80093109: return "CRYPT_E_ASN1_BADARGS";
    // Original object relative source line 2258.
    case 0x8009310A: return "CRYPT_E_ASN1_BADREAL";
    // Original object relative source line 2259.
    case 0x8009310B: return "CRYPT_E_ASN1_BADTAG";
    // Original object relative source line 2260.
    case 0x8009310C: return "CRYPT_E_ASN1_CHOICE";
    // Original object relative source line 2261.
    case 0x8009310D: return "CRYPT_E_ASN1_RULE";
    // Original object relative source line 2262.
    case 0x8009310E: return "CRYPT_E_ASN1_UTF8";
    // Original object relative source line 2263.
    case 0x80093133: return "CRYPT_E_ASN1_PDU_TYPE";
    // Original object relative source line 2264.
    case 0x80093134: return "CRYPT_E_ASN1_NYI";
    // Original object relative source line 2265.
    case 0x80093201: return "CRYPT_E_ASN1_EXTENDED";
    // Original object relative source line 2266.
    case 0x80093202: return "CRYPT_E_ASN1_NOEOD";
    // Original object relative source line 2267.
    case 0x80094006: return "CERTSRV_E_SERVER_SUSPENDED";
    // Original object relative source line 2268.
    case 0x80094007: return "CERTSRV_E_ENCODING_LENGTH";
    // Original object relative source line 2269.
    case 0x80094008: return "CERTSRV_E_ROLECONFLICT";
    // Original object relative source line 2270.
    case 0x80094009: return "CERTSRV_E_RESTRICTEDOFFICER";
    // Original object relative source line 2271.
    case 0x8009400A: return "CERTSRV_E_KEY_ARCHIVAL_NOT_CONFIGURED";
    // Original object relative source line 2272.
    case 0x8009400B: return "CERTSRV_E_NO_VALID_KRA";
    // Original object relative source line 2273.
    case 0x8009400C: return "CERTSRV_E_BAD_REQUEST_KEY_ARCHIVAL";
    // Original object relative source line 2274.
    case 0x8009400D: return "CERTSRV_E_NO_CAADMIN_DEFINED";
    // Original object relative source line 2275.
    case 0x8009400E: return "CERTSRV_E_BAD_RENEWAL_CERT_ATTRIBUTE";
    // Original object relative source line 2276.
    case 0x8009400F: return "CERTSRV_E_NO_DB_SESSIONS";
    // Original object relative source line 2277.
    case 0x80094010: return "CERTSRV_E_ALIGNMENT_FAULT";
    // Original object relative source line 2278.
    case 0x80094011: return "CERTSRV_E_ENROLL_DENIED";
    // Original object relative source line 2279.
    case 0x80094012: return "CERTSRV_E_TEMPLATE_DENIED";
    // Original object relative source line 2281.
    case 0x80094802: return "CERTSRV_E_TEMPLATE_CONFLICT";
    // Original object relative source line 2282.
    case 0x80094803: return "CERTSRV_E_SUBJECT_ALT_NAME_REQUIRED";
    // Original object relative source line 2283.
    case 0x80094804: return "CERTSRV_E_ARCHIVED_KEY_REQUIRED";
    // Original object relative source line 2284.
    case 0x80094805: return "CERTSRV_E_SMIME_REQUIRED";
    // Original object relative source line 2285.
    case 0x80094806: return "CERTSRV_E_BAD_RENEWAL_SUBJECT";
    // Original object relative source line 2286.
    case 0x80094807: return "CERTSRV_E_BAD_TEMPLATE_VERSION";
    // Original object relative source line 2287.
    case 0x80094808: return "CERTSRV_E_TEMPLATE_POLICY_REQUIRED";
    // Original object relative source line 2288.
    case 0x80094809: return "CERTSRV_E_SIGNATURE_POLICY_REQUIRED";
    // Original object relative source line 2289.
    case 0x8009480A: return "CERTSRV_E_SIGNATURE_COUNT";
    // Original object relative source line 2290.
    case 0x8009480B: return "CERTSRV_E_SIGNATURE_REJECTED";
    // Original object relative source line 2291.
    case 0x8009480C: return "CERTSRV_E_ISSUANCE_POLICY_REQUIRED";
    // Original object relative source line 2292.
    case 0x8009480D: return "CERTSRV_E_SUBJECT_UPN_REQUIRED";
    // Original object relative source line 2293.
    case 0x8009480E: return "CERTSRV_E_SUBJECT_DIRECTORY_GUID_REQUIRED";
    // Original object relative source line 2294.
    case 0x8009480F: return "CERTSRV_E_SUBJECT_DNS_REQUIRED";
    // Original object relative source line 2295.
    case 0x80094810: return "CERTSRV_E_ARCHIVED_KEY_UNEXPECTED";
    // Original object relative source line 2296.
    case 0x80094811: return "CERTSRV_E_KEY_LENGTH";
    // Original object relative source line 2300.
    case 0x80095000: return "XENROLL_E_KEY_NOT_EXPORTABLE";
    // Original object relative source line 2301.
    case 0x80095001: return "XENROLL_E_CANNOT_ADD_ROOT_CERT";
    // Original object relative source line 2302.
    case 0x80095002: return "XENROLL_E_RESPONSE_KA_HASH_NOT_FOUND";
    // Original object relative source line 2303.
    case 0x80095003: return "XENROLL_E_RESPONSE_UNEXPECTED_KA_HASH";
    // Original object relative source line 2304.
    case 0x80095004: return "XENROLL_E_RESPONSE_KA_HASH_MISMATCH";
    // Original object relative source line 2305.
    case 0x80095005: return "XENROLL_E_KEYSPEC_SMIME_MISMATCH";
    // Original object relative source line 2306.
    case 0x80097001: return "MSSIPOTF_E_OUTOFMEMRANGE";
    // Original object relative source line 2307.
    case 0x80097002: return "MSSIPOTF_E_CANTGETOBJECT";
    // Original object relative source line 2308.
    case 0x80097003: return "MSSIPOTF_E_NOHEADTABLE";
    // Original object relative source line 2309.
    case 0x80097004: return "MSSIPOTF_E_BAD_MAGICNUMBER";
    // Original object relative source line 2310.
    case 0x80097005: return "MSSIPOTF_E_BAD_OFFSET_TABLE";
    // Original object relative source line 2311.
    case 0x80097006: return "MSSIPOTF_E_TABLE_TAGORDER";
    // Original object relative source line 2312.
    case 0x80097007: return "MSSIPOTF_E_TABLE_LONGWORD";
    // Original object relative source line 2313.
    case 0x80097008: return "MSSIPOTF_E_BAD_FIRST_TABLE_PLACEMENT";
    // Original object relative source line 2314.
    case 0x80097009: return "MSSIPOTF_E_TABLES_OVERLAP";
    // Original object relative source line 2315.
    case 0x8009700A: return "MSSIPOTF_E_TABLE_PADBYTES";
    // Original object relative source line 2316.
    case 0x8009700B: return "MSSIPOTF_E_FILETOOSMALL";
    // Original object relative source line 2317.
    case 0x8009700C: return "MSSIPOTF_E_TABLE_CHECKSUM";
    // Original object relative source line 2318.
    case 0x8009700D: return "MSSIPOTF_E_FILE_CHECKSUM";
    // Original object relative source line 2319.
    case 0x80097010: return "MSSIPOTF_E_FAILED_POLICY";
    // Original object relative source line 2320.
    case 0x80097011: return "MSSIPOTF_E_FAILED_HINTS_CHECK";
    // Original object relative source line 2321.
    case 0x80097012: return "MSSIPOTF_E_NOT_OPENTYPE";
    // Original object relative source line 2322.
    case 0x80097013: return "MSSIPOTF_E_FILE";
    // Original object relative source line 2323.
    case 0x80097014: return "MSSIPOTF_E_CRYPT";
    // Original object relative source line 2324.
    case 0x80097015: return "MSSIPOTF_E_BADVERSION";
    // Original object relative source line 2325.
    case 0x80097016: return "MSSIPOTF_E_DSIG_STRUCTURE";
    // Original object relative source line 2326.
    case 0x80097017: return "MSSIPOTF_E_PCONST_CHECK";
    // Original object relative source line 2327.
    case 0x80097018: return "MSSIPOTF_E_STRUCTURE";
    // Original object relative source line 2328.
    case 0x800B0111: return "TRUST_E_EXPLICIT_DISTRUST";
    // Original object relative source line 2329.
    case 0x800B0112: return "CERT_E_UNTRUSTEDCA";
    // Original object relative source line 2330.
    case 0x800B0113: return "CERT_E_INVALID_POLICY";
    // Original object relative source line 2331.
    case 0x800B0114: return "CERT_E_INVALID_NAME";
    // Original object relative source line 2332.
    case 0x800F0231: return "SPAPI_E_NOT_DISABLEABLE";
    // Original object relative source line 2333.
    case 0x800F0232: return "SPAPI_E_CANT_REMOVE_DEVINST";
    // Original object relative source line 2334.
    case 0x800F0233: return "SPAPI_E_INVALID_TARGET";
    // Original object relative source line 2335.
    case 0x800F0234: return "SPAPI_E_DRIVER_NONNATIVE";
    // Original object relative source line 2336.
    case 0x800F0235: return "SPAPI_E_IN_WOW64";
    // Original object relative source line 2337.
    case 0x800F0236: return "SPAPI_E_SET_SYSTEM_RESTORE_POINT";
    // Original object relative source line 2338.
    case 0x800F0237: return "SPAPI_E_INCORRECTLY_COPIED_INF";
    // Original object relative source line 2339.
    case 0x800F0238: return "SPAPI_E_SCE_DISABLED";
    // Original object relative source line 2340.
    case 0x80100030: return "SCARD_E_NO_KEY_CONTAINER";
    // Original object relative source line 2341.
    case 0x8010006F: return "SCARD_W_CARD_NOT_AUTHENTICATED";
    // Original object relative source line 2342.
    case 0x80110401: return "COMADMIN_E_OBJECTERRORS";
    // Original object relative source line 2343.
    case 0x80110402: return "COMADMIN_E_OBJECTINVALID";
    // Original object relative source line 2344.
    case 0x80110403: return "COMADMIN_E_KEYMISSING";
    // Original object relative source line 2345.
    case 0x80110404: return "COMADMIN_E_ALREADYINSTALLED";
    // Original object relative source line 2346.
    case 0x80110407: return "COMADMIN_E_APP_FILE_WRITEFAIL";
    // Original object relative source line 2347.
    case 0x80110408: return "COMADMIN_E_APP_FILE_READFAIL";
    // Original object relative source line 2348.
    case 0x80110409: return "COMADMIN_E_APP_FILE_VERSION";
    // Original object relative source line 2349.
    case 0x8011040A: return "COMADMIN_E_BADPATH";
    // Original object relative source line 2350.
    case 0x8011040B: return "COMADMIN_E_APPLICATIONEXISTS";
    // Original object relative source line 2351.
    case 0x8011040C: return "COMADMIN_E_ROLEEXISTS";
    // Original object relative source line 2352.
    case 0x8011040D: return "COMADMIN_E_CANTCOPYFILE";
    // Original object relative source line 2353.
    case 0x8011040F: return "COMADMIN_E_NOUSER";
    // Original object relative source line 2354.
    case 0x80110410: return "COMADMIN_E_INVALIDUSERIDS";
    // Original object relative source line 2355.
    case 0x80110411: return "COMADMIN_E_NOREGISTRYCLSID";
    // Original object relative source line 2356.
    case 0x80110412: return "COMADMIN_E_BADREGISTRYPROGID";
    // Original object relative source line 2357.
    case 0x80110413: return "COMADMIN_E_AUTHENTICATIONLEVEL";
    // Original object relative source line 2358.
    case 0x80110414: return "COMADMIN_E_USERPASSWDNOTVALID";
    // Original object relative source line 2359.
    case 0x80110418: return "COMADMIN_E_CLSIDORIIDMISMATCH";
    // Original object relative source line 2360.
    case 0x80110419: return "COMADMIN_E_REMOTEINTERFACE";
    // Original object relative source line 2361.
    case 0x8011041A: return "COMADMIN_E_DLLREGISTERSERVER";
    // Original object relative source line 2362.
    case 0x8011041B: return "COMADMIN_E_NOSERVERSHARE";
    // Original object relative source line 2363.
    case 0x8011041D: return "COMADMIN_E_DLLLOADFAILED";
    // Original object relative source line 2364.
    case 0x8011041E: return "COMADMIN_E_BADREGISTRYLIBID";
    // Original object relative source line 2365.
    case 0x8011041F: return "COMADMIN_E_APPDIRNOTFOUND";
    // Original object relative source line 2366.
    case 0x80110423: return "COMADMIN_E_REGISTRARFAILED";
    // Original object relative source line 2367.
    case 0x80110424: return "COMADMIN_E_COMPFILE_DOESNOTEXIST";
    // Original object relative source line 2368.
    case 0x80110425: return "COMADMIN_E_COMPFILE_LOADDLLFAIL";
    // Original object relative source line 2369.
    case 0x80110426: return "COMADMIN_E_COMPFILE_GETCLASSOBJ";
    // Original object relative source line 2370.
    case 0x80110427: return "COMADMIN_E_COMPFILE_CLASSNOTAVAIL";
    // Original object relative source line 2371.
    case 0x80110428: return "COMADMIN_E_COMPFILE_BADTLB";
    // Original object relative source line 2372.
    case 0x80110429: return "COMADMIN_E_COMPFILE_NOTINSTALLABLE";
    // Original object relative source line 2373.
    case 0x8011042A: return "COMADMIN_E_NOTCHANGEABLE";
    // Original object relative source line 2374.
    case 0x8011042B: return "COMADMIN_E_NOTDELETEABLE";
    // Original object relative source line 2375.
    case 0x8011042C: return "COMADMIN_E_SESSION";
    // Original object relative source line 2376.
    case 0x8011042D: return "COMADMIN_E_COMP_MOVE_LOCKED";
    // Original object relative source line 2377.
    case 0x8011042E: return "COMADMIN_E_COMP_MOVE_BAD_DEST";
    // Original object relative source line 2378.
    case 0x80110430: return "COMADMIN_E_REGISTERTLB";
    // Original object relative source line 2379.
    case 0x80110433: return "COMADMIN_E_SYSTEMAPP";
    // Original object relative source line 2380.
    case 0x80110434: return "COMADMIN_E_COMPFILE_NOREGISTRAR";
    // Original object relative source line 2381.
    case 0x80110435: return "COMADMIN_E_COREQCOMPINSTALLED";
    // Original object relative source line 2382.
    case 0x80110436: return "COMADMIN_E_SERVICENOTINSTALLED";
    // Original object relative source line 2383.
    case 0x80110437: return "COMADMIN_E_PROPERTYSAVEFAILED";
    // Original object relative source line 2384.
    case 0x80110438: return "COMADMIN_E_OBJECTEXISTS";
    // Original object relative source line 2385.
    case 0x80110439: return "COMADMIN_E_COMPONENTEXISTS";
    // Original object relative source line 2386.
    case 0x8011043B: return "COMADMIN_E_REGFILE_CORRUPT";
    // Original object relative source line 2387.
    case 0x8011043C: return "COMADMIN_E_PROPERTY_OVERFLOW";
    // Original object relative source line 2388.
    case 0x8011043E: return "COMADMIN_E_NOTINREGISTRY";
    // Original object relative source line 2389.
    case 0x8011043F: return "COMADMIN_E_OBJECTNOTPOOLABLE";
    // Original object relative source line 2390.
    case 0x80110446: return "COMADMIN_E_APPLID_MATCHES_CLSID";
    // Original object relative source line 2391.
    case 0x80110447: return "COMADMIN_E_ROLE_DOES_NOT_EXIST";
    // Original object relative source line 2392.
    case 0x80110448: return "COMADMIN_E_START_APP_NEEDS_COMPONENTS";
    // Original object relative source line 2393.
    case 0x80110449: return "COMADMIN_E_REQUIRES_DIFFERENT_PLATFORM";
    // Original object relative source line 2394.
    case 0x8011044A: return "COMADMIN_E_CAN_NOT_EXPORT_APP_PROXY";
    // Original object relative source line 2395.
    case 0x8011044B: return "COMADMIN_E_CAN_NOT_START_APP";
    // Original object relative source line 2396.
    case 0x8011044C: return "COMADMIN_E_CAN_NOT_EXPORT_SYS_APP";
    // Original object relative source line 2397.
    case 0x8011044D: return "COMADMIN_E_CANT_SUBSCRIBE_TO_COMPONENT";
    // Original object relative source line 2398.
    case 0x8011044E: return "COMADMIN_E_EVENTCLASS_CANT_BE_SUBSCRIBER";
    // Original object relative source line 2399.
    case 0x8011044F: return "COMADMIN_E_LIB_APP_PROXY_INCOMPATIBLE";
    // Original object relative source line 2400.
    case 0x80110450: return "COMADMIN_E_BASE_PARTITION_ONLY";
    // Original object relative source line 2401.
    case 0x80110451: return "COMADMIN_E_START_APP_DISABLED";
    // Original object relative source line 2402.
    case 0x80110457: return "COMADMIN_E_CAT_DUPLICATE_PARTITION_NAME";
    // Original object relative source line 2403.
    case 0x80110458: return "COMADMIN_E_CAT_INVALID_PARTITION_NAME";
    // Original object relative source line 2404.
    case 0x80110459: return "COMADMIN_E_CAT_PARTITION_IN_USE";
    // Original object relative source line 2405.
    case 0x8011045A: return "COMADMIN_E_FILE_PARTITION_DUPLICATE_FILES";
    // Original object relative source line 2406.
    case 0x8011045B: return "COMADMIN_E_CAT_IMPORTED_COMPONENTS_NOT_ALLOWED";
    // Original object relative source line 2407.
    case 0x8011045C: return "COMADMIN_E_AMBIGUOUS_APPLICATION_NAME";
    // Original object relative source line 2408.
    case 0x8011045D: return "COMADMIN_E_AMBIGUOUS_PARTITION_NAME";
    // Original object relative source line 2409.
    case 0x80110472: return "COMADMIN_E_REGDB_NOTINITIALIZED";
    // Original object relative source line 2410.
    case 0x80110473: return "COMADMIN_E_REGDB_NOTOPEN";
    // Original object relative source line 2411.
    case 0x80110474: return "COMADMIN_E_REGDB_SYSTEMERR";
    // Original object relative source line 2412.
    case 0x80110475: return "COMADMIN_E_REGDB_ALREADYRUNNING";
    // Original object relative source line 2413.
    case 0x80110480: return "COMADMIN_E_MIG_VERSIONNOTSUPPORTED";
    // Original object relative source line 2414.
    case 0x80110481: return "COMADMIN_E_MIG_SCHEMANOTFOUND";
    // Original object relative source line 2415.
    case 0x80110482: return "COMADMIN_E_CAT_BITNESSMISMATCH";
    // Original object relative source line 2416.
    case 0x80110483: return "COMADMIN_E_CAT_UNACCEPTABLEBITNESS";
    // Original object relative source line 2417.
    case 0x80110484: return "COMADMIN_E_CAT_WRONGAPPBITNESS";
    // Original object relative source line 2418.
    case 0x80110485: return "COMADMIN_E_CAT_PAUSE_RESUME_NOT_SUPPORTED";
    // Original object relative source line 2419.
    case 0x80110486: return "COMADMIN_E_CAT_SERVERFAULT";
    // Original object relative source line 2420.
    case 0x80110600: return "COMQC_E_APPLICATION_NOT_QUEUED";
    // Original object relative source line 2421.
    case 0x80110601: return "COMQC_E_NO_QUEUEABLE_INTERFACES";
    // Original object relative source line 2422.
    case 0x80110602: return "COMQC_E_QUEUING_SERVICE_NOT_AVAILABLE";
    // Original object relative source line 2423.
    case 0x80110603: return "COMQC_E_NO_IPERSISTSTREAM";
    // Original object relative source line 2424.
    case 0x80110604: return "COMQC_E_BAD_MESSAGE";
    // Original object relative source line 2425.
    case 0x80110605: return "COMQC_E_UNAUTHENTICATED";
    // Original object relative source line 2426.
    case 0x80110606: return "COMQC_E_UNTRUSTED_ENQUEUER";
    // Original object relative source line 2427.
    case 0x80110701: return "MSDTC_E_DUPLICATE_RESOURCE";
    // Original object relative source line 2428.
    case 0x80110808: return "COMADMIN_E_OBJECT_PARENT_MISSING";
    // Original object relative source line 2429.
    case 0x80110809: return "COMADMIN_E_OBJECT_DOES_NOT_EXIST";
    // Original object relative source line 2430.
    case 0x8011080A: return "COMADMIN_E_APP_NOT_RUNNING";
    // Original object relative source line 2431.
    case 0x8011080B: return "COMADMIN_E_INVALID_PARTITION";
    // Original object relative source line 2432.
    case 0x8011080D: return "COMADMIN_E_SVCAPP_NOT_POOLABLE_OR_RECYCLABLE";
    // Original object relative source line 2433.
    case 0x8011080E: return "COMADMIN_E_USER_IN_SET";
    // Original object relative source line 2434.
    case 0x8011080F: return "COMADMIN_E_CANTRECYCLELIBRARYAPPS";
    // Original object relative source line 2435.
    case 0x80110811: return "COMADMIN_E_CANTRECYCLESERVICEAPPS";
    // Original object relative source line 2436.
    case 0x80110812: return "COMADMIN_E_PROCESSALREADYRECYCLED";
    // Original object relative source line 2437.
    case 0x80110813: return "COMADMIN_E_PAUSEDPROCESSMAYNOTBERECYCLED";
    // Original object relative source line 2438.
    case 0x80110814: return "COMADMIN_E_CANTMAKEINPROCSERVICE";
    // Original object relative source line 2439.
    case 0x80110815: return "COMADMIN_E_PROGIDINUSEBYCLSID";
    // Original object relative source line 2440.
    case 0x80110816: return "COMADMIN_E_DEFAULT_PARTITION_NOT_IN_SET";
    // Original object relative source line 2441.
    case 0x80110817: return "COMADMIN_E_RECYCLEDPROCESSMAYNOTBEPAUSED";
    // Original object relative source line 2442.
    case 0x80110818: return "COMADMIN_E_PARTITION_ACCESSDENIED";
    // Original object relative source line 2443.
    case 0x80110819: return "COMADMIN_E_PARTITION_MSI_ONLY";
    // Original object relative source line 2444.
    case 0x8011081A: return "COMADMIN_E_LEGACYCOMPS_NOT_ALLOWED_IN_1_0_FORMAT";
    // Original object relative source line 2445.
    case 0x8011081B: return "COMADMIN_E_LEGACYCOMPS_NOT_ALLOWED_IN_NONBASE_PARTITIONS";
    // Original object relative source line 2446.
    case 0x8011081C: return "COMADMIN_E_COMP_MOVE_SOURCE";
    // Original object relative source line 2447.
    case 0x8011081D: return "COMADMIN_E_COMP_MOVE_DEST";
    // Original object relative source line 2448.
    case 0x8011081E: return "COMADMIN_E_COMP_MOVE_PRIVATE";
    // Original object relative source line 2449.
    case 0x8011081F: return "COMADMIN_E_BASEPARTITION_REQUIRED_IN_SET";
    // Original object relative source line 2450.
    case 0x80110820: return "COMADMIN_E_CANNOT_ALIAS_EVENTCLASS";
    // Original object relative source line 2451.
    case 0x80110821: return "COMADMIN_E_PRIVATE_ACCESSDENIED";
    // Original object relative source line 2452.
    case 0x80110822: return "COMADMIN_E_SAFERINVALID";
    // Original object relative source line 2453.
    case 0x80110823: return "COMADMIN_E_REGISTRY_ACCESSDENIED";
    // Original object relative source line 2457.
    case 0x0000012E:
    case 0x8007012E: return "ERROR_DISK_TOO_FRAGMENTED";
    // Original object relative source line 2458.
    case 0x0000012F:
    case 0x8007012F: return "ERROR_DELETE_PENDING";
    // Original object relative source line 2460.
    case 0x0000043C:
    case 0x8007043C: return "ERROR_NOT_SAFEBOOT_SERVICE";
    // Original object relative source line 2461.
    case 0x0000049D:
    case 0x8007049D: return "ERROR_JOURNAL_ENTRY_DELETED";
    // Original object relative source line 2462.
    case 0x000004E3:
    case 0x800704E3: return "ERROR_ONLY_IF_CONNECTED";
    // Original object relative source line 2463.
    case 0x000004E4:
    case 0x800704E4: return "ERROR_OVERRIDE_NOCHANGES";
    // Original object relative source line 2464.
    case 0x000004E5:
    case 0x800704E5: return "ERROR_BAD_USER_PROFILE";
    // Original object relative source line 2465.
    case 0x000004E6:
    case 0x800704E6: return "ERROR_NOT_SUPPORTED_ON_SBS";
    // Original object relative source line 2466.
    case 0x000004E7:
    case 0x800704E7: return "ERROR_SERVER_SHUTDOWN_IN_PROGRESS";
    // Original object relative source line 2467.
    case 0x000004E8:
    case 0x800704E8: return "ERROR_HOST_DOWN";
    // Original object relative source line 2468.
    case 0x000004E9:
    case 0x800704E9: return "ERROR_NON_ACCOUNT_SID";
    // Original object relative source line 2469.
    case 0x000004EA:
    case 0x800704EA: return "ERROR_NON_DOMAIN_SID";
    // Original object relative source line 2470.
    case 0x000004EB:
    case 0x800704EB: return "ERROR_APPHELP_BLOCK";
    // Original object relative source line 2471.
    case 0x000004EC:
    case 0x800704EC: return "ERROR_ACCESS_DISABLED_BY_POLICY";
    // Original object relative source line 2472.
    case 0x000004ED:
    case 0x800704ED: return "ERROR_REG_NAT_CONSUMPTION";
    // Original object relative source line 2473.
    case 0x000004EE:
    case 0x800704EE: return "ERROR_CSCSHARE_OFFLINE";
    // Original object relative source line 2474.
    case 0x000004EF:
    case 0x800704EF: return "ERROR_PKINIT_FAILURE";
    // Original object relative source line 2475.
    case 0x000004F0:
    case 0x800704F0: return "ERROR_SMARTCARD_SUBSYSTEM_FAILURE";
    // Original object relative source line 2476.
    case 0x000004F1:
    case 0x800704F1: return "ERROR_DOWNGRADE_DETECTED";
    // Original object relative source line 2477.
    case 0x000004F7:
    case 0x800704F7: return "ERROR_MACHINE_LOCKED";
    // Original object relative source line 2478.
    case 0x000004F9:
    case 0x800704F9: return "ERROR_CALLBACK_SUPPLIED_INVALID_DATA";
    // Original object relative source line 2479.
    case 0x000004FA:
    case 0x800704FA: return "ERROR_SYNC_FOREGROUND_REFRESH_REQUIRED";
    // Original object relative source line 2480.
    case 0x000004FB:
    case 0x800704FB: return "ERROR_DRIVER_BLOCKED";
    // Original object relative source line 2481.
    case 0x000004FC:
    case 0x800704FC: return "ERROR_INVALID_IMPORT_OF_NON_DLL";
    // Original object relative source line 2491.
    case 0x00000577:
    case 0x80070577: return "ERROR_CURRENT_DOMAIN_NOT_ALLOWED";
    // Original object relative source line 2492.
    case 0x00000641:
    case 0x80070641: return "ERROR_INSTALL_SERVICE_FAILURE";
    // Original object relative source line 2493.
    case 0x0000064D:
    case 0x8007064D: return "ERROR_INSTALL_PACKAGE_VERSION";
    // Original object relative source line 2494.
    case 0x00000652:
    case 0x80070652: return "ERROR_INSTALL_ALREADY_RUNNING";
    // Original object relative source line 2495.
    case 0x00000653:
    case 0x80070653: return "ERROR_INSTALL_PACKAGE_OPEN_FAILED";
    // Original object relative source line 2496.
    case 0x00000654:
    case 0x80070654: return "ERROR_INSTALL_PACKAGE_INVALID";
    // Original object relative source line 2497.
    case 0x00000655:
    case 0x80070655: return "ERROR_INSTALL_UI_FAILURE";
    // Original object relative source line 2498.
    case 0x00000656:
    case 0x80070656: return "ERROR_INSTALL_LOG_FAILURE";
    // Original object relative source line 2499.
    case 0x00000657:
    case 0x80070657: return "ERROR_INSTALL_LANGUAGE_UNSUPPORTED";
    // Original object relative source line 2500.
    case 0x00000658:
    case 0x80070658: return "ERROR_INSTALL_TRANSFORM_FAILURE";
    // Original object relative source line 2501.
    case 0x00000659:
    case 0x80070659: return "ERROR_INSTALL_PACKAGE_REJECTED";
    // Original object relative source line 2502.
    case 0x0000065A:
    case 0x8007065A: return "ERROR_FUNCTION_NOT_CALLED";
    // Original object relative source line 2503.
    case 0x0000065B:
    case 0x8007065B: return "ERROR_FUNCTION_FAILED";
    // Original object relative source line 2504.
    case 0x0000065C:
    case 0x8007065C: return "ERROR_INVALID_TABLE";
    // Original object relative source line 2505.
    case 0x0000065D:
    case 0x8007065D: return "ERROR_DATATYPE_MISMATCH";
    // Original object relative source line 2506.
    case 0x0000065E:
    case 0x8007065E: return "ERROR_UNSUPPORTED_TYPE";
    // Original object relative source line 2507.
    case 0x0000065F:
    case 0x8007065F: return "ERROR_CREATE_FAILED";
    // Original object relative source line 2508.
    case 0x00000660:
    case 0x80070660: return "ERROR_INSTALL_TEMP_UNWRITABLE";
    // Original object relative source line 2509.
    case 0x00000661:
    case 0x80070661: return "ERROR_INSTALL_PLATFORM_UNSUPPORTED";
    // Original object relative source line 2510.
    case 0x00000662:
    case 0x80070662: return "ERROR_INSTALL_NOTUSED";
    // Original object relative source line 2511.
    case 0x00000663:
    case 0x80070663: return "ERROR_PATCH_PACKAGE_OPEN_FAILED";
    // Original object relative source line 2512.
    case 0x00000664:
    case 0x80070664: return "ERROR_PATCH_PACKAGE_INVALID";
    // Original object relative source line 2513.
    case 0x00000665:
    case 0x80070665: return "ERROR_PATCH_PACKAGE_UNSUPPORTED";
    // Original object relative source line 2514.
    case 0x00000666:
    case 0x80070666: return "ERROR_PRODUCT_VERSION";
    // Original object relative source line 2515.
    case 0x00000667:
    case 0x80070667: return "ERROR_INVALID_COMMAND_LINE";
    // Original object relative source line 2516.
    case 0x00000668:
    case 0x80070668: return "ERROR_INSTALL_REMOTE_DISALLOWED";
    // Original object relative source line 2517.
    case 0x00000669:
    case 0x80070669: return "ERROR_SUCCESS_REBOOT_INITIATED";
    // Original object relative source line 2518.
    case 0x0000066A:
    case 0x8007066A: return "ERROR_PATCH_TARGET_NOT_FOUND";
    // Original object relative source line 2519.
    case 0x0000066B:
    case 0x8007066B: return "ERROR_PATCH_PACKAGE_REJECTED";
    // Original object relative source line 2520.
    case 0x0000066C:
    case 0x8007066C: return "ERROR_INSTALL_TRANSFORM_REJECTED";
    // Original object relative source line 2522.
    case 0x00000782:
    case 0x80070782: return "RPC_S_ENTRY_TYPE_MISMATCH";
    // Original object relative source line 2523.
    case 0x00000783:
    case 0x80070783: return "RPC_S_NOT_ALL_OBJS_EXPORTED";
    // Original object relative source line 2524.
    case 0x00000784:
    case 0x80070784: return "RPC_S_INTERFACE_NOT_EXPORTED";
    // Original object relative source line 2525.
    case 0x00000785:
    case 0x80070785: return "RPC_S_PROFILE_NOT_ADDED";
    // Original object relative source line 2526.
    case 0x00000786:
    case 0x80070786: return "RPC_S_PRF_ELT_NOT_ADDED";
    // Original object relative source line 2527.
    case 0x00000787:
    case 0x80070787: return "RPC_S_PRF_ELT_NOT_REMOVED";
    // Original object relative source line 2528.
    case 0x00000788:
    case 0x80070788: return "RPC_S_GRP_ELT_NOT_ADDED";
    // Original object relative source line 2529.
    case 0x00000789:
    case 0x80070789: return "RPC_S_GRP_ELT_NOT_REMOVED";
    // Original object relative source line 2530.
    case 0x0000078A:
    case 0x8007078A: return "ERROR_KM_DRIVER_BLOCKED";
    // Original object relative source line 2531.
    case 0x0000078B:
    case 0x8007078B: return "ERROR_CONTEXT_EXPIRED";
    // Original object relative source line 2535.
    case 0x0000083D:
    case 0x8007083D: return "ERROR_CONNECTED_OTHER_PASSWORD_DEFAULT";
    // Original object relative source line 2536.
    case 0x00000BC5:
    case 0x80070BC5: return "ERROR_PRINTER_DRIVER_WARNED";
    // Original object relative source line 2537.
    case 0x00000BC6:
    case 0x80070BC6: return "ERROR_PRINTER_DRIVER_BLOCKED";
    // Original object relative source line 2538.
    case 0x000010F1:
    case 0x800710F1: return "ERROR_VOLUME_CONTAINS_SYS_FILES";
    // Original object relative source line 2539.
    case 0x000010F2:
    case 0x800710F2: return "ERROR_INDIGENOUS_TYPE";
    // Original object relative source line 2540.
    case 0x000010F3:
    case 0x800710F3: return "ERROR_NO_SUPPORTING_DRIVES";
    // Original object relative source line 2541.
    case 0x000010F4:
    case 0x800710F4: return "ERROR_CLEANER_CARTRIDGE_INSTALLED";
    // Original object relative source line 2542.
    case 0x00001129:
    case 0x80071129: return "ERROR_REPARSE_TAG_INVALID";
    // Original object relative source line 2543.
    case 0x0000112A:
    case 0x8007112A: return "ERROR_REPARSE_TAG_MISMATCH";
    // Original object relative source line 2544.
    case 0x00001194:
    case 0x80071194: return "ERROR_VOLUME_NOT_SIS_ENABLED";
    // Original object relative source line 2545.
    case 0x000013AA:
    case 0x800713AA: return "ERROR_QUORUM_OWNER_ALIVE";
    // Original object relative source line 2546.
    case 0x000013AB:
    case 0x800713AB: return "ERROR_NETWORK_NOT_AVAILABLE";
    // Original object relative source line 2547.
    case 0x000013AC:
    case 0x800713AC: return "ERROR_NODE_NOT_AVAILABLE";
    // Original object relative source line 2548.
    case 0x000013AD:
    case 0x800713AD: return "ERROR_ALL_NODES_NOT_AVAILABLE";
    // Original object relative source line 2549.
    case 0x000013AE:
    case 0x800713AE: return "ERROR_RESOURCE_FAILED";
    // Original object relative source line 2550.
    case 0x000013AF:
    case 0x800713AF: return "ERROR_CLUSTER_INVALID_NODE";
    // Original object relative source line 2551.
    case 0x000013B0:
    case 0x800713B0: return "ERROR_CLUSTER_NODE_EXISTS";
    // Original object relative source line 2552.
    case 0x000013B1:
    case 0x800713B1: return "ERROR_CLUSTER_JOIN_IN_PROGRESS";
    // Original object relative source line 2553.
    case 0x000013B2:
    case 0x800713B2: return "ERROR_CLUSTER_NODE_NOT_FOUND";
    // Original object relative source line 2554.
    case 0x000013B3:
    case 0x800713B3: return "ERROR_CLUSTER_LOCAL_NODE_NOT_FOUND";
    // Original object relative source line 2555.
    case 0x000013B4:
    case 0x800713B4: return "ERROR_CLUSTER_NETWORK_EXISTS";
    // Original object relative source line 2556.
    case 0x000013B5:
    case 0x800713B5: return "ERROR_CLUSTER_NETWORK_NOT_FOUND";
    // Original object relative source line 2557.
    case 0x000013B6:
    case 0x800713B6: return "ERROR_CLUSTER_NETINTERFACE_EXISTS";
    // Original object relative source line 2558.
    case 0x000013B7:
    case 0x800713B7: return "ERROR_CLUSTER_NETINTERFACE_NOT_FOUND";
    // Original object relative source line 2559.
    case 0x000013B8:
    case 0x800713B8: return "ERROR_CLUSTER_INVALID_REQUEST";
    // Original object relative source line 2560.
    case 0x000013B9:
    case 0x800713B9: return "ERROR_CLUSTER_INVALID_NETWORK_PROVIDER";
    // Original object relative source line 2561.
    case 0x000013BA:
    case 0x800713BA: return "ERROR_CLUSTER_NODE_DOWN";
    // Original object relative source line 2562.
    case 0x000013BB:
    case 0x800713BB: return "ERROR_CLUSTER_NODE_UNREACHABLE";
    // Original object relative source line 2563.
    case 0x000013BC:
    case 0x800713BC: return "ERROR_CLUSTER_NODE_NOT_MEMBER";
    // Original object relative source line 2564.
    case 0x000013BD:
    case 0x800713BD: return "ERROR_CLUSTER_JOIN_NOT_IN_PROGRESS";
    // Original object relative source line 2565.
    case 0x000013BE:
    case 0x800713BE: return "ERROR_CLUSTER_INVALID_NETWORK";
    // Original object relative source line 2566.
    case 0x000013C0:
    case 0x800713C0: return "ERROR_CLUSTER_NODE_UP";
    // Original object relative source line 2567.
    case 0x000013C1:
    case 0x800713C1: return "ERROR_CLUSTER_IPADDR_IN_USE";
    // Original object relative source line 2568.
    case 0x000013C2:
    case 0x800713C2: return "ERROR_CLUSTER_NODE_NOT_PAUSED";
    // Original object relative source line 2569.
    case 0x000013C3:
    case 0x800713C3: return "ERROR_CLUSTER_NO_SECURITY_CONTEXT";
    // Original object relative source line 2570.
    case 0x000013C4:
    case 0x800713C4: return "ERROR_CLUSTER_NETWORK_NOT_INTERNAL";
    // Original object relative source line 2571.
    case 0x000013C5:
    case 0x800713C5: return "ERROR_CLUSTER_NODE_ALREADY_UP";
    // Original object relative source line 2572.
    case 0x000013C6:
    case 0x800713C6: return "ERROR_CLUSTER_NODE_ALREADY_DOWN";
    // Original object relative source line 2573.
    case 0x000013C7:
    case 0x800713C7: return "ERROR_CLUSTER_NETWORK_ALREADY_ONLINE";
    // Original object relative source line 2574.
    case 0x000013C8:
    case 0x800713C8: return "ERROR_CLUSTER_NETWORK_ALREADY_OFFLINE";
    // Original object relative source line 2575.
    case 0x000013C9:
    case 0x800713C9: return "ERROR_CLUSTER_NODE_ALREADY_MEMBER";
    // Original object relative source line 2576.
    case 0x000013CA:
    case 0x800713CA: return "ERROR_CLUSTER_LAST_INTERNAL_NETWORK";
    // Original object relative source line 2577.
    case 0x000013CB:
    case 0x800713CB: return "ERROR_CLUSTER_NETWORK_HAS_DEPENDENTS";
    // Original object relative source line 2578.
    case 0x000013CC:
    case 0x800713CC: return "ERROR_INVALID_OPERATION_ON_QUORUM";
    // Original object relative source line 2579.
    case 0x000013CD:
    case 0x800713CD: return "ERROR_DEPENDENCY_NOT_ALLOWED";
    // Original object relative source line 2580.
    case 0x000013CE:
    case 0x800713CE: return "ERROR_CLUSTER_NODE_PAUSED";
    // Original object relative source line 2581.
    case 0x000013CF:
    case 0x800713CF: return "ERROR_NODE_CANT_HOST_RESOURCE";
    // Original object relative source line 2582.
    case 0x000013D0:
    case 0x800713D0: return "ERROR_CLUSTER_NODE_NOT_READY";
    // Original object relative source line 2583.
    case 0x000013D1:
    case 0x800713D1: return "ERROR_CLUSTER_NODE_SHUTTING_DOWN";
    // Original object relative source line 2584.
    case 0x000013D2:
    case 0x800713D2: return "ERROR_CLUSTER_JOIN_ABORTED";
    // Original object relative source line 2585.
    case 0x000013D3:
    case 0x800713D3: return "ERROR_CLUSTER_INCOMPATIBLE_VERSIONS";
    // Original object relative source line 2586.
    case 0x000013D4:
    case 0x800713D4: return "ERROR_CLUSTER_MAXNUM_OF_RESOURCES_EXCEEDED";
    // Original object relative source line 2587.
    case 0x000013D5:
    case 0x800713D5: return "ERROR_CLUSTER_SYSTEM_CONFIG_CHANGED";
    // Original object relative source line 2588.
    case 0x000013D6:
    case 0x800713D6: return "ERROR_CLUSTER_RESOURCE_TYPE_NOT_FOUND";
    // Original object relative source line 2589.
    case 0x000013D7:
    case 0x800713D7: return "ERROR_CLUSTER_RESTYPE_NOT_SUPPORTED";
    // Original object relative source line 2590.
    case 0x000013D8:
    case 0x800713D8: return "ERROR_CLUSTER_RESNAME_NOT_FOUND";
    // Original object relative source line 2591.
    case 0x000013D9:
    case 0x800713D9: return "ERROR_CLUSTER_NO_RPC_PACKAGES_REGISTERED";
    // Original object relative source line 2592.
    case 0x000013DA:
    case 0x800713DA: return "ERROR_CLUSTER_OWNER_NOT_IN_PREFLIST";
    // Original object relative source line 2593.
    case 0x000013DB:
    case 0x800713DB: return "ERROR_CLUSTER_DATABASE_SEQMISMATCH";
    // Original object relative source line 2594.
    case 0x000013DC:
    case 0x800713DC: return "ERROR_RESMON_INVALID_STATE";
    // Original object relative source line 2595.
    case 0x000013DD:
    case 0x800713DD: return "ERROR_CLUSTER_GUM_NOT_LOCKER";
    // Original object relative source line 2596.
    case 0x000013DE:
    case 0x800713DE: return "ERROR_QUORUM_DISK_NOT_FOUND";
    // Original object relative source line 2597.
    case 0x000013DF:
    case 0x800713DF: return "ERROR_DATABASE_BACKUP_CORRUPT";
    // Original object relative source line 2598.
    case 0x000013E0:
    case 0x800713E0: return "ERROR_CLUSTER_NODE_ALREADY_HAS_DFS_ROOT";
    // Original object relative source line 2599.
    case 0x000013E1:
    case 0x800713E1: return "ERROR_RESOURCE_PROPERTY_UNCHANGEABLE";
    // Original object relative source line 2600.
    case 0x00001702:
    case 0x80071702: return "ERROR_CLUSTER_MEMBERSHIP_INVALID_STATE";
    // Original object relative source line 2601.
    case 0x00001703:
    case 0x80071703: return "ERROR_CLUSTER_QUORUMLOG_NOT_FOUND";
    // Original object relative source line 2602.
    case 0x00001704:
    case 0x80071704: return "ERROR_CLUSTER_MEMBERSHIP_HALT";
    // Original object relative source line 2603.
    case 0x00001705:
    case 0x80071705: return "ERROR_CLUSTER_INSTANCE_ID_MISMATCH";
    // Original object relative source line 2604.
    case 0x00001706:
    case 0x80071706: return "ERROR_CLUSTER_NETWORK_NOT_FOUND_FOR_IP";
    // Original object relative source line 2605.
    case 0x00001707:
    case 0x80071707: return "ERROR_CLUSTER_PROPERTY_DATA_TYPE_MISMATCH";
    // Original object relative source line 2606.
    case 0x00001708:
    case 0x80071708: return "ERROR_CLUSTER_EVICT_WITHOUT_CLEANUP";
    // Original object relative source line 2607.
    case 0x00001709:
    case 0x80071709: return "ERROR_CLUSTER_PARAMETER_MISMATCH";
    // Original object relative source line 2608.
    case 0x0000170A:
    case 0x8007170A: return "ERROR_NODE_CANNOT_BE_CLUSTERED";
    // Original object relative source line 2609.
    case 0x0000170B:
    case 0x8007170B: return "ERROR_CLUSTER_WRONG_OS_VERSION";
    // Original object relative source line 2610.
    case 0x0000170C:
    case 0x8007170C: return "ERROR_CLUSTER_CANT_CREATE_DUP_CLUSTER_NAME";
    // Original object relative source line 2616.
    case 0x00001779:
    case 0x80071779: return "ERROR_FILE_READ_ONLY";
    // Original object relative source line 2617.
    case 0x0000177A:
    case 0x8007177A: return "ERROR_DIR_EFS_DISALLOWED";
    // Original object relative source line 2618.
    case 0x0000177B:
    case 0x8007177B: return "ERROR_EFS_SERVER_NOT_TRUSTED";
    // Original object relative source line 2619.
    case 0x0000177C:
    case 0x8007177C: return "ERROR_BAD_RECOVERY_POLICY";
    // Original object relative source line 2620.
    case 0x0000177D:
    case 0x8007177D: return "ERROR_EFS_ALG_BLOB_TOO_BIG";
    // Original object relative source line 2621.
    case 0x0000177E:
    case 0x8007177E: return "ERROR_VOLUME_NOT_SUPPORT_EFS";
    // Original object relative source line 2622.
    case 0x0000177F:
    case 0x8007177F: return "ERROR_EFS_DISABLED";
    // Original object relative source line 2623.
    case 0x00001780:
    case 0x80071780: return "ERROR_EFS_VERSION_NOT_SUPPORT";
    // Original object relative source line 2624.
    case 0x00001838:
    case 0x80071838: return "SCHED_E_SERVICE_NOT_LOCALSYSTEM";
    // Original object relative source line 2625.
    case 0x00001B8C:
    case 0x80071B8C: return "ERROR_CTX_CLIENT_LICENSE_IN_USE";
    // Original object relative source line 2626.
    case 0x00001B8D:
    case 0x80071B8D: return "ERROR_CTX_CLIENT_LICENSE_NOT_SET";
    // Original object relative source line 2627.
    case 0x00001B8E:
    case 0x80071B8E: return "ERROR_CTX_LICENSE_NOT_AVAILABLE";
    // Original object relative source line 2628.
    case 0x00001B8F:
    case 0x80071B8F: return "ERROR_CTX_LICENSE_CLIENT_INVALID";
    // Original object relative source line 2629.
    case 0x00001B90:
    case 0x80071B90: return "ERROR_CTX_LICENSE_EXPIRED";
    // Original object relative source line 2630.
    case 0x00001B91:
    case 0x80071B91: return "ERROR_CTX_SHADOW_NOT_RUNNING";
    // Original object relative source line 2631.
    case 0x00001B92:
    case 0x80071B92: return "ERROR_CTX_SHADOW_ENDED_BY_MODE_CHANGE";
    // Original object relative source line 2633.
    case 0x00002045:
    case 0x80072045: return "ERROR_DS_SORT_CONTROL_MISSING";
    // Original object relative source line 2634.
    case 0x00002046:
    case 0x80072046: return "ERROR_DS_OFFSET_RANGE_ERROR";
    // Original object relative source line 2635.
    case 0x00002093:
    case 0x80072093: return "ERROR_DS_OBJECT_BEING_REMOVED";
    // Original object relative source line 2636.
    case 0x0000211E:
    case 0x8007211E: return "ERROR_DS_DS_REQUIRED";
    // Original object relative source line 2637.
    case 0x0000211F:
    case 0x8007211F: return "ERROR_DS_INVALID_LDAP_DISPLAY_NAME";
    // Original object relative source line 2638.
    case 0x00002120:
    case 0x80072120: return "ERROR_DS_NON_BASE_SEARCH";
    // Original object relative source line 2639.
    case 0x00002121:
    case 0x80072121: return "ERROR_DS_CANT_RETRIEVE_ATTS";
    // Original object relative source line 2640.
    case 0x00002122:
    case 0x80072122: return "ERROR_DS_BACKLINK_WITHOUT_LINK";
    // Original object relative source line 2641.
    case 0x00002123:
    case 0x80072123: return "ERROR_DS_EPOCH_MISMATCH";
    // Original object relative source line 2642.
    case 0x00002124:
    case 0x80072124: return "ERROR_DS_SRC_NAME_MISMATCH";
    // Original object relative source line 2643.
    case 0x00002125:
    case 0x80072125: return "ERROR_DS_SRC_AND_DST_NC_IDENTICAL";
    // Original object relative source line 2644.
    case 0x00002126:
    case 0x80072126: return "ERROR_DS_DST_NC_MISMATCH";
    // Original object relative source line 2645.
    case 0x00002127:
    case 0x80072127: return "ERROR_DS_NOT_AUTHORITIVE_FOR_DST_NC";
    // Original object relative source line 2646.
    case 0x00002128:
    case 0x80072128: return "ERROR_DS_SRC_GUID_MISMATCH";
    // Original object relative source line 2647.
    case 0x00002129:
    case 0x80072129: return "ERROR_DS_CANT_MOVE_DELETED_OBJECT";
    // Original object relative source line 2648.
    case 0x0000212A:
    case 0x8007212A: return "ERROR_DS_PDC_OPERATION_IN_PROGRESS";
    // Original object relative source line 2649.
    case 0x0000212B:
    case 0x8007212B: return "ERROR_DS_CROSS_DOMAIN_CLEANUP_REQD";
    // Original object relative source line 2650.
    case 0x0000212C:
    case 0x8007212C: return "ERROR_DS_ILLEGAL_XDOM_MOVE_OPERATION";
    // Original object relative source line 2651.
    case 0x0000212D:
    case 0x8007212D: return "ERROR_DS_CANT_WITH_ACCT_GROUP_MEMBERSHPS";
    // Original object relative source line 2652.
    case 0x0000212E:
    case 0x8007212E: return "ERROR_DS_NC_MUST_HAVE_NC_PARENT";
    // Original object relative source line 2653.
    case 0x0000212F:
    case 0x8007212F: return "ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE";
    // Original object relative source line 2654.
    case 0x00002130:
    case 0x80072130: return "ERROR_DS_DST_DOMAIN_NOT_NATIVE";
    // Original object relative source line 2655.
    case 0x00002131:
    case 0x80072131: return "ERROR_DS_MISSING_INFRASTRUCTURE_CONTAINER";
    // Original object relative source line 2656.
    case 0x00002132:
    case 0x80072132: return "ERROR_DS_CANT_MOVE_ACCOUNT_GROUP";
    // Original object relative source line 2657.
    case 0x00002133:
    case 0x80072133: return "ERROR_DS_CANT_MOVE_RESOURCE_GROUP";
    // Original object relative source line 2658.
    case 0x00002134:
    case 0x80072134: return "ERROR_DS_INVALID_SEARCH_FLAG";
    // Original object relative source line 2659.
    case 0x00002135:
    case 0x80072135: return "ERROR_DS_NO_TREE_DELETE_ABOVE_NC";
    // Original object relative source line 2660.
    case 0x00002136:
    case 0x80072136: return "ERROR_DS_COULDNT_LOCK_TREE_FOR_DELETE";
    // Original object relative source line 2661.
    case 0x00002137:
    case 0x80072137: return "ERROR_DS_COULDNT_IDENTIFY_OBJECTS_FOR_TREE_DELETE";
    // Original object relative source line 2662.
    case 0x00002138:
    case 0x80072138: return "ERROR_DS_SAM_INIT_FAILURE";
    // Original object relative source line 2663.
    case 0x00002139:
    case 0x80072139: return "ERROR_DS_SENSITIVE_GROUP_VIOLATION";
    // Original object relative source line 2664.
    case 0x0000213A:
    case 0x8007213A: return "ERROR_DS_CANT_MOD_PRIMARYGROUPID";
    // Original object relative source line 2665.
    case 0x0000213B:
    case 0x8007213B: return "ERROR_DS_ILLEGAL_BASE_SCHEMA_MOD";
    // Original object relative source line 2666.
    case 0x0000213C:
    case 0x8007213C: return "ERROR_DS_NONSAFE_SCHEMA_CHANGE";
    // Original object relative source line 2667.
    case 0x0000213D:
    case 0x8007213D: return "ERROR_DS_SCHEMA_UPDATE_DISALLOWED";
    // Original object relative source line 2668.
    case 0x0000213E:
    case 0x8007213E: return "ERROR_DS_CANT_CREATE_UNDER_SCHEMA";
    // Original object relative source line 2669.
    case 0x0000213F:
    case 0x8007213F: return "ERROR_DS_INSTALL_NO_SRC_SCH_VERSION";
    // Original object relative source line 2670.
    case 0x00002140:
    case 0x80072140: return "ERROR_DS_INSTALL_NO_SCH_VERSION_IN_INIFILE";
    // Original object relative source line 2671.
    case 0x00002141:
    case 0x80072141: return "ERROR_DS_INVALID_GROUP_TYPE";
    // Original object relative source line 2672.
    case 0x00002142:
    case 0x80072142: return "ERROR_DS_NO_NEST_GLOBALGROUP_IN_MIXEDDOMAIN";
    // Original object relative source line 2673.
    case 0x00002143:
    case 0x80072143: return "ERROR_DS_NO_NEST_LOCALGROUP_IN_MIXEDDOMAIN";
    // Original object relative source line 2674.
    case 0x00002144:
    case 0x80072144: return "ERROR_DS_GLOBAL_CANT_HAVE_LOCAL_MEMBER";
    // Original object relative source line 2675.
    case 0x00002145:
    case 0x80072145: return "ERROR_DS_GLOBAL_CANT_HAVE_UNIVERSAL_MEMBER";
    // Original object relative source line 2676.
    case 0x00002146:
    case 0x80072146: return "ERROR_DS_UNIVERSAL_CANT_HAVE_LOCAL_MEMBER";
    // Original object relative source line 2677.
    case 0x00002147:
    case 0x80072147: return "ERROR_DS_GLOBAL_CANT_HAVE_CROSSDOMAIN_MEMBER";
    // Original object relative source line 2678.
    case 0x00002148:
    case 0x80072148: return "ERROR_DS_LOCAL_CANT_HAVE_CROSSDOMAIN_LOCAL_MEMBER";
    // Original object relative source line 2679.
    case 0x00002149:
    case 0x80072149: return "ERROR_DS_HAVE_PRIMARY_MEMBERS";
    // Original object relative source line 2680.
    case 0x0000214A:
    case 0x8007214A: return "ERROR_DS_STRING_SD_CONVERSION_FAILED";
    // Original object relative source line 2681.
    case 0x0000214B:
    case 0x8007214B: return "ERROR_DS_NAMING_MASTER_GC";
    // Original object relative source line 2682.
    case 0x0000214C:
    case 0x8007214C: return "ERROR_DS_DNS_LOOKUP_FAILURE";
    // Original object relative source line 2683.
    case 0x0000214D:
    case 0x8007214D: return "ERROR_DS_COULDNT_UPDATE_SPNS";
    // Original object relative source line 2684.
    case 0x0000214E:
    case 0x8007214E: return "ERROR_DS_CANT_RETRIEVE_SD";
    // Original object relative source line 2685.
    case 0x0000214F:
    case 0x8007214F: return "ERROR_DS_KEY_NOT_UNIQUE";
    // Original object relative source line 2686.
    case 0x00002150:
    case 0x80072150: return "ERROR_DS_WRONG_LINKED_ATT_SYNTAX";
    // Original object relative source line 2687.
    case 0x00002151:
    case 0x80072151: return "ERROR_DS_SAM_NEED_BOOTKEY_PASSWORD";
    // Original object relative source line 2688.
    case 0x00002152:
    case 0x80072152: return "ERROR_DS_SAM_NEED_BOOTKEY_FLOPPY";
    // Original object relative source line 2689.
    case 0x00002153:
    case 0x80072153: return "ERROR_DS_CANT_START";
    // Original object relative source line 2690.
    case 0x00002154:
    case 0x80072154: return "ERROR_DS_INIT_FAILURE";
    // Original object relative source line 2691.
    case 0x00002155:
    case 0x80072155: return "ERROR_DS_NO_PKT_PRIVACY_ON_CONNECTION";
    // Original object relative source line 2692.
    case 0x00002156:
    case 0x80072156: return "ERROR_DS_SOURCE_DOMAIN_IN_FOREST";
    // Original object relative source line 2693.
    case 0x00002157:
    case 0x80072157: return "ERROR_DS_DESTINATION_DOMAIN_NOT_IN_FOREST";
    // Original object relative source line 2694.
    case 0x00002158:
    case 0x80072158: return "ERROR_DS_DESTINATION_AUDITING_NOT_ENABLED";
    // Original object relative source line 2695.
    case 0x00002159:
    case 0x80072159: return "ERROR_DS_CANT_FIND_DC_FOR_SRC_DOMAIN";
    // Original object relative source line 2696.
    case 0x0000215A:
    case 0x8007215A: return "ERROR_DS_SRC_OBJ_NOT_GROUP_OR_USER";
    // Original object relative source line 2697.
    case 0x0000215B:
    case 0x8007215B: return "ERROR_DS_SRC_SID_EXISTS_IN_FOREST";
    // Original object relative source line 2698.
    case 0x0000215C:
    case 0x8007215C: return "ERROR_DS_SRC_AND_DST_OBJECT_CLASS_MISMATCH";
    // Original object relative source line 2699.
    case 0x0000215D:
    case 0x8007215D: return "ERROR_SAM_INIT_FAILURE";
    // Original object relative source line 2700.
    case 0x0000215E:
    case 0x8007215E: return "ERROR_DS_DRA_SCHEMA_INFO_SHIP";
    // Original object relative source line 2701.
    case 0x0000215F:
    case 0x8007215F: return "ERROR_DS_DRA_SCHEMA_CONFLICT";
    // Original object relative source line 2702.
    case 0x00002160:
    case 0x80072160: return "ERROR_DS_DRA_EARLIER_SCHEMA_CONFLICT";
    // Original object relative source line 2703.
    case 0x00002161:
    case 0x80072161: return "ERROR_DS_DRA_OBJ_NC_MISMATCH";
    // Original object relative source line 2704.
    case 0x00002162:
    case 0x80072162: return "ERROR_DS_NC_STILL_HAS_DSAS";
    // Original object relative source line 2705.
    case 0x00002163:
    case 0x80072163: return "ERROR_DS_GC_REQUIRED";
    // Original object relative source line 2706.
    case 0x00002164:
    case 0x80072164: return "ERROR_DS_LOCAL_MEMBER_OF_LOCAL_ONLY";
    // Original object relative source line 2707.
    case 0x00002165:
    case 0x80072165: return "ERROR_DS_NO_FPO_IN_UNIVERSAL_GROUPS";
    // Original object relative source line 2708.
    case 0x00002166:
    case 0x80072166: return "ERROR_DS_CANT_ADD_TO_GC";
    // Original object relative source line 2709.
    case 0x00002167:
    case 0x80072167: return "ERROR_DS_NO_CHECKPOINT_WITH_PDC";
    // Original object relative source line 2710.
    case 0x00002168:
    case 0x80072168: return "ERROR_DS_SOURCE_AUDITING_NOT_ENABLED";
    // Original object relative source line 2711.
    case 0x00002169:
    case 0x80072169: return "ERROR_DS_CANT_CREATE_IN_NONDOMAIN_NC";
    // Original object relative source line 2712.
    case 0x0000216A:
    case 0x8007216A: return "ERROR_DS_INVALID_NAME_FOR_SPN";
    // Original object relative source line 2713.
    case 0x0000216B:
    case 0x8007216B: return "ERROR_DS_FILTER_USES_CONTRUCTED_ATTRS";
    // Original object relative source line 2714.
    case 0x0000216C:
    case 0x8007216C: return "ERROR_DS_UNICODEPWD_NOT_IN_QUOTES";
    // Original object relative source line 2715.
    case 0x0000216D:
    case 0x8007216D: return "ERROR_DS_MACHINE_ACCOUNT_QUOTA_EXCEEDED";
    // Original object relative source line 2716.
    case 0x0000216E:
    case 0x8007216E: return "ERROR_DS_MUST_BE_RUN_ON_DST_DC";
    // Original object relative source line 2717.
    case 0x0000216F:
    case 0x8007216F: return "ERROR_DS_SRC_DC_MUST_BE_SP4_OR_GREATER";
    // Original object relative source line 2718.
    case 0x00002170:
    case 0x80072170: return "ERROR_DS_CANT_TREE_DELETE_CRITICAL_OBJ";
    // Original object relative source line 2719.
    case 0x00002171:
    case 0x80072171: return "ERROR_DS_INIT_FAILURE_CONSOLE";
    // Original object relative source line 2720.
    case 0x00002172:
    case 0x80072172: return "ERROR_DS_SAM_INIT_FAILURE_CONSOLE";
    // Original object relative source line 2721.
    case 0x00002173:
    case 0x80072173: return "ERROR_DS_FOREST_VERSION_TOO_HIGH";
    // Original object relative source line 2722.
    case 0x00002174:
    case 0x80072174: return "ERROR_DS_DOMAIN_VERSION_TOO_HIGH";
    // Original object relative source line 2723.
    case 0x00002175:
    case 0x80072175: return "ERROR_DS_FOREST_VERSION_TOO_LOW";
    // Original object relative source line 2724.
    case 0x00002176:
    case 0x80072176: return "ERROR_DS_DOMAIN_VERSION_TOO_LOW";
    // Original object relative source line 2725.
    case 0x00002177:
    case 0x80072177: return "ERROR_DS_INCOMPATIBLE_VERSION";
    // Original object relative source line 2726.
    case 0x00002178:
    case 0x80072178: return "ERROR_DS_LOW_DSA_VERSION";
    // Original object relative source line 2727.
    case 0x00002179:
    case 0x80072179: return "ERROR_DS_NO_BEHAVIOR_VERSION_IN_MIXEDDOMAIN";
    // Original object relative source line 2728.
    case 0x0000217A:
    case 0x8007217A: return "ERROR_DS_NOT_SUPPORTED_SORT_ORDER";
    // Original object relative source line 2729.
    case 0x0000217B:
    case 0x8007217B: return "ERROR_DS_NAME_NOT_UNIQUE";
    // Original object relative source line 2730.
    case 0x0000217C:
    case 0x8007217C: return "ERROR_DS_MACHINE_ACCOUNT_CREATED_PRENT4";
    // Original object relative source line 2731.
    case 0x0000217D:
    case 0x8007217D: return "ERROR_DS_OUT_OF_VERSION_STORE";
    // Original object relative source line 2732.
    case 0x0000217E:
    case 0x8007217E: return "ERROR_DS_INCOMPATIBLE_CONTROLS_USED";
    // Original object relative source line 2733.
    case 0x0000217F:
    case 0x8007217F: return "ERROR_DS_NO_REF_DOMAIN";
    // Original object relative source line 2734.
    case 0x00002180:
    case 0x80072180: return "ERROR_DS_RESERVED_LINK_ID";
    // Original object relative source line 2735.
    case 0x00002181:
    case 0x80072181: return "ERROR_DS_LINK_ID_NOT_AVAILABLE";
    // Original object relative source line 2736.
    case 0x00002182:
    case 0x80072182: return "ERROR_DS_AG_CANT_HAVE_UNIVERSAL_MEMBER";
    // Original object relative source line 2737.
    case 0x00002183:
    case 0x80072183: return "ERROR_DS_MODIFYDN_DISALLOWED_BY_INSTANCE_TYPE";
    // Original object relative source line 2738.
    case 0x00002184:
    case 0x80072184: return "ERROR_DS_NO_OBJECT_MOVE_IN_SCHEMA_NC";
    // Original object relative source line 2739.
    case 0x00002185:
    case 0x80072185: return "ERROR_DS_MODIFYDN_DISALLOWED_BY_FLAG";
    // Original object relative source line 2740.
    case 0x00002186:
    case 0x80072186: return "ERROR_DS_MODIFYDN_WRONG_GRANDPARENT";
    // Original object relative source line 2741.
    case 0x00002187:
    case 0x80072187: return "ERROR_DS_NAME_ERROR_TRUST_REFERRAL";
    // Original object relative source line 2742.
    case 0x00002188:
    case 0x80072188: return "ERROR_NOT_SUPPORTED_ON_STANDARD_SERVER";
    // Original object relative source line 2743.
    case 0x00002189:
    case 0x80072189: return "ERROR_DS_CANT_ACCESS_REMOTE_PART_OF_AD";
    // Original object relative source line 2744.
    case 0x0000218A:
    case 0x8007218A: return "ERROR_DS_CR_IMPOSSIBLE_TO_VALIDATE_V2";
    // Original object relative source line 2745.
    case 0x0000218B:
    case 0x8007218B: return "ERROR_DS_THREAD_LIMIT_EXCEEDED";
    // Original object relative source line 2746.
    case 0x0000218C:
    case 0x8007218C: return "ERROR_DS_NOT_CLOSEST";
    // Original object relative source line 2747.
    case 0x0000218D:
    case 0x8007218D: return "ERROR_DS_CANT_DERIVE_SPN_WITHOUT_SERVER_REF";
    // Original object relative source line 2748.
    case 0x0000218E:
    case 0x8007218E: return "ERROR_DS_SINGLE_USER_MODE_FAILED";
    // Original object relative source line 2749.
    case 0x0000218F:
    case 0x8007218F: return "ERROR_DS_NTDSCRIPT_SYNTAX_ERROR";
    // Original object relative source line 2750.
    case 0x00002190:
    case 0x80072190: return "ERROR_DS_NTDSCRIPT_PROCESS_ERROR";
    // Original object relative source line 2751.
    case 0x00002191:
    case 0x80072191: return "ERROR_DS_DIFFERENT_REPL_EPOCHS";
    // Original object relative source line 2752.
    case 0x00002192:
    case 0x80072192: return "ERROR_DS_DRS_EXTENSIONS_CHANGED";
    // Original object relative source line 2753.
    case 0x00002193:
    case 0x80072193: return "ERROR_DS_REPLICA_SET_CHANGE_NOT_ALLOWED_ON_DISABLED_CR";
    // Original object relative source line 2754.
    case 0x00002194:
    case 0x80072194: return "ERROR_DS_NO_MSDS_INTID";
    // Original object relative source line 2755.
    case 0x00002195:
    case 0x80072195: return "ERROR_DS_DUP_MSDS_INTID";
    // Original object relative source line 2756.
    case 0x00002196:
    case 0x80072196: return "ERROR_DS_EXISTS_IN_RDNATTID";
    // Original object relative source line 2757.
    case 0x00002197:
    case 0x80072197: return "ERROR_DS_AUTHORIZATION_FAILED";
    // Original object relative source line 2758.
    case 0x00002198:
    case 0x80072198: return "ERROR_DS_INVALID_SCRIPT";
    // Original object relative source line 2759.
    case 0x00002199:
    case 0x80072199: return "ERROR_DS_REMOTE_CROSSREF_OP_FAILED";
    // Original object relative source line 2778.
    case 0x00002593:
    case 0x80072593: return "DNS_ERROR_FORWARDER_ALREADY_EXISTS";
    // Original object relative source line 2779.
    case 0x00002594:
    case 0x80072594: return "DNS_ERROR_ZONE_REQUIRES_MASTER_IP";
    // Original object relative source line 2780.
    case 0x00002595:
    case 0x80072595: return "DNS_ERROR_ZONE_IS_SHUTDOWN";
    // Original object relative source line 2781.
    case 0x000026AC:
    case 0x800726AC: return "DNS_ERROR_DP_BASE";
    // Original object relative source line 2782.
    case 0x000026AD:
    case 0x800726AD: return "DNS_ERROR_DP_DOES_NOT_EXIST";
    // Original object relative source line 2783.
    case 0x000026AE:
    case 0x800726AE: return "DNS_ERROR_DP_ALREADY_EXISTS";
    // Original object relative source line 2784.
    case 0x000026AF:
    case 0x800726AF: return "DNS_ERROR_DP_NOT_ENLISTED";
    // Original object relative source line 2785.
    case 0x000026B0:
    case 0x800726B0: return "DNS_ERROR_DP_ALREADY_ENLISTED";
    // Original object relative source line 2787.
    case 0x00002B08:
    case 0x80072B08: return "WSA_QOS_ESERVICETYPE";
    // Original object relative source line 2788.
    case 0x00002B09:
    case 0x80072B09: return "WSA_QOS_EFLOWSPEC";
    // Original object relative source line 2789.
    case 0x00002B0A:
    case 0x80072B0A: return "WSA_QOS_EPROVSPECBUF";
    // Original object relative source line 2790.
    case 0x00002B0B:
    case 0x80072B0B: return "WSA_QOS_EFILTERSTYLE";
    // Original object relative source line 2791.
    case 0x00002B0C:
    case 0x80072B0C: return "WSA_QOS_EFILTERTYPE";
    // Original object relative source line 2792.
    case 0x00002B0D:
    case 0x80072B0D: return "WSA_QOS_EFILTERCOUNT";
    // Original object relative source line 2793.
    case 0x00002B0E:
    case 0x80072B0E: return "WSA_QOS_EOBJLENGTH";
    // Original object relative source line 2794.
    case 0x00002B0F:
    case 0x80072B0F: return "WSA_QOS_EFLOWCOUNT";
    // Original object relative source line 2795.
    case 0x00002B10:
    case 0x80072B10: return "WSA_QOS_EUNKOWNPSOBJ";
    // Original object relative source line 2796.
    case 0x00002B11:
    case 0x80072B11: return "WSA_QOS_EPOLICYOBJ";
    // Original object relative source line 2797.
    case 0x00002B12:
    case 0x80072B12: return "WSA_QOS_EFLOWDESC";
    // Original object relative source line 2798.
    case 0x00002B13:
    case 0x80072B13: return "WSA_QOS_EPSFLOWSPEC";
    // Original object relative source line 2799.
    case 0x00002B14:
    case 0x80072B14: return "WSA_QOS_EPSFILTERSPEC";
    // Original object relative source line 2800.
    case 0x00002B15:
    case 0x80072B15: return "WSA_QOS_ESDMODEOBJ";
    // Original object relative source line 2801.
    case 0x00002B16:
    case 0x80072B16: return "WSA_QOS_ESHAPERATEOBJ";
    // Original object relative source line 2802.
    case 0x00002B17:
    case 0x80072B17: return "WSA_QOS_RESERVED_PETYPE";
    // Original object relative source line 2803.
    case 0x000036B0:
    case 0x800736B0: return "ERROR_SXS_SECTION_NOT_FOUND";
    // Original object relative source line 2804.
    case 0x000036B1:
    case 0x800736B1: return "ERROR_SXS_CANT_GEN_ACTCTX";
    // Original object relative source line 2805.
    case 0x000036B2:
    case 0x800736B2: return "ERROR_SXS_INVALID_ACTCTXDATA_FORMAT";
    // Original object relative source line 2806.
    case 0x000036B3:
    case 0x800736B3: return "ERROR_SXS_ASSEMBLY_NOT_FOUND";
    // Original object relative source line 2807.
    case 0x000036B4:
    case 0x800736B4: return "ERROR_SXS_MANIFEST_FORMAT_ERROR";
    // Original object relative source line 2808.
    case 0x000036B5:
    case 0x800736B5: return "ERROR_SXS_MANIFEST_PARSE_ERROR";
    // Original object relative source line 2809.
    case 0x000036B6:
    case 0x800736B6: return "ERROR_SXS_ACTIVATION_CONTEXT_DISABLED";
    // Original object relative source line 2810.
    case 0x000036B7:
    case 0x800736B7: return "ERROR_SXS_KEY_NOT_FOUND";
    // Original object relative source line 2811.
    case 0x000036B8:
    case 0x800736B8: return "ERROR_SXS_VERSION_CONFLICT";
    // Original object relative source line 2812.
    case 0x000036B9:
    case 0x800736B9: return "ERROR_SXS_WRONG_SECTION_TYPE";
    // Original object relative source line 2813.
    case 0x000036BA:
    case 0x800736BA: return "ERROR_SXS_THREAD_QUERIES_DISABLED";
    // Original object relative source line 2814.
    case 0x000036BB:
    case 0x800736BB: return "ERROR_SXS_PROCESS_DEFAULT_ALREADY_SET";
    // Original object relative source line 2815.
    case 0x000036BC:
    case 0x800736BC: return "ERROR_SXS_UNKNOWN_ENCODING_GROUP";
    // Original object relative source line 2816.
    case 0x000036BD:
    case 0x800736BD: return "ERROR_SXS_UNKNOWN_ENCODING";
    // Original object relative source line 2817.
    case 0x000036BE:
    case 0x800736BE: return "ERROR_SXS_INVALID_XML_NAMESPACE_URI";
    // Original object relative source line 2818.
    case 0x000036BF:
    case 0x800736BF: return "ERROR_SXS_ROOT_MANIFEST_DEPENDENCY_NOT_INSTALLED";
    // Original object relative source line 2819.
    case 0x000036C0:
    case 0x800736C0: return "ERROR_SXS_LEAF_MANIFEST_DEPENDENCY_NOT_INSTALLED";
    // Original object relative source line 2820.
    case 0x000036C1:
    case 0x800736C1: return "ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE";
    // Original object relative source line 2821.
    case 0x000036C2:
    case 0x800736C2: return "ERROR_SXS_MANIFEST_MISSING_REQUIRED_DEFAULT_NAMESPACE";
    // Original object relative source line 2822.
    case 0x000036C3:
    case 0x800736C3: return "ERROR_SXS_MANIFEST_INVALID_REQUIRED_DEFAULT_NAMESPACE";
    // Original object relative source line 2823.
    case 0x000036C4:
    case 0x800736C4: return "ERROR_SXS_PRIVATE_MANIFEST_CROSS_PATH_WITH_REPARSE_POINT";
    // Original object relative source line 2824.
    case 0x000036C5:
    case 0x800736C5: return "ERROR_SXS_DUPLICATE_DLL_NAME";
    // Original object relative source line 2825.
    case 0x000036C6:
    case 0x800736C6: return "ERROR_SXS_DUPLICATE_WINDOWCLASS_NAME";
    // Original object relative source line 2826.
    case 0x000036C7:
    case 0x800736C7: return "ERROR_SXS_DUPLICATE_CLSID";
    // Original object relative source line 2827.
    case 0x000036C8:
    case 0x800736C8: return "ERROR_SXS_DUPLICATE_IID";
    // Original object relative source line 2828.
    case 0x000036C9:
    case 0x800736C9: return "ERROR_SXS_DUPLICATE_TLBID";
    // Original object relative source line 2829.
    case 0x000036CA:
    case 0x800736CA: return "ERROR_SXS_DUPLICATE_PROGID";
    // Original object relative source line 2830.
    case 0x000036CB:
    case 0x800736CB: return "ERROR_SXS_DUPLICATE_ASSEMBLY_NAME";
    // Original object relative source line 2831.
    case 0x000036CC:
    case 0x800736CC: return "ERROR_SXS_FILE_HASH_MISMATCH";
    // Original object relative source line 2832.
    case 0x000036CD:
    case 0x800736CD: return "ERROR_SXS_POLICY_PARSE_ERROR";
    // Original object relative source line 2833.
    case 0x000036CE:
    case 0x800736CE: return "ERROR_SXS_XML_E_MISSINGQUOTE";
    // Original object relative source line 2834.
    case 0x000036CF:
    case 0x800736CF: return "ERROR_SXS_XML_E_COMMENTSYNTAX";
    // Original object relative source line 2835.
    case 0x000036D0:
    case 0x800736D0: return "ERROR_SXS_XML_E_BADSTARTNAMECHAR";
    // Original object relative source line 2836.
    case 0x000036D1:
    case 0x800736D1: return "ERROR_SXS_XML_E_BADNAMECHAR";
    // Original object relative source line 2837.
    case 0x000036D2:
    case 0x800736D2: return "ERROR_SXS_XML_E_BADCHARINSTRING";
    // Original object relative source line 2838.
    case 0x000036D3:
    case 0x800736D3: return "ERROR_SXS_XML_E_XMLDECLSYNTAX";
    // Original object relative source line 2839.
    case 0x000036D4:
    case 0x800736D4: return "ERROR_SXS_XML_E_BADCHARDATA";
    // Original object relative source line 2840.
    case 0x000036D5:
    case 0x800736D5: return "ERROR_SXS_XML_E_MISSINGWHITESPACE";
    // Original object relative source line 2841.
    case 0x000036D6:
    case 0x800736D6: return "ERROR_SXS_XML_E_EXPECTINGTAGEND";
    // Original object relative source line 2842.
    case 0x000036D7:
    case 0x800736D7: return "ERROR_SXS_XML_E_MISSINGSEMICOLON";
    // Original object relative source line 2843.
    case 0x000036D8:
    case 0x800736D8: return "ERROR_SXS_XML_E_UNBALANCEDPAREN";
    // Original object relative source line 2844.
    case 0x000036D9:
    case 0x800736D9: return "ERROR_SXS_XML_E_INTERNALERROR";
    // Original object relative source line 2845.
    case 0x000036DA:
    case 0x800736DA: return "ERROR_SXS_XML_E_UNEXPECTED_WHITESPACE";
    // Original object relative source line 2846.
    case 0x000036DB:
    case 0x800736DB: return "ERROR_SXS_XML_E_INCOMPLETE_ENCODING";
    // Original object relative source line 2847.
    case 0x000036DC:
    case 0x800736DC: return "ERROR_SXS_XML_E_MISSING_PAREN";
    // Original object relative source line 2848.
    case 0x000036DD:
    case 0x800736DD: return "ERROR_SXS_XML_E_EXPECTINGCLOSEQUOTE";
    // Original object relative source line 2849.
    case 0x000036DE:
    case 0x800736DE: return "ERROR_SXS_XML_E_MULTIPLE_COLONS";
    // Original object relative source line 2850.
    case 0x000036DF:
    case 0x800736DF: return "ERROR_SXS_XML_E_INVALID_DECIMAL";
    // Original object relative source line 2851.
    case 0x000036E0:
    case 0x800736E0: return "ERROR_SXS_XML_E_INVALID_HEXIDECIMAL";
    // Original object relative source line 2852.
    case 0x000036E1:
    case 0x800736E1: return "ERROR_SXS_XML_E_INVALID_UNICODE";
    // Original object relative source line 2853.
    case 0x000036E2:
    case 0x800736E2: return "ERROR_SXS_XML_E_WHITESPACEORQUESTIONMARK";
    // Original object relative source line 2854.
    case 0x000036E3:
    case 0x800736E3: return "ERROR_SXS_XML_E_UNEXPECTEDENDTAG";
    // Original object relative source line 2855.
    case 0x000036E4:
    case 0x800736E4: return "ERROR_SXS_XML_E_UNCLOSEDTAG";
    // Original object relative source line 2856.
    case 0x000036E5:
    case 0x800736E5: return "ERROR_SXS_XML_E_DUPLICATEATTRIBUTE";
    // Original object relative source line 2857.
    case 0x000036E6:
    case 0x800736E6: return "ERROR_SXS_XML_E_MULTIPLEROOTS";
    // Original object relative source line 2858.
    case 0x000036E7:
    case 0x800736E7: return "ERROR_SXS_XML_E_INVALIDATROOTLEVEL";
    // Original object relative source line 2859.
    case 0x000036E8:
    case 0x800736E8: return "ERROR_SXS_XML_E_BADXMLDECL";
    // Original object relative source line 2860.
    case 0x000036E9:
    case 0x800736E9: return "ERROR_SXS_XML_E_MISSINGROOT";
    // Original object relative source line 2861.
    case 0x000036EA:
    case 0x800736EA: return "ERROR_SXS_XML_E_UNEXPECTEDEOF";
    // Original object relative source line 2862.
    case 0x000036EB:
    case 0x800736EB: return "ERROR_SXS_XML_E_BADPEREFINSUBSET";
    // Original object relative source line 2863.
    case 0x000036EC:
    case 0x800736EC: return "ERROR_SXS_XML_E_UNCLOSEDSTARTTAG";
    // Original object relative source line 2864.
    case 0x000036ED:
    case 0x800736ED: return "ERROR_SXS_XML_E_UNCLOSEDENDTAG";
    // Original object relative source line 2865.
    case 0x000036EE:
    case 0x800736EE: return "ERROR_SXS_XML_E_UNCLOSEDSTRING";
    // Original object relative source line 2866.
    case 0x000036EF:
    case 0x800736EF: return "ERROR_SXS_XML_E_UNCLOSEDCOMMENT";
    // Original object relative source line 2867.
    case 0x000036F0:
    case 0x800736F0: return "ERROR_SXS_XML_E_UNCLOSEDDECL";
    // Original object relative source line 2868.
    case 0x000036F1:
    case 0x800736F1: return "ERROR_SXS_XML_E_UNCLOSEDCDATA";
    // Original object relative source line 2869.
    case 0x000036F2:
    case 0x800736F2: return "ERROR_SXS_XML_E_RESERVEDNAMESPACE";
    // Original object relative source line 2870.
    case 0x000036F3:
    case 0x800736F3: return "ERROR_SXS_XML_E_INVALIDENCODING";
    // Original object relative source line 2871.
    case 0x000036F4:
    case 0x800736F4: return "ERROR_SXS_XML_E_INVALIDSWITCH";
    // Original object relative source line 2872.
    case 0x000036F5:
    case 0x800736F5: return "ERROR_SXS_XML_E_BADXMLCASE";
    // Original object relative source line 2873.
    case 0x000036F6:
    case 0x800736F6: return "ERROR_SXS_XML_E_INVALID_STANDALONE";
    // Original object relative source line 2874.
    case 0x000036F7:
    case 0x800736F7: return "ERROR_SXS_XML_E_UNEXPECTED_STANDALONE";
    // Original object relative source line 2875.
    case 0x000036F8:
    case 0x800736F8: return "ERROR_SXS_XML_E_INVALID_VERSION";
    // Original object relative source line 2876.
    case 0x000036F9:
    case 0x800736F9: return "ERROR_SXS_XML_E_MISSINGEQUALS";
    // Original object relative source line 2877.
    case 0x000036FA:
    case 0x800736FA: return "ERROR_SXS_PROTECTION_RECOVERY_FAILED";
    // Original object relative source line 2878.
    case 0x000036FB:
    case 0x800736FB: return "ERROR_SXS_PROTECTION_PUBLIC_KEY_TOO_SHORT";
    // Original object relative source line 2879.
    case 0x000036FC:
    case 0x800736FC: return "ERROR_SXS_PROTECTION_CATALOG_NOT_VALID";
    // Original object relative source line 2880.
    case 0x000036FD:
    case 0x800736FD: return "ERROR_SXS_UNTRANSLATABLE_HRESULT";
    // Original object relative source line 2881.
    case 0x000036FE:
    case 0x800736FE: return "ERROR_SXS_PROTECTION_CATALOG_FILE_MISSING";
    // Original object relative source line 2882.
    case 0x000036FF:
    case 0x800736FF: return "ERROR_SXS_MISSING_ASSEMBLY_IDENTITY_ATTRIBUTE";
    // Original object relative source line 2883.
    case 0x00003700:
    case 0x80073700: return "ERROR_SXS_INVALID_ASSEMBLY_IDENTITY_ATTRIBUTE_NAME";
    // Original object relative source line 2884.
    case 0x000032C8:
    case 0x800732C8: return "ERROR_IPSEC_QM_POLICY_EXISTS";
    // Original object relative source line 2885.
    case 0x000032C9:
    case 0x800732C9: return "ERROR_IPSEC_QM_POLICY_NOT_FOUND";
    // Original object relative source line 2886.
    case 0x000032CA:
    case 0x800732CA: return "ERROR_IPSEC_QM_POLICY_IN_USE";
    // Original object relative source line 2887.
    case 0x000032CB:
    case 0x800732CB: return "ERROR_IPSEC_MM_POLICY_EXISTS";
    // Original object relative source line 2888.
    case 0x000032CC:
    case 0x800732CC: return "ERROR_IPSEC_MM_POLICY_NOT_FOUND";
    // Original object relative source line 2889.
    case 0x000032CD:
    case 0x800732CD: return "ERROR_IPSEC_MM_POLICY_IN_USE";
    // Original object relative source line 2890.
    case 0x000032CE:
    case 0x800732CE: return "ERROR_IPSEC_MM_FILTER_EXISTS";
    // Original object relative source line 2891.
    case 0x000032CF:
    case 0x800732CF: return "ERROR_IPSEC_MM_FILTER_NOT_FOUND";
    // Original object relative source line 2892.
    case 0x000032D0:
    case 0x800732D0: return "ERROR_IPSEC_TRANSPORT_FILTER_EXISTS";
    // Original object relative source line 2893.
    case 0x000032D1:
    case 0x800732D1: return "ERROR_IPSEC_TRANSPORT_FILTER_NOT_FOUND";
    // Original object relative source line 2894.
    case 0x000032D2:
    case 0x800732D2: return "ERROR_IPSEC_MM_AUTH_EXISTS";
    // Original object relative source line 2895.
    case 0x000032D3:
    case 0x800732D3: return "ERROR_IPSEC_MM_AUTH_NOT_FOUND";
    // Original object relative source line 2896.
    case 0x000032D4:
    case 0x800732D4: return "ERROR_IPSEC_MM_AUTH_IN_USE";
    // Original object relative source line 2897.
    case 0x000032D5:
    case 0x800732D5: return "ERROR_IPSEC_DEFAULT_MM_POLICY_NOT_FOUND";
    // Original object relative source line 2898.
    case 0x000032D6:
    case 0x800732D6: return "ERROR_IPSEC_DEFAULT_MM_AUTH_NOT_FOUND";
    // Original object relative source line 2899.
    case 0x000032D7:
    case 0x800732D7: return "ERROR_IPSEC_DEFAULT_QM_POLICY_NOT_FOUND";
    // Original object relative source line 2900.
    case 0x000032D8:
    case 0x800732D8: return "ERROR_IPSEC_TUNNEL_FILTER_EXISTS";
    // Original object relative source line 2901.
    case 0x000032D9:
    case 0x800732D9: return "ERROR_IPSEC_TUNNEL_FILTER_NOT_FOUND";
    // Original object relative source line 2902.
    case 0x000032DA:
    case 0x800732DA: return "ERROR_IPSEC_MM_FILTER_PENDING_DELETION";
    // Original object relative source line 2903.
    case 0x000032DB:
    case 0x800732DB: return "ERROR_IPSEC_TRANSPORT_FILTER_PENDING_DELETION";
    // Original object relative source line 2904.
    case 0x000032DC:
    case 0x800732DC: return "ERROR_IPSEC_TUNNEL_FILTER_PENDING_DELETION";
    // Original object relative source line 2905.
    case 0x000032DD:
    case 0x800732DD: return "ERROR_IPSEC_MM_POLICY_PENDING_DELETION";
    // Original object relative source line 2906.
    case 0x000032DE:
    case 0x800732DE: return "ERROR_IPSEC_MM_AUTH_PENDING_DELETION";
    // Original object relative source line 2907.
    case 0x000032DF:
    case 0x800732DF: return "ERROR_IPSEC_QM_POLICY_PENDING_DELETION";
    // Original object relative source line 2910.
    case 0x000035E8:
    case 0x800735E8: return "ERROR_IPSEC_IKE_NEG_STATUS_BEGIN";
    // Original object relative source line 2911.
    case 0x000035E9:
    case 0x800735E9: return "ERROR_IPSEC_IKE_AUTH_FAIL";
    // Original object relative source line 2912.
    case 0x000035EA:
    case 0x800735EA: return "ERROR_IPSEC_IKE_ATTRIB_FAIL";
    // Original object relative source line 2913.
    case 0x000035EB:
    case 0x800735EB: return "ERROR_IPSEC_IKE_NEGOTIATION_PENDING";
    // Original object relative source line 2914.
    case 0x000035EC:
    case 0x800735EC: return "ERROR_IPSEC_IKE_GENERAL_PROCESSING_ERROR";
    // Original object relative source line 2915.
    case 0x000035ED:
    case 0x800735ED: return "ERROR_IPSEC_IKE_TIMED_OUT";
    // Original object relative source line 2916.
    case 0x000035EE:
    case 0x800735EE: return "ERROR_IPSEC_IKE_NO_CERT";
    // Original object relative source line 2917.
    case 0x000035EF:
    case 0x800735EF: return "ERROR_IPSEC_IKE_SA_DELETED";
    // Original object relative source line 2918.
    case 0x000035F0:
    case 0x800735F0: return "ERROR_IPSEC_IKE_SA_REAPED";
    // Original object relative source line 2919.
    case 0x000035F1:
    case 0x800735F1: return "ERROR_IPSEC_IKE_MM_ACQUIRE_DROP";
    // Original object relative source line 2920.
    case 0x000035F2:
    case 0x800735F2: return "ERROR_IPSEC_IKE_QM_ACQUIRE_DROP";
    // Original object relative source line 2921.
    case 0x000035F3:
    case 0x800735F3: return "ERROR_IPSEC_IKE_QUEUE_DROP_MM";
    // Original object relative source line 2922.
    case 0x000035F4:
    case 0x800735F4: return "ERROR_IPSEC_IKE_QUEUE_DROP_NO_MM";
    // Original object relative source line 2923.
    case 0x000035F5:
    case 0x800735F5: return "ERROR_IPSEC_IKE_DROP_NO_RESPONSE";
    // Original object relative source line 2924.
    case 0x000035F6:
    case 0x800735F6: return "ERROR_IPSEC_IKE_MM_DELAY_DROP";
    // Original object relative source line 2925.
    case 0x000035F7:
    case 0x800735F7: return "ERROR_IPSEC_IKE_QM_DELAY_DROP";
    // Original object relative source line 2926.
    case 0x000035F8:
    case 0x800735F8: return "ERROR_IPSEC_IKE_ERROR";
    // Original object relative source line 2927.
    case 0x000035F9:
    case 0x800735F9: return "ERROR_IPSEC_IKE_CRL_FAILED";
    // Original object relative source line 2928.
    case 0x000035FA:
    case 0x800735FA: return "ERROR_IPSEC_IKE_INVALID_KEY_USAGE";
    // Original object relative source line 2929.
    case 0x000035FB:
    case 0x800735FB: return "ERROR_IPSEC_IKE_INVALID_CERT_TYPE";
    // Original object relative source line 2930.
    case 0x000035FC:
    case 0x800735FC: return "ERROR_IPSEC_IKE_NO_PRIVATE_KEY";
    // Original object relative source line 2931.
    case 0x000035FE:
    case 0x800735FE: return "ERROR_IPSEC_IKE_DH_FAIL";
    // Original object relative source line 2932.
    case 0x00003600:
    case 0x80073600: return "ERROR_IPSEC_IKE_INVALID_HEADER";
    // Original object relative source line 2933.
    case 0x00003601:
    case 0x80073601: return "ERROR_IPSEC_IKE_NO_POLICY";
    // Original object relative source line 2934.
    case 0x00003602:
    case 0x80073602: return "ERROR_IPSEC_IKE_INVALID_SIGNATURE";
    // Original object relative source line 2935.
    case 0x00003603:
    case 0x80073603: return "ERROR_IPSEC_IKE_KERBEROS_ERROR";
    // Original object relative source line 2936.
    case 0x00003604:
    case 0x80073604: return "ERROR_IPSEC_IKE_NO_PUBLIC_KEY";
    // Original object relative source line 2937.
    case 0x00003605:
    case 0x80073605: return "ERROR_IPSEC_IKE_PROCESS_ERR";
    // Original object relative source line 2938.
    case 0x00003606:
    case 0x80073606: return "ERROR_IPSEC_IKE_PROCESS_ERR_SA";
    // Original object relative source line 2939.
    case 0x00003607:
    case 0x80073607: return "ERROR_IPSEC_IKE_PROCESS_ERR_PROP";
    // Original object relative source line 2940.
    case 0x00003608:
    case 0x80073608: return "ERROR_IPSEC_IKE_PROCESS_ERR_TRANS";
    // Original object relative source line 2941.
    case 0x00003609:
    case 0x80073609: return "ERROR_IPSEC_IKE_PROCESS_ERR_KE";
    // Original object relative source line 2942.
    case 0x0000360A:
    case 0x8007360A: return "ERROR_IPSEC_IKE_PROCESS_ERR_ID";
    // Original object relative source line 2943.
    case 0x0000360B:
    case 0x8007360B: return "ERROR_IPSEC_IKE_PROCESS_ERR_CERT";
    // Original object relative source line 2944.
    case 0x0000360C:
    case 0x8007360C: return "ERROR_IPSEC_IKE_PROCESS_ERR_CERT_REQ";
    // Original object relative source line 2945.
    case 0x0000360D:
    case 0x8007360D: return "ERROR_IPSEC_IKE_PROCESS_ERR_HASH";
    // Original object relative source line 2946.
    case 0x0000360E:
    case 0x8007360E: return "ERROR_IPSEC_IKE_PROCESS_ERR_SIG";
    // Original object relative source line 2947.
    case 0x0000360F:
    case 0x8007360F: return "ERROR_IPSEC_IKE_PROCESS_ERR_NONCE";
    // Original object relative source line 2948.
    case 0x00003610:
    case 0x80073610: return "ERROR_IPSEC_IKE_PROCESS_ERR_NOTIFY";
    // Original object relative source line 2949.
    case 0x00003611:
    case 0x80073611: return "ERROR_IPSEC_IKE_PROCESS_ERR_DELETE";
    // Original object relative source line 2950.
    case 0x00003612:
    case 0x80073612: return "ERROR_IPSEC_IKE_PROCESS_ERR_VENDOR";
    // Original object relative source line 2951.
    case 0x00003613:
    case 0x80073613: return "ERROR_IPSEC_IKE_INVALID_PAYLOAD";
    // Original object relative source line 2952.
    case 0x00003614:
    case 0x80073614: return "ERROR_IPSEC_IKE_LOAD_SOFT_SA";
    // Original object relative source line 2953.
    case 0x00003615:
    case 0x80073615: return "ERROR_IPSEC_IKE_SOFT_SA_TORN_DOWN";
    // Original object relative source line 2954.
    case 0x00003616:
    case 0x80073616: return "ERROR_IPSEC_IKE_INVALID_COOKIE";
    // Original object relative source line 2955.
    case 0x00003617:
    case 0x80073617: return "ERROR_IPSEC_IKE_NO_PEER_CERT";
    // Original object relative source line 2956.
    case 0x00003618:
    case 0x80073618: return "ERROR_IPSEC_IKE_PEER_CRL_FAILED";
    // Original object relative source line 2957.
    case 0x00003619:
    case 0x80073619: return "ERROR_IPSEC_IKE_POLICY_CHANGE";
    // Original object relative source line 2958.
    case 0x0000361A:
    case 0x8007361A: return "ERROR_IPSEC_IKE_NO_MM_POLICY";
    // Original object relative source line 2959.
    case 0x0000361B:
    case 0x8007361B: return "ERROR_IPSEC_IKE_NOTCBPRIV";
    // Original object relative source line 2960.
    case 0x0000361C:
    case 0x8007361C: return "ERROR_IPSEC_IKE_SECLOADFAIL";
    // Original object relative source line 2961.
    case 0x0000361D:
    case 0x8007361D: return "ERROR_IPSEC_IKE_FAILSSPINIT";
    // Original object relative source line 2962.
    case 0x0000361E:
    case 0x8007361E: return "ERROR_IPSEC_IKE_FAILQUERYSSP";
    // Original object relative source line 2963.
    case 0x0000361F:
    case 0x8007361F: return "ERROR_IPSEC_IKE_SRVACQFAIL";
    // Original object relative source line 2964.
    case 0x00003620:
    case 0x80073620: return "ERROR_IPSEC_IKE_SRVQUERYCRED";
    // Original object relative source line 2965.
    case 0x00003621:
    case 0x80073621: return "ERROR_IPSEC_IKE_GETSPIFAIL";
    // Original object relative source line 2966.
    case 0x00003622:
    case 0x80073622: return "ERROR_IPSEC_IKE_INVALID_FILTER";
    // Original object relative source line 2967.
    case 0x00003623:
    case 0x80073623: return "ERROR_IPSEC_IKE_OUT_OF_MEMORY";
    // Original object relative source line 2968.
    case 0x00003624:
    case 0x80073624: return "ERROR_IPSEC_IKE_ADD_UPDATE_KEY_FAILED";
    // Original object relative source line 2969.
    case 0x00003625:
    case 0x80073625: return "ERROR_IPSEC_IKE_INVALID_POLICY";
    // Original object relative source line 2970.
    case 0x00003626:
    case 0x80073626: return "ERROR_IPSEC_IKE_UNKNOWN_DOI";
    // Original object relative source line 2971.
    case 0x00003627:
    case 0x80073627: return "ERROR_IPSEC_IKE_INVALID_SITUATION";
    // Original object relative source line 2972.
    case 0x00003628:
    case 0x80073628: return "ERROR_IPSEC_IKE_DH_FAILURE";
    // Original object relative source line 2973.
    case 0x00003629:
    case 0x80073629: return "ERROR_IPSEC_IKE_INVALID_GROUP";
    // Original object relative source line 2974.
    case 0x0000362A:
    case 0x8007362A: return "ERROR_IPSEC_IKE_ENCRYPT";
    // Original object relative source line 2975.
    case 0x0000362B:
    case 0x8007362B: return "ERROR_IPSEC_IKE_DECRYPT";
    // Original object relative source line 2976.
    case 0x0000362C:
    case 0x8007362C: return "ERROR_IPSEC_IKE_POLICY_MATCH";
    // Original object relative source line 2977.
    case 0x0000362D:
    case 0x8007362D: return "ERROR_IPSEC_IKE_UNSUPPORTED_ID";
    // Original object relative source line 2978.
    case 0x0000362E:
    case 0x8007362E: return "ERROR_IPSEC_IKE_INVALID_HASH";
    // Original object relative source line 2979.
    case 0x0000362F:
    case 0x8007362F: return "ERROR_IPSEC_IKE_INVALID_HASH_ALG";
    // Original object relative source line 2980.
    case 0x00003630:
    case 0x80073630: return "ERROR_IPSEC_IKE_INVALID_HASH_SIZE";
    // Original object relative source line 2981.
    case 0x00003631:
    case 0x80073631: return "ERROR_IPSEC_IKE_INVALID_ENCRYPT_ALG";
    // Original object relative source line 2982.
    case 0x00003632:
    case 0x80073632: return "ERROR_IPSEC_IKE_INVALID_AUTH_ALG";
    // Original object relative source line 2983.
    case 0x00003633:
    case 0x80073633: return "ERROR_IPSEC_IKE_INVALID_SIG";
    // Original object relative source line 2984.
    case 0x00003634:
    case 0x80073634: return "ERROR_IPSEC_IKE_LOAD_FAILED";
    // Original object relative source line 2985.
    case 0x00003635:
    case 0x80073635: return "ERROR_IPSEC_IKE_RPC_DELETE";
    // Original object relative source line 2986.
    case 0x00003636:
    case 0x80073636: return "ERROR_IPSEC_IKE_BENIGN_REINIT";
    // Original object relative source line 2987.
    case 0x00003637:
    case 0x80073637: return "ERROR_IPSEC_IKE_INVALID_RESPONDER_LIFETIME_NOTIFY";
    // Original object relative source line 2988.
    case 0x00003639:
    case 0x80073639: return "ERROR_IPSEC_IKE_INVALID_CERT_KEYLEN";
    // Original object relative source line 2989.
    case 0x0000363A:
    case 0x8007363A: return "ERROR_IPSEC_IKE_MM_LIMIT";
    // Original object relative source line 2990.
    case 0x0000363B:
    case 0x8007363B: return "ERROR_IPSEC_IKE_NEGOTIATION_DISABLED";
    // Original object relative source line 2991.
    case 0x0000363C:
    case 0x8007363C: return "ERROR_IPSEC_IKE_NEG_STATUS_END";
    // Original object relative source line 2996.
    case 0x88760005: return "DDERR_ALREADYINITIALIZED";
    // Original object relative source line 2997.
    case 0x8876000A: return "DDERR_CANNOTATTACHSURFACE";
    // Original object relative source line 2998.
    case 0x88760014: return "DDERR_CANNOTDETACHSURFACE";
    // Original object relative source line 2999.
    case 0x88760028: return "DDERR_CURRENTLYNOTAVAIL";
    // Original object relative source line 3000.
    case 0x88760037: return "DDERR_EXCEPTION";
    // Original object relative source line 3002.
    case 0x8876005A: return "DDERR_HEIGHTALIGN";
    // Original object relative source line 3003.
    case 0x8876005F: return "DDERR_INCOMPATIBLEPRIMARY";
    // Original object relative source line 3004.
    case 0x88760064: return "DDERR_INVALIDCAPS";
    // Original object relative source line 3005.
    case 0x8876006E: return "DDERR_INVALIDCLIPLIST";
    // Original object relative source line 3006.
    case 0x88760078: return "DDERR_INVALIDMODE";
    // Original object relative source line 3007.
    case 0x88760082: return "DDERR_INVALIDOBJECT";
    // Original object relative source line 3009.
    case 0x88760091: return "DDERR_INVALIDPIXELFORMAT";
    // Original object relative source line 3010.
    case 0x88760096: return "DDERR_INVALIDRECT";
    // Original object relative source line 3011.
    case 0x887600A0: return "DDERR_LOCKEDSURFACES";
    // Original object relative source line 3012.
    case 0x887600AA: return "DDERR_NO3D";
    // Original object relative source line 3013.
    case 0x887600B4: return "DDERR_NOALPHAHW";
    // Original object relative source line 3014.
    case 0x887600B5: return "DDERR_NOSTEREOHARDWARE";
    // Original object relative source line 3015.
    case 0x887600B6: return "DDERR_NOSURFACELEFT";
    // Original object relative source line 3016.
    case 0x887600CD: return "DDERR_NOCLIPLIST";
    // Original object relative source line 3017.
    case 0x887600D2: return "DDERR_NOCOLORCONVHW";
    // Original object relative source line 3018.
    case 0x887600D4: return "DDERR_NOCOOPERATIVELEVELSET";
    // Original object relative source line 3019.
    case 0x887600D7: return "DDERR_NOCOLORKEY";
    // Original object relative source line 3020.
    case 0x887600DC: return "DDERR_NOCOLORKEYHW";
    // Original object relative source line 3021.
    case 0x887600DE: return "DDERR_NODIRECTDRAWSUPPORT";
    // Original object relative source line 3022.
    case 0x887600E1: return "DDERR_NOEXCLUSIVEMODE";
    // Original object relative source line 3023.
    case 0x887600E6: return "DDERR_NOFLIPHW";
    // Original object relative source line 3024.
    case 0x887600F0: return "DDERR_NOGDI";
    // Original object relative source line 3025.
    case 0x887600FA: return "DDERR_NOMIRRORHW";
    // Original object relative source line 3026.
    case 0x887600FF: return "DDERR_NOTFOUND";
    // Original object relative source line 3027.
    case 0x88760104: return "DDERR_NOOVERLAYHW";
    // Original object relative source line 3028.
    case 0x8876010E: return "DDERR_OVERLAPPINGRECTS";
    // Original object relative source line 3029.
    case 0x88760118: return "DDERR_NORASTEROPHW";
    // Original object relative source line 3030.
    case 0x88760122: return "DDERR_NOROTATIONHW";
    // Original object relative source line 3031.
    case 0x88760136: return "DDERR_NOSTRETCHHW";
    // Original object relative source line 3032.
    case 0x8876013C: return "DDERR_NOT4BITCOLOR";
    // Original object relative source line 3033.
    case 0x8876013D: return "DDERR_NOT4BITCOLORINDEX";
    // Original object relative source line 3034.
    case 0x88760140: return "DDERR_NOT8BITCOLOR";
    // Original object relative source line 3035.
    case 0x8876014A: return "DDERR_NOTEXTUREHW";
    // Original object relative source line 3036.
    case 0x8876014F: return "DDERR_NOVSYNCHW";
    // Original object relative source line 3037.
    case 0x88760154: return "DDERR_NOZBUFFERHW";
    // Original object relative source line 3038.
    case 0x8876015E: return "DDERR_NOZOVERLAYHW";
    // Original object relative source line 3039.
    case 0x88760168: return "DDERR_OUTOFCAPS";
    // Original object relative source line 3042.
    case 0x8876017E: return "DDERR_OVERLAYCANTCLIP";
    // Original object relative source line 3043.
    case 0x88760180: return "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
    // Original object relative source line 3044.
    case 0x88760183: return "DDERR_PALETTEBUSY";
    // Original object relative source line 3045.
    case 0x88760190: return "DDERR_COLORKEYNOTSET";
    // Original object relative source line 3046.
    case 0x8876019A: return "DDERR_SURFACEALREADYATTACHED";
    // Original object relative source line 3047.
    case 0x887601A4: return "DDERR_SURFACEALREADYDEPENDENT";
    // Original object relative source line 3048.
    case 0x887601AE: return "DDERR_SURFACEBUSY";
    // Original object relative source line 3049.
    case 0x887601B3: return "DDERR_CANTLOCKSURFACE";
    // Original object relative source line 3050.
    case 0x887601B8: return "DDERR_SURFACEISOBSCURED";
    // Original object relative source line 3051.
    case 0x887601C2: return "DDERR_SURFACELOST";
    // Original object relative source line 3052.
    case 0x887601CC: return "DDERR_SURFACENOTATTACHED";
    // Original object relative source line 3053.
    case 0x887601D6: return "DDERR_TOOBIGHEIGHT";
    // Original object relative source line 3054.
    case 0x887601E0: return "DDERR_TOOBIGSIZE";
    // Original object relative source line 3055.
    case 0x887601EA: return "DDERR_TOOBIGWIDTH";
    // Original object relative source line 3057.
    case 0x887601FE: return "DDERR_UNSUPPORTEDFORMAT";
    // Original object relative source line 3058.
    case 0x88760208: return "DDERR_UNSUPPORTEDMASK";
    // Original object relative source line 3059.
    case 0x88760209: return "DDERR_INVALIDSTREAM";
    // Original object relative source line 3060.
    case 0x88760219: return "DDERR_VERTICALBLANKINPROGRESS";
    // Original object relative source line 3061.
    case 0x8876021C: return "DDERR_WASSTILLDRAWING";
    // Original object relative source line 3062.
    case 0x8876021E: return "DDERR_DDSCAPSCOMPLEXREQUIRED";
    // Original object relative source line 3063.
    case 0x88760230: return "DDERR_XALIGN";
    // Original object relative source line 3064.
    case 0x88760231: return "DDERR_INVALIDDIRECTDRAWGUID";
    // Original object relative source line 3065.
    case 0x88760232: return "DDERR_DIRECTDRAWALREADYCREATED";
    // Original object relative source line 3066.
    case 0x88760233: return "DDERR_NODIRECTDRAWHW";
    // Original object relative source line 3067.
    case 0x88760234: return "DDERR_PRIMARYSURFACEALREADYEXISTS";
    // Original object relative source line 3068.
    case 0x88760235: return "DDERR_NOEMULATION";
    // Original object relative source line 3069.
    case 0x88760236: return "DDERR_REGIONTOOSMALL";
    // Original object relative source line 3070.
    case 0x88760237: return "DDERR_CLIPPERISUSINGHWND";
    // Original object relative source line 3071.
    case 0x88760238: return "DDERR_NOCLIPPERATTACHED";
    // Original object relative source line 3072.
    case 0x88760239: return "DDERR_NOHWND";
    // Original object relative source line 3073.
    case 0x8876023A: return "DDERR_HWNDSUBCLASSED";
    // Original object relative source line 3074.
    case 0x8876023B: return "DDERR_HWNDALREADYSET";
    // Original object relative source line 3075.
    case 0x8876023C: return "DDERR_NOPALETTEATTACHED";
    // Original object relative source line 3076.
    case 0x8876023D: return "DDERR_NOPALETTEHW";
    // Original object relative source line 3077.
    case 0x8876023E: return "DDERR_BLTFASTCANTCLIP";
    // Original object relative source line 3078.
    case 0x8876023F: return "DDERR_NOBLTHW";
    // Original object relative source line 3079.
    case 0x88760240: return "DDERR_NODDROPSHW";
    // Original object relative source line 3080.
    case 0x88760241: return "DDERR_OVERLAYNOTVISIBLE";
    // Original object relative source line 3081.
    case 0x88760242: return "DDERR_NOOVERLAYDEST";
    // Original object relative source line 3082.
    case 0x88760243: return "DDERR_INVALIDPOSITION";
    // Original object relative source line 3083.
    case 0x88760244: return "DDERR_NOTAOVERLAYSURFACE";
    // Original object relative source line 3084.
    case 0x88760245: return "DDERR_EXCLUSIVEMODEALREADYSET";
    // Original object relative source line 3085.
    case 0x88760246: return "DDERR_NOTFLIPPABLE";
    // Original object relative source line 3086.
    case 0x88760247: return "DDERR_CANTDUPLICATE";
    // Original object relative source line 3087.
    case 0x88760248: return "DDERR_NOTLOCKED";
    // Original object relative source line 3088.
    case 0x88760249: return "DDERR_CANTCREATEDC";
    // Original object relative source line 3089.
    case 0x8876024A: return "DDERR_NODC";
    // Original object relative source line 3090.
    case 0x8876024B: return "DDERR_WRONGMODE";
    // Original object relative source line 3091.
    case 0x8876024C: return "DDERR_IMPLICITLYCREATED";
    // Original object relative source line 3092.
    case 0x8876024D: return "DDERR_NOTPALETTIZED";
    // Original object relative source line 3093.
    case 0x8876024E: return "DDERR_UNSUPPORTEDMODE";
    // Original object relative source line 3094.
    case 0x8876024F: return "DDERR_NOMIPMAPHW";
    // Original object relative source line 3095.
    case 0x88760250: return "DDERR_INVALIDSURFACETYPE";
    // Original object relative source line 3096.
    case 0x88760258: return "DDERR_NOOPTIMIZEHW";
    // Original object relative source line 3097.
    case 0x88760259: return "DDERR_NOTLOADED";
    // Original object relative source line 3098.
    case 0x8876025A: return "DDERR_NOFOCUSWINDOW";
    // Original object relative source line 3099.
    case 0x8876025B: return "DDERR_NOTONMIPMAPSUBLEVEL";
    // Original object relative source line 3100.
    case 0x8876026C: return "DDERR_DCALREADYCREATED";
    // Original object relative source line 3101.
    case 0x88760276: return "DDERR_NONONLOCALVIDMEM";
    // Original object relative source line 3102.
    case 0x88760280: return "DDERR_CANTPAGELOCK";
    // Original object relative source line 3103.
    case 0x88760294: return "DDERR_CANTPAGEUNLOCK";
    // Original object relative source line 3104.
    case 0x887602A8: return "DDERR_NOTPAGELOCKED";
    // Original object relative source line 3105.
    case 0x887602B2: return "DDERR_MOREDATA";
    // Original object relative source line 3106.
    case 0x887602B3: return "DDERR_EXPIRED";
    // Original object relative source line 3107.
    case 0x887602B4: return "DDERR_TESTFINISHED";
    // Original object relative source line 3108.
    case 0x887602B5: return "DDERR_NEWMODE";
    // Original object relative source line 3109.
    case 0x887602B6: return "DDERR_D3DNOTINITIALIZED";
    // Original object relative source line 3110.
    case 0x887602B7: return "DDERR_VIDEONOTACTIVE";
    // Original object relative source line 3111.
    case 0x887602B8: return "DDERR_NOMONITORINFORMATION";
    // Original object relative source line 3112.
    case 0x887602B9: return "DDERR_NODRIVERSUPPORT";
    // Original object relative source line 3113.
    case 0x887602BB: return "DDERR_DEVICEDOESNTOWNSURFACE";
    // Original object relative source line 3132.
    case 0x80040200: return "DIERR_INSUFFICIENTPRIVS & VFW_E_INVALIDMEDIATYPE";
    // Original object relative source line 3133.
    case 0x80040201: return "DIERR_DEVICEFULL & VFW_E_INVALIDSUBTYPE & DMO_E_INVALIDSTREAMINDEX";
    // Original object relative source line 3134.
    case 0x80040202: return "DIERR_MOREDATA & VFW_E_NEED_OWNER & DMO_E_INVALIDTYPE";
    // Original object relative source line 3135.
    case 0x80040203: return "DIERR_NOTDOWNLOADED & VFW_E_ENUM_OUT_OF_SYNC & DMO_E_TYPE_NOT_SET";
    // Original object relative source line 3136.
    case 0x80040204: return "DIERR_HASEFFECTS & VFW_E_ALREADY_CONNECTED & DMO_E_NOTACCEPTING";
    // Original object relative source line 3137.
    case 0x80040205: return "DIERR_NOTEXCLUSIVEACQUIRED & VFW_E_FILTER_ACTIVE & DMO_E_TYPE_NOT_ACCEPTED";
    // Original object relative source line 3138.
    case 0x80040206: return "DIERR_INCOMPLETEEFFECT & VFW_E_NO_TYPES & DMO_E_NO_MORE_ITEMS";
    // Original object relative source line 3139.
    case 0x80040207: return "DIERR_NOTBUFFERED & VFW_E_NO_ACCEPTABLE_TYPES";
    // Original object relative source line 3140.
    case 0x80040208: return "DIERR_EFFECTPLAYING & VFW_E_INVALID_DIRECTION";
    // Original object relative source line 3141.
    case 0x80040209: return "DIERR_UNPLUGGED & VFW_E_NOT_CONNECTED";
    // Original object relative source line 3142.
    case 0x8004020A: return "DIERR_REPORTFULL & VFW_E_NO_ALLOCATOR";
    // Original object relative source line 3143.
    case 0x8004020B: return "DIERR_MAPFILEFAIL & VFW_E_RUNTIME_ERROR";
    // Original object relative source line 3172.
    case 0x80040300: return "DIERR_DRIVERFIRST";
    // Original object relative source line 3173.
    case 0x80040301: return "DIERR_DRIVERFIRST+1";
    // Original object relative source line 3174.
    case 0x80040302: return "DIERR_DRIVERFIRST+2";
    // Original object relative source line 3175.
    case 0x80040303: return "DIERR_DRIVERFIRST+3";
    // Original object relative source line 3176.
    case 0x80040304: return "DIERR_DRIVERFIRST+4";
    // Original object relative source line 3177.
    case 0x80040305: return "DIERR_DRIVERFIRST+5";
    // Original object relative source line 3178.
    case 0x800403FF: return "DIERR_DRIVERLAST";
    // Original object relative source line 3179.
    case 0x80040400: return "DIERR_INVALIDCLASSINSTALLER";
    // Original object relative source line 3180.
    case 0x80040401: return "DIERR_CANCELLED & MS_E_SAMPLEALLOC";
    // Original object relative source line 3181.
    case 0x80040402: return "DIERR_BADINF & MS_E_PURPOSEID";
    // Original object relative source line 3188.
    case 0x00150005: return "DV_FULLDUPLEX";
    // Original object relative source line 3189.
    case 0x0015000A: return "DV_HALFDUPLEX";
    // Original object relative source line 3190.
    case 0x00150010: return "DV_PENDING";
    // Original object relative source line 3191.
    case 0x8015001E: return "DVERR_BUFFERTOOSMALL";
    // Original object relative source line 3192.
    case 0x8015004A: return "DVERR_EXCEPTION";
    // Original object relative source line 3194.
    case 0x80150078: return "DVERR_INVALIDFLAGS";
    // Original object relative source line 3195.
    case 0x80150082: return "DVERR_INVALIDOBJECT";
    // Original object relative source line 3196.
    case 0x80150087: return "DVERR_INVALIDPLAYER";
    // Original object relative source line 3197.
    case 0x80150091: return "DVERR_INVALIDGROUP";
    // Original object relative source line 3198.
    case 0x80150096: return "DVERR_INVALIDHANDLE";
    // Original object relative source line 3203.
    case 0x8015012C: return "DVERR_SESSIONLOST";
    // Original object relative source line 3204.
    case 0x8015012E: return "DVERR_NOVOICESESSION";
    // Original object relative source line 3205.
    case 0x80150168: return "DVERR_CONNECTIONLOST";
    // Original object relative source line 3206.
    case 0x80150169: return "DVERR_NOTINITIALIZED";
    // Original object relative source line 3207.
    case 0x8015016A: return "DVERR_CONNECTED";
    // Original object relative source line 3208.
    case 0x8015016B: return "DVERR_NOTCONNECTED";
    // Original object relative source line 3209.
    case 0x8015016E: return "DVERR_CONNECTABORTING";
    // Original object relative source line 3210.
    case 0x8015016F: return "DVERR_NOTALLOWED";
    // Original object relative source line 3211.
    case 0x80150170: return "DVERR_INVALIDTARGET";
    // Original object relative source line 3212.
    case 0x80150171: return "DVERR_TRANSPORTNOTHOST";
    // Original object relative source line 3213.
    case 0x80150172: return "DVERR_COMPRESSIONNOTSUPPORTED";
    // Original object relative source line 3214.
    case 0x80150173: return "DVERR_ALREADYPENDING";
    // Original object relative source line 3215.
    case 0x80150174: return "DVERR_SOUNDINITFAILURE";
    // Original object relative source line 3216.
    case 0x80150175: return "DVERR_TIMEOUT";
    // Original object relative source line 3217.
    case 0x80150176: return "DVERR_CONNECTABORTED";
    // Original object relative source line 3218.
    case 0x80150177: return "DVERR_NO3DSOUND";
    // Original object relative source line 3219.
    case 0x80150178: return "DVERR_ALREADYBUFFERED";
    // Original object relative source line 3220.
    case 0x80150179: return "DVERR_NOTBUFFERED";
    // Original object relative source line 3221.
    case 0x8015017A: return "DVERR_HOSTING";
    // Original object relative source line 3222.
    case 0x8015017B: return "DVERR_NOTHOSTING";
    // Original object relative source line 3223.
    case 0x8015017C: return "DVERR_INVALIDDEVICE";
    // Original object relative source line 3224.
    case 0x8015017D: return "DVERR_RECORDSYSTEMERROR";
    // Original object relative source line 3225.
    case 0x8015017E: return "DVERR_PLAYBACKSYSTEMERROR";
    // Original object relative source line 3226.
    case 0x8015017F: return "DVERR_SENDERROR";
    // Original object relative source line 3227.
    case 0x80150180: return "DVERR_USERCANCEL";
    // Original object relative source line 3228.
    case 0x80150183: return "DVERR_RUNSETUP";
    // Original object relative source line 3229.
    case 0x80150184: return "DVERR_INCOMPATIBLEVERSION";
    // Original object relative source line 3230.
    case 0x80150187: return "DVERR_INITIALIZED";
    // Original object relative source line 3232.
    case 0x80150188: return "DVERR_NOTRANSPORT";
    // Original object relative source line 3233.
    case 0x80150189: return "DVERR_NOCALLBACK";
    // Original object relative source line 3234.
    case 0x8015018A: return "DVERR_TRANSPORTNOTINIT";
    // Original object relative source line 3235.
    case 0x8015018B: return "DVERR_TRANSPORTNOSESSION";
    // Original object relative source line 3236.
    case 0x8015018C: return "DVERR_TRANSPORTNOPLAYER";
    // Original object relative source line 3237.
    case 0x8015018D: return "DVERR_USERBACK";
    // Original object relative source line 3238.
    case 0x8015018E: return "DVERR_NORECVOLAVAILABLE";
    // Original object relative source line 3239.
    case 0x8015018F: return "DVERR_INVALIDBUFFER";
    // Original object relative source line 3240.
    case 0x80150190: return "DVERR_LOCKEDBUFFER";
    // Original object relative source line 3246.
    case 0x80158030: return "DPNERR_ABORTED";
    // Original object relative source line 3247.
    case 0x80158040: return "DPNERR_ADDRESSING";
    // Original object relative source line 3248.
    case 0x80158050: return "DPNERR_ALREADYCLOSING";
    // Original object relative source line 3249.
    case 0x80158060: return "DPNERR_ALREADYCONNECTED";
    // Original object relative source line 3250.
    case 0x80158070: return "DPNERR_ALREADYDISCONNECTING";
    // Original object relative source line 3251.
    case 0x80158080: return "DPNERR_ALREADYINITIALIZED";
    // Original object relative source line 3252.
    case 0x80158090: return "DPNERR_ALREADYREGISTERED";
    // Original object relative source line 3253.
    case 0x80158100: return "DPNERR_BUFFERTOOSMALL";
    // Original object relative source line 3254.
    case 0x80158110: return "DPNERR_CANNOTCANCEL";
    // Original object relative source line 3255.
    case 0x80158120: return "DPNERR_CANTCREATEGROUP";
    // Original object relative source line 3256.
    case 0x80158130: return "DPNERR_CANTCREATEPLAYER";
    // Original object relative source line 3257.
    case 0x80158140: return "DPNERR_CANTLAUNCHAPPLICATION";
    // Original object relative source line 3258.
    case 0x80158150: return "DPNERR_CONNECTING";
    // Original object relative source line 3259.
    case 0x80158160: return "DPNERR_CONNECTIONLOST";
    // Original object relative source line 3260.
    case 0x80158170: return "DPNERR_CONVERSION";
    // Original object relative source line 3261.
    case 0x80158175: return "DPNERR_DATATOOLARGE";
    // Original object relative source line 3262.
    case 0x80158180: return "DPNERR_DOESNOTEXIST";
    // Original object relative source line 3263.
    case 0x80158185: return "DPNERR_DPNSVRNOTAVAILABLE";
    // Original object relative source line 3264.
    case 0x80158190: return "DPNERR_DUPLICATECOMMAND";
    // Original object relative source line 3265.
    case 0x80158200: return "DPNERR_ENDPOINTNOTRECEIVING";
    // Original object relative source line 3266.
    case 0x80158210: return "DPNERR_ENUMQUERYTOOLARGE";
    // Original object relative source line 3267.
    case 0x80158220: return "DPNERR_ENUMRESPONSETOOLARGE";
    // Original object relative source line 3268.
    case 0x80158230: return "DPNERR_EXCEPTION";
    // Original object relative source line 3270.
    case 0x80158240: return "DPNERR_GROUPNOTEMPTY";
    // Original object relative source line 3271.
    case 0x80158250: return "DPNERR_HOSTING";
    // Original object relative source line 3272.
    case 0x80158260: return "DPNERR_HOSTREJECTEDCONNECTION";
    // Original object relative source line 3273.
    case 0x80158270: return "DPNERR_HOSTTERMINATEDSESSION";
    // Original object relative source line 3274.
    case 0x80158280: return "DPNERR_INCOMPLETEADDRESS";
    // Original object relative source line 3275.
    case 0x80158290: return "DPNERR_INVALIDADDRESSFORMAT";
    // Original object relative source line 3276.
    case 0x80158300: return "DPNERR_INVALIDAPPLICATION";
    // Original object relative source line 3277.
    case 0x80158310: return "DPNERR_INVALIDCOMMAND";
    // Original object relative source line 3278.
    case 0x80158320: return "DPNERR_INVALIDDEVICEADDRESS";
    // Original object relative source line 3279.
    case 0x80158330: return "DPNERR_INVALIDENDPOINT";
    // Original object relative source line 3280.
    case 0x80158340: return "DPNERR_INVALIDFLAGS";
    // Original object relative source line 3281.
    case 0x80158350: return "DPNERR_INVALIDGROUP";
    // Original object relative source line 3282.
    case 0x80158360: return "DPNERR_INVALIDHANDLE";
    // Original object relative source line 3283.
    case 0x80158370: return "DPNERR_INVALIDHOSTADDRESS";
    // Original object relative source line 3284.
    case 0x80158380: return "DPNERR_INVALIDINSTANCE";
    // Original object relative source line 3285.
    case 0x80158390: return "DPNERR_INVALIDINTERFACE";
    // Original object relative source line 3286.
    case 0x80158400: return "DPNERR_INVALIDOBJECT";
    // Original object relative source line 3288.
    case 0x80158410: return "DPNERR_INVALIDPASSWORD";
    // Original object relative source line 3289.
    case 0x80158420: return "DPNERR_INVALIDPLAYER";
    // Original object relative source line 3291.
    case 0x80158430: return "DPNERR_INVALIDPRIORITY";
    // Original object relative source line 3292.
    case 0x80158440: return "DPNERR_INVALIDSTRING";
    // Original object relative source line 3293.
    case 0x80158450: return "DPNERR_INVALIDURL";
    // Original object relative source line 3294.
    case 0x80158460: return "DPNERR_INVALIDVERSION";
    // Original object relative source line 3295.
    case 0x80158470: return "DPNERR_NOCAPS";
    // Original object relative source line 3296.
    case 0x80158480: return "DPNERR_NOCONNECTION";
    // Original object relative source line 3297.
    case 0x80158490: return "DPNERR_NOHOSTPLAYER";
    // Original object relative source line 3299.
    case 0x80158500: return "DPNERR_NOMOREADDRESSCOMPONENTS";
    // Original object relative source line 3300.
    case 0x80158510: return "DPNERR_NORESPONSE";
    // Original object relative source line 3301.
    case 0x80158520: return "DPNERR_NOTALLOWED";
    // Original object relative source line 3302.
    case 0x80158530: return "DPNERR_NOTHOST";
    // Original object relative source line 3303.
    case 0x80158540: return "DPNERR_NOTREADY";
    // Original object relative source line 3304.
    case 0x80158550: return "DPNERR_NOTREGISTERED";
    // Original object relative source line 3307.
    case 0x80158560: return "DPNERR_PLAYERALREADYINGROUP";
    // Original object relative source line 3308.
    case 0x80158570: return "DPNERR_PLAYERLOST";
    // Original object relative source line 3309.
    case 0x80158580: return "DPNERR_PLAYERNOTINGROUP";
    // Original object relative source line 3310.
    case 0x80158590: return "DPNERR_PLAYERNOTREACHABLE";
    // Original object relative source line 3311.
    case 0x80158600: return "DPNERR_SENDTOOLARGE";
    // Original object relative source line 3312.
    case 0x80158610: return "DPNERR_SESSIONFULL";
    // Original object relative source line 3313.
    case 0x80158620: return "DPNERR_TABLEFULL";
    // Original object relative source line 3314.
    case 0x80158630: return "DPNERR_TIMEDOUT";
    // Original object relative source line 3315.
    case 0x80158640: return "DPNERR_UNINITIALIZED";
    // Original object relative source line 3317.
    case 0x80158650: return "DPNERR_USERCANCEL";
    // Original object relative source line 3325.
    case 0x88760352: return "DXFILEERR_BADOBJECT";
    // Original object relative source line 3326.
    case 0x88760353: return "DXFILEERR_BADVALUE";
    // Original object relative source line 3327.
    case 0x88760354: return "DXFILEERR_BADTYPE";
    // Original object relative source line 3328.
    case 0x88760355: return "DXFILEERR_BADSTREAMHANDLE";
    // Original object relative source line 3329.
    case 0x88760356: return "DXFILEERR_BADALLOC";
    // Original object relative source line 3330.
    case 0x88760357: return "DXFILEERR_NOTFOUND";
    // Original object relative source line 3331.
    case 0x88760358: return "DXFILEERR_NOTDONEYET";
    // Original object relative source line 3332.
    case 0x88760359: return "DXFILEERR_FILENOTFOUND";
    // Original object relative source line 3333.
    case 0x8876035A: return "DXFILEERR_RESOURCENOTFOUND";
    // Original object relative source line 3334.
    case 0x8876035B: return "DXFILEERR_URLNOTFOUND";
    // Original object relative source line 3335.
    case 0x8876035C: return "DXFILEERR_BADRESOURCE";
    // Original object relative source line 3336.
    case 0x8876035D: return "DXFILEERR_BADFILETYPE";
    // Original object relative source line 3337.
    case 0x8876035E: return "DXFILEERR_BADFILEVERSION";
    // Original object relative source line 3338.
    case 0x8876035F: return "DXFILEERR_BADFILEFLOATSIZE";
    // Original object relative source line 3339.
    case 0x88760360: return "DXFILEERR_BADFILECOMPRESSIONTYPE";
    // Original object relative source line 3340.
    case 0x88760361: return "DXFILEERR_BADFILE";
    // Original object relative source line 3341.
    case 0x88760362: return "DXFILEERR_PARSEERROR";
    // Original object relative source line 3342.
    case 0x88760363: return "DXFILEERR_NOTEMPLATE";
    // Original object relative source line 3343.
    case 0x88760364: return "DXFILEERR_BADARRAYSIZE";
    // Original object relative source line 3344.
    case 0x88760365: return "DXFILEERR_BADDATAREFERENCE";
    // Original object relative source line 3345.
    case 0x88760366: return "DXFILEERR_INTERNALERROR";
    // Original object relative source line 3346.
    case 0x88760367: return "DXFILEERR_NOMOREOBJECTS";
    // Original object relative source line 3347.
    case 0x88760368: return "DXFILEERR_BADINTRINSICS";
    // Original object relative source line 3348.
    case 0x88760369: return "DXFILEERR_NOMORESTREAMHANDLES";
    // Original object relative source line 3349.
    case 0x8876036A: return "DXFILEERR_NOMOREDATA";
    // Original object relative source line 3350.
    case 0x8876036B: return "DXFILEERR_BADCACHEFILE";
    // Original object relative source line 3351.
    case 0x8876036C: return "DXFILEERR_NOINTERNET";
    // Original object relative source line 3358.
    case 0x88760818: return "D3DERR_WRONGTEXTUREFORMAT";
    // Original object relative source line 3359.
    case 0x88760819: return "D3DERR_UNSUPPORTEDCOLOROPERATION";
    // Original object relative source line 3360.
    case 0x8876081A: return "D3DERR_UNSUPPORTEDCOLORARG";
    // Original object relative source line 3361.
    case 0x8876081B: return "D3DERR_UNSUPPORTEDALPHAOPERATION";
    // Original object relative source line 3362.
    case 0x8876081C: return "D3DERR_UNSUPPORTEDALPHAARG";
    // Original object relative source line 3363.
    case 0x8876081D: return "D3DERR_TOOMANYOPERATIONS";
    // Original object relative source line 3364.
    case 0x8876081E: return "D3DERR_CONFLICTINGTEXTUREFILTER";
    // Original object relative source line 3365.
    case 0x8876081F: return "D3DERR_UNSUPPORTEDFACTORVALUE";
    // Original object relative source line 3366.
    case 0x88760821: return "D3DERR_CONFLICTINGRENDERSTATE";
    // Original object relative source line 3367.
    case 0x88760822: return "D3DERR_UNSUPPORTEDTEXTUREFILTER";
    // Original object relative source line 3368.
    case 0x88760826: return "D3DERR_CONFLICTINGTEXTUREPALETTE";
    // Original object relative source line 3369.
    case 0x88760827: return "D3DERR_DRIVERINTERNALERROR";
    // Original object relative source line 3370.
    case 0x88760866: return "D3DERR_NOTFOUND";
    // Original object relative source line 3371.
    case 0x88760867: return "D3DERR_MOREDATA";
    // Original object relative source line 3372.
    case 0x88760868: return "D3DERR_DEVICELOST";
    // Original object relative source line 3373.
    case 0x88760869: return "D3DERR_DEVICENOTRESET";
    // Original object relative source line 3374.
    case 0x8876086A: return "D3DERR_NOTAVAILABLE";
    // Original object relative source line 3375.
    case 0x8876017C: return "D3DERR_OUTOFVIDEOMEMORY";
    // Original object relative source line 3376.
    case 0x8876086B: return "D3DERR_INVALIDDEVICE";
    // Original object relative source line 3377.
    case 0x8876086C: return "D3DERR_INVALIDCALL";
    // Original object relative source line 3378.
    case 0x8876086D: return "D3DERR_DRIVERINVALIDCALL";
    // Original object relative source line 3385.
    case 0x0876086F: return "D3DOK_NOAUTOGEN";
    // Original object relative source line 3391.
    case 0x88760B54: return "D3DXERR_CANNOTMODIFYINDEXBUFFER";
    // Original object relative source line 3392.
    case 0x88760B55: return "D3DXERR_INVALIDMESH";
    // Original object relative source line 3393.
    case 0x88760B56: return "D3DXERR_CANNOTATTRSORT";
    // Original object relative source line 3394.
    case 0x88760B57: return "D3DXERR_SKINNINGNOTSUPPORTED";
    // Original object relative source line 3395.
    case 0x88760B58: return "D3DXERR_TOOMANYINFLUENCES";
    // Original object relative source line 3396.
    case 0x88760B59: return "D3DXERR_INVALIDDATA";
    // Original object relative source line 3397.
    case 0x88760B5A: return "D3DXERR_LOADEDMESHASNODATA";
    // Original object relative source line 3398.
    case 0x88760B5B: return "D3DXERR_DUPLICATENAMEDFRAGMENT";
    // Original object relative source line 3399.
    case 0x88760B5C: return "D3DXERR_CANNOTREMOVELASTITEM";
    // Original object relative source line 3405.
    case 0xC8770BB8: return "D3DXERR_NOMEMORY";
    // Original object relative source line 3406.
    case 0xC8770BB9: return "D3DXERR_NULLPOINTER";
    // Original object relative source line 3407.
    case 0xC8770BBA: return "D3DXERR_INVALIDD3DXDEVICEINDEX";
    // Original object relative source line 3408.
    case 0xC8770BBB: return "D3DXERR_NODIRECTDRAWAVAILABLE";
    // Original object relative source line 3409.
    case 0xC8770BBC: return "D3DXERR_NODIRECT3DAVAILABLE";
    // Original object relative source line 3410.
    case 0xC8770BBD: return "D3DXERR_NODIRECT3DDEVICEAVAILABLE";
    // Original object relative source line 3411.
    case 0xC8770BBE: return "D3DXERR_NOPRIMARYAVAILABLE";
    // Original object relative source line 3412.
    case 0xC8770BBF: return "D3DXERR_NOZBUFFERAVAILABLE";
    // Original object relative source line 3413.
    case 0xC8770BC0: return "D3DXERR_NOBACKBUFFERAVAILABLE";
    // Original object relative source line 3414.
    case 0xC8770BC1: return "D3DXERR_COULDNTUPDATECAPS";
    // Original object relative source line 3415.
    case 0xC8770BC2: return "D3DXERR_NOZBUFFER";
    // Original object relative source line 3416.
    case 0xC8770BC3: return "D3DXERR_INVALIDMODE";
    // Original object relative source line 3417.
    case 0xC8770BC4: return "D3DXERR_INVALIDPARAMETER";
    // Original object relative source line 3418.
    case 0xC8770BC5: return "D3DXERR_INITFAILED";
    // Original object relative source line 3419.
    case 0xC8770BC6: return "D3DXERR_STARTUPFAILED";
    // Original object relative source line 3420.
    case 0xC8770BC7: return "D3DXERR_D3DXNOTSTARTEDYET";
    // Original object relative source line 3421.
    case 0xC8770BC8: return "D3DXERR_NOTINITIALIZED";
    // Original object relative source line 3422.
    case 0xC8770BC9: return "D3DXERR_FAILEDDRAWTEXT";
    // Original object relative source line 3423.
    case 0xC8770BCA: return "D3DXERR_BADD3DXCONTEXT";
    // Original object relative source line 3424.
    case 0xC8770BCB: return "D3DXERR_CAPSNOTSUPPORTED";
    // Original object relative source line 3425.
    case 0xC8770BCC: return "D3DXERR_UNSUPPORTEDFILEFORMAT";
    // Original object relative source line 3426.
    case 0xC8770BCD: return "D3DXERR_IFLERROR";
    // Original object relative source line 3427.
    case 0xC8770BCE: return "D3DXERR_FAILEDGETCAPS";
    // Original object relative source line 3428.
    case 0xC8770BCF: return "D3DXERR_CANNOTRESIZEFULLSCREEN";
    // Original object relative source line 3429.
    case 0xC8770BD0: return "D3DXERR_CANNOTRESIZENONWINDOWED";
    // Original object relative source line 3430.
    case 0xC8770BD1: return "D3DXERR_FRONTBUFFERALREADYEXISTS";
    // Original object relative source line 3431.
    case 0xC8770BD2: return "D3DXERR_FULLSCREENPRIMARYEXISTS";
    // Original object relative source line 3432.
    case 0xC8770BD3: return "D3DXERR_GETDCFAILED";
    // Original object relative source line 3433.
    case 0xC8770BD4: return "D3DXERR_BITBLTFAILED";
    // Original object relative source line 3434.
    case 0xC8770BD5: return "D3DXERR_NOTEXTURE";
    // Original object relative source line 3435.
    case 0xC8770BD6: return "D3DXERR_MIPLEVELABSENT";
    // Original object relative source line 3436.
    case 0xC8770BD7: return "D3DXERR_SURFACENOTPALETTED";
    // Original object relative source line 3437.
    case 0xC8770BD8: return "D3DXERR_ENUMFORMATSFAILED";
    // Original object relative source line 3438.
    case 0xC8770BD9: return "D3DXERR_COLORDEPTHTOOLOW";
    // Original object relative source line 3439.
    case 0xC8770BDA: return "D3DXERR_INVALIDFILEFORMAT";
    // Original object relative source line 3440.
    case 0xC8770BDB: return "D3DXERR_NOMATCHFOUND";
    // Original object relative source line 3446.
    case 0x88760384: return "D3DXFERR_BADOBJECT";
    // Original object relative source line 3447.
    case 0x88760385: return "D3DXFERR_BADVALUE";
    // Original object relative source line 3448.
    case 0x88760386: return "D3DXFERR_BADTYPE";
    // Original object relative source line 3449.
    case 0x88760387: return "D3DXFERR_NOTFOUND";
    // Original object relative source line 3450.
    case 0x88760388: return "D3DXFERR_NOTDONEYET";
    // Original object relative source line 3451.
    case 0x88760389: return "D3DXFERR_FILENOTFOUND";
    // Original object relative source line 3452.
    case 0x8876038A: return "D3DXFERR_RESOURCENOTFOUND";
    // Original object relative source line 3453.
    case 0x8876038B: return "D3DXFERR_BADRESOURCE";
    // Original object relative source line 3454.
    case 0x8876038C: return "D3DXFERR_BADFILETYPE";
    // Original object relative source line 3455.
    case 0x8876038D: return "D3DXFERR_BADFILEVERSION";
    // Original object relative source line 3456.
    case 0x8876038E: return "D3DXFERR_BADFILEFLOATSIZE";
    // Original object relative source line 3457.
    case 0x8876038F: return "D3DXFERR_BADFILE";
    // Original object relative source line 3458.
    case 0x88760390: return "D3DXFERR_PARSEERROR";
    // Original object relative source line 3459.
    case 0x88760391: return "D3DXFERR_BADARRAYSIZE";
    // Original object relative source line 3460.
    case 0x88760392: return "D3DXFERR_BADDATAREFERENCE";
    // Original object relative source line 3461.
    case 0x88760393: return "D3DXFERR_NOMOREOBJECTS";
    // Original object relative source line 3462.
    case 0x88760394: return "D3DXFERR_NOMOREDATA";
    // Original object relative source line 3463.
    case 0x88760395: return "D3DXFERR_BADCACHEFILE";
    // Original object relative source line 3470.
    case 0x0878000A: return "DS_NO_VIRTUALIZATION";
    // Original object relative source line 3472.
    case 0x8878000A: return "DSERR_ALLOCATED";
    // Original object relative source line 3473.
    case 0x8878001E: return "DSERR_CONTROLUNAVAIL";
    // Original object relative source line 3475.
    case 0x88780032: return "DSERR_INVALIDCALL";
    // Original object relative source line 3477.
    case 0x88780046: return "DSERR_PRIOLEVELNEEDED";
    // Original object relative source line 3479.
    case 0x88780064: return "DSERR_BADFORMAT";
    // Original object relative source line 3481.
    case 0x88780078: return "DSERR_NODRIVER";
    // Original object relative source line 3482.
    case 0x88780082: return "DSERR_ALREADYINITIALIZED";
    // Original object relative source line 3484.
    case 0x88780096: return "DSERR_BUFFERLOST";
    // Original object relative source line 3485.
    case 0x887800A0: return "DSERR_OTHERAPPHASPRIO";
    // Original object relative source line 3486.
    case 0x887800AA: return "DSERR_UNINITIALIZED";
    // Original object relative source line 3489.
    case 0x887800B4: return "DSERR_BUFFERTOOSMALL";
    // Original object relative source line 3490.
    case 0x887800BE: return "DSERR_DS8_REQUIRED";
    // Original object relative source line 3491.
    case 0x887800C8: return "DSERR_SENDLOOP";
    // Original object relative source line 3492.
    case 0x887800D2: return "DSERR_BADSENDBUFFERGUID";
    // Original object relative source line 3493.
    case 0x88781161: return "DSERR_OBJECTNOTFOUND";
    // Original object relative source line 3498.
    case 0x08781091: return "DMUS_S_PARTIALLOAD";
    // Original object relative source line 3499.
    case 0x08781092: return "DMUS_S_PARTIALDOWNLOAD";
    // Original object relative source line 3500.
    case 0x08781200: return "DMUS_S_REQUEUE";
    // Original object relative source line 3501.
    case 0x08781201: return "DMUS_S_FREE";
    // Original object relative source line 3502.
    case 0x08781202: return "DMUS_S_END";
    // Original object relative source line 3503.
    case 0x08781210: return "DMUS_S_STRING_TRUNCATED";
    // Original object relative source line 3504.
    case 0x08781211: return "DMUS_S_LAST_TOOL";
    // Original object relative source line 3505.
    case 0x08781212: return "DMUS_S_OVER_CHORD";
    // Original object relative source line 3506.
    case 0x08781213: return "DMUS_S_UP_OCTAVE";
    // Original object relative source line 3507.
    case 0x08781214: return "DMUS_S_DOWN_OCTAVE";
    // Original object relative source line 3508.
    case 0x08781215: return "DMUS_S_NOBUFFERCONTROL";
    // Original object relative source line 3509.
    case 0x08781216: return "DMUS_S_GARBAGE_COLLECTED";
    // Original object relative source line 3510.
    case 0x88781101: return "DMUS_E_DRIVER_FAILED";
    // Original object relative source line 3511.
    case 0x88781102: return "DMUS_E_PORTS_OPEN";
    // Original object relative source line 3512.
    case 0x88781103: return "DMUS_E_DEVICE_IN_USE";
    // Original object relative source line 3513.
    case 0x88781104: return "DMUS_E_INSUFFICIENTBUFFER";
    // Original object relative source line 3514.
    case 0x88781105: return "DMUS_E_BUFFERNOTSET";
    // Original object relative source line 3515.
    case 0x88781106: return "DMUS_E_BUFFERNOTAVAILABLE";
    // Original object relative source line 3516.
    case 0x88781108: return "DMUS_E_NOTADLSCOL";
    // Original object relative source line 3517.
    case 0x88781109: return "DMUS_E_INVALIDOFFSET";
    // Original object relative source line 3518.
    case 0x88781111: return "DMUS_E_ALREADY_LOADED";
    // Original object relative source line 3519.
    case 0x88781113: return "DMUS_E_INVALIDPOS";
    // Original object relative source line 3520.
    case 0x88781114: return "DMUS_E_INVALIDPATCH";
    // Original object relative source line 3521.
    case 0x88781115: return "DMUS_E_CANNOTSEEK";
    // Original object relative source line 3522.
    case 0x88781116: return "DMUS_E_CANNOTWRITE";
    // Original object relative source line 3523.
    case 0x88781117: return "DMUS_E_CHUNKNOTFOUND";
    // Original object relative source line 3524.
    case 0x88781119: return "DMUS_E_INVALID_DOWNLOADID";
    // Original object relative source line 3525.
    case 0x88781120: return "DMUS_E_NOT_DOWNLOADED_TO_PORT";
    // Original object relative source line 3526.
    case 0x88781121: return "DMUS_E_ALREADY_DOWNLOADED";
    // Original object relative source line 3527.
    case 0x88781122: return "DMUS_E_UNKNOWN_PROPERTY";
    // Original object relative source line 3528.
    case 0x88781123: return "DMUS_E_SET_UNSUPPORTED";
    // Original object relative source line 3529.
    case 0x88781124: return "DMUS_E_GET_UNSUPPORTED";
    // Original object relative source line 3530.
    case 0x88781125: return "DMUS_E_NOTMONO";
    // Original object relative source line 3531.
    case 0x88781126: return "DMUS_E_BADARTICULATION";
    // Original object relative source line 3532.
    case 0x88781127: return "DMUS_E_BADINSTRUMENT";
    // Original object relative source line 3533.
    case 0x88781128: return "DMUS_E_BADWAVELINK";
    // Original object relative source line 3534.
    case 0x88781129: return "DMUS_E_NOARTICULATION";
    // Original object relative source line 3535.
    case 0x8878112A: return "DMUS_E_NOTPCM";
    // Original object relative source line 3536.
    case 0x8878112B: return "DMUS_E_BADWAVE";
    // Original object relative source line 3537.
    case 0x8878112C: return "DMUS_E_BADOFFSETTABLE";
    // Original object relative source line 3538.
    case 0x8878112D: return "DMUS_E_UNKNOWNDOWNLOAD";
    // Original object relative source line 3539.
    case 0x8878112E: return "DMUS_E_NOSYNTHSINK";
    // Original object relative source line 3540.
    case 0x8878112F: return "DMUS_E_ALREADYOPEN";
    // Original object relative source line 3541.
    case 0x88781130: return "DMUS_E_ALREADYCLOSED";
    // Original object relative source line 3542.
    case 0x88781131: return "DMUS_E_SYNTHNOTCONFIGURED";
    // Original object relative source line 3543.
    case 0x88781132: return "DMUS_E_SYNTHACTIVE";
    // Original object relative source line 3544.
    case 0x88781133: return "DMUS_E_CANNOTREAD";
    // Original object relative source line 3545.
    case 0x88781134: return "DMUS_E_DMUSIC_RELEASED";
    // Original object relative source line 3546.
    case 0x88781135: return "DMUS_E_BUFFER_EMPTY";
    // Original object relative source line 3547.
    case 0x88781136: return "DMUS_E_BUFFER_FULL";
    // Original object relative source line 3548.
    case 0x88781137: return "DMUS_E_PORT_NOT_CAPTURE";
    // Original object relative source line 3549.
    case 0x88781138: return "DMUS_E_PORT_NOT_RENDER";
    // Original object relative source line 3550.
    case 0x88781139: return "DMUS_E_DSOUND_NOT_SET";
    // Original object relative source line 3551.
    case 0x8878113A: return "DMUS_E_ALREADY_ACTIVATED";
    // Original object relative source line 3552.
    case 0x8878113B: return "DMUS_E_INVALIDBUFFER";
    // Original object relative source line 3553.
    case 0x8878113C: return "DMUS_E_WAVEFORMATNOTSUPPORTED";
    // Original object relative source line 3554.
    case 0x8878113D: return "DMUS_E_SYNTHINACTIVE";
    // Original object relative source line 3555.
    case 0x8878113E: return "DMUS_E_DSOUND_ALREADY_SET";
    // Original object relative source line 3556.
    case 0x8878113F: return "DMUS_E_INVALID_EVENT";
    // Original object relative source line 3557.
    case 0x88781150: return "DMUS_E_UNSUPPORTED_STREAM";
    // Original object relative source line 3558.
    case 0x88781151: return "DMUS_E_ALREADY_INITED";
    // Original object relative source line 3559.
    case 0x88781152: return "DMUS_E_INVALID_BAND";
    // Original object relative source line 3560.
    case 0x88781155: return "DMUS_E_TRACK_HDR_NOT_FIRST_CK";
    // Original object relative source line 3561.
    case 0x88781156: return "DMUS_E_TOOL_HDR_NOT_FIRST_CK";
    // Original object relative source line 3562.
    case 0x88781157: return "DMUS_E_INVALID_TRACK_HDR";
    // Original object relative source line 3563.
    case 0x88781158: return "DMUS_E_INVALID_TOOL_HDR";
    // Original object relative source line 3564.
    case 0x88781159: return "DMUS_E_ALL_TOOLS_FAILED";
    // Original object relative source line 3565.
    case 0x88781160: return "DMUS_E_ALL_TRACKS_FAILED";
    // Original object relative source line 3567.
    case 0x88781162: return "DMUS_E_NOT_INIT";
    // Original object relative source line 3568.
    case 0x88781163: return "DMUS_E_TYPE_DISABLED";
    // Original object relative source line 3569.
    case 0x88781164: return "DMUS_E_TYPE_UNSUPPORTED";
    // Original object relative source line 3570.
    case 0x88781165: return "DMUS_E_TIME_PAST";
    // Original object relative source line 3571.
    case 0x88781166: return "DMUS_E_TRACK_NOT_FOUND";
    // Original object relative source line 3572.
    case 0x88781167: return "DMUS_E_TRACK_NO_CLOCKTIME_SUPPORT";
    // Original object relative source line 3573.
    case 0x88781170: return "DMUS_E_NO_MASTER_CLOCK";
    // Original object relative source line 3574.
    case 0x88781180: return "DMUS_E_LOADER_NOCLASSID";
    // Original object relative source line 3575.
    case 0x88781181: return "DMUS_E_LOADER_BADPATH";
    // Original object relative source line 3576.
    case 0x88781182: return "DMUS_E_LOADER_FAILEDOPEN";
    // Original object relative source line 3577.
    case 0x88781183: return "DMUS_E_LOADER_FORMATNOTSUPPORTED";
    // Original object relative source line 3578.
    case 0x88781184: return "DMUS_E_LOADER_FAILEDCREATE";
    // Original object relative source line 3579.
    case 0x88781185: return "DMUS_E_LOADER_OBJECTNOTFOUND";
    // Original object relative source line 3580.
    case 0x88781186: return "DMUS_E_LOADER_NOFILENAME";
    // Original object relative source line 3581.
    case 0x88781200: return "DMUS_E_INVALIDFILE";
    // Original object relative source line 3582.
    case 0x88781201: return "DMUS_E_ALREADY_EXISTS";
    // Original object relative source line 3583.
    case 0x88781202: return "DMUS_E_OUT_OF_RANGE";
    // Original object relative source line 3584.
    case 0x88781203: return "DMUS_E_SEGMENT_INIT_FAILED";
    // Original object relative source line 3585.
    case 0x88781204: return "DMUS_E_ALREADY_SENT";
    // Original object relative source line 3586.
    case 0x88781205: return "DMUS_E_CANNOT_FREE";
    // Original object relative source line 3587.
    case 0x88781206: return "DMUS_E_CANNOT_OPEN_PORT";
    // Original object relative source line 3588.
    case 0x88781207: return "DMUS_E_CANNOT_CONVERT";
    // Original object relative source line 3589.
    case 0x88781210: return "DMUS_E_DESCEND_CHUNK_FAIL";
    // Original object relative source line 3590.
    case 0x88781211: return "DMUS_E_NOT_LOADED";
    // Original object relative source line 3591.
    case 0x88781213: return "DMUS_E_SCRIPT_LANGUAGE_INCOMPATIBLE";
    // Original object relative source line 3592.
    case 0x88781214: return "DMUS_E_SCRIPT_UNSUPPORTED_VARTYPE";
    // Original object relative source line 3593.
    case 0x88781215: return "DMUS_E_SCRIPT_ERROR_IN_SCRIPT";
    // Original object relative source line 3594.
    case 0x88781216: return "DMUS_E_SCRIPT_CANTLOAD_OLEAUT32";
    // Original object relative source line 3595.
    case 0x88781217: return "DMUS_E_SCRIPT_LOADSCRIPT_ERROR";
    // Original object relative source line 3596.
    case 0x88781218: return "DMUS_E_SCRIPT_INVALID_FILE";
    // Original object relative source line 3597.
    case 0x88781219: return "DMUS_E_INVALID_SCRIPTTRACK";
    // Original object relative source line 3598.
    case 0x8878121A: return "DMUS_E_SCRIPT_VARIABLE_NOT_FOUND";
    // Original object relative source line 3599.
    case 0x8878121B: return "DMUS_E_SCRIPT_ROUTINE_NOT_FOUND";
    // Original object relative source line 3600.
    case 0x8878121C: return "DMUS_E_SCRIPT_CONTENT_READONLY";
    // Original object relative source line 3601.
    case 0x8878121D: return "DMUS_E_SCRIPT_NOT_A_REFERENCE";
    // Original object relative source line 3602.
    case 0x8878121E: return "DMUS_E_SCRIPT_VALUE_NOT_SUPPORTED";
    // Original object relative source line 3603.
    case 0x88781220: return "DMUS_E_INVALID_SEGMENTTRIGGERTRACK";
    // Original object relative source line 3604.
    case 0x88781221: return "DMUS_E_INVALID_LYRICSTRACK";
    // Original object relative source line 3605.
    case 0x88781222: return "DMUS_E_INVALID_PARAMCONTROLTRACK";
    // Original object relative source line 3606.
    case 0x88781223: return "DMUS_E_AUDIOVBSCRIPT_SYNTAXERROR";
    // Original object relative source line 3607.
    case 0x88781224: return "DMUS_E_AUDIOVBSCRIPT_RUNTIMEERROR";
    // Original object relative source line 3608.
    case 0x88781225: return "DMUS_E_AUDIOVBSCRIPT_OPERATIONFAILURE";
    // Original object relative source line 3609.
    case 0x88781226: return "DMUS_E_AUDIOPATHS_NOT_VALID";
    // Original object relative source line 3610.
    case 0x88781227: return "DMUS_E_AUDIOPATHS_IN_USE";
    // Original object relative source line 3611.
    case 0x88781228: return "DMUS_E_NO_AUDIOPATH_CONFIG";
    // Original object relative source line 3612.
    case 0x88781229: return "DMUS_E_AUDIOPATH_INACTIVE";
    // Original object relative source line 3613.
    case 0x8878122A: return "DMUS_E_AUDIOPATH_NOBUFFER";
    // Original object relative source line 3614.
    case 0x8878122B: return "DMUS_E_AUDIOPATH_NOPORT";
    // Original object relative source line 3615.
    case 0x8878122C: return "DMUS_E_NO_AUDIOPATH";
    // Original object relative source line 3616.
    case 0x8878122D: return "DMUS_E_INVALIDCHUNK";
    // Original object relative source line 3617.
    case 0x8878122E: return "DMUS_E_AUDIOPATH_NOGLOBALFXBUFFER";
    // Original object relative source line 3618.
    case 0x8878122F: return "DMUS_E_INVALID_CONTAINER_OBJECT";
    // Original object relative source line 3635.
    case 0x8004020C: return "VFW_E_BUFFER_NOTSET";
    // Original object relative source line 3636.
    case 0x8004020D: return "VFW_E_BUFFER_OVERFLOW";
    // Original object relative source line 3637.
    case 0x8004020E: return "VFW_E_BADALIGN";
    // Original object relative source line 3638.
    case 0x8004020F: return "VFW_E_ALREADY_COMMITTED";
    // Original object relative source line 3639.
    case 0x80040210: return "VFW_E_BUFFERS_OUTSTANDING";
    // Original object relative source line 3640.
    case 0x80040211: return "VFW_E_NOT_COMMITTED";
    // Original object relative source line 3641.
    case 0x80040212: return "VFW_E_SIZENOTSET";
    // Original object relative source line 3642.
    case 0x80040213: return "VFW_E_NO_CLOCK";
    // Original object relative source line 3643.
    case 0x80040214: return "VFW_E_NO_SINK";
    // Original object relative source line 3644.
    case 0x80040215: return "VFW_E_NO_INTERFACE";
    // Original object relative source line 3645.
    case 0x80040216: return "VFW_E_NOT_FOUND";
    // Original object relative source line 3646.
    case 0x80040217: return "VFW_E_CANNOT_CONNECT";
    // Original object relative source line 3647.
    case 0x80040218: return "VFW_E_CANNOT_RENDER";
    // Original object relative source line 3648.
    case 0x80040219: return "VFW_E_CHANGING_FORMAT";
    // Original object relative source line 3649.
    case 0x8004021A: return "VFW_E_NO_COLOR_KEY_SET";
    // Original object relative source line 3650.
    case 0x8004021B: return "VFW_E_NOT_OVERLAY_CONNECTION";
    // Original object relative source line 3651.
    case 0x8004021C: return "VFW_E_NOT_SAMPLE_CONNECTION";
    // Original object relative source line 3652.
    case 0x8004021D: return "VFW_E_PALETTE_SET";
    // Original object relative source line 3653.
    case 0x8004021E: return "VFW_E_COLOR_KEY_SET";
    // Original object relative source line 3654.
    case 0x8004021F: return "VFW_E_NO_COLOR_KEY_FOUND";
    // Original object relative source line 3655.
    case 0x80040220: return "VFW_E_NO_PALETTE_AVAILABLE";
    // Original object relative source line 3656.
    case 0x80040221: return "VFW_E_NO_DISPLAY_PALETTE";
    // Original object relative source line 3657.
    case 0x80040222: return "VFW_E_TOO_MANY_COLORS";
    // Original object relative source line 3658.
    case 0x80040223: return "VFW_E_STATE_CHANGED";
    // Original object relative source line 3659.
    case 0x80040224: return "VFW_E_NOT_STOPPED";
    // Original object relative source line 3660.
    case 0x80040225: return "VFW_E_NOT_PAUSED";
    // Original object relative source line 3661.
    case 0x80040226: return "VFW_E_NOT_RUNNING";
    // Original object relative source line 3662.
    case 0x80040227: return "VFW_E_WRONG_STATE";
    // Original object relative source line 3663.
    case 0x80040228: return "VFW_E_START_TIME_AFTER_END";
    // Original object relative source line 3664.
    case 0x80040229: return "VFW_E_INVALID_RECT";
    // Original object relative source line 3665.
    case 0x8004022A: return "VFW_E_TYPE_NOT_ACCEPTED";
    // Original object relative source line 3666.
    case 0x8004022B: return "VFW_E_SAMPLE_REJECTED";
    // Original object relative source line 3667.
    case 0x8004022C: return "VFW_E_SAMPLE_REJECTED_EOS";
    // Original object relative source line 3668.
    case 0x8004022D: return "VFW_E_DUPLICATE_NAME";
    // Original object relative source line 3669.
    case 0x0004022D: return "VFW_S_DUPLICATE_NAME";
    // Original object relative source line 3670.
    case 0x8004022E: return "VFW_E_TIMEOUT";
    // Original object relative source line 3671.
    case 0x8004022F: return "VFW_E_INVALID_FILE_FORMAT";
    // Original object relative source line 3672.
    case 0x80040230: return "VFW_E_ENUM_OUT_OF_RANGE";
    // Original object relative source line 3673.
    case 0x80040231: return "VFW_E_CIRCULAR_GRAPH";
    // Original object relative source line 3674.
    case 0x80040232: return "VFW_E_NOT_ALLOWED_TO_SAVE";
    // Original object relative source line 3675.
    case 0x80040233: return "VFW_E_TIME_ALREADY_PASSED";
    // Original object relative source line 3676.
    case 0x80040234: return "VFW_E_ALREADY_CANCELLED";
    // Original object relative source line 3677.
    case 0x80040235: return "VFW_E_CORRUPT_GRAPH_FILE";
    // Original object relative source line 3678.
    case 0x80040236: return "VFW_E_ADVISE_ALREADY_SET";
    // Original object relative source line 3679.
    case 0x00040237: return "VFW_S_STATE_INTERMEDIATE";
    // Original object relative source line 3680.
    case 0x80040238: return "VFW_E_NO_MODEX_AVAILABLE";
    // Original object relative source line 3681.
    case 0x80040239: return "VFW_E_NO_ADVISE_SET";
    // Original object relative source line 3682.
    case 0x8004023A: return "VFW_E_NO_FULLSCREEN";
    // Original object relative source line 3683.
    case 0x8004023B: return "VFW_E_IN_FULLSCREEN_MODE";
    // Original object relative source line 3684.
    case 0x80040240: return "VFW_E_UNKNOWN_FILE_TYPE";
    // Original object relative source line 3685.
    case 0x80040241: return "VFW_E_CANNOT_LOAD_SOURCE_FILTER";
    // Original object relative source line 3686.
    case 0x00040242: return "VFW_S_PARTIAL_RENDER";
    // Original object relative source line 3687.
    case 0x80040243: return "VFW_E_FILE_TOO_SHORT";
    // Original object relative source line 3688.
    case 0x80040244: return "VFW_E_INVALID_FILE_VERSION";
    // Original object relative source line 3689.
    case 0x00040245: return "VFW_S_SOME_DATA_IGNORED";
    // Original object relative source line 3690.
    case 0x00040246: return "VFW_S_CONNECTIONS_DEFERRED";
    // Original object relative source line 3691.
    case 0x80040247: return "VFW_E_INVALID_CLSID";
    // Original object relative source line 3692.
    case 0x80040248: return "VFW_E_INVALID_MEDIA_TYPE";
    // Original object relative source line 3693.
    case 0x800403F2: return "VFW_E_BAD_KEY";
    // Original object relative source line 3694.
    case 0x00040103: return "VFW_S_NO_MORE_ITEMS";
    // Original object relative source line 3695.
    case 0x80040249: return "VFW_E_SAMPLE_TIME_NOT_SET";
    // Original object relative source line 3696.
    case 0x00040250: return "VFW_S_RESOURCE_NOT_NEEDED";
    // Original object relative source line 3697.
    case 0x80040251: return "VFW_E_MEDIA_TIME_NOT_SET";
    // Original object relative source line 3698.
    case 0x80040252: return "VFW_E_NO_TIME_FORMAT_SET";
    // Original object relative source line 3699.
    case 0x80040253: return "VFW_E_MONO_AUDIO_HW";
    // Original object relative source line 3700.
    case 0x00040254: return "VFW_S_MEDIA_TYPE_IGNORED";
    // Original object relative source line 3701.
    case 0x80040255: return "VFW_E_NO_DECOMPRESSOR";
    // Original object relative source line 3702.
    case 0x80040256: return "VFW_E_NO_AUDIO_HARDWARE";
    // Original object relative source line 3703.
    case 0x00040257: return "VFW_S_VIDEO_NOT_RENDERED";
    // Original object relative source line 3704.
    case 0x00040258: return "VFW_S_AUDIO_NOT_RENDERED";
    // Original object relative source line 3705.
    case 0x80040259: return "VFW_E_RPZA";
    // Original object relative source line 3706.
    case 0x0004025A: return "VFW_S_RPZA";
    // Original object relative source line 3707.
    case 0x8004025B: return "VFW_E_PROCESSOR_NOT_SUITABLE";
    // Original object relative source line 3708.
    case 0x8004025C: return "VFW_E_UNSUPPORTED_AUDIO";
    // Original object relative source line 3709.
    case 0x8004025D: return "VFW_E_UNSUPPORTED_VIDEO";
    // Original object relative source line 3710.
    case 0x8004025E: return "VFW_E_MPEG_NOT_CONSTRAINED";
    // Original object relative source line 3711.
    case 0x8004025F: return "VFW_E_NOT_IN_GRAPH";
    // Original object relative source line 3712.
    case 0x00040260: return "VFW_S_ESTIMATED";
    // Original object relative source line 3713.
    case 0x80040261: return "VFW_E_NO_TIME_FORMAT";
    // Original object relative source line 3714.
    case 0x80040262: return "VFW_E_READ_ONLY";
    // Original object relative source line 3715.
    case 0x00040263: return "VFW_S_RESERVED";
    // Original object relative source line 3716.
    case 0x80040264: return "VFW_E_BUFFER_UNDERFLOW";
    // Original object relative source line 3717.
    case 0x80040265: return "VFW_E_UNSUPPORTED_STREAM";
    // Original object relative source line 3718.
    case 0x80040266: return "VFW_E_NO_TRANSPORT";
    // Original object relative source line 3719.
    case 0x00040267: return "VFW_S_STREAM_OFF";
    // Original object relative source line 3720.
    case 0x00040268: return "VFW_S_CANT_CUE";
    // Original object relative source line 3721.
    case 0x80040269: return "VFW_E_BAD_VIDEOCD";
    // Original object relative source line 3722.
    case 0x00040270: return "VFW_S_NO_STOP_TIME";
    // Original object relative source line 3723.
    case 0x80040271: return "VFW_E_OUT_OF_VIDEO_MEMORY";
    // Original object relative source line 3724.
    case 0x80040272: return "VFW_E_VP_NEGOTIATION_FAILED";
    // Original object relative source line 3725.
    case 0x80040273: return "VFW_E_DDRAW_CAPS_NOT_SUITABLE";
    // Original object relative source line 3726.
    case 0x80040274: return "VFW_E_NO_VP_HARDWARE";
    // Original object relative source line 3727.
    case 0x80040275: return "VFW_E_NO_CAPTURE_HARDWARE";
    // Original object relative source line 3728.
    case 0x80040276: return "VFW_E_DVD_OPERATION_INHIBITED";
    // Original object relative source line 3729.
    case 0x80040277: return "VFW_E_DVD_INVALIDDOMAIN";
    // Original object relative source line 3730.
    case 0x80040278: return "VFW_E_DVD_NO_BUTTON";
    // Original object relative source line 3731.
    case 0x80040279: return "VFW_E_DVD_GRAPHNOTREADY";
    // Original object relative source line 3732.
    case 0x8004027A: return "VFW_E_DVD_RENDERFAIL";
    // Original object relative source line 3733.
    case 0x8004027B: return "VFW_E_DVD_DECNOTENOUGH";
    // Original object relative source line 3734.
    case 0x8004027C: return "VFW_E_DDRAW_VERSION_NOT_SUITABLE";
    // Original object relative source line 3735.
    case 0x8004027D: return "VFW_E_COPYPROT_FAILED";
    // Original object relative source line 3736.
    case 0x0004027E: return "VFW_S_NOPREVIEWPIN";
    // Original object relative source line 3737.
    case 0x8004027F: return "VFW_E_TIME_EXPIRED";
    // Original object relative source line 3738.
    case 0x00040280: return "VFW_S_DVD_NON_ONE_SEQUENTIAL";
    // Original object relative source line 3739.
    case 0x80040281: return "VFW_E_DVD_WRONG_SPEED";
    // Original object relative source line 3740.
    case 0x80040282: return "VFW_E_DVD_MENU_DOES_NOT_EXIST";
    // Original object relative source line 3741.
    case 0x80040283: return "VFW_E_DVD_CMD_CANCELLED";
    // Original object relative source line 3742.
    case 0x80040284: return "VFW_E_DVD_STATE_WRONG_VERSION";
    // Original object relative source line 3743.
    case 0x80040285: return "VFW_E_DVD_STATE_CORRUPT";
    // Original object relative source line 3744.
    case 0x80040286: return "VFW_E_DVD_STATE_WRONG_DISC";
    // Original object relative source line 3745.
    case 0x80040287: return "VFW_E_DVD_INCOMPATIBLE_REGION";
    // Original object relative source line 3746.
    case 0x80040288: return "VFW_E_DVD_NO_ATTRIBUTES";
    // Original object relative source line 3747.
    case 0x80040289: return "VFW_E_DVD_NO_GOUP_PGC";
    // Original object relative source line 3748.
    case 0x8004028A: return "VFW_E_DVD_LOW_PARENTAL_LEVEL";
    // Original object relative source line 3749.
    case 0x8004028B: return "VFW_E_DVD_NOT_IN_KARAOKE_MODE";
    // Original object relative source line 3750.
    case 0x0004028C: return "VFW_S_DVD_CHANNEL_CONTENTS_NOT_AVAILABLE";
    // Original object relative source line 3751.
    case 0x0004028D: return "VFW_S_DVD_NOT_ACCURATE";
    // Original object relative source line 3752.
    case 0x8004028E: return "VFW_E_FRAME_STEP_UNSUPPORTED";
    // Original object relative source line 3753.
    case 0x8004028F: return "VFW_E_DVD_STREAM_DISABLED";
    // Original object relative source line 3754.
    case 0x80040290: return "VFW_E_DVD_TITLE_UNKNOWN";
    // Original object relative source line 3755.
    case 0x80040291: return "VFW_E_DVD_INVALID_DISC";
    // Original object relative source line 3756.
    case 0x80040292: return "VFW_E_DVD_NO_RESUME_INFORMATION";
    // Original object relative source line 3757.
    case 0x80040293: return "VFW_E_PIN_ALREADY_BLOCKED_ON_THIS_THREAD";
    // Original object relative source line 3758.
    case 0x80040294: return "VFW_E_PIN_ALREADY_BLOCKED";
    // Original object relative source line 3759.
    case 0x80040295: return "VFW_E_CERTIFICATION_FAILURE";
    // Original object relative source line 3768.
    case 0x00040003: return "MS_S_ENDOFSTREAM & WBEM_S_DIFFERENT";
    // Original object relative source line 3771.
    case 0x80040403: return "MS_E_NOSTREAM";
    // Original object relative source line 3772.
    case 0x80040404: return "MS_E_NOSEEKING";
    // Original object relative source line 3773.
    case 0x80040405: return "MS_E_INCOMPATIBLE";
    // Original object relative source line 3774.
    case 0x80040406: return "MS_E_BUSY";
    // Original object relative source line 3775.
    case 0x80040407: return "MS_E_NOTINIT";
    // Original object relative source line 3776.
    case 0x80040408: return "MS_E_SOURCEALREADYDEFINED";
    // Original object relative source line 3777.
    case 0x80040409: return "MS_E_INVALIDSTREAMTYPE";
    // Original object relative source line 3778.
    case 0x8004040A: return "MS_E_NOTRUNNING";
    // Original object relative source line 3787.
    case 0x00040004: return "WBEM_S_TIMEDOUT";
    // Original object relative source line 3788.
    case 0x00040005: return "WBEM_S_NO_MORE_DATA";
    // Original object relative source line 3789.
    case 0x00040006: return "WBEM_S_OPERATION_CANCELLED";
    // Original object relative source line 3790.
    case 0x00040007: return "WBEM_S_PENDING";
    // Original object relative source line 3791.
    case 0x00040008: return "WBEM_S_DUPLICATE_OBJECTS";
    // Original object relative source line 3792.
    case 0x00040009: return "WBEM_S_ACCESS_DENIED";
    // Original object relative source line 3793.
    case 0x00040010: return "WBEM_S_PARTIAL_RESULTS";
    // Original object relative source line 3794.
    case 0x00040017: return "WBEM_S_SOURCE_NOT_AVAILABLE";
    // Original object relative source line 3795.
    case 0x80041001: return "WBEM_E_FAILED";
    // Original object relative source line 3796.
    case 0x80041002: return "WBEM_E_NOT_FOUND";
    // Original object relative source line 3797.
    case 0x80041003: return "WBEM_E_ACCESS_DENIED";
    // Original object relative source line 3798.
    case 0x80041004: return "WBEM_E_PROVIDER_FAILURE";
    // Original object relative source line 3799.
    case 0x80041005: return "WBEM_E_TYPE_MISMATCH";
    // Original object relative source line 3800.
    case 0x80041006: return "WBEM_E_OUT_OF_MEMORY";
    // Original object relative source line 3801.
    case 0x80041007: return "WBEM_E_INVALID_CONTEXT";
    // Original object relative source line 3802.
    case 0x80041008: return "WBEM_E_INVALID_PARAMETER";
    // Original object relative source line 3803.
    case 0x80041009: return "WBEM_E_NOT_AVAILABLE";
    // Original object relative source line 3804.
    case 0x8004100A: return "WBEM_E_CRITICAL_ERROR";
    // Original object relative source line 3805.
    case 0x8004100B: return "WBEM_E_INVALID_STREAM";
    // Original object relative source line 3806.
    case 0x8004100C: return "WBEM_E_NOT_SUPPORTED";
    // Original object relative source line 3807.
    case 0x8004100D: return "WBEM_E_INVALID_SUPERCLASS";
    // Original object relative source line 3808.
    case 0x8004100E: return "WBEM_E_INVALID_NAMESPACE";
    // Original object relative source line 3809.
    case 0x8004100F: return "WBEM_E_INVALID_OBJECT";
    // Original object relative source line 3810.
    case 0x80041010: return "WBEM_E_INVALID_CLASS";
    // Original object relative source line 3811.
    case 0x80041011: return "WBEM_E_PROVIDER_NOT_FOUND";
    // Original object relative source line 3812.
    case 0x80041012: return "WBEM_E_INVALID_PROVIDER_REGISTRATION";
    // Original object relative source line 3813.
    case 0x80041013: return "WBEM_E_PROVIDER_LOAD_FAILURE";
    // Original object relative source line 3814.
    case 0x80041014: return "WBEM_E_INITIALIZATION_FAILURE";
    // Original object relative source line 3815.
    case 0x80041015: return "WBEM_E_TRANSPORT_FAILURE";
    // Original object relative source line 3816.
    case 0x80041016: return "WBEM_E_INVALID_OPERATION";
    // Original object relative source line 3817.
    case 0x80041017: return "WBEM_E_INVALID_QUERY";
    // Original object relative source line 3818.
    case 0x80041018: return "WBEM_E_INVALID_QUERY_TYPE";
    // Original object relative source line 3819.
    case 0x80041019: return "WBEM_E_ALREADY_EXISTS";
    // Original object relative source line 3820.
    case 0x8004101A: return "WBEM_E_OVERRIDE_NOT_ALLOWED";
    // Original object relative source line 3821.
    case 0x8004101B: return "WBEM_E_PROPAGATED_QUALIFIER";
    // Original object relative source line 3822.
    case 0x8004101C: return "WBEM_E_PROPAGATED_PROPERTY";
    // Original object relative source line 3823.
    case 0x8004101D: return "WBEM_E_UNEXPECTED";
    // Original object relative source line 3824.
    case 0x8004101E: return "WBEM_E_ILLEGAL_OPERATION";
    // Original object relative source line 3825.
    case 0x8004101F: return "WBEM_E_CANNOT_BE_KEY";
    // Original object relative source line 3826.
    case 0x80041020: return "WBEM_E_INCOMPLETE_CLASS";
    // Original object relative source line 3827.
    case 0x80041021: return "WBEM_E_INVALID_SYNTAX";
    // Original object relative source line 3828.
    case 0x80041022: return "WBEM_E_NONDECORATED_OBJECT";
    // Original object relative source line 3829.
    case 0x80041023: return "WBEM_E_READ_ONLY";
    // Original object relative source line 3830.
    case 0x80041024: return "WBEM_E_PROVIDER_NOT_CAPABLE";
    // Original object relative source line 3831.
    case 0x80041025: return "WBEM_E_CLASS_HAS_CHILDREN";
    // Original object relative source line 3832.
    case 0x80041026: return "WBEM_E_CLASS_HAS_INSTANCES";
    // Original object relative source line 3833.
    case 0x80041027: return "WBEM_E_QUERY_NOT_IMPLEMENTED";
    // Original object relative source line 3834.
    case 0x80041028: return "WBEM_E_ILLEGAL_NULL";
    // Original object relative source line 3835.
    case 0x80041029: return "WBEM_E_INVALID_QUALIFIER_TYPE";
    // Original object relative source line 3836.
    case 0x8004102A: return "WBEM_E_INVALID_PROPERTY_TYPE";
    // Original object relative source line 3837.
    case 0x8004102B: return "WBEM_E_VALUE_OUT_OF_RANGE";
    // Original object relative source line 3838.
    case 0x8004102C: return "WBEM_E_CANNOT_BE_SINGLETON";
    // Original object relative source line 3839.
    case 0x8004102D: return "WBEM_E_INVALID_CIM_TYPE";
    // Original object relative source line 3840.
    case 0x8004102E: return "WBEM_E_INVALID_METHOD";
    // Original object relative source line 3841.
    case 0x8004102F: return "WBEM_E_INVALID_METHOD_PARAMETERS";
    // Original object relative source line 3842.
    case 0x80041030: return "WBEM_E_SYSTEM_PROPERTY";
    // Original object relative source line 3843.
    case 0x80041031: return "WBEM_E_INVALID_PROPERTY";
    // Original object relative source line 3844.
    case 0x80041032: return "WBEM_E_CALL_CANCELLED";
    // Original object relative source line 3845.
    case 0x80041033: return "WBEM_E_SHUTTING_DOWN";
    // Original object relative source line 3846.
    case 0x80041034: return "WBEM_E_PROPAGATED_METHOD";
    // Original object relative source line 3847.
    case 0x80041035: return "WBEM_E_UNSUPPORTED_PARAMETER";
    // Original object relative source line 3848.
    case 0x80041036: return "WBEM_E_MISSING_PARAMETER_ID";
    // Original object relative source line 3849.
    case 0x80041037: return "WBEM_E_INVALID_PARAMETER_ID";
    // Original object relative source line 3850.
    case 0x80041038: return "WBEM_E_NONCONSECUTIVE_PARAMETER_IDS";
    // Original object relative source line 3851.
    case 0x80041039: return "WBEM_E_PARAMETER_ID_ON_RETVAL";
    // Original object relative source line 3852.
    case 0x8004103A: return "WBEM_E_INVALID_OBJECT_PATH";
    // Original object relative source line 3853.
    case 0x8004103B: return "WBEM_E_OUT_OF_DISK_SPACE";
    // Original object relative source line 3854.
    case 0x8004103C: return "WBEM_E_BUFFER_TOO_SMALL";
    // Original object relative source line 3855.
    case 0x8004103D: return "WBEM_E_UNSUPPORTED_PUT_EXTENSION";
    // Original object relative source line 3856.
    case 0x8004103E: return "WBEM_E_UNKNOWN_OBJECT_TYPE";
    // Original object relative source line 3857.
    case 0x8004103F: return "WBEM_E_UNKNOWN_PACKET_TYPE";
    // Original object relative source line 3858.
    case 0x80041040: return "WBEM_E_MARSHAL_VERSION_MISMATCH";
    // Original object relative source line 3859.
    case 0x80041041: return "WBEM_E_MARSHAL_INVALID_SIGNATURE";
    // Original object relative source line 3860.
    case 0x80041042: return "WBEM_E_INVALID_QUALIFIER";
    // Original object relative source line 3861.
    case 0x80041043: return "WBEM_E_INVALID_DUPLICATE_PARAMETER";
    // Original object relative source line 3862.
    case 0x80041044: return "WBEM_E_TOO_MUCH_DATA";
    // Original object relative source line 3863.
    case 0x80041045: return "WBEM_E_SERVER_TOO_BUSY";
    // Original object relative source line 3864.
    case 0x80041046: return "WBEM_E_INVALID_FLAVOR";
    // Original object relative source line 3865.
    case 0x80041047: return "WBEM_E_CIRCULAR_REFERENCE";
    // Original object relative source line 3866.
    case 0x80041048: return "WBEM_E_UNSUPPORTED_CLASS_UPDATE";
    // Original object relative source line 3867.
    case 0x80041049: return "WBEM_E_CANNOT_CHANGE_KEY_INHERITANCE";
    // Original object relative source line 3868.
    case 0x80041050: return "WBEM_E_CANNOT_CHANGE_INDEX_INHERITANCE";
    // Original object relative source line 3869.
    case 0x80041051: return "WBEM_E_TOO_MANY_PROPERTIES";
    // Original object relative source line 3870.
    case 0x80041052: return "WBEM_E_UPDATE_TYPE_MISMATCH";
    // Original object relative source line 3871.
    case 0x80041053: return "WBEM_E_UPDATE_OVERRIDE_NOT_ALLOWED";
    // Original object relative source line 3872.
    case 0x80041054: return "WBEM_E_UPDATE_PROPAGATED_METHOD";
    // Original object relative source line 3873.
    case 0x80041055: return "WBEM_E_METHOD_NOT_IMPLEMENTED";
    // Original object relative source line 3874.
    case 0x80041056: return "WBEM_E_METHOD_DISABLED";
    // Original object relative source line 3875.
    case 0x80041057: return "WBEM_E_REFRESHER_BUSY";
    // Original object relative source line 3876.
    case 0x80041058: return "WBEM_E_UNPARSABLE_QUERY";
    // Original object relative source line 3877.
    case 0x80041059: return "WBEM_E_NOT_EVENT_CLASS";
    // Original object relative source line 3878.
    case 0x8004105A: return "WBEM_E_MISSING_GROUP_WITHIN";
    // Original object relative source line 3879.
    case 0x8004105B: return "WBEM_E_MISSING_AGGREGATION_LIST";
    // Original object relative source line 3880.
    case 0x8004105C: return "WBEM_E_PROPERTY_NOT_AN_OBJECT";
    // Original object relative source line 3881.
    case 0x8004105D: return "WBEM_E_AGGREGATING_BY_OBJECT";
    // Original object relative source line 3882.
    case 0x8004105F: return "WBEM_E_UNINTERPRETABLE_PROVIDER_QUERY";
    // Original object relative source line 3883.
    case 0x80041060: return "WBEM_E_BACKUP_RESTORE_WINMGMT_RUNNING";
    // Original object relative source line 3884.
    case 0x80041061: return "WBEM_E_QUEUE_OVERFLOW";
    // Original object relative source line 3885.
    case 0x80041062: return "WBEM_E_PRIVILEGE_NOT_HELD";
    // Original object relative source line 3886.
    case 0x80041063: return "WBEM_E_INVALID_OPERATOR";
    // Original object relative source line 3887.
    case 0x80041064: return "WBEM_E_LOCAL_CREDENTIALS";
    // Original object relative source line 3888.
    case 0x80041065: return "WBEM_E_CANNOT_BE_ABSTRACT";
    // Original object relative source line 3889.
    case 0x80041066: return "WBEM_E_AMENDED_OBJECT";
    // Original object relative source line 3890.
    case 0x80041067: return "WBEM_E_CLIENT_TOO_SLOW";
    // Original object relative source line 3891.
    case 0x80041068: return "WBEM_E_NULL_SECURITY_DESCRIPTOR";
    // Original object relative source line 3892.
    case 0x80041069: return "WBEM_E_TIMED_OUT";
    // Original object relative source line 3893.
    case 0x8004106A: return "WBEM_E_INVALID_ASSOCIATION";
    // Original object relative source line 3894.
    case 0x8004106B: return "WBEM_E_AMBIGUOUS_OPERATION";
    // Original object relative source line 3895.
    case 0x8004106C: return "WBEM_E_QUOTA_VIOLATION";
    // Original object relative source line 3896.
    case 0x8004106D: return "WBEM_E_RESERVED_001";
    // Original object relative source line 3897.
    case 0x8004106E: return "WBEM_E_RESERVED_002";
    // Original object relative source line 3898.
    case 0x8004106F: return "WBEM_E_UNSUPPORTED_LOCALE";
    // Original object relative source line 3899.
    case 0x80041070: return "WBEM_E_HANDLE_OUT_OF_DATE";
    // Original object relative source line 3900.
    case 0x80041071: return "WBEM_E_CONNECTION_FAILED";
    // Original object relative source line 3901.
    case 0x80041072: return "WBEM_E_INVALID_HANDLE_REQUEST";
    // Original object relative source line 3902.
    case 0x80041073: return "WBEM_E_PROPERTY_NAME_TOO_WIDE";
    // Original object relative source line 3903.
    case 0x80041074: return "WBEM_E_CLASS_NAME_TOO_WIDE";
    // Original object relative source line 3904.
    case 0x80041075: return "WBEM_E_METHOD_NAME_TOO_WIDE";
    // Original object relative source line 3905.
    case 0x80041076: return "WBEM_E_QUALIFIER_NAME_TOO_WIDE";
    // Original object relative source line 3906.
    case 0x80041077: return "WBEM_E_RERUN_COMMAND";
    // Original object relative source line 3907.
    case 0x80041078: return "WBEM_E_DATABASE_VER_MISMATCH";
    // Original object relative source line 3908.
    case 0x80041079: return "WBEM_E_VETO_DELETE";
    // Original object relative source line 3909.
    case 0x8004107A: return "WBEM_E_VETO_PUT";
    // Original object relative source line 3910.
    case 0x80041080: return "WBEM_E_INVALID_LOCALE";
    // Original object relative source line 3911.
    case 0x80041081: return "WBEM_E_PROVIDER_SUSPENDED";
    // Original object relative source line 3912.
    case 0x80041082: return "WBEM_E_SYNCHRONIZATION_REQUIRED";
    // Original object relative source line 3913.
    case 0x80041083: return "WBEM_E_NO_SCHEMA";
    // Original object relative source line 3914.
    case 0x80041084: return "WBEM_E_PROVIDER_ALREADY_REGISTERED";
    // Original object relative source line 3915.
    case 0x80041085: return "WBEM_E_PROVIDER_NOT_REGISTERED";
    // Original object relative source line 3916.
    case 0x80041086: return "WBEM_E_FATAL_TRANSPORT_ERROR";
    // Original object relative source line 3917.
    case 0x80041087: return "WBEM_E_ENCRYPTED_CONNECTION_REQUIRED";
    // Original object relative source line 3918.
    case 0x80041088: return "WBEM_E_PROVIDER_TIMED_OUT";
    // Original object relative source line 3919.
    case 0x80041089: return "WBEM_E_NO_KEY";
    // Original object relative source line 3920.
    case 0x8004108A: return "WBEM_E_PROVIDER_DISABLED";
    // Original object relative source line 3921.
    case 0x80042001: return "WBEMESS_E_REGISTRATION_TOO_BROAD";
    // Original object relative source line 3922.
    case 0x80042002: return "WBEMESS_E_REGISTRATION_TOO_PRECISE";
    // Original object relative source line 3924.
    case 0x80044001: return "WBEMMOF_E_EXPECTED_QUALIFIER_NAME";
    // Original object relative source line 3925.
    case 0x80044002: return "WBEMMOF_E_EXPECTED_SEMI";
    // Original object relative source line 3926.
    case 0x80044003: return "WBEMMOF_E_EXPECTED_OPEN_BRACE";
    // Original object relative source line 3927.
    case 0x80044004: return "WBEMMOF_E_EXPECTED_CLOSE_BRACE";
    // Original object relative source line 3928.
    case 0x80044005: return "WBEMMOF_E_EXPECTED_CLOSE_BRACKET";
    // Original object relative source line 3929.
    case 0x80044006: return "WBEMMOF_E_EXPECTED_CLOSE_PAREN";
    // Original object relative source line 3930.
    case 0x80044007: return "WBEMMOF_E_ILLEGAL_CONSTANT_VALUE";
    // Original object relative source line 3931.
    case 0x80044008: return "WBEMMOF_E_EXPECTED_TYPE_IDENTIFIER";
    // Original object relative source line 3932.
    case 0x80044009: return "WBEMMOF_E_EXPECTED_OPEN_PAREN";
    // Original object relative source line 3933.
    case 0x8004400A: return "WBEMMOF_E_UNRECOGNIZED_TOKEN";
    // Original object relative source line 3934.
    case 0x8004400B: return "WBEMMOF_E_UNRECOGNIZED_TYPE";
    // Original object relative source line 3935.
    case 0x8004400C: return "WBEMMOF_E_EXPECTED_PROPERTY_NAME";
    // Original object relative source line 3936.
    case 0x8004400D: return "WBEMMOF_E_TYPEDEF_NOT_SUPPORTED";
    // Original object relative source line 3937.
    case 0x8004400E: return "WBEMMOF_E_UNEXPECTED_ALIAS";
    // Original object relative source line 3938.
    case 0x8004400F: return "WBEMMOF_E_UNEXPECTED_ARRAY_INIT";
    // Original object relative source line 3939.
    case 0x80044010: return "WBEMMOF_E_INVALID_AMENDMENT_SYNTAX";
    // Original object relative source line 3940.
    case 0x80044011: return "WBEMMOF_E_INVALID_DUPLICATE_AMENDMENT";
    // Original object relative source line 3941.
    case 0x80044012: return "WBEMMOF_E_INVALID_PRAGMA";
    // Original object relative source line 3942.
    case 0x80044013: return "WBEMMOF_E_INVALID_NAMESPACE_SYNTAX";
    // Original object relative source line 3943.
    case 0x80044014: return "WBEMMOF_E_EXPECTED_CLASS_NAME";
    // Original object relative source line 3944.
    case 0x80044015: return "WBEMMOF_E_TYPE_MISMATCH";
    // Original object relative source line 3945.
    case 0x80044016: return "WBEMMOF_E_EXPECTED_ALIAS_NAME";
    // Original object relative source line 3946.
    case 0x80044017: return "WBEMMOF_E_INVALID_CLASS_DECLARATION";
    // Original object relative source line 3947.
    case 0x80044018: return "WBEMMOF_E_INVALID_INSTANCE_DECLARATION";
    // Original object relative source line 3948.
    case 0x80044019: return "WBEMMOF_E_EXPECTED_DOLLAR";
    // Original object relative source line 3949.
    case 0x8004401A: return "WBEMMOF_E_CIMTYPE_QUALIFIER";
    // Original object relative source line 3950.
    case 0x8004401B: return "WBEMMOF_E_DUPLICATE_PROPERTY";
    // Original object relative source line 3951.
    case 0x8004401C: return "WBEMMOF_E_INVALID_NAMESPACE_SPECIFICATION";
    // Original object relative source line 3952.
    case 0x8004401D: return "WBEMMOF_E_OUT_OF_RANGE";
    // Original object relative source line 3953.
    case 0x8004401E: return "WBEMMOF_E_INVALID_FILE";
    // Original object relative source line 3954.
    case 0x8004401F: return "WBEMMOF_E_ALIASES_IN_EMBEDDED";
    // Original object relative source line 3955.
    case 0x80044020: return "WBEMMOF_E_NULL_ARRAY_ELEM";
    // Original object relative source line 3956.
    case 0x80044021: return "WBEMMOF_E_DUPLICATE_QUALIFIER";
    // Original object relative source line 3957.
    case 0x80044022: return "WBEMMOF_E_EXPECTED_FLAVOR_TYPE";
    // Original object relative source line 3958.
    case 0x80044023: return "WBEMMOF_E_INCOMPATIBLE_FLAVOR_TYPES";
    // Original object relative source line 3959.
    case 0x80044024: return "WBEMMOF_E_MULTIPLE_ALIASES";
    // Original object relative source line 3960.
    case 0x80044025: return "WBEMMOF_E_INCOMPATIBLE_FLAVOR_TYPES2";
    // Original object relative source line 3961.
    case 0x80044026: return "WBEMMOF_E_NO_ARRAYS_RETURNED";
    // Original object relative source line 3962.
    case 0x80044027: return "WBEMMOF_E_MUST_BE_IN_OR_OUT";
    // Original object relative source line 3963.
    case 0x80044028: return "WBEMMOF_E_INVALID_FLAGS_SYNTAX";
    // Original object relative source line 3964.
    case 0x80044029: return "WBEMMOF_E_EXPECTED_BRACE_OR_BAD_TYPE";
    // Original object relative source line 3965.
    case 0x8004402A: return "WBEMMOF_E_UNSUPPORTED_CIMV22_QUAL_VALUE";
    // Original object relative source line 3966.
    case 0x8004402B: return "WBEMMOF_E_UNSUPPORTED_CIMV22_DATA_TYPE";
    // Original object relative source line 3967.
    case 0x8004402C: return "WBEMMOF_E_INVALID_DELETEINSTANCE_SYNTAX";
    // Original object relative source line 3968.
    case 0x8004402D: return "WBEMMOF_E_INVALID_QUALIFIER_SYNTAX";
    // Original object relative source line 3969.
    case 0x8004402E: return "WBEMMOF_E_QUALIFIER_USED_OUTSIDE_SCOPE";
    // Original object relative source line 3970.
    case 0x8004402F: return "WBEMMOF_E_ERROR_CREATING_TEMP_FILE";
    // Original object relative source line 3971.
    case 0x80044030: return "WBEMMOF_E_ERROR_INVALID_INCLUDE_FILE";
    // Original object relative source line 3972.
    case 0x80044031: return "WBEMMOF_E_INVALID_DELETECLASS_SYNTAX";
    default: return "Unknown";
    }
}
