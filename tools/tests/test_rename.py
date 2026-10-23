"""tools/rename.py on a miniature tree: a temporary git repository holding
small ledgers and sources, so every rule is exercised without the real ledger
or a compiler (verification is injected)."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402


@pytest.fixture(autouse=True)
def _evidence_gates_stubbed(monkeypatch):
    """The agreement-record and canonical-evidence gates have their own tests
    (test_rename_fixes.py); these exercise everything else."""
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)

OLD = "?Rva00401000@Widget@@QAEHH@Z"
NEW = "?countParts@Widget@@QAEHH@Z"
EH = "__ehhandler$" + OLD

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,40,Code/Game/Widget.cpp,matched,address-derived
{EH},,0x00790000,10,Code/Game/Widget.cpp,matched,gen-ehstub
$L100,,0x00790010,8,Code/Game/Widget.cpp,matched,gen-funclet;parent={OLD}
?caller@Gadget@@QAEXXZ,,0x00402000,20,Code/Game/Gadget.cpp,matched,calls {OLD}
?count@Widget@@QAEHXZ,,0x00403000,6,Code/Game/Widget.cpp,matched,real name
?Rva00404000@@YAXXZ,,0x00404000,6,Code/Game/Free.cpp,matched,vendored=zlib-1.1.4
?Rva00405000@@YAXXZ,,0x00405000,6,Code/gen_asm/gen_0001.asm,matched,gen-dump
?Rva00406000@@YAXXZ,,0x00406000,6,Code/Game/Lit.cpp,matched,address-derived
?Rva00407000@@YAXXZ,,0x00407000,6,Code/Game/Free.cpp,matched,exported
"""
SYMBOLS = f"""name,address,notes
{OLD},0x00401000,pin
?Rva00401000Alias@@YAXXZ,0x00401000,other name on the same address
?unrelated@@YAXXZ,0x00500000,fold-proof={OLD}
"""
DELETED = 'name,target_rva,reason\n?gone@@YAXXZ,0x00100000,"old, retired"\n'
WIDGET = """// cl: /O2
// ?Rva00401000@Widget@@QAEHH@Z @ 0x00401000
class Widget {
public:
    int Rva00401000(int n);
    int count();
};
// ?Widget::Rva00401000 present-unmatched
int Widget::Rva00401000(int n) { return n + 1; }
int Widget::count() { return 0; }
"""
GADGET = """class Widget { public: int Rva00401000(int n); };
#pragma comment(linker, "/alternatename:?Rva00401000@Widget@@QAEHH@Z=?other@@YAXXZ")
struct Gadget { void caller(); Widget *w; };
void Gadget::caller() { w->Rva00401000(3); }\r
"""
LIT = 'void Rva00406000() { const char *s = "Rva00406000"; }\n'
FREE = "void Rva00404000() {}\nvoid Rva00407000() {}\n"


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True)


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": SYMBOLS,
        "reverse/deleted_rows.csv": DELETED,
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n1,0x1,0x00407000,.text,code,"
                               "?Rva00407000@@YAXXZ\n",
        "reverse/gate_baseline.txt": "",
        "Code/Game/Widget.cpp": WIDGET,
        "Code/Game/Gadget.cpp": GADGET,
        "Code/Game/Lit.cpp": LIT,
        "Code/Game/Free.cpp": FREE,
        "Code/gen_asm/gen_0001.asm": "Rva00405000 PROC\n",
        "docs/guide.md": f"see {OLD}\n",
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


def plan(root, **overrides):
    args = dict(rva=0x00401000, new="countParts", basis="inferred", evidence="agree:abc123")
    args.update(overrides)
    return rename.plan_rename("function", ctx=ctx_of(root), **args)


# ------------------------------------------------------------ mangled rewrite

def test_rewrites_only_the_identifier():
    assert rename.rename_function_symbol(OLD, "countParts") == NEW
    assert rename.rename_function_symbol("_Rva00401000", "readToken") == "_readToken"
    assert rename.rename_function_symbol("_Rva00401000@8", "readToken") == "_readToken@8"
    assert rename.rename_function_symbol("?Rva1@@YAXPAVFoo@@@Z", "bar") == "?bar@@YAXPAVFoo@@@Z"


@pytest.mark.parametrize("mangled,new", [
    ("?Rva00401000@@YAXPAV0@@Z", "bar"),        # back-reference to the identifier
    ("?Rva00401000@Foo@@QAEXPAVBar@@@Z", "Bar"),  # new name would become a back-reference
    ("??0Widget@@QAE@XZ", "bar"),               # a constructor's identifier is its class
    ("??$make@H@@YAHXZ", "bar"),                # template function
    ("__ehhandler$?f@@YAXXZ", "bar"),           # a funclet follows its parent
])
def test_refuses_unsafe_mangled_rewrites(mangled, new):
    with pytest.raises(Refusal):
        rename.rename_function_symbol(mangled, new)


def test_shared_placeholder_definition():
    assert rename.is_placeholder("Rva00401000")
    assert rename.is_placeholder(OLD)
    assert rename.is_placeholder("bfmeThing")
    assert rename.is_placeholder("tmp", "local")
    assert not rename.is_placeholder("countParts")
    assert not rename.is_placeholder("?count@Widget@@QAEHXZ")


@pytest.mark.parametrize("basis", ["", "guess", "canonical:", "canonical:hunch"])
def test_basis_vocabulary(basis):
    with pytest.raises(Refusal):
        rename.basis_kind(basis)


def test_basis_kinds():
    assert rename.basis_kind("inferred") == "inferred"
    assert rename.basis_kind("canonical:wb") == "canonical"


# ------------------------------------------------------------ plan and apply

def test_full_rename(tree):
    p = plan(tree)
    assert p.new == NEW
    assert p.verify == ["Code/Game/Gadget.cpp", "Code/Game/Widget.cpp"]
    assert sorted(c for c in p.claims if isinstance(c, int)) == [0x00401000, 0x00402000, 0x00790000, 0x00790010]
    assert "file:Code/Game/Widget.cpp" in p.claims
    assert any("?Rva00401000Alias@@YAXXZ" in w for w in p.warnings)
    assert "docs/guide.md" in p.mentions
    seen = []
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: seen.append(sources) or True)
    assert seen == [["Code/Game/Gadget.cpp", "Code/Game/Widget.cpp"]]

    widget = (tree / "Code/Game/Widget.cpp").read_text()
    assert "int countParts(int n);" in widget
    assert "int Widget::countParts(int n)" in widget
    assert f"// {NEW} @ 0x00401000" in widget
    assert "// ?Widget::countParts present-unmatched" in widget
    assert "Rva00401000" not in widget
    gadget = (tree / "Code/Game/Gadget.cpp").read_bytes()
    assert gadget.endswith(b"w->countParts(3); }\r\n")    # line endings kept
    assert f'"/alternatename:{NEW}=?other@@YAXXZ"'.encode() in gadget

    functions = (tree / "reverse/functions.csv").read_text()
    assert f"{NEW},,0x00401000,40," in functions
    assert f"__ehhandler${NEW},,0x00790000," in functions
    assert f"parent={NEW}" in functions and f"calls {NEW}" in functions
    assert OLD not in functions
    symbols = (tree / "reverse/symbols.csv").read_text()
    assert f"{NEW},0x00401000,pin" in symbols and f"fold-proof={NEW}" in symbols
    assert "?Rva00401000Alias@@YAXXZ,0x00401000" in symbols

    deleted = (tree / "reverse/deleted_rows.csv").read_text()
    assert deleted.startswith(DELETED)
    assert (f'{OLD},0x00401000,"Renamed to {NEW} by tools/rename.py (inferred)"\n') in deleted
    assert (f'{EH},0x00790000,"Renamed to __ehhandler${NEW} by tools/rename.py (inferred)"\n') in deleted
    basis = (tree / "reverse/name_basis.csv").read_text().splitlines()
    assert basis == ["kind,old,new,basis,evidence,source,rva",
                     f"function,{OLD},{NEW},inferred,agree:abc123,Code/Game/Widget.cpp,0x00401000"]
    assert p.subject() == "Rename Rva00401000 to countParts (inferred)"


def test_unrelated_bytes_untouched(tree):
    before = snapshot(tree)
    p = plan(tree)
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    after = snapshot(tree)
    changed = {rel for rel in after if before.get(rel) != after[rel]}
    assert changed == {"Code/Game/Widget.cpp", "Code/Game/Gadget.cpp", "reverse/functions.csv",
                       "reverse/symbols.csv", "reverse/deleted_rows.csv", "reverse/name_basis.csv"}
    old_lines = before["reverse/functions.csv"].splitlines()
    new_lines = after["reverse/functions.csv"].splitlines()
    assert sum(a != b for a, b in zip(old_lines, new_lines)) == 4


def test_rollback_on_failed_verification(tree):
    before = snapshot(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: False)
    assert snapshot(tree) == before
    assert not (tree / "reverse/name_basis.csv").exists()


def test_rollback_on_exception(tree):
    before = snapshot(tree)

    def boom(ctx, sources):
        raise KeyboardInterrupt

    with pytest.raises(KeyboardInterrupt):
        rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=boom)
    assert snapshot(tree) == before


def test_refuses_a_tree_that_moved_since_planning(tree):
    p = plan(tree)
    (tree / "Code/Game/Widget.cpp").write_text(WIDGET + "// edit\n")
    with pytest.raises(Refusal, match="changed since"):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)


def test_canonical_may_replace_an_inferred_name(tree):
    rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    p = plan(tree, new="partCount", basis="canonical:wb", evidence="wb assert Widget::partCount")
    assert p.new == "?partCount@Widget@@QAEHH@Z"
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    # ... and nothing replaces a canonical one
    with pytest.raises(Refusal, match="recorded canonical"):
        plan(tree, new="partTotal", basis="canonical:zh", evidence="zh")
    assert (tree / "reverse/name_basis.csv").read_text().count("\n") == 3


def test_inferred_may_not_replace_an_inferred_name(tree):
    rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    with pytest.raises(Refusal, match="real name"):
        plan(tree, new="partCount")


def test_canonical_may_replace_a_placeholder(tree):
    p = plan(tree, basis="canonical:string", evidence="retail string 'Widget::countParts'")
    assert p.basis == "canonical:string" and not any("inferred" in w for w in p.warnings)


class FakeResult(tuple):
    def __new__(cls, claimed, refused, tokens=None, unconfirmed=()):
        self = tuple.__new__(cls, (list(claimed), list(refused)))
        self.tokens, self.unconfirmed = dict(tokens or {}), list(unconfirmed)
        return self


class FakeClaims:
    """tools/claims.py's surface rename.py uses: owner/_names/active/claim/release/key_of."""
    class ClaimsUnavailable(RuntimeError):
        def __init__(self, message, claimed=(), refused=()):
            super().__init__(message)
            self.claimed, self.refused = list(claimed), list(refused)

    def __init__(self, result=None, error=None, active=None):
        self.result, self.error, self.released, self._active = result, error, [], active or {}

    @staticmethod
    def key_of(key):
        return key if isinstance(key, int) or "/" in key else "file/" + key.split(":", 1)[1]

    def owner(self, root=None):
        return "me"

    def _names(self, who, root=None):
        return [who]

    def active(self, root=None):
        return self._active

    def claim(self, keys, note="", root=None):
        if self.error:
            raise self.error
        return self.result

    def release(self, keys, root=None, tokens=None):
        self.released.append((list(keys), dict(tokens or {})))


def test_claims_refused_by_another_worker(monkeypatch):
    fake = FakeClaims(result=FakeResult([0x401000], [0x790000], tokens={0x401000: "t1"}))
    monkeypatch.setitem(sys.modules, "claims", fake)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    with pytest.raises(Refusal, match="another worker"):
        rename.take_claims([0x401000, 0x790000], True)
    assert fake.released == [([0x401000], {0x401000: "t1"})]


def test_claims_taken_and_released_with_tokens(monkeypatch):
    fake = FakeClaims(result=FakeResult([0x401000, "file/abc"], [], tokens={0x401000: "t1", "file/abc": "t2"}))
    monkeypatch.setitem(sys.modules, "claims", fake)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    taken = rename.take_claims([0x401000, "file:Code/Game/Widget.cpp"], True)
    assert taken.new == [0x401000, "file/abc"]
    taken.release()
    assert fake.released == [([0x401000, "file/abc"], {0x401000: "t1", "file/abc": "t2"})]


def test_claims_already_held_are_never_released(monkeypatch):
    """Finding 12: claim() renews a claim the caller already holds and lists
    it as claimed; releasing it would drop the caller's own claim."""
    fake = FakeClaims(result=FakeResult([0x401000, 0x402000], [], tokens={0x401000: "a", 0x402000: "b"}),
                      active={0x401000: {"owner": "me"}, 0x403000: {"owner": "other"}})
    monkeypatch.setitem(sys.modules, "claims", fake)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    taken = rename.take_claims([0x401000, 0x402000], True)
    assert taken.new == [0x402000]
    taken.release()
    assert fake.released == [([0x402000], {0x402000: "b"})]


def test_unconfirmed_claims_are_reported_not_refused(monkeypatch, capsys):
    fake = FakeClaims(result=FakeResult([0x401000], [0x402000], unconfirmed=[0x402000]))
    monkeypatch.setitem(sys.modules, "claims", fake)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    taken = rename.take_claims([0x401000, 0x402000], True)
    assert taken.new == [0x401000] and taken.unconfirmed == [0x402000]
    assert "could not confirm" in capsys.readouterr().err


def test_claims_unavailable_works_unclaimed(monkeypatch):
    fake = FakeClaims()
    fake.error = FakeClaims.ClaimsUnavailable("offline")
    monkeypatch.setitem(sys.modules, "claims", fake)
    monkeypatch.delenv("BFME_CLAIMS", raising=False)
    taken = rename.take_claims([0x401000], True)
    assert taken.new == []
    taken.release()
    assert fake.released == []


def test_claim_keys_cover_every_written_file(tree):
    p = plan(tree)
    keys = rename.claim_keys(p)
    assert 0x00401000 in keys and "file:Code/Game/Gadget.cpp" in keys and "file:Code/Game/Widget.cpp" in keys
    assert not any(str(k).startswith("file:reverse/") for k in keys)


def test_full_mangled_new_must_change_only_the_identifier(tree):
    assert plan(tree, new=NEW).new == NEW
    with pytest.raises(Refusal, match="beyond the identifier"):
        plan(tree, new="?countParts@Widget@@QAEXH@Z")


@pytest.mark.parametrize("overrides,message", [
    (dict(rva=0x00409999), "no functions.csv row"),
    (dict(rva=0x00403000, new="partCount"), "real name"),
    (dict(rva=0x00403000, new="partCount", basis="canonical:zh", evidence="zh"), "real name"),
    (dict(rva=0x00404000, new="inflateAll"), "vendored"),
    (dict(rva=0x00407000, new="inflateAll"), "retail export"),
    (dict(rva=0x00405000, new="inflateAll"), "generated"),
    (dict(rva=0x00406000, new="formatName"), "string literal"),
    (dict(new="Rva00999999"), "placeholder"),
    (dict(new="count"), "already a name"),
    (dict(new="int"), "keyword"),
    (dict(new="2bad"), "not a C\\+\\+ identifier"),
    (dict(evidence=""), "evidence"),
    (dict(basis="canonical:guess"), "unknown canonical"),
    (dict(max_files=1), "max-files"),
])
def test_refusals(tree, overrides, message):
    before = snapshot(tree)
    with pytest.raises(Refusal, match=message):
        plan(tree, **overrides)
    assert snapshot(tree) == before


def test_refuses_collision_with_an_existing_symbol(tree):
    with (tree / "reverse/symbols.csv").open("a") as handle:
        handle.write(f"{NEW},0x00600000,taken\n")
    with pytest.raises(Refusal, match="already names a row or pin"):
        plan(tree)


def test_refuses_a_name_keyed_in_a_frozen_baseline(tree):
    (tree / "reverse/gate_baseline.txt").write_text(f"extent 0x00401000 {OLD}\n")
    with pytest.raises(Refusal, match="frozen"):
        plan(tree)


def test_refuses_an_identifier_another_symbol_shares(tree):
    with (tree / "reverse/symbols.csv").open("a") as handle:
        handle.write("?other@Rva00401000@@QAEXXZ,0x00600000,class spelled like the method\n")
    with pytest.raises(Refusal, match="also spells"):
        plan(tree)


def test_refuses_a_retail_module_class_name(tree):
    (tree / "reverse/module_factory_registrations.csv").write_text(
        "index,name,call_rva,instance_factory_rva,data_factory_rva,hook_rva,module_type,interface_mask\n"
        "0,Rva00406000,0x1,0x2,0x3,,0,1\n")
    with pytest.raises(Refusal, match="module class"):
        plan(tree, rva=0x00406000, new="formatName")


def test_dry_run_writes_nothing(tree, capsys):
    before = snapshot(tree)
    code = rename.main(["function", "--rva", "0x00401000", "--new", "countParts", "--basis", "inferred",
                        "--evidence", "agree:abc", "--dry-run", "--no-claim", "--root", str(tree)])
    assert code == 0
    out = capsys.readouterr().out
    assert "suggested subject: Rename Rva00401000 to countParts (inferred)" in out
    assert "nothing written" in out
    assert snapshot(tree) == before


def test_cli_reports_refusals(tree, capsys):
    code = rename.main(["function", "--rva", "0x00403000", "--new", "partCount", "--basis", "inferred",
                        "--evidence", "x", "--no-claim", "--root", str(tree)])
    assert code == 2
    assert "refused" in capsys.readouterr().err


def test_cli_apply_restores_on_build_failure(tree, capsys):
    (tree / "build.sh").write_text("#!/bin/sh\necho 'Functions: FAIL 1/2'\nexit 1\n")
    (tree / "build.sh").chmod(0o755)
    before = snapshot(tree)
    code = rename.main(["function", "--rva", "0x00401000", "--new", "countParts", "--basis", "inferred",
                        "--evidence", "agree:abc", "--no-claim", "--root", str(tree)])
    assert code == 1
    after = snapshot(tree)
    after.pop("reverse/.add_match.lock", None)
    assert after == before


def test_cli_apply_needs_functions_ok(tree):
    (tree / "build.sh").write_text("#!/bin/sh\necho 'Functions: OK 3/3 matched'\nexit 0\n")
    (tree / "build.sh").chmod(0o755)
    code = rename.main(["function", "--rva", "0x00401000", "--new", "countParts", "--basis", "inferred",
                        "--evidence", "agree:abc", "--no-claim", "--root", str(tree)])
    assert code == 0
    assert NEW in (tree / "reverse/functions.csv").read_text()


# ------------------------------------------------------------ the real tree

@pytest.mark.skipif(not (rename.ROOT / rename.FUNCTIONS).exists(), reason="no real ledger")
def test_real_tree_dry_run_smoke():
    """Plan (never apply) a function rename on live placeholder rows: the
    planner must either plan or refuse with a reason -- never crash."""
    import re
    ctx = rename.Context(rename.ROOT, object_scan=False)
    candidates = [r for r in ctx.rows() if re.fullmatch(r"\?Rva[0-9A-F]{8}@[A-Za-z]\w*@@Q.*", r["name"])
                  and not rename.is_generated(r["source"])][:15]
    planned = []
    for row in candidates:
        try:
            p = rename.plan_rename("function", ctx=ctx, rva=int(row["target_rva"], 16), new="smokeTestName",
                                   basis="inferred", evidence="smoke", old=row["name"])
        except Refusal:
            continue
        assert p.new.startswith("?smokeTestName@") and p.verify and p.renamed_rows
        assert p.after["reverse/name_basis.csv"].endswith(b"\n")
        planned.append(p)
        if len(planned) == 2:
            break
    assert planned, "no live placeholder method could be planned"


def test_refuses_a_name_the_data_ledger_embeds(tree):
    (tree / "reverse/data_ledger.csv").write_text(f"address,name\n0x00A00000,?$S1@?1?{OLD}@4IA\n")
    _git(tree, "add", "reverse/data_ledger.csv")
    with pytest.raises(Refusal, match="frozen"):
        plan(tree)


def test_refuses_a_local_static_ledger_name_embedding_the_function(tree):
    with (tree / "reverse/data_rows.csv").open("a") as handle:
        handle.write(f"?$S1@?1?{OLD}@4IA,0x00A00000,rva,4,.bss,Code/Game/Widget.cpp,matched,guard,m\n")
    with pytest.raises(Refusal, match="local static.*embeds"):
        plan(tree)


# ------------------------------------------------- alias pins (trial-1 finding)
# A caller unit's private view can mangle the same method differently (the
# real case: AerialPathfinder::rva0037609C pinned as ...PBE1_N@Z by its caller
# beside the row's ...PBE3_N@Z). Same address, same Class::method: the same
# identity, renamed with it rather than refused as "also spells".

ALIAS = "?Rva00401000@Widget@@QAEHI@Z"
ALIAS_NEW = "?countParts@Widget@@QAEHI@Z"


def test_alias_pin_at_the_address_is_renamed_with_the_function(tree):
    with (tree / "reverse/symbols.csv").open("a") as handle:
        handle.write(f"{ALIAS},0x00401000,callee of ?caller@Gadget@@QAEXXZ\n")
    p = plan(tree)
    assert (ALIAS, ALIAS_NEW, "0x00401000") in p.renamed_pins
    assert not any(ALIAS in w for w in p.warnings)
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    symbols = (tree / "reverse/symbols.csv").read_text()
    assert f"{ALIAS_NEW},0x00401000,callee of" in symbols and ALIAS not in symbols
    assert f"{NEW},0x00401000,pin" in symbols


def test_alias_pin_spelled_whole_in_a_comment_is_respelled(tree):
    with (tree / "reverse/symbols.csv").open("a") as handle:
        handle.write(f"{ALIAS},0x00401000,caller view\n")
    gadget = tree / "Code/Game/Gadget.cpp"
    gadget.write_bytes(gadget.read_bytes() + f"// binds {ALIAS}\n".encode())
    rename.apply_rename(plan(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: True)
    assert f"// binds {ALIAS_NEW}" in gadget.read_text()


def test_same_identifier_pin_at_another_address_still_refused(tree):
    with (tree / "reverse/symbols.csv").open("a") as handle:
        handle.write(f"{ALIAS},0x00600000,a different function\n")
    with pytest.raises(Refusal, match="also spells"):
        plan(tree)


def test_alias_pin_whose_new_spelling_collides_is_refused(tree):
    with (tree / "reverse/symbols.csv").open("a") as handle:
        handle.write(f"{ALIAS},0x00401000,caller view\n{ALIAS_NEW},0x00700000,taken\n")
    with pytest.raises(Refusal, match="already names"):
        plan(tree)
