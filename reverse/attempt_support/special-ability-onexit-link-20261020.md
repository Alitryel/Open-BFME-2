# Special-ability direct base calls

The recovered `SpecialAbilityUpdate::onExit` owner at `0x004502CE` is a
protected virtual method taking two `bool` arguments. Four existing callers
still declared it private and nonvirtual, leaving the obsolete
`?onExit@SpecialAbilityUpdate@@AAEX_N0@Z` reference unresolved after the
correct `?onExit@SpecialAbilityUpdate@@MAEX_N0@Z` provider landed.

Native direct calls establish the target and receiver independently for each
caller:

| Caller RVA | Complete size | Direct call RVA |
| --- | ---: | --- |
| `0x00492930` | 161 | `0x0049293B` |
| `0x00490F35` | 121 | `0x00490F40` |
| `0x004B0414` | 56 | `0x004B041F` |
| `0x004ADBF2` | 70 | `0x004ADC2F` |

All calls target `0x004502CE`, preserve the primary receiver in ECX, and pass
the two incoming arguments in their original stack slots. The caller views
now declare the established protected virtual method. The first three
already use qualified base calls; the fourth now explicitly qualifies its
call too, preserving direct dispatch.

These partial views are used only by existing caller bodies. No constructor,
destructor, RTTI, or vtable definition is added. Frozen COFF comparison shows
the same defined-symbol sets and weak externals, with only the intended
undefined callee name changed. The provider object is unchanged.

At BFME2 `24bc709a164cff181a32062b16b3d663aa82a933`, pinned BFME1
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`:

- All 21 existing rows across the four callers and provider remain exact.
  The current `killSpecialObjects` and frame-rate data owners also pass all
  34 of their existing function rows and 12 data rows.
- All five provider exception graphs remain exact; the callers have none.
- Paired frozen objects against published index `144ed0ccab` change the four
  caller units from blocked to linking: **407 census-accounted bytes**, out of
  408 bytes of complete row extents. The accounting excludes the `0xCC`
  displacement byte at `0x00492945`; it is part of an instruction, not padding.
- Both sides include the same freshly verified `killSpecialObjects` and
  data-owner objects. The seven-unit total changes from 1,057 to 1,464
  linkable bytes, so the already recovered dependencies receive no credit.
- The provider unit retains its unsigned `g_00E033D0` reference, which differs
  from the existing signed-int data owner at VA `0x00E033D0`. Its 5,211
  nonpadding bytes remain blocked and receive no credit. The provider's
  `0x004502CE` claim was held by `StarkillerHDX@fleet` (seat w1, about 1.5 hours
  remaining when checked); no provider edit was attempted.
- The affected-caller placement scan finds no new bodies or pins.

The old private-name pin remains because the separate destructor consumer
still uses it. That source emits an incomplete primary vtable: simply adding
this virtual method would put it in slot 1 instead of native slot 13, so it
requires class-contract reconciliation. The `0x0049C5D9` wrapper also remains
unchanged because its current signature forwards two integers; a `bool`
signature needs separate proof. Neither prerequisite is hidden by an alias.

This is a linking repair with no new recovered coverage.
