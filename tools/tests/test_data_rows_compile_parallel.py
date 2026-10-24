import sys
import threading
import time
from pathlib import Path
from types import SimpleNamespace
import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import data_rows


def setup(monkeypatch, tmp_path, rows, workers=24, object_path=None):
    monkeypatch.setattr(data_rows,'ROOT',tmp_path)
    monkeypatch.setattr(data_rows,'load',lambda:rows)
    monkeypatch.setattr(data_rows,'Resolver',lambda every:object())
    monkeypatch.setattr(data_rows,'_tools',lambda:(SimpleNamespace(
        _pool_size=lambda:workers,obj_path=object_path or (lambda p:p.with_suffix('.obj'))),
        SimpleNamespace(Image=lambda:object())))


def test_compile_groups_overlap_but_source_writers_and_diagnostics_stay_ordered(monkeypatch,tmp_path):
    rows=[{'source':s,'name':n} for s,n in [('a.cpp','a1'),('b.cpp','b1'),('a.cpp','a2'),('c.cpp','c1')]]
    setup(monkeypatch,tmp_path,rows)
    barrier=threading.Barrier(3);lock=threading.Lock();active=set();seen=[]
    def verify(row,img,resolve,compile):
        assert compile is True
        with lock:
            assert row['source'] not in active
            active.add(row['source'])
        if row['name']!='a2':barrier.wait(timeout=5)
        with lock:
            active.remove(row['source']);seen.append(row['name'])
        return False,'wrong '+row['name']
    monkeypatch.setattr(data_rows,'verify_row',verify)
    logs=[]
    with pytest.raises(SystemExit) as error:data_rows.verify(compile=True,log=logs.append)
    assert error.value.code==1 and set(seen)=={'a1','a2','b1','c1'}
    assert seen.index('a1')<seen.index('a2')
    assert logs==[f"    {r['name']} ({r['source']}): wrong {r['name']}" for r in rows]+['Data rows: FAIL 4 of 4']


def test_compiler_failure_waits_for_other_writers_before_raising(monkeypatch,tmp_path):
    rows=[{'source':s,'name':s} for s in ['bad.cpp','slow.cpp']]
    setup(monkeypatch,tmp_path,rows)
    barrier=threading.Barrier(2);finished=threading.Event()
    def verify(row,*args):
        barrier.wait(timeout=5)
        if row['source']=='bad.cpp':raise OSError('compiler failed')
        time.sleep(.03);finished.set();return True,'verified'
    monkeypatch.setattr(data_rows,'verify_row',verify)
    with pytest.raises(OSError,match='compiler failed'):data_rows.verify(compile=True)
    assert finished.is_set()


def test_canonical_source_aliases_share_one_writer_group(monkeypatch,tmp_path):
    (tmp_path/'alias').mkdir()
    rows=[{'source':'unit.cpp','name':'a'},{'source':'alias/../unit.cpp','name':'b'}]
    setup(monkeypatch,tmp_path,rows)
    groups=data_rows._compiled_source_groups(rows,lambda p:p.with_suffix('.obj'))
    assert [[r['name'] for i,r in group] for group in groups]==[['a','b']]


def test_distinct_sources_with_one_provider_object_are_serialized(monkeypatch,tmp_path):
    rows=[{'source':'a.cpp','name':'a'},{'source':'b.cpp','name':'b'}]
    setup(monkeypatch,tmp_path,rows)
    assert len(data_rows._compiled_source_groups(rows,lambda p:tmp_path/'shared.obj'))==1


def test_probe_crc_collision_is_serialized_including_wine_case_rules(monkeypatch,tmp_path):
    import zlib
    rows=[{'source':'left/Unit.cpp','name':'x'},{'source':'right/unit.cpp','name':'y'}]
    setup(monkeypatch,tmp_path,rows)
    monkeypatch.setattr(zlib,'crc32',lambda value:0)
    groups=data_rows._compiled_source_groups(rows,lambda p:p.with_suffix('.obj'))
    assert len(groups)==1 and [i for i,r in groups[0]]==[0,1]


def test_transitive_probe_collisions_share_one_group(monkeypatch,tmp_path):
    import zlib
    rows=[{'source':s,'name':n} for s,n in [('a/unit.cpp','x'),('a/unit.cpp','y'),('b/unit.cpp','x'),('c/unit.cpp','y')]]
    setup(monkeypatch,tmp_path,rows)
    monkeypatch.setattr(zlib,'crc32',lambda value:1 if value.endswith(b'x') else 2)
    assert len(data_rows._compiled_source_groups(rows,lambda p:p.with_suffix('.obj')))==1


def test_compiling_filter_and_success_count_are_unchanged(monkeypatch,tmp_path):
    rows=[{'source':s,'name':s} for s in ('a.cpp','b.cpp','c.cpp')]
    setup(monkeypatch,tmp_path,rows);seen=[]
    monkeypatch.setattr(data_rows,'verify_row',lambda row,*args:(seen.append(row['source']) or True,'valid'))
    assert data_rows.verify(sources=['source:b.cpp'],compile=True,log=lambda text:None)==1
    assert seen==['b.cpp']


def test_casefolded_provider_aliases_register_every_object_output(monkeypatch,tmp_path):
    # Wine-equivalent provider paths may still have distinct encoded objects.
    # A third provider can collide with the second alias's object, so keep
    # every raw source's output in the resource graph, not just its first alias.
    rows=[{'source':s,'name':s} for s in ['a/Unit.cpp','a/unit.cpp','a_unit.cpp']]
    setup(monkeypatch,tmp_path,rows)
    def object_path(source):
        return tmp_path/('upper.obj' if source.name=='Unit.cpp' else 'shared.obj')
    groups=data_rows._compiled_source_groups(rows,object_path)
    assert len(groups)==1 and [i for i,r in groups[0]]==[0,1,2]
