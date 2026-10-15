#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

// add -static flag whiler compling.

typedef struct {
    uintptr_t srt_p;
    uintptr_t end_p;
    int cap;
} memory_block;

typedef struct {
    uintptr_t point;
    int size;
    uintptr_t next_p;
    uintptr_t prep_p;
} free_memory;


memory_block My;


int add_free_memory_block(free_memory *FMB ,uintptr_t point, int size, uintptr_t next_p, uintptr_t prep_p){
    FMB->point = point;
    FMB->size = size;
    FMB->next_p = next_p;
    FMB->prep_p = prep_p;

    return 0;
}

void *my_malloc(int size){

}

int main(){

    // fiund the corrent last poiter of the program;
    uintptr_t i = (uintptr_t)syscall(SYS_brk, 0);

    memory_block MEM_blk;
    MEM_blk.srt_p = i;
    MEM_blk.cap = 100;

    uintptr_t o;
    if((o = syscall(SYS_brk, i += MEM_blk.cap)) > 0){
        MEM_blk.end_p = o;
    } else {
        return 0;
    }



    int index = 0;
    while(index < 10){
        char *p = (char *)(i+index);
        printf("place %d : %d[%c]\n", index, p[index], p[index]);
        index++;
    }

    return 0;

}