// /* I N C L U D E S */
//
// #include <stdio.h>
// #include <stdlib.h>
// #include <stdbool.h>
// #include <stdint.h>







/* F U N C T I O N S */

void loadjobfile(void) {
  system(MOVE_JOB_FILE);
  sprintf(print_string,"START PROGRAM:\n\n");
  printout(log_file,print_string);
}


void loadconfig(void) {

  char buff[25];

  config_file = fopen(CONFIG_FILE,"r");

  fscanf(config_file,"%s %ld", buff, &MAIN_MEMORY);
  fscanf(config_file,"%s %d", buff, &RESOURCE_TYPES);
  fscanf(config_file,"%s %d", buff, &TIME_QUANTUM);
  fscanf(config_file,"%s %d", buff, &SCHEDULING);
  fscanf(config_file,"%s %d", buff, &PREEMPTIVE);

  fclose(config_file);

}

void printconfig(void) {
  sprintf(print_string,"\nCONFIG\n\n");
  printout(log_file,print_string);
  sprintf(print_string,"MAIN MEMORY: %ld\n",MAIN_MEMORY);
  printout(log_file,print_string);
  sprintf(print_string,"RESOURCE TYPES: %d\n",RESOURCE_TYPES);
  printout(log_file,print_string);
  sprintf(print_string,"TIME QUANTUM: %d\n",TIME_QUANTUM);
  printout(log_file,print_string);
  sprintf(print_string,"SCHEDULING: %d\n",SCHEDULING);
  printout(log_file,print_string);
  sprintf(print_string,"PREEMPTIVE: %s\n", (PREEMPTIVE? "TRUE" : "FALSE") );
  printout(log_file,print_string);

}


void loadresources(void) {
  char buff[25];
  resource_file = fopen(RESOURCE_FILE,"r");
  sysres_current = SYSTEM_RESOURCES;
  for(i = 0; i < RESOURCE_TYPES; i++) {
    if(SYSTEM_RESOURCES == NULL) {
      SYSTEM_RESOURCES = malloc(sizeof(system_resource_t));
      fscanf(resource_file,"%d %s %d", &SYSTEM_RESOURCES->type, buff, &SYSTEM_RESOURCES->count);
      SYSTEM_RESOURCES->instances = NULL;

      inst_current = SYSTEM_RESOURCES->instances;
      for(j = 0; j < SYSTEM_RESOURCES->count; j++) {
        if(inst_current == NULL) {
          SYSTEM_RESOURCES->instances = malloc(sizeof(resource_instance_t));
          SYSTEM_RESOURCES->instances->id = j;
          SYSTEM_RESOURCES->instances->status = FREE;
          SYSTEM_RESOURCES->instances->next = NULL;
          inst_current = SYSTEM_RESOURCES->instances;
        } else {
          while(inst_current->next != NULL) {
            inst_current = inst_current->next;
          }
          inst_current->next = malloc(sizeof(resource_instance_t));
          inst_current->next->id = j;
          inst_current->next->status = FREE;
          inst_current->next->next = NULL;
        }
      }

      SYSTEM_RESOURCES->next = NULL;
      sysres_current = SYSTEM_RESOURCES;
    } else {
      while(sysres_current->next != NULL) {
        sysres_current = sysres_current->next;
      }


      sysres_current->next = malloc(sizeof(system_resource_t));
      fscanf(resource_file,"%d %s %d", &sysres_current->next->type, buff, &sysres_current->next->count);
      sysres_current->next->instances = NULL;

      inst_current = sysres_current->next->instances;
      for(j = 0; j < sysres_current->next->count; j++) {
        if(inst_current == NULL) {
          sysres_current->next->instances = malloc(sizeof(resource_instance_t));
          sysres_current->next->instances->id = j;
          sysres_current->next->instances->status = FREE;
          sysres_current->next->instances->next = NULL;
          inst_current = sysres_current->next->instances;
        } else {
          while(inst_current->next != NULL) {
            inst_current = inst_current->next;
          }
          inst_current->next = malloc(sizeof(resource_instance_t));
          inst_current->next->id = j;
          inst_current->next->status = FREE;
          inst_current->next->next = NULL;
        }
      }

      sysres_current->next->next = NULL;
    }

  }

}

void printresources(void) {
  sprintf(print_string,"\nRESOURCES\n\n");
  printout(log_file,print_string);
  sysres_current = SYSTEM_RESOURCES;

  while(sysres_current != NULL) {
    sprintf(print_string,"RESOURCE: %d\n", sysres_current->type);
    printout(log_file, print_string);
    sprintf(print_string,"COUNT: %d\n", sysres_current->count);
    printout(log_file, print_string);


    inst_current = sysres_current->instances;
    while(inst_current != NULL){
      sprintf(print_string,"\tINSTANCE: %d\n", inst_current->id);
      printout(log_file, print_string);
      sprintf(print_string,"\tSTATUS: %s\n", !inst_current->status? "FREE" : "CLAIMED");
      printout(log_file, print_string);
      inst_current = inst_current->next;
    }

    sysres_current = sysres_current->next;
  }
}

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createjoblist(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createjoblist(int *data) {
//
//   JOBS_LIST = malloc(sizeof(job_t));
//
//   job_t * head = JOBS_LIST;
//
//   head->id = data[0];
//   head->process_state = WAITING;
//   head->prog_count = 0;
//   head->total_mem = data[1];
//   head->min_mem = data[2];
//
//   head->next = NULL;
//
//   return;
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createjoblist(void)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void createjoblist(int *data, int *ops, int *regs, int *resources) {


  JOBS_LIST = malloc(sizeof(job_t));
  JOBS_LIST->id = data[0];
  JOBS_LIST->arrival_time = data[1];
  JOBS_LIST->priority = data[2];
  JOBS_LIST->process_state = WAITING;
  JOBS_LIST->prog_count = 0;
  JOBS_LIST->total_mem = data[3];
  JOBS_LIST->min_mem = data[4];
  JOBS_LIST->num_regs = data[5];
  JOBS_LIST->num_ops = data[6];
  JOBS_LIST->num_resources = data[7];

  gettimeofday(&JOBS_LIST->start_wait, NULL);


  for(i = 0; i < data[5]; i++) {
    if(JOBS_LIST->registers == NULL) {
      JOBS_LIST->registers = malloc(sizeof(reg_t));
      JOBS_LIST->registers->id = regs[i];
      JOBS_LIST->registers->next = NULL;
    } else {
      reg_current = JOBS_LIST->registers;
      while(reg_current->next != NULL) {
        reg_current = reg_current->next;
      }
      reg_current->next = malloc(sizeof(reg_t));
      reg_current->next->id = regs[i];
      reg_current->next->next = NULL;
    }
  }

  for(i = 0; i < data[6]; i++) {
    if(JOBS_LIST->operations == NULL) {
      JOBS_LIST->operations = malloc(sizeof(operation_t));
      JOBS_LIST->operations->id = i;
      JOBS_LIST->operations->type = ops[2*i];
      JOBS_LIST->operations->duration = ops[2*i + 1];
      JOBS_LIST->operations->next = NULL;
    } else {
      op_current = JOBS_LIST->operations;
      while(op_current->next != NULL) {
        op_current = op_current->next;
      }
      op_current->status = 0;
      op_current->next = malloc(sizeof(operation_t));
      op_current->next->id = i;
      op_current->next->type = ops[2*i];
      op_current->next->duration = ops[2*i + 1];
      op_current->next->next = NULL;
    }
  }

  for(i = 0; i < data[7]; i++) {
    if(JOBS_LIST->resources == NULL) {
      JOBS_LIST->resources = malloc(sizeof(resource_t));
      JOBS_LIST->resources->id = i;
      JOBS_LIST->resources->type = resources[i];
      JOBS_LIST->resources->status = FREE;
      JOBS_LIST->resources->next = NULL;
    } else {
      resource_current = JOBS_LIST->resources;
      while(resource_current->next != NULL) {
        resource_current = resource_current->next;
      }
      resource_current->next = malloc(sizeof(resource_t));
      resource_current->next->id = i;
      resource_current->next->type = resources[i];
      resource_current->next->status = FREE;
      resource_current->next->next = NULL;
    }
  }

  JOBS_LIST->next = NULL;


}


/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createreadyq(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createreadyq(void) {
//
//   head = malloc(sizeof(job_t));
//   head->id = id;
//   head->next = NULL;
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createwaitq(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createwaitq(void) {
//
//   head = malloc(sizeof(job_t));
//   head->id = id;
//   head->next = NULL;
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  createioq(int)

  DISC:     This function is meant to create a new list starting from the
            head node.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void createioq(void) {
//
//   head = malloc(sizeof(job_t));
//   head->id = id;
//   head->next = NULL;
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  listempty()

  DISC:     This function determines if the linked list is empty or not.

  ARGS:     None.

  RETURN:   Return bool true if the linked list is empty and false if the
            linked list is not empty.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// bool listempty(void) {
//
//   if(head == NULL) {
//     return true;
//   } else {
//     return false;
//   }
//
// }

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  appendjobtolist(job_t * head, int *data, int list)

  DISC:     This function is meant to append a new node to the list to be
            the new tail of the linked list.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void appendjobtolist(job_t * head, int *data, int list, int *ops, int *regs, int *resources) {
  // printout(log_file,"/t/t/t/t/t/t*************appendjobtolist()***************\n");

  current = head;
  // sprintf(print_string,"** H E R E 1 **\n");
  // printout(log_file,print_string);
  if(head == NULL) {
    createjoblist(data, ops, regs, resources);
    // sprintf(print_string,"** H E R E 0 **\n");
    // printout(log_file,print_string);
    return;
  }


  while(current->next != NULL) {
    current = current->next;
  }
  current->next = malloc(sizeof(job_t));
  current->next->id = data[0];
  current->next->process_state = WAITING;
  current->next->prog_count = 0;
  current->next->arrival_time = data[1];
  current->next->priority = data[2];
  current->next->total_mem = data[3];
  current->next->min_mem = data[4];
  current->next->num_regs = data[5];
  current->next->num_ops = data[6];
  current->next->num_resources = data[7];

  gettimeofday(&current->start_wait, NULL);
  current->checking_wait = 1;

  for(i = 0; i < data[5]; i++) {
    if(current->next->registers == NULL) {
      current->next->registers = malloc(sizeof(reg_t));
      current->next->registers->id = regs[i];
      current->next->registers->next = NULL;
    } else {
      reg_current = current->next->registers;
      while(reg_current->next != NULL) {
        reg_current = reg_current->next;
      }
      reg_current->next = malloc(sizeof(reg_t));
      reg_current->next->id = regs[i];
      reg_current->next->next = NULL;
    }
  }

  for(i = 0; i < data[6]; i++) {
    if(current->next->operations == NULL) {
      current->next->operations = malloc(sizeof(operation_t));
      current->next->operations->id = i;
      current->next->operations->type = ops[2*i];
      current->next->operations->duration = ops[2*i + 1];
      current->next->operations->next = NULL;
    } else {
      op_current = current->next->operations;
      while(op_current->next != NULL) {
        op_current = op_current->next;
      }
      op_current->next = malloc(sizeof(operation_t));
      op_current->next->id = i;
      op_current->next->type = ops[2*i];
      op_current->next->duration = ops[2*i + 1];
      op_current->next->next = NULL;
    }
  }

  for(i = 0; i < data[7]; i++) {
    if(current->next->resources == NULL) {
      current->next->resources = malloc(sizeof(operation_t));
      current->next->resources->id = i;
      current->next->resources->type = resources[i];
      current->next->resources->status = FREE;
      current->next->resources->next = NULL;
    } else {
      resource_current = current->next->resources;
      while(resource_current->next != NULL) {
        resource_current = resource_current->next;
      }
      resource_current->next = malloc(sizeof(operation_t));
      resource_current->next->id = i;
      resource_current->next->type = resources[i];
      resource_current->next->status = FREE;
      resource_current->next->next = NULL;
    }
  }

  current->next->next = NULL;


}

void loadjobs(void) {

  int32_t i, j, data[10],registers[20], operations[30], resources[20];
  int8_t c, buff[20];

  while(1) {
    if( (job_file = fopen(JOB_FILE, "r")) != NULL) {
      for(i = 0; i < 6; i++) {
        // fscanf(job_file, "%s %d %s %d %s %d %s %d %s %d", buff, &data[0], buff, &data[1], buff, &data[2], buff, &data[3], buff, &data[4]);
        fscanf(job_file, "%s %d %s %d %s %d %s %d %s %d %s %d %s", buff, &data[0], buff, &data[1], buff, &data[2], buff, &data[3], buff, &data[4], buff, &data[5], buff);
        for( j = 0; j < data[5]; j++) {
          fscanf(job_file, "%d", &registers[j]);
        }

        fscanf(job_file, "%s %d %s", buff, &data[6], buff);

        for( j = 0; j < data[6]; j++) {
          fscanf(job_file, "%d %d", &operations[2*j], &operations[2*j + 1]);
        }

        fscanf(job_file, "%s %d %s", buff, &data[7], buff);

        for( j = 0; j < data[7]; j++) {
          fscanf(job_file, "%d", &resources[j]);
        }

        appendjobtolist(JOBS_LIST, data, JOBS, operations, registers, resources);

      }

      if(remove(JOB_FILE) == -1) {
        sprintf(print_string,"ERROR DELETING FILE: %s\n", JOB_FILE);
        printout(log_file,print_string);

      }
    } else {
      break;
    }
  }
}
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  appendjobtolist(job_t * head, int *data, int list)
//
//   DISC:     This function is meant to append a new node to the list to be
//             the new tail of the linked list.
//
//   ARGS:     int id - The id value of the new node.
//
//   RETURN:   None.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// void appendoptolist(job_t * head, int count int *data) {
//
//   job_t * current = head;
//
//   if(current == NULL) {
//
//     createjoblist(data);
//     return;
//   } else {
//
//     while(current->next != NULL) {
//       current = current->next;
//     }
//
//     current->next = malloc(sizeof(job_t));
//     current->next->id = data[0];
//     current->next->process_state = 0;
//     current->next->prog_count = 0;
//     current->next->total_mem = data[1];
//     current->next->min_mem = data[2];
//
//     current->next->next = NULL;
//   }
// }


/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  prependtolist(int)

  DISC:     This function is meant to prepend a new node to the list to be
            the new head of the linked list.

  ARGS:     int id - The id value of the new node.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// void prependtolist(int id) {
//
//   if(listempty()) {
//     createlist(id);
//     return;
//   }
//
//   job_t * new_node = malloc(sizeof(job_t));
//
//   new_node->id = id;
//   new_node->next = head;
//   head = new_node;
//
// }
//
/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  appendtonode(int, int)

  DISC:     This function is meant to insert a node after the node of the
            specified index.

  ARGS:     int search_id - The id value of the node that a new node will be
            inserted after.

            int id - The id of the new node.

  RETURN:   Return 1 for success and return 0 for failure.

 * * * * * * * * * * * * * * * * * * * * * * * * */
// int appendtonode(int search_id, int id) {
//
//   if(listempty()) {
//     return 0;
//   }
//
//   job_t * new_node = malloc(sizeof(job_t));
//   new_node->id = id;
//
//   current = JOBS;
//   while(current->id != search_id) {
//     if(current->next == NULL) {
//       return 0;
//     }
//     current = current->next;
//   }
//
//   if(JOBS->id == id) {
//     new_node->next = JOBS->next;
//     JOBS->next = new_node;
//   }else{
//     new_node->next = current->next;
//     current->next = new_node;
//   }
//
//   return 1;
// }


/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  prependtonode(int, int)

  DISC:     This function is meant to insert a node after the node of the
            specified index.

  ARGS:     int search_id - The id value of the node that a new node will be
            inserted after.

            int id - The id of the new node.

  RETURN:   Return 1 for success and return 0 for failure.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void prependjobcopytonode(int list, job_t * original, bool priority_check) {

  bool node_found = false;
  bool new_list = 0;

  job_t * new_node = malloc(sizeof(job_t));
  job_t * local_current = malloc(sizeof(job_t));
  operation_t * orig_op_current;
  resource_t * orig_resource_current;
  reg_t * orig_reg_current;

  switch(list) {
    case JOBS:
      if(JOBS_LIST == NULL) {
        JOBS_LIST = malloc(sizeof(job_t));
        new_list = 1;
      }
      local_current = JOBS_LIST;
      break;

    case READY:
      if(READY_Q == NULL) {
        READY_Q = malloc(sizeof(job_t));
        new_list = 1;
      }
      local_current = READY_Q;
      break;

    case IO:
      if(IO_Q == NULL) {
        IO_Q = malloc(sizeof(job_t));
        new_list = 1;
      }
      local_current = IO_Q;
      break;
  }

  // current = destination;
//This may cause a segfault....

  if(new_list) {
    local_current->id = original->id;
    local_current->process_state = original->process_state;
    local_current->prog_count = original->prog_count;
    local_current->total_mem = original->total_mem;
    local_current->min_mem = original->min_mem;
    local_current->num_regs = original->num_regs;
    local_current->num_ops = original->num_ops;
    local_current->num_resources = original->num_resources;


    gettimeofday(&local_current->start_wait, NULL);
    local_current->checking_wait = 1;

    for(i = 0; i < local_current->num_regs; i++) {
      if(local_current->registers == NULL) {
        local_current->registers = malloc(sizeof(reg_t));
        local_current->registers->id = original->registers->id;
        local_current->registers->next = NULL;
      } else {
        reg_current = local_current->registers;
        orig_reg_current = original->registers;
        while(reg_current->next != NULL) {
          reg_current = reg_current->next;
          orig_reg_current = orig_reg_current->next;

        }
        reg_current->next = malloc(sizeof(reg_t));
        reg_current->next->id = orig_reg_current->id;
        reg_current->next->next = NULL;
      }
    }

    for(i = 0; i < local_current->num_ops; i++) {
      if(local_current->operations == NULL) {
        local_current->operations = malloc(sizeof(operation_t));
        local_current->operations->id = original->operations->id;
        local_current->operations->type = original->operations->type;
        local_current->operations->duration = original->operations->duration;
        local_current->operations->next = NULL;
      } else {
        op_current = local_current->operations;
        orig_op_current = original->operations;
        while(op_current->next != NULL) {
          op_current = op_current->next;
          orig_op_current = orig_op_current->next;
        }
        op_current->next = malloc(sizeof(operation_t));
        op_current->next->id = orig_op_current->id;
        op_current->next->type = orig_op_current->type;
        op_current->next->duration = orig_op_current->duration;
        op_current->next->next = NULL;
      }
    }

    for(i = 0; i < local_current->num_resources; i++) {
      if(local_current->resources == NULL) {
        local_current->resources = malloc(sizeof(operation_t));
        local_current->resources->id = original->resources->id;
        local_current->resources->type = original->resources->type;
        local_current->resources->status = original->resources->status;
        local_current->resources->next = NULL;
      } else {
        resource_current = local_current->resources;
        orig_resource_current = original->resources;
        while(resource_current->next != NULL) {
          resource_current = resource_current->next;
          orig_resource_current = orig_resource_current->next;
        }
        resource_current->next = malloc(sizeof(operation_t));
        resource_current->next->id = orig_resource_current->id;
        resource_current->next->type = orig_resource_current->type;
        resource_current->next->status = orig_resource_current->status;
        resource_current->next->next = NULL;
      }
    }







  } else if(!new_list) {
    //Never reaching NULL
    printf("%d\n", CURRENT_OS_RUNTIME );
    while(local_current->next != NULL) {
      if(local_current->process_state != ACTIVE) {
        op_current = local_current->operations;
        orig_op_current = original->operations;
        while(op_current->status == 1 && op_current != NULL && !priority_check){
          op_current = op_current->next;
          printf("op\n" );
        }
        while(orig_op_current->status == 1 && orig_op_current != NULL && !priority_check) {
          orig_op_current = orig_op_current->next;
        }
        if( ((op_current->duration > orig_op_current->duration) && !priority_check) || ((local_current->priority < original->priority) && priority_check) ) {
          node_found = true;
        }
        if(node_found) {
          break;
        }

        local_current = local_current->next;
      }
    }

    printf("org_op\n" );

    new_node->id = original->id;
    new_node->process_state = original->process_state;
    new_node->prog_count = original->prog_count;
    new_node->total_mem = original->total_mem;
    new_node->min_mem = original->min_mem;
    new_node->num_regs = original->num_regs;
    new_node->num_ops = original->num_ops;
    new_node->num_resources = original->num_resources;





    gettimeofday(&new_node->start_wait, NULL);
    new_node->checking_wait = 1;

    // printf("%d--\n",orig_reg_current->id);
    for(i = 0; i < new_node->num_regs; i++) {
      if(new_node->registers == NULL) {
        new_node->registers = malloc(sizeof(reg_t));
        new_node->registers->id = original->registers->id;
        new_node->registers->next = NULL;
      } else {
        reg_current = new_node->registers;
        orig_reg_current = original->registers;
        while(reg_current->next != NULL && orig_reg_current->next != NULL) {
          reg_current = reg_current->next;

          orig_reg_current = orig_reg_current->next;
        }
        if(orig_reg_current == NULL){
          break;
        }


        reg_current->next = malloc(sizeof(reg_t));
        reg_current->next->id = orig_reg_current->id;
        reg_current->next->next = NULL;



      }
    }

    for(i = 0; i < new_node->num_ops; i++) {
      if(new_node->operations == NULL) {
        new_node->operations = malloc(sizeof(operation_t));
        new_node->operations->id = original->operations->id;
        new_node->operations->type = original->operations->type;
        new_node->operations->duration = original->operations->duration;
        new_node->operations->next = NULL;
      } else {
        op_current = new_node->operations;
        orig_op_current = original->operations;
        while(op_current->next != NULL && orig_op_current->next != NULL) {
          op_current = op_current->next;
          orig_op_current = orig_op_current->next;
        }

        if(orig_op_current == NULL) {
          break;
        }

        op_current->next = malloc(sizeof(operation_t));
        op_current->next->id = orig_op_current->id;
        op_current->next->type = orig_op_current->type;
        op_current->next->duration = orig_op_current->duration;
        op_current->next->next = NULL;
      }
    }

    for(i = 0; i < new_node->num_resources; i++) {
      if(new_node->resources == NULL) {
        new_node->resources = malloc(sizeof(operation_t));
        new_node->resources->id = original->resources->id;
        new_node->resources->type = original->resources->type;
        new_node->resources->status = original->resources->status;
        new_node->resources->next = NULL;
      } else {
        resource_current = new_node->resources;
        orig_resource_current = original->resources;
        while(resource_current->next != NULL && orig_resource_current->next != NULL) {
          resource_current = resource_current->next;
          orig_resource_current = orig_resource_current->next;
        }

        if(orig_resource_current == NULL) {
          break;
        }

        resource_current->next = malloc(sizeof(operation_t));
        resource_current->next->id = orig_resource_current->id;
        resource_current->next->type = orig_resource_current->type;
        resource_current->next->status = orig_resource_current->status;
        resource_current->next->next = NULL;
      }
    }



    if(local_current->next == NULL) {
      printf("here--\n");
      local_current->next = new_node;
    } else {
      new_node->next = local_current;
      local_current = new_node;
    }
  }

}
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  appendtoindex(int, int)
//
//   DISC:     This function is meant to insert a node after the node of the
//             specified index.
//
//   ARGS:     int index - The index the new node will be inserted after.
//
//             int id - The id value of the new node.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int appendtoindex(int index, int id) {
//
//     if(index < 0 || (listempty() && index != 0)) { //Invalid index value.
//       return 0;
//     }
//
//     int i;
//     job_t * new_node = malloc(sizeof(job_t));
//     new_node->id = id;
//
//     current = head;
//
//     for( i = 0; i < index; i++) {
//       if(current->next == NULL) {
//         return 0;
//       }
//       current = current->next;
//     }
//     if(index == 0) {
//       new_node->next = head->next;
//       head->next = new_node;
//     } else {
//       new_node->next = current->next;
//       current->next = new_node;
//     }
//
//     return 1;
// }
//
/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  printlist(void)

  DISC:     This function is meant to diplay the contents of the linked list.

  ARGS:     None.

  RETURN:   None.

 * * * * * * * * * * * * * * * * * * * * * * * * */
void printlist(job_t * head) {

  current = head;
  time(&current_time);

  if(current == NULL) {
    sprintf(print_string,"- THE LIST IS EMPTY\n- \n");
    printout(log_file,print_string);
    return;
  }
  while(current != NULL) {
    sprintf(print_string,"- ID: %d\n",current->id);
    printout(log_file,print_string);
    if( CURRENT_OS_RUNTIME >= current->arrival_time) {
      sprintf(print_string,"- ARRIVING: ARRIVED\n");
    } else{
      sprintf(print_string,"- ARRIVING: T - %llu\n", current->arrival_time - CURRENT_OS_RUNTIME );
    }
    printout(log_file,print_string);

    sprintf(print_string,"- PROCESS_STATE\t PROGRAM_COUNT\tTOTAL_MEMORY\tMINIMUM_MEMORY\n");
    printout(log_file,print_string);

    switch(current->process_state) {
      case WAITING:
      sprintf(print_string,"- WAITING\t ");
        printout(log_file,print_string);
        break;
      case READY:
      sprintf(print_string,"- READY\t\t ");
        printout(log_file,print_string);
        break;
      case BUSY:
      sprintf(print_string,"- BUSY\t\t ");
        printout(log_file,print_string);
        break;
      case ACTIVE:
      sprintf(print_string,"- ACTIVE\t ");
        printout(log_file,print_string);
        break;
      case COMPLETE:
      sprintf(print_string,"- COMPLETE\t");
        printout(log_file,print_string);
        break;
    }
    sprintf(print_string,"%d\t\t",current->prog_count);
    printout(log_file,print_string);
    sprintf(print_string,"%d\t\t",current->total_mem);
    printout(log_file,print_string);
    sprintf(print_string,"%d\n",current->min_mem);
    printout(log_file,print_string);

    sprintf(print_string,"- REGISTERS:");
    printout(log_file,print_string);
    if(current->registers != NULL) {
      reg_current = current->registers;
      while(reg_current != NULL){
        sprintf(print_string,"%d ",reg_current->id);
        printout(log_file,print_string);
        reg_current = reg_current->next;
      }
    } else {
      sprintf(print_string,"NONE");
      printout(log_file,print_string);
    }
    sprintf(print_string,"\n");
    printout(log_file,print_string);

    sprintf(print_string,"- OPERATIONS:");
    printout(log_file,print_string);
    if(current->operations != NULL) {
      op_current = current->operations;
      while(op_current != NULL){
        sprintf(print_string,"%d %d %d ",op_current->status, op_current->type, op_current->duration);
        printout(log_file,print_string);
        op_current = op_current->next;
      }
    } else {
      sprintf(print_string,"NONE");
      printout(log_file,print_string);
    }
    sprintf(print_string,"\n-\n");
    printout(log_file,print_string);

    current = current->next;
  }
  sprintf(print_string,"-\n");
  printout(log_file,print_string);
}

/* * * * * * * * * * * * * * * * * * * * * * * * *

  FUCTION:  removehead(void)

  DISC:     This function is meant to remove the head node of the linked list.

  ARGS:     None.

  RETURN:   Return 1 for success and return 0 for failure.

 * * * * * * * * * * * * * * * * * * * * * * * * */
int removehead(int list) {

job_t * temp;
// job_t * head;

switch(list) {
  case JOBS:
    if(JOBS_LIST == NULL) {
      // printout(log_file,"NO JOBS IN LIST\n");
      return 0;
    }
    // printout(log_file,"REMOVING JOBS HEAD\n");
    temp = JOBS_LIST;
    JOBS_LIST = temp->next;
    free(temp);
    break;
  case READY:
    if(READY_Q == NULL) {
      // printout(log_file,"NO JOBS IN READY Q\n");
      return 0;
    }
    // printout(log_file,"REMOVING READY HEAD\n");
    temp = READY_Q;
    READY_Q = temp->next;
    free(temp);
    break;
  case IO:
    if(IO_Q == NULL) {
      // printout(log_file,"NO JOBS IN IO Q\n");
      return 0;
    }
    // printout(log_file,"REMOVING IO HEAD\n");
    temp = IO_Q;
    IO_Q = temp->next;
    free(temp);
    break;
}


  return 1;
}
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removetail(void)
//
//   DISC:     This function is meant to remove the tail node of the linked list.
//
//   ARGS:     None.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removetail(void) {
//   if(listempty()) {
//     return 0;
//   }
//
//   job_t * temp = malloc(sizeof(job_t));
//
//   current = head;
//   while(current->next->next != NULL) {
//     current = current->next;
//   }
//   temp = current->next;
//   current->next = temp->next;
//   free(temp);
//   return 1;
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removenode(int)
//
//   DISC:     This function is meant to remove the node of the linked list
//             specified by the id passed into the function.
//
//   ARGS:     int id- The id value of the node in the linked list to be removed.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removenode(int id) {
//   if(listempty()) {
//     return 0;
//   }
//
//   job_t * temp = malloc(sizeof(job_t));
//
//   current = head;
//   while(current->next != NULL) {
//     if(current->next->id == id) {
//       break;
//     }
//     current = current->next;
//   }
//
//   temp = current->next;
//   current->next = temp->next;
//   free(temp);
//
//   return 1;
// }
//
// /* * * * * * * * * * * * * * * * * * * * * * * * *
//
//   FUCTION:  removeindex(int)
//
//   DISC:     This function removes the node from the linked list at the
//             specified index.
//
//   ARGS:     int index- The index of the node in the linked list to be removed.
//
//   RETURN:   Return 1 for success and return 0 for failure.
//
//  * * * * * * * * * * * * * * * * * * * * * * * * */
// int removeindex(int index) {
//
//   if(listempty()) {
//     return 0;
//   }
//
//   int i;
//   job_t * temp = NULL;
//
//   current = head;
//
//   for( i = 0; i < index-1; i++) {
//     if(current->next->next == NULL) {
//       return 0;
//     }
//     current = current->next;
//   }
//   if(index == 0) {
//     temp = head;
//     head = temp->next;
//   } else {
//     temp = current->next;
//     current->next = temp->next;
//   }
//   free(temp);
//
//
//   return 1;
// }
