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

int jmp_func(Cpu*, char**);
int je_func(Cpu*, char**);
int jne_func(Cpu*, char**);
int jc_func(Cpu*, char**);
int jnc_func(Cpu*, char**);
int jl_func(Cpu*, char**);
int jle_func(Cpu*, char**);
int jg_func(Cpu*, char**);
int jge_func(Cpu*, char**);

#endif