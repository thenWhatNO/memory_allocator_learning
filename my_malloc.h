#ifndef MY_MALLOC_H
#define MY_MALLOC_H

typedef struct Free_Memory_slot Free_Memory_slot;

void* my_malloc(int size_n, int size_type);

#define ELI_MALLOC(n, type) ((type *)my_malloc(n, sizeof(type)))

long get_FMS_point(Free_Memory_slot *FMS);
int  get_FMS_size(Free_Memory_slot *FMS);
Free_Memory_slot *get_FMS_nextp(Free_Memory_slot *FMS);
Free_Memory_slot *get_FMS_prepp(Free_Memory_slot *FMS);

Free_Memory_slot *get_last_slot(Free_Memory_slot *FMS);
Free_Memory_slot *find_free_FMS(Free_Memory_slot *FMS, int size);

int init_central_FMS();

Free_Memory_slot *alloc_FMS(long str_p, int Dstr_p, int size, int Dsize);

void appand_memory_slot(Free_Memory_slot *cor_FMS, Free_Memory_slot *new_FMS); 
void insert(Free_Memory_slot *cor_FMS, Free_Memory_slot *new_FMS);

#endif