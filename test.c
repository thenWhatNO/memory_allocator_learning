#include <stdio.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdint.h>


typedef struct list list;

struct list {
    int value;
    list *next_v;
};

void append(list *ls, int v){
    uintptr_t i = (uintptr_t)syscall(SYS_brk, 0);
    int o;
    if ((o = syscall(SYS_brk, i+10)) < 0) return;

    //printf("%p, ", i);
    list *new_ob = (list*)&i;

    new_ob->value = v;
    new_ob->next_v = NULL;

    ls->next_v = new_ob;
}

int main(){
    list my_list;
    my_list.value = 5;
    my_list.next_v = NULL;

    int i;
    list *mem = &my_list;
    for (i = 0; i < 10; i++){
        
        append(mem, i);
        mem = mem->next_v;
    }

    // mem = NULL;

    // for (mem = &my_list; mem != NULL ; mem = mem->next_v){
    //     printf("%d, ", mem->value);
    // }

    return 1;
}