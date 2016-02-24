void opcpu(void) {
  // printf("opcpu()\n");

  if(READY_Q == NULL) {
    return;
  } else if(READY_Q->process_state == ACTIVE) {
    CURRENT_CPU_COUNT++;
    op_current = READY_Q->operations;
    // printf("check\n");
    while(op_current != NULL) {
      // printf("check\n");
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }
    if(op_current != NULL && CURRENT_CPU_COUNT >= op_current->duration) {
      // op_current->status = 1;
      // READY_Q->process_state = WAITING;
      current = JOBS_LIST;
      while(current->id != READY_Q->id) {
        if(current == NULL) {
          printf("NO ID FOUND FOR IO\n");
        }
        current = current->next;
      }
      // printf("check\n");
      current->prog_count += CURRENT_CPU_COUNT;
      op_current = current->operations;
      while(op_current != NULL) {
        // printf("check\n");
        if(op_current->status == 0) {
          break;
        }
        op_current = op_current->next;
      }
      // printf("check\n");
      // printf("check\n");
      op_current->status = 1;
      current->process_state = WAITING;
      if(current->checking_cpu == 1) {
        gettimeofday(&current->finish_cpu, NULL);
        current->checking_cpu = 0;
        current->total_cpu_time += 1000 * (current->finish_cpu.tv_sec - current->start_cpu.tv_sec) + (current->finish_cpu.tv_usec - current->start_cpu.tv_usec) / 1000;
      }
      gettimeofday(&current->start_wait, NULL);
      current->checking_wait = 1;

      removehead(READY);
      // printf("--------------------------------------------------------------------\n");
      // printf("JOB LIST\n");
      // printlist(JOBS_LIST);
      //
      // printf("READY QUEUE\n");
      // printlist(READY_Q);
      //
      // printf("IO QUEUE\n");
      // printlist(IO_Q);
      // printf("--------------------------------------------------------------------\n");
    }
    // if(op_current == NULL) {
      // printf("null operation\n");
    // }
  }
}

void opio(void) {
  // printf("opio()\n");

  if(IO_Q == NULL){
    return;
  } else if(IO_Q->process_state == ACTIVE) {
    // printf("here\n");
    CURRENT_IO_COUNT++;
    op_current = IO_Q->operations;
    while(op_current != NULL) {
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }

    if(op_current != NULL && CURRENT_IO_COUNT >= op_current->duration) {
      // op_current->status = 1;
      // IO_Q->process_state = WAITING;
      current = JOBS_LIST;
      while(current->id != IO_Q->id) {
        if(current == NULL) {
          printf("NO ID FOUND FOR IO\n");
        }
        current = current->next;

      }
      current->prog_count += CURRENT_IO_COUNT;
      op_current = current->operations;
      while(op_current != NULL) {
        // printf("check\n");
        if(op_current->status == 0) {
          break;
        }
        op_current = op_current->next;
      }
      // printf("check\n");
      op_current->status = 1;
      current->process_state = WAITING;
      if(current->checking_cpu == 1) {
        gettimeofday(&current->finish_cpu, NULL);
        current->checking_cpu = 0;
        current->total_cpu_time += 1000 * (current->finish_cpu.tv_sec - current->start_cpu.tv_sec) + (current->finish_cpu.tv_usec - current->start_cpu.tv_usec) / 1000;
      }
      gettimeofday(&current->start_wait, NULL);
      current->checking_wait = 1;
      removehead(IO);
      // printf("--------------------------------------------------------------------\n");
      // printf("JOB LIST\n");
      // printlist(JOBS_LIST);
      //
      // printf("READY QUEUE\n");
      // printlist(READY_Q);
      //
      // printf("IO QUEUE\n");
      // printlist(IO_Q);
      // printf("--------------------------------------------------------------------\n");
    }
  } else if (IO_Q->process_state == READY) {
    op_current = IO_Q->operations;
    // elapsed = op_current->duration;

    while(op_current != NULL) {
      if(op_current->status == 0) {
        break;
      }
      op_current = op_current->next;
    }

    if(op_current == NULL) {
      IO_Q->process_state = COMPLETE;
      current = JOBS_LIST;
      while(current->id != IO_Q->id) {
        current = current->next;
      }
      current->process_state = COMPLETE;
      gettimeofday(&current->finish_job, NULL);
      current->total_run_time = 1000 * (current->finish_job.tv_sec - current->start_job.tv_sec) + (current->finish_job.tv_usec - current->start_job.tv_usec) / 1000;

      removehead(IO);


    }

    if(op_current->status == 0) {
      printf("NEW IO OPERTATION\n");
      // cpu_op_finish_time = current_time + op_current->duration;
      // previous_time = op_current->duration;
      IO_Q->process_state = ACTIVE;
      CURRENT_IO_COUNT = 0;
      current = JOBS_LIST;
      while(current->id != IO_Q->id) {
        current = current->next;
      }
      current->process_state = BUSY;
      if(current->job_started == 0){
        gettimeofday(&current->start_job, NULL);
        current->job_started = 1;
      }
      if(current->checking_wait == 1) {
        gettimeofday(&current->finish_wait, NULL);
        current->checking_wait = 0;
        current->total_wait_time += 1000 * (current->finish_wait.tv_sec - current->start_wait.tv_sec) + (current->finish_wait.tv_usec - current->start_wait.tv_usec) / 1000;
        if(current->response_checked == 0) {
          printf("1 %d-%ld / %ld\n",current->id,1000*current->finish_wait.tv_sec+current->finish_wait.tv_usec/1000,1000*current->start_job.tv_sec+current->start_job.tv_usec/1000);
          current->response_time = 1000 * (current->finish_wait.tv_sec - current->on_line.tv_sec) + (current->finish_wait.tv_usec - current->on_line.tv_usec) / 1000;
          current->response_checked = 1;
        }
      }
      gettimeofday(&current->start_cpu, NULL);
      current->checking_cpu = 1;

    }
    printf("-----------------------------PRINT %4.0d-----------------------------\n",++print_count);
    printf("JOB LIST\n");
    printlist(JOBS_LIST);

    printf("READY QUEUE\n");
    printlist(READY_Q);

    printf("IO QUEUE\n");
    printlist(IO_Q);
    printf("--------------------------------------------------------------------\n");
  }


}

void printdetails(void) {

    uint32_t temp_total_wait_time, temp_total_cpu_time, job_count;
    temp_total_cpu_time = 0;
    temp_total_wait_time = 0;
    job_count = 0;

    current = JOBS_LIST;
    while(current != NULL) {
      job_count++;
      temp_total_wait_time += current->total_wait_time;
      temp_total_cpu_time += current->total_cpu_time;
      current = current->next;
    }

    if(job_count == 0) {
      printf("NO JOBS RECIEVED\n");
    }


    printf("\n\n*********************** ALL JOBS COMPlETE ***********************\n");
    printf("\nTOTAL RUN TIME: %lldms\n",prog_total_time);
    printf("TOTAL CPU TIME: %ums\n", temp_total_cpu_time);
    printf("AVERAGE TOTAL WAIT TIME: %0.2fm\n", (float)temp_total_wait_time/job_count);

    current = JOBS_LIST;
    while(current != NULL) {

      current->average_wait_time = (float)current->total_wait_time/current->num_ops;

      printf("\n");
      printf("JOB: %d\n",current->id);
      printf("RESPONSE TIME: %ums\n", current->response_time);
      printf("TOTAL RUN TIME: %ums\n", current->total_run_time);
      printf("TOTAL CPU TIME: %ums\n", current->total_cpu_time);
      printf("TOTAL WAIT TIME: %ums\n", current->total_wait_time);
      printf("AVERAGE WAIT TIME: %0.2fms\n", current->average_wait_time);
      printf("\n");
      current = current->next;
    }

}

static inline void start()
{
    gettimeofday(&prog_start_time, NULL);
}

static inline void stop()
{

    gettimeofday(&prog_end_time, NULL);

    prog_total_time = 1000 * (prog_end_time.tv_sec - prog_start_time.tv_sec) + (prog_end_time.tv_usec - prog_start_time.tv_usec) / 1000;
}
