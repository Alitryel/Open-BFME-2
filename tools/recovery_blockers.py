#!/usr/bin/env python3
"""Local fleet prerequisite queue; never a substitute for origin retail claims.

Use one SQLite file on the same local filesystem for all fleet workers. Evidence
is append-only. Queue leases coordinate investigations only: claim the affected
retail RVAs separately with tools/claims.py, and bank verdicts with re_log.py.
"""
import argparse
from contextlib import closing, contextmanager
import json
import math
import os
from pathlib import Path
import re
import sqlite3
import sys
import time

ROOT = Path(__file__).resolve().parents[1]
STATES = ("open", "in_progress", "blocked", "resolved")
ID = re.compile(r"[a-z0-9][a-z0-9_.-]{0,95}\Z")


class QueueError(ValueError):
    pass


def identifier(value):
    if not isinstance(value, str) or not ID.fullmatch(value):
        raise QueueError("blocker IDs must be lowercase letters/digits/._- (1..96 characters)")
    return value


def nonempty(value, label):
    if not isinstance(value, str) or not value.strip() or "\x00" in value:
        raise QueueError(f"{label} must be nonempty text without NUL")
    return value.strip()


def rva(value):
    try:
        number = int(str(value), 0) if not isinstance(value, int) else value
    except (TypeError, ValueError) as exc:
        raise QueueError(f"invalid RVA: {value!r}") from exc
    if isinstance(value, bool) or not 0 < number <= 0xFFFFFFFF:
        raise QueueError("RVA must be a positive 32-bit address")
    return f"0x{number:08X}"


class BlockerQueue:
    def __init__(self, path, *, clock=time.time):
        self.path = Path(path)
        self.clock = clock
        self.path.parent.mkdir(parents=True, exist_ok=True)
        with closing(self._connect()) as db:
            db.execute("PRAGMA journal_mode=WAL")
            db.executescript("""
                CREATE TABLE IF NOT EXISTS blockers (
                    id TEXT PRIMARY KEY, title TEXT NOT NULL,
                    prerequisite TEXT NOT NULL, affected_rvas TEXT NOT NULL,
                    depends_on TEXT NOT NULL, status TEXT NOT NULL,
                    owner TEXT, lease_until REAL,
                    created_at REAL NOT NULL, updated_at REAL NOT NULL
                );
                CREATE TABLE IF NOT EXISTS evidence (
                    sequence INTEGER PRIMARY KEY AUTOINCREMENT,
                    blocker_id TEXT NOT NULL REFERENCES blockers(id),
                    at REAL NOT NULL, owner TEXT NOT NULL,
                    action TEXT NOT NULL, text TEXT NOT NULL
                );
            """)

    def _connect(self):
        db = sqlite3.connect(self.path, timeout=15)
        db.row_factory = sqlite3.Row
        db.execute("PRAGMA foreign_keys=ON")
        db.execute("PRAGMA synchronous=FULL")
        return db

    @contextmanager
    def _write(self):
        db = self._connect()
        try:
            db.execute("BEGIN IMMEDIATE")
            yield db
            db.commit()
        except BaseException:
            db.rollback()
            raise
        finally:
            db.close()

    @staticmethod
    def _row(db, key):
        row = db.execute("SELECT * FROM blockers WHERE id=?", (identifier(key),)).fetchone()
        if row is None:
            raise QueueError(f"unknown blocker: {key}")
        return row

    def _event(self, db, key, owner, action, evidence, now):
        db.execute("INSERT INTO evidence(blocker_id,at,owner,action,text) VALUES(?,?,?,?,?)",
                   (key, now, owner, action, evidence))

    @staticmethod
    def _active(row, now):
        return row["owner"] is not None and row["lease_until"] is not None and row["lease_until"] > now

    def _editable(self, row, owner, now):
        if self._active(row, now) and row["owner"] != owner:
            raise QueueError(f"blocker {row['id']} is leased by {row['owner']}")

    def _dependencies(self, db, key, dependencies):
        dependencies = sorted({identifier(dep) for dep in dependencies})
        for dep in dependencies:
            self._row(db, dep)
        # Updating an existing row can introduce a cycle, even when every named
        # dependency exists. Check the prospective graph inside the transaction.
        def reaches(node, seen):
            if node == key:
                return True
            if node in seen:
                return False
            seen.add(node)
            return any(reaches(child, seen) for child in json.loads(self._row(db, node)["depends_on"]))
        if any(reaches(dep, set()) for dep in dependencies):
            raise QueueError("dependency cycle")
        return dependencies

    def add(self, key, title, prerequisite, *, owner, evidence, affected_rvas=(), depends_on=()):
        key, owner = identifier(key), nonempty(owner, "owner")
        title, prerequisite = nonempty(title, "title"), nonempty(prerequisite, "prerequisite")
        evidence = nonempty(evidence, "evidence")
        addresses = sorted({rva(address) for address in affected_rvas})
        now = self.clock()
        with self._write() as db:
            if db.execute("SELECT 1 FROM blockers WHERE id=?", (key,)).fetchone():
                raise QueueError(f"blocker already exists: {key}; use update to append evidence")
            dependencies = self._dependencies(db, key, depends_on)
            db.execute("INSERT INTO blockers VALUES(?,?,?,?,?,?,?,?,?,?)",
                       (key, title, prerequisite, json.dumps(addresses), json.dumps(dependencies),
                        "open", None, None, now, now))
            self._event(db, key, owner, "add", evidence, now)
        return self.show(key)

    def update(self, key, *, owner, evidence, title=None, prerequisite=None,
               affected_rvas=(), depends_on=(), status=None):
        owner, evidence = nonempty(owner, "owner"), nonempty(evidence, "evidence")
        if status is not None and status not in ("open", "blocked"):
            raise QueueError("update status must be open or blocked; use claim/resolve for other transitions")
        now = self.clock()
        with self._write() as db:
            row = self._row(db, key)
            self._editable(row, owner, now)
            addresses = sorted(set(json.loads(row["affected_rvas"])) | {rva(x) for x in affected_rvas})
            dependencies = self._dependencies(db, key, set(json.loads(row["depends_on"])) | set(depends_on))
            state = status or row["status"]
            lease_owner, lease_until = row["owner"], row["lease_until"]
            if status is not None:
                lease_owner = lease_until = None
            db.execute("UPDATE blockers SET title=?,prerequisite=?,affected_rvas=?,depends_on=?,"
                       "status=?,owner=?,lease_until=?,updated_at=? WHERE id=?",
                       (nonempty(title, "title") if title is not None else row["title"],
                        nonempty(prerequisite, "prerequisite") if prerequisite is not None else row["prerequisite"],
                        json.dumps(addresses), json.dumps(dependencies), state, lease_owner, lease_until, now, key))
            self._event(db, key, owner, "update", evidence, now)
        return self.show(key)

    def claim(self, key, *, owner, lease_seconds=14400):
        owner = nonempty(owner, "owner")
        try:
            duration = float(lease_seconds)
        except (TypeError, ValueError) as exc:
            raise QueueError("lease duration must be a finite positive number") from exc
        if not math.isfinite(duration) or not 0 < duration <= 86400:
            raise QueueError("lease duration must be in (0, 86400] seconds")
        now = self.clock()
        with self._write() as db:
            row = self._row(db, key)
            self._editable(row, owner, now)
            if row["status"] in ("blocked", "resolved"):
                raise QueueError(f"blocker is {row['status']}; update --status open with new evidence first")
            unresolved = [dep for dep in json.loads(row["depends_on"])
                          if self._row(db, dep)["status"] != "resolved"]
            if unresolved:
                raise QueueError("unresolved dependencies: " + ", ".join(unresolved))
            db.execute("UPDATE blockers SET status='in_progress',owner=?,lease_until=?,updated_at=? WHERE id=?",
                       (owner, now + duration, now, key))
            self._event(db, key, owner, "claim", f"investigation lease {duration:g}s; retail claims remain separate", now)
        return self.show(key)

    def release(self, key, *, owner, evidence, blocked=False):
        return self._finish(key, owner, evidence, "blocked" if blocked else "open", require_active=False)

    def resolve(self, key, *, owner, evidence):
        return self._finish(key, owner, evidence, "resolved", require_active=True)

    def _finish(self, key, owner, evidence, status, *, require_active):
        owner, evidence = nonempty(owner, "owner"), nonempty(evidence, "evidence")
        now = self.clock()
        with self._write() as db:
            row = self._row(db, key)
            if row["owner"] != owner or (require_active and not self._active(row, now)):
                raise QueueError(f"{owner} does not hold the required lease for {key}")
            db.execute("UPDATE blockers SET status=?,owner=NULL,lease_until=NULL,updated_at=? WHERE id=?",
                       (status, now, key))
            self._event(db, key, owner, "resolve" if status == "resolved" else "release", evidence, now)
        return self.show(key)

    def _decode(self, db, row):
        result = dict(row)
        for field in ("affected_rvas", "depends_on"):
            result[field] = json.loads(result[field])
        now = self.clock()
        result["lease_active"] = self._active(row, now)
        result["lease_expired"] = row["owner"] is not None and not result["lease_active"]
        result["unresolved_dependencies"] = [dep for dep in result["depends_on"]
                                              if self._row(db, dep)["status"] != "resolved"]
        result["claimable"] = (row["status"] in ("open", "in_progress")
                               and not result["lease_active"] and not result["unresolved_dependencies"])
        return result

    def show(self, key):
        with closing(self._connect()) as db:
            result = self._decode(db, self._row(db, key))
            result["evidence"] = [dict(event) for event in db.execute(
                "SELECT sequence,at,owner,action,text FROM evidence WHERE blocker_id=? ORDER BY sequence", (key,))]
            return result

    def list(self, *, status=None, claimable=False):
        if status is not None and status not in STATES:
            raise QueueError("unknown status")
        with closing(self._connect()) as db:
            rows = db.execute("SELECT * FROM blockers ORDER BY created_at,id").fetchall()
            return [item for row in rows if (status is None or row["status"] == status)
                    for item in [self._decode(db, row)] if not claimable or item["claimable"]]


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--db", type=Path,
                        default=Path(os.environ.get("BFME_BLOCKER_DB", ROOT / "build/recovery-blockers.sqlite3")))
    sub = parser.add_subparsers(dest="command", required=True)
    for command in ("add", "update", "claim", "release", "resolve", "show", "list"):
        cmd = sub.add_parser(command)
        if command != "list":
            cmd.add_argument("id")
        if command not in ("show", "list"):
            cmd.add_argument("--owner", default=os.environ.get("BFME_CLAIM_OWNER"))
        if command in ("add", "update", "release", "resolve"):
            cmd.add_argument("--evidence", required=True, help="append diagnostic result or tracked evidence path")
        if command in ("add", "update"):
            cmd.add_argument("--title", required=command == "add")
            cmd.add_argument("--prerequisite", required=command == "add")
            cmd.add_argument("--rva", action="append", default=[])
            cmd.add_argument("--depends-on", action="append", default=[])
        if command == "update":
            cmd.add_argument("--status", choices=("open", "blocked"))
        if command == "claim":
            cmd.add_argument("--lease-seconds", type=float, default=14400)
        if command == "release":
            cmd.add_argument("--blocked", action="store_true")
        if command == "list":
            cmd.add_argument("--status", choices=STATES)
            cmd.add_argument("--claimable", action="store_true")
    args = vars(parser.parse_args(argv))
    command, path = args.pop("command"), args.pop("db")
    if "id" in args:
        args["key"] = args.pop("id")
    if "rva" in args:
        args["affected_rvas"] = args.pop("rva")
    try:
        queue = BlockerQueue(path)
        result = getattr(queue, command)(**args)
        print(json.dumps(result, indent=2, sort_keys=True))
        return 0
    except (QueueError, sqlite3.Error, OSError) as exc:
        print(f"blocker queue: {exc}", file=sys.stderr)
        return 2


if __name__ == "__main__":
    raise SystemExit(main())
