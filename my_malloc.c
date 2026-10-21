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

Free_Memory_slot *find_free_FMS(Free_Memory_slot *FMS, int size){
    extern Free_Memory_slot *central_FMS;
    for(Free_Memory_slot *mem = central_FMS; mem != NULL; mem = mem->next_p){
        if (mem->size >= size + sizeof(Free_Memory_slot) + 8) return mem;
    }
    return NULL;
}

void* my_malloc(int size_n, int size_type){
    extern Free_Memory_slot *central_FMS;
    int total_size = size_n + size_type;

    Free_Memory_slot *corr_FMS;

    // need to make sure the new slot have enough free space for the data and the hader
    if ((corr_FMS = find_free_FMS(central_FMS, total_size)) == NULL){
        corr_FMS = get_last_slot(central_FMS);
        add_new_memory_slot(size_n + size_type, NULL, NULL);
    } else {
        int new_slot_size = total_size + sizeof(Free_Memory_slot);
        if (corr_FMS->size == total_size){
            
        }
        else {
            Free_Memory_slot *new_slot = add_new_memory_slot(total_size, corr_FMS->next_p, corr_FMS)
            corr_FMS->next_p = new_slot;
            corr_FMS->size =- total_size;
        }
    }
    
    // addinf to that pravoase memory slot new slot
    

    // add the new slot to the old one

    
}

Free_Memory_slot *alloc_FMS(long str_p, int Dstr_p, int size, int Dsize){
    
}


void appand_memory_slot(Free_Memory_slot *cor_FMS, Free_Memory_slot *new_FMS){
    cor_FMS->next_p = new_FMS;
    new_FMS->prep_p = cor_FMS;

    return;
}

void insert(Free_Memory_slot *cor_FMS, Free_Memory_slot *new_FMS){
    cor_FMS->next_p = new_FMS;
    new_FMS->prep_p = cor_FMS;
    new_FMS->next_p = cor_FMS->next_p;
    new_FMS->next_p->prep_p = new_FMS;

    return;
}