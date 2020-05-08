#include <stdio.h>
#include "os.h"

void task1(void) {
  int i = 0;
  for(;;){
    i++;
    os_delay(10);
  }
}

void task2(void) {
  int i = 0;
  for(;;){
    i++;
    yield();
  }
}

void task3(void) {
  int i = 0;
  for(;;){
    i++;
    yield();
  }
}