# Archive directory destructor ownership (2026-10-18)

ArchiveFile.cpp implicitly emitted DetailedArchivedDirectoryInfo::~DetailedArchivedDirectoryInfo under its own compiler settings. The current index proves that copy is not retail's body; it was the selected definition and the sole link blocker of AptPlayerDtor.cpp (246 matched bytes). The rowed 68-byte destructor at RVA 0x00224252 already compiles in ArchiveDirInfoO1.cpp. The index lists only these two providers for this name, so removing ArchiveFile's competing definition drains this cause.

ArchiveFile now declares that destructor in a local archive view instead of generating it. The field order, types, inline clear operations and ArchivedFileInfo construction come from the ZH ArchiveFileSystem.h used by this unit (verified BFME 1 pointer 64d369b90170b7e9ec917d646f020b11f13eb0d5). ArchiveDirInfoO1.cpp already uses the same header-guard/local-layout technique. This is donor layout provenance; the target facts are the existing ledger identities, full byte checks and selected-body failure, not an independent new layout claim.

Before and after previews replace the same three current objects together: ArchiveFile.cpp, ArchiveDirInfoO1.cpp and AptPlayerDtor.cpp. They improve from 0 to 246 linked bytes. ArchiveFile retains unrelated AsciiString comparator/allocator/construction blockers; ArchiveDirInfoO1 retains detailed-directory tree/pair COMDAT blockers. No authored C++ coverage grows and no ledger identity changes.

prepare.log records 26/26 normal byte checks and strict reusable receipts for all three explicit providers. The result is a legacy link prediction with self-strict provider evidence, not a closed-strict census or full link result. The census/index/status were not changed.
