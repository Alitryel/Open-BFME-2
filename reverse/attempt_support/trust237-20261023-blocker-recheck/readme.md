# 0x237D3D: unchanged binary-patch prerequisite

Read-only reassessment of the standing assignment, 2026-10-23 03:44 UTC,
BFME2 `954c27539ebcbed82725834346b119ffd45a3b4c`. Continue from
[round18](../trust237-20261023-round18/readme.md) and
[round17's provenance evidence](../trust237-20261023-round17/readme.md).
Model: gpt-6.1-sol. No new source/codegen hypothesis is claimed.

The scoped `pick-hard --rva 0x237D3D` history was reviewed before claiming.
Earlier controls already addressed control flow, declaration lifetime/scope,
types/layout, callee visibility and compiler settings. Round17 recovered the
overwritten comparisons; round18 then tested their switch/result-copy shapes.
No relevant source, compiler-tool, bank or instruction change has landed since
that work. An unrelated recipes update supplies no new NOP producer. Repeating
those matrices would not address the established input patch.

Fresh checks, recorded in [evidence.json](evidence.json):

* `check_csv.py`: OK, 98104 functions / 15853 symbols / 2139 data rows.
* BFME1's verified `f36a4db066` pointer and checkout agree; the 02:02 UTC
  freshness receipt is under 24 hours old. The active update lock belongs to
  another seat (`codex8`); its checkout and lock were preserved.
* Independent `variant.py` compilation of the unchanged bank: **226 B**,
  raw SHA256 `ffcdd41b39c5b09965e653b339f650fa9177c99056e8f6c4fcd52292d53753f3`,
  prefix205, exactly **16 differing bytes at +CD..DC**, retained score70/86.
* The round17 audit's image/bank/API portion was rerun against the fresh
  object, omitting its old variant matrices. Full-file hashes and all 26
  image differences agree; actual IAT names and direct-call thunks agree.
  **1704 executions** pass API/layout/return/ABI checks. The independent body
  returns zero for the two recovered errors; baseline and bank return one.
* `build.sh VersionDestructor.cpp VersionInitGlobals.cpp`, using full source
  paths: **39/39**, all scoped data/source/string/import checks pass.
* Published index fetched. `link_check.py` confirms VersionDestructor already
  links **1275 B**. VersionInitGlobals still has **200 B** held out solely by
  unresolved `?Rva00237D3DCheck@@YAHXZ`; its exit1 is that known blocker.
* `progress.py origin/master`: **+0 authored C++ bytes, +0 linking bytes**.

The best bank remains `reverse/attempts/0x00237d3d.cpp`, unchanged. Reproduction
uses round17's tracked `audit.py.txt`, stopping before its `original_check`
matrix import and changing the object path to the freshly compiled bank. All
large artifacts and the recheck wrapper remain ignored under
`build/trust237-blocker-recheck/`.

**Blocker:** the canonical sixteen-NOP patch replaces the independently
recovered comparisons at RVA0x237E0A. No legal C++ producer is established;
this is not a universal compiler-impossibility proof. Further work needs new
concrete compiler evidence or an upstream decision about representing this
proven binary patch. No missing game callee is identified. Do not insert
asm/emit padding, substitute the original zero-returning body, or alter the
baseline/verifier. The claim is released. The standing assignment excludes
other bodies until this lands, so no broad queue or unchanged matrix was run.

## Subsequent input-only reassessment

At `154dfa9d44`, the scoped history and standing assignment were reread. Git
comparison against the above verified revision finds no changes to AGENTS.md,
recipes, tools, the BFME1 pointer, bank, or either affected source unit. Fresh
SHA256 checks of the bank and all three image artifacts agree with the existing
receipt. BFME1's committed and checked-out verified pointers still agree, and
its freshness receipt remains under 24 hours old. The other seat's update lock
was preserved. The ledger now passes at 98104 functions, 15858 symbols and
2140 data rows; progress against origin/master remains +0 C++ and +0 linking
bytes. See `latest_input_reassessment` in evidence.json for this check's time
and inputs.

No new source hypothesis is supported by these unchanged inputs. Earlier
control-flow, lifetime, layout, visibility and compiler-setting trials are not
repeated, and earlier compilation/emulation/link results above are historical,
not new runs. The same binary-patch representation prerequisite remains.
The best 226-byte bank and score70/86 are preserved without modification.
The standing assignment still excludes the fallback bodies while this check is
unmatched; the claim is released and the session reports blocked.

## Recheck after the verified BFME1 pointer update

At BFME2 `88983ceb42`, the checkout and committed BFME1 pointer are both
`138757e9b74645fbcbb7724a7af2764e34931e11`. Its committed
[paired gate evidence](../bfme1-reference-138757e9-20261023/README.md)
records passing old/new full gates. Another seat (`codex8`) holds the live
update lock; it was preserved and a further update was skipped as instructed.
The freshness receipt remains under 24 hours old. Changed inputs since the
last session were reviewed: the pointer-IV CSE recipe and verified data-owner
precedence do not supply a new producer for the target's internal NOP span.
The bank, affected production sources and compiler driver are unchanged.

The bank was compiled again with `variant.py`: **226 B**, the same raw hash,
prefix205 and **16 differences solely at +CD..DC**. The existing provenance
and API audit was rerun with that fresh object: all three complete image
hashes, all 26 image differences and **1704 ABI/API executions** pass.
The audit initially lacked Unicorn; installing Unicorn 2.1.4 into ignored
`build/trust237-blocker-recheck/python-deps` resolved that setup failure.
No previous source-search matrix was repeated. The two affected production
units pass **39/39** plus data, string and import checks; `check_csv.py` passes
with 98112 functions, 15853 symbols and 2140 data rows. The fresh results are
under `post_pointer_update_reassessment` in evidence.json.

The published index was fetched (census `456ce161c5`, 06:28 UTC).
The fresh predictor again reports VersionDestructor **LINKS, 1275 B** and
VersionInitGlobals **unresolved check, 200 B**; its exit1 is this known blocker.

Retain the existing best 226-byte bank and score70/86. The independently
evidenced binary patch remains the concrete prerequisite: new compiler
evidence or an upstream representation decision is needed. No missing game
callee is identified, and no source, ledger row, pin or verifier was changed.
The standing assignment continues to exclude other bodies while this body is
unmatched and available; release its claim after recording this recheck.
