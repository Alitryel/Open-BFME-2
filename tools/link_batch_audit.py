"""Report linking regressions once for an outgoing push, using verified objects.

This is a shadow audit. A census index at the pushed base supplies the before
state; the byte gate supplies current objects for the changed source scope.
"""

import argparse
import collections
import subprocess
import sys
from pathlib import Path

import build
import link_census
import link_check


def git(*args):
    return subprocess.run(("git", *args), cwd=link_check.ROOT, check=True,
                          capture_output=True, text=True).stdout.strip()


def changed_sources(base, tip):
    names = git("diff", "--name-only", base, tip, "--", "Code").splitlines()
    return {name for name in names if Path(name).suffix.lower() in (".cpp", ".c", ".asm")}


def definitions(index, name, rank):
    """Link-order definitions of one name, with census retail verdicts."""
    objects = index["objects"]
    copies = {objects[i]: (digest, verdict) for i, digest, verdict in index["comdat"].get(name, ())
              if objects[i] in rank and objects[i] not in index.get("forgotten", ())}
    strong = {objects[i] for i in index["strong"].get(name, ())
              if objects[i] in rank and objects[i] not in index.get("forgotten", ())}
    return copies, strong


def selected(index, name, rank):
    copies, strong = definitions(index, name, rank)
    definers = set(copies) | strong
    if not definers:
        return None, None
    holder = min(definers, key=rank.__getitem__)
    exceptions = index["selection"]["exceptions"]
    if name in exceptions:
        position = exceptions[name]
        exception = index["objects"][position] if position is not None else None
        holder = exception if exception is None or exception in definers else holder
    verdict = link_census.judge_selected(holder, copies, definers, strong,
                                         index["selection"]["owners"].get(name, set()))
    return holder, verdict


def overlay(index, replacements, removed, truth):
    """Copy table containers, preserving the saved index for before comparisons."""
    updated = dict(index)
    for key in ("strong", "comdat", "common", "alternates", "blockers", "digests"):
        updated[key] = dict(index[key])
    updated["objects"] = list(index["objects"])
    updated["forgotten"] = set(index.get("forgotten", ()))
    if "references" in index:
        graph = index["references"]
        updated["references"] = {**graph, "edges": dict(graph["edges"]),
                                 "referenced": set(graph["referenced"])}
    link_check.forget(updated, removed)
    for obj in replacements:
        if obj.name not in updated["objects"]:
            updated["objects"].append(obj.name)
        updated["forgotten"].discard(obj.name)
    link_check.refresh(updated, replacements, truth)
    return updated


def audit(base, tip, verified):
    changes = changed_sources(base, tip)
    if not changes and not verified:
        print("link batch audit: no changed source objects")
        return
    if not link_check.INDEX.exists():
        print("link batch audit: INCONCLUSIVE: census index missing; fetch with link_check.py --fetch-index")
        return
    index = link_check.load_index()
    meta = index.get("meta", {})
    exact_base = bool(meta.get("commit") and base.startswith(meta["commit"]) and
                      meta.get("clean_tree", True))
    if not exact_base:
        print(f"link batch audit: INCONCLUSIVE baseline: index at {meta.get('commit', '?')}, "
              f"outgoing base {base}; findings below are provisional since-index changes")
    try:
        link_check.require_common_index(index)
    except SystemExit as exc:
        print(f"link batch audit: INCONCLUSIVE: {exc}")
        return
    rows = link_census.ledger()
    truth = link_census.RetailTruth(rows)
    sources = {row["source"] for row in rows} | {row["source"] for row in link_census.data_ledger()}
    scope = (changes | set(verified)) & sources
    old_by_source = {source: entry["object"] for source, entry in index["blockers"].items()
                     if "object" in entry}
    removed = {old_by_source[source] for source in changes if source in old_by_source and source not in sources}
    replacements = []
    missing = []
    for source in sorted(scope):
        obj = build.obj_path(link_check.ROOT / source)
        if not obj.is_file() or not link_census.object_current(link_check.ROOT / source, obj):
            missing.append(source)
        else:
            replacements.append(obj)
    if missing:
        print(f"link batch audit: INCONCLUSIVE: {len(missing)} source object(s) lack current receipts; "
              f"first: {missing[0]}")
        return
    # A changed ledger may remove an object without deleting its source path.
    current_objects = {build.obj_path(link_check.ROOT / source).name for source in sources}
    removed |= {obj for source, obj in old_by_source.items() if source not in sources and obj not in current_objects}
    before_rank = {name: i for i, name in enumerate(index["objects"])
                   if name not in index.get("forgotten", ())}
    after_rank = link_check.link_rank(rows)
    updated = overlay(index, replacements, removed, truth)
    updated["selection"] = {**index["selection"], "owners": dict(link_census.ledger_owners(rows))}
    touched = set()
    changed_objects = removed | {obj.name for obj in replacements}
    for name, entries in index["comdat"].items():
        if any(index["objects"][i] in changed_objects for i, _, _ in entries):
            touched.add(name)
    for name, entries in index["strong"].items():
        if any(index["objects"][i] in changed_objects for i in entries):
            touched.add(name)
    for obj in replacements:
        copies, strong, _, _ = link_census.object_facts(obj, truth)
        touched.update(name for name, _, _, _ in copies)
        touched.update(strong)
    findings = []
    for name in sorted(touched):
        old_holder, old_verdict = selected(index, name, before_rank)
        new_holder, new_verdict = selected(updated, name, after_rank)
        if old_holder != new_holder and old_verdict != "wrong" and new_verdict == "wrong":
            findings.append((name, old_holder, new_holder, "wrong selected provider"))
        elif old_holder and not new_holder and old_verdict != "wrong":
            findings.append((name, old_holder, None, "provider disappeared"))
    lost = collections.Counter()
    for source in sorted(scope):
        prior = index["blockers"].get(source, {})
        if not prior.get("linked"):
            continue
        obj = build.obj_path(link_check.ROOT / source)
        result = link_check.check_object(obj, updated, truth, source)
        for name in result["unresolved"]:
            before, _ = selected(index, name, before_rank)
            after, _ = selected(updated, name, after_rank)
            lost[(name, before, after, "unresolved in " + source)] += index["bytes"].get(source, 0)
    print(f"link batch audit: {len(replacements)} current object(s), {len(removed)} retired; "
          f"index {meta.get('date', '?')} at {base}")
    for name, before, after, reason in findings:
        print(f"  REVIEW {reason}: {name}; selected {before or '(none)'} -> {after or '(none)'}; "
              "affected consumer bytes require census confirmation")
    for (name, before, after, reason), byte_count in sorted(lost.items()):
        label = "LOST" if exact_base else "POSSIBLE LOSS"
        print(f"  {label} {byte_count:,} previously linked source bytes: {reason}: {name}; "
              f"provider {before or '(none)'} -> {after or '(none)'}")
    if findings or lost:
        print("link batch audit: SHADOW findings; verify affected consumers and record repairs")
    elif not exact_base:
        print("link batch audit: INCONCLUSIVE: no provisional finding from the older index")
    else:
        print("link batch audit: no selected-provider change or changed-unit unresolved blocker found")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--base", required=True)
    parser.add_argument("--tip", required=True)
    parser.add_argument("--sources-from", metavar="FILE", required=True,
                        help="NUL-delimited byte-verified source paths")
    args = parser.parse_args()
    raw = Path(args.sources_from).read_bytes()
    if raw and not raw.endswith(b"\0"):
        raise ValueError("unterminated verified source list")
    verified = [part.decode("utf-8") for part in raw.split(b"\0") if part]
    try:
        audit(args.base, args.tip, verified)
    except (OSError, ValueError, KeyError, SystemExit, subprocess.CalledProcessError,
            link_census.MissingObject) as exc:
        print(f"link batch audit: INCONCLUSIVE: {exc}")
    return 0  # reporting mode


if __name__ == "__main__":
    sys.exit(main())
