#include<stdio.h>

#define SLAB_SIZE 4096
#define MAX_SLAB 128

unsigned char* slab_pool[MAX_SLAB][SLAB_SIZE]
void* pslab_list[MAX_SLAB]
unsigned int next_free_slab;

void slab_pool_init(){
  unsigned int i;
  for(i = 0; i<MAX_SLAB ; i++){
    pslab_list[i] = (void*)&slab_pool[i][0];
  }
  next_free_slab = 0;
}

void* slab_alloc_4k(){
  void* pmem = pslab_ist[next_free_slab];
  next_free_slab++;
  next_free_slab &= (MAX_SLABS-1);
  return pmem;
}

void slab_free(void* pmem){
  next_free_slab--;
  if(next_free_slab<0)
    next_free_slab = 0;
  pslab_list[next_free_slab] = pmem; 
}
