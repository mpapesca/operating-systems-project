/* I N C L U D E S */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "headers/defs.h"
#include "headers/global.h"
#include "headers/node_operations.h"


/* M A I N */

int main(void) {

  int32_t i, j, data[10],registers[20], operations[30];
  int8_t c, buff[20];



  // job_t *job_list, *ready_q, *waiting_q, *io_q;
  FILE * job_file;

  system(MOVE_FILE);
  printf("START PROGRAM: ");
  printlist(JOBS_LIST);
  printf("\n");


  while(1) {
    if( (job_file = fopen(FILE_PATH, "r")) != NULL) {
      for(i = 0; i < 4; i++) {
        // fscanf(job_file, "%s %d %s %d %s %d %s %d %s %d", buff, &data[0], buff, &data[1], buff, &data[2], buff, &data[3], buff, &data[4]);
        fscanf(job_file, "%s %d %s %d %s %d %s %d %s", buff, &data[0], buff, &data[1], buff, &data[2], buff, &data[3], buff);

        for( j = 0; j < data[3]; j++) {
          fscanf(job_file, "%d", &registers[j]);
        }

        fscanf(job_file, "%s %d %s", buff, &data[4], buff);

        for( j = 0; j < data[4]; j++) {
          fscanf(job_file, "%d %d", &operations[2*j], &operations[2*j + 1]);
        }

        appendjobtolist(JOBS_LIST, data, JOBS, operations, registers);

      }

      if(remove(FILE_PATH) == -1) {
        printf("ERROR DELETING FILE: %s\n", FILE_PATH);
      }
    } else {
      break;
    }
  }

  printlist(JOBS_LIST);


  // operation_t * operation_head;

  // printlist();
  //
  // appendtolist(5);
  // appendtolist(6);
  // appendtolist(7);
  // appendtolist(8);
  // prependtolist(4);
  // prependtolist(3);
  // prependtolist(2);
  // prependtolist(1);
  // prependtolist(0);
  //
  // printlist();
  //
  // removehead();
  //
  // printlist();
  //
  // removetail();
  //
  // printlist();
  //
  // removenode(4);
  //
  // printlist();
  //
  // removeindex(5);
  //
  // printlist();
  //
  // prependtolist(9);
  //
  // printlist();
  //
  // appendtonode(9,25);
  //
  // printlist();
//
//   operation_t *op;
//   op->next = NULL;
//   op->id = 1;
//   op->duration = 50;
//
//
//
//
//   long i;
//
//   i = op;
//
//   // operation_t * op2 = (operation_t *)i;
//   //
//   // op2 = (operation_t *)i;
//   // // op2 = malloc(sizeof(oper))
//   // op2->duration = 22;
//   //
//   // op2->next = malloc(sizeof(operation_t));
//   // op2->next->id = 999;
//   if(i == NULL){
//   printf("%ld\n",i);
// }
//   else {
//     printf("not null\n");
//   }

  return 0;
}
