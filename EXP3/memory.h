#ifndef _MEMORY_H
#define _MEMORY_H
#include <stdio.h>
#include <stdlib.h>

#include "memory.c"
int mode;

void initial();
int first_fit(int id,int size);
int cyclic_first_fit(int id,int size);
int best_fit();
int worst_fit();
void alloc_memory(int (*alloc_func)(int,int));
int free_memory(int mode);
void show_memory();

#endif