"""Git batch readers must preserve their protocol without bidirectional pipes."""
import importlib
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
check_csv = importlib.import_module("check_csv")
progress = importlib.import_module("progress")


@pytest.fixture(params=["ledger", "progress"])
def reader(request, monkeypatch, tmp_path):
    module = check_csv if request.param == "ledger" else progress
    monkeypatch.setattr(module, "ROOT", tmp_path)
    call = (lambda paths, ref: check_csv.read_blobs(paths, ref)) if request.param == "ledger" \
        else (lambda paths, ref: progress._batch_git_texts(ref, paths))
    return request.param, module, call


def frame(body):
    return b"0" * 40 + b" blob " + str(len(body)).encode() + b"\n" + body + b"\n"


def expected(kind, body):
    return body if kind == "ledger" else body.decode("utf-8", errors="replace")


def child_transport(monkeypatch, tmp_path, stdout, stderr=b"", returncode=0):
    """Reply before consuming the large request, as a streaming Git child can."""
    reply = tmp_path / "reply.bin"
    error = tmp_path / "error.bin"
    received = tmp_path / "received.bin"
    reply.write_bytes(stdout)
    error.write_bytes(stderr)
    script = tmp_path / "child.py"
    script.write_text(
        "import os, pathlib, stat, sys\n"
        "assert all(stat.S_ISREG(os.fstat(fd).st_mode) for fd in (0, 1, 2))\n"
        "sys.stdout.buffer.write(pathlib.Path(sys.argv[1]).read_bytes())\n"
        "sys.stdout.buffer.flush()\n"
        "sys.stderr.buffer.write(pathlib.Path(sys.argv[2]).read_bytes())\n"
        "sys.stderr.buffer.flush()\n"
        "pathlib.Path(sys.argv[3]).write_bytes(sys.stdin.buffer.read())\n"
        "sys.exit(int(sys.argv[4]))\n"
    )
    real_run = subprocess.run
    calls = []

    def run(argv, **kwargs):
        calls.append((argv, kwargs.get("cwd")))
        result = real_run(
            [sys.executable, str(script), str(reply), str(error), str(received), str(returncode)],
            timeout=10, **kwargs,
        )
        # The production exception must retain the original Git command.
        result.args = argv
        return result

    monkeypatch.setattr(subprocess, "run", run)
    return received, calls


def test_large_request_and_early_large_reply(reader, monkeypatch, tmp_path):
    kind, _, call = reader
    paths = [f"Code/{i:05d}-" + "long-name-" * 7 + ".cpp" for i in range(2048)]
    body = b"line one\nembedded\0byte\xff\r\n" * 64
    reply = frame(body) * len(paths)
    errors = b"diagnostic\n" * 16384
    received, calls = child_transport(monkeypatch, tmp_path, reply, errors)
    result = call(paths, "HEAD")
    assert result == {path: expected(kind, body) for path in paths}
    request = "".join(f"HEAD:{path}\n" for path in paths).encode()
    assert len(request) > 65536 and len(reply) > 65536 and len(errors) > 65536
    assert received.read_bytes() == request
    argv, cwd = calls[0]
    assert argv == (["git", "-C", str(tmp_path), "cat-file", "--batch"]
                    if kind == "ledger" else ["git", "cat-file", "--batch"])
    assert cwd == (None if kind == "ledger" else tmp_path)


def test_nonzero_child_preserves_failure_payload(reader, monkeypatch, tmp_path):
    kind, _, call = reader
    stdout = b"partial\0response\n" * 8192
    stderr = b"fatal: failed batch\n" * 8192
    child_transport(monkeypatch, tmp_path, stdout, stderr, 37)
    if kind == "ledger":
        with pytest.raises(subprocess.CalledProcessError) as caught:
            call(["Code/a.cpp"], "HEAD")
        assert caught.value.returncode == 37
        assert caught.value.cmd == ["git", "-C", str(tmp_path), "cat-file", "--batch"]
        assert caught.value.output == stdout
        assert caught.value.stderr == stderr
    else:
        with pytest.raises(SystemExit) as caught:
            call(["Code/a.cpp"], "HEAD")
        assert str(caught.value) == "cannot read naked sources at HEAD: " + stderr.decode().strip()


@pytest.mark.parametrize("payload,paths,ledger_exception", [
    (b"HEAD:a missing\n", ["a"], SystemExit),
    (b"", ["a"], ValueError),
    (b"malformed\n", ["a"], IndexError),
    (frame(b"complete") + b"unfinished header", ["a", "b"], ValueError),
    (b"0" * 40 + b" blob 100\nshort", ["a", "b"], ValueError),
])
def test_missing_malformed_and_truncated_batch_preserve_parser_errors(
        reader, monkeypatch, payload, paths, ledger_exception):
    kind, _, call = reader

    def run(argv, **kwargs):
        kwargs["stdout"].write(payload)
        return subprocess.CompletedProcess(argv, 0)

    monkeypatch.setattr(subprocess, "run", run)
    with pytest.raises(ledger_exception if kind == "ledger" else SystemExit):
        call(paths, "HEAD")


def test_final_short_body_keeps_existing_parser_behavior(reader, monkeypatch):
    # These readers historically slice the final body without an extent check.
    # Changing that decision is separate from repairing their subprocess transport.
    kind, _, call = reader

    def run(argv, **kwargs):
        kwargs["stdout"].write(b"0" * 40 + b" blob 100\nshort")
        return subprocess.CompletedProcess(argv, 0)

    monkeypatch.setattr(subprocess, "run", run)
    assert call(["a"], "HEAD") == {"a": expected(kind, b"short")}


def test_real_git_index_batch_with_binary_blob(reader, monkeypatch, tmp_path):
    kind, _, call = reader
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    body = b"line\n\0binary\xff\r\n" * 128
    (tmp_path / "binary.cpp").write_bytes(body)
    subprocess.run(["git", "add", "binary.cpp"], cwd=tmp_path, check=True)
    # Both request and response exceed the pipe capacity of the observed failure.
    paths = ["binary.cpp"] * 8192
    real_run = subprocess.run

    def bounded(argv, **kwargs):
        return real_run(argv, timeout=10, **kwargs)

    monkeypatch.setattr(subprocess, "run", bounded)
    assert call(paths, "") == {"binary.cpp": expected(kind, body)}


def test_progress_empty_paths_do_not_launch_git(monkeypatch):
    def unexpected(*args, **kwargs):
        raise AssertionError("empty progress batch launched Git")
    monkeypatch.setattr(subprocess, "run", unexpected)
    assert progress._batch_git_texts("HEAD", []) == {}


def test_ledger_worktree_reads_do_not_launch_git(monkeypatch, tmp_path):
    def unexpected(*args, **kwargs):
        raise AssertionError("worktree read launched Git")
    monkeypatch.setattr(subprocess, "run", unexpected)
    monkeypatch.setattr(check_csv, "ROOT", tmp_path)
    (tmp_path / "body.cpp").write_bytes(b"\0\xff\n")
    assert check_csv.read_blobs(["body.cpp"], None) == {"body.cpp": b"\0\xff\n"}
    assert check_csv.read_blobs([], None) == {}
