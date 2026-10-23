# One ordinary destructor-visibility trial: rejected and restored

## Independent identity check before editing

Exact demand: `??1?$RefCountPtr@VTextureClass@@@@QAE@XZ`, the existing physical
row at RVA 0x0017098D, 12 bytes, owned by streakRender.cpp through the real global
RefCountPtr<T> template in reference/shims/bfmestreak/ref_ptr.h. No alternate
handle class, alias pin, new attribute or sizeof-based identity was used.

Retail callback 0x007B7040 supplies ECX=0x00DEE918 and tail-jumps directly to
0x0017098D. The full native destructor is 8b0985c97405e978e34a00c3: load the
referent, null-test, tail-release, return on null. Its sole REL32, at +7, targets
TextureBaseClass::Release_Ref at RVA 0x0061ED10. The pretrial Record COMDAT of
the exact same decorated specialization matches all 12 bytes after resolving
that relocation. The existing Shutdown object independently demands that exact
decorated name. ABI: ordinary public nonvirtual __thiscall destructor, no
arguments, no this adjustment, no clearing store. The provider's cached object
was absent; no provider compilation was performed or claimed.

The declaration-only change is preserved in trial.patch and
DebugStatisticsRecordTexture.trial.cpp.txt; the original is preserved separately.
All 31 held claims were rechecked before the edit.

## Actual trial outcomes

One normal explicit four-source build; only Record recompiled, three cached.
25/27 matched rows survive; the ordinary build exits 1 for two byte mismatches.
Scoped EH independently remains 3/3 EXACT, no missing objects or baseline debt.

| Emitted definition | Baseline | Trial | Result |
| --- | ---: | ---: | --- |
| generated handle shutdown _$E2 | 16 B | 10 B | exact retail callback after both proven relocations |
| Add_Record_Texture, RVA 0x0012A210 | 154 B | 165 B | matched-row regression |
| Debug_Statistics::Record_Texture, RVA 0x0012A2B0 | 333 B | 349 B | matched-row regression |
| Record's TextureStatisticsStruct destructor COMDAT | 12 B | 5 B | now tail-jumps to handle destructor |
| Record's RefCountPtr<TextureClass> destructor COMDAT | 12 B | absent | becomes undefined exact-name demand |

The new 10 B callback is mov ecx,&latest_texture; jmp the ordinary handle
destructor. Its DIR32 at +1 resolves to VA 0x00DEE918; REL32 at +6 resolves to
RVA 0x0017098D. callback-proof.json compares the full resolved body to retail.
This is diagnostic proof, not an admitted row or sole-storage/link closure.

The destructor's opacity also changes temporary lifetime code: Record_Texture's
temporary null handle now has an out-of-line cleanup call; Add_Record_Texture's
stack TextureStatisticsStruct cleanup routes through the changed destructor
chain. Null-state optimization and register/stack shape differ. Raw bodies,
disassembly and every relocation are preserved in coff/ and
emission-relocation-diff.json. EH funclet labels change, but the scoped normal EH
verifier still proves all three native graphs exact. It does not establish that
the new 5 B COMDAT copy is retail's 12 B TextureStatisticsStruct destructor or
that a linker would select a correct copy. No current link census was run.

The three other complete objects are byte-identical to baseline. No statics are
moved or removed. All three handle/vector storage pairs, six CRT initializer
entries and six atexit registrations remain. Record's 22 B handle initializer,
26 B vector initializer and 10 B vector cleanup remain unchanged. The additional
28 B deleting-destructor copy in Shutdown remains unchanged.

## Restoration and footprint

Only the owned seven-line destructor edit was restored. A second normal
explicit four-source build (the authorized restoration, not another hypothesis)
recompiled Record only and returned 27/27 exact, 1,763 B. All scoped reference
gates pass; restoration EH returns 3/3 EXACT. All four source hashes match the
accepted baseline and tracked git status is clean.

All parsed restored symbols and non-debug COFF sections equal baseline. A raw
object-equality diagnostic stopped on Record's .debug$S output filename changing
from the original guest job directory to the restoration job directory. That
exact difference is preserved in restored-raw-section-diff.json; it is debug
metadata only, not a byte-gate exception. No build was retried in response.

Each build interval has seven captured guest jobs: six normal build-internal
winepath operations and one compiler invocation of Record only. All exit 0;
the trial's build exit 1 is byte comparison, not compiler/runtime failure.
Pin138, seat-specific outputs/prefix, read-only inputs, BUILD_POOL=1 and
BFME_OBJSTORE=off are unchanged. Grant was unset immediately after each build.
Raw guest receipts/stdout/stderr, all object snapshots and normal gate outputs
are preserved. No source expansion, generated probes, provider compilation,
runtime repair, source/flag/header/ledger/data change, commit or push remains.

Conclusion: ordinary declaration-only destructor visibility genuinely explains
the callback's missing out-of-line tail jump, but is not a whole-TU repair:
opaque temporary destruction breaks two established bodies and changes another
emitted COMDAT. No further visibility/source variations were attempted under
this one-trial authorization. Claims remain held pending parent direction.
