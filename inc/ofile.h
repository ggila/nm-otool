/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ofile.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggilaber <ggilaber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/19 16:24:55 by ggilaber          #+#    #+#             */
/*   Updated: 2016/02/19 19:44:52 by ggilaber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OFILE_H
# define OFILE_H

# include <stdint.h>

/*
** define in /usr/include/mach-o/loader.h
*/

typedef struct	s_mach_header
{
	uint32_t		magic;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		filetype;
	uint32_t		ncmds;
	uint32_t		sizeofcmds;
	uint32_t		flags;
}				t_mach_header;

# define MH_MAGIC 0xfeedface
# define MH_CIGAM 0xcefaedf
# define MH_MAGIC_64 0xfeedfacf
# define MH_CIGAM_64 0xcffaedfe

typedef struct	s_mach_header_64
{
	uint32_t		magic;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		filetype;
	uint32_t		ncmds;
	uint32_t		sizeofcmds;
	uint32_t		flags;
	uint32_t		reserved;
}				t_mach_header_64;

/*
** typedef struct	dylib_module
**   - uint32_t module_name             the module name (index into string table)
** -------
**   - uint32_t iextdefsym;             index into externally defined symbols
**   - uint32_t nextdefsym;             number of externally defined symbols
**   - uint32_t irefsym;                index into reference symbol table
**   - uint32_t nrefsym;                number of reference symbol table entries
**   - uint32_t ilocalsym;              index into symbols for local symbols
**   - uint32_t nlocalsym;              number of local symbols
** -------
**   - uint32_t iextrel;                index into external relocation entries
**   - uint32_t nextrel;                number of external relocation entries
** -------
**   - uint32_t iinit_iterm;            low 16 bits are the index into the init
**                                      section, high 16 bits are the index into
**                                      the term section
**   - uint32_t ninit_nterm;            low 16 bits are the number of init section
**                                      entries, high 16 bits are the number of
**                                      term section entries
** -------
**   - uint32_t objc_module_info_addr;  for this module address of the start of
**                                      the (__OBJC,__module_info) section
**   - uint32_t objc_module_info_size;  for this module size of
**                                       the (__OBJC,__module_info) section
*/

typedef struct	s_dylib_module
{
    uint32_t	module_name;
    uint32_t	iextdefsym;
    uint32_t	nextdefsym;
    uint32_t	irefsym;
    uint32_t	nrefsym;
    uint32_t	ilocalsym;
    uint32_t	nlocalsym;
    uint32_t	iextrel;
    uint32_t	nextrel;
    uint32_t	iinit_iterm;
    uint32_t	ninit_nterm;
    uint32_t	objc_module_info_addr;
    uint32_t	objc_module_info_size;
}				t_dylib_module;

typedef struct	s_dylib_module_64
{
    uint32_t module_name;
    uint32_t iextdefsym;
    uint32_t nextdefsym;
    uint32_t irefsym;
    uint32_t nrefsym;
    uint32_t ilocalsym;
    uint32_t nlocalsym;
    uint32_t iextrel;
    uint32_t nextrel;
    uint32_t iinit_iterm;
    uint32_t ninit_nterm;
    uint32_t objc_module_info_size;
    uint64_t objc_module_info_addr;
}				t_dylib_module_64;

/*
** define in stuff/bytesex.h
*/

enum			e_byte_sex
{
	UNKNOWN_BYTE_SEX,
	BIG_ENDIAN_BYTE_SEX,
	LITTLE_ENDIAN_BYTE_SEX
};

/*
** define in stuff/arch.h
*/

typedef struct	s_arch_flag
{
	char			*name;
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
}				t_arch_flag;

typedef struct	s_fat_header
{
	uint32_t	magic;
	uint32_t	nfat_arch;
}				t_fat_header;

typedef struct	s_fat_arch
{
	cpu_type_t		cputype;
	cpu_subtype_t	cpusubtype;
	uint32_t		offset;
	uint32_t		size;
	uint32_t		align;
}				t_fat_arch;

/*
** define in ar.h
** --
**  ARMAG    :  ar "magic number"
**  SARMAG   :  strlen(ARMAG)
** --
** struct ar_hdr:
** - ar_name :  name
** - ar_date :  modification time
** - ar_uid  :  user id
** - ar_gid  :  group id
** - ar_mode :  octal file permissions
** - ar_size :  size in bytes
** - ar_fmag :  consistency check
*/

# define ARMAG "!<arch>\n"
# define SARMAG 8

typedef struct	s_ar_hdr
{
	char ar_name[16];
	char ar_date[12];
	char ar_uid[6];
	char ar_gid[6];
	char ar_mode[8];
	char ar_size[10];
	char ar_fmag[2];
}				t_ar_hdr;

/*
** define in stuff/ofile.h
*/

enum			e_ofile_type
{
	OFILE_UNKNOWN,
	OFILE_FAT,
	OFILE_ARCHIVE,
	OFILE_MACH_O
};

/*
** struct ofile
**    - char *file_name                       pointer to name malloc'ed by ofile_map
**    - char *file_addr                       pointer to vm_allocate'ed memory
**    - unsigned long file_size               size of vm_allocate'ed memory
**    - enum ofile_type file_type             type of the file
**   ------
**    If a fat file these are filled in and if needed converted to host byte sex:
**    - struct fat_header *fat_header
**    - struct fat_arch *fat_archs
**   -----
**   If this is a fat file then these are valid and filled in
**    - unsigned long narch                   the current architecture
**    - enum ofile_type arch_type             the type of file for this arch
**    - struct arch_flag arch_flag            the arch_flag for this arch,
**   the name field is pointing at space malloc'ed by ofile_map.
**   -----
**    If this structure is currently referencing an archive member or an object
**    file that is an archive member these are valid and filled in:
**    - unsigned long member_offset            logical offset to the member starting
**    - char *member_addr                      pointer to the member contents
**    - unsigned long member_size              actual size of the member (not rounded)
**    - struct ar_hdr *member_ar_hdr           pointer to the ar_hdr for this member
**    - char *member_name                      name of this member
**    - unsigned long member_name_size         size of the member name
**    - enum ofile_type member_type            the type of file for this member
**    if the archive contains objects then these two fields reflect the object
**    at are in the archive.
**    - cpu_type_t archive_cputype             
**    - cpu_subtype_t archive_cpusubtype                             
**   ------
**    If this structure is currently referencing a dynamic library module these are
**    valid and filled in
**    - struct dylib_module *modtab            the 32-bit module table
**    - struct dylib_module_64 *modtab64;      the 64-bit module table
**    - unsigned long nmodtab                  the number of module table entries
**    - struct dylib_module *dylib_module      pointer to the 32-bit dylib_module for this module.
**    - struct dylib_module_64 *dylib_module64 pointer to the 64-bit dylib_module for this module.
**    - char *dylib_module_name                the name of the module
**   ------
**    If this structure is currently referencing an object file these are valid and
**    filled in. The mach_header and load commands have been converted to the host byte
**    sex if needed
**    - char *object_addr                      the address of the object file
**    - unsigned long object_size              the size of the object file
**    - enum byte_sex object_byte_sex          the byte sex of the object file
**    - struct mach_header *mh                 the mach_header of 32-bit object file
**    - struct mach_header_64 *mh64            the mach_header of 64-bit object file
**    - struct load_command *load_commands     the start of the load commands
**    these copied from the mach header above
**    - cpu_type_t mh_cputype                  cpu specifier
**    - cpu_subtype_t mh_cpusubtype            machine specifier
**    - uint32_t mh_filetype                   type of file
*/

typedef struct	s_ofile
{
	char					*file_name;
	char					*file_addr;
	unsigned long			file_size;
	enum e_ofile_type		file_type;
	t_fat_header			*fat_header;
	t_fat_arch				*fat_archs;
	unsigned long			narch;
	enum e_ofile_type		arch_type;
	t_arch_flag				arch_flag;
	unsigned long			member_offset;
	char					*member_addr;
	unsigned long			member_size;
	t_ar_hdr				*member_ar_hdr;
	char					*member_name;
	unsigned long			member_name_size;
	enum e_ofile_type		member_type;
	cpu_type_t				archive_cputype;
	cpu_subtype_t			archive_cpusubtype;
	t_dylib_module			*modtab;
	t_dylib_module_64		*modtab64;
	unsigned long			nmodtab;
	char					*dylib_module_name;
	char					*object_addr;
	unsigned long			object_size;
	enum e_byte_sex			object_byte_sex;
	t_mach_header			*mh;
	t_mach_header_64		*mh64;
	cpu_type_t				mh_cputype;
	cpu_subtype_t			mh_cpusubtype;
	uint32_t				mh_filetype;
}				t_ofile;

#endif
