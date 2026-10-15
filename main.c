#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

// add -static flag whiler compling.

typedef struct {
    uintptr_t str_p;
    uintptr_t end_p;
    int cap;
} memory_block;

typedef struct {
    uintptr_t point;
    int size;
    uintptr_t next_p;
    uintptr_t prep_p;
} free_memory;


memory_block My_free_memory;

int set_memory_block(	memory_block *mem,
			int cap,
			uintptr_t str,
			uintptr_t end){
	mem->cap = cap;
	mem->str_p = str;
	mem->end_p = end;
	return 0;
}

int add_free_memory_block(free_memory *FMB,
			  uintptr_t point,
			  int size,
			  uintptr_t next_p,
			  uintptr_t prep_p){
    FMB->point = point;
    FMB->size = size;
    FMB->next_p = next_p;
    FMB->prep_p = prep_p;

    return 0;
}

void *my_malloc(int size){
	return NULL;
}

int main(){

	extern memory_block My_free_memory;
    // fiund the corrent last poiter of the program;
	uintptr_t i = (uintptr_t)syscall(SYS_brk, 0);

	int new_size = 0x00F0;
	int new_end = i + new_size;

    uintptr_t o;
    if((o = syscall(SYS_brk, new_end)) ){
	set_memory_block(&My_free_memory, new_size, i, o);
    } else {
        return 0;
    }

    //int index = 0;
    //while(index < 10){
    //    char *p = (char *)(i+index);
    //    printf("place %d : %d[%c]\n", index, p[index], p[index]);
    //    index++;
    //}

    return 0;

}
