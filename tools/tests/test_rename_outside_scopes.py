"""tools/rename.py relatives_outside_the_rewrite: what a canonical function rename reads in the files it
does not rewrite. Beside the classes that declare or qualify the new word, an untouched file's preprocessor
lines, its unqualified spellings inside a method of the renamed class or of a class derived from it, and
the out-of-line methods of an unrelated class defined in a header are read, and a word an unreverted
inferred landing holds is refused. A miniature tree (a temporary git repository), so no compiler is needed."""
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

from rename import Refusal  # noqa: E402
from test_rename_canonical_collisions import (  # noqa: E402,F401
    BASIS_HEADER, OTHER_CPP, OTHER_ROW, ROW, SRC, SUB_H, _evidence_gates_stubbed, plan_outside)

WIDGET_BAR_H = "class Widget { public: virtual void rva00701000(int); void bar(); virtual ~Widget(); };\n"
WIDGET_H = "Code/Game/Widget.h"
W2 = "Code/Game/Widget2.cpp"
W2_ROW = f"?bar@Widget@@QAEXXZ,,0x00702000,10,{W2},matched,address-derived\n"
NOT_A_CLASS = "// no classes\n"


def w2(text):
    return {W2: '// cl: /O2\n#include "Widget.h"\n' + text, SUB_H: NOT_A_CLASS, WIDGET_H: WIDGET_BAR_H}


def plan_w2(tmp_path, text, **extra):
    files = w2(text)
    files.update(extra)
    return plan_outside(tmp_path, files, rows=ROW + W2_ROW)


def renamed(plan):
    return "void Widget::lookup(int x)" in plan.after[SRC].decode()


# ----------------------------------------- an unqualified spelling inside a method of the renamed class

def test_a_method_of_the_renamed_class_calling_a_global_of_the_word_is_refused(tmp_path):
    with pytest.raises(Refusal, match=r"Widget::bar is a method of Widget, which is or derives from a renamed "
                                      r"class, and spells lookup unqualified, where .*; Code/Game/Widget2.cpp spells lookup"):
        plan_w2(tmp_path, "void lookup(int);\nvoid Widget::bar() { lookup(1); }\n")


def test_a_method_of_a_derived_class_calling_a_global_of_the_word_is_refused(tmp_path):
    with pytest.raises(Refusal, match=r"D::bar is a method of D, which is or derives from a renamed class"):
        plan_w2(tmp_path, "void lookup(int);\nstruct D : Widget { void bar(); };\nvoid D::bar() { lookup(1); }\n")


def test_an_inline_method_of_a_descendant_in_an_untouched_header_is_refused(tmp_path):
    sub = '#include "Widget.h"\nint lookup(int);\nclass Sub : public Widget { public: void go() { lookup(1); } };\n'
    with pytest.raises(Refusal, match=r"Sub is or derives from a renamed class and spells lookup unqualified in a function body"):
        plan_outside(tmp_path, {SUB_H: sub})


def test_a_parameter_or_a_local_of_the_word_in_a_method_of_the_renamed_class_is_fine(tmp_path):
    text = ("void Widget::bar() { int lookup = 1; lookup += 2; { int again = lookup; } }\n"
            "struct D : Widget { void baz(int lookup); };\nvoid D::baz(int lookup) { lookup += 1; }\n")
    assert renamed(plan_w2(tmp_path, text))


def test_a_use_before_the_local_of_the_word_in_a_method_of_the_renamed_class_is_refused(tmp_path):
    with pytest.raises(Refusal, match=r"Widget::bar is a method of Widget"):
        plan_w2(tmp_path, "void Widget::bar() { lookup(1); int lookup = 1; lookup += 2; }\n")


def test_a_free_function_or_an_unrelated_method_may_spell_the_word_unqualified(tmp_path):
    text = ("void lookup(int);\nvoid free(int) { lookup(1); }\nclass Plain { public: void foo(); };\n"
            "void Plain::foo() { lookup(1); }\n")
    assert renamed(plan_w2(tmp_path, text))


def test_a_method_of_a_class_with_an_undeclared_base_spelling_the_word_is_refused(tmp_path):
    with pytest.raises(Refusal, match=r"Lost, in which lookup is spelled in a function, is not a class declared "
                                      r"with all its bases"):
        plan_w2(tmp_path, "void lookup(int);\nclass Lost : public Missing { public: void foo(); };\n"
                          "void Lost::foo() { lookup(1); }\n")


def test_a_call_through_an_object_in_a_method_of_the_renamed_class_is_not_read(tmp_path):
    assert renamed(plan_w2(tmp_path, "void Widget::bar() { Other o; o.lookup(1); o->lookup(2); }\n"))


# ----------------------------------------- a preprocessor line that spells the word

@pytest.mark.parametrize("line", ["#define lookup(x) other_##x", "#define DECL void lookup(int);",
                                  "#define CALL_LOOKUP(x) lookup(x)"])
def test_a_macro_spelling_the_word_in_an_untouched_header_is_refused(tmp_path, line):
    with pytest.raises(Refusal, match=r"a preprocessor line in Code/Game/Sub.h spells lookup"):
        plan_outside(tmp_path, {SUB_H: line + "\n"})


def test_a_descendant_that_declares_the_word_through_a_macro_is_refused(tmp_path):
    sub = '#include "Widget.h"\n#define DECL void lookup(int);\nclass Sub : public Widget { public: DECL };\n'
    with pytest.raises(Refusal, match=r"a preprocessor line in Code/Game/Sub.h spells lookup"):
        plan_outside(tmp_path, {SUB_H: sub})


def test_a_macro_formal_named_like_the_word_is_not_a_spelling(tmp_path):
    assert renamed(plan_outside(tmp_path, {SUB_H: "#define APPLY(lookup) ((lookup) + 1)\nclass Plain "
                                                  "{ public: void lookup(int); };\n"}))


# ----------------------------------------- the out-of-line methods of an unrelated class in a header

def test_a_method_of_an_unrelated_class_defined_in_a_touched_header_that_spells_the_old_word_is_refused(tmp_path):
    files = {SUB_H: "class Plain { public: void lookup(int); void foo(); };\n",
             "Code/Game/Util.h": "inline void Plain::foo() { rva00701000(1); }\n",
             SRC: '// cl: /O2\n#include "Widget.h"\n#include "Sub.h"\n#include "Util.h"\n'
                  'void Widget::rva00701000(int x) {}\n'}
    with pytest.raises(Refusal, match=r"rva00701000 is spelled unqualified inside Plain"):
        plan_outside(tmp_path, files)


def test_the_same_method_defined_in_the_unit_is_refused_as_before(tmp_path):
    files = {SUB_H: "class Plain { public: void lookup(int); void foo(); };\n",
             SRC: '// cl: /O2\n#include "Widget.h"\n#include "Sub.h"\nvoid Plain::foo() { rva00701000(1); }\n'
                  'void Widget::rva00701000(int x) {}\n'}
    with pytest.raises(Refusal, match=r"rva00701000 is spelled unqualified inside Plain"):
        plan_outside(tmp_path, files)


# ----------------------------------------- a word an unreverted inferred landing holds

LANDING = "function,rva00555000,lookup,inferred,agree:abc123,Code/Game/Other.cpp,0x00555000\n"


def test_an_unreverted_inferred_landing_of_the_word_makes_an_outside_spelling_refuse(tmp_path):
    files = {SUB_H: "class Other { public: virtual void lookup(int); };\n",
             "reverse/name_basis.csv": BASIS_HEADER + LANDING}
    with pytest.raises(Refusal, match=r"outside the files this rename rewrites .*agree:abc123 landed lookup "
                                      r"as an inferred name"):
        plan_outside(tmp_path, files)


def test_a_restored_landing_does_not_hold_the_word(tmp_path):
    restored = "function,rva00555000,Rva00555000,restored,revert:abc123,Code/Game/Other.cpp,0x00555000\n"
    files = {SUB_H: "class Other { public: virtual void lookup(int); };\n",
             "reverse/name_basis.csv": BASIS_HEADER + LANDING + restored}
    assert renamed(plan_outside(tmp_path, files))


def test_an_inferred_rename_reads_only_the_files_it_rewrites(tmp_path):
    # Decided: an inferred rename is not extended to files outside its rewrite. A later `revert` of it would
    # rewrite the unrelated class's `lookup` too, which foreign_declarations refuses (it fails closed), so
    # the landing stays, only unrevertable; refusing every outside spelling would turn away most inferred names.
    files = {SUB_H: "class Unrelated { public: virtual void lookup(int); };\n"}
    plan = plan_outside(tmp_path, files, basis="inferred")
    assert renamed(plan)


def test_an_inline_method_of_an_unrelated_class_may_spell_the_word_unqualified(tmp_path):
    sub = 'int lookup(int);\nclass Plain { public: void go() { lookup(1); } };\n'
    assert renamed(plan_outside(tmp_path, {SUB_H: sub}))


# ----------------------------------------- shapes name_metric.functions_in does not read as a function
# Out-of-line members of a class template, operators, a constructor's member-initializer list, a static
# member's initializer and a default argument are in the scope of their class, but the function scan
# returns nothing for the first two and the spot is not a body for the others. A touched file refuses all
# of them as file-scope names; an untouched one must refuse them too when the class is or derives from a
# renamed class.

CLASS_SUB = "class Sub : public Widget { public: %s };\n"
SCOPE_SHAPES = {
    "template method": ("template<class T> class Sub : public Widget { public: void go(); };\n"
                        "template<class T> void Sub<T>::go() { lookup(1); }\n"),
    "operator": CLASS_SUB % "int operator+(int);" + "inline int Sub::operator+(int a) { return lookup(a); }\n",
    "operator call": CLASS_SUB % "int operator()(int);" + "inline int Sub::operator()(int a) { return lookup(a); }\n",
    "constructor initializer": CLASS_SUB % "Sub(); int a;" + "inline Sub::Sub() : a((lookup(1), 0)) {}\n",
    "inline constructor initializer": CLASS_SUB % "Sub() : a((lookup(1), 0)) {} int a;",
    "static member initializer": CLASS_SUB % "static int k;" + "int Sub::k = (lookup(1), 0);\n",
    "static member call initializer": CLASS_SUB % "static int k;" + "int Sub::k = lookup(1);\n",
    "static member array initializer": CLASS_SUB % "static int k[2];" + "int Sub::k[2] = { lookup(1), 2 };\n",
    "default argument": CLASS_SUB % "void go(int a = sizeof(lookup(1)));",
    "inline default argument": CLASS_SUB % "void go(int a = 2, int b = lookup(1));",
    "template default argument": ("template<class T> class Sub : public Widget { public: void go(int a = lookup(1)); };\n"),
    "macro prefixed static member": CLASS_SUB % "static int k;" + "DECLARE(x)\nint Sub::k = lookup(1);\n",
}


@pytest.mark.parametrize("shape", list(SCOPE_SHAPES))
def test_an_unqualified_spelling_in_a_shape_the_function_scan_misses_is_refused(tmp_path, shape):
    sub = '#include "Widget.h"\nint lookup(int);\n' + SCOPE_SHAPES[shape]
    with pytest.raises(Refusal, match=r"Sub is or derives from a renamed class and spells lookup unqualified in|"
                                      r"Sub::Sub is a method of Sub, which is or derives from a renamed class"):
        plan_outside(tmp_path, {SUB_H: sub})


@pytest.mark.parametrize("shape", list(SCOPE_SHAPES))
def test_the_same_shapes_of_an_unrelated_class_may_spell_the_word_unqualified(tmp_path, shape):
    sub = '#include "Widget.h"\nint lookup(int);\n' + SCOPE_SHAPES[shape].replace(" : public Widget", "")
    assert renamed(plan_outside(tmp_path, {SUB_H: sub}))


def test_a_method_of_the_renamed_class_itself_in_those_shapes_is_refused(tmp_path):
    with pytest.raises(Refusal, match=r"Widget::Widget is a method of Widget"):
        plan_w2(tmp_path, "void lookup(int);\nWidget::Widget() : x((lookup(1), 0)) {}\n"
                          "void Widget::bar() { lookup(1); }\n")
    with pytest.raises(Refusal, match=r"Widget is or derives from a renamed class and spells lookup unqualified"):
        plan_w2(tmp_path, "void lookup(int);\nint Widget::k = (lookup(1), 0);\n")


def test_a_parameter_or_a_local_of_the_word_in_those_shapes_is_fine(tmp_path):
    text = ("template<class T> struct D : Widget { void baz(int); int operator+(int); D(int); int m; };\n"
            "template<class T> void D<T>::baz(int lookup) { lookup += 1; }\n"
            "template<class T> int D<T>::operator+(int a) { int lookup = a; return lookup; }\n"
            "template<class T> D<T>::D(int lookup) : m(lookup) {}\n")
    assert renamed(plan_w2(tmp_path, text))


def test_a_local_does_not_excuse_a_spelling_in_the_initializer_list(tmp_path):
    text = ("void lookup(int);\nstruct D : Widget { D(); int m; };\n"
            "D::D() : m((lookup(1), 0)) { int lookup = 2; lookup += 1; }\n")
    with pytest.raises(Refusal, match=r"D::D is a method of D, which is or derives from a renamed class"):
        plan_w2(tmp_path, text)


def test_a_file_scope_declaration_a_type_or_a_qualified_call_is_not_a_class_scope(tmp_path):
    sub = ('#include "Widget.h"\nint lookup(int);\nstruct Plain { typedef int Handle; static int make(int); };\n'
           'Plain::Handle lookup2(Plain::Handle h = lookup(1));\nint table[] = { lookup(1), 2 };\n'
           'int made = Plain::make(lookup(3));\nclass Sub : public Widget { public: void go(int lookup); };\n')
    assert renamed(plan_outside(tmp_path, {SUB_H: sub}))
