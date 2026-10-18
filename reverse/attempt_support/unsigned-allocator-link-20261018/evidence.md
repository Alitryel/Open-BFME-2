# Shader result lifetime recoveries

Existing natural C++ substring conversion 1520B4 and setup factory 152C47 emit complete 25-byte state-bit result cleanup bodies at 766C19 and 766D2C. Independently EXACT parent EH graphs bind each compiler-local label. The former tail-calls canonical AsciiString destructor48BA39; the latter uses a 16-byte null-guarded reference destructor folded at7B724. Target count+4 and virtual slot0 ownership agree with the existing FXShaderSetup base. The explicit ICF-owner admission verifies the emitted specialization and preserves the existing physical owner; no pin was added.

Both standalone assembly PROC bodies are retired in separate verified commits. The actual C++ sources are unchanged. Net C++ exact increases50 bytes; total exact coverage is unchanged. Their evidence JSON records native bytes, parents, labels and canonical callees. No full-game runtime claim.

The unsigned allocator suppression trial was dropped after concurrent upstream656a9997 fixed that family and established StatsReporter as its fold proof. No incremental allocator linkability gain from that discarded trial is claimed.
