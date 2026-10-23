# Registry setters: explicit SDK headers

The two existing BFME1 donor ports, RegistrySetString.cpp and
RegistrySetUnsignedInt.cpp, directly include `windows.h`. At verified BFME1
pin 4483e88da1c2 their effective search roots were the source directory,
`asciistring_downloadmanager`, ZH GameEngine/Include, ZH WWLib, and Vc7/include.
None supplied that header. The real toolchain PlatformSDK/Include/Windows.h
exists but was not searched. Add the existing per-source `// platformsdk`
opt-in; compiler argv and optimization flags remain unchanged.

The SDK defaults to STRICT handles; a marker-only diagnostic compiled with
HKEY__* parameter names and could not supply the existing four ledger symbols.
The pinned donor and its previous sweep/windows.h use HKEY as void*.
SDK WinDef.h explicitly supports NO_STRICT before inclusion; WinNT.h then
makes DECLARE_HANDLE(HKEY) use the opaque HANDLE typedef. Set this normal
source-local SDK mode to preserve the established AsciiString overloads:

- `?setStringInRegistry@@YA_NPAXVAsciiString@@11@Z`, 0x00234621 / 201 bytes;
- `?setUnsignedIntInRegistry@@YA_NPAXVAsciiString@@1I@Z`, 0x002346EA / 158 bytes;
- their compiler EH handlers at 0x0076FEF0 and 0x0076FF02, 10 bytes each.

No additional named Code consumer of these AsciiString overloads was found.
The separate WWDownload std::string overloads intentionally use HKEY__* and
are untouched. This preserves an existing source/API contract; it does not
infer the spelling of an original retail typedef. There are no function-body,
shared-header, flag, ledger, alias, or pin changes.

The first prechange ordinary build entered the known Wine ntdll segv_handler
loop while its direct header was unresolved. A bounded process sample
confirmed it; only that build and its compiler child were terminated. The
second identical missing-header case was not repeated. A successful current
prechange compile is unavailable, so no before/after native-equivalence claim
is made. The failed STRICT diagnostic is also not an accepted baseline.

Final ordinary build and supported `link_check.py --prepare-current` both
pass all four rows and six named imports. Frozen object replay proves all
379 extent bytes and both EH graphs EXACT. Strict reusable dependency
receipts resolve Windows.h, WinDef.h, WinNT.h and WinReg.h under the actual
Vc7/PlatformSDK/Include directory. Source/object/receipt hashes and key SDK
header hashes are in `proof.json`; full frozen receipts remain in
`build/near-batch4-registry-sdk/final/`. Placement finds 0 bodies/0 pins.
The ordinary published-index preview finds both current units clean, totaling
359 nonpadding linked bytes. This is not a paired prechange measurement.
Recovery credit and new linking credit are zero;
this repairs a reproducible build prerequisite for the existing bodies.

Diagnostic sample, effective path inventory, exact compiler argv comparison,
and strict preparation output are retained under
`build/near-batch4-registry-sdk/`. t=15min model=Codex(runtime-model-not-exposed).
