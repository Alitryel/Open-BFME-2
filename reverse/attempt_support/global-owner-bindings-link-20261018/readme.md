Two consumers now bind the single existing owner of their retail storage.

* Rva0059EB6FBox: target cmp [0x00E02324],0 tests the pointer already owned
  as GameSpyStagingRoom *TheGameSpyGame by CreateAHeroManagerList. Replace
  the integer-flag alias with that declaration. Body remains exactly 64B.
* GlobalArrayIndexGetters: VA DBEC90 is the already rowed 68B pointer table
  BfmeThingClassNames, not a second unsigned array. Return its indexed
  pointer as the existing integer ABI. Both 12B getters remain exact.

Paired current LEGACY previews: GameSpy 73 -> 137B; getters 0 -> 24B.
The consumers newly link 88 matched bytes in total. Unchanged owners are
included in the paired checks. Self-strict reusable checks verify all three
consumer functions plus the 17 class-name table/string data rows. This is
not a closed-strict link closure measurement. Normal build.sh gates pass.
No data definitions, pins or ledger bodies are added.

The batch also records the independent rejected ifstream helper suppression
probe in re_attempts.log. Its original source was restored and 14/14 rows
passed; it contributed no gain and its claims were released.
