#ifndef LOGICS_H
#define LOGICS_H

#include "cpu.h"


int add_func(Cpu *, char **);
int mul_func(Cpu *, char **);
int sub_func(Cpu *, char **);
int div_func(Cpu *, char **);

int stor_func(Cpu *, char **);
int load_func(Cpu *, char **);

int push_func(Cpu *, char **);
int pop_func(Cpu *, char **);
#endif