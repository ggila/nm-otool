#include <stdio.h>

#if defined(__LITTLE_ENDIAN__)
 #define ENDIANESS "OSLittleEndian"
#elif defined(__BIG_ENDIAN__)
 #define ENDIANESS "OSBigEndian"
#else
 #define ENDIANESS "OSUnknownByteOrder"
#endif

main() {printf("%s\n", ENDIANESS);}
