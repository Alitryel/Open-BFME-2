"""Global rewrites must emit declarations even when prose mentions extern."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_globals

INDEX = {0x00E23300: ['?SharedGlobal@@3HA']}



class TestGlobalDeclarations(unittest.TestCase):
    def test_comment_before_initializer_does_not_supply_declaration(self):
        source = '// The extern spellings above use a different shape.\nstatic int *const p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert 'extern int SharedGlobal;' in rewritten
        assert '(int *)&SharedGlobal' in rewritten


    def test_block_comment_does_not_supply_declaration(self):
        source = '/* extern int SharedGlobal; */\nstatic int *p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert rewritten.startswith('extern int SharedGlobal;\n')


    def test_quoted_declaration_does_not_supply_declaration(self):
        source = 'const char *note = "extern int SharedGlobal;";\nstatic int *p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert rewritten.startswith('extern int SharedGlobal;\n')
        assert '"extern int SharedGlobal;"' in rewritten


    def test_existing_declaration_survives_comment_markers_in_literals(self):
        source = 'const char *note = "https://example.test/*path*/";\nextern int SharedGlobal;\nstatic int *p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert rewritten.count('extern int SharedGlobal;') == 1
        assert '"https://example.test/*path*/"' in rewritten
        assert '(int *)&SharedGlobal' in rewritten


if __name__ == "__main__":
    unittest.main()
