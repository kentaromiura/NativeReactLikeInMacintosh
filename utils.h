#include "types.h"
#include <Dialogs.h>
#include <string.h>

#ifndef UTILS_H
#define UTILS_H

#define toConstStr255Param(var) (ConstStr255Param) &(var)

// Probably better to return a malloc'd struct for performance,
// for now this is fine.
PString toPascal(char * str) {
    PString pStr;
    unsigned char len = strlen(str);
    if (len > 255) len = 255;
    strncpy(pStr.content, str, len);
    pStr.len = len;
    return pStr;
}

#endif