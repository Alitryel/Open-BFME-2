#!/usr/bin/env python3
"""Check a discovery checkpoint against retail; this does not verify C++ claims."""
import argparse
import csv
import hashlib
import json
from pathlib import Path

import build
from capstone import Cs, CS_ARCH_X86, CS_MODE_32


def sha256(path):
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, "sha256").hexdigest()


def read_ranges(path):
    with path.open(encoding="utf-8", newline="") as stream:
        return [tuple(int(row[key], 16) for key in
                      ("entry_rva", "start_rva", "end_exclusive"))
                for row in csv.DictReader(stream, delimiter="\t")]


def require(condition, message):
    if not condition:
        raise ValueError(message)


def check(directory, baseline_ranges=None):
    manifest = json.loads((directory / "manifest.json").read_text(encoding="utf-8"))
    require(manifest["schema_version"] == 1, "Unsupported checkpoint schema")
    for name, expected in manifest["files"].items():
        require(Path(name).name == name, "Manifest paths must be simple filenames")
        require(sha256(directory / name) == expected, f"Artifact hash mismatch: {name}")
    image, sections = build.exe_image()
    require(hashlib.sha256(image).hexdigest() == manifest["baseline_sha256"],
            "Retail image hash mismatch")
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    text_start = int(manifest["text_start"], 16)
    text_end = int(manifest["text_end_exclusive"], 16)
    occupied = bytearray(text_end)
    entries, ranges, total = set(), [], 0
    with (directory / "validated-entries.jsonl").open(encoding="utf-8") as stream:
        for line in stream:
            record = json.loads(line)
            entry = int(record["entry"], 16)
            require(entry not in entries, f"Duplicate entry {entry:#x}")
            require(not record["issues"], f"Unresolved accepted entry {entry:#x}")
            require(any(key in record for key in
                        ("entry_evidence", "evidence", "registrations")),
                    f"Missing entry provenance {entry:#x}")
            entries.add(entry)
            body_hash, size, contains_entry = hashlib.sha256(), 0, False
            for low, high in record["ranges"]:
                low, high = int(low, 16), int(high, 16)
                require(text_start <= low < high <= text_end, "Range outside .text")
                require(not any(occupied[low:high]), f"Overlapping range {low:#x}")
                occupied[low:high] = b"\1" * (high - low)
                contains_entry |= low <= entry < high
                offset = build.rva_to_file_offset(sections, low)
                body = image[offset:offset + high - low]
                require(len(body) == high - low, "Truncated retail range")
                body_hash.update(body)
                cursor = low
                for instruction in decoder.disasm(body, low):
                    require(instruction.address == cursor, "Noncontiguous decode")
                    cursor += instruction.size
                require(cursor == high, f"Undecodable range ending at {high:#x}")
                size += high - low
                ranges.append((entry, low, high))
            require(contains_entry, f"Entry outside its ranges: {entry:#x}")
            require(size == record["body_bytes"], f"Size mismatch: {entry:#x}")
            require(body_hash.hexdigest() == record["retail_body_sha256"],
                    f"Body hash mismatch: {entry:#x}")
            total += size
    require(sorted(ranges) == read_ranges(directory / "ranges.tsv"),
            "Range export differs from evidence")
    seed_entries = set()
    for line in (directory / "seeds.tsv").read_text(encoding="utf-8").splitlines():
        if not line or line.startswith("#"):
            continue
        address, size, name = line.split("\t")
        entry = int(address, 16)
        require(size == "0", "Seed must not force a body extent")
        require(name == f"boundary_rva_{entry:08x}", "Unexpected seed identity")
        require(entry not in seed_entries, "Duplicate seed")
        seed_entries.add(entry)
    require(seed_entries == entries, "Seeds differ from accepted entries")
    require(len(entries) == manifest["added_entries"], "Entry count mismatch")
    require(len(ranges) == manifest["added_ranges"], "Range count mismatch")
    require(total == manifest["added_body_bytes"], "Byte count mismatch")
    if baseline_ranges:
        require(sha256(baseline_ranges) ==
                manifest["original_inventory"]["input_hashes"]["function_ranges"],
                "Original range export hash mismatch")
        original = read_ranges(baseline_ranges)
        require(not entries.intersection(entry for entry, _, _ in original),
                "Entry already present in original inventory")
        for _, low, high in original:
            require(not any(occupied[low:high]), "Overlap with original inventory")
            occupied[low:high] = b"\1" * (high - low)
        census = manifest["final_census"]
        require(len(entries | {entry for entry, _, _ in original}) ==
                census["mapped_text_entries"], "Combined entry count mismatch")
        require(sum(occupied) == census["mapped_body_bytes"], "Combined byte count mismatch")
    print(f"Checkpoint OK: {len(entries):,} entries, {total:,} retail bytes; "
          f"original-map overlap check {'passed' if baseline_ranges else 'not requested'}.")
    print("This checks artifact integrity and decoding; entry semantics and control-flow "
          "proofs remain in the recorded discovery evidence.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("directory", type=Path)
    parser.add_argument("--baseline-ranges", type=Path,
                        help="Original Ghidra function_ranges.tsv (hash must match manifest)")
    args = parser.parse_args()
    check(args.directory, args.baseline_ranges)
