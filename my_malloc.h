#ifndef MY_MALLOC_H
#define MY_MALLOC_H

typedef struct Free_Memory_slot Free_Memory_slot;

void* my_malloc(int size_n, int size_type);

#define ELI_MALLOC(n, type) ((type *)my_malloc(n, sizeof(type)))

int set_free_memory_slot(Free_Memory_slot *FMS, long point, int size, Free_Memory_slot *next_p, Free_Memory_slot *prep_p);
Free_Memory_slot *add_new_memory_slot(long point, int size, Free_Memory_slot* next_p, Free_Memory_slot prep_p);

#endif