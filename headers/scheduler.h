
int nextoperation(job_t *job) {
  // printf("nextoperation()\n");

  int elapsed = 0;

  op_current = job->operations;

  while( op_current != NULL) {
    if(op_current->status == 0) {
      break;
    }
    op_current = op_current->next;
  }

  if(op_current == NULL) {
    printf("JOB %d OPERATIONS FINISHED\n", job->id);
    return OP_FIN;
  }
  return op_current->type;
}

/**
 * [longtermscheduler description]
 */
void longtermscheduler(void) {
  // printf("longtermscheduler()\n");
  job_t * queue_tail;
  reg_t * queue_reg;
  operation_t * queue_op;
  int found = 0;


  current = JOBS_LIST;
  while(current != NULL) {
    if(current->process_state == WAITING) {
      found = 1;

      switch(nextoperation(current)) {
        case CPU_OP:
          current->process_state = READY;

          if(READY_Q == NULL) {
            READY_Q = malloc(sizeof(job_t));

            queue_tail = READY_Q;
          } else {
            queue_tail = READY_Q;
            while(queue_tail->next != NULL) {
              queue_tail = queue_tail->next;
            }
            queue_tail->next = malloc(sizeof(job_t));
            queue_tail = queue_tail->next;
          }

          break;
        case IO_OP:

          current->process_state = BUSY;

          if(IO_Q == NULL) {
            IO_Q = malloc(sizeof(job_t));
            queue_tail = IO_Q;
          } else {
            queue_tail = IO_Q;
            while(queue_tail->next != NULL) {
              queue_tail = queue_tail->next;
            }
            queue_tail->next = malloc(sizeof(job_t));
            queue_tail = queue_tail->next;
          }

          break;
        case OP_FIN:
          current->process_state = COMPLETE;
          printf("--------------------------------------------------------------------\n");
          printf("JOB LIST\n");
          printlist(JOBS_LIST);

          printf("READY QUEUE\n");
          printlist(READY_Q);

          printf("IO QUEUE\n");
          printlist(IO_Q);
          printf("--------------------------------------------------------------------\n");
          continue;
          // break;
        default:

          break;
      }


      queue_tail->id = current->id;

      queue_tail->process_state = READY;
      queue_tail->prog_count = current->prog_count;
      queue_tail->total_mem = current->total_mem;
      queue_tail->min_mem = current->min_mem;
      queue_tail->num_regs = current->num_regs;
      queue_tail->num_ops = current->num_ops;

      if(current->registers != NULL) {
        if(queue_tail->registers == NULL) {
          queue_tail->registers = malloc(sizeof(reg_t));
        }
        queue_reg = queue_tail->registers;
        reg_current = current->registers;
        while(reg_current != NULL) {
          queue_reg->id = reg_current->id;
          queue_reg->next = NULL;
          reg_current = reg_current->next;
          if(reg_current != NULL) {
            queue_reg->next = malloc(sizeof(reg_t));
          }
          queue_reg = queue_reg->next;
        }
      }


      if(current->operations != NULL) {
        if(queue_tail->operations == NULL) {
          queue_tail->operations = malloc(sizeof(operation_t));
        }
        queue_op = queue_tail->operations;
        op_current = current->operations;
        while(op_current != NULL) {
          queue_op->id = op_current->id;
          queue_op->type = op_current->type;
          queue_op->duration = op_current->duration;
          queue_op->next = NULL;
          op_current = op_current->next;
          if(op_current != NULL) {
            queue_op->next = malloc(sizeof(operation_t));
          }
          queue_op = queue_op->next;
        }
      }


      queue_tail->next = NULL;



    }
    current = current->next;
  }
  if(found){

  }
}


/**
 * [shorttermscheduler description]
 */
void shorttermscheduler(void) { //Still needs a lot of work.

  // printf("shorttermscheduler()\n");

  if(READY_Q == NULL) {
    return;
  }

  int elapsed = 0;

  time ( &current_time );

  if(READY_Q->process_state == READY) {

    op_current = READY_Q->operations;


    while(op_current != NULL) {
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }

    if(op_current == NULL) {
      READY_Q->process_state = COMPLETE;
      current = JOBS_LIST;
      while(current->id != READY_Q->id) {
        current = current->next;
      }
      current->process_state = COMPLETE;
      removehead(READY);

    }

    if(op_current->status == 0) {
      printf("NEW CPU OPERTATION\n");
      READY_Q->process_state = ACTIVE;
      CURRENT_CPU_COUNT = 0;
      current = JOBS_LIST;
      while(current->id != READY_Q->id) {
        current = current->next;
      }
      current->process_state = ACTIVE;
      printf("--------------------------------------------------------------------\n");
      printf("JOB LIST\n");
      printlist(JOBS_LIST);

      printf("READY QUEUE\n");
      printlist(READY_Q);

      printf("IO QUEUE\n");
      printlist(IO_Q);
      printf("--------------------------------------------------------------------\n");
    }

  }


}
