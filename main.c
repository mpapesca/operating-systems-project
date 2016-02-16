/* I N C L U D E S */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include "headers/defs.h"
#include "headers/global.h"
#include "headers/node_operations.h"
#include "headers/scheduler.h"


/* M A I N */

int main(void) {

  loadjobfile();

  loadjobs();
  printf("JOB LIST\n");
  printlist(JOBS_LIST);

  while(1) {

  longtermscheduler();
  //
  // printf("READY QUEUE\n");
  // printlist(READY_Q);

  // printf("IO QUEUE\n");
  // printlist(IO_Q);

  shorttermscheduler();
  //
  }

  return 0;
}
