#!/usr/bin/env python3
"""Rank link blockers by the matched bytes they keep from linking.

A matched row whose unit cannot link is half done: the bytes are proved,
but the unit is not yet part of a buildable game. This reads the last link
census (build/link_census/, written by tools/link_census.py) and says where
a fix pays most.

For every ledger unit it collects what holds the unit back:

  U name   an unresolved name the unit references
  D name   a name the unit and another unit both define
  L name   a COMDAT copy the unit compiled that is not retail's body
           (link_census.keep_rule)
  S name   a name the unit defines or references whose definition the link
           keeps is proven not retail's (link_census wrong_selected)
  A        a hard-coded image address in the source (tools/link_debt.py)

and reports:

  sole     blockers that are a unit's ONLY blocker, by that unit's bytes:
           fix one, a unit links
  names    every blocking name by bytes shared out among the blockers of
           the units it blocks: what a fix moves overall
  near     units with at most --near blockers, largest first: the work list

and, never as a blocker, the diagnostic the census keeps for copies its
`unreferenced` rule exempts (link_census.unreferenced_differs):

  V name   a copy of a no-address COMDAT nothing the link keeps references
           that differs from the majority copy; layout-like (same length, a
           few bytes off) is the signature of a stale private class view

Usage:
  python3 tools/link_rank.py [--top N] [--near K] [--kind U|D|L|S|A] [--json PATH]
  python3 tools/link_rank.py --file SOURCE     one unit's blockers (and V diagnostics)
  python3 tools/link_rank.py --stale-views     units by layout-like V copies

Run tools/link_census.py --history first; this reads the blockers it
recorded (build/link_census/link_index.pkl) and never links anything itself.
"""
import argparse
import collections
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import link_census as lc  # noqa: E402


def blockers():
    """({source: {(kind, name)}}, {source: matched bytes}), the blockers the
    last census itself counted (link_check.census_blockers: its index), so a
    unit this calls linked is one the census counts as linked."""
    import link_check
    rows = lc.ledger()
    census = link_check.census_blockers()
    sizes, seen = collections.Counter(), set()
    for row in rows:
        source = row["source"]
        if not source.lower().endswith((".c", ".cpp")):
            continue
        key = (source, row["target_rva"])
        if key not in seen:
            seen.add(key)
            sizes[source] += int(row["target_size"] or 0, 0)
    out = {}
    for source, entry in census.items():
        found = {("U", s) for s in entry["unresolved"]}
        found |= {("D", s) for s in entry["duplicates"]}
        found |= {("L", s) for s in entry["losers"]}
        found |= {("S", s) for s in entry.get("wrong_selected", ())}
        if entry["addresses"]:
            found.add(("A", ""))
        out[source] = found
    return out, sizes


def stale_views():
    """{source: [unreferenced_differs entry]} from the last census's index."""
    import link_check
    return {source: entry.get("unreferenced_differs", [])
            for source, entry in link_check.census_blockers().items() if entry.get("unreferenced_differs")}


def generated(source):
    return source.startswith(("Code/gen_asm/", "Code/gen_small/"))


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--top", type=int, default=30)
    parser.add_argument("--near", type=int, default=3)
    parser.add_argument("--kind", choices="UDLSA")
    parser.add_argument("--file")
    parser.add_argument("--json", help="write {source: [[kind, name], ...]} here")
    parser.add_argument("--stale-views", action="store_true",
                        help="list units by layout-like V copies (diagnostic, not blockers), largest first")
    parser.add_argument("--all-kinds", action="store_true",
                        help="with --stale-views: count every V copy, codegen-like and relocation too")
    args = parser.parse_args(argv)
    found, sizes = blockers()
    if args.stale_views:
        views = stale_views()
        names = collections.Counter()
        listed = []
        for source, entries in views.items():
            picked = [e for e in entries if args.all_kinds or e["kind"] == "layout"]
            if picked:
                listed.append((source, picked))
                names.update(e["name"] for e in picked)
        listed.sort(key=lambda item: (-len(item[1]), -sizes[item[0]]))
        linked = {s for s, b in found.items() if not b}
        print(f"{len(listed):,} units hold {sum(len(p) for _, p in listed):,} "
              f"{'differing' if args.all_kinds else 'layout-like'} unreferenced copies "
              f"({sum(sizes[s] for s, _ in listed):,} matched bytes; diagnostic, not blockers)")
        for source, picked in listed[:args.top]:
            print(f"  {len(picked):4} {sizes[source]:8,} {'links' if source in linked else '     '}  {source}  "
                  f"[{'; '.join(e['name'][:60] for e in picked[:3])}{'; ...' if len(picked) > 3 else ''}]")
        print("\nnames:")
        for name, count in names.most_common(args.top):
            print(f"  {count:4} units  {name[:150]}")
        return 0
    if args.json:
        Path(args.json).write_text(json.dumps({s: sorted(b) for s, b in found.items()}), encoding="utf-8")
    if args.file:
        names = sorted(found.get(args.file, ()))
        print(f"{args.file}: {sizes[args.file]} matched bytes, "
              f"{'links' if not names else f'{len(names)} blocker(s)'}")
        for kind, name in names:
            print(f"  {kind} {name}")
        for entry in stale_views().get(args.file, ()):
            import link_check
            print(f"  V {entry['name']}  ({link_check.describe_differ(entry)}; not a blocker)")
        return 0
    authored = {s: b for s, b in found.items() if not generated(s)}
    linked = [s for s, b in authored.items() if not b]
    print(f"{len(linked):,} of {len(authored):,} authored units link "
          f"({sum(sizes[s] for s in linked):,} of {sum(sizes[s] for s in authored):,} matched bytes)")

    def wanted(item):
        return args.kind is None or item[0] == args.kind

    sole, sole_units = collections.Counter(), collections.Counter()
    share, share_units = collections.Counter(), collections.Counter()
    for source, items in authored.items():
        if len(items) == 1:
            item = next(iter(items))
            sole[item] += sizes[source]
            sole_units[item] += 1
        for item in items:
            share[item] += sizes[source] / len(items)
            share_units[item] += 1

    def label(item):
        return f"{item[0]} {item[1] or '(source has a hard-coded image address)'}"

    print(f"\nsole blockers (fix one, these units link):")
    for item, value in [(i, v) for i, v in sole.most_common() if wanted(i)][:args.top]:
        print(f"  {value:8,} {sole_units[item]:4} units  {label(item)[:150]}")
    print(f"\nblocking names by shared bytes:")
    for item, value in [(i, v) for i, v in share.most_common() if wanted(i)][:args.top]:
        print(f"  {int(value):8,} {share_units[item]:4} units  {label(item)[:150]}")
    print(f"\nunits within {args.near} blocker(s) of linking:")
    near = sorted((s for s, b in authored.items() if 0 < len(b) <= args.near and all(wanted(i) for i in b)),
                  key=lambda s: -sizes[s])
    for source in near[:args.top]:
        names = "; ".join(label(i)[:70] for i in sorted(authored[source]))
        print(f"  {sizes[source]:7,}  {source}  [{names}]")
    return 0


if __name__ == "__main__":
    sys.exit(main())
