#include "os.h"

cpu_t *stk_tmp;

cpu_t *PrepareStack(void *task, cpu_t *stk){
  *stk-- = (cpu_t)((int)task & 0xFF);
  *stk-- = (cpu_t)((int)task >> 8);
  *stk-- = 0;
  *stk-- = 0;
  *stk-- = 0;
  *stk = 0;
  return stk;
}


interrupt void SwitchContext(void){

  SAVE_SP();
  
  TCB[ct].stk=stk_tmp;
  stk_tmp = scheduler();
  
  RESTORE_SP();    
}


void init_os_timer(void){
  TPM1SC = 0x00;
  TPM1MOD = 19999;
  TPM1SC = 0x48;
}  


interrupt void os_timer(void){
   int i = 0;
   TPM1SC_TOF = 0;
   os_time++;
   
   for(i = 0;i<it;i++){
    if (TCB[i].timeout == os_time) TCB[i].ready = 1;
   }
}