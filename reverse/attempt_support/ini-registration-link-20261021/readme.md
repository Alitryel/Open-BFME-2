INI registration providers, 2026-10-21

The current registration unit held 130 exact 21-byte startup bodies but lacked
129 of its 130 node providers. Its current-object link result was 0/2728
nonpadding bytes. This repair defines those existing node names with their
complete native twelve-byte {next, token, callback} contents. All callbacks
already have matched rows; no function name, pin, body or boundary is added.

Target evidence

- Native nodes, tokens and callback RVAs are individually recorded beside the
  definitions in Rva007ABBF6BlockParseInits.cpp. Every initial next word is zero;
  every full token and callback pointer was independently read from game.dat.
  The rowed constructor 0004147D and finder 0002BBFC establish the three fields.
  Existing exact startup bodies establish which named global each links.
- The AptButtonTooltipMap node retains its existing 44-byte data owner in
  Rva00224A3F.cpp; no second owner or truncated replacement is introduced.
- ControlBarResizer's callback is the shared one-byte RET at 000B3FD0. A cast
  of the existing cdecl Rva000B3FD0AptFreeSound row supplies that same address;
  this does not identify the original callback or add another name there.
- Native DC18A8 contains sixteen string pointers and a final null (68 bytes).
  Its field-table consumer passes it to parseBitString16/32; the rowed 002EB38
  implementation casts userData to ConstCharPtrArray and scans bit names.
  The previous LookupListRec[9] view misclassified alternating string pointers
  as integer values and included the next node's initial next word at DC18EC.
  Correcting the existing global to const char *const[17] removes those raw
  addresses and makes room for the complete LivingWorldAnimObject node.
  The global's identifier and address remain unchanged; its mangled type and
  data extent are corrected together. No other source refers to its old type.
- Static-only callback declarations retain exact existing names and cdecl ABI;
  they assert no instance layout. None is a registered canonical class view.

Reference review

Verified BFME1 input 5987fd1b859e86801d093256eadc6fb63d87785f, ini.cpp lines
217-245, carries the same three-word registration pattern. BFME1 tokens,
addresses and callback selections were not transplanted. BFME2's node contents,
providers, bit-name list and ordering are target facts. The previously documented
comparative full-gate blocker still prevents updating the donor pointer; no
freshness stamp or new donor revision is claimed.

Acceptance

Published census index: 17918792f6, 2026-10-21 09:22 UTC. Before and after use
current objects against that same index:

- Registration unit: 0 -> 2728 bytes, LINKS after repair.
- Rva003FD7CEParse: 105 -> 105 bytes, LINKS both times.
- Combined: 105 -> 2833 bytes, gain 2728. These are legacy predictions.
- build.sh both units: 133/133 code rows and 132/132 data rows pass.
- link_check --prepare-current: both providers obtain strict reusable self
  receipts and pass their byte gates. Closed-strict closure was not measured.
- check_csv, data_rows --check, class_gate, find_declared_unmatched and
  data_check --converged pass. The compiler-renumbered parser unwind label is
  resolved through its verified parent EH graph; no funclet row is changed.

No full link cycle, census, nightly or boot runner was started. Scratch command
outputs and the provider audit remain under ignored build/blockparse-link/.
