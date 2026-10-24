# stlport_wide_money_put_string.cpp: ~_String_base<wchar_t> COMDAT link blocker (2026-10-24)

Unit 2,616 B; sole blocker `??1?$_String_base@GV?$allocator@G@_STL@@@_STL@@QAE@XZ`
(retail 0x142D70, 14 B `if (_M_start) free(_M_start)`). The unit is first in
link order (lowest RVA 0xDF20) among the copies, and its copy is 82 B: the
nine `_MoneyPhantom` destructor calls survive in the standalone body (verdict
unknown: `??1_MoneyPhantom` has no retail address), so it loses.

Observed (target facts from this TU's objects, model claude-opus-5-5, t=45):
- The standalone COMDAT never inlines a callee that needs EH unwinding
  (implicit dtor of a struct with a non-trivial member; a member function with
  an EH local): explicit `~_MoneyPhantom() {}`, `__forceinline`, `throw()` /
  `__declspec(nothrow)` on ~_MoneyLeak, a wrapper `_MoneyKill(this)` all keep
  the calls (do_put stays exact).
- Every EH-free filler (nop member, `_MoneyLeak()` temporary, `_MoneyNop(0)`
  with up to 100 dead statements, `_MoneyKill(this, 0)` guarding the dtor call,
  `if (this == 0) exit(1)` x6..32 after the deallocate) gives retail's 14 B
  standalone copy but do_put then calls ~basic_string at the three currency
  sites where retail calls ~_String_base (6+3 -> 9). Guards placed before the
  deallocate are not folded in the standalone copy.
- So the outlining at those sites is caused by the EH property of the filler,
  not by its size. Untried: a filler that is EH-requiring only inside do_put's
  frame context; moving the out-of-line ~_String_base calls' origin (unwind
  states of base-only constructed temporaries) to a different construct.
