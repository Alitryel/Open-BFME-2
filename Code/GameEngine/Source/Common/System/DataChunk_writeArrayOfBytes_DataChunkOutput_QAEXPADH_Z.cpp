// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/inputs/reference/shims/asciistring_outofline -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source -Ireference/open-bfme-1/game/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Os -Ireference/open-bfme-1/game/GameEngine/Source/Common/System
// stlport
#define Matrix4x4 Matrix4  // BFME renamed it
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

// DataChunk.cpp
// Implementation of Data Chunk save/load system
// Author: Michael S. Booth, October 2000

#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

// ??0OutputChunk@@QAE@XZ present-unmatched
// ??0Mapping@@QAE@XZ present-unmatched

#include "stdlib.h"
#include "string.h"
#include "Compression.h"
// BFME's placement operator delete is one shared 12-byte body that calls the
// CRT free import at 0x009F6C3A directly; ZH's macro routes it through
// ::operator delete, which is a different (and here, wrong) callee.  Scoped to
// the one header that declares this TU's pooled classes.
#pragma push_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#undef MEMORY_POOL_GLUE_WITHOUT_GCMP
extern "C" void free(void *);
#define MEMORY_POOL_GLUE_WITHOUT_GCMP(ARGCLASS) \
friend class DataChunkInput; \
protected: \
	virtual ~ARGCLASS(); \
public: \
	enum ARGCLASS##MagicEnum { ARGCLASS##_GLUE_NOT_IMPLEMENTED = 0 }; \
public: \
	inline void *operator new(size_t s, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return MP_GLUE_ALLOCATE(ARGCLASS); \
	} \
public: \
	inline void operator delete(void *p, ARGCLASS##MagicEnum e DECLARE_LITERALSTRING_ARG2) \
	{ \
		free(p); \
	} \
protected: \
	inline void *operator new(size_t s) \
	{ \
		DEBUG_ASSERTCRASH(s == sizeof(ARGCLASS), ("The wrong operator new is being called; ensure all objects in the hierarchy have MemoryPoolGlue set up correctly")); \
		return ::operator new(s); \
	} \
	inline void operator delete(void *p) \
	{ \
		::operator delete(p); \
	} \
private: \
	virtual MemoryPool *getObjectMemoryPool() \
	{ \
		return ARGCLASS::getClassMemoryPool(); \
	} \
public:
#include "Common/DataChunk.h"
#pragma pop_macro("MEMORY_POOL_GLUE_WITHOUT_GCMP")
#include "Common/File.h"
#include "Common/FileSystem.h"
#include "Common/GameEngine.h"

// UnicodeString is StringBase<WideChar>, and retail inlined its one-line
// forwarders away: the call sites below encode the StringBase<WideChar> bodies
// directly, not the ZH UnicodeString spellings (which resolve to the NARROW
// StringBase<char> bodies).
#include "string_base.h"

// ??0?$StringBase@G@@AAE@ABV0@@Z at 0x00888400 -- private, which is what
// mangles it AAE.  Present-unmatched: this is donor scaffolding for a body at
// a different retail address (0x00888400) that the sweep's own compile command
// needs emitted, not a definition this TU claims.  writeArrayOfBytes below
// does not touch it, and the real UnicodeString copy constructor is claimed at
// 0x00006618 by Code/Libraries/Source/WWVegas/WWLib/unicode_string.cpp.
inline UnicodeString::UnicodeString( const UnicodeString &stringSrc )
{
	((StringBase<WideChar> *)this)->StringBase<WideChar>::StringBase(
		*(const StringBase<WideChar> *)&stringSrc );
}


// ?writeArrayOfBytes@DataChunkOutput@@QAEXPADH@Z
// retail 0x00306D2F, 25 bytes. Dedicated TU ported from the Open-BFME-1 donor
// game/GameEngine/Source/Common/System/DataChunk.cpp (reference/open-bfme-1),
// recompiled /Os: byte-identical to retail once relocations are masked (unique
// masked placement on unclaimed .text). Only the placed body is defined here;
// the donor's other thirty-five definitions are omitted.
//
// IDENTITY IS CARRIED FROM THE DONOR, NOT INDEPENDENTLY ESTABLISHED HERE.
// DataChunkOutput and its writeArrayOfBytes member are named by the retail
// header Common/DataChunk.h, and the body is a plain fwrite of len bytes from
// ptr into m_tmp_file -- the temporary file DataChunkOutput accumulates into
// before it is flushed, per the donor's own note. The call target is the CRT's
// imported fwrite, so the body's identity rests on the header plus the
// signature, not on retail bytes alone.

void DataChunkOutput::writeArrayOfBytes(char *ptr, Int len) 
{ 
	::fwrite( (const char *)ptr, 1, len , m_tmp_file ); 
}
