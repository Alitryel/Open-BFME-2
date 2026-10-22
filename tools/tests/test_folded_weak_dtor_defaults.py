import struct
import pytest
from test_gate_exploits import TEXT, coff, gate

WEAK = '??_EWidget@@UAEPAXI@Z'
DEFAULT = '??_GWidget@@UAEPAXI@Z'
PEER = '??_GOriginal@@UAEPAXI@Z'
BODY = bytes.fromhex('568bf1e800000000f644240801740756e800000000598bc65ec20400')


def folded_fixture(gate, *, owner_source='Code/x.cpp', missing_definition=False,
                   peer_notes='', peer_size=28, own_addend=0, wrong_peer=False,
                   characteristic=2, malformed_target=False, chained=False):
    own = bytearray(BODY)
    struct.pack_into('<i', own, 4, own_addend)
    peer = bytearray(BODY)
    if wrong_peer:
        peer[0] = 0x57
    symbols = [('_f', 0, 1, 32, 2, 0), (WEAK, 0, 0, 32, 105, 1),
               (DEFAULT, 0, 0 if missing_definition else 2, 32, 2, 0),
               (PEER, 0, 3, 32, 2, 0), ('_dtor', 0, 0, 32, 2, 0),
               ('_delete', 0, 0, 32, 2, 0)]
    raw = bytearray(coff(
        [('.text', TEXT, bytes.fromhex('83e918e900000000'), [(4, 1, 20)]),
         ('.text$g', TEXT, bytes(own), [(4, 5, 20), (16, 6, 20)]),
         ('.text$p', TEXT, bytes(peer), [(4, 5, 20), (16, 6, 20)])], symbols))
    table = struct.unpack_from('<I', raw, 8)[0]
    struct.pack_into('<II', raw, table + 2 * 18, 1 if chained else 3, characteristic)
    gate.obj.write_bytes(raw)
    gate.memory[0x1000] = bytes.fromhex('83e918e9') + struct.pack('<i', (0x2001 if malformed_target else 0x2000) - 0x1008)
    native = bytearray(BODY)
    struct.pack_into('<i', native, 4, 0x3000 - 0x2008)
    struct.pack_into('<i', native, 16, 0x4000 - 0x2014)
    gate.memory[0x2000] = bytes(native) + b'\xcc' * 32
    gate.row('_f', 0x1000, 8)
    gate.row(DEFAULT, 0x2000, 28, notes='gen-alias', source=owner_source)
    gate.row(PEER, 0x2000, peer_size, notes=peer_notes, source='Code/canonical.cpp')
    gate.pins += [('_dtor', '0x3000', 'proven dtor'), ('_delete', '0x4000', 'proven delete')]


def test_same_unit_strict_scalar_fold_uses_local_weak_default(gate):
    folded_fixture(gate)
    assert gate.gate()
    # This proves the object-local edge without installing a global E pin.
    assert WEAK not in gate.build.load_symbol_map()


@pytest.mark.parametrize('changes', [
    {'owner_source': 'Code/elsewhere.cpp'},
    {'missing_definition': True},
    {'peer_notes': 'gen-alias'},
    {'peer_notes': 'object-symbol=??_GWrong@@UAEPAXI@Z'},
    {'peer_notes': 'gen-dump'},
    {'peer_size': 27},
    {'own_addend': 1},
    {'wrong_peer': True},
    {'characteristic': 1},
    {'characteristic': 3},
    {'malformed_target': True},
    {'chained': True},
])
def test_unproven_folded_weak_default_remains_rejected(gate, changes):
    folded_fixture(gate, **changes)
    assert not gate.gate()


def test_fold_with_no_canonical_scalar_owner_still_fails(gate):
    folded_fixture(gate)
    gate.rows = gate.rows[:2]
    assert not gate.gate()


def test_fold_does_not_ignore_strong_e_binding(gate):
    folded_fixture(gate)
    gate.pins.append((WEAK, '0x5000', 'real competing E'))
    assert not gate.gate()


def test_fold_does_not_borrow_masked_wrong_callee(gate):
    folded_fixture(gate)
    gate.pins = [('_dtor', '0x3100', 'wrong destructor'), ('_delete', '0x4000', 'delete')]
    assert not gate.gate()
