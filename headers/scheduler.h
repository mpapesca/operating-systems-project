
int nextoperation(job_t *job) {

  int elapsed = 0;

  op_current = job->operations;

  while(elapsed < job->prog_count && op_current != NULL) {
    elapsed += op_current->duration;
    op_current = op_current->next;
  }

  if(op_current == NULL) {
    printf("op finished\n");
    return OP_FIN;
  }
  printf("op type:%d", op_current->type);
  return op_current->type;
}

/**
 * [longtermscheduler description]
 */
void longtermscheduler(void) {

  job_t * queue_tail;
  reg_t * queue_reg;

  operation_t * queue_op;


  current = JOBS_LIST;

  while(current != NULL) {
    if(current->process_state == WAITING) {

      switch (nextoperation(current)) {
        case CPU_OP:
          current->process_state = READY;
          queue_tail = READY_Q;
          break;
        case IO_OP:
          current->process_state = BUSY;
          queue_tail = IO_Q;
          break;
      }

      while(queue_tail != NULL){
        queue_tail = queue_tail->next;
      }
      queue_tail = malloc(sizeof(job_t));

      queue_tail->id = current->id;
      queue_tail->process_state = current->process_state;
      queue_tail->prog_count = current->prog_count;
      queue_tail->total_mem = current->total_mem;
      queue_tail->min_mem = current->min_mem;
      queue_tail->num_regs = current->num_regs;
      queue_tail->num_ops = current->num_ops;

      if(current->registers != NULL) {
        queue_reg = queue_tail->registers;
        reg_current = current->registers;
        while(reg_current != NULL) {
          queue_reg = malloc(sizeof(reg_t));
          queue_reg->id = reg_current->id;
          queue_reg->next = NULL;
          reg_current = reg_current->next;
        }
      }

      if(current->operations != NULL) {
        queue_op = queue_tail->operations;
        op_current = current->operations;
        while(op_current != NULL) {
          queue_op = malloc(sizeof(operation_t));
          queue_op->id = op_current->id;
          queue_op->type = op_current->type;
          queue_op->duration = op_current->duration;
          queue_op->next = NULL;
          op_current = op_current->next;
        }
      }

      queue_tail->next = NULL;
    }
    current = current->next;
  }
}


/**
 * [shorttermscheduler description]
 */
void shorttermscheduler(void) {

}