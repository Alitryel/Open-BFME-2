"""tools/rename.py: a canonical function rename may take a word that another
scope the rewrite cannot reach already spells. Three real blocked leads set the
shapes -- a member (and a qualified call) of an unrelated class view
(0x00467AB8 onRemoving), an out-of-line method of a sibling class
(0x006F1600 objectMemberLookup) and a local of the renamed function itself
(0x000BEE25 adjustAnimation). Each is tested with the neighbours that stay
refused, and an inferred name keeps the old refusal (revert is whole-word).
A miniature tree (a temporary git repository), so no compiler is needed."""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal  # noqa: E402
from test_rename_collisions import tree_of  # noqa: E402

SRC = "Code/Game/Widget.cpp"
ROW = f"?rva00701000@Widget@@QAEXH@Z,,0x00701000,10,{SRC},matched,address-derived\n"


@pytest.fixture(autouse=True)
def _evidence_gates_stubbed(monkeypatch):
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)


def plan(tmp_path, cpp, new, *, basis="canonical:wb", extra=None):
    sources = {SRC: "// cl: /O2\n" + cpp}
    sources.update(extra or {})
    tree = tree_of(tmp_path, ROW, **sources)
    ctx = rename.Context(tree, object_scan=False)
    return rename.plan_rename("function", ctx=ctx, rva=0x00701000, new=new, basis=basis,
                              evidence="wb lead 0x00701000: x")


WIDGET = "class Widget { public: void rva00701000(int); };\n"


# ----------------------------------------------------------- the three real shapes

def test_member_and_qualified_call_of_an_unrelated_class(tmp_path):
    cpp = ("class Other { public: virtual void onRemoving(int); };\n" + WIDGET +
           "void Widget::rva00701000(int x) { ((Other *)this)->Other::onRemoving(x); }\n")
    text = plan(tmp_path, cpp, "onRemoving").after[SRC].decode()
    assert "void Widget::onRemoving(int x)" in text and "void rva00701000" not in text
    # the other class's own spellings are untouched
    assert "virtual void onRemoving(int);" in text and "->Other::onRemoving(x)" in text


def test_out_of_line_method_of_a_sibling_class(tmp_path):
    cpp = ("class Xml { public: virtual int lookup(int) const; static int sMethod(int); };\n"
           "class Widget { public: int rva00701000(int); };\n"
           "int Xml::lookup(int k) const { Widget *w = 0; return w->rva00701000(k); }\n")
    row = f"?rva00701000@Widget@@QAEHH@Z,,0x00701000,10,{SRC},matched,address-derived\n"
    tree = tree_of(tmp_path, row, **{SRC: "// cl: /O2\n" + cpp})
    ctx = rename.Context(tree, object_scan=False)
    result = rename.plan_rename("function", ctx=ctx, rva=0x00701000, new="lookup", basis="canonical:wb",
                                evidence="wb lead 0x00701000: x")
    text = result.after[SRC].decode()
    assert "w->lookup(k)" in text and "int Xml::lookup(int k) const" in text and "rva00701000" not in text


def test_local_of_the_function_being_renamed(tmp_path):
    cpp = (WIDGET + "struct Thing { void touch(); };\nextern Thing things[4];\n"
           "void Widget::rva00701000(int x) { int count = x; Thing &lookup = things[count]; lookup.touch(); }\n")
    text = plan(tmp_path, cpp, "lookup").after[SRC].decode()
    assert "void Widget::lookup(int x)" in text and "Thing &lookup = things[count]" in text


def test_parameter_of_another_function_and_a_prototype_parameter(tmp_path):
    cpp = (WIDGET + "void use(int lookup) { lookup += 1; }\nvoid declared(int lookup);\n"
           "void Widget::rva00701000(int x) { use(x); }\n")
    assert "void Widget::lookup(int x)" in plan(tmp_path, cpp, "lookup").after[SRC].decode()


@pytest.mark.parametrize("cpp,why", [
    ("class Other { public: virtual void onRemoving(int); };\n" + WIDGET +
     "void Widget::rva00701000(int x) { ((Other *)this)->Other::onRemoving(x); }\n", "member + qualified call"),
    ("struct Thing { void touch(); };\n" + WIDGET +
     "void Widget::rva00701000(int x) { Thing &onRemoving = *(Thing *)0; onRemoving.touch(); }\n", "local"),
])
def test_an_inferred_name_keeps_the_old_refusal(tmp_path, cpp, why):
    with pytest.raises(Refusal, match="onRemoving is already a name in Code/Game/Widget.cpp$"):
        plan(tmp_path, cpp, "onRemoving", basis="inferred")
    assert plan(tmp_path / "canonical", cpp, "onRemoving")      # the same text lands as canonical


# ------------------------------------------------------ neighbours that stay refused

def refused(tmp_path, cpp, new, match, **kwargs):
    with pytest.raises(Refusal, match=r"%s is already a name in Code/Game/Widget.cpp \(.*%s" % (new, match)):
        plan(tmp_path, cpp, new, **kwargs)


def test_a_local_in_a_function_that_spells_the_old_word_stays_refused(tmp_path):
    # the function refers to itself: the local would hide the member at that call
    cpp = (WIDGET + "struct Thing { void touch(); };\n"
           "void Widget::rva00701000(int x) { Thing &lookup = *(Thing *)0; if (x) rva00701000(x - 1); }\n")
    refused(tmp_path, cpp, "lookup", "spells rva00701000 itself")


def test_a_local_in_another_function_that_calls_the_old_word_stays_refused(tmp_path):
    cpp = (WIDGET + "struct Thing { void touch(); };\nvoid Widget::rva00701000(int x) {}\n"
           "void run(Widget *w) { Thing &lookup = *(Thing *)0; w->rva00701000(1); lookup.touch(); }\n")
    refused(tmp_path, cpp, "lookup", "spells rva00701000 itself")


def test_a_spelling_before_the_local_declaration_stays_refused(tmp_path):
    cpp = (WIDGET + "struct Thing { void touch(); };\nint lookup(int);\n"
           "void Widget::rva00701000(int x) { lookup(x); Thing &lookup = *(Thing *)0; lookup.touch(); }\n")
    refused(tmp_path, cpp, "lookup", "file scope")


def test_a_local_use_outside_its_block_stays_refused(tmp_path):
    cpp = (WIDGET + "struct Thing { void touch(); };\n"
           "void Widget::rva00701000(int x) { if (x) { Thing &lookup = *(Thing *)0; lookup.touch(); } lookup(x); }\n")
    refused(tmp_path, cpp, "lookup", "not confined")


def test_a_base_class_member_stays_refused(tmp_path):
    cpp = ("class Other { public: virtual void onRemoving(int); };\n"
           "class Widget : public Other { public: void rva00701000(int); };\n"
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "Other is a base of Widget")


def test_a_base_through_a_template_specialization_stays_refused(tmp_path):
    cpp = ("class Other { public: virtual void onRemoving(int); };\n"
           "template<int N> class Slots : public Slots<N-1> { public: virtual void gap(int); };\n"
           "template<> class Slots<0> : public Other { };\n"
           "class Widget : public Slots<3> { public: void rva00701000(int); };\n"
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "Other is a base of Widget")


@pytest.mark.parametrize("base", ["Pair<A, B>", "Wrapper<Mid<A> >", "Wrapper<Mid<A>>", "Pair<A, Wrapper<B, C> >"])
def test_a_base_through_a_multi_argument_or_nested_template_stays_refused(tmp_path, base):
    # the base list is split on top-level commas only and a template's arguments are not bases:
    # Widget -> Pair<A, B> -> Other, so Widget::onRemoving would override Other's virtual
    cpp = ("class Other { public: virtual void onRemoving(int); void call(); };\n"
           "class A { }; class B { }; class C { }; class Mid { };\n"
           "template<class X, class Y> class Pair : public Other { };\n"
           "template<class X> class Wrapper : public Other { };\n"
           f"class Widget : public {base} {{ public: void rva00701000(int); }};\n"
           "void Widget::rva00701000(int x) {}\nvoid Other::onRemoving(int x) {}\n")
    if base.startswith("Pair<A, Wrapper"):
        cpp = cpp.replace("template<class X, class Y> class Pair : public Other { };",
                          "template<class X, class Y> class Pair : public Wrapper<X> { };")
    refused(tmp_path, cpp, "onRemoving", "Other is a base of Widget")


@pytest.mark.parametrize("base", ["Dep<Other>", "Typed<Other>", "Outer<Other>::Inner"])
def test_a_dependent_base_stays_refused(tmp_path, base):
    # a base the scan cannot name (a template parameter, a nested type) leaves the chain unknown
    cpp = ("class Other { public: virtual void onRemoving(int); };\n"
           "template<class T> class Dep : public T { };\n"
           "template<class T> class Typed : public T::Base { };\n"
           "template<class T> struct Outer { struct Inner { }; };\n"
           f"class Widget : public {base} {{ public: void rva00701000(int); }};\n"
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "a base of Widget is not declared")


def test_a_template_base_clause_is_read_at_top_level_only():
    names = rename.base_clause_names
    assert names(" public Pair<A, B>, private Z") == ["Pair", "Z"]
    assert names("public Wrapper<Mid<A> >") == names("public Wrapper<Mid<A>>") == ["Wrapper"]
    assert names("virtual public ns::Base<int>, ::Top") == ["Base", "Top"]
    for unreadable in ("typename T::X", "public Pair<A>::Inner", "public T...", "public Foo<(1>2)>",
                       "public Foo<A", "public A,, public B"):
        assert names(unreadable) is None, unreadable


def test_a_class_derived_from_the_renamed_class_stays_refused(tmp_path):
    cpp = (WIDGET + "class Sub : public Widget { public: void onRemoving(int); };\n"
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "Sub derives from Widget")


def test_a_class_deriving_from_both_stays_refused(tmp_path):
    cpp = ("class Other { public: virtual void onRemoving(int); };\n" + WIDGET +
           "class Both : public Widget, public Other { };\nvoid Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "Both derives from Widget and from Other")


def test_a_class_with_an_undeclared_base_stays_refused(tmp_path):
    cpp = ("class Other : public Missing { public: virtual void onRemoving(int); };\n" + WIDGET +
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "Other is not a class declared with all its bases")


def test_an_undeclared_base_of_the_renamed_class_stays_refused(tmp_path):
    cpp = ("class Other { public: virtual void onRemoving(int); };\n"
           "class Widget : public Missing { public: void rva00701000(int); };\n"
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "a base of Widget is not declared")


def test_the_renamed_class_itself_declaring_the_word_stays_refused(tmp_path):
    cpp = ("class Widget { public: void rva00701000(int); void onRemoving(char); };\n"
           "void Widget::rva00701000(int x) {}\nvoid Widget::onRemoving(char) {}\n")
    refused(tmp_path, cpp, "onRemoving", "Widget itself")


def test_the_old_word_spelled_inside_the_other_class_stays_refused(tmp_path):
    # `rva00701000(1)` in Other's own method would become `onRemoving(1)` -- Other's member
    cpp = ("class Other { public: virtual void onRemoving(int); void run() { rva00701000(1); } };\n" + WIDGET +
           "void Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "spelled unqualified inside Other")


def test_the_old_word_unqualified_in_the_others_out_of_line_method_stays_refused(tmp_path):
    cpp = ("class Other { public: virtual void onRemoving(int); void run(); };\n" + WIDGET +
           "void Other::run() { rva00701000(1); }\nvoid Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "onRemoving", "spelled unqualified inside Other")


@pytest.mark.parametrize("cpp,match", [
    ("void onRemoving(int);\n" + WIDGET + "void Widget::rva00701000(int x) {}\n", "file scope"),
    ("int onRemoving = 3;\n" + WIDGET + "void Widget::rva00701000(int x) {}\n", "file scope"),
    ("#define onRemoving 1\n" + WIDGET + "void Widget::rva00701000(int x) {}\n", "preprocessor"),
    ("class Other { public: void onRemoving(int); };\n" + WIDGET +
     "void Widget::rva00701000(int x) { Other *o = 0; o->onRemoving(x); }\n", "object whose type"),
    ("class Other { public: void onRemoving(int); };\n" + WIDGET +
     "void Widget::rva00701000(int x) { Other o; o.onRemoving(x); }\n", "object whose type"),
    ("class Other { public: void onRemoving(int); };\n" + WIDGET +
     "void Widget::rva00701000(int x) { ::onRemoving(x); }\n", "global-scope"),
    ("class Other { public: void onRemoving(int); };\nclass Nope;\n" + WIDGET +
     "void Widget::rva00701000(int x) { Nope::onRemoving(x); }\n", "Nope is not a class"),
    ("class Base { public: void onRemoving(int); };\nclass Other { public: using Base::onRemoving; };\n" + WIDGET +
     "void Widget::rva00701000(int x) {}\n", "using"),
    ("void onRemoving(int);\nclass Other { friend void onRemoving(int); };\n" + WIDGET +
     "void Widget::rva00701000(int x) {}\n", "file scope|friend"),
    ("struct { int onRemoving; } cfg;\n" + WIDGET + "void Widget::rva00701000(int x) {}\n", "cfg is not a class"),
    ("DECLARE(int onRemoving);\n" + WIDGET + "void Widget::rva00701000(int x) {}\n", "no function and no prototype"),
    ("class Other { public: Other(int a) : m(onRemoving) {} int m; };\n" + WIDGET +
     "void Widget::rva00701000(int x) {}\n", "no function and no prototype|not confined|spells"),
    # a definition that does not start its line is no prototype: its body would call the shadowing parameter
    (WIDGET + "class Sub : public Widget { public: void go(int onRemoving) { rva00701000(1); } };\n"
     "void Widget::rva00701000(int x) {}\n", "no function and no prototype"),
    ("int tag; " + WIDGET + "struct Sub { void go(int onRemoving) const { } };\n"
     "void Widget::rva00701000(int x) {}\n", "no function and no prototype"),
    # the member-initializer list is part of the function: the parameter would capture its call
    (WIDGET + "class Derived : public Widget { public: Derived(int onRemoving); int m; };\n"
     "Derived::Derived(int onRemoving) : m(rva00701000(1)) {}\nvoid Widget::rva00701000(int x) {}\n",
     "Derived::Derived spells rva00701000 itself"),
])
def test_other_spellings_stay_refused(tmp_path, cpp, match):
    refused(tmp_path, cpp, "onRemoving", match)


def test_a_free_function_rename_keeps_the_old_refusal(tmp_path):
    cpp = ("class Other { public: void lookup(int); };\nvoid rva00701000(int x) {}\n")
    row = f"?rva00701000@@YAXH@Z,,0x00701000,10,{SRC},matched,address-derived\n"
    tree = tree_of(tmp_path, row, **{SRC: "// cl: /O2\n" + cpp})
    ctx = rename.Context(tree, object_scan=False)
    with pytest.raises(Refusal, match=r"lookup is already a name in .*no class"):
        rename.plan_rename("function", ctx=ctx, rva=0x00701000, new="lookup", basis="canonical:wb",
                           evidence="wb lead 0x00701000: x")


# ------------------------------------------------- the scans the rule stands on

def test_occurrence_spots_carry_the_offset_of_each_kind():
    code = "class A { public: void f(int word); };\nint word;\nvoid g() { int word = 1; }\n"
    spots = rename.occurrence_spots(code, "word")
    assert [kind for _at, kind in spots] == rename.occurrence_kinds(code, "word") == ["param", "ns", "fnbody"]
    assert all(code[at:at + 4] == "word" for at, _kind in spots)


def test_a_chain_through_a_template_specialization_is_not_cut(tmp_path):
    cpp = ("class Root { };\ntemplate<int N> class Slots : public Slots<N-1> { };\n"
           "template<> class Slots<0> : public Root { };\nclass Leaf : public Slots<2> { };\n")
    tree = tree_of(tmp_path, "", **{SRC: cpp})
    ctx = rename.Context(tree, object_scan=False)
    assert rename.class_ancestors(ctx, SRC, "Leaf") == {"Leaf", "Slots", "Root"}


def test_a_chain_through_multi_argument_and_nested_template_bases_is_not_cut(tmp_path):
    cpp = ("class Root { };\ntemplate<class X, class Y> class Pair : public Root { };\n"
           "template<class X> class Wrapper : public Pair<X, X> { };\n"
           "class Leaf : public Wrapper<Pair<int, char> > { };\n"
           "class Odd : public Wrapper<Pair<int, char> >::Inner { };\n")
    tree = tree_of(tmp_path, "", **{SRC: cpp})
    ctx = rename.Context(tree, object_scan=False)
    assert rename.class_ancestors(ctx, SRC, "Leaf") == {"Leaf", "Wrapper", "Pair", "Root"}
    assert rename.class_ancestors(ctx, SRC, "Odd") is None


# ------------------------------------------- a share must not make a recorded landing unrevertible

BASIS_HEADER = "kind,old,new,basis,evidence,source,rva\n"
SHARED = ("class Other { public: virtual void lookup(int); };\n" + WIDGET +
          "void Other::lookup(int) {}\nvoid Widget::rva00701000(int x) {}\n")


def test_a_word_an_unreverted_inferred_landing_holds_is_not_shared(tmp_path):
    record = "function,rva00555000,lookup,inferred,agree:abc123,Code/Game/Widget.cpp,0x00555000\n"
    basis = {"reverse/name_basis.csv": BASIS_HEADER + record}
    with pytest.raises(Refusal, match=r"lookup is already a name in .*agree:abc123 landed lookup"):
        plan(tmp_path, SHARED, "lookup", extra=basis)


def test_a_reverted_landing_or_another_word_leaves_the_share_open(tmp_path):
    record = "function,rva00555000,lookup,inferred,agree:abc123,Code/Game/Widget.cpp,0x00555000\n"
    restored = "function,lookup,rva00555000,restored,revert:abc123 wrong,Code/Game/Widget.cpp,0x00555000\n"
    other = "function,rva00555000,otherName,inferred,agree:def456,Code/Game/Widget.cpp,0x00555000\n"
    for rows in (record + restored, other):
        extra = {"reverse/name_basis.csv": BASIS_HEADER + rows}
        assert plan(tmp_path / str(abs(hash(rows))), SHARED, "lookup", extra=extra)


# ------------------------------- a declaration the rewrite respells besides the row's own
# The word rewrite also respells the base's declaration of the one virtual function (and
# every overrider's), so those classes are renamed scopes: a class beside or beyond them
# that already spells the new word would become an override (or a second overload).

def plan_virtual(tmp_path, owner, cpp, new="lookup"):
    row = f"?rva00701000@{owner}@@UAEXH@Z,,0x00701000,10,{SRC},matched,address-derived\n"
    tree = tree_of(tmp_path, row, **{SRC: "// cl: /O2\n" + cpp})
    ctx = rename.Context(tree, object_scan=False)
    return rename.plan_rename("function", ctx=ctx, rva=0x00701000, new=new, basis="canonical:wb",
                              evidence="wb lead 0x00701000: x")


BASE = ("class Base { public: virtual void rva00701000(int); virtual ~Base(); };\n"
        "class Widget : public Base { public: virtual void rva00701000(int); };\n")


@pytest.mark.parametrize("declaration", ["virtual void lookup(int);", "void lookup(int);"])
def test_a_sibling_of_the_respelled_base_declaring_the_word_is_refused(tmp_path, declaration):
    # Base::rva00701000 becomes Base::lookup too, so Sibling::lookup would override it
    cpp = BASE + f"class Sibling : public Base {{ public: {declaration} }};\n"
    with pytest.raises(Refusal, match=r"lookup is already a name in Code/Game/Widget.cpp \(.*Sibling derives from Base"):
        plan_virtual(tmp_path, "Widget", cpp)


def test_a_qualified_spelling_through_a_sibling_of_the_respelled_base_is_refused(tmp_path):
    cpp = BASE + ("class Sibling : public Base { public: void lookup(int); };\n"
                  "void Widget::rva00701000(int x) { ((Sibling *)this)->Sibling::lookup(x); }\n")
    with pytest.raises(Refusal, match=r"Sibling derives from Base"):
        plan_virtual(tmp_path, "Widget", cpp)


@pytest.mark.parametrize("declaration", ["virtual void lookup(int);", "void lookup(int);"])
def test_a_second_base_of_the_respelled_overrider_declaring_the_word_is_refused(tmp_path, declaration):
    # renaming the base's row also renames Widget's override, which a second base of Widget now matches
    cpp = (f"class Extra {{ public: {declaration} }};\n"
           "class Base { public: virtual void rva00701000(int); virtual ~Base(); };\n"
           "class Widget : public Base, public Extra { public: virtual void rva00701000(int); };\n")
    with pytest.raises(Refusal, match=r"Extra is a base of Widget"):
        plan_virtual(tmp_path, "Base", cpp)


def test_a_class_deriving_from_the_respelled_overrider_is_refused_from_the_base_row(tmp_path):
    cpp = BASE + "class Leaf : public Widget { public: void lookup(int); };\n"
    with pytest.raises(Refusal, match=r"Leaf derives from Base"):
        plan_virtual(tmp_path, "Base", cpp)


def test_a_class_deriving_from_the_respelled_base_and_another_is_refused(tmp_path):
    cpp = ("class Other { public: virtual void lookup(int); };\n" + BASE +
           "class Both : public Base, public Other { };\n")
    with pytest.raises(Refusal, match=r"Both derives from Base and from Other"):
        plan_virtual(tmp_path, "Widget", cpp)


def test_an_unrelated_class_beside_a_respelled_base_still_shares_the_word(tmp_path):
    cpp = ("class Other { public: virtual void lookup(int); };\n" + BASE)
    text = plan_virtual(tmp_path, "Widget", cpp).after[SRC].decode()
    assert "class Base { public: virtual void lookup(int);" in text
    assert "class Widget : public Base { public: virtual void lookup(int); };" in text
    assert "class Other { public: virtual void lookup(int); };" in text and "rva00701000" not in text


# ---------------------------------- the class relations are read across the header closure, too
# A unit's classes are often declared in a header and only defined out of line in the .cpp. The
# respelled base and overrider (and so the sibling that would become an override) must be found
# there, not only in the one file's own text.

HEADER = "Code/Game/Widget.h"


def plan_split(tmp_path, header, cpp, owner="Widget", new="lookup"):
    row = f"?rva00701000@{owner}@@UAEXH@Z,,0x00701000,10,{SRC},matched,address-derived\n"
    tree = tree_of(tmp_path, row, **{SRC: '// cl: /O2\n#include "Widget.h"\n' + cpp, HEADER: header})
    ctx = rename.Context(tree, object_scan=False)
    return rename.plan_rename("function", ctx=ctx, rva=0x00701000, new=new, basis="canonical:wb",
                              evidence="wb lead 0x00701000: x")


@pytest.mark.parametrize("declaration", ["virtual void lookup(int);", "void lookup(int);"])
def test_a_sibling_of_a_base_declared_in_the_header_is_refused(tmp_path, declaration):
    # Base and Widget are in the header; the .cpp holds Widget::rva00701000 and Sibling
    cpp = (f"class Sibling : public Base {{ public: {declaration} }};\n"
           "void Widget::rva00701000(int x) {}\n")
    with pytest.raises(Refusal, match=r"lookup is already a name in Code/Game/Widget.cpp \(.*Sibling derives from Base"):
        plan_split(tmp_path, BASE, cpp)


def test_a_class_deriving_from_a_header_overrider_is_refused_from_the_base_row(tmp_path):
    cpp = ("class Leaf : public Widget { public: void lookup(int); };\n"
           "void Base::rva00701000(int x) {}\n")
    with pytest.raises(Refusal, match=r"Leaf derives from Base"):
        plan_split(tmp_path, BASE, cpp, owner="Base")


def test_a_second_base_of_a_header_overrider_declaring_the_word_is_refused(tmp_path):
    header = ("class Extra { public: virtual void lookup(int); };\n"
              "class Base { public: virtual void rva00701000(int); virtual ~Base(); };\n"
              "class Widget : public Base, public Extra { public: virtual void rva00701000(int); };\n")
    cpp = "void Base::rva00701000(int x) {}\nvoid Extra::lookup(int) {}\n"
    with pytest.raises(Refusal, match=r"Extra is a base of Widget"):
        plan_split(tmp_path, header, cpp, owner="Base")


def test_an_unrelated_class_in_the_cpp_beside_the_header_classes_shares_the_word(tmp_path):
    cpp = ("class Other { public: virtual void lookup(int); };\n"
           "void Widget::rva00701000(int x) {}\n")
    plan = plan_split(tmp_path, BASE, cpp)
    assert "class Other { public: virtual void lookup(int); };" in plan.after[SRC].decode()
    assert "virtual void lookup(int);" in plan.after[HEADER].decode() and "rva00701000" not in plan.after[HEADER].decode()


# ------------------------------------ a macro can carry the old word into a scope of the new one
# The word rewrite respells a macro body too, so a function (or class) that declares the new
# word and invokes a macro that spells the old one would see the new word captured.

OBJECT_MACRO = "#define CALL_RVA this->rva00701000(1)\n"
FUNCTION_MACRO = "#define CALL_RVA(arg) this->rva00701000(arg)\n"


@pytest.mark.parametrize("macro,use", [(OBJECT_MACRO, "CALL_RVA;"), (FUNCTION_MACRO, "CALL_RVA(2);")])
def test_a_local_that_reaches_the_old_word_through_a_macro_is_refused(tmp_path, macro, use):
    cpp = (WIDGET + "struct Thing { void touch(); };\n" + macro +
           f"void run(Widget *w) {{ Thing &lookup = *(Thing *)0; {use} lookup.touch(); }}\n")
    refused(tmp_path, cpp, "lookup", "invokes the macro CALL_RVA")


@pytest.mark.parametrize("macro,use", [(OBJECT_MACRO, "CALL_RVA;"), (FUNCTION_MACRO, "CALL_RVA(2);")])
def test_a_parameter_that_reaches_the_old_word_through_a_macro_is_refused(tmp_path, macro, use):
    cpp = WIDGET + macro + f"void run(int lookup) {{ {use} }}\n"
    refused(tmp_path, cpp, "lookup", "invokes the macro CALL_RVA")


def test_a_macro_reaching_the_old_word_through_another_macro_is_refused(tmp_path):
    cpp = (WIDGET + "struct Thing { void touch(); };\n" + FUNCTION_MACRO + "#define OUTER(arg) CALL_RVA(arg)\n"
           "void run(Widget *w) { Thing &lookup = *(Thing *)0; OUTER(2); lookup.touch(); }\n")
    refused(tmp_path, cpp, "lookup", "invokes the macro OUTER")


def test_a_macro_in_a_header_reaching_the_old_word_is_refused(tmp_path):
    cpp = ("struct Thing { void touch(); };\n"
           "void run(Widget *w) { Thing &lookup = *(Thing *)0; CALL_RVA(2); lookup.touch(); }\n"
           "void Widget::rva00701000(int x) {}\n")
    with pytest.raises(Refusal, match=r"invokes the macro CALL_RVA"):
        plan_split(tmp_path, WIDGET.replace("virtual ", "") + FUNCTION_MACRO, cpp)


def test_a_macro_invoked_in_the_other_classs_method_is_refused(tmp_path):
    cpp = ("class Other { public: virtual void lookup(int); };\n" + WIDGET + FUNCTION_MACRO +
           "void Other::lookup(int x) { CALL_RVA(x); }\nvoid Widget::rva00701000(int x) {}\n")
    refused(tmp_path, cpp, "lookup", "invokes the macro CALL_RVA")


def test_a_macro_invoked_in_a_class_body_declared_in_a_header_is_refused(tmp_path):
    header = ("class Other { public: virtual void lookup(int); void again(int x) { CALL_RVA(x); } };\n"
              + WIDGET + FUNCTION_MACRO)
    cpp = "void Other::lookup(int) {}\nvoid Widget::rva00701000(int x) {}\n"
    with pytest.raises(Refusal, match=r"invokes the macro CALL_RVA"):
        plan_split(tmp_path, header, cpp)


def test_a_macro_that_never_reaches_the_old_word_or_is_not_invoked_there_shares_the_word(tmp_path):
    # the macro spells the old word but no scope that declares the new word invokes it; and a macro
    # that does not spell it may be invoked anywhere
    cpp = (WIDGET + "struct Thing { void touch(); };\n" + FUNCTION_MACRO + "#define PLAIN(arg) ((arg) + 1)\n"
           "void run(Widget *w) { CALL_RVA(1); }\n"
           "void other(Widget *w) { Thing &lookup = *(Thing *)0; int n = PLAIN(2); lookup.touch(); }\n"
           "void Widget::rva00701000(int x) {}\n")
    text = plan(tmp_path, cpp, "lookup").after[SRC].decode()
    assert "this->lookup(arg)" in text and "Thing &lookup = *(Thing *)0;" in text
