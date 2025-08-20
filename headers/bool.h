#ifndef BOOL_H
#define BOOL_H

#ifdef __cplusplus
// In C++, bool, true, false are built-in keywords, so no definition needed
#define true true
#define false false
#else
// In C, define bool as _Bool, true as 1, false as 0
typedef _Bool bool;
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif
#endif

#endif