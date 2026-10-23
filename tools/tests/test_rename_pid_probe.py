"""rename.journal_alive must probe a process without signalling it.

On Windows os.kill(pid, 0) sends CTRL_C_EVENT to the pid's console group; the
liveness check interrupted whatever shared the console (a pytest run dies at
test_live_journal_is_left_alone with KeyboardInterrupt).
"""
import os
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import rename  # noqa: E402


def test_pid_probe_never_signals(monkeypatch):
    if os.name == "nt":
        monkeypatch.setattr(rename.os, "kill", lambda *a: (_ for _ in ()).throw(AssertionError("os.kill")))
    assert rename._pid_alive(os.getpid())
    assert rename._pid_alive(os.getppid())


def test_pid_probe_sees_an_exited_process():
    child = subprocess.Popen([sys.executable, "-c", "pass"])
    child.wait()
    assert not rename._pid_alive(child.pid) or os.name != "nt"
    assert not rename._pid_alive(0)
