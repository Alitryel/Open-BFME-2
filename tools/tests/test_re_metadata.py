#!/usr/bin/env python3
"""tools/re_metadata.py: the curated metadata overlay and its Ghidra round trip.

Offline tests need only Python. Tests marked `ghidra` run real analyzeHeadless
processes against fresh private projects built from the synthetic fixture
(tools/tests/fixtures/re_metadata/); they skip, saying so, when Ghidra or the JDK
cannot be found (GHIDRA_INSTALL_DIR / JAVA_HOME or build/toolchains). Keep pytest's
--basetemp and TMPDIR on the work disk: the projects are written there.
Acceptance ids (A01..A18) refer to docs/re_metadata.md.
"""
import copy
import csv
import json
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import ghidra_refdb as refdb  # noqa: E402
import re_metadata as rm  # noqa: E402

FIX = ROOT / "tools" / "tests" / "fixtures" / "re_metadata"
PKG = FIX / "package"
EXE = FIX / "fixture.exe"
PROGRAM = "fixture.exe"


def _ghidra():
    try:
        return refdb.ghidra_home(), refdb.java_home()
    except SystemExit:
        return None


GHIDRA = _ghidra()
ghidra = pytest.mark.skipif(GHIDRA is None, reason="Ghidra/JDK not found (GHIDRA_INSTALL_DIR, JAVA_HOME or "
                                                   "build/toolchains); integration criteria NOT run")


def variant(tmp_path, edit=None, name="pkg"):
    """A copy of the fixture package, edited and re-digested."""
    dest = tmp_path / name
    shutil.copytree(PKG, dest)
    pkg = rm.Package.load(dest)
    if edit:
        edit(pkg)
    for sub in ("functions", "types", "comments"):
        shutil.rmtree(dest / sub, ignore_errors=True)
    pkg.manifest["metadata_sha256"] = pkg.digest()
    pkg.write(dest)
    return dest


def scoped(obs):
    return rm.digest({k: obs[k] for k in ("functions", "types", "comments")})


# ================================================================== offline

def test_canonical_form_is_stable_and_integer_only():
    a = {"b": [1, {"y": "x\n\u0001\"\\", "x": None}], "a": True}
    assert rm.canonical(a) == b'{"a":true,"b":[1,{"x":null,"y":"x\\n\\u0001\\"\\\\"}]}'
    assert rm.digest(a) == rm.digest(json.loads(json.dumps(a)))
    with pytest.raises(rm.MetadataError):
        rm.canonical({"f": 1.5})


def test_managed_segments_preserve_unmanaged_text():
    text = "analyst line\n[re-metadata:s]\nold\n[/re-metadata:s]\nanalyst tail"
    assert rm.segment_text(text, "s") == "old"
    assert rm.with_segment(text, "s", "new") == "analyst line\n[re-metadata:s]\nnew\n[/re-metadata:s]\nanalyst tail"
    removed = rm.with_segment(text, "s", None)
    assert removed == "analyst line\nanalyst tail"
    assert rm.with_segment(removed, "s", None) == removed            # deletion is idempotent
    assert rm.with_segment(None, "s", "v") == "[re-metadata:s]\nv\n[/re-metadata:s]"
    assert rm.with_segment("[re-metadata:s]\nv\n[/re-metadata:s]", "s", None) is None
    assert rm.with_segment("keep", "s", "v") == "keep\n[re-metadata:s]\nv\n[/re-metadata:s]"
    assert rm.with_segment(rm.with_segment("keep", "s", "v"), "s", None) == "keep"
    for bad in ("[re-metadata:s]\nno end", "[re-metadata:s]\na\n[/re-metadata:s]\n[re-metadata:s]\nb\n[/re-metadata:s]"):
        with pytest.raises(rm.MetadataError):
            rm.segment_text(bad, "s")


def test_interval_rules():
    assert rm.range_errors([["0x00001000", "0x00001010"], ["0x00001020", "0x00001030"]], "0x00001000") == []
    assert rm.range_errors([["0x00001000", "0x00001010"]], "0x00001010")            # entry outside
    assert rm.range_errors([["0x00001010", "0x00001000"]])                          # inverted
    assert rm.range_errors([["0x00001000", "0x00001010"], ["0x00001010", "0x00001020"]])   # adjacent
    assert rm.range_errors([["0x00001000", "0x00001010"], ["0x00001008", "0x00001020"]])   # overlap
    assert rm.range_errors([["0xfffffff0", "0x100000000"]])                         # wraps / malformed
    assert rm.range_errors([["0x1000", "0x1010"]])                                  # not fixed width


def test_fixture_package_validates_against_its_executable():
    report = rm.validate(rm.Package.load(PKG), EXE)
    assert report["status"] == "ok", report["errors"]
    assert report["counts"] == {"functions": 12, "types": 5, "comments": 2}


def test_a14_unknown_schema_and_malformed_interval_are_invalid(tmp_path):
    def bad(pkg):
        pkg.records["functions/0x00001000.json"]["body"]["ranges"] = [["0x00001000", "0x00000fff"]]
        pkg.records["functions/0x00001010.json"]["schema"] = "re-metadata/9"
    report = rm.validate(rm.Package.load(variant(tmp_path, bad)))
    assert report["status"] == "invalid"
    assert any("inverted" in e for e in report["errors"])
    assert any("unknown record schema" in e for e in report["errors"])
    pkg = rm.Package.load(variant(tmp_path, name="p2"))
    pkg.manifest["schema"] = "re-metadata/2"
    assert rm.validate(pkg)["errors"] == ["unknown manifest schema 're-metadata/2'"]


def test_a03_validation_names_a_changed_contract(tmp_path):
    roots = tmp_path / "contracts"
    shutil.copytree(FIX / "class_contracts", roots)

    def edit(pkg):
        pkg.manifest["contract_roots"] = [str(roots)]
        for key in ("fx_point", "fx_box"):
            pkg.records[rm.type_record_name(key)]["contract"] = {"path": str(roots / f"{key}.json"),
                                                            "sha256": rm.file_sha256(roots / f"{key}.json")}
    path = variant(tmp_path, edit)
    assert rm.validate(rm.Package.load(path))["status"] == "ok"
    data = json.loads((roots / "fx_point.json").read_text())
    data["fields"][2]["offset"] = 10
    (roots / "fx_point.json").write_text(json.dumps(data))
    errors = rm.validate(rm.Package.load(path))["errors"]
    assert any("fx_point.json changed since the record was made" in e for e in errors)


def test_name_evidence_reuses_the_existing_tier_rules():
    root = FIX / "evidence"
    entry, raw = "0x00001030", "?count@fx_box@@QAEIH@Z"
    row = next(r for r in rm.evidence_rows(root, "reverse/functions.csv") if r["name"] == raw)
    prov = {"identity_tier": "ilt", "evidence_refs": [rm.evidence_ref("ilt", row)]}
    assert rm.check_name_evidence(root, entry, raw, prov)[0] == []
    # A04: a forged tier label over a matched row without ILT evidence.
    forged = next(r for r in rm.evidence_rows(root, "reverse/functions.csv") if r["name"] == "fx_mid")
    problems, _ = rm.check_name_evidence(root, "0x000011e1", "fx_mid",
                                         {"identity_tier": "ilt", "evidence_refs": [rm.evidence_ref("ilt", forged)]})
    assert any("does not admit tier ilt" in p for p in problems)
    # A generated reloc identity is not real evidence either.
    gen = next(r for r in rm.evidence_rows(root, "reverse/reloc_names.csv") if r["name"] == "fx_mid")
    problems, _ = rm.check_name_evidence(root, "0x000011e1", "fx_mid",
                                         {"identity_tier": "reloc", "evidence_refs": [rm.evidence_ref("reloc", gen)]})
    assert any("does not admit tier reloc" in p for p in problems)
    # A tier claimed from the wrong file, and a changed record.
    wrong = {"identity_tier": "export", "evidence_refs": [rm.evidence_ref("ilt", row)]}
    assert rm.check_name_evidence(root, entry, raw, wrong)[0]
    stale = {"identity_tier": "ilt", "evidence_refs": [dict(rm.evidence_ref("ilt", row), sha256="0" * 64)]}
    assert any("evidence changed" in p for p in rm.check_name_evidence(root, entry, raw, stale)[0])
    assert rm.check_name_evidence(root, entry, raw, {"identity_tier": "matched", "evidence_refs": []})[0]


def test_alias_names_are_a_conflict(tmp_path):
    root = tmp_path / "ev"
    shutil.copytree(FIX / "evidence", root)
    with (root / "reverse" / "exports.csv").open("a") as handle:
        handle.write("2,0x000011C7,,.text,code,fx_frag_alias\n")
    row = next(r for r in rm.evidence_rows(root, "reverse/exports.csv") if r["name"] == "fx_frag")
    problems, _ = rm.check_name_evidence(root, "0x000011c7", "fx_frag",
                                         {"identity_tier": "export", "evidence_refs": [rm.evidence_ref("export", row)]})
    assert any("alias conflict" in p and "fx_frag_alias" in p for p in problems)


def test_evidence_names_unchanged_by_the_admits_refactor(tmp_path):
    reverse = tmp_path / "reverse"
    shutil.copytree(FIX / "evidence" / "reverse", reverse)
    assert refdb.evidence_names(reverse) == {
        0x11C7: ("fx_frag", "export"), 0x1010: ("?fx_scale@@YGFPAUfx_point@@H@Z", "ilt"),
        0x1030: ("?count@fx_box@@QAEIH@Z", "ilt"), 0x1000: ("fx_add", "reloc"), 0x1050: ("fx_reset", "reloc"),
        0x1070: ("fx_ratio", "reloc"), 0x1090: ("fx_sum", "reloc"), 0x10C0: ("fx_byval", "reloc"),
        0x10D0: ("fx_wide", "reloc"), 0x11D7: ("fx_hidden", "reloc"), 0x11F3: ("fx_orphan", "reloc")}


def test_a10_a11_fixture_types_resolve_with_dependencies():
    resolved = rm.resolve(rm.Package.load(PKG))
    assert resolved["conflicts"] == [] and resolved["unsupported"] == []
    order = resolved["type_order"]
    assert order.index("/ReMetadata/fx_point") < order.index("/ReMetadata/fx_box")
    assert order.index("/ReMetadata/fx_kind") < order.index("/ReMetadata/fx_box")
    box = resolved["types"]["/ReMetadata/fx_box"]["projection"]
    assert box["size"] == 52 and box["packing"] is False
    assert [(f["name"], f["offset"], f["size"]) for f in box["fields"]] == [
        ("lo", 0, 12), ("hi", 12, 12), ("next", 24, 4), ("kind", 28, 4), ("counts", 32, 16), ("id", 48, 4)]
    assert box["fields"][2]["type"] == {"ptr": {"named": "/ReMetadata/fx_box"}}           # pointer cycle
    assert box["fields"][4]["type"] == {"array": {"prim": "i32"}, "count": 4}
    assert box["fields"][2]["comment"] == "layout_by=bytes; name_by=fixture-source"
    kind = resolved["types"]["/ReMetadata/fx_kind"]["projection"]
    assert kind["signed_state"] == "signed" and kind["values"][0] == ["FX_KIND_NEG", -2]
    flags = resolved["types"]["/ReMetadata/fx_flags"]["projection"]
    assert flags["signed_state"] == "unsigned" and flags["values"][-1] == ["FX_FLAG_HIGH", 0xFFFFFFF0]


def _contract_variant(tmp_path, mutate):
    roots = tmp_path / "contracts"
    shutil.copytree(FIX / "class_contracts", roots)
    data = json.loads((roots / "fx_box.json").read_text())
    mutate(data)
    (roots / "fx_box.json").write_text(json.dumps(data))

    def edit(pkg):
        pkg.manifest["contract_roots"] = [str(roots)]
        for key in ("fx_point", "fx_box"):
            pkg.records[rm.type_record_name(key)]["contract"] = {"path": str(roots / f"{key}.json"),
                                                            "sha256": rm.file_sha256(roots / f"{key}.json")}
    return rm.resolve(rm.Package.load(variant(tmp_path, edit)))


def test_a13_unresolved_and_unsupported_contracts(tmp_path):
    queued = _contract_variant(tmp_path / "q", lambda d: d.update(queue=[{"attribute": "size"}]))
    assert any("unresolved ABI decision" in c["reason"] for c in queued["conflicts"])
    assert "/ReMetadata/fx_box" not in queued["types"]
    # Signatures that use the broken type are not replayed either.
    assert any(u["record"] == "functions/0x00001050.json" for u in queued["unsupported"])
    unresolved = _contract_variant(tmp_path / "u", lambda d: d["fields"].__setitem__(
        5, dict(d["fields"][5], type="Missing")))
    assert any("unresolved field type" in c["reason"] for c in unresolved["conflicts"])
    union = _contract_variant(tmp_path / "n", lambda d: d["fields"].__setitem__(
        3, dict(d["fields"][3], offset=24)))
    assert any("overlaps its predecessor" in u["reason"] for u in union["unsupported"])
    bits = _contract_variant(tmp_path / "b", lambda d: d["fields"].__setitem__(
        3, dict(d["fields"][3], kind="bitfield")))
    assert any("bitfield" in u["reason"] for u in bits["unsupported"])
    vt = _contract_variant(tmp_path / "v", lambda d: d.update(bases=["Base"]))
    assert any("inheritance" in u["reason"] for u in vt["unsupported"])
    byval = _contract_variant(tmp_path / "c", lambda d: d["fields"].__setitem__(
        2, dict(d["fields"][2], type="fx_box", size=52)))
    assert any("by-value cycle" in u["reason"] or "cycle" in u["reason"] for u in byval["unsupported"] + byval["conflicts"])


def test_a11_enum_width_and_signedness_are_enforced(tmp_path):
    def edit(pkg):
        pkg.records[rm.type_record_name("fx_flags")]["layout"]["values"].append(["NEG", -1])
    resolved = rm.resolve(rm.Package.load(variant(tmp_path, edit)))
    assert any("does not fit a unsigned 4-byte enum" in c["reason"] for c in resolved["conflicts"])


def test_a13_signature_classification():
    ts = rm.resolve_types(rm.Package.load(PKG), {k: v for k, v in rm.Package.load(PKG).records.items()
                                                 if k.startswith("types/")})
    ok = {"convention": "__thiscall", "variadic": False, "storage_mode": "dynamic",
          "return": {"type": {"named": "fx_u32"}, "storage": [{"reg": "EAX", "size": 4}]},
          "params": [{"name": "i", "type": {"prim": "i32"}, "storage": [{"stack": 4, "size": 4}]}],
          "auto_params": [{"role": "this", "storage": [{"reg": "ECX", "size": 4}]}]}
    assert rm.signature_problems(ok, ts) == []
    cases = {
        "varargs": dict(ok, variadic=True),
        "custom storage": dict(ok, storage_mode="custom"),
        "convention": dict(ok, convention="__fastcall"),
        "aggregate (or unresolved) return": dict(ok, **{"return": {"type": {"named": "fx_point"}, "storage": []}}),
        "register-pair": dict(ok, **{"return": {"type": {"prim": "i64"}, "storage": [{"reg": "EAX", "size": 4}]}}),
        "aggregate-by-value": dict(ok, params=[{"name": "p", "type": {"named": "fx_box"},
                                                "storage": [{"stack": 4, "size": 52}]}]),
        "duplicate the automatic": dict(ok, params=[{"name": "this", "type": {"prim": "i32"},
                                                     "storage": [{"stack": 4, "size": 4}]}]),
        "split": dict(ok, params=[{"name": "i", "type": {"prim": "i32"},
                                   "storage": [{"reg": "EAX", "size": 2}, {"reg": "EDX", "size": 2}]}]),
        "ambiguous": dict(ok, auto_params=[]),
    }
    for needle, sig in cases.items():
        assert any(needle in w for w in rm.signature_problems(sig, ts)), needle


def test_a13_unexcluded_unsupported_signatures_are_reported(tmp_path):
    pkg = rm.Package.load(variant(tmp_path, lambda p: p.manifest.update(exclusions=[])))
    resolved = rm.resolve(pkg)
    got = {u["record"]: u["reason"] for u in resolved["unsupported"]}
    assert "varargs" in got["functions/0x00001090.json"]
    assert "aggregate-by-value" in got["functions/0x000010c0.json"]
    assert "register-pair" in got["functions/0x000010d0.json"]


def _observation(resolved, pkg, **over):
    """A synthetic observation in which every desired value is still the analysis default."""
    obs = {"schema": rm.OBSERVATION_SCHEMA, "analysis_options": {},
           "program": dict({k: pkg.manifest["target"][k] for k in ("executable_sha256", "image_base", "address_space",
                                                                    "pointer_size", "language_id", "compiler_spec_id")},
                           name=PROGRAM, ghidra_version="12.1.2"),
           "functions": {}, "types": {p: {"projection": None, "parents": []} for p in resolved["types"]},
           "managed_type_paths": [], "comments": {}, "state": None, "baseline": None}
    for entry, fn in resolved["functions"].items():
        body = fn["body"]["desired"]["body"] if "body" in fn else [[entry, rm.rva_text(int(entry, 16) + 1)]]
        obs["functions"][entry] = {
            "exists": True, "entry_rva": entry, "body": body, "name_source": "DEFAULT",
            "name": {"name": f"FUN_{int(entry, 16) + 0x10000000:08x}", "namespace": []},
            "signature": {"convention": "__cdecl", "variadic": False, "storage_mode": "dynamic",
                          "return": {"type": {"prim": "undefined4"}, "storage": [{"reg": "EAX", "size": 4}]},
                          "params": [], "auto_params": []},
            "signature_source": "ANALYSIS", "probe": {"unmapped": None, "overlaps": [], "defined_data": False},
            "name_probe": {"kinds": [], "holders": []}}
    for a, k, _ in resolved["comments"]:
        obs["comments"][f"{a}:{k}"] = None
    obs.update(over)
    return obs


def test_plan_is_deterministic_and_ordered():
    pkg = rm.Package.load(PKG)
    resolved = rm.resolve(pkg)
    a = rm.build_plan(pkg, resolved, _observation(resolved, pkg))
    b = rm.build_plan(pkg, rm.resolve(pkg), _observation(rm.resolve(pkg), pkg))
    assert a == b and a["status"] == "ready"
    kinds = [op["kind"] for op in a["operations"]]
    assert kinds == sorted(kinds, key=rm.OP_ORDER.index)
    assert kinds.count("set_type") == 5 and "set_function_body" not in kinds   # bodies already equal
    assert a["excluded"] and a["plan_sha256"] == rm.digest({k: v for k, v in a.items() if k != "plan_sha256"})


def test_a02_wrong_target_is_rejected_before_any_operation():
    pkg = rm.Package.load(PKG)
    resolved = rm.resolve(pkg)
    for key, value in (("executable_sha256", "1" * 64), ("image_base", "0x00400000"),
                       ("language_id", "x86:LE:64:default")):
        obs = _observation(resolved, pkg)
        obs["program"][key] = value
        with pytest.raises(rm.MetadataError) as err:
            rm.build_plan(pkg, resolved, obs)
        assert err.value.category == "blocked" and key in str(err.value)


def test_plan_conflicts_follow_field_policy():
    pkg = rm.Package.load(PKG)
    resolved = rm.resolve(pkg)
    obs = _observation(resolved, pkg)
    f = obs["functions"]
    f["0x00001000"].update(name={"name": "AnalystName", "namespace": []}, name_source="USER_DEFINED")   # reloc tier
    f["0x00001010"].update(name={"name": "AnalystName2", "namespace": []}, name_source="USER_DEFINED")  # ilt tier
    f["0x00001030"]["name_probe"] = {"kinds": ["clash:Label"], "holders": []}
    f["0x00001050"]["name_probe"] = {"kinds": [], "holders": ["0x00001070"]}
    f["0x000011d7"]["body"] = [["0x000011d7", "0x000011e1"]]                     # differs, no baseline
    f["0x000011e1"]["probe"] = {"unmapped": None, "overlaps": ["0x000011c7"], "defined_data": False}
    f["0x00001070"]["signature_source"] = "USER_DEFINED"
    obs["baseline"] = {"binding": {"executable_sha256": pkg.manifest["target"]["executable_sha256"]}, "functions": {}}
    obs["types"]["/ReMetadata/fx_point"]["projection"] = {"kind": "struct", "size": 4, "fields": []}
    obs["managed_type_paths"] = ["/ReMetadata/fx_kind.conflict"]
    plan = rm.build_plan(pkg, resolved, obs)
    reasons = {(c["record"], c["field"]): c["reason"] for c in plan["conflicts"]}
    assert plan["status"] == "blocked"
    assert "only ilt may" in reasons[("functions/0x00001000.json", "name")]
    assert ("functions/0x00001010.json", "name") not in reasons                  # the ILT oracle may correct it
    assert "namespace collision" in reasons[("functions/0x00001030.json", "name")]
    assert "name collision" in reasons[("functions/0x00001050.json", "name")]
    assert "baseline" in reasons[("functions/0x000011d7.json", "body")]
    assert "overlaps" in reasons[("functions/0x000011e1.json", "body")]
    assert "not a verified analysis baseline" in reasons[("functions/0x00001070.json", "signature")]
    assert "unmanaged layout" in reasons[(rm.type_record_name("fx_point"), "type")]
    assert "suffixed duplicate" in reasons[(rm.type_record_name("fx_kind"), "type")]


def test_managed_values_may_be_updated_and_unmanaged_edits_conflict():
    pkg = rm.Package.load(PKG)
    resolved = rm.resolve(pkg)
    obs = _observation(resolved, pkg)
    old = {"kind": "struct", "size": 12, "fields": []}
    obs["types"]["/ReMetadata/fx_point"]["projection"] = old
    obs["types"]["/ReMetadata/fx_point"]["parents"] = ["/ReMetadata/fx_box"]
    seg = "older text"
    obs["comments"]["0x000011c7:plate"] = f"mine\n[re-metadata:summary]\n{seg}\n[/re-metadata:summary]"
    obs["state"] = {"fields": {"type:/ReMetadata/fx_point": {"digest": rm.digest({"projection": old})},
                               "comment:0x000011c7:plate:summary": {"digest": rm.digest({"segment": seg})}}}
    plan = rm.build_plan(pkg, resolved, obs)
    assert plan["status"] == "ready", plan["conflicts"]
    ops = {(op["kind"], json.dumps(op["target"], sort_keys=True)): op for op in plan["operations"]}
    assert any(op["expected"] == {"projection": old} for op in plan["operations"] if op["kind"] == "set_type")
    assert any(op["expected"] == {"segment": seg} for op in plan["operations"] if op["kind"] == "set_comment_segment")
    obs["state"]["fields"]["comment:0x000011c7:plate:summary"]["digest"] = "0" * 64
    obs["types"]["/ReMetadata/fx_point"]["parents"] = ["/Other/Consumer"]
    plan = rm.build_plan(pkg, resolved, obs)
    reasons = " ".join(c["reason"] for c in plan["conflicts"])
    assert "edited outside the tool" in reasons and "out-of-scope consumers" in reasons
    assert ops


def test_a03_plan_bindings_name_what_changed(tmp_path):
    ev = tmp_path / "ev"
    shutil.copytree(FIX / "evidence", ev)
    path = variant(tmp_path, lambda p: p.manifest.update(evidence_root=str(ev)))
    pkg = rm.Package.load(path)
    resolved = rm.resolve(pkg)
    plan = rm.build_plan(pkg, resolved, _observation(resolved, pkg))
    assert rm.check_plan_bindings(plan, pkg) == []
    rows = (ev / "reverse" / "functions.csv").read_text().replace("ilt-verified=fixture\n?count", "ilt-verified=other\n?count")
    (ev / "reverse" / "functions.csv").write_text(rows)
    rm._CSV_CACHE.clear()
    assert any(c.startswith("evidence record reverse/functions.csv#target_rva=0x00001010")
               for c in rm.check_plan_bindings(plan, pkg))
    tampered = copy.deepcopy(plan)
    tampered["tools"]["tools/ghidra/apply_metadata.java"] = "0" * 64
    tampered["plan_sha256"] = rm.digest({k: v for k, v in tampered.items() if k != "plan_sha256"})
    assert "tool tools/ghidra/apply_metadata.java" in rm.check_plan_bindings(tampered, pkg)
    forged = copy.deepcopy(plan)
    forged["operations"] = forged["operations"][1:]
    assert rm.check_plan_bindings(forged, pkg) == ["plan content (its digest does not match)"]
    pkg.records["comments/0x000011e5-eol-role.json"]["text"] = "changed"
    assert "metadata package (records or manifest)" in rm.check_plan_bindings(plan, pkg)


def test_legacy_tsv_sync_apply_is_refused_before_mutation(tmp_path):
    plan = tmp_path / "plan.tsv"
    plan.write_text("0x00001000\tFUN_00401000\t?Exported@@YAXXZ\texport\n")
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "ghidra_refdb.py"), "sync-apply", "--project",
                           str(tmp_path / "none.gpr"), "--program", "x", "--plan", str(plan)],
                          capture_output=True, text=True)
    assert proc.returncode == rm.EXIT["invalid"]
    assert "regenerate a bound plan" in json.loads(proc.stdout)["error"]


def test_fixture_executable_rebuilds_from_source(tmp_path):
    clang, lld = shutil.which("clang"), shutil.which("lld-link")
    if not (clang and lld):
        pytest.skip("clang/lld-link not available: fixture reproducibility NOT checked")
    recipe = json.loads((FIX / "build.json").read_text())
    obj, exe = tmp_path / "fixture.obj", tmp_path / "fixture.exe"
    subprocess.run([clang, *recipe["clang"], "-c", str(FIX / "src" / "fixture.c"), "-o", str(obj)], check=True)
    subprocess.run([lld, *recipe["lld_link"], f"/out:{exe}", str(obj)], check=True)
    version = subprocess.run([clang, "--version"], capture_output=True, text=True).stdout.split("\n")[0]
    if rm.file_sha256(exe) != recipe["sha256"]:
        pytest.skip(f"{version} builds different bytes than the recorded {recipe['clang_version']}: "
                    "the committed fixture.exe stays the reference")
    assert rm.file_sha256(exe) == rm.file_sha256(EXE)


# ================================================================== Ghidra integration

def _headless(project, log, **kw):
    return rm.run_headless(project.parent, project.stem, program=PROGRAM, log=log, **kw)


@pytest.fixture(scope="module")
def baseline_project(tmp_path_factory):
    """One fresh import + analysis + baseline; tests work on copies of it."""
    if GHIDRA is None:
        pytest.skip("Ghidra not available")
    d = tmp_path_factory.mktemp("baseline")
    pkg = rm.Package.load(PKG)
    resolved = rm.resolve(pkg)
    rm.write_json(d / "request.json", rm.observation_request(resolved, pkg))
    rm.write_json(d / "binding.json", {"executable_sha256": pkg.manifest["target"]["executable_sha256"],
                                       "metadata_sha256": pkg.digest(), "recipe_sha256": pkg.recipe_digest()})
    t = pkg.manifest["target"]
    rm.run_headless(d / "proj", "fx", import_path=EXE, analysis=True, log=d / "import.log",
                    import_args=["-processor", t["language_id"], "-cspec", t["compiler_spec_id"]],
                    post=[("export_metadata.java", ["baseline", d / "request.json", d / "baseline.json",
                                                    d / "binding.json"])])
    return d, rm.read_json(d / "baseline.json")


@pytest.fixture
def project(baseline_project, tmp_path):
    d, _ = baseline_project
    shutil.copytree(d / "proj", tmp_path / "proj")
    return tmp_path / "proj" / "fx.gpr"


def _observe(project, tmp_path, tag, pkg_path=PKG):
    pkg = rm.Package.load(pkg_path)
    return rm.observe(project, PROGRAM, rm.observation_request(rm.resolve(pkg), pkg), tmp_path / f"{tag}.json",
                      log=tmp_path / f"{tag}.log")


def _edit(project, tmp_path, edits, tag="edit"):
    rm.write_json(tmp_path / f"{tag}.json", edits)
    _headless(project, tmp_path / f"{tag}.log", script_paths=[FIX / "ghidra"],
              post=[("fixture_edit.java", [tmp_path / f"{tag}.json"])])


def _plan_apply(pkg_path, project, tmp_path, tag, **kw):
    plan = rm.cmd_plan(pkg_path, project, PROGRAM, tmp_path / f"{tag}.plan.json", work=tmp_path / tag)
    receipt = rm.cmd_apply(pkg_path, project, PROGRAM, tmp_path / f"{tag}.plan.json", tmp_path / f"{tag}.receipt.json", **kw)
    return plan, receipt


def _raw_apply(project, tmp_path, plan, tag, evidence_root=FIX / "evidence"):
    rm.write_json(tmp_path / f"{tag}.plan.json", plan)
    rm.apply_plan(project, PROGRAM, tmp_path / f"{tag}.plan.json", tmp_path / f"{tag}.result.json",
                  evidence_root, log=tmp_path / f"{tag}.log")
    return rm.read_json(tmp_path / f"{tag}.result.json")


def _resign(plan):
    for op in plan["operations"]:
        op["operation_id"] = rm.digest({k: op[k] for k in ("kind", "target", "expected", "desired", "provenance")})
    plan["plan_sha256"] = rm.digest({k: v for k, v in plan.items() if k != "plan_sha256"})
    return plan


@ghidra
def test_a15_a05_a01_fresh_rebuilds_round_trip_and_agree(tmp_path):
    receipts, finals = [], []
    for n in (1, 2):
        receipt = rm.cmd_rebuild(PKG, EXE, tmp_path / f"r{n}" / "fx.gpr", PROGRAM, tmp_path / f"r{n}.receipt.json")
        steps = {s["step"]: s for s in receipt["steps"]}
        assert receipt["status"] == "ok", {k: v for k, v in steps.items() if v["status"] != "passed"}
        assert all(s["status"] == "passed" for s in receipt["steps"])
        assert steps["plan_apply"]["result"]["changed"] == 28
        second = steps["second_apply"]["result"]
        assert second["status"] == "noop" and second["changed"] == 0
        assert second["before_sha256"] == second["after_sha256"] == steps["plan_apply"]["result"]["after_sha256"]
        assert receipt["inputs"] and receipt["tools"] and receipt["environment"]["ghidra_version"] == "12.1.2"
        assert receipt["metadata_sha256"] == rm.Package.load(PKG).digest()
        assert [e["record"] for e in receipt["exclusions"]] == ["functions/0x00001090.json",
                                                                "functions/0x000010c0.json",
                                                                "functions/0x000010d0.json"]
        receipts.append(receipt)
        finals.append(rm.read_json(tmp_path / f"r{n}.receipt.work" / "observation.json"))
    # A15: two fresh projects from the same executable and recipe reach the same curated state.
    assert scoped(finals[0]) == scoped(finals[1])
    s = [{s["step"]: s for s in r["steps"]} for r in receipts]
    assert s[0]["compare"]["compared_sha256"] == s[1]["compare"]["compared_sha256"]
    assert s[0]["refdb_export_queries"]["problems"] == []
    # A05: no duplicate types (suffixes), symbols or segments after the second apply.
    assert not [p for p in finals[0]["managed_type_paths"] if "conflict" in p]
    assert finals[0]["comments"]["0x000011c7:plate"].count("[re-metadata:summary]") == 1
    # A01: the same project state exported twice gives identical canonical text.
    gpr = tmp_path / "r1" / "fx.gpr"
    a, b = _observe(gpr, tmp_path, "again1"), _observe(gpr, tmp_path, "again2")
    assert (tmp_path / "again1.json").read_bytes() == (tmp_path / "again2.json").read_bytes()
    assert scoped(a) == scoped(b) == scoped(finals[0])


@ghidra
def test_baseline_cannot_be_taken_on_a_saved_program(project, tmp_path):
    with pytest.raises(rm.MetadataError):
        _headless(project, tmp_path / "b.log", post=[("export_metadata.java", [
            "baseline", tmp_path / "missing-request.json", tmp_path / "out.json", tmp_path / "binding.json"])])
    rm.write_json(tmp_path / "req.json", {"functions": [], "types": [], "comments": []})
    rm.write_json(tmp_path / "bind.json", {"executable_sha256": rm.file_sha256(EXE)})
    with pytest.raises(rm.MetadataError):
        _headless(project, tmp_path / "b2.log", post=[("export_metadata.java", [
            "baseline", tmp_path / "req.json", tmp_path / "out.json", tmp_path / "bind.json"])])
    assert "baseline refused: the program was saved before" in (tmp_path / "b2.log").read_text()


@ghidra
def test_a02_a17_java_refuses_wrong_target_and_malformed_plans(project, tmp_path):
    before = scoped(_observe(project, tmp_path, "before"))
    plan = rm.cmd_plan(PKG, project, PROGRAM, tmp_path / "good.json", work=tmp_path / "w")
    assert plan["status"] == "ready"
    wrong = _resign(copy.deepcopy(plan))
    wrong["target"]["executable_sha256"] = "1" * 64
    result = _raw_apply(project, tmp_path, _resign(wrong), "wrong")
    assert result["status"] == "refused" and "wrong target" in result["error"]
    unsigned = copy.deepcopy(plan)
    unsigned["operations"][0]["desired"]["projection"]["size"] = 99
    result = _raw_apply(project, tmp_path, unsigned, "unsigned")
    assert result["status"] == "refused" and "digest" in result["error"]
    (tmp_path / "junk.plan.json").write_text("[1, 2]")
    rm.apply_plan(project, PROGRAM, tmp_path / "junk.plan.json", tmp_path / "junk.result.json", FIX / "evidence",
                  log=tmp_path / "junk.log")
    assert rm.read_json(tmp_path / "junk.result.json")["status"] == "refused"
    blocked = _resign(dict(copy.deepcopy(plan), status="blocked"))
    assert _raw_apply(project, tmp_path, blocked, "blocked")["status"] == "refused"
    assert scoped(_observe(project, tmp_path, "after")) == before


@ghidra
def test_a17_forged_ilt_plan_is_refused_by_the_java_path(project, tmp_path):
    before = _observe(project, tmp_path, "before")
    pkg = rm.Package.load(PKG)
    row = next(r for r in rm.evidence_rows(FIX / "evidence", "reverse/functions.csv") if r["name"] == "fx_mid")
    plan = rm.build_plan(pkg, rm.resolve(pkg), before)
    current = before["functions"]["0x000011e1"]
    forged = rm._op("set_function_name",
                    {"executable_sha256": pkg.manifest["target"]["executable_sha256"], "address_space": "ram",
                     "entry_rva": "0x000011e1"},
                    {"name": current["name"], "source": current["name_source"]},
                    {"name": {"name": "fx_mid", "namespace": []}, "raw": "fx_mid"},
                    {"origin": "target", "status": "supported", "review": "accepted", "identity_tier": "ilt",
                     "evidence_refs": [rm.evidence_ref("ilt", row)]})
    plan["operations"] = [forged]
    plan["noops"], plan["status"] = [], "ready"
    result = _raw_apply(project, tmp_path, _resign(plan), "forged")
    assert result["status"] == "refused" and "does not admit tier ilt" in result["error"]
    # The same claim with a digest that no longer matches the row.
    forged["provenance"]["evidence_refs"][0]["sha256"] = "0" * 64
    result = _raw_apply(project, tmp_path, _resign(plan), "forged2")
    assert result["status"] == "refused" and "changed since planning" in result["error"]
    assert scoped(_observe(project, tmp_path, "after")) == scoped(before)


@ghidra
def test_a04_name_changed_after_planning_is_a_stale_plan(project, tmp_path):
    rm.cmd_plan(PKG, project, PROGRAM, tmp_path / "p.json", work=tmp_path / "w")
    _edit(project, tmp_path, [{"op": "rename", "rva": "0x00001000", "name": "AnalystName"}])
    before = _observe(project, tmp_path, "before")
    with pytest.raises(rm.MetadataError) as err:
        rm.cmd_apply(PKG, project, PROGRAM, tmp_path / "p.json", tmp_path / "r.json")
    receipt = rm.read_json(tmp_path / "r.json")
    assert err.value.category == "blocked" and "stale plan" in receipt["result"]["error"]
    assert receipt["result"]["status"] == "refused"
    after = _observe(project, tmp_path, "after")
    assert scoped(after) == scoped(before)
    assert after["functions"]["0x00001000"]["name"]["name"] == "AnalystName"
    # A new plan sees the analyst's name and refuses to overwrite it on reloc evidence.
    plan = rm.cmd_plan(PKG, project, PROGRAM, tmp_path / "p2.json", work=tmp_path / "w2")
    assert plan["status"] == "blocked"
    assert any(c["field"] == "name" and "only ilt may" in c["reason"] for c in plan["conflicts"])


@ghidra
def test_a06_injected_failure_rolls_back_the_whole_batch(project, tmp_path):
    before = _observe(project, tmp_path, "before")
    with pytest.raises(rm.MetadataError) as err:
        _plan_apply(PKG, project, tmp_path, "a", fail_after=8)
    receipt = rm.read_json(tmp_path / "a.receipt.json")
    assert err.value.category == "execution"
    assert receipt["result"]["status"] == "rolled_back" and receipt["result"]["applied_before_failure"] == 8
    after = _observe(project, tmp_path, "after")          # a fresh process: the persisted state
    assert scoped(after) == scoped(before) and after["state"] is None
    assert after["managed_type_paths"] == []


@ghidra
def test_a12_wrong_expected_storage_rolls_back(project, tmp_path):
    def edit(pkg):
        pkg.records["functions/0x00001070.json"]["signature"]["return"]["storage"] = [{"reg": "EAX", "size": 4}]
    path = variant(tmp_path, edit)
    before = _observe(project, tmp_path, "before", path)
    with pytest.raises(rm.MetadataError):
        _plan_apply(path, project, tmp_path, "s")
    result = rm.read_json(tmp_path / "s.receipt.json")["result"]
    assert result["status"] == "rolled_back" and "verification failed for set_function_signature" in result["error"]
    assert '"reg":"ST0"' in result["error"]
    assert scoped(_observe(project, tmp_path, "after", path)) == scoped(before)


@ghidra
def test_a13_unsupported_plan_mutates_nothing(project, tmp_path):
    path = variant(tmp_path, lambda p: p.manifest.update(exclusions=[]))
    before = _observe(project, tmp_path, "before", path)
    plan = rm.cmd_plan(path, project, PROGRAM, tmp_path / "p.json", work=tmp_path / "w")
    assert plan["status"] == "unsupported" and len(plan["unsupported"]) == 3
    with pytest.raises(rm.MetadataError) as err:
        rm.cmd_apply(path, project, PROGRAM, tmp_path / "p.json", tmp_path / "r.json")
    assert err.value.category == "unsupported"
    assert scoped(_observe(project, tmp_path, "after", path)) == scoped(before)


@ghidra
def test_a14_collisions_and_overlaps_block_the_plan(project, tmp_path):
    _edit(project, tmp_path, [{"op": "label", "rva": "0x00003004", "name": "fx_box"},
                              {"op": "struct", "path": "/ReMetadata/fx_point"},
                              {"op": "struct", "path": "/ReMetadata/fx_kind.conflict"}])

    def edit(pkg):
        pkg.records["functions/0x000011e1.json"]["body"]["ranges"] = [["0x000011e1", "0x000011ef"]]
    path = variant(tmp_path, edit)
    before = _observe(project, tmp_path, "before", path)
    plan = rm.cmd_plan(path, project, PROGRAM, tmp_path / "p.json", work=tmp_path / "w")
    reasons = {(c["record"], c["field"]): c["reason"] for c in plan["conflicts"]}
    assert plan["status"] == "blocked"
    assert "namespace collision" in reasons[("functions/0x00001030.json", "name")]
    assert "unmanaged layout" in reasons[(rm.type_record_name("fx_point"), "type")]
    assert "suffixed duplicate" in reasons[(rm.type_record_name("fx_kind"), "type")]
    assert "overlaps function(s) ['0x000011c7']" in reasons[("functions/0x000011e1.json", "body")]
    with pytest.raises(rm.MetadataError):
        rm.cmd_apply(path, project, PROGRAM, tmp_path / "p.json", tmp_path / "r.json")
    assert scoped(_observe(project, tmp_path, "after", path)) == scoped(before)


@ghidra
def test_a07_managed_segments_beside_analyst_text(project, tmp_path):
    _plan_apply(PKG, project, tmp_path, "first")
    block = "[re-metadata:summary]\nFragmented fixture body: the hot part is here, the cold part follows fx_mid.\n" \
            "[/re-metadata:summary]"
    _edit(project, tmp_path, [{"op": "comment", "rva": "0x000011c7", "kind": "plate",
                               "text": "Analyst: first line\n" + block + "\nAnalyst: tail é"}])
    changed = variant(tmp_path, lambda p: p.records["comments/0x000011c7-plate-summary.json"].update(
        text="Updated summary."), "changed")
    plan, receipt = _plan_apply(changed, project, tmp_path, "update")
    assert [op["kind"] for op in plan["operations"]] == ["set_comment_segment"]
    assert receipt["counts"]["changed"] == 1
    obs = _observe(project, tmp_path, "o1", changed)
    assert obs["comments"]["0x000011c7:plate"] == ("Analyst: first line\n[re-metadata:summary]\nUpdated summary.\n"
                                                   "[/re-metadata:summary]\nAnalyst: tail é")
    tomb = variant(tmp_path, lambda p: p.records["comments/0x000011c7-plate-summary.json"].update(
        deleted=True, text=None), "tomb")
    _plan_apply(tomb, project, tmp_path, "delete")
    obs = _observe(project, tmp_path, "o2", tomb)
    assert obs["comments"]["0x000011c7:plate"] == "Analyst: first line\nAnalyst: tail é"
    again = rm.cmd_plan(tomb, project, PROGRAM, tmp_path / "again.json", work=tmp_path / "w3")
    assert again["status"] == "noop" and again["operations"] == []          # deletion is idempotent
    # An edit inside the managed segment is never overwritten.
    _edit(project, tmp_path, [{"op": "comment", "rva": "0x000011e5", "kind": "eol",
                               "text": "[re-metadata:role]\nanalyst rewrote this\n[/re-metadata:role]"}], "e2")
    plan = rm.cmd_plan(tomb, project, PROGRAM, tmp_path / "p4.json", work=tmp_path / "w4")
    assert plan["status"] == "blocked" and "edited outside the tool" in plan["conflicts"][0]["reason"]


@ghidra
def test_java_and_python_agree_on_shared_rules(project, tmp_path):
    names = ["FUN_00401000", "?rva00486F35@Rva00486F35@@QAEHXZ", "BfmeThing", "sub_4010A0", "fx_add",
             "?validateAudio@ThingTemplate@@IAEXXZ", "??0Coord3D@@QAE@XZ", "??1Coord3D@@QAE@XZ",
             "??8Coord3D@@QAE_NABU0@@Z", "?count@fx_box@@QAEIH@Z", "?fx_scale@@YGFPAUfx_point@@H@Z",
             "?f@B@A@@YAXXZ", "CafeBabe", "Badge", "x_ABCDEF"]
    canon = [{"b": 1, "a": [None, True, "é\n\u0001\"\\/"]}, " ", 123456789012345678]
    segments = [{"text": "a\n[re-metadata:s]\nx\n[/re-metadata:s]\nb", "id": "s", "value": None},
                {"text": "a", "id": "s", "value": "v"}, {"text": None, "id": "s", "value": None},
                {"text": "[re-metadata:s]\nx\n[/re-metadata:s]", "id": "s", "value": None},
                {"text": "[re-metadata:s]\n\n[/re-metadata:s]", "id": "s", "value": "y"},
                {"text": "[re-metadata:s]\nbroken", "id": "s", "value": "y"}]
    texts = ['a,b\r\n"x, ""y""",z\n\n1,\n', "h\nlast"]
    rm.write_json(tmp_path / "v.json", {"names": names, "canonical": canon, "segments": segments, "csv": texts})
    _headless(project, tmp_path / "self.log", read_only=True,
              post=[("apply_metadata.java", ["selftest", tmp_path / "v.json", tmp_path / "o.json"])])
    out = rm.read_json(tmp_path / "o.json")
    for n in names:
        assert out["names"][n] == {"placeholder": refdb.placeholder(n), "qualified": rm.qualified_parts(n)}, n
    assert out["canonical"] == [f"{rm.canonical(v).decode()} {rm.digest(v)}" for v in canon]
    for got, v in zip(out["segments"], segments):
        try:
            want = {"segment": rm.segment_text(v["text"], v["id"]), "result": rm.with_segment(v["text"], v["id"], v["value"])}
        except rm.MetadataError:
            want = {"error": "malformed"}
        assert got == want, v
    for got, text in zip(out["csv"], texts):
        assert got == [r for r in csv.reader(text.splitlines(keepends=True)) if r]


def test_body_and_signature_evidence_is_verified(tmp_path):
    ev = tmp_path / "ev"
    shutil.copytree(FIX / "evidence", ev)
    led = next(r for r in rm.evidence_rows(ev, "reverse/functions.csv") if r["name"] == "?count@fx_box@@QAEIH@Z")

    def edit(pkg):
        pkg.manifest["evidence_root"] = str(ev)
        fn = pkg.records["functions/0x00001030.json"]
        fn["body"]["provenance"]["evidence_refs"] = [rm.evidence_ref("ilt", led)]     # ledger extent 17 bytes
        fn["body"]["ranges"] = [["0x00001030", "0x00001040"]]                          # 16: disagrees
        pkg.records["functions/0x00001000.json"]["signature"]["provenance"]["evidence_refs"] = []
        pkg.records["functions/0x00001050.json"]["body"]["provenance"]["evidence_refs"][0]["sha256"] = "0" * 64
    resolved = rm.resolve(rm.Package.load(variant(tmp_path, edit)))
    reasons = {(c["record"], c["field"]): c["reason"] for c in resolved["conflicts"]}
    assert "does not support this body" in reasons[("functions/0x00001030.json", "body")]
    assert "needs evidence_refs" in reasons[("functions/0x00001000.json", "signature")]
    assert "evidence changed: tools/tests/fixtures/re_metadata/src/fixture.c" in reasons[("functions/0x00001050.json", "body")]
    ok = rm.resolve(rm.Package.load(PKG))
    assert ok["evidence"]["tools/tests/fixtures/re_metadata/src/fixture.c"] == rm.file_sha256(FIX / "src" / "fixture.c")


def test_cli_exit_codes_follow_the_status(tmp_path):
    def run(*args):
        proc = subprocess.run([sys.executable, str(ROOT / "tools" / "ghidra_refdb.py"), *map(str, args)],
                              capture_output=True, text=True)
        return proc.returncode, json.loads(proc.stdout)
    code, out = run("metadata-validate", "--metadata", PKG, "--executable", EXE)
    assert (code, out["status"]) == (0, "ok")
    code, out = run("metadata-validate", "--metadata", variant(tmp_path, lambda p: p.manifest.update(exclusions=[])))
    assert (code, out["status"]) == (rm.EXIT["unsupported"], "unsupported")
    bad = variant(tmp_path, name="bad")
    (bad / "functions" / "0x00001000.json").write_text("{}")
    code, out = run("metadata-validate", "--metadata", bad)
    assert (code, out["status"]) == (rm.EXIT["invalid"], "invalid")


@ghidra
def test_metadata_export_writes_proposals_and_reports_coverage(project, tmp_path):
    scope = {"target": {"executable_sha256": rm.file_sha256(EXE)},
             "functions": ["0x00001000", "0x000010d0", "0x000011c7"], "types": [],
             "comments": [{"address_rva": "0x000011c7", "kind": "plate"}]}
    rm.write_json(tmp_path / "scope.json", scope)
    report = rm.cmd_export(project, PROGRAM, None, tmp_path / "scope.json", tmp_path / "out")
    # fx_wide's analysed signature returns in EDX:EAX: reported, not silently dropped.
    assert report["status"] == "partial"
    assert [u["artifact"] for u in report["unsupported"]] == ["function 0x000010d0 signature"]
    assert "split or register-pair storage" in report["unsupported"][0]["reason"]
    assert sorted(report["written"]) == ["comments/0x000011c7-plate.json", "functions/0x00001000.json",
                                         "functions/0x000010d0.json", "functions/0x000011c7.json"]
    frag = rm.read_json(tmp_path / "out" / "functions" / "0x000011c7.json")
    assert frag["body"]["ranges"] == [["0x000011c7", "0x000011d7"], ["0x000011e9", "0x000011ef"]]
    assert frag["observed_name"]["provenance"] == {"origin": "analysis", "status": "observation",
                                                   "review": "proposed", "observed_source": "IMPORTED"}
    assert frag["observed_name"]["ghidra_name"] == "fx_frag"
    again = rm.cmd_export(project, PROGRAM, None, tmp_path / "scope.json", tmp_path / "out2")
    assert again["observation_sha256"] == report["observation_sha256"]
    for name in report["written"]:
        assert (tmp_path / "out" / name).read_bytes() == (tmp_path / "out2" / name).read_bytes()
    scope["target"]["executable_sha256"] = "2" * 64
    rm.write_json(tmp_path / "scope2.json", scope)
    with pytest.raises(rm.MetadataError):
        rm.cmd_export(project, PROGRAM, None, tmp_path / "scope2.json", tmp_path / "out3")


@ghidra
def test_bound_name_sync_replaces_the_unbound_importer(project, tmp_path, monkeypatch):
    monkeypatch.setenv("TMPDIR", str(tmp_path))
    meta = refdb.export(project, PROGRAM, tmp_path / "fx.sqlite")
    assert meta["schema_version"] == "2" and meta["compiler_spec"] == "clangwindows"
    reverse = FIX / "evidence" / "reverse"
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "ghidra_refdb.py"), "sync-plan",
                           str(tmp_path / "fx.sqlite"), "--reverse", str(reverse), "--project", str(project),
                           "--program", PROGRAM, "--out", str(tmp_path / "sync.json")],
                          capture_output=True, text=True, env=dict(__import__("os").environ, TMPDIR=str(tmp_path)))
    out = json.loads(proc.stdout)
    assert proc.returncode == 0 and out["status"] == "ready", out
    plan = rm.read_json(tmp_path / "sync.json")
    renamed = {op["target"]["entry_rva"]: op["desired"]["name"] for op in plan["operations"]}
    assert renamed["0x00001030"] == {"name": "count", "namespace": ["fx_box"]}
    assert "0x000011c7" not in renamed                       # Ghidra already holds the exported name
    assert all(op["kind"] == "set_function_name" for op in plan["operations"])
    proc = subprocess.run([sys.executable, str(ROOT / "tools" / "ghidra_refdb.py"), "sync-apply", "--project",
                           str(project), "--program", PROGRAM, "--plan", str(tmp_path / "sync.json")],
                          capture_output=True, text=True)
    assert proc.returncode == 0, proc.stdout + proc.stderr
    obs = _observe(project, tmp_path, "after")
    assert obs["functions"]["0x00001030"]["name"] == {"name": "count", "namespace": ["fx_box"]}
    assert obs["functions"]["0x00001000"]["name_source"] == "IMPORTED"
