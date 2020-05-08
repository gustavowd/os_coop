#include "port.h"

typedef void (*ptask)(void);

typedef struct _TCB{
  cpu_t *stk;
  cpu_t ready;
  long long timeout;
}TCB_t;

extern volatile TCB_t TCB[4];
extern volatile cpu_t ct;
extern volatile cpu_t it;
extern volatile long long os_time;

void InstallTask(ptask task, cpu_t *stk, int stk_size);
void start_os(void);
cpu_t *scheduler(void);
void os_delay(long long time);
