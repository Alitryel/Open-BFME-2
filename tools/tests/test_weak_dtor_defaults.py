import struct
import pytest
from test_gate_exploits import TEXT, RDATA, coff, gate

WEAK = '??_EWidget@@UAEPAXI@Z'
DEFAULT = '??_GWidget@@UAEPAXI@Z'
SCALAR = b'\xe8\0\0\0\0\xc3'


def fixture(gate, *, tag=3, characteristic=2, scalar=SCALAR, extent=6,
            opcode=0xe9, addend=0, called=0x2000, scalar_called=0x3000,
            storage=105, aux=1, chars=TEXT, default=DEFAULT, owner_source='Code/x.cpp'):
    # indices: caller 0, weak 1, auxiliary 2, scalar 3, destructor 4
    obj = bytearray(coff(
        [('.text', TEXT, bytes([opcode]) + struct.pack('<i', addend), [(1, 1, 20)]),
         ('.text$g', chars, scalar, [(1, 4, 20)])],
        [('_f', 0, 1, 32, 2, 0), (WEAK, 0, 0, 32, storage, aux),
         (default, 0, 2, 32, 2, 0), ('_dtor', 0, 0, 32, 2, 0)]))
    table = struct.unpack_from('<I', obj, 8)[0]
    if aux:
        struct.pack_into('<II', obj, table + 2 * 18, tag, characteristic)
    gate.obj.write_bytes(obj)
    gate.memory[0x1000] = bytes([opcode]) + struct.pack('<i', called - 0x1005)
    gate.memory[0x2000] = b'\xe8' + struct.pack('<i', scalar_called - 0x2005) + b'\xc3' + b'\xcc' * 32
    gate.row('_f', 0x1000, 5)
    gate.row(DEFAULT, 0x2000, extent, source=owner_source)
    gate.pins.append(('_dtor', '0x3000', 'known destructor'))


def test_real_weak_default_to_same_unit_exact_owner_passes(gate):
    fixture(gate)
    assert gate.gate()


@pytest.mark.parametrize('changes', [
    {'characteristic': 0}, {'characteristic': 1}, {'characteristic': 3},
    {'tag': 1}, {'tag': 2}, {'tag': 99}, {'tag': 4}, {'storage': 2},
    {'scalar': SCALAR + b'\x90'}, {'scalar': b'\xe8\0\0\0\0\x90'},
    {'called': 0x2001}, {'scalar_called': 0x3100},
    {'addend': 1}, {'addend': -1}, {'opcode': 0xb8}, {'opcode': 0xe8},
    {'scalar': b'\xe8\x01\0\0\0\xc3'},
    {'default': '??_GOther@@UAEPAXI@Z'},
    {'owner_source': 'Code/owner.cpp'},
])
def test_invalid_or_unproven_fallback_fails(gate, changes):
    fixture(gate, **changes)
    assert not gate.gate()


def test_unrowed_default_fails(gate):
    fixture(gate)
    gate.rows = gate.rows[:1]
    assert not gate.gate()


def test_real_primary_binding_takes_precedence(gate):
    fixture(gate)
    gate.pins.append((WEAK, '0x4000', 'real vector destructor elsewhere'))
    assert not gate.gate()


def test_alias_owner_cannot_vouch_for_fallback(gate):
    fixture(gate)
    gate.rows[1]['notes'] = 'gen-alias'
    assert not gate.gate()


def test_same_object_strong_primary_wins_over_weak_default(gate):
    fixture(gate)
    data = bytearray(gate.obj.read_bytes())
    table, count = struct.unpack_from('<II', data, 8)
    strong = bytearray(data[table + 18:table + 36])
    struct.pack_into('<h', strong, 12, 2)
    strong[16:18] = bytes([2, 0])
    data[table + count * 18:table + count * 18] = strong
    struct.pack_into('<I', data, 12, count + 1)
    gate.obj.write_bytes(data)
    assert not gate.gate()


def test_data_default_is_not_code(gate):
    fixture(gate, chars=RDATA)
    # Judge the new edge directly: the ordinary owner gate also rejects the
    # false code claim, by SystemExit before its normal summary.
    b = gate.build
    assert not b.proven_weak_dtor_default(gate.rows[0], WEAK, 0x2000, gate.obj,
                                        {DEFAULT: [0x2000], '_dtor': [0x3000]})

