# Multiplayer combo assignment link blocker

Current baseline at 3ce21d8068: MpGameSetupSlots_Init_InitGadgets_InitGadgets.cpp
does not link (0/1,341 B). Its only unresolved name is
??4MpGameSetupComboRef@@QAEAAV0@PAVGameWindow@@@Z. The other former blocker,
AptMpGameSetup::rva004404AC, now has a verified provider on master.

The existing symbol pin at 7B719 names a structural assignment: shutdown
43DE19 passes zero to each one-pointer color wrapper at +2F4. The complete
native 11-byte body is 8b c1 8b 4c 24 04 89 08 c2 04 00 (store argument at
this+0 and return this). The existing Rva00323674(GameWindow*) owner and
const int-list iterator constructor are complete ICF twins there. No new
application identity, member offset or pin was proposed.

Tested a real out-of-line operator= { m_window = window; return *this; }
in the existing class view. The proposed assignment itself passes the byte
gate, but each of three complete-unit trials fails shutdown 43DE19:

* Definition immediately after class: the compiler inlines the store and
  removes the call, changing the native loop and frame/register allocation.
* __declspec(noinline) on declaration: restores the call, but changes the
  loop pointer to EDX, zero to EDI and count to EBX (native EDI/EBX/[ebp-10]).
* Definition after all callers, without noinline: still fails the same caller;
  delayed source order does not hide the body from this compiler.

The retained after-caller patch is diagnostic only. add_match rolled back
each tentative row. Original source restored and 11/11 rows byte-verified;
no Code edit or pin retained and all claims released. The next distinct
hypothesis is a provider outside this caller TU, preferably in an existing
compatible class view or a reconciled shared header, so caller visibility
and clobber information stay unchanged. Do not repeat these three placements.
Compiler settings: existing /O1 profile, BFME 1 74ea60ad41ef; no custom flags.
Legacy evidence only; no strict closure or gain claimed. t=8 min, gpt-6.1-sol.
