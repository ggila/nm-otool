# mach-O format

![Mach-o](img/mach_o_segments.gif)

## header

in /usr/include/mach-o/loader.h

### 32-bit

```
/*
 * The 32-bit mach header appears at the very beginning of the object file for
 * 32-bit architectures.
 */
struct mach_header {
	uint32_t		magic;		/* mach magic number identifier */
	cpu_type_t		cputype;	/* cpu specifier */
	cpu_subtype_t	cpusubtype;	/* machine specifier */
	uint32_t		filetype;	/* type of file */
	uint32_t		ncmds;		/* number of load commands */
	uint32_t		sizeofcmds;	/* the size of all the load commands */
	uint32_t		flags;		/* flags */
};

/* Constant for the magic field of the mach_header (32-bit architectures) */
\#define MH_MAGIC 0xfeedface	/* the mach magic number */
\#define MH_CIGAM 0xcefaedfe	/* NXSwapInt(MH_MAGIC) */
```

### 64-bit

```
/*
 * The 64-bit mach header appears at the very beginning of object files for
 * 64-bit architectures.
 */
struct mach_header_64 {
	uint32_t		magic;		/* mach magic number identifier */
	cpu_type_t		cputype;	/* cpu specifier */
	cpu_subtype_t	cpusubtype;	/* machine specifier */
	uint32_t		filetype;	/* type of file */
	uint32_t		ncmds;		/* number of load commands */
	uint32_t		sizeofcmds;	/* the size of all the load commands */
	uint32_t		flags;		/* flags */
	uint32_t		reserved;	/* reserved */
};

/* Constant for the magic field of the mach_header_64 (64-bit architectures) */
\#define MH_MAGIC_64 0xfeedfacf /* the 64-bit mach magic number */
\#define MH_CIGAM_64 0xcffaedfe /* NXSwapInt(MH_MAGIC_64) */
```

## command

```
/*
 \* The load commands directly follow the mach_header.  The total size of all
 \* of the commands is given by the sizeofcmds field in the mach_header.  All
 \* load commands must have as their first two fields cmd and cmdsize.  The cmd
 \* field is filled in with a constant for that command type.  Each command type
 \* has a structure specifically for it.  The cmdsize field is the size in bytes
 \* of the particular load command structure plus anything that follows it that
 \* is a part of the load command (i.e. section structures, strings, etc.).  To
 \* advance to the next load command the cmdsize can be added to the offset or
 \* pointer of the current load command.  The cmdsize for 32-bit architectures
 \* MUST be a multiple of 4 bytes and for 64-bit architectures MUST be a multiple
 \* of 8 bytes (these are forever the maximum alignment of any load commands).
 \* The padded bytes must be zero.  All tables in the object file must also
 \* follow these rules so the file can be memory mapped.  Otherwise the pointers
 \* to these tables will not work well or at all on some machines.  With all
 \* padding zeroed like objects will compare byte for byte.
 */
struct load_command {
	uint32_t cmd;		/* type of load command */
	uint32_t cmdsize;	/* total size of command in bytes */
};
```

### symtab\_command

# nm

## man nm

### Description

> Nm displays the name list (symbol table) of each object file in the argument list. If an argument is an archive, a listing for each object file in the archive will be produced. File can be of the form libx.a(x.o), in which case only symbols from that member of the object file are listed. (The parentheses have to be quoted to get by the shell.) If no file is given, the symbols in a.out are listed.

> Each symbol name is preceded by its value (blanks if undefined). Unless the -m option is specified, this value is followed by one of the following characters, representing the symbol type: 

> * U (undefined),
* A (absolute),
* T (text section symbol),
* D (data section symbol), 
* B (bsssection symbol),
* C (common symbol), 
* (for debugger symbol table entries; see -a below),
* I S (symbol in a section other than those above),
* I (indirect symbol). 

> If the symbol is local (non-external), the symbol's type is instead represented by the corresponding lowercase letter. A lower case u in a dynamic shared library indicates a undefined reference to a private external in another module in the same
library.

> If the symbol is a Objective C method, the symbol name is +-[Class\_name(category\_name) method:name:], where \`+' is for class methods, \`-' is for instance methods, and (category\_name) is present only when the method is in a category.

### option

> * -a: &nbsp;&nbsp;&nbsp; Display all symbol table entries, including those inserted for use by debuggers.
* -g : &nbsp;&nbsp;&nbsp; Display only global (external) symbols.
* -n : &nbsp;&nbsp;&nbsp; Sort numerically rather than alphabetically.
* -o : &nbsp;&nbsp;&nbsp; Prepend file or archive element name to each output line, rather than only once.
* -p : &nbsp;&nbsp;&nbsp; Don't sort; display in symbol-table order.
* -r : &nbsp;&nbsp;&nbsp; Sort in reverse order.
* -u : &nbsp;&nbsp;&nbsp; Display only undefined symbols.
* -U : &nbsp;&nbsp;&nbsp; Don't display undefined symbols.
* -m : &nbsp;&nbsp;&nbsp; Display the N\_SECT type symbols (Mach-O symbols) as (segment\_name, section\_name) followed by either external or non-external and then the symbol name. Undefined, common, absolute and indirect symbols get displayed as (undefined), (common), (absolute), and (indirect), respectively.
* -x : &nbsp;&nbsp;&nbsp; Display the symbol table entry's fields in hexadecimal, along with the name as a string.
* -j : &nbsp;&nbsp;&nbsp; Just display the symbol names (no value or type).
* -s : &nbsp;&nbsp;&nbsp; ame sectname: List only those symbols in the section (segname,sectname).
* -l : &nbsp;&nbsp;&nbsp; List a pseudo symbol .section\_start if no symbol has as its value the start address of the section. (This is used with the -s option above.)
* -arch arch\_type: &nbsp;&nbsp;&nbsp; Specifies the architecture, arch\_type, of the file for nm(1) to operate on when the file is a universal file (see arch(3) for the currently known arch\_types). The arch\_type can be "all" to operate on all architectures in the file. The default is to display the symbols from only the host architecture, if the file contains it; otherwise, symbols for all architectures in the file are displayed.
* -f : &nbsp;&nbsp;&nbsp; Display the symbol table of a dynamic library flat (as one file not separate modules).
* -A : &nbsp;&nbsp;&nbsp; Write the pathname or library name of an object on each line.
* -P : &nbsp;&nbsp;&nbsp; Write information in a portable output format.
* -t : &nbsp;&nbsp;&nbsp; format: For the -P output, write the numeric value in the specified format. The format shall be dependent on the single character used as the format option-argument:
 * d: The value shall be written in decimal (default).
 * o: The value shall be written in octal.
 * x: The value shall be written in hexadecimal.


## implementation

* map binary:
 * open (get fd)
 * fstat (get size)
 * mmap(0, size, PROT\_READ, MAP\_PRIVATE, fd, 0)
* 
