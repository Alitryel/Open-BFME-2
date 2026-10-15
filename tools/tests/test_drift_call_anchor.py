import struct
import sys
from pathlib import Path
import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import drift_classify as drift


def fixture(prefix, start, raw_pointer=64):
    section = {'rva': 0x1000, 'raw_pointer': raw_pointer, 'size': 256}
    image = bytearray(b'\xcc' * (raw_pointer + 256))
    body = b'\x90' * prefix + b'\xe8\0\0\0\0\xc3'
    linked = bytearray(body)
    callee = 0x1080
    struct.pack_into('<i', linked, prefix + 1, callee - (start + prefix + 5))
    at = raw_pointer + start - 0x1000
    image[at:at + len(body)] = linked
    image = bytes(image)
    sites = drift.prescan_call_sites(image, section)
    return image, section, body, [(prefix + 1, 20, '_callee')], {'_callee': [callee]}, sites


@pytest.mark.parametrize('prefix,start', [(0, 0x1000), (0, 0x1010), (3, 0x1010), (16, 0x1010)])
def test_rel32_operand_aligns_with_native_operand(prefix, start):
    image, section, body, relocs, symbols, sites = fixture(prefix, start)
    candidates = drift.find_candidates(image, [section], section, body, relocs,
                                      symbols, sites, set(), [], Path('unused.obj'))
    assert candidates[0][1] == start
    assert all(rva != start - 1 for _, rva in candidates)


def test_claimed_body_does_not_leave_a_false_lead_one_byte_before_it():
    start = 0x1010
    image, section, body, relocs, symbols, sites = fixture(3, start)
    candidates = drift.find_candidates(image, [section], section, body, relocs,
                                      symbols, sites, {start}, [(start, start + len(body))],
                                      Path('unused.obj'))
    assert candidates == []
