// Header shim: reference/open-bfme-1's WWLib ffactory.h (BFME 1 7e60724c) with ONE
// change -- FileFactoryClass is defined under #pragma optimize("gsy", on), so
// the scalar deleting destructor the compiler generates for it is the size-built
// body retail links (??_GFileFactoryClass@@UAEPAXI@Z, 0x0007827B, 29 bytes,
// `pop ecx` after operator delete).
//
// MSVC 7.1 builds a deleting destructor with the optimization state in force
// where the class's destructor is defined, not where its vtable is first
// needed: an anchor deriving from FileFactoryClass under "gsy" left this
// unit's copy unchanged, while the same pragma around the class definition
// switched it. Retail's ffactory unit is speed-built, so its own copy was the
// 31-byte `add esp,4` body that the link discarded for the /O1 one; this unit
// carries the kept body instead, so it no longer charges a losing COMDAT.
// SimpleFileFactoryClass stays outside the pragma: its deleting destructor
// (0x006131A0) is the speed-built body.
//
// rawfile.h and mutex.h are reached through the include path, as the donor
// header reached them from its own directory: a quoted include here would find
// the WWLib unit's local mutex.h first.
// File-factory declarations for the Generals Zero Hour reference
// (Libraries/Source/WWVegas/WWLib/ffactory.h): the abstract FileFactoryClass, the
// SimpleFileFactoryClass that ffactory.cpp implements (the default read factory), the
// RawFileFactoryClass used for writing, the file_auto_ptr helper, and the global
// factory pointers. SimpleFileFactoryClass embeds a StringClass and a CriticalSectionClass,
// so their layout headers are pulled in here.
#ifndef FFACTORY_H
#define FFACTORY_H

#include <rawfile.h>
#include <mutex.h>

class FileClass;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ffactory.h
#pragma optimize("gsy", on)
class FileFactoryClass {
public:
	virtual ~FileFactoryClass(void){};
	virtual FileClass * Get_File( char const *filename ) = 0;
	virtual void Return_File( FileClass *file ) = 0;
};
#pragma optimize("", on)

//
// Handy auto pointer class.  Prevents you from having to call Return_File manually
//
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ffactory.h
class file_auto_ptr
{
public:
	explicit	file_auto_ptr(FileFactoryClass *fac, const char *filename);
				~file_auto_ptr();

	operator FileClass*(void) const
		{return (get()); }

	FileClass& operator*() const
		{return (*get()); }

	FileClass *operator->() const
		{return (get()); }

	FileClass *get() const
		{return (_Ptr); }

private:
	// prevent these from getting auto-generated or used
						file_auto_ptr(const file_auto_ptr &other);
	file_auto_ptr	&operator=(const file_auto_ptr &other);


	FileClass			*_Ptr;
	FileFactoryClass	*_Fac;
};

/*
** RawFileFactoryClass is a derived FileFactoryClass which
** gives RawFileClass objects
*/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ffactory.h
class	RawFileFactoryClass {
public:
	RawFileClass * Get_File( char const *filename );
	void Return_File( FileClass *file );
};

/*
** SimpleFileFactoryClass is the default read factory: it hands out BufferedFileClass
** objects, honouring an optional (semicolon separated) search path and path stripping.
*/
// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib/ffactory.h
class	SimpleFileFactoryClass : public FileFactoryClass {

public:
	SimpleFileFactoryClass( void );
	~SimpleFileFactoryClass( void )	{}

	virtual FileClass *	Get_File( char const *filename );
	virtual void			Return_File( FileClass *file );

	// sub_directory may be a semicolon seperated search path.  New files will always
	//   go in the last dir in the path.
	void						Get_Sub_Directory( StringClass& new_dir ) const;
	void						Set_Sub_Directory( const char * sub_directory );
	void						Prepend_Sub_Directory( const char * sub_directory );
	void						Append_Sub_Directory( const char * sub_directory );
	bool						Get_Strip_Path( void ) const								{ return IsStripPath; }
	void						Set_Strip_Path( bool set )									{ IsStripPath = set; }
	void						Reset_Sub_Directory( void )								{ SubDirectory = ""; }

protected:
	StringClass				SubDirectory;
	bool						IsStripPath;

	// Mutex must be mutable because const functions lock on it.
	mutable CriticalSectionClass	Mutex;
};

extern FileFactoryClass	*	_TheFileFactory;
extern SimpleFileFactoryClass	*	_TheSimpleFileFactory;
extern RawFileFactoryClass	*	_TheWritingFileFactory;

#endif
