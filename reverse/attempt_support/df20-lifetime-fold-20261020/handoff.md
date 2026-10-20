# 0x0000DF20: independent sign local and allocator-constructor fold

The bank remains partial. It now emits 2594/2610 bytes and has retail's 0x118
frame. No matched function row was added. Its historical score 0.8114 is retained
conservatively; the measured improvement is in `before-align.txt` and
`after-align.txt` (whitespace normalized in diagnostic text): structural/memory/register differences 22/127/49 -> 20/111/34.
The first byte difference moves from +0x1D (frame size) to +0x2A (locale local).
Both old and new EH comparisons first fail in the associative text at 0x75BB60,
17 bytes differing. This is not a complete EH match.

## Inputs and identity

Parent revision: 6c0f01763997864b2f3e94f9267adf6f6ea18090. Toolchain: default
MSVC 7.1 through official align_diff/explain_mismatch, BFME_OBJSTORE=off,
/EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC. Vendor STLport 4.5.3
supplies the monetary algorithm. Target identity/boundary/vtable evidence remains
in ../df20-money-put-20261019/. Do not infer additional target layout or names
from matching instructions alone.

Ledger check passed. BFME 1's successful-check stamp is under 24 hours old at
0dc8a26a9c6041c73dc564754cd059dc54faa72a; the active freshness lock belongs to
codex5, so this seat did not move the pointer. The published link index was
fetched. Main assignment 0x6EFBC0 and the first three fallbacks were held by other
seats; this seat claimed the permitted fallback 0xDF20 and its ctor prerequisite.

## Verified prerequisite

Retail DF20+0x449 calls 0x00689600, the existing 37-byte narrow allocator-base
constructor. Explicitly instantiating the wide base constructor in the same
ledger source reproduces the full 37 bytes, including its REL32 at +0x1B. Its
wide allocator proxy emits the complete 11-byte, relocation-free body at retail
0x7410, independently proven against the SightingInfo proxy owner. The fold
admission tool recursively proves this callee, so a second proxy pin is unneeded.

The new wide-base pin carries fold-proof=Code/Libraries/Source/WWVegas/WWLib/
stlport_narrow_string.cpp (one unbroken path in symbols.csv). No other address
for this name exists. pin_admission --add accepted the full proof. The parent
bank now has no unresolved callees. This is a verified dependency improvement,
not newly recovered unique bytes. The hatch tool admitted its pin and removed
two obsolete allow stamps from already committed entries automatically.

Checks: build.sh on the owner passes all 20 rows; find_declared_unmatched passes;
pin_consistency --check and check_csv pass; link_check --new-variants passes.
The broader link_check still reports 0 linked bytes and pre-existing string
COMDAT/selected-definition blockers. This change does not claim to repair them.

## Trials and conclusions

Read the prior handoffs before retrying blanket visibility or budget hypotheses.
`trials.json` records each factorial combination, including failed compilations.

- Callee visibility/lifetime: allocator versus proxy late-dead destruction,
  throwing versus nothrow, opaque versus visible wide base, and locale inline
  decoration do not improve the old bank. SP1 and DDK toolchain profiles do not
  improve it. Wide copy-constructor visibility remains inert.
- Control flow: an inner currency/sign scope with early goto separates the
  grouping/locale tail and removes the explicit locale call. With the original
  tag it gives 2576 bytes, 22/129/49; final wide destruction still calls the base.
  Nested ifs and a shared named iterator result lose overall. The scoped source
  is retained in scoped-cleanup.cpp.txt as a regional lead, not the best bank.
- Compiler settings: depths 1,2,3,4,5,6,8,12 crossed with scope and wide-copy
  visibility lose. Nonzero depth affects unrelated helper expansion too.
- Ownership wrapper: raw aligned storage plus an active flag, with ownership
  cleared before/after explicit cleanup, compiles but adds states/operations.
  Currency-only is 2677 bytes; all-wide ownership is 2736 bytes. Neither improves
  the bank. The latter is retained in owned-storage.cpp.txt. Initial failed
  versions had placement-new namespace and protected-base access errors.
- Types and local lifetimes: a 32-way matrix separates the negative boolean
  from the derived copy tag, moves pointer and fraction declarations, moves the
  aligned pattern declaration, and crosses these with the goto scope. Only the
  independent boolean changes code. Without goto it improves all three counts
  and gives the exact frame. With goto it gives 2594 bytes, 20/123/34 and no
  locale call, but is weaker overall than the retained 20/111/34 bank. Declaration
  moves are inert in every combination. No padding was introduced.

- Sign temporary order: 16 semantic-equivalent ternary polarity/arm orders
  crossed with const versus assigned negative boolean are inert or add one
  structural region. They do not repair the sign temporary cleanup.

## Remaining work and reproduction

Currency still needs a whole destructor at the first exit, a base destructor at
the second, and inline free at normal exit. The bank has three whole calls,
seven base calls, three frees and one locale call; retail has three whole calls,
six base calls and six frees. The final three wide calls and first-return tail
remain wrong. The 14-byte 0x142D70 body is also _M_deallocate_block, so cleanup
addresses alone do not justify renaming destructor providers.

Start from the new bank. The sign conditional may need a different construction
context (for example explicit control flow), rather than polarity changes or
repeating declarations/flags above. All ordinary
parent call targets are now resolved. Preserve the stronger bank if an experiment
only improves one cleanup region while worsening allocation elsewhere.

Reproducers here are diagnostic evidence, not gate tools. From the repo root,
restore this commit's parent bank to build/df20-seat-20261020/baseline.cpp before
running trials.py, then control.py, depth.py and lifetimes.py in that order.
They compile isolated variants with official align_diff and never call
build.compile_source directly. The complete raw trials remain under build/.
