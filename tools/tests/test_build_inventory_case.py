"""Shared include inventories must agree with each receipt's root spelling."""
import os
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build


def test_windows_inventory_cache_preserves_root_spelling(tmp_path):
    if os.name != "nt":
        import pytest
        pytest.skip("Windows path equality folds case")
    first = tmp_path / "Wwutil"
    first.mkdir()
    (first / "Existing.h").write_text("// existing include\n")
    second = tmp_path / "WWutil"
    assert first.samefile(second)
    expected_first = build._inventory_for_roots([first])
    expected_second = build._inventory_for_roots([second])
    cache = {}
    assert build._inventory_for_roots([first], cache) == expected_first
    assert build._inventory_for_roots([second], cache) == expected_second
    assert build._inventory_cache_still_current(cache)
    (first / "Added.h").write_text("// newly shadowing include\n")
    assert not build._inventory_cache_still_current(cache)
