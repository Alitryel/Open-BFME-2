import hashlib,struct
import link_census
def sha(data):
    return hashlib.sha256(data).hexdigest()

def facts(obj):
    data = obj.read_bytes()
    symbols = link_census._coff_symbols(data)
    by_index = {s['index']: s for s in symbols}
    copies = {}
    for symbol, body, relocs, digest, size in link_census._comdat_sections(data):
        copies[symbol['name']] = {
            'bytes_sha256': sha(body), 'size': size, 'digest': digest,
            'relocations': [(offset, kind, ref['name'], ref['value'], ref['storage'])
                            for offset, kind, ref in relocs],
        }
    ordinary = []
    count = struct.unpack_from('<H', data, 2)[0]
    optional = struct.unpack_from('<H', data, 16)[0]
    for number in range(count):
        at = 20 + optional + number * 40
        name = data[at:at+8].rstrip(b'\0').decode('latin-1')
        size, pointer, relocation = struct.unpack_from('<III', data, at+16)
        nrelocs = struct.unpack_from('<H', data, at+32)[0]
        flags = struct.unpack_from('<I', data, at+36)[0]
        if flags & link_census.COMDAT or name.startswith('.debug'):
            continue
        relocs = []
        for r in range(nrelocs):
            offset, target, kind = struct.unpack_from('<IIH', data, relocation+r*10)
            ref = by_index[target]
            relocs.append((offset, kind, ref['name'], ref['value'], ref['storage']))
        body=data[pointer:pointer+size] if pointer else b''
        if name == '.sxdata':
            entries = [by_index[struct.unpack_from('<I', body, off)[0]] for off in range(0,size,4)]
            ordinary.append({'name':name,'size':size,'flags':flags,
              'safeseh_handlers':[(x['name'],x['value'],x['storage']) for x in entries],
              'relocations':relocs})
        else:
            ordinary.append({'name':name,'size':size,'flags':flags,
              'bytes_sha256':sha(body) if pointer else None,'relocations':relocs})
    external = sorted((s['name'], s['value'], s['section'] > 0, s['storage'])
                      for s in symbols if s['storage'] in (2, 105))
    return copies, ordinary, external

def directives(obj):
    data = obj.read_bytes()
    count = struct.unpack_from('<H', data, 2)[0]
    optional = struct.unpack_from('<H', data, 16)[0]
    for n in range(count):
        at = 20 + optional + n * 40
        if data[at:at+8] == b'.drectve':
            size, start = struct.unpack_from('<II', data, at+16)
            return data[start:start+size].decode('latin-1')
    return ''


