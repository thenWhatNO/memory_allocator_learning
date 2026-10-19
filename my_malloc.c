#include "my_malloc.h"

#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>

Free_Memory_slot *central_FMS;

struct Free_Memory_slot {
    long point;
    int size;
    Free_Memory_slot *next_p;
    Free_Memory_slot *prep_p;
};

long get_FMS_point(Free_Memory_slot *FMS){return FMS->point;}
int  get_FMS_size(Free_Memory_slot *FMS){return FMS->size;}
Free_Memory_slot *get_FMS_nextp(Free_Memory_slot *FMS){return FMS->next_p;}
Free_Memory_slot *get_FMS_prepp(Free_Memory_slot *FMS){return FMS->prep_p;}

int init_central_FMS(){
    extern Free_Memory_slot *central_FMS;
    central_FMS = add_new_memory_slot(0, NULL, NULL);

    if(central_FMS == NULL)return -1;
    return 0;
}

Free_Memory_slot *get_last_slot(Free_Memory_slot *FMS){
    extern Free_Memory_slot *central_FMS;
    for(Free_Memory_slot *mem = central_FMS; mem != NULL; mem = mem->next_p){
        if(mem->next_p == NULL) return mem;
    }

    return NULL;
}

void* my_malloc(int size_n, int size_type){
    extern Free_Memory_slot *central_FMS;
    // prevease memory slot
    
    // addinf to that pravoase memory slot new slot
    add_new_memory_slot(size_n + size_type, NULL, NULL);

    // add the new slot to the old one

    
}

Free_Memory_slot *add_new_memory_slot(
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

    return (Free_Memory_slot*)new_slot;
}
