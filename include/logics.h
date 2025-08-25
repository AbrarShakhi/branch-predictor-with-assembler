#ifndef LOGICS_H
#define LOGICS_H

#include "cpu.h"


void add_func(Cpu *cpu, char **operand);
void mul_func(Cpu *cpu, char **operand);
void sub_func(Cpu *cpu, char **operand);
void div_func(Cpu *cpu, char **operand);

void push_func(Cpu *cpu, char **operand);
void pop_func(Cpu *cpu, char **operand);
#endif