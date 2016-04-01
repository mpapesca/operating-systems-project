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
#include "headers/printout.h"
#include "headers/node_operations.h"
#include "headers/prog_operations.h"
#include "headers/scheduler.h"


/* M A I N */

int main(void) {

  start();

  loadconfig();
  printconfig();
  loadresources();
  printresources();
  loadjobfile();
  loadjobs();

  sprintf(print_string,"-----------------------------PRINT %0.4d-----------------------------\n",print_count++);
  printout(log_file,print_string);
  sprintf(print_string,"- JOB LIST\n");
  printout(log_file,print_string);
  printlist(JOBS_LIST);

  sprintf(print_string,"- READY QUEUE\n");
  printout(log_file,print_string);
  printlist(READY_Q);

  sprintf(print_string,"- IO QUEUE\n");
  printout(log_file,print_string);
  printlist(IO_Q);
  sprintf(print_string,"--------------------------------------------------------------------\n\n\n\n");
  printout(log_file,print_string);


  while(1) {
    switch(SCHEDULING) {
      case FCFS:
        OP_FINISHED = longtermscheduler_fcfs(); //Working
        break;
      case SJF:
        OP_FINISHED = longtermscheduler_sjf(); //Not Working
        break;
      case PRIORITY_NPRE:
        OP_FINISHED = longtermscheduler_priority_npre(); //Not Working
        break;
      case PRIORITY_PRE:
        OP_FINISHED = longtermscheduler_priority_pre(); //Not Working
        break;
      case RR
        OP_FINISHED = longtermscheduler_rr(); //Not Working
        break;
    }

    if(OP_FINISHED) {
      break;
    }

    shorttermscheduler();// Add a global flag variable to trigger LTS.

    opcpu();

    opio();

    // cycle();
  }

  stop();

  printdetails();

  return 0;
}
