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
    long end_p = syscall(SYS_brk, 0);
    if(syscall(SYS_brk, end_p + 128) == -1) return -1;
    central_FMS = (Free_Memory_slot*)end_p;

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

    
    // addinf to that pravoase memory slot new slot
    

    // add the new slot to the old one

    return NULL;
}

int std_size(int size){
    int sizes[5] = {8, 16, 32, 64, 128};

    for(int i = 4; i > 0; i--){
        if(sizes[i] < size)return sizes[i];
    }
    return -1;
}

Free_Memory_slot *alloc_FMS(int size, int Dsize){
    extern Free_Memory_slot *central_FMS;
    long end_heap = syscall(SYS_brk, 0);

    // get tru size for the accuall size of the FMS
    int true_size = std_size(size + sizeof(Free_Memory_slot));
    if (true_size == -1){return NULL;}

    // all first check if there a free FMS with enoghe space to hold the new data

    // the min size is a porameter that show how small can i split a free memory slot
    // if there be a split, the new splited slot well have a size of sizeof(FMS) + 8
    // meaning there well be only 8 free space for acuall data
    int min_size = true_size + 8;
    Free_Memory_slot *fms;
    for(fms = central_FMS; fms->next_p != NULL; fms = fms->next_p){
        if (fms->size >= min_size) break;
    }

    long new_p;
    Free_Memory_slot *new_FMS = NULL;

    if (fms->next_p == NULL){
        new_p = end_heap;
        syscall(SYS_brk, end_heap + true_size);
        new_FMS = (Free_Memory_slot*)new_p;
        appand_memory_slot(fms,  new_FMS);
        // the go to to the end of the function
        // i know it not good to use goto,  but i want to try it once!!
        goto ret_data;
    } // i want to tri a go to thing hare!!

    // if the fms is not null, then i nned to split the slot
    // first ill create a new FMS struct at the addres offset of the needed size

    int offset = fms->size - true_size;
    new_p = (long)fms + offset + sizeof(Free_Memory_slot);
    new_FMS = (Free_Memory_slot*)new_p;
    insert_memory_slot(fms, new_FMS);

    fms->size = offset;

    ret_data:

    new_FMS->point = (long)new_FMS + sizeof(Free_Memory_slot);
    new_FMS->size = 0;

    return new_FMS;
}


void appand_memory_slot(Free_Memory_slot *cor_FMS, Free_Memory_slot *new_FMS){
    cor_FMS->next_p = new_FMS;
    new_FMS->prep_p = cor_FMS;

    return;
}

void insert_memory_slot(Free_Memory_slot *cor_FMS, Free_Memory_slot *new_FMS){
    cor_FMS->next_p = new_FMS;
    new_FMS->prep_p = cor_FMS;
    new_FMS->next_p = cor_FMS->next_p;
    new_FMS->next_p->prep_p = new_FMS;

    return;
}