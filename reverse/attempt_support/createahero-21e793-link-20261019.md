# CreateAHero whole-file admission blocker

The complete844-line CreateAHero.cpp was read, including prior constructor
attempts. No source or pin edit was made. Official build33/33 is exact and all
eight native parent EH graphs are EXACT. Handler76E968 of constructor21E793
is unrowed. Its nine native cleanup addresses already belong to the real
subclass destructor in BfmePod216Dtor.cpp, so they must not be stolen/recounted.

Current link preview against26f19e6e34:0->0 of3434 own bytes, with eight
unresolved names, one differing insert_unique COMDAT and three selected
providers proven wrong. Do not bank the handler from this unlinked unit.
Detailed local results: build/resume-oct19-createahero-preflight.log and
build/resume-oct19-createahero-eh.json.

Six unresolved code names have known actual owners:
- INI::loadFile at2DC75 returns unsigned char (195B INI_loadFile.cpp);
  this caller declares void. Same parameters, but different decorated name.
- BfmeStringPresenceValue::isEmpty at1E2F is the rowed20B
  StringBase<char>::isEmpty in Common/System/AsciiString.cpp. The caller also
  has a real inline specialization; changing which spelling is called must
  preserve its global reload/register scheduling.
- Subclass count21BC2C is the39B Rva0021BC2CWrapper.cpp member, currently
  non-const and address-class-named; map+24 and value vector14/18 agree.
- Find wrapper21D120 is Rva0021D120Find in StlSweepR3Rva0021D120.cpp,
 27B, returning const Rva0021BBDCRecord*, taking const ranges and a
 StringBase<char>* key. Actual record16B string at+8 agrees with bling lookup.
- Record destructor21F8F3 is104B Rva0021F876::~ in Rva0021F876Dtor.cpp;
  caller uses constructor-view Rva0021F804. Both are five strings plus
  subclass vector at14; the two view names need ownership reconciliation.
- Manager add/find22020C is179B Rva0021FFEE::rva0022020C
  in Rva0021FFEEDtor.cpp, taking mutable Rva0021F876& and returning its
  address. Caller currently declares void and const Rva0021F804&.

CreateAHeroSystemFieldParse atBE6888 has a provisional data-ledger record
but no definition found in Code; CreateAHeroClassFieldParse atDBA0D8 likewise
has only this caller declaration. Both complete native tables and their
callback bindings need proper providers. No fake array/alias was introduced.

The remaining STLport findings are insert_unique's hinted overload COMDAT,
selected int-map iterator increment/decrement and vector<unsigned>::push_back.
The file already uses declaration-only specializations, so compare the actual
kept providers and current objects before further suppression or renaming.

Companion BfmePod216Dtor.cpp was read completely. It uses ScienceType
vectors at30/3C and a set<BfmeStringRecord0021A940> at54 (record declared as
two ints), whereas this constructor uses NameKeyType vectors and
map<int,AttributeBlingBounds> at54 (group plus three strings). These are
different structural views; this review does not establish which complete
type contracts are right. Reconcile against native parser/accessors and the
actual recursive cleanup providers before moving the shared handler there
merely because its immediate bytes pass.

Inputs: author5c7db225ec, BFME1f52d3a5c, flags retained from source.
This is a dependency handoff, not new C++ coverage or proof of full linkage.
