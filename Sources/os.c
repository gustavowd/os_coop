#include "os.h"

volatile TCB_t TCB[4];
cpu_t idle_stk[128];

volatile cpu_t ct = 0;
volatile cpu_t it = 0;
volatile long long os_time = 0;

void InstallTask(ptask task, cpu_t *stk, int stk_size){
  stk = (cpu_t*)((int)stk + stk_size - sizeof(cpu_t));
  
  stk = PrepareStack(task, stk);
  
  TCB[it].stk = stk;
  TCB[it].ready = 1;
  it++;
}

cpu_t *scheduler(void){
#if 0
retry:  
  ct++;
  if (ct >= it) ct = 0;
  if (!TCB[ct].ready) goto retry;
  return TCB[ct].stk;
#endif
  do{
    ct++;
    if (ct >= it) ct = 0;    
  }while(!TCB[ct].ready);
  return TCB[ct].stk;
}

void start_os(void){

  init_os_timer();
  stk_tmp = TCB[0].stk;
  
  dispatcher();
}


void os_delay(long long time){
  TCB[ct].timeout = os_time + time;
  TCB[ct].ready = 0;
  yield();  
}