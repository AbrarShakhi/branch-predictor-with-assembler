#ifndef BOOL_H
#define BOOL_H

#ifdef __cplusplus
// In C++, these are built-in, no need to define or include anything
#define bool bool
#define true true
#define false false
#else
// Check if stdbool.h has already defined bool
#ifndef __bool_true_false_are_defined
#include <stdbool.h>
// If somehow still not defined (on non-conforming systems), fallback
#else
typedef _Bool bool;
#define true 1
#define false 0
#define __bool_true_false_are_defined 1
#endif

#endif

#endif
