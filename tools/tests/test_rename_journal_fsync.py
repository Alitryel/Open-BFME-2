"""rename.write_journal must fsync through a writable handle.

On Windows os.fsync on a read-only descriptor fails with EBADF, which made
every non-dry-run rename abort before its first write.
"""
import os
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
sys.path.insert(0, str(Path(__file__).resolve().parent))

import rename  # noqa: E402
from test_rename_fixes import ctx_of, function_plan, make_tree  # noqa: E402


@pytest.fixture
def tree(tmp_path):
    return make_tree(tmp_path)


def test_write_journal_completes_and_is_readable(tree):
    ctx = ctx_of(tree)
    path = rename.write_journal(ctx, function_plan(tree))
    assert path.exists() and not path.with_suffix(".tmp").exists()
    assert len(rename.journals(ctx)) == 1


def test_journal_fsync_gets_a_writable_descriptor(tree, monkeypatch):
    seen = []
    real = os.fsync

    def checked(fd):
        if os.name == "posix":
            import fcntl
            seen.append(fcntl.fcntl(fd, fcntl.F_GETFL) & os.O_ACCMODE != os.O_RDONLY)
        else:
            seen.append(True)
        return real(fd)  # EBADF here on Windows for a read-only handle

    monkeypatch.setattr(rename.os, "fsync", checked)
    rename.write_journal(ctx_of(tree), function_plan(tree))
    assert seen and all(seen)
