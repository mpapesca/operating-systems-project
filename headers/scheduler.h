
int nextoperation(job_t *job) {
  // fprintf(log_file,"nextoperation()\n");

  int elapsed = 0;

  op_current = job->operations;

  while( op_current != NULL) {
    if(op_current->status == 0) {
      break;
    }
    op_current = op_current->next;
  }

  if(op_current == NULL) {
    // fprintf(log_file,"JOB %d OPERATIONS FINISHED\n", job->id);
    return OP_FIN;
  }
  return op_current->type;
}

/**
 * [longtermscheduler description]
 */
int longtermscheduler(void) {
  // fprintf(log_file,"longtermscheduler()\n");
  job_t * queue_tail;
  reg_t * queue_reg;
  operation_t * queue_op;
  int found_waiting = 0;
  int found_active = 0;
  int found_busy = 0;


  current = JOBS_LIST;
  while(current != NULL) {
    if(current->process_state == WAITING) {
      found_waiting = 1;

      switch(nextoperation(current)) {
        case CPU_OP:
          current->process_state = READY;
          if(current->response_checked == 0) {
            gettimeofday(&current->on_line, NULL);
          }

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
          if(current->checking_wait == 1) {
            gettimeofday(&current->finish_wait, NULL);
            current->checking_wait = 0;
            current->total_wait_time += 1000 * (current->finish_wait.tv_sec - current->start_wait.tv_sec) + (current->finish_wait.tv_usec - current->start_wait.tv_usec) / 1000;
            if(current->response_checked == 0) {
              // fprintf(log_file,"2 %d-%ld / %ld\n",current->id,1000*current->finish_wait.tv_sec+current->finish_wait.tv_usec/1000,1000*current->start_job.tv_sec+current->start_job.tv_usec/1000);
              current->response_time = 1000 * (current->finish_wait.tv_sec - current->on_line.tv_sec) + (current->finish_wait.tv_usec - current->on_line.tv_usec) / 1000;
              // current->response_time = 1000 * (current->finish_wait.tv_sec - current->start_job.tv_sec) + (current->finish_wait.tv_usec - current->start_job.tv_usec) / 1000;
              current->response_checked = 1;
            }
          }
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
          if(current->checking_cpu == 1) {
            gettimeofday(&current->finish_cpu, NULL);
            current->checking_cpu = 0;
            current->total_cpu_time += 1000 * (current->finish_cpu.tv_sec - current->start_cpu.tv_sec) + (current->finish_cpu.tv_usec - current->start_cpu.tv_usec) / 1000;
          }
          gettimeofday(&current->finish_job, NULL);
          current->total_run_time = 1000 * (current->finish_job.tv_sec - current->start_job.tv_sec) + (current->finish_job.tv_usec - current->start_job.tv_usec) / 1000;
          fprintf(log_file,"-----------------------------PRINT %0.4d-----------------------------\n",print_count++);
          fprintf(log_file,"- JOB LIST\n");
          printlist(JOBS_LIST);

          fprintf(log_file,"- READY QUEUE\n");
          printlist(READY_Q);

          fprintf(log_file,"- IO QUEUE\n");
          printlist(IO_Q);
          fprintf(log_file,"--------------------------------------------------------------------\n\n\n\n");
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



    } else if(current->process_state == ACTIVE) {
      found_active = 1;
    } else if(current->process_state == BUSY) {
      found_busy = 1;
    }
    current = current->next;
  }

  if( !found_waiting && !found_active && !found_busy ) {
    return 1;
  }
  return 0;
}


/**
 * [shorttermscheduler description]
 */
void shorttermscheduler(void) { //Still needs a lot of work.

  // fprintf(log_file,"shorttermscheduler()\n");

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
      if(current->checking_cpu == 1) {
        gettimeofday(&current->finish_cpu, NULL);
        current->checking_cpu = 0;
        current->total_cpu_time += 1000 * (current->finish_cpu.tv_sec - current->start_cpu.tv_sec) + (current->finish_cpu.tv_usec - current->start_cpu.tv_usec) / 1000;
      }
      gettimeofday(&current->finish_job, NULL);
      current->total_run_time = 1000 * (current->finish_job.tv_sec - current->start_job.tv_sec) + (current->finish_job.tv_usec - current->start_job.tv_usec) / 1000;

      removehead(READY);

    }

    if(op_current->status == 0) {
      // fprintf(log_file,"NEW CPU OPERATION\n");
      READY_Q->process_state = ACTIVE;
      CURRENT_CPU_COUNT = 0;
      current = JOBS_LIST;
      while(current->id != READY_Q->id) {
        current = current->next;
      }
      current->process_state = ACTIVE;
      if(current->job_started == 0){
        gettimeofday(&current->start_job, NULL);
        current->job_started = 1;
      }
      if(current->checking_wait == 1) {
        gettimeofday(&current->finish_wait, NULL);
        current->checking_wait = 0;
        current->total_wait_time += 1000 * (current->finish_wait.tv_sec - current->start_wait.tv_sec) + (current->finish_wait.tv_usec - current->start_wait.tv_usec) / 1000;
        if(current->response_checked == 0) {
          // fprintf(log_file,"3 %d-%ld / %ld\n",current->id,1000*current->finish_wait.tv_sec+current->finish_wait.tv_usec/1000,1000*current->start_job.tv_sec+current->start_job.tv_usec/1000);
          current->response_time = 1000 * (current->finish_wait.tv_sec - current->on_line.tv_sec) + (current->finish_wait.tv_usec - current->on_line.tv_usec) / 1000;
          // current->response_time = 1000 * (current->finish_wait.tv_sec - current->start_job.tv_sec) + (current->finish_wait.tv_usec - current->start_job.tv_usec) / 1000;
          current->response_checked = 1;
        }
      }
      gettimeofday(&current->start_cpu, NULL);
      current->checking_cpu = 1;
      fprintf(log_file,"-----------------------------PRINT %0.4d-----------------------------\n",print_count++);
      fprintf(log_file,"- JOB LIST\n");
      printlist(JOBS_LIST);

      fprintf(log_file,"- READY QUEUE\n");
      printlist(READY_Q);

      fprintf(log_file,"- IO QUEUE\n");
      printlist(IO_Q);
      fprintf(log_file,"--------------------------------------------------------------------\n\n\n\n");
    }

  }


}
