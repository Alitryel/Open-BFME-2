# STLport exception cleanup: +173 B in the legacy link preview

Base BFME2 7b06b38f8a; published index 3f413ed3ff, 2026-10-20 18:52.
Move the existing empty __Named_exception destructor from the /O2 exception
wrapper unit to its existing /Od counterpart. The existing fold pin resolves
its 29-byte retail body at 0x00023850 (std::bad_alloc owner). The /O2 body was
wrong; the /Od body has the retail bytes and relocation. No pin, alias, import,
new identity or authored-body coverage is added.

Paired current-object checks overlay the same four explicit providers onto
the same census: 0/4, 0 B before; 2/4, 173 B after. NamedException.cpp (133 B)
and stlport_ios_failure_dtor.cpp (40 B) have identical before/after object
hashes and now pass the legacy prediction. The two exception provider units
still have independent ordinary/deleting-wrapper copy conflicts. No
closed-strict closure or executable placement gain is claimed. paired.json
records hashes, COMDAT changes, blockers and self-strict receipt status.

Acceptance: normal gate 19/19 touched rows; strict reusable receipts before
and after 24/24 rows across all four explicit providers; EH comparison has
one pre-existing retail_only baseline mismatch and zero new mismatches;
frozen-definition and class gates pass; data enforcement zero findings;
converged ownership ten addresses, zero second names or unjudged rows;
existing pin consistency passes; whitespace clean. All retained COMDAT
bodies are unchanged. Defining the destructor in the /Od unit additionally
emits its vftable and deleting wrapper; their selection is included in the
paired comparison, rather than inferred from source alone.

The established split exception units and existing BFME2 fold pin supply the
identity and compiler-setting evidence. No BFME1 source was imported.

A separate ScriptEngineGetObjectTypes.cpp trial failed twice: externalizing
the vector growth helper or its already fold-pinned push_back changes parent
register allocation/cleanup and loses a funclet. Its source was restored and
4/4 rows reverified; the blocker is logged at 0x00358286 and claims released.
