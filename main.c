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
#include "headers/prog_operations.h"
#include "headers/scheduler.h"


/* M A I N */

int main(void) {

  loadjobfile();
  loadjobs();

  printf("--------------------------------------------------------------------\n");
  printf("JOB LIST\n");
  printlist(JOBS_LIST);

  printf("READY QUEUE\n");
  printlist(READY_Q);

  printf("IO QUEUE\n");
  printlist(IO_Q);
  printf("--------------------------------------------------------------------\n");

  while(1) {
    // printf("main1\n");
    longtermscheduler();

    // printf("main2\n");
    shorttermscheduler();

    // printf("main3\n");
    opcpu();

    // printf("main4\n");
    opio();
  }

  return 0;
}
