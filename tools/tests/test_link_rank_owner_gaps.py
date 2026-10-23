"""Ownership discovery must not turn additive address hints into identities."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from link_rank import owner_gaps


def row(name, rva, source="Code/provider.cpp", status="matched"):
    return dict(name=name, target_rva=hex(rva), source=source, status=status)


class OwnerGapsTest(unittest.TestCase):
    def test_preserves_all_additive_candidates_and_deduplicates(self):
        result = owner_gaps({"Code/user.cpp": {("U", "call")}}, {"Code/user.cpp": 100},
                            [row("other", 16), row("call", 32)], {"call": [16, 32, 16]})
        self.assertEqual([c["rva"] for c in result[0]["candidates"]], ["0x00000010", "0x00000020"])
        self.assertEqual([c["kind"] for c in result[0]["candidates"]], ["identity-gap", "provider-refresh"])
        self.assertEqual(result[0]["affected_bytes"], 100)

    def test_ranks_by_all_remaining_blockers_not_only_mapped_calls(self):
        found = {"Code/a.cpp": {("U", "one"), ("S", "wrong"), ("A", "")},
                 "Code/b.cpp": {("U", "two")}}
        result = owner_gaps(found, {"Code/a.cpp": 300, "Code/b.cpp": 200},
                            [row("a", 16), row("b", 32)], {"one": [16], "two": [32]})
        self.assertEqual([r["name"] for r in result], ["two", "one"])
        self.assertEqual(result[1]["shared_bytes"], 100)
        self.assertEqual(result[1]["min_blockers"], 3)

    def test_generated_owner_requires_recovery_and_generated_consumer_is_skipped(self):
        result = owner_gaps({"Code/user.cpp": {("U", "call")},
                             "Code/gen_asm/dump.asm": {("U", "call")}},
                            {"Code/user.cpp": 100, "Code/gen_asm/dump.asm": 1000},
                            [row("call", 16, "Code/gen_small/body.cpp")], {"call": [16]})
        self.assertEqual(result[0]["consumers"], ["Code/user.cpp"])
        self.assertEqual(result[0]["candidates"][0]["kind"], "recovery")

    def test_ignores_missing_addresses_unmatched_rows_and_non_unresolved_blockers(self):
        self.assertEqual(owner_gaps({"Code/a.cpp": {("S", "one"), ("U", "two"), ("U", "three")}},
                                   {}, [row("b", 32, status="partial")],
                                   {"one": [16], "two": [32], "three": [48]}), [])

    def test_shared_provider_counts_each_consumer_once(self):
        result = owner_gaps({"Code/a.cpp": {("U", "call")}, "Code/b.cpp": {("U", "call")}},
                            {"Code/a.cpp": 100, "Code/b.cpp": 50},
                            [row("call", 16), row("call", 16)], {"call": [16]})
        self.assertEqual(result[0]["affected_bytes"], 150)
        self.assertEqual(len(result[0]["candidates"]), 1)


if __name__ == "__main__":
    unittest.main()
