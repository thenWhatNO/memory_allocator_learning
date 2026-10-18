#include "my_malloc.h"

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

struct Free_Memory_slot {
    long point;
    int size;
    Free_Memory_slot *next_p;
    Free_Memory_slot *prep_p;
};

void* my_malloc(int size_n, int size_type);

int set_free_memory_slot(
                            Free_Memory_slot *FMS, 
                            long point, 
                            int size, 
                            Free_Memory_slot *next_p, 
                            Free_Memory_slot *prep_p
                        )
    {
    FMS->point = point;
    FMS->size = size;
    FMS->next_p = next_p;
    FMS->prep_p = prep_p;
}

Free_Memory_slot *add_new_memory_slot(
                            long point, 
                            int size, 
                            Free_Memory_slot *next_p, 
                            Free_Memory_slot *prep_p
                        )
    {

    long new_slot = syscall(SYS_brk, 0);
    if(syscall(SYS_brk, new_slot + sizeof(Free_Memory_slot) + size) == -1){
		return NULL;
    }

    Free_Memory_slot *FMS = (Free_Memory_slot*)new_slot;
    
    long data_p = new_slot + sizeof(Free_Memory_slot);

	set_free_memory_slot(FMS, data_p, size, NULL, NULL);


}
