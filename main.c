#include <unistd.h>
#include <sys/syscall.h>
#include <stdio.h>
#include <stdint.h>

// add -static flag while compling.

void *my_malloc(int size_n, int size_t);

#define ELI_MALLOC(n, type) ((type *)my_malloc(n, sizeof(type)))

typedef struct {
    uintptr_t str_p;
    uintptr_t end_p;
    int cap;
} memory_block;

typedef struct {
    uintptr_t point;
    int size;
    free_memory *next_p;
    free_memory *prep_p;
} free_memory;


memory_block My_memory;
free_memory My_free_memory;

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
			  free_memory *next_p,
			  free_memory *prep_p
			)
	{
    FMB->point = point;
    FMB->size = size;
    FMB->next_p = next_p;
    FMB->prep_p = prep_p;

    return 0;
}

void *my_malloc_a(int size_n, int size_type){

	extern free_memory My_free_memory;
	
	int std_sizes[5] = {4, 8, 16, 32, 64};

	int i, ret_size;
	i = 0;
	ret_size = size_n * size_type;
	while(std_sizes[i] < ret_size){
		i++;
		std_sizes[i] = ret_size;
		break;
	}

	void *pointer;
	for(free_memory *mem = &My_free_memory; mem->next_p != NULL; mem = mem->next_p){
		if (mem->size >= ret_size){
			pointer = (void*)mem->point;

			free_memory new_block; 

			uintptr_t i = syscall(SYS_brk, 0);
			uintptr_t o;
			if((o = syscall(SYS_brk, i+ret_size)) > 0){
				add_free_memory_block(&new_block, o, mem->size - ret_size, NULL, mem);
			} else {return NULL;}
			
			mem->next_p = new_block;
			mem->size = 0;

			return pointer;
		}
	}
	
	return NULL;
}

int increace_memory_block(int new_size){
	uintptr_t i = (uintptr_t)syscall(SYS_brk, 0);

	int new_end = i + new_size;

    uintptr_t o;
    if((o = syscall(SYS_brk, new_end)) > 0){
		set_memory_block(&My_memory, new_size, i, o);
		return 0;
    } else {
        return -1;
    }
}

int main(){

	extern memory_block My_memory;
	extern free_memory My_free_memory;

	increace_memory_block(0x0F00);
	printf("cap: %d\nstart: %p\nend: %p\n", My_memory.cap, My_memory.str_p, My_memory.end_p);

	add_free_memory_block(&My_free_memory, My_memory.str_p, My_memory.cap, NULL, NULL);

    return 0;

}
