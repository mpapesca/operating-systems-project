/* I N C L U D E S */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "headers/defs.h"
#include "headers/global.h"
#include "headers/node_operations.h"
#include "headers/prog_operations.h"
#include "headers/scheduler.h"


/* M A I N */

int main(void) {

  start();

  loadjobfile();
  loadjobs();

  fprintf(log_file,"--------------------------------------------------------------------\n");
  fprintf(log_file,"JOB LIST\n");
  printlist(JOBS_LIST);

  fprintf(log_file,"READY QUEUE\n");
  printlist(READY_Q);

  fprintf(log_file,"IO QUEUE\n");
  printlist(IO_Q);
  fprintf(log_file,"--------------------------------------------------------------------\n");

  while(1) {

    if(longtermscheduler()){
      break;
    }

    shorttermscheduler();

    opcpu();

    opio();
  }

  stop();

  printdetails();

  return 0;
}
