#ifndef __LIBRARIAN_PRIVATE_H_
#define __LIBRARIAN_PRIVATE_H_
#include <stdint.h>
#include "khash.h"

typedef struct onesymbol_s {
    uintptr_t   offs;
    uint32_t    sz;
    // need to track type of symbol?
    // need to track origin?
} onesymbol_t;

typedef struct {
    char        *name;
    library_t   *lib;
} onelib_t;

KHASH_MAP_DECLARE_STR(mapsymbols, onesymbol_t)

typedef struct lib_s {
    khash_t(mapsymbols)   *mapsymbols;
    onelib_t              *libraries;
    int                   libsz;
    int                   libcap;
    
    bridge_t                *bridge;        // all x86 -> arm bridge
} lib_t;

#endif //__LIBRARIAN_PRIVATE_H_